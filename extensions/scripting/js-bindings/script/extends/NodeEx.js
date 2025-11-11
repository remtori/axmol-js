const kDispatchNodeEvent = Symbol.for("axmol:dispatchNodeEvent");

function noop() {}

cc.Node.prototype[kDispatchNodeEvent] = function (nodeEvent) {
    switch (nodeEvent) {
        case 0:
            this.onEnter();
            break;
        case 1:
            this.onExit();
            break;
        case 2:
            this.onEnterTransitionDidFinish();
            break;
        case 3:
            this.onExitTransitionDidStart();
            break;
        case 4:
            this.onCleanup();
            break;
        default:
            break;
    }
}

cc.Node.prototype.onEnter = noop;
cc.Node.prototype.onExit = noop;
cc.Node.prototype.onEnterTransitionDidFinish = noop;
cc.Node.prototype.onExitTransitionDidStart = noop;
cc.Node.prototype.onCleanup = noop;
