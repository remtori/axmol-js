// From https://github.com/denoland/deno/blob/59c416662b4b52e37731893f89012a86c8447555/ext/node/polyfills/01_require.js
// Also reference https://github.com/nodejs/node/blob/ef2e0848ba366ca278d936f1f793d455188e792e/lib/module.js

"use strict";

((window) => {
    const { core, primordials, ops, internals } = window.__bootstrap;
    const { op_require_read_file, op_require_real_path, op_require_stat, op_require_cwd } = ops;
    const {
        ArrayIsArray,
        ArrayPrototypeIncludes,
        ArrayPrototypeIndexOf,
        ArrayPrototypeJoin,
        ArrayPrototypePush,
        ArrayPrototypeUnshiftApply,
        ArrayPrototypeSlice,
        ArrayPrototypeSplice,
        Error,
        JSONParse,
        ObjectCreate,
        ObjectEntries,
        ObjectGetOwnPropertyDescriptor,
        ObjectGetPrototypeOf,
        ObjectHasOwn,
        ObjectKeys,
        ObjectPrototype,
        ObjectSetPrototypeOf,
        Proxy,
        RegExpPrototypeTest,
        SafeMap,
        SafeWeakMap,
        String,
        StringPrototypeCharAt,
        StringPrototypeCharCodeAt,
        StringPrototypeEndsWith,
        StringPrototypeIncludes,
        StringPrototypeIndexOf,
        StringPrototypeSlice,
        StringPrototypeStartsWith,
        TypeError,
    } = primordials;

    const nativeModuleExports = ObjectCreate(null);
    const builtinModules = [];

    function setupBuiltinModules() {
        const nodeModules = {
            module: Module,
            path: internals.path,
            'internal/ops': ops,
            'internal': core,
        };
        for (const [name, moduleExports] of ObjectEntries(nodeModules)) {
            nativeModuleExports[name] = moduleExports;
            ArrayPrototypePush(builtinModules, name);
        }
    }
    setupBuiltinModules();

    function pathDirname(filepath) {
        if (filepath == null) {
            throw new Error("Empty filepath.");
        } else if (filepath === "") {
            return ".";
        }
        return internals.path.dirname(filepath);
    }

    function pathResolve(...args) {
        return internals.path.resolve(...args);
    }

    function isRequestRelative(request) {
        if (
            StringPrototypeStartsWith(request, "./") ||
            StringPrototypeStartsWith(request, "../") ||
            request === ".."
        ) {
            return true;
        }

        if (
            StringPrototypeStartsWith(request, ".\\") ||
            StringPrototypeStartsWith(request, "..\\")
        ) {
            return true;
        }

        return false;
    }

    const nativeModulePolyfill = new SafeMap();

    const relativeResolveCache = ObjectCreate(null);
    let requireDepth = 0;
    let statCache = null;
    let mainModule = null;
    // Are we running with --node-modules-dir flag or byonm?
    let usesLocalNodeModulesDir = false;

    function stat(filename) {
        // TODO: required only on windows
        // filename = path.toNamespacedPath(filename);
        if (statCache !== null) {
            const result = statCache.get(filename);
            if (result !== undefined) {
                return result;
            }
        }
        const result = op_require_stat(filename);
        if (statCache !== null && result >= 0) {
            statCache.set(filename, result);
        }

        return result;
    }

    function updateChildren(parent, child, scan) {
        if (!parent) {
            return;
        }

        const children = parent.children;
        if (children && !(scan && ArrayPrototypeIncludes(children, child))) {
            ArrayPrototypePush(children, child);
        }
    }

    function tryFile(requestPath, _isMain) {
        const rc = stat(requestPath);
        if (rc !== 0) return;
        return toRealPath(requestPath);
    }

    function tryPackage(requestPath, exts, isMain, originalPath) {
        throw new Error(`We dont support require from node_modules (yet!!)`);
    }

    const realpathCache = new SafeMap();
    function toRealPath(requestPath) {
        const maybeCached = realpathCache.get(requestPath);
        if (maybeCached) {
            return maybeCached;
        }
        const rp = op_require_real_path(requestPath);
        realpathCache.set(requestPath, rp);
        return rp;
    }

    function tryExtensions(p, exts, isMain) {
        for (let i = 0; i < exts.length; i++) {
            const filename = tryFile(p + exts[i], isMain);

            if (filename) {
                return filename;
            }
        }
        return false;
    }

    /**
     * Tries to get the absolute file path of the parent module.
     * @param {Module} parent The parent module object.
     */
    function trySelfParentPath(parent) {
        if (!parent) {
            return false;
        }

        if (parent.filename) {
            return parent.filename;
        } else if (parent.id === "<repl>" || parent.id === "internal/preload") {
            return false;
        }
    }

    /**
     * Attempt to resolve a module request using the parent module package metadata.
     * @param {string} parentPath The path of the parent module
     * @param {string} request The module request to resolve
     */
    function trySelf(parentPath, request, conditions) {
        if (!parentPath) {
            return false;
        }

        const pkg = packageJsonReader.getNearestParentPackageJSON(parentPath);
        if (pkg?.data.exports === undefined || pkg.data.name === undefined) {
            return false;
        }

        let expansion;
        if (request === pkg.data.name) {
            expansion = ".";
        } else if (StringPrototypeStartsWith(request, `${pkg.data.name}/`)) {
            expansion =
                "." + StringPrototypeSlice(request, pkg.data.name.length);
        } else {
            return false;
        }

        try {
            const {
                packageExportsResolve,
            } = require("internal/modules/esm/resolve");
            return finalizeEsmResolution(
                packageExportsResolve(
                    pathToFileURL(pkg.path),
                    expansion,
                    pkg.data,
                    pathToFileURL(parentPath),
                    conditions
                ),
                parentPath,
                pkg.path
            );
        } catch (e) {
            if (e.code === "ERR_MODULE_NOT_FOUND") {
                throw createEsmNotFoundErr(request, pkg.path);
            }
            throw e;
        }
    }

    // Find the longest (possibly multi-dot) extension registered in
    // Module._extensions
    function findLongestRegisteredExtension(filename) {
        const name = internals.path.basename(filename);
        let currentExtension;
        let index;
        let startIndex = 0;
        while ((index = StringPrototypeIndexOf(name, ".", startIndex)) !== -1) {
            startIndex = index + 1;
            if (index === 0) continue; // Skip dotfiles like .gitignore
            currentExtension = StringPrototypeSlice(name, index);
            if (Module._extensions[currentExtension]) {
                return currentExtension;
            }
        }
        return ".js";
    }

    function getExportsForCircularRequire(module) {
        if (
            module.exports &&
            ObjectGetPrototypeOf(module.exports) === ObjectPrototype &&
            // Exclude transpiled ES6 modules / TypeScript code because those may
            // employ unusual patterns for accessing 'module.exports'. That should
            // be okay because ES6 modules have a different approach to circular
            // dependencies anyway.
            !module.exports.__esModule
        ) {
            // This is later unset once the module is done loading.
            ObjectSetPrototypeOf(
                module.exports,
                CircularRequirePrototypeWarningProxy
            );
        }

        return module.exports;
    }

    function emitCircularRequireWarning(prop) {
        console.warn(
            `Accessing non-existent property '${String(
                prop
            )}' of module exports ` + "inside circular dependency"
        );
    }

    // A Proxy that can be used as the prototype of a module.exports object and
    // warns when non-existent properties are accessed.
    const CircularRequirePrototypeWarningProxy = new Proxy(
        {},
        {
            get(target, prop) {
                // Allow __esModule access in any case because it is used in the output
                // of transpiled code to determine whether something comes from an
                // ES module, and is not used as a regular key of `module.exports`.
                if (prop in target || prop === "__esModule")
                    return target[prop];
                emitCircularRequireWarning(prop);
                return undefined;
            },

            getOwnPropertyDescriptor(target, prop) {
                if (ObjectHasOwn(target, prop) || prop === "__esModule") {
                    return ObjectGetOwnPropertyDescriptor(target, prop);
                }
                emitCircularRequireWarning(prop);
                return undefined;
            },
        }
    );

    const moduleParentCache = new SafeWeakMap();
    function Module(id = "", parent) {
        this.id = id;
        this.path = pathDirname(id);
        this.exports = {};
        moduleParentCache.set(this, parent);
        updateChildren(parent, this, false);
        this.filename = null;
        this.loaded = false;
        this.parent = parent;
        this.children = [];
    }

    Module.builtinModules = builtinModules;

    Module._extensions = ObjectCreate(null);
    Module._cache = ObjectCreate(null);
    Module._pathCache = ObjectCreate(null);
    let modulePaths = [];
    Module.globalPaths = modulePaths;

    const CHAR_FORWARD_SLASH = 47;
    const TRAILING_SLASH_REGEX = /(?:^|\/)\.?\.$/;

    Module._findPath = function (request, paths, isMain, parentPath) {
        const absoluteRequest = internals.path.isAbsolute(request);
        if (absoluteRequest) {
            paths = [""];
        } else if (!paths || paths.length === 0) {
            return false;
        }

        const cacheKey = request + "\x00" + ArrayPrototypeJoin(paths, "\x00");
        const entry = Module._pathCache[cacheKey];
        if (entry) {
            return entry;
        }

        let exts;
        let trailingSlash =
            request.length > 0 &&
            StringPrototypeCharCodeAt(request, request.length - 1) ===
                CHAR_FORWARD_SLASH;
        if (!trailingSlash) {
            trailingSlash = RegExpPrototypeTest(TRAILING_SLASH_REGEX, request);
        }

        // For each path
        for (let i = 0; i < paths.length; i++) {
            // Don't search further if path doesn't exist
            const curPath = paths[i];
            if (curPath && stat(curPath) < 1) continue;

            let basePath = pathResolve(curPath, request);
            let filename;

            const rc = stat(basePath);
            if (!trailingSlash) {
                if (rc === 0) {
                    // File.
                    filename = toRealPath(basePath);
                }

                if (!filename) {
                    // Try it with each of the extensions
                    if (exts === undefined) {
                        exts = ObjectKeys(Module._extensions);
                    }
                    filename = tryExtensions(basePath, exts, isMain);
                }
            }

            if (!filename && rc === 1) {
                // Directory.
                // try it with each of the extensions at "index"
                if (exts === undefined) {
                    exts = ObjectKeys(Module._extensions);
                }
                filename = tryPackage(basePath, exts, isMain, request);
            }

            if (filename) {
                Module._pathCache[cacheKey] = filename;
                return filename;
            }
        }

        return false;
    };

    /**
     * Get a list of potential module directories
     * @param {string} fromPath The directory name of the module
     * @returns {string[]} List of module directories
     */
    Module._nodeModulePaths = function (fromPath) {
        // return op_require_node_module_paths(fromPath);
        return [];
    };

    Module._resolveLookupPaths = function (request, parent) {
        const paths = [];

        if (isRequestRelative(request)) {
            ArrayPrototypePush(
                paths,
                parent?.filename ? internals.path.dirname(parent.filename) : "."
            );
            return paths;
        }

        // Check for node modules paths.
        if (
            StringPrototypeCharAt(request, 0) !== "." ||
            (request.length > 1 &&
                StringPrototypeCharAt(request, 1) !== "." &&
                StringPrototypeCharAt(request, 1) !== "/" &&
                (!isWindows || StringPrototypeCharAt(request, 1) !== "\\"))
        ) {
            /** @type {string[]} */
            let paths;
            if (parent?.paths?.length) {
                paths = ArrayPrototypeSlice(modulePaths);
                ArrayPrototypeUnshiftApply(paths, parent.paths);
            } else {
                paths = modulePaths;
            }

            return paths.length > 0 ? paths : null;
        }

        const parentDir = [path.dirname(parent.filename)];
        return parentDir;
    };

    Module._load = function (request, parent, isMain) {
        let relResolveCacheIdentifier;
        if (parent) {
            // Fast path for (lazy loaded) modules in the same directory. The indirect
            // caching is required to allow cache invalidation without changing the old
            // cache key names.
            relResolveCacheIdentifier = `${parent.path}\x00${request}`;
            const filename = relativeResolveCache[relResolveCacheIdentifier];
            if (filename !== undefined) {
                const cachedModule = Module._cache[filename];
                if (cachedModule !== undefined) {
                    updateChildren(parent, cachedModule, true);
                    if (!cachedModule.loaded) {
                        return getExportsForCircularRequire(cachedModule);
                    }
                    return cachedModule.exports;
                }
                delete relativeResolveCache[relResolveCacheIdentifier];
            }
        }

        const filename = Module._resolveFilename(request, parent, isMain);
        if (StringPrototypeStartsWith(filename, "node:")) {
            // Slice 'node:' prefix
            const id = StringPrototypeSlice(filename, 5);

            const module = loadNativeModule(id, id);
            if (!module) {
                // TODO:
                // throw new ERR_UNKNOWN_BUILTIN_MODULE(filename);
                throw new Error("Unknown built-in module");
            }

            return module.exports;
        }

        const cachedModule = Module._cache[filename];
        if (cachedModule !== undefined) {
            updateChildren(parent, cachedModule, true);
            if (!cachedModule.loaded) {
                return getExportsForCircularRequire(cachedModule);
            }
            return cachedModule.exports;
        }

        const mod = loadNativeModule(filename, request);
        if (mod) {
            return mod.exports;
        }
        // Don't call updateChildren(), Module constructor already does.
        const module = cachedModule || new Module(filename, parent);

        if (isMain) {
            mainModule = module;
            module.id = ".";
        }

        Module._cache[filename] = module;
        if (parent !== undefined) {
            relativeResolveCache[relResolveCacheIdentifier] = filename;
        }

        let threw = true;
        try {
            module.load(filename);
            threw = false;
        } finally {
            if (threw) {
                delete Module._cache[filename];
                if (parent !== undefined) {
                    delete relativeResolveCache[relResolveCacheIdentifier];
                    const children = parent?.children;
                    if (ArrayIsArray(children)) {
                        const index = ArrayPrototypeIndexOf(children, module);
                        if (index !== -1) {
                            ArrayPrototypeSplice(children, index, 1);
                        }
                    }
                }
            } else if (
                module.exports &&
                ObjectGetPrototypeOf(module.exports) ===
                    CircularRequirePrototypeWarningProxy
            ) {
                ObjectSetPrototypeOf(module.exports, ObjectPrototype);
            }
        }

        return module.exports;
    };

    Module._resolveFilename = function (request, parent, isMain, options) {
        if (
            StringPrototypeStartsWith(request, "node:") ||
            nativeModuleCanBeRequiredByUsers(request)
        ) {
            return request;
        }

        let paths;

        if (typeof options === "object" && options !== null) {
            if (ArrayIsArray(options.paths)) {
                const isRelative = isRequestRelative(request);

                if (isRelative) {
                    paths = options.paths;
                } else {
                    const fakeParent = new Module("", null);
                    paths = [];

                    for (let i = 0; i < options.paths.length; i++) {
                        const path = options.paths[i];
                        fakeParent.paths = Module._nodeModulePaths(path);
                        const lookupPaths = Module._resolveLookupPaths(
                            request,
                            fakeParent
                        );

                        for (let j = 0; j < lookupPaths.length; j++) {
                            if (
                                !ArrayPrototypeIncludes(paths, lookupPaths[j])
                            ) {
                                ArrayPrototypePush(paths, lookupPaths[j]);
                            }
                        }
                    }
                }
            } else if (options.paths === undefined) {
                paths = Module._resolveLookupPaths(request, parent);
            } else {
                // TODO:
                // throw new ERR_INVALID_ARG_VALUE("options.paths", options.paths);
                throw new Error(
                    "Invalid arg value options.paths",
                    options.path
                );
            }
        } else {
            paths = Module._resolveLookupPaths(request, parent);
        }

        // Try module self resolution first
        const parentPath = trySelfParentPath(
            !!parent,
            parent?.filename,
            parent?.id
        );
        const selfResolved = trySelf(parentPath, request);
        if (selfResolved) {
            const cacheKey =
                request +
                "\x00" +
                (paths.length === 1
                    ? paths[0]
                    : ArrayPrototypeJoin(paths, "\x00"));
            Module._pathCache[cacheKey] = selfResolved;
            return selfResolved;
        }

        // Look up the filename first, since that's the cache key.
        const filename = Module._findPath(request, paths, isMain, parentPath);
        if (filename) {
            return op_require_real_path(filename);
        }
        const requireStack = [];
        for (
            let cursor = parent;
            cursor;
            cursor = moduleParentCache.get(cursor)
        ) {
            ArrayPrototypePush(requireStack, cursor.filename || cursor.id);
        }
        let message = `Cannot find module '${request}'`;
        if (requireStack.length > 0) {
            message =
                message +
                "\nRequire stack:\n- " +
                ArrayPrototypeJoin(requireStack, "\n- ");
        }
        // eslint-disable-next-line no-restricted-syntax
        const err = new Error(message);
        err.code = "MODULE_NOT_FOUND";
        err.requireStack = requireStack;

        // fallback and attempt to resolve bare specifiers using
        // the global cache when not using --node-modules-dir
        if (
            !usesLocalNodeModulesDir &&
            ArrayIsArray(options?.paths) &&
            request[0] !== "." &&
            request[0] !== "#" &&
            !request.startsWith("file:///") &&
            !isRequestRelative(request) &&
            !internals.path.isAbsolute(request)
        ) {
            try {
                return Module._resolveFilename(request, parent, isMain, {
                    ...options,
                    paths: undefined,
                });
            } catch {
                // ignore
            }
        }

        // throw the original error
        throw err;
    };

    /**
     * Internal CommonJS API to always require modules before requiring the actual
     * one when calling `require("my-module")`. This is used by require hooks such
     * as `ts-node/register`.
     * @param {string[]} requests List of modules to preload
     */
    Module._preloadModules = function (requests) {
        if (!ArrayIsArray(requests) || requests.length === 0) {
            return;
        }

        const parent = new Module("internal/preload", null);
        // All requested files must be resolved against cwd
        parent.paths = Module._nodeModulePaths(op_require_cwd());
        for (let i = 0; i < requests.length; i++) {
            parent.require(requests[i]);
        }
    };

    Module.prototype.load = function (filename) {
        if (this.loaded) {
            throw new Error("Module already loaded");
        }

        // Canonicalize the path so it's not pointing to the symlinked directory
        // in `node_modules` directory of the referrer.
        this.filename = op_require_real_path(filename);
        this.paths = Module._nodeModulePaths(pathDirname(this.filename));
        const extension = findLongestRegisteredExtension(filename);
        Module._extensions[extension](this, this.filename);
        this.loaded = true;

        // TODO: do caching
    };

    // Loads a module at the given file path. Returns that module's
    // `exports` property.
    Module.prototype.require = function (id) {
        if (typeof id !== "string") {
            // TODO(bartlomieju): it should use different error type
            // ("ERR_INVALID_ARG_VALUE")
            throw new TypeError("Invalid argument type");
        }

        if (id === "") {
            // TODO(bartlomieju): it should use different error type
            // ("ERR_INVALID_ARG_VALUE")
            throw new TypeError("id must be non empty");
        }
        requireDepth++;
        try {
            return Module._load(id, this, /* isMain */ false);
        } finally {
            requireDepth--;
        }
    };

    Module.wrapper = [
        "(function (exports, require, module, __filename, __dirname) { ",
        "\n});",
    ];
    Module.wrap = function (script) {
        script = script.replace(/^#!.*?\n/, "");
        return `${Module.wrapper[0]}${script}${Module.wrapper[1]}`;
    };

    function wrapSafe(filename, content, cjsModuleInstance, format) {
        const wrapper = Module.wrap(content);
        const [f, err] = core.evalContext(wrapper, filename, [
            format !== "module",
        ]);
        if (err) {
            throw err.thrown;
        }
        return f;
    }

    Module.prototype._compile = function (content, filename, format) {
        const compiledWrapper = wrapSafe(filename, content, this, format);

        const dirname = pathDirname(filename);
        const require = makeRequireFunction(this);
        const exports = this.exports;
        const thisValue = exports;
        if (requireDepth === 0) {
            statCache = new SafeMap();
        }
        const result = compiledWrapper.call(
            thisValue,
            exports,
            require,
            this,
            filename,
            dirname
        );
        if (requireDepth === 0) {
            statCache = null;
        }
        return result;
    };

    Module._extensions[".js"] = loadMaybeCjs;
    Module._extensions[".cjs"] = loadCjs;

    function loadMaybeCjs(module, filename) {
        const content = op_require_read_file(filename);
        module._compile(content, filename, undefined);
    }

    function loadCjs(module, filename) {
        const content = op_require_read_file(filename);
        module._compile(content, filename, "commonjs");
    }

    function stripBOM(content) {
        if (StringPrototypeCharCodeAt(content, 0) === 0xfeff) {
            content = StringPrototypeSlice(content, 1);
        }
        return content;
    }

    // Native extension for .json
    Module._extensions[".json"] = function (module, filename) {
        const content = op_require_read_file(filename);

        try {
            module.exports = JSONParse(stripBOM(content));
        } catch (err) {
            err.message = filename + ": " + err.message;
            throw err;
        }
    };

    function createRequireFromPath(filename) {
        // Allow a directory to be passed as the filename
        const trailingSlash =
            StringPrototypeEndsWith(filename, "/") ||
            StringPrototypeEndsWith(filename, "\\");

        const proxyPath = trailingSlash
            ? internals.path.join(filename, "noop.js")
            : filename;

        const mod = new Module(proxyPath);
        mod.filename = proxyPath;
        mod.paths = Module._nodeModulePaths(mod.path);
        return makeRequireFunction(mod);
    }

    function makeRequireFunction(mod) {
        const require = function require(path) {
            return mod.require(path);
        };

        function resolve(request, options) {
            return Module._resolveFilename(request, mod, false, options);
        }

        require.resolve = resolve;

        function paths(request) {
            return Module._resolveLookupPaths(request, mod);
        }

        resolve.paths = paths;
        require.main = mainModule;
        // Enable support to add extra extension types.
        require.extensions = Module._extensions;
        require.cache = Module._cache;

        return require;
    }

    // Matches to:
    // - /foo/...
    // - \foo\...
    // - C:/foo/...
    // - C:\foo\...
    const RE_START_OF_ABS_PATH = /^([/\\]|[a-zA-Z]:[/\\])/;

    function isAbsolute(filenameOrUrl) {
        return RE_START_OF_ABS_PATH.test(filenameOrUrl);
    }

    function createRequire(filename) {
        if (typeof filename !== "string") {
            throw new Error(
                `The argument 'filename' must be an absolute path string. Received ${filename}`
            );
        }

        if (!isAbsolute(filename)) {
            throw new Error(
                `The argument 'filename' must be an absolute path string. Received ${filename}`
            );
        }

        return createRequireFromPath(filename);
    }

    function isBuiltin(moduleName) {
        if (typeof moduleName !== "string") {
            return false;
        }

        if (StringPrototypeStartsWith(moduleName, "node:")) {
            moduleName = StringPrototypeSlice(moduleName, 5);
        } else if (moduleName === "test") {
            // test is only a builtin if it has the "node:" scheme
            // see https://github.com/nodejs/node/blob/73025c4dec042e344eeea7912ed39f7b7c4a3991/test/parallel/test-module-isBuiltin.js#L14
            return false;
        }

        return (
            moduleName in nativeModuleExports &&
            !StringPrototypeStartsWith(moduleName, "internal/")
        );
    }

    Module.isBuiltin = isBuiltin;

    Module.createRequire = createRequire;

    Module._initPaths = function () {
        const paths = [];
        modulePaths = paths;
        Module.globalPaths = ArrayPrototypeSlice(modulePaths);
    };

    Module.Module = Module;

    nativeModuleExports.module = Module;

    function loadNativeModule(_id, request) {
        if (nativeModulePolyfill.has(request)) {
            return nativeModulePolyfill.get(request);
        }
        const modExports = nativeModuleExports[request];
        if (modExports) {
            const nodeMod = new Module(request);
            nodeMod.exports = modExports;
            nodeMod.loaded = true;
            nativeModulePolyfill.set(request, nodeMod);
            return nodeMod;
        }
        return undefined;
    }

    function nativeModuleCanBeRequiredByUsers(request) {
        return !!nativeModuleExports[request];
    }

    internals.Module = Module;
})(globalThis);
