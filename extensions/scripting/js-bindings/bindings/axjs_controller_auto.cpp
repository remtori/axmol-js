#include "js-bindings/bindings/axjs_controller_auto.hpp"
#if (AX_TARGET_PLATFORM == AX_PLATFORM_ANDROID || AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
#    include "axmol/base/GameController.h"
#    include "js-bindings/manual/JSConversions.h"
static void js_register_ax_controller_Controller(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Controller> class_Controller(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_Controller.member_function("getDeviceName", &ax::Controller::getDeviceName)
        .member_function("getDeviceId", &ax::Controller::getDeviceId)
        .member_function("isConnected", &ax::Controller::isConnected)
        .member_function("receiveExternalKeyEvent", &ax::Controller::receiveExternalKeyEvent)
        .member_function("setTag", &ax::Controller::setTag)
        .member_function("getTag", &ax::Controller::getTag)
        .static_function("getControllerByTag", &ax::Controller::getControllerByTag)
        .static_function("getControllerByDeviceId", &ax::Controller::getControllerByDeviceId)
        .static_function("startDiscoveryController", &ax::Controller::startDiscoveryController)
        .static_function("stopDiscoveryController", &ax::Controller::stopDiscoveryController)
        .auto_wrap_objects(true);
    mod.class_("Controller", class_Controller);
}
static void js_register_ax_controller_EventController(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventController> class_EventController(isolate);
    class_EventController
        .ctor([](ax::EventController::ControllerEventType arg0, ax::Controller* arg1, bool arg2)
              { return new ax::EventController(arg0, arg1, arg2); },
              [](ax::EventController::ControllerEventType arg0, ax::Controller* arg1, int arg2)
              { return new ax::EventController(arg0, arg1, arg2); })
        .template inherit<ax::Event>()
        .member_function("getControllerEventType", &ax::EventController::getControllerEventType)
        .member_function("getController", &ax::EventController::getController)
        .member_function("getKeyCode", &ax::EventController::getKeyCode)
        .member_function("setKeyCode", &ax::EventController::setKeyCode)
        .member_function("setConnectStatus", &ax::EventController::setConnectStatus)
        .member_function("isConnected", &ax::EventController::isConnected)
        .auto_wrap_objects(true);
    mod.class_("EventController", class_EventController);
}
static void js_register_ax_controller_EventListenerController(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventListenerController> class_EventListenerController(isolate);
    class_EventListenerController.template inherit<ax::EventListener>()
        .static_function("create", &ax::EventListenerController::create)
        .auto_wrap_objects(true);
    mod.class_("EventListenerController", class_EventListenerController);
}
void js_register_all_ax_controller(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_controller_Controller(mod);
    js_register_ax_controller_EventController(mod);
    js_register_ax_controller_EventListenerController(mod);
}
#endif
