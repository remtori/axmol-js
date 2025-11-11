/// From https://github.com/denoland/deno_core

"use strict";

((window) => {
    const {
        ArrayPrototypePush,
        Error,
        ErrorCaptureStackTrace,
        FunctionPrototypeBind,
        ObjectAssign,
        ObjectFreeze,
        ObjectKeys,
        ObjectHasOwn,
        SafeMap,
        SafeWeakMap,
        Set,
        StringPrototypeSlice,
        Symbol,
        TypedArrayPrototypeGetLength,
        TypedArrayPrototypeJoin,
        TypedArrayPrototypeSlice,
        TypedArrayPrototypeGetSymbolToStringTag,
        TypeError,
    } = window.__bootstrap.primordials;
    const { registerErrorClass } = window.__bootstrap.core;
    const { __setLeakTracingEnabled, __isLeakTracingEnabled } = window.__infra;
    const {
        op_decode,
        op_deserialize,
        // op_destructure_error,
        op_dispatch_exception,
        op_encode,
        op_encode_binary_string,
        op_eval_context,
        op_get_promise_details,
        op_get_proxy_details,
        op_print,
        op_serialize,
        // op_set_handled_promise_rejection_handler,
        // op_str_byte_length,
        op_timer_cancel,
        op_timer_queue,
        // op_leak_tracing_enable,
        // op_leak_tracing_submit,
        // op_leak_tracing_get_all,
        // op_leak_tracing_get,
        op_run_microtasks,
        op_get_extras_binding_object,
        op_call_console,
        op_memory_usage,

        op_is_any_array_buffer,
        op_is_arguments_object,
        op_is_array_buffer,
        op_is_array_buffer_view,
        op_is_async_function,
        op_is_big_int_object,
        op_is_boolean_object,
        op_is_boxed_primitive,
        op_is_data_view,
        op_is_date,
        op_is_generator_function,
        op_is_generator_object,
        op_is_map,
        op_is_map_iterator,
        op_is_module_namespace_object,
        op_is_native_error,
        op_is_number_object,
        op_is_promise,
        op_is_proxy,
        op_is_reg_exp,
        op_is_set,
        op_is_set_iterator,
        op_is_shared_array_buffer,
        op_is_string_object,
        op_is_symbol_object,
        op_is_typed_array,
        op_is_weak_map,
        op_is_weak_set,
    } = window.__bootstrap.ops;

    const {
        getContinuationPreservedEmbedderData,
        setContinuationPreservedEmbedderData,
    } = op_get_extras_binding_object();

    // core/infra collaborative code
    delete window.__infra;

    function submitTimerTrace(id) {
        const error = new Error();
        ErrorCaptureStackTrace(error, submitTimerTrace);
        // We submit interval and timer traces as type "Timer"
        // "Error\n".length == 6
        op_leak_tracing_submit(2, id, StringPrototypeSlice(error.stack, 6));
    }

    let unhandledPromiseRejectionHandler = () => false;
    let timerDepth = 0;
    let timersRunning = false;
    const cancelledTimers = new Set();

    const nextTickCallbacks = [];
    function setNextTickCallback(cb) {
        ArrayPrototypePush(nextTickCallbacks, cb);
    }

    function processNodeEvents(nodeEvents) {
        for (let i = 0; i < nodeEvents.length; i += 2) {
            const func = nodeEvents[i];
            const args = nodeEvents[i + 1];

            try {
                switch (args.length) {
                    case 0:
                        func();
                        break;
                    case 1:
                        func(args[0]);
                        break;
                    case 2:
                        func(args[0], args[1]);
                        break;
                    case 3:
                        func(args[0], args[1], args[2]);
                        break;
                    case 4:
                        func(args[0], args[1], args[2], args[3]);
                        break;
                    case 5:
                        func(args[0], args[1], args[2], args[3], args[4]);
                        break;
                    default:
                        func(...args);
                        break;
                }
            } catch (e) {
                reportExceptionCallback(e);
            }
        }
    }

    function eventLoopTick(nodeEvents, rejections, timers) {
        // Cocos cc.Node events
        processNodeEvents(nodeEvents);

        for (let i = 0; i < nextTickCallbacks.length; i++) {
            nextTickCallbacks[i]();
        }

        if (timers) {
            timersRunning = true;
            for (let i = 0; i < timers.length; i += 3) {
                timerDepth = timers[i];
                const id = timers[i + 1];
                if (cancelledTimers.has(id)) {
                    continue;
                }
                try {
                    const f = timers[i + 2];
                    f.call(window);
                } catch (e) {
                    reportExceptionCallback(e);
                }
                op_run_microtasks();
            }
            timersRunning = false;
            timerDepth = 0;
            cancelledTimers.clear();
        }

        // If we have any rejections for this tick, attempt to process them
        if (rejections) {
            for (let i = 0; i < rejections.length; i += 2) {
                const handled = unhandledPromiseRejectionHandler(
                    rejections[i],
                    rejections[i + 1]
                );
                if (!handled) {
                    const err = rejections[i + 1];
                    op_dispatch_exception(err, true);
                }
            }
        }
    }

    let reportExceptionCallback = (error) => {
        op_dispatch_exception(error, false);
    };

    // Used to report errors thrown from functions passed to `queueMicrotask()`.
    // The callback will be passed the thrown error. For example, you can use this
    // to dispatch an error event to the global scope.
    // In other words, set the implementation for
    // https://html.spec.whatwg.org/multipage/webappapis.html#report-the-exception
    function setReportExceptionCallback(cb) {
        if (cb === null || cb === undefined) {
            reportExceptionCallback = (error) => {
                op_dispatch_exception(error, false);
            };
        } else {
            if (typeof cb != "function") {
                throw new TypeError("expected a function");
            }
            reportExceptionCallback = cb;
        }
    }

    class BadResource extends Error {
        constructor(msg, options) {
            super(msg, options);
            this.name = "BadResource";
        }
    }
    const BadResourcePrototype = BadResource.prototype;

    class Interrupted extends Error {
        constructor(msg, options) {
            super(msg, options);
            this.name = "Interrupted";
        }
    }
    const InterruptedPrototype = Interrupted.prototype;

    class NotCapable extends Error {
        constructor(msg, options) {
            super(msg, options);
            this.name = "NotCapable";
        }
    }
    const NotCapablePrototype = NotCapable.prototype;

    registerErrorClass("BadResource", BadResource);
    registerErrorClass("Interrupted", Interrupted);
    registerErrorClass("NotCapable", NotCapable);

    // A helper function that will bind our own console implementation
    // with default implementation of Console from V8. This will cause
    // console messages to be piped to inspector console.
    //
    // We are using `core.callConsole` binding to preserve proper stack
    // frames in inspector console. This has to be done because V8 considers
    // the last JS stack frame as gospel for the inspector. In our case we
    // specifically want the latest user stack frame to be the one that matters
    // though.
    //
    // Inspired by:
    // https://github.com/nodejs/node/blob/1317252dfe8824fd9cfee125d2aaa94004db2f3b/lib/internal/util/inspector.js#L39-L61
    function wrapConsole(customConsole, consoleFromV8) {
        const keys = ObjectKeys(consoleFromV8);
        for (let i = 0; i < keys.length; ++i) {
            const key = keys[i];
            if (ObjectHasOwn(customConsole, key)) {
                customConsole[key] = FunctionPrototypeBind(
                    op_call_console,
                    customConsole,
                    consoleFromV8[key],
                    customConsole[key]
                );
            } else {
                // Add additional console APIs from the inspector
                customConsole[key] = consoleFromV8[key];
            }
        }
    }

    // Minimal console implementation, that uses `Deno.core.print` under the hood.
    // It's not fully fledged and is meant to make debugging slightly easier when working with
    // only `deno_core` crate.
    class CoreConsole {
        log = (...args) => {
            op_print(`${consoleStringify(...args)}\n`, false);
        };

        debug = (...args) => {
            op_print(`${consoleStringify(...args)}\n`, false);
        };

        warn = (...args) => {
            op_print(`${consoleStringify(...args)}\n`, false);
        };

        error = (...args) => {
            op_print(`${consoleStringify(...args)}\n`, false);
        };
    }

    const consoleStringify = (...args) =>
        args.map(consoleStringifyArg).join(" ");

    const consoleStringifyArg = (arg) => {
        if (
            typeof arg === "string" ||
            typeof arg === "boolean" ||
            typeof arg === "number" ||
            arg === null ||
            arg === undefined
        ) {
            return arg;
        }
        const tag = TypedArrayPrototypeGetSymbolToStringTag(arg);
        if (op_is_typed_array(arg)) {
            return `${tag}(${TypedArrayPrototypeGetLength(
                arg
            )}) [${TypedArrayPrototypeJoin(
                TypedArrayPrototypeSlice(arg, 0, 10),
                ", "
            )}]`;
        }
        if (tag !== undefined) {
            tag + " " + JSON.stringify(arg, undefined, 2);
        } else {
            return JSON.stringify(arg, undefined, 2);
        }
    };

    const v8Console = globalThis.console;
    const coreConsole = new CoreConsole();
    globalThis.console = coreConsole;
    wrapConsole(coreConsole, v8Console);

    function propWritable(value) {
        return {
            value,
            writable: true,
            enumerable: true,
            configurable: true,
        };
    }

    function propNonEnumerable(value) {
        return {
            value,
            writable: true,
            enumerable: false,
            configurable: true,
        };
    }

    function propReadOnly(value) {
        return {
            value,
            enumerable: true,
            writable: false,
            configurable: true,
        };
    }

    function propGetterOnly(getter) {
        return {
            get: getter,
            set() { },
            enumerable: true,
            configurable: true,
        };
    }

    function propWritableLazyLoaded(getter, loadFn) {
        let valueIsSet = false;
        let value;

        return {
            get() {
                const loadedValue = loadFn();
                if (valueIsSet) {
                    return value;
                } else {
                    return getter(loadedValue);
                }
            },
            set(v) {
                loadFn();
                valueIsSet = true;
                value = v;
            },
            enumerable: true,
            configurable: true,
        };
    }

    function propNonEnumerableLazyLoaded(getter, loadFn) {
        let valueIsSet = false;
        let value;

        return {
            get() {
                const loadedValue = loadFn();
                if (valueIsSet) {
                    return value;
                } else {
                    return getter(loadedValue);
                }
            },
            set(v) {
                loadFn();
                valueIsSet = true;
                value = v;
            },
            enumerable: false,
            configurable: true,
        };
    }

    const getAsyncContext = getContinuationPreservedEmbedderData;
    const setAsyncContext = setContinuationPreservedEmbedderData;

    function scopeAsyncContext(ctx) {
        const old = getAsyncContext();
        setAsyncContext(ctx);
        return {
            __proto__: null,
            [Symbol.dispose]() {
                setAsyncContext(old);
            },
        };
    }

    let asyncVariableCounter = 0;
    class AsyncVariable {
        #id = asyncVariableCounter++;
        #data = new SafeWeakMap();

        enter(value) {
            const previousContextMapping = getAsyncContext();
            const entry = { id: this.#id };
            const asyncContextMapping = {
                __proto__: null,
                ...previousContextMapping,
                [this.#id]: entry,
            };
            this.#data.set(entry, value);
            setAsyncContext(asyncContextMapping);
            return previousContextMapping;
        }

        get() {
            const current = getAsyncContext();
            const entry = current?.[this.#id];
            if (entry) {
                return this.#data.get(entry);
            }
            return undefined;
        }
    }

    ObjectAssign(globalThis.__bootstrap.core, {
        eventLoopTick,
        BadResource,
        BadResourcePrototype,
        Interrupted,
        InterruptedPrototype,
        NotCapable,
        NotCapablePrototype,
        setReportExceptionCallback,
        consoleStringify,
        print: (msg, isErr) => op_print(msg, isErr),
        setLeakTracingEnabled: (enabled) => {
            __setLeakTracingEnabled(enabled);
            op_leak_tracing_enable(enabled);
        },
        isLeakTracingEnabled: () => __isLeakTracingEnabled(),
        getAllLeakTraces: () => {
            const traces = op_leak_tracing_get_all();
            return new SafeMap(traces);
        },
        setNextTickCallback,
        evalContext: (source, specifier, hostDefinedOptions) => {
            const [result, error] = op_eval_context(
                source,
                specifier,
                hostDefinedOptions
            );
            if (error) {
                const {
                    0: thrown,
                    1: isNativeError,
                    2: isCompileError,
                } = error;
                return [
                    result,
                    {
                        thrown,
                        isNativeError,
                        isCompileError,
                    },
                ];
            }
            return [result, null];
        },
        encode: (text) => op_encode(text),
        encodeBinaryString: (buffer) => op_encode_binary_string(buffer),
        decode: (buffer) => op_decode(buffer),
        serialize: (value, options, errorCallback) => {
            return op_serialize(
                value,
                options?.hostObjects,
                options?.transferredArrayBuffers,
                options?.forStorage ?? false,
                errorCallback
            );
        },
        deserialize: (buffer, options) => {
            return op_deserialize(
                buffer,
                options?.hostObjects,
                options?.transferredArrayBuffers,
                options?.forStorage ?? false
            );
        },
        getPromiseDetails: (promise) => op_get_promise_details(promise),
        getProxyDetails: (proxy) => op_get_proxy_details(proxy),
        isAnyArrayBuffer: (value) => op_is_any_array_buffer(value),
        isArgumentsObject: (value) => op_is_arguments_object(value),
        isArrayBuffer: (value) => op_is_array_buffer(value),
        isArrayBufferView: (value) => op_is_array_buffer_view(value),
        isAsyncFunction: (value) => op_is_async_function(value),
        isBigIntObject: (value) => op_is_big_int_object(value),
        isBooleanObject: (value) => op_is_boolean_object(value),
        isBoxedPrimitive: (value) => op_is_boxed_primitive(value),
        isDataView: (value) => op_is_data_view(value),
        isDate: (value) => op_is_date(value),
        isGeneratorFunction: (value) => op_is_generator_function(value),
        isGeneratorObject: (value) => op_is_generator_object(value),
        isMap: (value) => op_is_map(value),
        isMapIterator: (value) => op_is_map_iterator(value),
        isModuleNamespaceObject: (value) =>
            op_is_module_namespace_object(value),
        isNativeError: (value) => op_is_native_error(value),
        isNumberObject: (value) => op_is_number_object(value),
        isPromise: (value) => op_is_promise(value),
        isProxy: (value) => op_is_proxy(value),
        isRegExp: (value) => op_is_reg_exp(value),
        isSet: (value) => op_is_set(value),
        isSetIterator: (value) => op_is_set_iterator(value),
        isSharedArrayBuffer: (value) => op_is_shared_array_buffer(value),
        isStringObject: (value) => op_is_string_object(value),
        isSymbolObject: (value) => op_is_symbol_object(value),
        isTypedArray: (value) => op_is_typed_array(value),
        isWeakMap: (value) => op_is_weak_map(value),
        isWeakSet: (value) => op_is_weak_set(value),
        memoryUsage: () => op_memory_usage(),
        destructureError: (error) => op_destructure_error(error),
        byteLength: (str) => op_str_byte_length(str),
        setHandledPromiseRejectionHandler: (handler) =>
            op_set_handled_promise_rejection_handler(handler),
        setUnhandledPromiseRejectionHandler: (handler) =>
            (unhandledPromiseRejectionHandler = handler),
        reportUnhandledException: (e) => op_dispatch_exception(e, false),
        reportUnhandledPromiseRejection: (e) => op_dispatch_exception(e, true),
        queueUserTimer: (depth, repeat, timeout, task) => {
            const id = op_timer_queue(depth, repeat, timeout, task);
            if (__isLeakTracingEnabled()) {
                submitTimerTrace(id);
            }
            return id;
        },
        cancelTimer: (id) => {
            if (timersRunning) {
                cancelledTimers.add(id);
            }
            op_timer_cancel(id);
        },
        getTimerDepth: () => timerDepth,
        wrapConsole,
        v8Console,
        propReadOnly,
        propWritable,
        propNonEnumerable,
        propGetterOnly,
        propWritableLazyLoaded,
        propNonEnumerableLazyLoaded,
        getAsyncContext,
        setAsyncContext,
        scopeAsyncContext,
        AsyncVariable,
    });

    const internals = {};
    ObjectAssign(globalThis.__bootstrap, { internals });
    ObjectFreeze(globalThis.__bootstrap.core);
})(globalThis);
