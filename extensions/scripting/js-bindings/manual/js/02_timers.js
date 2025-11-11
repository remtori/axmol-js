((window) => {
    // Copyright 2018-2025 the Deno authors. MIT license.

    const { core, primordials } = window.__bootstrap;
    const { ObjectDefineProperties, TypeError, ReflectApply, MathTrunc, NumberIsFinite } = primordials;
    const { getAsyncContext, setAsyncContext } = core;

    function toLong(value) {
        value = Number(value);
        if (!NumberIsFinite(value) || value === 0) {
            return 0;
        }

        return MathTrunc(value);
    }

    function checkThis(thisArg) {
        if (
            thisArg !== null &&
            thisArg !== undefined &&
            thisArg !== globalThis
        ) {
            throw new TypeError("Illegal invocation");
        }
    }

    /**
     * Call a callback function after a delay.
     */
    function setTimeout(callback, timeout = 0, ...args) {
        checkThis(this);

        const unboundCallback = callback;
        const asyncContext = getAsyncContext();
        callback = () => {
            const oldContext = getAsyncContext();
            try {
                setAsyncContext(asyncContext);
                ReflectApply(unboundCallback, globalThis, args);
            } finally {
                setAsyncContext(oldContext);
            }
        };
        timeout = toLong(timeout);
        return core.queueUserTimer(
            core.getTimerDepth() + 1,
            false,
            timeout,
            callback
        );
    }

    /**
     * Call a callback function after a delay.
     */
    function setInterval(callback, timeout = 0, ...args) {
        checkThis(this);
        const unboundCallback = callback;
        const asyncContext = getAsyncContext();
        callback = () => {
            const oldContext = getAsyncContext(asyncContext);
            try {
                setAsyncContext(asyncContext);
                ReflectApply(unboundCallback, globalThis, args);
            } finally {
                setAsyncContext(oldContext);
            }
        };
        timeout = toLong(timeout);
        return core.queueUserTimer(
            core.getTimerDepth() + 1,
            true,
            timeout,
            callback
        );
    }

    /**
     * Clear a timeout or interval.
     */
    function clearTimeout(id = 0) {
        checkThis(this);
        id = toLong(id);
        core.cancelTimer(id);
    }

    /**
     * Clear a timeout or interval.
     */
    function clearInterval(id = 0) {
        checkThis(this);
        id = toLong(id);
        core.cancelTimer(id);
    }

    ObjectDefineProperties(window, {
        setTimeout: core.propWritable(setTimeout),
        setInterval: core.propWritable(setInterval),
        clearTimeout: core.propWritable(clearTimeout),
        clearInterval: core.propWritable(clearInterval),
    });
})(globalThis);
