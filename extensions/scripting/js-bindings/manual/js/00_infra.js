/// From https://github.com/denoland/deno_core

"use strict";

((window) => {
    const {
        Error,
        ErrorCaptureStackTrace,
        ObjectAssign,
        RangeError,
        ReferenceError,
        SafeArrayIterator,
        SymbolFor,
        SyntaxError,
        TypeError,
        URIError,
    } = window.__bootstrap.primordials;

    let isLeakTracingEnabled = false;
    let submitLeakTrace;
    let eventLoopTick;

    function __setLeakTracingEnabled(enabled) {
        isLeakTracingEnabled = enabled;
    }

    function __isLeakTracingEnabled() {
        return isLeakTracingEnabled;
    }

    function __initializeCoreMethods(eventLoopTick_, submitLeakTrace_) {
        eventLoopTick = eventLoopTick_;
        submitLeakTrace = submitLeakTrace_;
    }

    const errorMap = {};
    // Builtin v8 / JS errors
    registerErrorClass("Error", Error);
    registerErrorClass("RangeError", RangeError);
    registerErrorClass("ReferenceError", ReferenceError);
    registerErrorClass("SyntaxError", SyntaxError);
    registerErrorClass("TypeError", TypeError);
    registerErrorClass("URIError", URIError);

    function buildCustomError(className, message, additionalProperties) {
        let error;
        try {
            error = errorMap[className]?.(message);
        } catch (e) {
            throw new Error(
                `Unable to build custom error for "${className}"\n	${e.message}`
            );
        }
        // Strip buildCustomError() calls from stack trace
        if (typeof error == "object") {
            ErrorCaptureStackTrace(error, buildCustomError);
            if (additionalProperties) {
                const keys = [];
                for (const property of new SafeArrayIterator(
                    additionalProperties
                )) {
                    const key = property[0];
                    if (!(key in error)) {
                        keys.push(key);
                        error[key] = property[1];
                    }
                }
                Object.defineProperty(
                    error,
                    SymbolFor("errorAdditionalPropertyKeys"),
                    {
                        value: keys,
                        writable: false,
                        enumerable: false,
                        configurable: false,
                    }
                );
            }
        }
        return error;
    }

    function registerErrorClass(className, errorClass) {
        registerErrorBuilder(className, (msg) => new errorClass(msg));
    }

    function registerErrorBuilder(className, errorBuilder) {
        if (typeof errorMap[className] !== "undefined") {
            throw new TypeError(
                `Error class for "${className}" already registered`
            );
        }
        errorMap[className] = errorBuilder;
    }

    const core = {
        registerErrorBuilder,
        buildCustomError,
        registerErrorClass,
    };

    const infra = {
        __setLeakTracingEnabled,
        __isLeakTracingEnabled,
        __initializeCoreMethods,
    };

    ObjectAssign(globalThis, { __infra: infra });
    ObjectAssign(globalThis.__bootstrap, { core });
})(globalThis);
