/// <reference types="../manual/js/core.d.ts" />

((window) => {
    const __bindings = window.__bindings;
    delete window.__bindings;

    const { core, ops, primordials, internals } = __bootstrap;
    delete window.__bootstrap;

    const { ObjectAssign, ObjectDefineProperty } = primordials;

    const cc = __bindings.ax;
    cc.Director.prototype.setDisplayStats =
        cc.Director.prototype.setStatsDisplay;

    // tmp
    cc.director = cc.Director.getInstance();

    cc.Sprite3D = cc.MeshRenderer;
    const ccb = __bindings.axb;
    const ccui = __bindings.axui;
    const ccexp = __bindings.axexp;

    const cocosRequire = (path) => ops.op_cocos_require(path);

    ObjectAssign(window, {
        cc,
        ccb,
        ccui,
        ccexp,
        fgui: __bindings.fgui,
        sp: __bindings.sp,
        ccs: __bindings.ccs,
        jsb: {
            __core: core,
            fileUtils: cc.FileUtils.getInstance(),
        },
        require: cocosRequire,
    });

    ObjectDefineProperty(window, "window", {
        value: window,
        writable: false,
        configurable: false,
        enumerable: true,
    });

    // We dont know where user code put this file, so we need a way to just find other file relative to this
    // Code in other area shouldnt use this ops and can just use require() relative to them directly
    const setupRequire = internals.Module.createRequire(ops.op_eval_origin());
    const futils = cc.FileUtils.getInstance();

    setupRequire("./core/cc.js");
    setupRequire("./extends/NodeEx.js");
    setupRequire("./device.js");
    setupRequire("./display.js");
    setupRequire("./storage.js");
    // setupRequire("./cocos2d-x-v3-compat/index.js");

    const defaultResPath = sys.sessionStorage.getItem(
        "__defaultResourceRootPath__"
    )
    // || (jsb.fileUtils.getDefaultResourceRootPath() + 'cocos2dx-tests');
    if (defaultResPath) {
        futils.setDefaultResourceRootPath(defaultResPath);
    }

    const require = internals.Module.createRequire(
        futils.getDefaultResourceRootPath()
    );

    // Read project.json and run user code
    const projectJson = require("./project.json");
    if (projectJson.main) {
        require(projectJson.main);
    } else {
        ops.op_cocos_require("main.js");
    }
})(globalThis);
