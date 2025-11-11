#include "js-bindings/bindings/axjs_base_auto.hpp"
#include "axmol/axmol.h"
#include "axmol/2d/ProtectedNode.h"
#include "axmol/renderer/Renderer.h"
#include "axmol/renderer/PipelineDesc.h"
#include "axmol/rhi/RenderTarget.h"
#include "axmol/renderer/ProgramManager.h"
#include "js-bindings/manual/JSConversions.h"
static void js_register_ax_base_Object(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Object> class_Object(isolate);
    class_Object.member_function("retain", &ax::Object::retain)
        .member_function("release", &ax::Object::release)
        .member_function("getReferenceCount", &ax::Object::getReferenceCount)
        .auto_wrap_objects(true);
    mod.class_("Object", class_Object);
}
static void js_register_ax_base_Touch(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Touch> class_Touch(isolate);
    class_Touch.ctor([]() { return new ax::Touch(); })
        .template inherit<ax::Object>()
        .member_function("getLocation", &ax::Touch::getLocation)
        .member_function("getPreviousLocation", &ax::Touch::getPreviousLocation)
        .member_function("getStartLocation", &ax::Touch::getStartLocation)
        .member_function("getDelta", &ax::Touch::getDelta)
        .member_function("getLocationInView", &ax::Touch::getLocationInView)
        .member_function("getPreviousLocationInView", &ax::Touch::getPreviousLocationInView)
        .member_function("getStartLocationInView", &ax::Touch::getStartLocationInView)
        .member_function(
            "setTouchInfo",
            [](ax::Touch* self, int arg0, float arg1, float arg2, float arg3, float arg4)
            { self->setTouchInfo(arg0, arg1, arg2, arg3, arg4); },
            [](ax::Touch* self, int arg0, float arg1, float arg2) { self->setTouchInfo(arg0, arg1, arg2); })
        .member_function("getId", &ax::Touch::getID)
        .member_function("getCurrentForce", &ax::Touch::getCurrentForce)
        .member_function("getMaxForce", &ax::Touch::getMaxForce)
        .auto_wrap_objects(true);
    mod.class_("Touch", class_Touch);
}
static void js_register_ax_base_Event(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Event> class_Event(isolate);
    class_Event.ctor([](ax::Event::Type arg0) { return new ax::Event(arg0); })
        .template inherit<ax::Object>()
        .member_function("getType", &ax::Event::getType)
        .member_function("stopPropagation", &ax::Event::stopPropagation)
        .member_function("isStopped", &ax::Event::isStopped)
        .member_function("getCurrentTarget", &ax::Event::getCurrentTarget)
        .auto_wrap_objects(true);
    mod.class_("Event", class_Event);
}
static void js_register_ax_base_EventTouch(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventTouch> class_EventTouch(isolate);
    class_EventTouch.ctor([]() { return new ax::EventTouch(); })
        .template inherit<ax::Event>()
        .member_function("getEventCode", &ax::EventTouch::getEventCode)
        .member_function("setEventCode", &ax::EventTouch::setEventCode)
        .auto_wrap_objects(true);
    mod.class_("EventTouch", class_EventTouch);
}
static void js_register_ax_base_EventKeyboard(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventKeyboard> class_EventKeyboard(isolate);
    class_EventKeyboard
        .ctor([](ax::EventKeyboard::KeyCode arg0, bool arg1) { return new ax::EventKeyboard(arg0, arg1); },
              [](ax::EventKeyboard::KeyCode arg0, bool arg1, bool arg2) { return new ax::EventKeyboard(arg0, arg1, arg2); })
        .template inherit<ax::Event>()
        .member_function("isRepeat", &ax::EventKeyboard::isRepeat)
        .auto_wrap_objects(true);
    mod.class_("EventKeyboard", class_EventKeyboard);
}
static void js_register_ax_base_Action(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Action> class_Action(isolate);
    class_Action.template inherit<ax::Object>()
        .member_function("clone", &ax::Action::clone)
        .member_function("reverse", &ax::Action::reverse)
        .member_function("isDone", &ax::Action::isDone)
        .member_function("startWithTarget", &ax::Action::startWithTarget)
        .member_function("stop", &ax::Action::stop)
        .member_function("step", &ax::Action::step)
        .member_function("update", &ax::Action::update)
        .member_function("getTarget", &ax::Action::getTarget)
        .member_function("setTarget", &ax::Action::setTarget)
        .member_function("getOriginalTarget", &ax::Action::getOriginalTarget)
        .member_function("setOriginalTarget", &ax::Action::setOriginalTarget)
        .member_function("getTag", &ax::Action::getTag)
        .member_function("setTag", &ax::Action::setTag)
        .member_function("getFlags", &ax::Action::getFlags)
        .member_function("setFlags", &ax::Action::setFlags)
        .auto_wrap_objects(true);
    mod.class_("Action", class_Action);
}
static void js_register_ax_base_FiniteTimeAction(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FiniteTimeAction> class_FiniteTimeAction(isolate);
    class_FiniteTimeAction.template inherit<ax::Action>()
        .member_function("getDuration", &ax::FiniteTimeAction::getDuration)
        .member_function("setDuration", &ax::FiniteTimeAction::setDuration)
        .auto_wrap_objects(true);
    mod.class_("FiniteTimeAction", class_FiniteTimeAction);
}
static void js_register_ax_base_Speed(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Speed> class_Speed(isolate);
    class_Speed.ctor([]() { return new ax::Speed(); })
        .template inherit<ax::Action>()
        .member_function("getSpeed", &ax::Speed::getSpeed)
        .member_function("setSpeed", &ax::Speed::setSpeed)
        .member_function("setInnerAction", &ax::Speed::setInnerAction)
        .member_function("getInnerAction", &ax::Speed::getInnerAction)
        .member_function("initWithAction", &ax::Speed::initWithAction)
        .static_function("create", &ax::Speed::create)
        .auto_wrap_objects(true);
    mod.class_("Speed", class_Speed);
}
static void js_register_ax_base_Follow(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Follow> class_Follow(isolate);
    class_Follow.ctor([]() { return new ax::Follow(); })
        .template inherit<ax::Action>()
        .member_function("isBoundarySet", &ax::Follow::isBoundarySet)
        .member_function("setBoundarySet", &ax::Follow::setBoundarySet)
        .member_function(
            "initWithTarget",
            [](ax::Follow* self, ax::Node* arg0) { return self->initWithTarget(arg0); },
            [](ax::Follow* self, ax::Node* arg0, ax::Rect arg1) { return self->initWithTarget(arg0, arg1); })
        .member_function(
            "initWithTargetAndOffset",
            [](ax::Follow* self, ax::Node* arg0, float arg1, float arg2) { return self->initWithTargetAndOffset(arg0, arg1, arg2); },
            [](ax::Follow* self, ax::Node* arg0, float arg1, float arg2, ax::Rect arg3)
            { return self->initWithTargetAndOffset(arg0, arg1, arg2, arg3); })
        .static_function(
            "create",
            [](ax::Node* arg0) { return ax::Follow::create(arg0); },
            [](ax::Node* arg0, ax::Rect arg1) { return ax::Follow::create(arg0, arg1); })
        .static_function(
            "createWithOffset",
            [](ax::Node* arg0, float arg1, float arg2) { return ax::Follow::createWithOffset(arg0, arg1, arg2); },
            [](ax::Node* arg0, float arg1, float arg2, ax::Rect arg3) { return ax::Follow::createWithOffset(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("Follow", class_Follow);
}
static void js_register_ax_base_ShaderCache(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::rhi::ShaderCache> class_ShaderCache(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_ShaderCache.member_function("purge", &ax::rhi::ShaderCache::purge)
        .member_function("acquireVertexShaderModule", &ax::rhi::ShaderCache::acquireVertexShaderModule)
        .member_function("acquireFragmentShaderModule", &ax::rhi::ShaderCache::acquireFragmentShaderModule)
        .member_function("removeUnusedShader", &ax::rhi::ShaderCache::removeUnusedShader)
        .static_function("getInstance", &ax::rhi::ShaderCache::getInstance)
        .static_function("destroyInstance", &ax::rhi::ShaderCache::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("ShaderCache", class_ShaderCache);
}
static void js_register_ax_base_Texture2D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Texture2D> class_Texture2D(isolate);
    class_Texture2D.ctor([]() { return new ax::Texture2D(); })
        .template inherit<ax::Object>()
        .member_function(
            "initWithImage",
            [](ax::Texture2D* self, ax::Image* arg0) { return self->initWithImage(arg0); },
            [](ax::Texture2D* self, ax::Image* arg0, ax::rhi::PixelFormat arg1) { return self->initWithImage(arg0, arg1); },
            [](ax::Texture2D* self, ax::Image* arg0, ax::rhi::PixelFormat arg1, bool arg2)
            { return self->initWithImage(arg0, arg1, arg2); })
        .member_function(
            "initWithString",
            [](ax::Texture2D* self, std::string_view arg0, ax::FontDefinition arg1) { return self->initWithString(arg0, arg1); },
            [](ax::Texture2D* self, std::string_view arg0, std::string_view arg1, float arg2)
            { return self->initWithString(arg0, arg1, arg2); },
            [](ax::Texture2D* self, std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3)
            { return self->initWithString(arg0, arg1, arg2, arg3); },
            [](ax::Texture2D* self, std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3, ax::TextHAlignment arg4)
            { return self->initWithString(arg0, arg1, arg2, arg3, arg4); },
            [](ax::Texture2D* self,
               std::string_view arg0,
               std::string_view arg1,
               float arg2,
               ax::Vec2 arg3,
               ax::TextHAlignment arg4,
               ax::TextVAlignment arg5) { return self->initWithString(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::Texture2D* self,
               std::string_view arg0,
               std::string_view arg1,
               float arg2,
               ax::Vec2 arg3,
               ax::TextHAlignment arg4,
               ax::TextVAlignment arg5,
               bool arg6) { return self->initWithString(arg0, arg1, arg2, arg3, arg4, arg5, arg6); },
            [](ax::Texture2D* self,
               std::string_view arg0,
               std::string_view arg1,
               float arg2,
               ax::Vec2 arg3,
               ax::TextHAlignment arg4,
               ax::TextVAlignment arg5,
               bool arg6,
               int arg7) { return self->initWithString(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); })
        .member_function(
            "updateSubData",
            [](ax::Texture2D* self, const void* arg0, int arg1, int arg2, int arg3, int arg4)
            { return self->updateSubData(arg0, arg1, arg2, arg3, arg4); },
            [](ax::Texture2D* self, const void* arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
            { return self->updateSubData(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::Texture2D* self, const void* arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
            { return self->updateSubData(arg0, arg1, arg2, arg3, arg4, arg5, arg6); })
        .member_function("invalidate", &ax::Texture2D::invalidate)
        .member_function("drawAtPoint", &ax::Texture2D::drawAtPoint)
        .member_function("drawInRect", &ax::Texture2D::drawInRect)
        .member_function("isRenderTarget", &ax::Texture2D::isRenderTarget)
        .member_function("setAntiAliasTexParameters", &ax::Texture2D::setAntiAliasTexParameters)
        .member_function("setAliasTexParameters", &ax::Texture2D::setAliasTexParameters)
        .member_function("getStringForFormat", &ax::Texture2D::getStringForFormat)
        .member_function(
            "getBitsPerPixelForFormat",
            [](ax::Texture2D* self, ax::rhi::PixelFormat arg0) { return self->getBitsPerPixelForFormat(arg0); },
            [](ax::Texture2D* self) { return self->getBitsPerPixelForFormat(); })
        .member_function("getContentSizeInPixels", &ax::Texture2D::getContentSizeInPixels)
        .member_function("hasPremultipliedAlpha", &ax::Texture2D::hasPremultipliedAlpha)
        .member_function("setPremultipliedAlpha", &ax::Texture2D::setPremultipliedAlpha)
        .member_function("hasMipmaps", &ax::Texture2D::hasMipmaps)
        .member_function("getPixelFormat", &ax::Texture2D::getPixelFormat)
        .member_function("getSamplerFlags", &ax::Texture2D::getSamplerFlags)
        .member_function("getPixelsWide", &ax::Texture2D::getPixelsWide)
        .member_function("getPixelsHigh", &ax::Texture2D::getPixelsHigh)
        .member_function("getRHITexture", &ax::Texture2D::getRHITexture)
        .member_function("getMaxS", &ax::Texture2D::getMaxS)
        .member_function("setMaxS", &ax::Texture2D::setMaxS)
        .member_function("getMaxT", &ax::Texture2D::getMaxT)
        .member_function("setMaxT", &ax::Texture2D::setMaxT)
        .member_function("getContentSize", &ax::Texture2D::getContentSize)
        .member_function("getPath", &ax::Texture2D::getPath)
        .auto_wrap_objects(true);
    mod.class_("Texture2D", class_Texture2D);
}
static void js_register_ax_base_Component(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Component> class_Component(isolate);
    class_Component.template inherit<ax::Object>()
        .member_function("init", &ax::Component::init)
        .member_function("isEnabled", &ax::Component::isEnabled)
        .member_function("setEnabled", &ax::Component::setEnabled)
        .member_function("getName", &ax::Component::getName)
        .member_function("setName", &ax::Component::setName)
        .member_function("getOwner", &ax::Component::getOwner)
        .member_function("setOwner", &ax::Component::setOwner)
        .member_function("update", &ax::Component::update)
        .member_function("onAdd", &ax::Component::onAdd)
        .member_function("onRemove", &ax::Component::onRemove)
        .static_function("create", &ax::Component::create)
        .auto_wrap_objects(true);
    mod.class_("Component", class_Component);
}
static void js_register_ax_base_Node(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Node> class_Node(isolate);
    class_Node.ctor([]() { return new ax::Node(); })
        .template inherit<ax::Object>()
        .member_function("getDescription", &ax::Node::getDescription)
        .member_function("setLocalZOrder", &ax::Node::setLocalZOrder)
        .member_function("updateOrderOfArrival", &ax::Node::updateOrderOfArrival)
        .member_function("getLocalZOrder", &ax::Node::getLocalZOrder)
        .member_function("setGlobalZOrder", &ax::Node::setGlobalZOrder)
        .member_function("getGlobalZOrder", &ax::Node::getGlobalZOrder)
        .member_function("setScaleX", &ax::Node::setScaleX)
        .member_function("getScaleX", &ax::Node::getScaleX)
        .member_function("setScaleY", &ax::Node::setScaleY)
        .member_function("getScaleY", &ax::Node::getScaleY)
        .member_function("setScaleZ", &ax::Node::setScaleZ)
        .member_function("getScaleZ", &ax::Node::getScaleZ)
        .member_function(
            "setScale",
            [](ax::Node* self, float arg0, float arg1) { self->setScale(arg0, arg1); },
            [](ax::Node* self, float arg0) { self->setScale(arg0); })
        .member_function("getScale", &ax::Node::getScale)
        .member_function(
            "setPosition",
            [](ax::Node* self, float arg0, float arg1) { self->setPosition(arg0, arg1); },
            [](ax::Node* self, ax::Vec2 arg0) { self->setPosition(arg0); })
        .member_function("setPositionNormalized", &ax::Node::setPositionNormalized)
        .member_function("setNormalizedPosition", &ax::Node::setNormalizedPosition)
        .member_function(
            "getPosition",
            [](ax::Node* self, float* arg0, float* arg1) { self->getPosition(arg0, arg1); },
            [](ax::Node* self) { return self->getPosition(); })
        .member_function("getPositionNormalized", &ax::Node::getPositionNormalized)
        .member_function("getNormalizedPosition", &ax::Node::getNormalizedPosition)
        .member_function("setPositionX", &ax::Node::setPositionX)
        .member_function("getPositionX", &ax::Node::getPositionX)
        .member_function("setPositionY", &ax::Node::setPositionY)
        .member_function("getPositionY", &ax::Node::getPositionY)
        .member_function("setPosition3D", &ax::Node::setPosition3D)
        .member_function("getPosition3D", &ax::Node::getPosition3D)
        .member_function("setPositionZ", &ax::Node::setPositionZ)
        .member_function("getPositionZ", &ax::Node::getPositionZ)
        .member_function("setSkewX", &ax::Node::setSkewX)
        .member_function("getSkewX", &ax::Node::getSkewX)
        .member_function("setSkewY", &ax::Node::setSkewY)
        .member_function("getSkewY", &ax::Node::getSkewY)
        .member_function("setAnchorPoint", &ax::Node::setAnchorPoint)
        .member_function("getAnchorPoint", &ax::Node::getAnchorPoint)
        .member_function("getAnchorPointInPoints", &ax::Node::getAnchorPointInPoints)
        .member_function("setContentSize", &ax::Node::setContentSize)
        .member_function("getContentSize", &ax::Node::getContentSize)
        .member_function("hitTest", &ax::Node::hitTest)
        .member_function("setVisible", &ax::Node::setVisible)
        .member_function("isVisible", &ax::Node::isVisible)
        .member_function("setRotation", &ax::Node::setRotation)
        .member_function("getRotation", &ax::Node::getRotation)
        .member_function("setRotation3D", &ax::Node::setRotation3D)
        .member_function("getRotation3D", &ax::Node::getRotation3D)
        .member_function("setRotationSkewX", &ax::Node::setRotationSkewX)
        .member_function("getRotationSkewX", &ax::Node::getRotationSkewX)
        .member_function("setRotationSkewY", &ax::Node::setRotationSkewY)
        .member_function("getRotationSkewY", &ax::Node::getRotationSkewY)
        .member_function("setIgnoreAnchorPointForPosition", &ax::Node::setIgnoreAnchorPointForPosition)
        .member_function("isIgnoreAnchorPointForPosition", &ax::Node::isIgnoreAnchorPointForPosition)
        .member_function(
            "addChild",
            [](ax::Node* self, ax::Node* arg0, int arg1) { self->addChild(arg0, arg1); },
            [](ax::Node* self, ax::Node* arg0) { self->addChild(arg0); },
            [](ax::Node* self, ax::Node* arg0, int arg1, int arg2) { self->addChild(arg0, arg1, arg2); },
            [](ax::Node* self, ax::Node* arg0, int arg1, std::string_view arg2) { self->addChild(arg0, arg1, arg2); })
        .member_function(
            "getChildren", [](ax::Node* self) { return self->getChildren(); }, [](ax::Node* self) { return self->getChildren(); })
        .member_function("getChildrenCount", &ax::Node::getChildrenCount)
        .member_function("setParent", &ax::Node::setParent)
        .member_function(
            "getParent", [](ax::Node* self) { return self->getParent(); }, [](ax::Node* self) { return self->getParent(); })
        .member_function(
            "removeFromParent",
            [](ax::Node* self, bool arg0) { self->removeFromParentAndCleanup(arg0); },
            [](ax::Node* self) { self->removeFromParent(); })
        .member_function(
            "removeChild",
            [](ax::Node* self, ax::Node* arg0) { self->removeChild(arg0); },
            [](ax::Node* self, ax::Node* arg0, bool arg1) { self->removeChild(arg0, arg1); })
        .member_function(
            "removeChildByTag",
            [](ax::Node* self, int arg0) { self->removeChildByTag(arg0); },
            [](ax::Node* self, int arg0, bool arg1) { self->removeChildByTag(arg0, arg1); })
        .member_function(
            "removeChildByName",
            [](ax::Node* self, std::string_view arg0) { self->removeChildByName(arg0); },
            [](ax::Node* self, std::string_view arg0, bool arg1) { self->removeChildByName(arg0, arg1); })
        .member_function(
            "removeAllChildren",
            [](ax::Node* self, bool arg0) { self->removeAllChildrenWithCleanup(arg0); },
            [](ax::Node* self) { self->removeAllChildren(); })
        .member_function("reorderChild", &ax::Node::reorderChild)
        .member_function("sortAllChildren", &ax::Node::sortAllChildren)
        .member_function("getTag", &ax::Node::getTag)
        .member_function("setTag", &ax::Node::setTag)
        .member_function("getName", &ax::Node::getName)
        .member_function("setName", &ax::Node::setName)
        .member_function("setUserObject", &ax::Node::setUserObject)
        .member_function("isRunning", &ax::Node::isRunning)
        .member_function("cleanup", &ax::Node::cleanup)
        .member_function(
            "draw",
            [](ax::Node* self) { self->draw(); },
            [](ax::Node* self, ax::Renderer* arg0, ax::Mat4 arg1, unsigned int arg2) { self->draw(arg0, arg1, arg2); })
        .member_function(
            "visit",
            [](ax::Node* self) { self->visit(); },
            [](ax::Node* self, ax::Renderer* arg0, ax::Mat4 arg1, unsigned int arg2) { self->visit(arg0, arg1, arg2); })
        .member_function("getScene", &ax::Node::getScene)
        .member_function("getBoundingBox", &ax::Node::getBoundingBox)
        .member_function("setEventDispatcher", &ax::Node::setEventDispatcher)
        .member_function("getEventDispatcher", &ax::Node::getEventDispatcher)
        .member_function("setActionManager", &ax::Node::setActionManager)
        .member_function(
            "getActionManager",
            [](ax::Node* self) { return self->getActionManager(); },
            [](ax::Node* self) { return self->getActionManager(); })
        .member_function("runAction", &ax::Node::runAction)
        .member_function("stopAllActions", &ax::Node::stopAllActions)
        .member_function("stopAction", &ax::Node::stopAction)
        .member_function("stopActionByTag", &ax::Node::stopActionByTag)
        .member_function("stopAllActionsByTag", &ax::Node::stopAllActionsByTag)
        .member_function("stopActionsByFlags", &ax::Node::stopActionsByFlags)
        .member_function("getActionByTag", &ax::Node::getActionByTag)
        .member_function("getNumberOfRunningActions", &ax::Node::getNumberOfRunningActions)
        .member_function("getNumberOfRunningActionsByTag", &ax::Node::getNumberOfRunningActionsByTag)
        .member_function("setScheduler", &ax::Node::setScheduler)
        .member_function(
            "getScheduler", [](ax::Node* self) { return self->getScheduler(); }, [](ax::Node* self) { return self->getScheduler(); })
        .member_function("resume", &ax::Node::resume)
        .member_function("pause", &ax::Node::pause)
        .member_function("update", &ax::Node::update)
        .member_function("updateTransform", &ax::Node::updateTransform)
        .member_function(
            "getNodeToParentTransform",
            [](ax::Node* self, ax::Node* arg0) { return self->getNodeToParentTransform(arg0); },
            [](ax::Node* self) { return self->getNodeToParentTransform(); })
        .member_function(
            "getNodeToParentAffineTransform",
            [](ax::Node* self, ax::Node* arg0) { return self->getNodeToParentAffineTransform(arg0); },
            [](ax::Node* self) { return self->getNodeToParentAffineTransform(); })
        .member_function("setNodeToParentTransform", &ax::Node::setNodeToParentTransform)
        .member_function("getParentToNodeTransform", &ax::Node::getParentToNodeTransform)
        .member_function("getParentToNodeAffineTransform", &ax::Node::getParentToNodeAffineTransform)
        .member_function("getNodeToWorldTransform", &ax::Node::getNodeToWorldTransform)
        .member_function("getNodeToWorldAffineTransform", &ax::Node::getNodeToWorldAffineTransform)
        .member_function("getWorldToNodeTransform", &ax::Node::getWorldToNodeTransform)
        .member_function("getWorldToNodeAffineTransform", &ax::Node::getWorldToNodeAffineTransform)
        .member_function("convertToNodeSpace", &ax::Node::convertToNodeSpace)
        .member_function("convertToWorldSpace", &ax::Node::convertToWorldSpace)
        .member_function("convertToNodeSpaceAR", &ax::Node::convertToNodeSpaceAR)
        .member_function("convertToWorldSpaceAR", &ax::Node::convertToWorldSpaceAR)
        .member_function("convertTouchToNodeSpace", &ax::Node::convertTouchToNodeSpace)
        .member_function("convertTouchToNodeSpaceAR", &ax::Node::convertTouchToNodeSpaceAR)
        .member_function("getWorldPosition", &ax::Node::getWorldPosition)
        .member_function("setWorldPosition", &ax::Node::setWorldPosition)
        .member_function("getComponent", &ax::Node::getComponent)
        .member_function("addComponent", &ax::Node::addComponent)
        .member_function(
            "removeComponent",
            [](ax::Node* self, ax::Component* arg0) { return self->removeComponent(arg0); },
            [](ax::Node* self, std::string_view arg0) { return self->removeComponent(arg0); })
        .member_function("removeAllComponents", &ax::Node::removeAllComponents)
        .member_function("getOpacity", &ax::Node::getOpacity)
        .member_function("getDisplayedOpacity", &ax::Node::getDisplayedOpacity)
        .member_function("setOpacity", &ax::Node::setOpacity)
        .member_function("updateDisplayedOpacity", &ax::Node::updateDisplayedOpacity)
        .member_function("isCascadeOpacityEnabled", &ax::Node::isCascadeOpacityEnabled)
        .member_function("setCascadeOpacityEnabled", &ax::Node::setCascadeOpacityEnabled)
        .member_function("getColor", &ax::Node::getColor)
        .member_function("getDisplayedColor", &ax::Node::getDisplayedColor)
        .member_function("setColor", &ax::Node::setColor)
        .member_function("updateDisplayedColor", &ax::Node::updateDisplayedColor)
        .member_function("isCascadeColorEnabled", &ax::Node::isCascadeColorEnabled)
        .member_function("setCascadeColorEnabled", &ax::Node::setCascadeColorEnabled)
        .member_function("setOpacityModifyRGB", &ax::Node::setOpacityModifyRGB)
        .member_function("isOpacityModifyRGB", &ax::Node::isOpacityModifyRGB)
        .member_function("getCameraMask", &ax::Node::getCameraMask)
        .member_function(
            "setCameraMask",
            [](ax::Node* self, unsigned short arg0) { self->setCameraMask(arg0); },
            [](ax::Node* self, unsigned short arg0, bool arg1) { self->setCameraMask(arg0, arg1); })
        .member_function("applyMaskOnEnter", &ax::Node::applyMaskOnEnter)
        .member_function(
            "setProgramState",
            [](ax::Node* self, ax::rhi::ProgramState* arg0) { return self->setProgramState(arg0); },
            [](ax::Node* self, ax::rhi::ProgramState* arg0, bool arg1) { return self->setProgramState(arg0, arg1); },
            [](ax::Node* self, unsigned int arg0) { self->setProgramState(arg0); })
        .member_function("setProgramStateWithRegistry", &ax::Node::setProgramStateWithRegistry)
        .member_function("setProgramStateByProgramId", &ax::Node::setProgramStateByProgramId)
        .member_function("getProgramState", &ax::Node::getProgramState)
        .member_function("updateProgramStateTexture", &ax::Node::updateProgramStateTexture)
        .member_function("resetChild", &ax::Node::resetChild)
        .member_function("init", &ax::Node::init)
        .member_function("initLayer", &ax::Node::initLayer)
        .member_function("setPhysicsBody", &ax::Node::setPhysicsBody)
        .member_function("getPhysicsBody", &ax::Node::getPhysicsBody)
        .static_function("create", &ax::Node::create)
        .static_function("getAttachedNodeCount", &ax::Node::getAttachedNodeCount)
        .auto_wrap_objects(true);
    mod.class_("Node", class_Node);
}
static void js_register_ax_base_Image(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Image> class_Image(isolate);
    class_Image.ctor([]() { return new ax::Image(); })
        .template inherit<ax::Object>()
        .member_function("initWithImageFile", &ax::Image::initWithImageFile)
        .member_function("flipRawData", &ax::Image::flipRawData)
        .member_function("getFileType", &ax::Image::getFileType)
        .member_function("getPixelFormat", &ax::Image::getPixelFormat)
        .member_function("getWidth", &ax::Image::getWidth)
        .member_function("getHeight", &ax::Image::getHeight)
        .member_function("getNumberOfMipmaps", &ax::Image::getNumberOfMipmaps)
        .member_function("hasPremultipliedAlpha", &ax::Image::hasPremultipliedAlpha)
        .member_function("getFilePath", &ax::Image::getFilePath)
        .member_function("getBitPerPixel", &ax::Image::getBitPerPixel)
        .member_function("hasAlpha", &ax::Image::hasAlpha)
        .member_function("isCompressed", &ax::Image::isCompressed)
        .member_function(
            "saveToFile",
            [](ax::Image* self, std::string_view arg0) { return self->saveToFile(arg0); },
            [](ax::Image* self, std::string_view arg0, bool arg1) { return self->saveToFile(arg0, arg1); })
        .member_function("premultiplyAlpha", &ax::Image::premultiplyAlpha)
        .member_function("reversePremultipliedAlpha", &ax::Image::reversePremultipliedAlpha)
        .static_function("setPNGPremultipliedAlphaEnabled", &ax::Image::setPNGPremultipliedAlphaEnabled)
        .static_function("setCompressedImagesHavePMA", &ax::Image::setCompressedImagesHavePMA)
        .static_function("isCompressedImageHavePMA", &ax::Image::isCompressedImageHavePMA)
        .auto_wrap_objects(true);
    mod.class_("Image", class_Image);
}
static void js_register_ax_base_PolygonInfo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PolygonInfo> class_PolygonInfo(isolate);
    class_PolygonInfo.ctor([]() { return new ax::PolygonInfo(); })
        .member_function("setQuad", &ax::PolygonInfo::setQuad)
        .member_function("setQuads", &ax::PolygonInfo::setQuads)
        .member_function("setTriangles", &ax::PolygonInfo::setTriangles)
        .member_function("getVertCount", &ax::PolygonInfo::getVertCount)
        .member_function("getTrianglesCount", &ax::PolygonInfo::getTrianglesCount)
        .member_function("getArea", &ax::PolygonInfo::getArea)
        .member_function("getRect", &ax::PolygonInfo::getRect)
        .member_function("setRect", &ax::PolygonInfo::setRect)
        .member_function("getFilename", &ax::PolygonInfo::getFilename)
        .member_function("setFilename", &ax::PolygonInfo::setFilename)
        .auto_wrap_objects(true);
    mod.class_("PolygonInfo", class_PolygonInfo);
}
static void js_register_ax_base_AutoPolygon(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::AutoPolygon> class_AutoPolygon(isolate);
    class_AutoPolygon.ctor([](std::string_view arg0) { return new ax::AutoPolygon(arg0); }).auto_wrap_objects(true);
    mod.class_("AutoPolygon", class_AutoPolygon);
}
static void js_register_ax_base_SpriteFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SpriteFrame> class_SpriteFrame(isolate);
    class_SpriteFrame.ctor([]() { return new ax::SpriteFrame(); })
        .template inherit<ax::Object>()
        .member_function("getRectInPixels", &ax::SpriteFrame::getRectInPixels)
        .member_function("setRectInPixels", &ax::SpriteFrame::setRectInPixels)
        .member_function("isRotated", &ax::SpriteFrame::isRotated)
        .member_function("setRotated", &ax::SpriteFrame::setRotated)
        .member_function("getRect", &ax::SpriteFrame::getRect)
        .member_function("setRect", &ax::SpriteFrame::setRect)
        .member_function("getCenterRect", &ax::SpriteFrame::getCenterRect)
        .member_function("setCenterRectInPixels", &ax::SpriteFrame::setCenterRectInPixels)
        .member_function("hasCenterRect", &ax::SpriteFrame::hasCenterRect)
        .member_function("getOffsetInPixels", &ax::SpriteFrame::getOffsetInPixels)
        .member_function("setOffsetInPixels", &ax::SpriteFrame::setOffsetInPixels)
        .member_function("getOriginalSizeInPixels", &ax::SpriteFrame::getOriginalSizeInPixels)
        .member_function("setOriginalSizeInPixels", &ax::SpriteFrame::setOriginalSizeInPixels)
        .member_function("getOriginalSize", &ax::SpriteFrame::getOriginalSize)
        .member_function("setOriginalSize", &ax::SpriteFrame::setOriginalSize)
        .member_function("getTexture", &ax::SpriteFrame::getTexture)
        .member_function("setTexture", &ax::SpriteFrame::setTexture)
        .member_function("getOffset", &ax::SpriteFrame::getOffset)
        .member_function("setOffset", &ax::SpriteFrame::setOffset)
        .member_function("getAnchorPoint", &ax::SpriteFrame::getAnchorPoint)
        .member_function("setAnchorPoint", &ax::SpriteFrame::setAnchorPoint)
        .member_function("hasAnchorPoint", &ax::SpriteFrame::hasAnchorPoint)
        .member_function("clone", &ax::SpriteFrame::clone)
        .member_function(
            "initWithTexture",
            [](ax::SpriteFrame* self, ax::Texture2D* arg0, ax::Rect arg1, bool arg2, ax::Vec2 arg3, ax::Vec2 arg4)
            { return self->initWithTexture(arg0, arg1, arg2, arg3, arg4); },
            [](ax::SpriteFrame* self, ax::Texture2D* arg0, ax::Rect arg1) { return self->initWithTexture(arg0, arg1); })
        .member_function(
            "initWithTextureFilename",
            [](ax::SpriteFrame* self, std::string_view arg0, ax::Rect arg1, bool arg2, ax::Vec2 arg3, ax::Vec2 arg4)
            { return self->initWithTextureFilename(arg0, arg1, arg2, arg3, arg4); },
            [](ax::SpriteFrame* self, std::string_view arg0, ax::Rect arg1) { return self->initWithTextureFilename(arg0, arg1); })
        .member_function("getName", &ax::SpriteFrame::getName)
        .static_function(
            "create",
            [](std::string_view arg0, ax::Rect arg1, bool arg2, ax::Vec2 arg3, ax::Vec2 arg4)
            { return ax::SpriteFrame::create(arg0, arg1, arg2, arg3, arg4); },
            [](std::string_view arg0, ax::Rect arg1) { return ax::SpriteFrame::create(arg0, arg1); })
        .static_function(
            "createWithTexture",
            [](ax::Texture2D* arg0, ax::Rect arg1, bool arg2, ax::Vec2 arg3, ax::Vec2 arg4)
            { return ax::SpriteFrame::createWithTexture(arg0, arg1, arg2, arg3, arg4); },
            [](ax::Texture2D* arg0, ax::Rect arg1) { return ax::SpriteFrame::createWithTexture(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("SpriteFrame", class_SpriteFrame);
}
static void js_register_ax_base_AnimationFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::AnimationFrame> class_AnimationFrame(isolate);
    class_AnimationFrame.ctor([]() { return new ax::AnimationFrame(); })
        .template inherit<ax::Object>()
        .member_function("getSpriteFrame", &ax::AnimationFrame::getSpriteFrame)
        .member_function("setSpriteFrame", &ax::AnimationFrame::setSpriteFrame)
        .member_function("getDelayUnits", &ax::AnimationFrame::getDelayUnits)
        .member_function("setDelayUnits", &ax::AnimationFrame::setDelayUnits)
        .member_function(
            "getUserInfo",
            [](ax::AnimationFrame* self) { return self->getUserInfo(); },
            [](ax::AnimationFrame* self) { return self->getUserInfo(); })
        .member_function("setUserInfo", &ax::AnimationFrame::setUserInfo)
        .member_function("clone", &ax::AnimationFrame::clone)
        .member_function("initWithSpriteFrame", &ax::AnimationFrame::initWithSpriteFrame)
        .static_function("create", &ax::AnimationFrame::create)
        .auto_wrap_objects(true);
    mod.class_("AnimationFrame", class_AnimationFrame);
}
static void js_register_ax_base_Animation(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Animation> class_Animation(isolate);
    class_Animation.ctor([]() { return new ax::Animation(); })
        .template inherit<ax::Object>()
        .member_function("addSpriteFrame", &ax::Animation::addSpriteFrame)
        .member_function("addSpriteFrameWithFile", &ax::Animation::addSpriteFrameWithFile)
        .member_function("addSpriteFrameWithTexture", &ax::Animation::addSpriteFrameWithTexture)
        .member_function("getTotalDelayUnits", &ax::Animation::getTotalDelayUnits)
        .member_function("setDelayPerUnit", &ax::Animation::setDelayPerUnit)
        .member_function("getDelayPerUnit", &ax::Animation::getDelayPerUnit)
        .member_function("getDuration", &ax::Animation::getDuration)
        .member_function("getFrames", &ax::Animation::getFrames)
        .member_function("setFrames", &ax::Animation::setFrames)
        .member_function("getRestoreOriginalFrame", &ax::Animation::getRestoreOriginalFrame)
        .member_function("setRestoreOriginalFrame", &ax::Animation::setRestoreOriginalFrame)
        .member_function("getLoops", &ax::Animation::getLoops)
        .member_function("setLoops", &ax::Animation::setLoops)
        .member_function("clone", &ax::Animation::clone)
        .member_function("init", &ax::Animation::init)
        .member_function(
            "initWithSpriteFrames",
            [](ax::Animation* self, ax::Vector<ax::SpriteFrame*> arg0) { return self->initWithSpriteFrames(arg0); },
            [](ax::Animation* self, ax::Vector<ax::SpriteFrame*> arg0, float arg1) { return self->initWithSpriteFrames(arg0, arg1); },
            [](ax::Animation* self, ax::Vector<ax::SpriteFrame*> arg0, float arg1, unsigned int arg2)
            { return self->initWithSpriteFrames(arg0, arg1, arg2); })
        .member_function("initWithAnimationFrames", &ax::Animation::initWithAnimationFrames)
        .static_function(
            "create",
            [](ax::Vector<ax::AnimationFrame*> arg0, float arg1) { return ax::Animation::create(arg0, arg1); },
            [](ax::Vector<ax::AnimationFrame*> arg0, float arg1, unsigned int arg2) { return ax::Animation::create(arg0, arg1, arg2); },
            []() { return ax::Animation::create(); })
        .static_function(
            "createWithSpriteFrames",
            [](ax::Vector<ax::SpriteFrame*> arg0) { return ax::Animation::createWithSpriteFrames(arg0); },
            [](ax::Vector<ax::SpriteFrame*> arg0, float arg1) { return ax::Animation::createWithSpriteFrames(arg0, arg1); },
            [](ax::Vector<ax::SpriteFrame*> arg0, float arg1, unsigned int arg2)
            { return ax::Animation::createWithSpriteFrames(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("Animation", class_Animation);
}
static void js_register_ax_base_ActionInterval(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ActionInterval> class_ActionInterval(isolate);
    class_ActionInterval.template inherit<ax::FiniteTimeAction>()
        .member_function("getElapsed", &ax::ActionInterval::getElapsed)
        .member_function("setAmplitudeRate", &ax::ActionInterval::setAmplitudeRate)
        .member_function("getAmplitudeRate", &ax::ActionInterval::getAmplitudeRate)
        .member_function("initWithDuration", &ax::ActionInterval::initWithDuration)
        .auto_wrap_objects(true);
    mod.class_("ActionInterval", class_ActionInterval);
}
static void js_register_ax_base_Sequence(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Sequence> class_Sequence(isolate);
    class_Sequence.ctor([]() { return new ax::Sequence(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithTwoActions", &ax::Sequence::initWithTwoActions)
        .member_function("init", &ax::Sequence::init)
        .auto_wrap_objects(true);
    mod.class_("Sequence", class_Sequence);
}
static void js_register_ax_base_Repeat(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Repeat> class_Repeat(isolate);
    class_Repeat.ctor([]() { return new ax::Repeat(); })
        .template inherit<ax::ActionInterval>()
        .member_function("setInnerAction", &ax::Repeat::setInnerAction)
        .member_function("getInnerAction", &ax::Repeat::getInnerAction)
        .member_function("initWithAction", &ax::Repeat::initWithAction)
        .static_function("create", &ax::Repeat::create)
        .auto_wrap_objects(true);
    mod.class_("Repeat", class_Repeat);
}
static void js_register_ax_base_RepeatForever(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::RepeatForever> class_RepeatForever(isolate);
    class_RepeatForever.ctor([]() { return new ax::RepeatForever(); })
        .template inherit<ax::ActionInterval>()
        .member_function("setInnerAction", &ax::RepeatForever::setInnerAction)
        .member_function("getInnerAction", &ax::RepeatForever::getInnerAction)
        .member_function("initWithAction", &ax::RepeatForever::initWithAction)
        .static_function("create", &ax::RepeatForever::create)
        .auto_wrap_objects(true);
    mod.class_("RepeatForever", class_RepeatForever);
}
static void js_register_ax_base_Spawn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Spawn> class_Spawn(isolate);
    class_Spawn.ctor([]() { return new ax::Spawn(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithTwoActions", &ax::Spawn::initWithTwoActions)
        .member_function("init", &ax::Spawn::init)
        .auto_wrap_objects(true);
    mod.class_("Spawn", class_Spawn);
}
static void js_register_ax_base_RotateTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::RotateTo> class_RotateTo(isolate);
    class_RotateTo.ctor([]() { return new ax::RotateTo(); })
        .template inherit<ax::ActionInterval>()
        .member_function(
            "initWithDuration",
            [](ax::RotateTo* self, float arg0, ax::Vec3 arg1) { return self->initWithDuration(arg0, arg1); },
            [](ax::RotateTo* self, float arg0, float arg1, float arg2) { return self->initWithDuration(arg0, arg1, arg2); })
        .static_function(
            "create",
            [](float arg0, float arg1) { return ax::RotateTo::create(arg0, arg1); },
            [](float arg0, float arg1, float arg2) { return ax::RotateTo::create(arg0, arg1, arg2); },
            [](float arg0, ax::Vec3 arg1) { return ax::RotateTo::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("RotateTo", class_RotateTo);
}
static void js_register_ax_base_RotateBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::RotateBy> class_RotateBy(isolate);
    class_RotateBy.ctor([]() { return new ax::RotateBy(); })
        .template inherit<ax::ActionInterval>()
        .member_function(
            "initWithDuration",
            [](ax::RotateBy* self, float arg0, float arg1, float arg2) { return self->initWithDuration(arg0, arg1, arg2); },
            [](ax::RotateBy* self, float arg0, float arg1) { return self->initWithDuration(arg0, arg1); },
            [](ax::RotateBy* self, float arg0, ax::Vec3 arg1) { return self->initWithDuration(arg0, arg1); })
        .static_function(
            "create",
            [](float arg0, float arg1, float arg2) { return ax::RotateBy::create(arg0, arg1, arg2); },
            [](float arg0, float arg1) { return ax::RotateBy::create(arg0, arg1); },
            [](float arg0, ax::Vec3 arg1) { return ax::RotateBy::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("RotateBy", class_RotateBy);
}
static void js_register_ax_base_MoveBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MoveBy> class_MoveBy(isolate);
    class_MoveBy.ctor([]() { return new ax::MoveBy(); })
        .template inherit<ax::ActionInterval>()
        .member_function(
            "initWithDuration",
            [](ax::MoveBy* self, float arg0, ax::Vec3 arg1) { return self->initWithDuration(arg0, arg1); },
            [](ax::MoveBy* self, float arg0, ax::Vec2 arg1) { return self->initWithDuration(arg0, arg1); })
        .static_function(
            "create",
            [](float arg0, ax::Vec3 arg1) { return ax::MoveBy::create(arg0, arg1); },
            [](float arg0, ax::Vec2 arg1) { return ax::MoveBy::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("MoveBy", class_MoveBy);
}
static void js_register_ax_base_MoveTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MoveTo> class_MoveTo(isolate);
    class_MoveTo.ctor([]() { return new ax::MoveTo(); })
        .template inherit<ax::MoveBy>()
        .member_function(
            "initWithDuration",
            [](ax::MoveTo* self, float arg0, ax::Vec3 arg1) { return self->initWithDuration(arg0, arg1); },
            [](ax::MoveTo* self, float arg0, ax::Vec2 arg1) { return self->initWithDuration(arg0, arg1); })
        .static_function(
            "create",
            [](float arg0, ax::Vec3 arg1) { return ax::MoveTo::create(arg0, arg1); },
            [](float arg0, ax::Vec2 arg1) { return ax::MoveTo::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("MoveTo", class_MoveTo);
}
static void js_register_ax_base_SkewTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SkewTo> class_SkewTo(isolate);
    class_SkewTo.ctor([]() { return new ax::SkewTo(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::SkewTo::initWithDuration)
        .static_function("create", &ax::SkewTo::create)
        .auto_wrap_objects(true);
    mod.class_("SkewTo", class_SkewTo);
}
static void js_register_ax_base_SkewBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SkewBy> class_SkewBy(isolate);
    class_SkewBy.ctor([]() { return new ax::SkewBy(); })
        .template inherit<ax::SkewTo>()
        .member_function("initWithDuration", &ax::SkewBy::initWithDuration)
        .static_function("create", &ax::SkewBy::create)
        .auto_wrap_objects(true);
    mod.class_("SkewBy", class_SkewBy);
}
static void js_register_ax_base_JumpBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::JumpBy> class_JumpBy(isolate);
    class_JumpBy.ctor([]() { return new ax::JumpBy(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::JumpBy::initWithDuration)
        .static_function("create", &ax::JumpBy::create)
        .auto_wrap_objects(true);
    mod.class_("JumpBy", class_JumpBy);
}
static void js_register_ax_base_JumpTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::JumpTo> class_JumpTo(isolate);
    class_JumpTo.ctor([]() { return new ax::JumpTo(); })
        .template inherit<ax::JumpBy>()
        .member_function("initWithDuration", &ax::JumpTo::initWithDuration)
        .static_function("create", &ax::JumpTo::create)
        .auto_wrap_objects(true);
    mod.class_("JumpTo", class_JumpTo);
}
static void js_register_ax_base_BezierBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::BezierBy> class_BezierBy(isolate);
    class_BezierBy.ctor([]() { return new ax::BezierBy(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::BezierBy::initWithDuration)
        .auto_wrap_objects(true);
    mod.class_("BezierBy", class_BezierBy);
}
static void js_register_ax_base_BezierTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::BezierTo> class_BezierTo(isolate);
    class_BezierTo.ctor([]() { return new ax::BezierTo(); })
        .template inherit<ax::BezierBy>()
        .member_function("initWithDuration", &ax::BezierTo::initWithDuration)
        .auto_wrap_objects(true);
    mod.class_("BezierTo", class_BezierTo);
}
static void js_register_ax_base_ScaleTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ScaleTo> class_ScaleTo(isolate);
    class_ScaleTo.ctor([]() { return new ax::ScaleTo(); })
        .template inherit<ax::ActionInterval>()
        .member_function(
            "initWithDuration",
            [](ax::ScaleTo* self, float arg0, float arg1, float arg2) { return self->initWithDuration(arg0, arg1, arg2); },
            [](ax::ScaleTo* self, float arg0, float arg1) { return self->initWithDuration(arg0, arg1); },
            [](ax::ScaleTo* self, float arg0, float arg1, float arg2, float arg3)
            { return self->initWithDuration(arg0, arg1, arg2, arg3); })
        .static_function(
            "create",
            [](float arg0, float arg1, float arg2) { return ax::ScaleTo::create(arg0, arg1, arg2); },
            [](float arg0, float arg1) { return ax::ScaleTo::create(arg0, arg1); },
            [](float arg0, float arg1, float arg2, float arg3) { return ax::ScaleTo::create(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("ScaleTo", class_ScaleTo);
}
static void js_register_ax_base_ScaleBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ScaleBy> class_ScaleBy(isolate);
    class_ScaleBy.ctor([]() { return new ax::ScaleBy(); })
        .template inherit<ax::ScaleTo>()
        .static_function(
            "create",
            [](float arg0, float arg1, float arg2) { return ax::ScaleBy::create(arg0, arg1, arg2); },
            [](float arg0, float arg1) { return ax::ScaleBy::create(arg0, arg1); },
            [](float arg0, float arg1, float arg2, float arg3) { return ax::ScaleBy::create(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("ScaleBy", class_ScaleBy);
}
static void js_register_ax_base_Blink(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Blink> class_Blink(isolate);
    class_Blink.ctor([]() { return new ax::Blink(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::Blink::initWithDuration)
        .static_function("create", &ax::Blink::create)
        .auto_wrap_objects(true);
    mod.class_("Blink", class_Blink);
}
static void js_register_ax_base_FadeTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FadeTo> class_FadeTo(isolate);
    class_FadeTo.ctor([]() { return new ax::FadeTo(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::FadeTo::initWithDuration)
        .static_function("create", &ax::FadeTo::create)
        .auto_wrap_objects(true);
    mod.class_("FadeTo", class_FadeTo);
}
static void js_register_ax_base_FadeIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FadeIn> class_FadeIn(isolate);
    class_FadeIn.ctor([]() { return new ax::FadeIn(); })
        .template inherit<ax::FadeTo>()
        .member_function("setReverseAction", &ax::FadeIn::setReverseAction)
        .static_function("create", &ax::FadeIn::create)
        .auto_wrap_objects(true);
    mod.class_("FadeIn", class_FadeIn);
}
static void js_register_ax_base_FadeOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FadeOut> class_FadeOut(isolate);
    class_FadeOut.ctor([]() { return new ax::FadeOut(); })
        .template inherit<ax::FadeTo>()
        .member_function("setReverseAction", &ax::FadeOut::setReverseAction)
        .static_function("create", &ax::FadeOut::create)
        .auto_wrap_objects(true);
    mod.class_("FadeOut", class_FadeOut);
}
static void js_register_ax_base_TintTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TintTo> class_TintTo(isolate);
    class_TintTo.ctor([]() { return new ax::TintTo(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::TintTo::initWithDuration)
        .static_function(
            "create",
            [](float arg0, ax::Color32 arg1) { return ax::TintTo::create(arg0, arg1); },
            [](float arg0, uint16_t arg1, uint16_t arg2, uint16_t arg3) { return ax::TintTo::create(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("TintTo", class_TintTo);
}
static void js_register_ax_base_TintBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TintBy> class_TintBy(isolate);
    class_TintBy.ctor([]() { return new ax::TintBy(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::TintBy::initWithDuration)
        .static_function("create", &ax::TintBy::create)
        .auto_wrap_objects(true);
    mod.class_("TintBy", class_TintBy);
}
static void js_register_ax_base_DelayTime(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::DelayTime> class_DelayTime(isolate);
    class_DelayTime.ctor([]() { return new ax::DelayTime(); })
        .template inherit<ax::ActionInterval>()
        .static_function("create", &ax::DelayTime::create)
        .auto_wrap_objects(true);
    mod.class_("DelayTime", class_DelayTime);
}
static void js_register_ax_base_Animate(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Animate> class_Animate(isolate);
    class_Animate.ctor([]() { return new ax::Animate(); })
        .template inherit<ax::ActionInterval>()
        .member_function("setAnimation", &ax::Animate::setAnimation)
        .member_function(
            "getAnimation", [](ax::Animate* self) { return self->getAnimation(); }, [](ax::Animate* self) { return self->getAnimation(); })
        .member_function("getCurrentFrameIndex", &ax::Animate::getCurrentFrameIndex)
        .member_function("initWithAnimation", &ax::Animate::initWithAnimation)
        .static_function("create", &ax::Animate::create)
        .auto_wrap_objects(true);
    mod.class_("Animate", class_Animate);
}
static void js_register_ax_base_TargetedAction(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TargetedAction> class_TargetedAction(isolate);
    class_TargetedAction.ctor([]() { return new ax::TargetedAction(); })
        .template inherit<ax::ActionInterval>()
        .member_function("setForcedTarget", &ax::TargetedAction::setForcedTarget)
        .member_function(
            "getForcedTarget",
            [](ax::TargetedAction* self) { return self->getForcedTarget(); },
            [](ax::TargetedAction* self) { return self->getForcedTarget(); })
        .member_function("initWithTarget", &ax::TargetedAction::initWithTarget)
        .static_function("create", &ax::TargetedAction::create)
        .auto_wrap_objects(true);
    mod.class_("TargetedAction", class_TargetedAction);
}
static void js_register_ax_base_Scene(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Scene> class_Scene(isolate);
    class_Scene.ctor([]() { return new ax::Scene(); })
        .template inherit<ax::Node>()
        .member_function("getDefaultCamera", &ax::Scene::getDefaultCamera)
        .member_function("initWithSize", &ax::Scene::initWithSize)
        .member_function("setCameraOrderDirty", &ax::Scene::setCameraOrderDirty)
        .member_function("onProjectionChanged", &ax::Scene::onProjectionChanged)
        .member_function("getPhysicsWorld", &ax::Scene::getPhysicsWorld)
        .member_function("initWithPhysics", &ax::Scene::initWithPhysics)
        .member_function("initPhysicsWorld", &ax::Scene::initPhysicsWorld)
        .member_function("fixedUpdate", &ax::Scene::fixedUpdate)
        .member_function("stepPhysicsAndNavigation", &ax::Scene::stepPhysicsAndNavigation)
        .static_function("create", &ax::Scene::create)
        .static_function("createWithSize", &ax::Scene::createWithSize)
        .static_function("createWithPhysics", &ax::Scene::createWithPhysics)
        .auto_wrap_objects(true);
    mod.class_("Scene", class_Scene);
}
static void js_register_ax_base_RenderView(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::RenderView> class_RenderView(isolate);
    class_RenderView.template inherit<ax::Object>()
        .member_function("end", &ax::RenderView::end)
        .member_function("isGfxContextReady", &ax::RenderView::isGfxContextReady)
        .member_function("swapBuffers", &ax::RenderView::swapBuffers)
        .member_function("setIMEKeyboardState", &ax::RenderView::setIMEKeyboardState)
        .member_function("windowShouldClose", &ax::RenderView::windowShouldClose)
        .member_function("pollEvents", &ax::RenderView::pollEvents)
        .member_function("getNativeWindowSize", &ax::RenderView::getNativeWindowSize)
        .member_function("getWindowSize", &ax::RenderView::getWindowSize)
        .member_function("setWindowSize", &ax::RenderView::setWindowSize)
        .member_function("setWindowZoomFactor", &ax::RenderView::setWindowZoomFactor)
        .member_function("getWindowZoomFactor", &ax::RenderView::getWindowZoomFactor)
        .member_function("getRenderSize", &ax::RenderView::getRenderSize)
        .member_function("setCursorVisible", &ax::RenderView::setCursorVisible)
        .member_function("getRenderScale", &ax::RenderView::getRenderScale)
        .member_function("getVisibleSize", &ax::RenderView::getVisibleSize)
        .member_function("getVisibleOrigin", &ax::RenderView::getVisibleOrigin)
        .member_function("getVisibleRect", &ax::RenderView::getVisibleRect)
        .member_function("getSafeAreaRect", &ax::RenderView::getSafeAreaRect)
        .member_function("setDesignResolutionSize", &ax::RenderView::setDesignResolutionSize)
        .member_function("getDesignResolutionSize", &ax::RenderView::getDesignResolutionSize)
        .member_function("setViewportInPoints", &ax::RenderView::setViewportInPoints)
        .member_function("setScissorInPoints", &ax::RenderView::setScissorInPoints)
        .member_function("isScissorEnabled", &ax::RenderView::isScissorEnabled)
        .member_function("getScissorInPoints", &ax::RenderView::getScissorInPoints)
        .member_function("setViewName", &ax::RenderView::setViewName)
        .member_function("getViewName", &ax::RenderView::getViewName)
        .member_function(
            "setIcon",
            [](ax::RenderView* self, std::vector<std::string_view> arg0) { self->setIcon(arg0); },
            [](ax::RenderView* self, std::string_view arg0) { self->setIcon(arg0); })
        .member_function("setDefaultIcon", &ax::RenderView::setDefaultIcon)
        .member_function("getViewportRect", &ax::RenderView::getViewportRect)
        .member_function("getScaleX", &ax::RenderView::getScaleX)
        .member_function("getScaleY", &ax::RenderView::getScaleY)
        .member_function("getResolutionPolicy", &ax::RenderView::getResolutionPolicy)
        .member_function("getNativeWindow", &ax::RenderView::getNativeWindow)
        .member_function("getNativeDisplay", &ax::RenderView::getNativeDisplay)
        .member_function("getWindowPlatform", &ax::RenderView::getWindowPlatform)
        .member_function("renderScene", &ax::RenderView::renderScene)
        .member_function("setInteractive", &ax::RenderView::setInteractive)
        .auto_wrap_objects(true);
    mod.class_("RenderView", class_RenderView);
}
static void js_register_ax_base_Director(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Director> class_Director(isolate,
                                              [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_Director.member_function("init", &ax::Director::init)
        .member_function("getRunningScene", &ax::Director::getRunningScene)
        .member_function("getNextScene", &ax::Director::getNextScene)
        .member_function("getAnimationInterval", &ax::Director::getAnimationInterval)
        // .member_function("setAnimationInterval", &ax::Director::setAnimationInterval)
        .member_function("isStatsDisplay", &ax::Director::isStatsDisplay)
        .member_function("setStatsDisplay", &ax::Director::setStatsDisplay)
        .member_function("getSecondsPerFrame", &ax::Director::getSecondsPerFrame)
        .member_function(
            "setStatsAnchor",
            [](ax::Director* self) { self->setStatsAnchor(); },
            [](ax::Director* self, ax::AnchorPreset arg0) { self->setStatsAnchor(arg0); })
        .member_function("getRenderView", &ax::Director::getRenderView)
        .member_function("setRenderView", &ax::Director::setRenderView)
        .member_function("getTextureCache", &ax::Director::getTextureCache)
        .member_function("isNextDeltaTimeZero", &ax::Director::isNextDeltaTimeZero)
        .member_function("setNextDeltaTimeZero", &ax::Director::setNextDeltaTimeZero)
        .member_function("isPaused", &ax::Director::isPaused)
        .member_function("getTotalFrames", &ax::Director::getTotalFrames)
        .member_function("setProjection", &ax::Director::setProjection)
        .member_function("setViewport", &ax::Director::setViewport)
        .member_function("isSendCleanupToScene", &ax::Director::isSendCleanupToScene)
        .member_function("getNotificationNode", &ax::Director::getNotificationNode)
        .member_function("setNotificationNode", &ax::Director::setNotificationNode)
        .member_function("getCanvasSize", &ax::Director::getCanvasSize)
        .member_function("getCanvasSizeInPixels", &ax::Director::getCanvasSizeInPixels)
        .member_function("getVisibleSize", &ax::Director::getVisibleSize)
        .member_function("getVisibleOrigin", &ax::Director::getVisibleOrigin)
        .member_function("getSafeAreaRect", &ax::Director::getSafeAreaRect)
        .member_function("screenToWorld", &ax::Director::screenToWorld)
        .member_function("worldToScreen", &ax::Director::worldToScreen)
        .member_function("getZEye", &ax::Director::getZEye)
        .member_function("runWithScene", &ax::Director::runWithScene)
        .member_function("pushScene", &ax::Director::pushScene)
        .member_function("popScene", &ax::Director::popScene)
        .member_function("popToRootScene", &ax::Director::popToRootScene)
        .member_function("popToSceneStackLevel", &ax::Director::popToSceneStackLevel)
        .member_function("replaceScene", &ax::Director::replaceScene)
        .member_function("popPreviousSceneOut", &ax::Director::popPreviousSceneOut)
        .member_function("end", &ax::Director::end)
        .member_function("pause", &ax::Director::pause)
        .member_function("resume", &ax::Director::resume)
        .member_function("restart", &ax::Director::restart)
        .member_function("stopAnimation", &ax::Director::stopAnimation)
        // .member_function("startAnimation", &ax::Director::startAnimation)
        .member_function("drawScene", &ax::Director::drawScene)
        .member_function("purgeCachedData", &ax::Director::purgeCachedData)
        .member_function("setDefaultValues", &ax::Director::setDefaultValues)
        .member_function("setRenderDefaults", &ax::Director::setRenderDefaults)
        .member_function("setClearColor", &ax::Director::setClearColor)
        .member_function("getClearColor", &ax::Director::getClearColor)
        .member_function(
            "mainLoop", [](ax::Director* self, float arg0) { self->mainLoop(arg0); }, [](ax::Director* self) { self->mainLoop(); })
        .member_function("setContentScaleFactor", &ax::Director::setContentScaleFactor)
        .member_function("getContentScaleFactor", &ax::Director::getContentScaleFactor)
        .member_function("getScheduler", &ax::Director::getScheduler)
        .member_function("setScheduler", &ax::Director::setScheduler)
        .member_function("getActionManager", &ax::Director::getActionManager)
        .member_function("setActionManager", &ax::Director::setActionManager)
        .member_function("getEventDispatcher", &ax::Director::getEventDispatcher)
        .member_function("setEventDispatcher", &ax::Director::setEventDispatcher)
        .member_function("getRenderer", &ax::Director::getRenderer)
        .member_function("getDeltaTime", &ax::Director::getDeltaTime)
        .member_function("getFrameRate", &ax::Director::getFrameRate)
        .member_function("pushMatrix", &ax::Director::pushMatrix)
        .member_function("popMatrix", &ax::Director::popMatrix)
        .member_function("loadIdentityMatrix", &ax::Director::loadIdentityMatrix)
        .member_function("loadMatrix", &ax::Director::loadMatrix)
        .member_function("multiplyMatrix", &ax::Director::multiplyMatrix)
        .member_function("getMatrix", &ax::Director::getMatrix)
        .member_function("resetMatrixStack", &ax::Director::resetMatrixStack)
        .member_function("setChildrenIndexerEnabled", &ax::Director::setChildrenIndexerEnabled)
        .member_function("isChildrenIndexerEnabled", &ax::Director::isChildrenIndexerEnabled)
        .member_function("isValid", &ax::Director::isValid)
        .static_function("getInstance", &ax::Director::getInstance)
        .static_function("destroyInstance", &ax::Director::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("Director", class_Director);
}
static void js_register_ax_base_Timer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Timer> class_Timer(isolate);
    class_Timer.template inherit<ax::Object>()
        .member_function("setupTimerWithInterval", &ax::Timer::setupTimerWithInterval)
        .member_function("setAborted", &ax::Timer::setAborted)
        .member_function("isAborted", &ax::Timer::isAborted)
        .member_function("isExhausted", &ax::Timer::isExhausted)
        .member_function("trigger", &ax::Timer::trigger)
        .member_function("cancel", &ax::Timer::cancel)
        .member_function("update", &ax::Timer::update)
        .auto_wrap_objects(true);
    mod.class_("Timer", class_Timer);
}
static void js_register_ax_base_Scheduler(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Scheduler> class_Scheduler(isolate);
    class_Scheduler.ctor([]() { return new ax::Scheduler(); })
        .template inherit<ax::Object>()
        .member_function("getTimeScale", &ax::Scheduler::getTimeScale)
        .member_function("setTimeScale", &ax::Scheduler::setTimeScale)
        .member_function("runOnAxmolThread", &ax::Scheduler::runOnAxmolThread)
        .member_function("removeAllPendingActions", &ax::Scheduler::removeAllPendingActions)
        .auto_wrap_objects(true);
    mod.class_("Scheduler", class_Scheduler);
}
static void js_register_ax_base_UserDefault(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::UserDefault> class_UserDefault(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_UserDefault
        .member_function(
            "getBoolForKey",
            [](ax::UserDefault* self, const char* arg0, bool arg1) { return self->getBoolForKey(arg0, arg1); },
            [](ax::UserDefault* self, const char* arg0) { return self->getBoolForKey(arg0); })
        .member_function(
            "getIntegerForKey",
            [](ax::UserDefault* self, const char* arg0, int arg1) { return self->getIntegerForKey(arg0, arg1); },
            [](ax::UserDefault* self, const char* arg0) { return self->getIntegerForKey(arg0); })
        .member_function(
            "getLargeIntForKey",
            [](ax::UserDefault* self, const char* arg0, long long arg1) { return self->getLargeIntForKey(arg0, arg1); },
            [](ax::UserDefault* self, const char* arg0) { return self->getLargeIntForKey(arg0); })
        .member_function(
            "getFloatForKey",
            [](ax::UserDefault* self, const char* arg0, float arg1) { return self->getFloatForKey(arg0, arg1); },
            [](ax::UserDefault* self, const char* arg0) { return self->getFloatForKey(arg0); })
        .member_function(
            "getDoubleForKey",
            [](ax::UserDefault* self, const char* arg0, double arg1) { return self->getDoubleForKey(arg0, arg1); },
            [](ax::UserDefault* self, const char* arg0) { return self->getDoubleForKey(arg0); })
        .member_function(
            "getStringForKey",
            [](ax::UserDefault* self, const char* arg0, std::string_view arg1) { return self->getStringForKey(arg0, arg1); },
            [](ax::UserDefault* self, const char* arg0) { return self->getStringForKey(arg0); })
        .member_function("setBoolForKey", &ax::UserDefault::setBoolForKey)
        .member_function("setIntegerForKey", &ax::UserDefault::setIntegerForKey)
        .member_function("setLargeIntForKey", &ax::UserDefault::setLargeIntForKey)
        .member_function("setFloatForKey", &ax::UserDefault::setFloatForKey)
        .member_function("setDoubleForKey", &ax::UserDefault::setDoubleForKey)
        .member_function("setStringForKey", &ax::UserDefault::setStringForKey)
        .member_function("flush", &ax::UserDefault::flush)
        .member_function("deleteValueForKey", &ax::UserDefault::deleteValueForKey)
        .member_function("setEncryptEnabled", &ax::UserDefault::setEncryptEnabled)
        .static_function("destroyInstance", &ax::UserDefault::destroyInstance)
        .static_function(
            "setFileName", []() { ax::UserDefault::setFileName(); }, [](std::string_view arg0) { ax::UserDefault::setFileName(arg0); })
        .auto_wrap_objects(true);
    mod.class_("UserDefault", class_UserDefault);
}
static void js_register_ax_base_FileUtils(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FileUtils> class_FileUtils(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_FileUtils.member_function("purgeCachedEntries", &ax::FileUtils::purgeCachedEntries)
        .member_function("getStringFromFile", &ax::FileUtils::getStringFromFile)
        .member_function("fullPathForFilename", &ax::FileUtils::fullPathForFilename)
        .member_function("fullPathFromRelativeFile", &ax::FileUtils::fullPathFromRelativeFile)
        .member_function("fullPathForDirectory", &ax::FileUtils::fullPathForDirectory)
        .member_function("setSearchPaths", &ax::FileUtils::setSearchPaths)
        .member_function("getDefaultResourceRootPath", &ax::FileUtils::getDefaultResourceRootPath)
        .member_function("setDefaultResourceRootPath", &ax::FileUtils::setDefaultResourceRootPath)
        .member_function(
            "addSearchPath",
            [](ax::FileUtils* self, std::string_view arg0) { self->addSearchPath(arg0); },
            [](ax::FileUtils* self, std::string_view arg0, bool arg1) { self->addSearchPath(arg0, arg1); })
        .member_function("getSearchPaths", &ax::FileUtils::getSearchPaths)
        .member_function("getOriginalSearchPaths", &ax::FileUtils::getOriginalSearchPaths)
        .member_function("getWritablePath", &ax::FileUtils::getWritablePath)
        .member_function("getNativeWritableAbsolutePath", &ax::FileUtils::getNativeWritableAbsolutePath)
        .member_function("setWritablePath", &ax::FileUtils::setWritablePath)
        .member_function("setPopupNotify", &ax::FileUtils::setPopupNotify)
        .member_function("isPopupNotify", &ax::FileUtils::isPopupNotify)
        .member_function("getValueMapFromFile", &ax::FileUtils::getValueMapFromFile)
        .member_function("getValueMapFromData", &ax::FileUtils::getValueMapFromData)
        .member_function("writeToFile", &ax::FileUtils::writeToFile)
        .member_function("writeStringToFile", &ax::FileUtils::writeStringToFile)
        .member_function("writeValueMapToFile", &ax::FileUtils::writeValueMapToFile)
        .member_function("writeValueVectorToFile", &ax::FileUtils::writeValueVectorToFile)
        .member_function("getValueVectorFromFile", &ax::FileUtils::getValueVectorFromFile)
        .member_function("isFileExist", &ax::FileUtils::isFileExist)
        .member_function("isAbsolutePath", &ax::FileUtils::isAbsolutePath)
        .member_function("isDirectoryExist", &ax::FileUtils::isDirectoryExist)
        .member_function("createDirectories", &ax::FileUtils::createDirectories)
        .member_function("removeDirectory", &ax::FileUtils::removeDirectory)
        .member_function("removeFile", &ax::FileUtils::removeFile)
        .member_function(
            "renameFile",
            [](ax::FileUtils* self, std::string_view arg0, std::string_view arg1) { return self->renameFile(arg0, arg1); },
            [](ax::FileUtils* self, std::string_view arg0, std::string_view arg1, std::string_view arg2)
            { return self->renameFile(arg0, arg1, arg2); })
        .member_function("getFileSize", &ax::FileUtils::getFileSize)
        .member_function("listFiles", &ax::FileUtils::listFiles)
        .member_function("isFileExistInternal", &ax::FileUtils::isFileExistInternal)
        .member_function("isDirectoryExistInternal", &ax::FileUtils::isDirectoryExistInternal)
        .static_function("getInstance", &ax::FileUtils::getInstance)
        .static_function("destroyInstance", &ax::FileUtils::destroyInstance)
        .static_function("getPathExtension", &ax::FileUtils::getPathExtension)
        .static_function("getPathBaseName", &ax::FileUtils::getPathBaseName)
        .static_function("getPathBaseNameNoExtension", &ax::FileUtils::getPathBaseNameNoExtension)
        .static_function("getPathDirName", &ax::FileUtils::getPathDirName)
        .static_function("isAbsolutePathInternal", &ax::FileUtils::isAbsolutePathInternal)
        .auto_wrap_objects(true);
    mod.class_("FileUtils", class_FileUtils);
}
static void js_register_ax_base_EventAcceleration(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventAcceleration> class_EventAcceleration(isolate);
    class_EventAcceleration.template inherit<ax::Event>().auto_wrap_objects(true);
    mod.class_("EventAcceleration", class_EventAcceleration);
}
static void js_register_ax_base_EventCustom(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventCustom> class_EventCustom(isolate);
    class_EventCustom.ctor([](std::string_view arg0) { return new ax::EventCustom(arg0); })
        .template inherit<ax::Event>()
        .member_function("getEventName", &ax::EventCustom::getEventName)
        .auto_wrap_objects(true);
    mod.class_("EventCustom", class_EventCustom);
}
static void js_register_ax_base_EventDispatcher(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventDispatcher> class_EventDispatcher(isolate);
    class_EventDispatcher.ctor([]() { return new ax::EventDispatcher(); })
        .template inherit<ax::Object>()
        .member_function("addEventListenerWithSceneGraphPriority", &ax::EventDispatcher::addEventListenerWithSceneGraphPriority)
        .member_function("addEventListenerWithFixedPriority", &ax::EventDispatcher::addEventListenerWithFixedPriority)
        .member_function("addCustomEventListener", &ax::EventDispatcher::addCustomEventListener)
        .member_function("removeEventListener", &ax::EventDispatcher::removeEventListener)
        .member_function("removeEventListenersForType", &ax::EventDispatcher::removeEventListenersForType)
        .member_function(
            "removeEventListenersForTarget",
            [](ax::EventDispatcher* self, ax::Node* arg0) { self->removeEventListenersForTarget(arg0); },
            [](ax::EventDispatcher* self, ax::Node* arg0, bool arg1) { self->removeEventListenersForTarget(arg0, arg1); })
        .member_function("removeCustomEventListeners", &ax::EventDispatcher::removeCustomEventListeners)
        .member_function("removeAllEventListeners", &ax::EventDispatcher::removeAllEventListeners)
        .member_function(
            "pauseEventListenersForTarget",
            [](ax::EventDispatcher* self, ax::Node* arg0) { self->pauseEventListenersForTarget(arg0); },
            [](ax::EventDispatcher* self, ax::Node* arg0, bool arg1) { self->pauseEventListenersForTarget(arg0, arg1); })
        .member_function(
            "resumeEventListenersForTarget",
            [](ax::EventDispatcher* self, ax::Node* arg0) { self->resumeEventListenersForTarget(arg0); },
            [](ax::EventDispatcher* self, ax::Node* arg0, bool arg1) { self->resumeEventListenersForTarget(arg0, arg1); })
        .member_function("setPriority", &ax::EventDispatcher::setPriority)
        .member_function("setEnabled", &ax::EventDispatcher::setEnabled)
        .member_function("isEnabled", &ax::EventDispatcher::isEnabled)
        .member_function(
            "dispatchEvent",
            [](ax::EventDispatcher* self, ax::Event* arg0) { self->dispatchEvent(arg0); },
            [](ax::EventDispatcher* self, ax::Event* arg0, bool arg1) { self->dispatchEvent(arg0, arg1); })
        .member_function(
            "dispatchCustomEvent",
            [](ax::EventDispatcher* self, std::string_view arg0) { self->dispatchCustomEvent(arg0); },
            [](ax::EventDispatcher* self, std::string_view arg0, void* arg1) { self->dispatchCustomEvent(arg0, arg1); },
            [](ax::EventDispatcher* self, std::string_view arg0, void* arg1, bool arg2) { self->dispatchCustomEvent(arg0, arg1, arg2); })
        .member_function("hasEventListener", &ax::EventDispatcher::hasEventListener)
        .auto_wrap_objects(true);
    mod.class_("EventDispatcher", class_EventDispatcher);
}
static void js_register_ax_base_EventFocus(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventFocus> class_EventFocus(isolate);
    class_EventFocus.ctor([](ax::ui::Widget* arg0, ax::ui::Widget* arg1) { return new ax::EventFocus(arg0, arg1); })
        .template inherit<ax::Event>()
        .auto_wrap_objects(true);
    mod.class_("EventFocus", class_EventFocus);
}
static void js_register_ax_base_EventMouse(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EventMouse> class_EventMouse(isolate);
    class_EventMouse.ctor([](ax::EventMouse::MouseEventType arg0) { return new ax::EventMouse(); })
        .template inherit<ax::Event>()
        .member_function("getMouseEventType", &ax::EventMouse::getMouseEventType)
        .member_function("setScrollData", &ax::EventMouse::setScrollData)
        .member_function("getScrollX", &ax::EventMouse::getScrollX)
        .member_function("getScrollY", &ax::EventMouse::getScrollY)
        .member_function("setMouseInfo", &ax::EventMouse::setMouseInfo)
        .member_function("setMouseButton", &ax::EventMouse::setMouseButton)
        .member_function("getMouseButton", &ax::EventMouse::getMouseButton)
        .member_function("getLocation", &ax::EventMouse::getLocation)
        .member_function("getPreviousLocation", &ax::EventMouse::getPreviousLocation)
        .member_function("getStartLocation", &ax::EventMouse::getStartLocation)
        .member_function("getDelta", &ax::EventMouse::getDelta)
        .member_function("getLocationInView", &ax::EventMouse::getLocationInView)
        .member_function("getPreviousLocationInView", &ax::EventMouse::getPreviousLocationInView)
        .member_function("getStartLocationInView", &ax::EventMouse::getStartLocationInView)
        .auto_wrap_objects(true);
    mod.class_("EventMouse", class_EventMouse);
}
static void js_register_ax_base_EventController(v8pp::module& mod)
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
static void js_register_ax_base_ActionCamera(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ActionCamera> class_ActionCamera(isolate);
    class_ActionCamera.ctor([]() { return new ax::ActionCamera(); })
        .template inherit<ax::ActionInterval>()
        .member_function(
            "setEye",
            [](ax::ActionCamera* self, float arg0, float arg1, float arg2) { self->setEye(arg0, arg1, arg2); },
            [](ax::ActionCamera* self, ax::Vec3 arg0) { self->setEye(arg0); })
        .member_function("getEye", &ax::ActionCamera::getEye)
        .member_function("setCenter", &ax::ActionCamera::setCenter)
        .member_function("getCenter", &ax::ActionCamera::getCenter)
        .member_function("setUp", &ax::ActionCamera::setUp)
        .member_function("getUp", &ax::ActionCamera::getUp)
        .auto_wrap_objects(true);
    mod.class_("ActionCamera", class_ActionCamera);
}
static void js_register_ax_base_OrbitCamera(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::OrbitCamera> class_OrbitCamera(isolate);
    class_OrbitCamera.ctor([]() { return new ax::OrbitCamera(); })
        .template inherit<ax::ActionCamera>()
        .member_function("initWithDuration", &ax::OrbitCamera::initWithDuration)
        .static_function("create", &ax::OrbitCamera::create)
        .auto_wrap_objects(true);
    mod.class_("OrbitCamera", class_OrbitCamera);
}
static void js_register_ax_base_CardinalSplineTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CardinalSplineTo> class_CardinalSplineTo(isolate);
    class_CardinalSplineTo.ctor([]() { return new ax::CardinalSplineTo(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::CardinalSplineTo::initWithDuration)
        .member_function("updatePosition", &ax::CardinalSplineTo::updatePosition)
        .member_function("getPoints", &ax::CardinalSplineTo::getPoints)
        .auto_wrap_objects(true);
    mod.class_("CardinalSplineTo", class_CardinalSplineTo);
}
static void js_register_ax_base_CardinalSplineBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CardinalSplineBy> class_CardinalSplineBy(isolate);
    class_CardinalSplineBy.ctor([]() { return new ax::CardinalSplineBy(); })
        .template inherit<ax::CardinalSplineTo>()
        .auto_wrap_objects(true);
    mod.class_("CardinalSplineBy", class_CardinalSplineBy);
}
static void js_register_ax_base_CatmullRomTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CatmullRomTo> class_CatmullRomTo(isolate);
    class_CatmullRomTo.template inherit<ax::CardinalSplineTo>()
        .member_function("initWithDuration", &ax::CatmullRomTo::initWithDuration)
        .auto_wrap_objects(true);
    mod.class_("CatmullRomTo", class_CatmullRomTo);
}
static void js_register_ax_base_CatmullRomBy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CatmullRomBy> class_CatmullRomBy(isolate);
    class_CatmullRomBy.template inherit<ax::CardinalSplineBy>()
        .member_function("initWithDuration", &ax::CatmullRomBy::initWithDuration)
        .auto_wrap_objects(true);
    mod.class_("CatmullRomBy", class_CatmullRomBy);
}
static void js_register_ax_base_ActionEase(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ActionEase> class_ActionEase(isolate);
    class_ActionEase.template inherit<ax::ActionInterval>()
        .member_function("getInnerAction", &ax::ActionEase::getInnerAction)
        .member_function("initWithAction", &ax::ActionEase::initWithAction)
        .auto_wrap_objects(true);
    mod.class_("ActionEase", class_ActionEase);
}
static void js_register_ax_base_EaseRateAction(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseRateAction> class_EaseRateAction(isolate);
    class_EaseRateAction.template inherit<ax::ActionEase>()
        .member_function("setRate", &ax::EaseRateAction::setRate)
        .member_function("getRate", &ax::EaseRateAction::getRate)
        .member_function("initWithAction", &ax::EaseRateAction::initWithAction)
        .static_function("create", &ax::EaseRateAction::create)
        .auto_wrap_objects(true);
    mod.class_("EaseRateAction", class_EaseRateAction);
}
static void js_register_ax_base_EaseExponentialIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseExponentialIn> class_EaseExponentialIn(isolate);
    class_EaseExponentialIn.ctor([]() { return new ax::EaseExponentialIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseExponentialIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseExponentialIn", class_EaseExponentialIn);
}
static void js_register_ax_base_EaseExponentialOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseExponentialOut> class_EaseExponentialOut(isolate);
    class_EaseExponentialOut.ctor([]() { return new ax::EaseExponentialOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseExponentialOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseExponentialOut", class_EaseExponentialOut);
}
static void js_register_ax_base_EaseExponentialInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseExponentialInOut> class_EaseExponentialInOut(isolate);
    class_EaseExponentialInOut.ctor([]() { return new ax::EaseExponentialInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseExponentialInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseExponentialInOut", class_EaseExponentialInOut);
}
static void js_register_ax_base_EaseSineIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseSineIn> class_EaseSineIn(isolate);
    class_EaseSineIn.ctor([]() { return new ax::EaseSineIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseSineIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseSineIn", class_EaseSineIn);
}
static void js_register_ax_base_EaseSineOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseSineOut> class_EaseSineOut(isolate);
    class_EaseSineOut.ctor([]() { return new ax::EaseSineOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseSineOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseSineOut", class_EaseSineOut);
}
static void js_register_ax_base_EaseSineInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseSineInOut> class_EaseSineInOut(isolate);
    class_EaseSineInOut.ctor([]() { return new ax::EaseSineInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseSineInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseSineInOut", class_EaseSineInOut);
}
static void js_register_ax_base_EaseBounce(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseBounce> class_EaseBounce(isolate);
    class_EaseBounce.template inherit<ax::ActionEase>().auto_wrap_objects(true);
    mod.class_("EaseBounce", class_EaseBounce);
}
static void js_register_ax_base_EaseBounceIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseBounceIn> class_EaseBounceIn(isolate);
    class_EaseBounceIn.ctor([]() { return new ax::EaseBounceIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseBounceIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseBounceIn", class_EaseBounceIn);
}
static void js_register_ax_base_EaseBounceOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseBounceOut> class_EaseBounceOut(isolate);
    class_EaseBounceOut.ctor([]() { return new ax::EaseBounceOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseBounceOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseBounceOut", class_EaseBounceOut);
}
static void js_register_ax_base_EaseBounceInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseBounceInOut> class_EaseBounceInOut(isolate);
    class_EaseBounceInOut.ctor([]() { return new ax::EaseBounceInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseBounceInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseBounceInOut", class_EaseBounceInOut);
}
static void js_register_ax_base_EaseBackIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseBackIn> class_EaseBackIn(isolate);
    class_EaseBackIn.ctor([]() { return new ax::EaseBackIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseBackIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseBackIn", class_EaseBackIn);
}
static void js_register_ax_base_EaseBackOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseBackOut> class_EaseBackOut(isolate);
    class_EaseBackOut.ctor([]() { return new ax::EaseBackOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseBackOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseBackOut", class_EaseBackOut);
}
static void js_register_ax_base_EaseBackInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseBackInOut> class_EaseBackInOut(isolate);
    class_EaseBackInOut.ctor([]() { return new ax::EaseBackInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseBackInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseBackInOut", class_EaseBackInOut);
}
static void js_register_ax_base_EaseQuadraticActionIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuadraticActionIn> class_EaseQuadraticActionIn(isolate);
    class_EaseQuadraticActionIn.ctor([]() { return new ax::EaseQuadraticActionIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuadraticActionIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuadraticActionIn", class_EaseQuadraticActionIn);
}
static void js_register_ax_base_EaseQuadraticActionOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuadraticActionOut> class_EaseQuadraticActionOut(isolate);
    class_EaseQuadraticActionOut.ctor([]() { return new ax::EaseQuadraticActionOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuadraticActionOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuadraticActionOut", class_EaseQuadraticActionOut);
}
static void js_register_ax_base_EaseQuadraticActionInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuadraticActionInOut> class_EaseQuadraticActionInOut(isolate);
    class_EaseQuadraticActionInOut.ctor([]() { return new ax::EaseQuadraticActionInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuadraticActionInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuadraticActionInOut", class_EaseQuadraticActionInOut);
}
static void js_register_ax_base_EaseQuarticActionIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuarticActionIn> class_EaseQuarticActionIn(isolate);
    class_EaseQuarticActionIn.ctor([]() { return new ax::EaseQuarticActionIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuarticActionIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuarticActionIn", class_EaseQuarticActionIn);
}
static void js_register_ax_base_EaseQuarticActionOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuarticActionOut> class_EaseQuarticActionOut(isolate);
    class_EaseQuarticActionOut.ctor([]() { return new ax::EaseQuarticActionOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuarticActionOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuarticActionOut", class_EaseQuarticActionOut);
}
static void js_register_ax_base_EaseQuarticActionInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuarticActionInOut> class_EaseQuarticActionInOut(isolate);
    class_EaseQuarticActionInOut.ctor([]() { return new ax::EaseQuarticActionInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuarticActionInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuarticActionInOut", class_EaseQuarticActionInOut);
}
static void js_register_ax_base_EaseQuinticActionIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuinticActionIn> class_EaseQuinticActionIn(isolate);
    class_EaseQuinticActionIn.ctor([]() { return new ax::EaseQuinticActionIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuinticActionIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuinticActionIn", class_EaseQuinticActionIn);
}
static void js_register_ax_base_EaseQuinticActionOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuinticActionOut> class_EaseQuinticActionOut(isolate);
    class_EaseQuinticActionOut.ctor([]() { return new ax::EaseQuinticActionOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuinticActionOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuinticActionOut", class_EaseQuinticActionOut);
}
static void js_register_ax_base_EaseQuinticActionInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseQuinticActionInOut> class_EaseQuinticActionInOut(isolate);
    class_EaseQuinticActionInOut.ctor([]() { return new ax::EaseQuinticActionInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseQuinticActionInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseQuinticActionInOut", class_EaseQuinticActionInOut);
}
static void js_register_ax_base_EaseCircleActionIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseCircleActionIn> class_EaseCircleActionIn(isolate);
    class_EaseCircleActionIn.ctor([]() { return new ax::EaseCircleActionIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseCircleActionIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseCircleActionIn", class_EaseCircleActionIn);
}
static void js_register_ax_base_EaseCircleActionOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseCircleActionOut> class_EaseCircleActionOut(isolate);
    class_EaseCircleActionOut.ctor([]() { return new ax::EaseCircleActionOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseCircleActionOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseCircleActionOut", class_EaseCircleActionOut);
}
static void js_register_ax_base_EaseCircleActionInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseCircleActionInOut> class_EaseCircleActionInOut(isolate);
    class_EaseCircleActionInOut.ctor([]() { return new ax::EaseCircleActionInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseCircleActionInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseCircleActionInOut", class_EaseCircleActionInOut);
}
static void js_register_ax_base_EaseCubicActionIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseCubicActionIn> class_EaseCubicActionIn(isolate);
    class_EaseCubicActionIn.ctor([]() { return new ax::EaseCubicActionIn(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseCubicActionIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseCubicActionIn", class_EaseCubicActionIn);
}
static void js_register_ax_base_EaseCubicActionOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseCubicActionOut> class_EaseCubicActionOut(isolate);
    class_EaseCubicActionOut.ctor([]() { return new ax::EaseCubicActionOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseCubicActionOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseCubicActionOut", class_EaseCubicActionOut);
}
static void js_register_ax_base_EaseCubicActionInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseCubicActionInOut> class_EaseCubicActionInOut(isolate);
    class_EaseCubicActionInOut.ctor([]() { return new ax::EaseCubicActionInOut(); })
        .template inherit<ax::ActionEase>()
        .static_function("create", &ax::EaseCubicActionInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseCubicActionInOut", class_EaseCubicActionInOut);
}
static void js_register_ax_base_EaseIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseIn> class_EaseIn(isolate);
    class_EaseIn.ctor([]() { return new ax::EaseIn(); })
        .template inherit<ax::EaseRateAction>()
        .static_function("create", &ax::EaseIn::create)
        .auto_wrap_objects(true);
    mod.class_("EaseIn", class_EaseIn);
}
static void js_register_ax_base_EaseOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseOut> class_EaseOut(isolate);
    class_EaseOut.ctor([]() { return new ax::EaseOut(); })
        .template inherit<ax::EaseRateAction>()
        .static_function("create", &ax::EaseOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseOut", class_EaseOut);
}
static void js_register_ax_base_EaseInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseInOut> class_EaseInOut(isolate);
    class_EaseInOut.ctor([]() { return new ax::EaseInOut(); })
        .template inherit<ax::EaseRateAction>()
        .static_function("create", &ax::EaseInOut::create)
        .auto_wrap_objects(true);
    mod.class_("EaseInOut", class_EaseInOut);
}
static void js_register_ax_base_EaseElastic(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseElastic> class_EaseElastic(isolate);
    class_EaseElastic.template inherit<ax::ActionEase>()
        .member_function("getPeriod", &ax::EaseElastic::getPeriod)
        .member_function("setPeriod", &ax::EaseElastic::setPeriod)
        .member_function(
            "initWithAction",
            [](ax::EaseElastic* self, ax::ActionInterval* arg0) { return self->initWithAction(arg0); },
            [](ax::EaseElastic* self, ax::ActionInterval* arg0, float arg1) { return self->initWithAction(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("EaseElastic", class_EaseElastic);
}
static void js_register_ax_base_EaseElasticIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseElasticIn> class_EaseElasticIn(isolate);
    class_EaseElasticIn.ctor([]() { return new ax::EaseElasticIn(); })
        .template inherit<ax::EaseElastic>()
        .static_function(
            "create",
            [](ax::ActionInterval* arg0) { return ax::EaseElasticIn::create(arg0); },
            [](ax::ActionInterval* arg0, float arg1) { return ax::EaseElasticIn::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("EaseElasticIn", class_EaseElasticIn);
}
static void js_register_ax_base_EaseElasticOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseElasticOut> class_EaseElasticOut(isolate);
    class_EaseElasticOut.ctor([]() { return new ax::EaseElasticOut(); })
        .template inherit<ax::EaseElastic>()
        .static_function(
            "create",
            [](ax::ActionInterval* arg0) { return ax::EaseElasticOut::create(arg0); },
            [](ax::ActionInterval* arg0, float arg1) { return ax::EaseElasticOut::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("EaseElasticOut", class_EaseElasticOut);
}
static void js_register_ax_base_EaseElasticInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseElasticInOut> class_EaseElasticInOut(isolate);
    class_EaseElasticInOut.ctor([]() { return new ax::EaseElasticInOut(); })
        .template inherit<ax::EaseElastic>()
        .static_function(
            "create",
            [](ax::ActionInterval* arg0) { return ax::EaseElasticInOut::create(arg0); },
            [](ax::ActionInterval* arg0, float arg1) { return ax::EaseElasticInOut::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("EaseElasticInOut", class_EaseElasticInOut);
}
static void js_register_ax_base_EaseBezierAction(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::EaseBezierAction> class_EaseBezierAction(isolate);
    class_EaseBezierAction.ctor([]() { return new ax::EaseBezierAction(); })
        .template inherit<ax::ActionEase>()
        .member_function("setBezierParamer", &ax::EaseBezierAction::setBezierParamer)
        .static_function("create", &ax::EaseBezierAction::create)
        .auto_wrap_objects(true);
    mod.class_("EaseBezierAction", class_EaseBezierAction);
}
static void js_register_ax_base_ActionInstant(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ActionInstant> class_ActionInstant(isolate);
    class_ActionInstant.template inherit<ax::FiniteTimeAction>().auto_wrap_objects(true);
    mod.class_("ActionInstant", class_ActionInstant);
}
static void js_register_ax_base_Show(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Show> class_Show(isolate);
    class_Show.ctor([]() { return new ax::Show(); })
        .template inherit<ax::ActionInstant>()
        .static_function("create", &ax::Show::create)
        .auto_wrap_objects(true);
    mod.class_("Show", class_Show);
}
static void js_register_ax_base_Hide(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Hide> class_Hide(isolate);
    class_Hide.ctor([]() { return new ax::Hide(); })
        .template inherit<ax::ActionInstant>()
        .static_function("create", &ax::Hide::create)
        .auto_wrap_objects(true);
    mod.class_("Hide", class_Hide);
}
static void js_register_ax_base_ToggleVisibility(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ToggleVisibility> class_ToggleVisibility(isolate);
    class_ToggleVisibility.ctor([]() { return new ax::ToggleVisibility(); })
        .template inherit<ax::ActionInstant>()
        .static_function("create", &ax::ToggleVisibility::create)
        .auto_wrap_objects(true);
    mod.class_("ToggleVisibility", class_ToggleVisibility);
}
static void js_register_ax_base_RemoveSelf(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::RemoveSelf> class_RemoveSelf(isolate);
    class_RemoveSelf.ctor([]() { return new ax::RemoveSelf(); })
        .template inherit<ax::ActionInstant>()
        .member_function("init", &ax::RemoveSelf::init)
        .static_function(
            "create", []() { return ax::RemoveSelf::create(); }, [](bool arg0) { return ax::RemoveSelf::create(arg0); })
        .auto_wrap_objects(true);
    mod.class_("RemoveSelf", class_RemoveSelf);
}
static void js_register_ax_base_FlipX(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FlipX> class_FlipX(isolate);
    class_FlipX.ctor([]() { return new ax::FlipX(); })
        .template inherit<ax::ActionInstant>()
        .member_function("initWithFlipX", &ax::FlipX::initWithFlipX)
        .static_function("create", &ax::FlipX::create)
        .auto_wrap_objects(true);
    mod.class_("FlipX", class_FlipX);
}
static void js_register_ax_base_FlipY(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FlipY> class_FlipY(isolate);
    class_FlipY.ctor([]() { return new ax::FlipY(); })
        .template inherit<ax::ActionInstant>()
        .member_function("initWithFlipY", &ax::FlipY::initWithFlipY)
        .static_function("create", &ax::FlipY::create)
        .auto_wrap_objects(true);
    mod.class_("FlipY", class_FlipY);
}
static void js_register_ax_base_Place(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Place> class_Place(isolate);
    class_Place.ctor([]() { return new ax::Place(); })
        .template inherit<ax::ActionInstant>()
        .member_function("initWithPosition", &ax::Place::initWithPosition)
        .static_function("create", &ax::Place::create)
        .auto_wrap_objects(true);
    mod.class_("Place", class_Place);
}
static void js_register_ax_base_CallFunc(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CallFunc> class_CallFunc(isolate);
    class_CallFunc.ctor([]() { return new ax::CallFunc(); })
        .template inherit<ax::ActionInstant>()
        .member_function("execute", &ax::CallFunc::execute)
        .member_function("initWithFunction", &ax::CallFunc::initWithFunction)
        .static_function("create", &ax::CallFunc::create)
        .auto_wrap_objects(true);
    mod.class_("CallFunc", class_CallFunc);
}
static void js_register_ax_base_GridAction(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::GridAction> class_GridAction(isolate);
    class_GridAction.template inherit<ax::ActionInterval>()
        .member_function("getGrid", &ax::GridAction::getGrid)
        .member_function("initWithDuration", &ax::GridAction::initWithDuration)
        .auto_wrap_objects(true);
    mod.class_("GridAction", class_GridAction);
}
static void js_register_ax_base_Grid3DAction(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Grid3DAction> class_Grid3DAction(isolate);
    class_Grid3DAction.template inherit<ax::GridAction>()
        .member_function("getGridRect", &ax::Grid3DAction::getGridRect)
        .auto_wrap_objects(true);
    mod.class_("Grid3DAction", class_Grid3DAction);
}
static void js_register_ax_base_TiledGrid3DAction(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TiledGrid3DAction> class_TiledGrid3DAction(isolate);
    class_TiledGrid3DAction.template inherit<ax::GridAction>().auto_wrap_objects(true);
    mod.class_("TiledGrid3DAction", class_TiledGrid3DAction);
}
static void js_register_ax_base_StopGrid(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::StopGrid> class_StopGrid(isolate);
    class_StopGrid.ctor([]() { return new ax::StopGrid(); })
        .template inherit<ax::ActionInstant>()
        .static_function("create", &ax::StopGrid::create)
        .auto_wrap_objects(true);
    mod.class_("StopGrid", class_StopGrid);
}
static void js_register_ax_base_ReuseGrid(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ReuseGrid> class_ReuseGrid(isolate);
    class_ReuseGrid.ctor([]() { return new ax::ReuseGrid(); })
        .template inherit<ax::ActionInstant>()
        .member_function("initWithTimes", &ax::ReuseGrid::initWithTimes)
        .static_function("create", &ax::ReuseGrid::create)
        .auto_wrap_objects(true);
    mod.class_("ReuseGrid", class_ReuseGrid);
}
static void js_register_ax_base_Waves3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Waves3D> class_Waves3D(isolate);
    class_Waves3D.ctor([]() { return new ax::Waves3D(); })
        .template inherit<ax::Grid3DAction>()
        .member_function("getAmplitude", &ax::Waves3D::getAmplitude)
        .member_function("setAmplitude", &ax::Waves3D::setAmplitude)
        .member_function("getAmplitudeRate", &ax::Waves3D::getAmplitudeRate)
        .member_function("setAmplitudeRate", &ax::Waves3D::setAmplitudeRate)
        .member_function("initWithDuration", &ax::Waves3D::initWithDuration)
        .static_function("create", &ax::Waves3D::create)
        .auto_wrap_objects(true);
    mod.class_("Waves3D", class_Waves3D);
}
static void js_register_ax_base_FlipX3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FlipX3D> class_FlipX3D(isolate);
    class_FlipX3D.ctor([]() { return new ax::FlipX3D(); })
        .template inherit<ax::Grid3DAction>()
        .member_function("initWithDuration", &ax::FlipX3D::initWithDuration)
        .member_function("initWithSize", &ax::FlipX3D::initWithSize)
        .static_function("create", &ax::FlipX3D::create)
        .auto_wrap_objects(true);
    mod.class_("FlipX3D", class_FlipX3D);
}
static void js_register_ax_base_FlipY3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FlipY3D> class_FlipY3D(isolate);
    class_FlipY3D.ctor([]() { return new ax::FlipY3D(); })
        .template inherit<ax::FlipX3D>()
        .static_function("create", &ax::FlipY3D::create)
        .auto_wrap_objects(true);
    mod.class_("FlipY3D", class_FlipY3D);
}
static void js_register_ax_base_Lens3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Lens3D> class_Lens3D(isolate);
    class_Lens3D.ctor([]() { return new ax::Lens3D(); })
        .template inherit<ax::Grid3DAction>()
        .member_function("getLensEffect", &ax::Lens3D::getLensEffect)
        .member_function("setLensEffect", &ax::Lens3D::setLensEffect)
        .member_function("setConcave", &ax::Lens3D::setConcave)
        .member_function("getPosition", &ax::Lens3D::getPosition)
        .member_function("setPosition", &ax::Lens3D::setPosition)
        .member_function("initWithDuration", &ax::Lens3D::initWithDuration)
        .static_function("create", &ax::Lens3D::create)
        .auto_wrap_objects(true);
    mod.class_("Lens3D", class_Lens3D);
}
static void js_register_ax_base_Ripple3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Ripple3D> class_Ripple3D(isolate);
    class_Ripple3D.ctor([]() { return new ax::Ripple3D(); })
        .template inherit<ax::Grid3DAction>()
        .member_function("getPosition", &ax::Ripple3D::getPosition)
        .member_function("setPosition", &ax::Ripple3D::setPosition)
        .member_function("getAmplitude", &ax::Ripple3D::getAmplitude)
        .member_function("setAmplitude", &ax::Ripple3D::setAmplitude)
        .member_function("getAmplitudeRate", &ax::Ripple3D::getAmplitudeRate)
        .member_function("setAmplitudeRate", &ax::Ripple3D::setAmplitudeRate)
        .member_function("initWithDuration", &ax::Ripple3D::initWithDuration)
        .static_function("create", &ax::Ripple3D::create)
        .auto_wrap_objects(true);
    mod.class_("Ripple3D", class_Ripple3D);
}
static void js_register_ax_base_Shaky3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Shaky3D> class_Shaky3D(isolate);
    class_Shaky3D.ctor([]() { return new ax::Shaky3D(); })
        .template inherit<ax::Grid3DAction>()
        .member_function("initWithDuration", &ax::Shaky3D::initWithDuration)
        .static_function("create", &ax::Shaky3D::create)
        .auto_wrap_objects(true);
    mod.class_("Shaky3D", class_Shaky3D);
}
static void js_register_ax_base_Liquid(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Liquid> class_Liquid(isolate);
    class_Liquid.ctor([]() { return new ax::Liquid(); })
        .template inherit<ax::Grid3DAction>()
        .member_function("getAmplitude", &ax::Liquid::getAmplitude)
        .member_function("setAmplitude", &ax::Liquid::setAmplitude)
        .member_function("getAmplitudeRate", &ax::Liquid::getAmplitudeRate)
        .member_function("setAmplitudeRate", &ax::Liquid::setAmplitudeRate)
        .member_function("initWithDuration", &ax::Liquid::initWithDuration)
        .static_function("create", &ax::Liquid::create)
        .auto_wrap_objects(true);
    mod.class_("Liquid", class_Liquid);
}
static void js_register_ax_base_Waves(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Waves> class_Waves(isolate);
    class_Waves.ctor([]() { return new ax::Waves(); })
        .template inherit<ax::Grid3DAction>()
        .member_function("getAmplitude", &ax::Waves::getAmplitude)
        .member_function("setAmplitude", &ax::Waves::setAmplitude)
        .member_function("getAmplitudeRate", &ax::Waves::getAmplitudeRate)
        .member_function("setAmplitudeRate", &ax::Waves::setAmplitudeRate)
        .member_function("initWithDuration", &ax::Waves::initWithDuration)
        .static_function("create", &ax::Waves::create)
        .auto_wrap_objects(true);
    mod.class_("Waves", class_Waves);
}
static void js_register_ax_base_Twirl(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Twirl> class_Twirl(isolate);
    class_Twirl.ctor([]() { return new ax::Twirl(); })
        .template inherit<ax::Grid3DAction>()
        .member_function("getPosition", &ax::Twirl::getPosition)
        .member_function("setPosition", &ax::Twirl::setPosition)
        .member_function("getAmplitude", &ax::Twirl::getAmplitude)
        .member_function("setAmplitude", &ax::Twirl::setAmplitude)
        .member_function("getAmplitudeRate", &ax::Twirl::getAmplitudeRate)
        .member_function("setAmplitudeRate", &ax::Twirl::setAmplitudeRate)
        .member_function("initWithDuration", &ax::Twirl::initWithDuration)
        .static_function("create", &ax::Twirl::create)
        .auto_wrap_objects(true);
    mod.class_("Twirl", class_Twirl);
}
static void js_register_ax_base_ActionManager(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ActionManager> class_ActionManager(isolate);
    class_ActionManager.ctor([]() { return new ax::ActionManager(); })
        .template inherit<ax::Object>()
        .member_function("addAction", &ax::ActionManager::addAction)
        .member_function("removeAllActions", &ax::ActionManager::removeAllActions)
        .member_function("removeAllActionsFromTarget", &ax::ActionManager::removeAllActionsFromTarget)
        .member_function("removeAction", &ax::ActionManager::removeAction)
        .member_function("removeActionByTag", &ax::ActionManager::removeActionByTag)
        .member_function("removeAllActionsByTag", &ax::ActionManager::removeAllActionsByTag)
        .member_function("removeActionsByFlags", &ax::ActionManager::removeActionsByFlags)
        .member_function("getActionByTag", &ax::ActionManager::getActionByTag)
        .member_function("getNumberOfRunningActionsInTarget", &ax::ActionManager::getNumberOfRunningActionsInTarget)
        .member_function("getNumberOfRunningActions", &ax::ActionManager::getNumberOfRunningActions)
        .member_function("getNumberOfRunningActionsInTargetByTag", &ax::ActionManager::getNumberOfRunningActionsInTargetByTag)
        .member_function("pauseTarget", &ax::ActionManager::pauseTarget)
        .member_function("resumeTarget", &ax::ActionManager::resumeTarget)
        .member_function("pauseAllRunningActions", &ax::ActionManager::pauseAllRunningActions)
        .member_function("resumeTargets", &ax::ActionManager::resumeTargets)
        .member_function("update", &ax::ActionManager::update)
        .auto_wrap_objects(true);
    mod.class_("ActionManager", class_ActionManager);
}
static void js_register_ax_base_PageTurn3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PageTurn3D> class_PageTurn3D(isolate);
    class_PageTurn3D.template inherit<ax::Grid3DAction>().static_function("create", &ax::PageTurn3D::create).auto_wrap_objects(true);
    mod.class_("PageTurn3D", class_PageTurn3D);
}
static void js_register_ax_base_ProgressTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ProgressTo> class_ProgressTo(isolate);
    class_ProgressTo.ctor([]() { return new ax::ProgressTo(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::ProgressTo::initWithDuration)
        .static_function("create", &ax::ProgressTo::create)
        .auto_wrap_objects(true);
    mod.class_("ProgressTo", class_ProgressTo);
}
static void js_register_ax_base_ProgressFromTo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ProgressFromTo> class_ProgressFromTo(isolate);
    class_ProgressFromTo.ctor([]() { return new ax::ProgressFromTo(); })
        .template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::ProgressFromTo::initWithDuration)
        .static_function("create", &ax::ProgressFromTo::create)
        .auto_wrap_objects(true);
    mod.class_("ProgressFromTo", class_ProgressFromTo);
}
static void js_register_ax_base_ShakyTiles3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ShakyTiles3D> class_ShakyTiles3D(isolate);
    class_ShakyTiles3D.ctor([]() { return new ax::ShakyTiles3D(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("initWithDuration", &ax::ShakyTiles3D::initWithDuration)
        .static_function("create", &ax::ShakyTiles3D::create)
        .auto_wrap_objects(true);
    mod.class_("ShakyTiles3D", class_ShakyTiles3D);
}
static void js_register_ax_base_ShatteredTiles3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ShatteredTiles3D> class_ShatteredTiles3D(isolate);
    class_ShatteredTiles3D.ctor([]() { return new ax::ShatteredTiles3D(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("initWithDuration", &ax::ShatteredTiles3D::initWithDuration)
        .static_function("create", &ax::ShatteredTiles3D::create)
        .auto_wrap_objects(true);
    mod.class_("ShatteredTiles3D", class_ShatteredTiles3D);
}
static void js_register_ax_base_ShuffleTiles(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ShuffleTiles> class_ShuffleTiles(isolate);
    class_ShuffleTiles.ctor([]() { return new ax::ShuffleTiles(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("getDelta", &ax::ShuffleTiles::getDelta)
        .member_function("initWithDuration", &ax::ShuffleTiles::initWithDuration)
        .static_function("create", &ax::ShuffleTiles::create)
        .auto_wrap_objects(true);
    mod.class_("ShuffleTiles", class_ShuffleTiles);
}
static void js_register_ax_base_FadeOutTRTiles(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FadeOutTRTiles> class_FadeOutTRTiles(isolate);
    class_FadeOutTRTiles.ctor([]() { return new ax::FadeOutTRTiles(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("testFunc", &ax::FadeOutTRTiles::testFunc)
        .member_function("turnOnTile", &ax::FadeOutTRTiles::turnOnTile)
        .member_function("turnOffTile", &ax::FadeOutTRTiles::turnOffTile)
        .member_function("transformTile", &ax::FadeOutTRTiles::transformTile)
        .static_function("create", &ax::FadeOutTRTiles::create)
        .auto_wrap_objects(true);
    mod.class_("FadeOutTRTiles", class_FadeOutTRTiles);
}
static void js_register_ax_base_FadeOutBLTiles(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FadeOutBLTiles> class_FadeOutBLTiles(isolate);
    class_FadeOutBLTiles.ctor([]() { return new ax::FadeOutBLTiles(); })
        .template inherit<ax::FadeOutTRTiles>()
        .static_function("create", &ax::FadeOutBLTiles::create)
        .auto_wrap_objects(true);
    mod.class_("FadeOutBLTiles", class_FadeOutBLTiles);
}
static void js_register_ax_base_FadeOutUpTiles(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FadeOutUpTiles> class_FadeOutUpTiles(isolate);
    class_FadeOutUpTiles.ctor([]() { return new ax::FadeOutUpTiles(); })
        .template inherit<ax::FadeOutTRTiles>()
        .static_function("create", &ax::FadeOutUpTiles::create)
        .auto_wrap_objects(true);
    mod.class_("FadeOutUpTiles", class_FadeOutUpTiles);
}
static void js_register_ax_base_FadeOutDownTiles(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FadeOutDownTiles> class_FadeOutDownTiles(isolate);
    class_FadeOutDownTiles.ctor([]() { return new ax::FadeOutDownTiles(); })
        .template inherit<ax::FadeOutUpTiles>()
        .static_function("create", &ax::FadeOutDownTiles::create)
        .auto_wrap_objects(true);
    mod.class_("FadeOutDownTiles", class_FadeOutDownTiles);
}
static void js_register_ax_base_TurnOffTiles(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TurnOffTiles> class_TurnOffTiles(isolate);
    class_TurnOffTiles.ctor([]() { return new ax::TurnOffTiles(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("turnOnTile", &ax::TurnOffTiles::turnOnTile)
        .member_function("turnOffTile", &ax::TurnOffTiles::turnOffTile)
        .member_function("initWithDuration", &ax::TurnOffTiles::initWithDuration)
        .static_function(
            "create",
            [](float arg0, ax::Vec2 arg1, unsigned int arg2) { return ax::TurnOffTiles::create(arg0, arg1, arg2); },
            [](float arg0, ax::Vec2 arg1) { return ax::TurnOffTiles::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("TurnOffTiles", class_TurnOffTiles);
}
static void js_register_ax_base_WavesTiles3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::WavesTiles3D> class_WavesTiles3D(isolate);
    class_WavesTiles3D.ctor([]() { return new ax::WavesTiles3D(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("getAmplitude", &ax::WavesTiles3D::getAmplitude)
        .member_function("setAmplitude", &ax::WavesTiles3D::setAmplitude)
        .member_function("getAmplitudeRate", &ax::WavesTiles3D::getAmplitudeRate)
        .member_function("setAmplitudeRate", &ax::WavesTiles3D::setAmplitudeRate)
        .member_function("initWithDuration", &ax::WavesTiles3D::initWithDuration)
        .static_function("create", &ax::WavesTiles3D::create)
        .auto_wrap_objects(true);
    mod.class_("WavesTiles3D", class_WavesTiles3D);
}
static void js_register_ax_base_JumpTiles3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::JumpTiles3D> class_JumpTiles3D(isolate);
    class_JumpTiles3D.ctor([]() { return new ax::JumpTiles3D(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("getAmplitude", &ax::JumpTiles3D::getAmplitude)
        .member_function("setAmplitude", &ax::JumpTiles3D::setAmplitude)
        .member_function("getAmplitudeRate", &ax::JumpTiles3D::getAmplitudeRate)
        .member_function("setAmplitudeRate", &ax::JumpTiles3D::setAmplitudeRate)
        .member_function("initWithDuration", &ax::JumpTiles3D::initWithDuration)
        .static_function("create", &ax::JumpTiles3D::create)
        .auto_wrap_objects(true);
    mod.class_("JumpTiles3D", class_JumpTiles3D);
}
static void js_register_ax_base_SplitRows(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SplitRows> class_SplitRows(isolate);
    class_SplitRows.ctor([]() { return new ax::SplitRows(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("initWithDuration", &ax::SplitRows::initWithDuration)
        .static_function("create", &ax::SplitRows::create)
        .auto_wrap_objects(true);
    mod.class_("SplitRows", class_SplitRows);
}
static void js_register_ax_base_SplitCols(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SplitCols> class_SplitCols(isolate);
    class_SplitCols.ctor([]() { return new ax::SplitCols(); })
        .template inherit<ax::TiledGrid3DAction>()
        .member_function("initWithDuration", &ax::SplitCols::initWithDuration)
        .static_function("create", &ax::SplitCols::create)
        .auto_wrap_objects(true);
    mod.class_("SplitCols", class_SplitCols);
}
static void js_register_ax_base_ActionTween(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ActionTween> class_ActionTween(isolate);
    class_ActionTween.template inherit<ax::ActionInterval>()
        .member_function("initWithDuration", &ax::ActionTween::initWithDuration)
        .static_function("create", &ax::ActionTween::create)
        .auto_wrap_objects(true);
    mod.class_("ActionTween", class_ActionTween);
}
static void js_register_ax_base_AtlasNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::AtlasNode> class_AtlasNode(isolate);
    class_AtlasNode.ctor([]() { return new ax::AtlasNode(); })
        .template inherit<ax::Node>()
        .member_function("updateAtlasValues", &ax::AtlasNode::updateAtlasValues)
        .member_function("getTexture", &ax::AtlasNode::getTexture)
        .member_function("setTexture", &ax::AtlasNode::setTexture)
        .member_function("setBlendFunc", &ax::AtlasNode::setBlendFunc)
        .member_function("getBlendFunc", &ax::AtlasNode::getBlendFunc)
        .member_function("setTextureAtlas", &ax::AtlasNode::setTextureAtlas)
        .member_function("getTextureAtlas", &ax::AtlasNode::getTextureAtlas)
        .member_function("setQuadsToDraw", &ax::AtlasNode::setQuadsToDraw)
        .member_function("getQuadsToDraw", &ax::AtlasNode::getQuadsToDraw)
        .member_function("initWithTileFile", &ax::AtlasNode::initWithTileFile)
        .member_function("initWithTexture", &ax::AtlasNode::initWithTexture)
        .static_function("create", &ax::AtlasNode::create)
        .auto_wrap_objects(true);
    mod.class_("AtlasNode", class_AtlasNode);
}
static void js_register_ax_base_ClippingNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ClippingNode> class_ClippingNode(isolate);
    class_ClippingNode.template inherit<ax::Node>()
        .member_function("getStencil", &ax::ClippingNode::getStencil)
        .member_function(
            "setStencil",
            [](ax::ClippingNode* self, ax::Node* arg0) { self->setStencil(arg0); },
            [](ax::ClippingNode* self, ax::Node* arg0, bool arg1) { self->setStencil(arg0, arg1); })
        .member_function("hasContent", &ax::ClippingNode::hasContent)
        .member_function("getAlphaThreshold", &ax::ClippingNode::getAlphaThreshold)
        .member_function("setAlphaThreshold", &ax::ClippingNode::setAlphaThreshold)
        .member_function("isInverted", &ax::ClippingNode::isInverted)
        .member_function("setInverted", &ax::ClippingNode::setInverted)
        .static_function(
            "create", [](ax::Node* arg0) { return ax::ClippingNode::create(arg0); }, []() { return ax::ClippingNode::create(); })
        .auto_wrap_objects(true);
    mod.class_("ClippingNode", class_ClippingNode);
}
static void js_register_ax_base_ClippingRectangleNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ClippingRectangleNode> class_ClippingRectangleNode(isolate);
    class_ClippingRectangleNode.template inherit<ax::Node>()
        .member_function("getClippingRegion", &ax::ClippingRectangleNode::getClippingRegion)
        .member_function("setClippingRegion", &ax::ClippingRectangleNode::setClippingRegion)
        .member_function("isClippingEnabled", &ax::ClippingRectangleNode::isClippingEnabled)
        .member_function("setClippingEnabled", &ax::ClippingRectangleNode::setClippingEnabled)
        .static_function(
            "create",
            []() { return ax::ClippingRectangleNode::create(); },
            [](ax::Rect arg0) { return ax::ClippingRectangleNode::create(arg0); })
        .auto_wrap_objects(true);
    mod.class_("ClippingRectangleNode", class_ClippingRectangleNode);
}
static void js_register_ax_base_DrawNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::DrawNode> class_DrawNode(isolate);
    class_DrawNode.ctor([]() { return new ax::DrawNode(); })
        .template inherit<ax::Node>()
        .member_function(
            "drawPoint",
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, ax::Color arg2) { self->drawPoint(arg0, arg1, arg2); },
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, ax::Color arg2, ax::DrawNode::PointType arg3)
            { self->drawPoint(arg0, arg1, arg2, arg3); })
        .member_function(
            "drawLine",
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Color arg2) { self->drawLine(arg0, arg1, arg2); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Color arg2, float arg3) { self->drawLine(arg0, arg1, arg2, arg3); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Color arg2, float arg3, ax::DrawNode::EndType arg4)
            { self->drawLine(arg0, arg1, arg2, arg3, arg4); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               ax::Vec2 arg1,
               ax::Color arg2,
               float arg3,
               ax::DrawNode::EndType arg4,
               ax::DrawNode::EndType arg5) { self->drawLine(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function(
            "drawRect",
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Vec2 arg2, ax::Vec2 arg3, ax::Color arg4)
            { self->drawRect(arg0, arg1, arg2, arg3, arg4); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Vec2 arg2, ax::Vec2 arg3, ax::Color arg4, float arg5)
            { self->drawRect(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Color arg2) { self->drawRect(arg0, arg1, arg2); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Color arg2, float arg3) { self->drawRect(arg0, arg1, arg2, arg3); })
        .member_function(
            "drawCircle",
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, unsigned int arg3, bool arg4, ax::Color arg5)
            { self->drawCircle(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, unsigned int arg3, bool arg4, ax::Color arg5, float arg6)
            { self->drawCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               float arg1,
               float arg2,
               unsigned int arg3,
               bool arg4,
               float arg5,
               float arg6,
               ax::Color arg7) { self->drawCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               float arg1,
               float arg2,
               unsigned int arg3,
               bool arg4,
               float arg5,
               float arg6,
               ax::Color arg7,
               float arg8) { self->drawCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); })
        .member_function(
            "drawStar",
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, unsigned int arg3, ax::Color arg4)
            { self->drawStar(arg0, arg1, arg2, arg3, arg4); },
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, unsigned int arg3, ax::Color arg4, float arg5)
            { self->drawStar(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function(
            "drawSolidStar",
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, unsigned int arg3, ax::Color arg4, ax::Color arg5)
            { self->drawSolidStar(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, unsigned int arg3, ax::Color arg4, ax::Color arg5, float arg6)
            { self->drawSolidStar(arg0, arg1, arg2, arg3, arg4, arg5, arg6); })
        .member_function(
            "drawQuadBezier",
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Vec2 arg2, unsigned int arg3, ax::Color arg4)
            { self->drawQuadBezier(arg0, arg1, arg2, arg3, arg4); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Vec2 arg2, unsigned int arg3, ax::Color arg4, float arg5)
            { self->drawQuadBezier(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function(
            "drawCubicBezier",
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Vec2 arg2, ax::Vec2 arg3, unsigned int arg4, ax::Color arg5)
            { self->drawCubicBezier(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               ax::Vec2 arg1,
               ax::Vec2 arg2,
               ax::Vec2 arg3,
               unsigned int arg4,
               ax::Color arg5,
               float arg6) { self->drawCubicBezier(arg0, arg1, arg2, arg3, arg4, arg5, arg6); })
        .member_function("drawDot", &ax::DrawNode::drawDot)
        .member_function(
            "drawSolidRect",
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Color arg2) { self->drawSolidRect(arg0, arg1, arg2); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Color arg2, float arg3)
            { self->drawSolidRect(arg0, arg1, arg2, arg3); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, ax::Color arg2, float arg3, ax::Color arg4)
            { self->drawSolidRect(arg0, arg1, arg2, arg3, arg4); })
        .member_function(
            "drawSolidCircle",
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, unsigned int arg3, float arg4, float arg5, ax::Color arg6)
            { self->drawSolidCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               float arg1,
               float arg2,
               unsigned int arg3,
               float arg4,
               float arg5,
               ax::Color arg6,
               float arg7,
               ax::Color arg8) { self->drawSolidCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               float arg1,
               float arg2,
               unsigned int arg3,
               float arg4,
               float arg5,
               ax::Color arg6,
               float arg7,
               ax::Color arg8,
               bool arg9) { self->drawSolidCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); },
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, unsigned int arg3, ax::Color arg4)
            { self->drawSolidCircle(arg0, arg1, arg2, arg3, arg4); })
        .member_function(
            "drawPie",
            [](ax::DrawNode* self, ax::Vec2 arg0, float arg1, float arg2, int arg3, int arg4, float arg5, float arg6, ax::Color arg7)
            { self->drawPie(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               float arg1,
               float arg2,
               int arg3,
               int arg4,
               float arg5,
               float arg6,
               ax::Color arg7,
               ax::DrawNode::DrawMode arg8) { self->drawPie(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               float arg1,
               float arg2,
               int arg3,
               int arg4,
               float arg5,
               float arg6,
               ax::Color arg7,
               ax::Color arg8) { self->drawPie(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               float arg1,
               float arg2,
               int arg3,
               int arg4,
               float arg5,
               float arg6,
               ax::Color arg7,
               ax::Color arg8,
               ax::DrawNode::DrawMode arg9) { self->drawPie(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               float arg1,
               float arg2,
               int arg3,
               int arg4,
               float arg5,
               float arg6,
               ax::Color arg7,
               ax::Color arg8,
               ax::DrawNode::DrawMode arg9,
               float arg10) { self->drawPie(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); })
        .member_function(
            "drawSegment",
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, float arg2, ax::Color arg3) { self->drawSegment(arg0, arg1, arg2, arg3); },
            [](ax::DrawNode* self, ax::Vec2 arg0, ax::Vec2 arg1, float arg2, ax::Color arg3, ax::DrawNode::EndType arg4)
            { self->drawSegment(arg0, arg1, arg2, arg3, arg4); },
            [](ax::DrawNode* self,
               ax::Vec2 arg0,
               ax::Vec2 arg1,
               float arg2,
               ax::Color arg3,
               ax::DrawNode::EndType arg4,
               ax::DrawNode::EndType arg5) { self->drawSegment(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function("clear", &ax::DrawNode::clear)
        .member_function("getBlendFunc", &ax::DrawNode::getBlendFunc)
        .member_function("setBlendFunc", &ax::DrawNode::setBlendFunc)
        .member_function("setIsolated", &ax::DrawNode::setIsolated)
        .member_function("isIsolated", &ax::DrawNode::isIsolated)
        .static_function("create", &ax::DrawNode::create)
        .auto_wrap_objects(true);
    mod.class_("DrawNode", class_DrawNode);
}
static void js_register_ax_base_Label(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Label> class_Label(isolate);
    class_Label.template inherit<ax::Node>()
        // .member_function("setTTFConfig", &ax::Label::setTTFConfig)
        // .member_function("getTTFConfig", &ax::Label::getTTFConfig)
        .member_function(
            "setBMFontFilePath",
            [](ax::Label* self, std::string_view arg0, ax::Rect arg1, bool arg2) { return self->setBMFontFilePath(arg0, arg1, arg2); },
            [](ax::Label* self, std::string_view arg0, ax::Rect arg1, bool arg2, float arg3)
            { return self->setBMFontFilePath(arg0, arg1, arg2, arg3); },
            [](ax::Label* self, std::string_view arg0) { return self->setBMFontFilePath(arg0); },
            [](ax::Label* self, std::string_view arg0, float arg1) { return self->setBMFontFilePath(arg0, arg1); },
            [](ax::Label* self, std::string_view arg0, std::string_view arg1) { return self->setBMFontFilePath(arg0, arg1); },
            [](ax::Label* self, std::string_view arg0, std::string_view arg1, float arg2)
            { return self->setBMFontFilePath(arg0, arg1, arg2); })
        .member_function("getBMFontFilePath", &ax::Label::getBMFontFilePath)
        .member_function(
            "setCharMap",
            [](ax::Label* self, ax::Texture2D* arg0, int arg1, int arg2, int arg3) { return self->setCharMap(arg0, arg1, arg2, arg3); },
            [](ax::Label* self, std::string_view arg0, int arg1, int arg2, int arg3) { return self->setCharMap(arg0, arg1, arg2, arg3); },
            [](ax::Label* self, std::string_view arg0) { return self->setCharMap(arg0); })
        .member_function("setSystemFontName", &ax::Label::setSystemFontName)
        .member_function("getSystemFontName", &ax::Label::getSystemFontName)
        .member_function("setSystemFontSize", &ax::Label::setSystemFontSize)
        .member_function("getSystemFontSize", &ax::Label::getSystemFontSize)
        .member_function("requestSystemFontRefresh", &ax::Label::requestSystemFontRefresh)
        .member_function("setString", &ax::Label::setString)
        .member_function("getString", &ax::Label::getString)
        .member_function("getStringNumLines", &ax::Label::getStringNumLines)
        .member_function("getStringLength", &ax::Label::getStringLength)
        .member_function("setTextColor", &ax::Label::setTextColor)
        .member_function("getTextColor", &ax::Label::getTextColor)
        .member_function(
            "enableShadow",
            [](ax::Label* self) { self->enableShadow(); },
            [](ax::Label* self, ax::Color32 arg0) { self->enableShadow(arg0); },
            [](ax::Label* self, ax::Color32 arg0, ax::Vec2 arg1) { self->enableShadow(arg0, arg1); },
            [](ax::Label* self, ax::Color32 arg0, ax::Vec2 arg1, int arg2) { self->enableShadow(arg0, arg1, arg2); })
        .member_function(
            "enableOutline",
            [](ax::Label* self, ax::Color32 arg0) { self->enableOutline(arg0); },
            [](ax::Label* self, ax::Color32 arg0, float arg1) { self->enableOutline(arg0, arg1); })
        .member_function(
            "enableGlow",
            [](ax::Label* self, ax::Color32 arg0) { self->enableGlow(arg0); },
            [](ax::Label* self, ax::Color32 arg0, float arg1) { self->enableGlow(arg0, arg1); })
        .member_function("enableItalics", &ax::Label::enableItalics)
        .member_function("enableBold", &ax::Label::enableBold)
        .member_function("enableUnderline", &ax::Label::enableUnderline)
        .member_function("enableStrikethrough", &ax::Label::enableStrikethrough)
        .member_function(
            "disableEffect",
            [](ax::Label* self, ax::LabelEffect arg0) { self->disableEffect(arg0); },
            [](ax::Label* self) { self->disableEffect(); })
        .member_function("isShadowEnabled", &ax::Label::isShadowEnabled)
        .member_function("getShadowOffset", &ax::Label::getShadowOffset)
        .member_function("getShadowBlurRadius", &ax::Label::getShadowBlurRadius)
        .member_function("getShadowColor", &ax::Label::getShadowColor)
        .member_function("getOutlineSize", &ax::Label::getOutlineSize)
        .member_function("getGlowRadius", &ax::Label::getGlowRadius)
        .member_function("getLabelEffectType", &ax::Label::getLabelEffectType)
        .member_function("getEffectColor", &ax::Label::getEffectColor)
        .member_function(
            "setAlignment",
            [](ax::Label* self, ax::TextHAlignment arg0, ax::TextVAlignment arg1) { self->setAlignment(arg0, arg1); },
            [](ax::Label* self, ax::TextHAlignment arg0) { self->setAlignment(arg0); })
        .member_function("getTextAlignment", &ax::Label::getTextAlignment)
        .member_function("setHorizontalAlignment", &ax::Label::setHorizontalAlignment)
        .member_function("getHorizontalAlignment", &ax::Label::getHorizontalAlignment)
        .member_function("setVerticalAlignment", &ax::Label::setVerticalAlignment)
        .member_function("getVerticalAlignment", &ax::Label::getVerticalAlignment)
        .member_function("setLineBreakWithoutSpace", &ax::Label::setLineBreakWithoutSpace)
        .member_function("setMaxLineWidth", &ax::Label::setMaxLineWidth)
        .member_function("getMaxLineWidth", &ax::Label::getMaxLineWidth)
        .member_function("setTTFFaceSize", &ax::Label::setTTFFaceSize)
        .member_function("getTTFFaceSize", &ax::Label::getTTFFaceSize)
        .member_function("setBMFontSize", &ax::Label::setBMFontSize)
        .member_function("getBMFontSize", &ax::Label::getBMFontSize)
        .member_function("enableWrap", &ax::Label::enableWrap)
        .member_function("isWrapEnabled", &ax::Label::isWrapEnabled)
        .member_function("setOverflow", &ax::Label::setOverflow)
        .member_function("getOverflow", &ax::Label::getOverflow)
        .member_function("setWidth", &ax::Label::setWidth)
        .member_function("getWidth", &ax::Label::getWidth)
        .member_function("setHeight", &ax::Label::setHeight)
        .member_function("getHeight", &ax::Label::getHeight)
        .member_function("setDimensions", &ax::Label::setDimensions)
        .member_function("getDimensions", &ax::Label::getDimensions)
        .member_function("updateContent", &ax::Label::updateContent)
        .member_function("getLetter", &ax::Label::getLetter)
        .member_function("setClipMarginEnabled", &ax::Label::setClipMarginEnabled)
        .member_function("isClipMarginEnabled", &ax::Label::isClipMarginEnabled)
        .member_function("setLineHeight", &ax::Label::setLineHeight)
        .member_function("getLineHeight", &ax::Label::getLineHeight)
        .member_function("setLineSpacing", &ax::Label::setLineSpacing)
        .member_function("getLineSpacing", &ax::Label::getLineSpacing)
        .member_function("getLabelType", &ax::Label::getLabelType)
        .member_function("getRenderingFontSize", &ax::Label::getRenderingFontSize)
        .member_function("setAdditionalKerning", &ax::Label::setAdditionalKerning)
        .member_function("getAdditionalKerning", &ax::Label::getAdditionalKerning)
        .member_function("getFontAtlas", &ax::Label::getFontAtlas)
        .member_function("getBlendFunc", &ax::Label::getBlendFunc)
        .member_function("setBlendFunc", &ax::Label::setBlendFunc)
        .member_function("removeAllChildrenWithCleanup", &ax::Label::removeAllChildrenWithCleanup)
        .member_function(
            "initWithTTF",
            [](ax::Label* self, ax::_ttfConfig arg0, std::string_view arg1) { return self->initWithTTF(arg0, arg1); },
            [](ax::Label* self, ax::_ttfConfig arg0, std::string_view arg1, ax::TextHAlignment arg2)
            { return self->initWithTTF(arg0, arg1, arg2); },
            [](ax::Label* self, ax::_ttfConfig arg0, std::string_view arg1, ax::TextHAlignment arg2, int arg3)
            { return self->initWithTTF(arg0, arg1, arg2, arg3); },
            [](ax::Label* self, std::string_view arg0, std::string_view arg1, float arg2) { return self->initWithTTF(arg0, arg1, arg2); },
            [](ax::Label* self, std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3)
            { return self->initWithTTF(arg0, arg1, arg2, arg3); },
            [](ax::Label* self, std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3, ax::TextHAlignment arg4)
            { return self->initWithTTF(arg0, arg1, arg2, arg3, arg4); },
            [](ax::Label* self,
               std::string_view arg0,
               std::string_view arg1,
               float arg2,
               ax::Vec2 arg3,
               ax::TextHAlignment arg4,
               ax::TextVAlignment arg5) { return self->initWithTTF(arg0, arg1, arg2, arg3, arg4, arg5); })
        .static_function("create", &ax::Label::create)
        .static_function(
            "createWithSystemFont",
            [](std::string_view arg0, std::string_view arg1, float arg2) { return ax::Label::createWithSystemFont(arg0, arg1, arg2); },
            [](std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3)
            { return ax::Label::createWithSystemFont(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3, ax::TextHAlignment arg4)
            { return ax::Label::createWithSystemFont(arg0, arg1, arg2, arg3, arg4); },
            [](std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3, ax::TextHAlignment arg4, ax::TextVAlignment arg5)
            { return ax::Label::createWithSystemFont(arg0, arg1, arg2, arg3, arg4, arg5); })
        .static_function(
            "createWithTTF",
            [](ax::_ttfConfig arg0, std::string_view arg1) { return ax::Label::createWithTTF(arg0, arg1); },
            [](ax::_ttfConfig arg0, std::string_view arg1, ax::TextHAlignment arg2) { return ax::Label::createWithTTF(arg0, arg1, arg2); },
            [](ax::_ttfConfig arg0, std::string_view arg1, ax::TextHAlignment arg2, int arg3)
            { return ax::Label::createWithTTF(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0, std::string_view arg1, float arg2) { return ax::Label::createWithTTF(arg0, arg1, arg2); },
            [](std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3)
            { return ax::Label::createWithTTF(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3, ax::TextHAlignment arg4)
            { return ax::Label::createWithTTF(arg0, arg1, arg2, arg3, arg4); },
            [](std::string_view arg0, std::string_view arg1, float arg2, ax::Vec2 arg3, ax::TextHAlignment arg4, ax::TextVAlignment arg5)
            { return ax::Label::createWithTTF(arg0, arg1, arg2, arg3, arg4, arg5); })
        .static_function(
            "createWithBMFont",
            [](std::string_view arg0, std::string_view arg1, ax::TextHAlignment arg2, int arg3, ax::Rect arg4, bool arg5)
            { return ax::Label::createWithBMFont(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](std::string_view arg0, std::string_view arg1) { return ax::Label::createWithBMFont(arg0, arg1); },
            [](std::string_view arg0, std::string_view arg1, ax::TextHAlignment arg2)
            { return ax::Label::createWithBMFont(arg0, arg1, arg2); },
            [](std::string_view arg0, std::string_view arg1, ax::TextHAlignment arg2, int arg3)
            { return ax::Label::createWithBMFont(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0, std::string_view arg1, ax::TextHAlignment arg2, int arg3, std::string_view arg4)
            { return ax::Label::createWithBMFont(arg0, arg1, arg2, arg3, arg4); })
        .static_function(
            "createWithCharMap",
            [](ax::Texture2D* arg0, int arg1, int arg2, int arg3) { return ax::Label::createWithCharMap(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0, int arg1, int arg2, int arg3) { return ax::Label::createWithCharMap(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0) { return ax::Label::createWithCharMap(arg0); })
        .auto_wrap_objects(true);
    mod.class_("Label", class_Label);
}
static void js_register_ax_base_LabelAtlas(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::LabelAtlas> class_LabelAtlas(isolate);
    class_LabelAtlas.ctor([]() { return new ax::LabelAtlas(); })
        .template inherit<ax::AtlasNode>()
        .member_function(
            "initWithString",
            [](ax::LabelAtlas* self, std::string_view arg0, std::string_view arg1) { return self->initWithString(arg0, arg1); },
            [](ax::LabelAtlas* self, std::string_view arg0, std::string_view arg1, int arg2, int arg3, int arg4)
            { return self->initWithString(arg0, arg1, arg2, arg3, arg4); },
            [](ax::LabelAtlas* self, std::string_view arg0, ax::Texture2D* arg1, int arg2, int arg3, int arg4)
            { return self->initWithString(arg0, arg1, arg2, arg3, arg4); })
        .member_function("setString", &ax::LabelAtlas::setString)
        .member_function("getString", &ax::LabelAtlas::getString)
        .static_function(
            "_create",
            [](std::string_view arg0, std::string_view arg1) { return ax::LabelAtlas::create(arg0, arg1); },
            [](std::string_view arg0, std::string_view arg1, int arg2, int arg3, int arg4)
            { return ax::LabelAtlas::create(arg0, arg1, arg2, arg3, arg4); },
            [](std::string_view arg0, ax::Texture2D* arg1, int arg2, int arg3, int arg4)
            { return ax::LabelAtlas::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("LabelAtlas", class_LabelAtlas);
}
static void js_register_ax_base_Sprite(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Sprite> class_Sprite(isolate);
    class_Sprite.ctor([]() { return new ax::Sprite(); })
        .template inherit<ax::Node>()
        .member_function("getBatchNode", &ax::Sprite::getBatchNode)
        .member_function("setBatchNode", &ax::Sprite::setBatchNode)
        .member_function(
            "setTexture",
            [](ax::Sprite* self, ax::Texture2D* arg0) { self->setTexture(arg0); },
            [](ax::Sprite* self, std::string_view arg0) { self->setTexture(arg0); })
        .member_function("getTexture", &ax::Sprite::getTexture)
        .member_function(
            "setTextureRect",
            [](ax::Sprite* self, ax::Rect arg0, bool arg1, ax::Vec2 arg2) { self->setTextureRect(arg0, arg1, arg2); },
            [](ax::Sprite* self, ax::Rect arg0) { self->setTextureRect(arg0); })
        .member_function("setVertexRect", &ax::Sprite::setVertexRect)
        .member_function("setCenterRectNormalized", &ax::Sprite::setCenterRectNormalized)
        .member_function("getCenterRectNormalized", &ax::Sprite::getCenterRectNormalized)
        .member_function("setCenterRect", &ax::Sprite::setCenterRect)
        .member_function("getCenterRect", &ax::Sprite::getCenterRect)
        .member_function(
            "setSpriteFrame",
            [](ax::Sprite* self, ax::SpriteFrame* arg0) { self->setSpriteFrame(arg0); },
            [](ax::Sprite* self, std::string_view arg0) { self->setSpriteFrame(arg0); })
        .member_function("isFrameDisplayed", &ax::Sprite::isFrameDisplayed)
        .member_function("getSpriteFrame", &ax::Sprite::getSpriteFrame)
        .member_function("setDisplayFrameWithAnimationName", &ax::Sprite::setDisplayFrameWithAnimationName)
        .member_function("isDirty", &ax::Sprite::isDirty)
        .member_function("setDirty", &ax::Sprite::setDirty)
        .member_function("removeAllChildrenWithCleanup", &ax::Sprite::removeAllChildrenWithCleanup)
        .member_function("isTextureRectRotated", &ax::Sprite::isTextureRectRotated)
        .member_function("getAtlasIndex", &ax::Sprite::getAtlasIndex)
        .member_function("setAtlasIndex", &ax::Sprite::setAtlasIndex)
        .member_function("getTextureRect", &ax::Sprite::getTextureRect)
        .member_function("getTextureAtlas", &ax::Sprite::getTextureAtlas)
        .member_function("setTextureAtlas", &ax::Sprite::setTextureAtlas)
        .member_function("getOffsetPosition", &ax::Sprite::getOffsetPosition)
        .member_function("isFlippedX", &ax::Sprite::isFlippedX)
        .member_function("setFlippedX", &ax::Sprite::setFlippedX)
        .member_function("isFlippedY", &ax::Sprite::isFlippedY)
        .member_function("setFlippedY", &ax::Sprite::setFlippedY)
        .member_function("setStretchEnabled", &ax::Sprite::setStretchEnabled)
        .member_function("isStretchEnabled", &ax::Sprite::isStretchEnabled)
        .member_function("setBlendFunc", &ax::Sprite::setBlendFunc)
        .member_function("getBlendFunc", &ax::Sprite::getBlendFunc)
        .member_function("getResourceType", &ax::Sprite::getResourceType)
        .member_function("getResourceName", &ax::Sprite::getResourceName)
        .member_function(
            "initWithTexture",
            [](ax::Sprite* self, ax::Texture2D* arg0, ax::Rect arg1) { return self->initWithTexture(arg0, arg1); },
            [](ax::Sprite* self, ax::Texture2D* arg0) { return self->initWithTexture(arg0); },
            [](ax::Sprite* self, ax::Texture2D* arg0, ax::Rect arg1, bool arg2) { return self->initWithTexture(arg0, arg1, arg2); })
        .member_function("initWithSpriteFrame", &ax::Sprite::initWithSpriteFrame)
        .member_function("initWithSpriteFrameName", &ax::Sprite::initWithSpriteFrameName)
        .member_function(
            "initWithFile",
            [](ax::Sprite* self, std::string_view arg0, ax::rhi::PixelFormat arg1) { return self->initWithFile(arg0, arg1); },
            [](ax::Sprite* self, std::string_view arg0) { return self->initWithFile(arg0); },
            [](ax::Sprite* self, std::string_view arg0, ax::Rect arg1) { return self->initWithFile(arg0, arg1); })
        .member_function("initWithImageData", &ax::Sprite::initWithImageData)
        .member_function("setVertexLayout", &ax::Sprite::setVertexLayout)
        .member_function("setAutoUpdatePS", &ax::Sprite::setAutoUpdatePS)
        .member_function("setAutoSize", &ax::Sprite::setAutoSize)
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::Sprite::create(arg0); },
            []() { return ax::Sprite::create(); },
            [](std::string_view arg0, ax::rhi::PixelFormat arg1) { return ax::Sprite::create(arg0, arg1); },
            [](ax::PolygonInfo arg0) { return ax::Sprite::create(arg0); },
            [](std::string_view arg0, ax::Rect arg1) { return ax::Sprite::create(arg0, arg1); },
            [](ax::Data arg0, std::string_view arg1) { return ax::Sprite::create(arg0, arg1); })
        .static_function(
            "createWithTexture",
            [](ax::Texture2D* arg0, ax::Rect arg1) { return ax::Sprite::createWithTexture(arg0, arg1); },
            [](ax::Texture2D* arg0, ax::Rect arg1, bool arg2) { return ax::Sprite::createWithTexture(arg0, arg1, arg2); },
            [](ax::Texture2D* arg0) { return ax::Sprite::createWithTexture(arg0); })
        .static_function("createWithSpriteFrame", &ax::Sprite::createWithSpriteFrame)
        .static_function("createWithSpriteFrameName", &ax::Sprite::createWithSpriteFrameName)
        .auto_wrap_objects(true);
    mod.class_("Sprite", class_Sprite);
}
static void js_register_ax_base_Layer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Layer> class_Layer(isolate);
    class_Layer.template inherit<ax::Node>().static_function("create", &ax::Layer::create).auto_wrap_objects(true);
    mod.class_("Layer", class_Layer);
}
static void js_register_ax_base_LayerColor(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::LayerColor> class_LayerColor(isolate);
    class_LayerColor.ctor([]() { return new ax::LayerColor(); })
        .template inherit<ax::Sprite>()
        .member_function("changeWidth", &ax::LayerColor::changeWidth)
        .member_function("changeHeight", &ax::LayerColor::changeHeight)
        .member_function("changeWidthAndHeight", &ax::LayerColor::changeWidthAndHeight)
        .member_function(
            "initWithColor",
            [](ax::LayerColor* self, ax::Color32 arg0) { return self->initWithColor(arg0); },
            [](ax::LayerColor* self, ax::Color32 arg0, float arg1, float arg2) { return self->initWithColor(arg0, arg1, arg2); })
        .static_function(
            "create",
            [](ax::Color32 arg0, float arg1, float arg2) { return ax::LayerColor::create(arg0, arg1, arg2); },
            []() { return ax::LayerColor::create(); },
            [](ax::Color32 arg0) { return ax::LayerColor::create(arg0); })
        .auto_wrap_objects(true);
    mod.class_("LayerColor", class_LayerColor);
}
static void js_register_ax_base_LayerGradient(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::LayerGradient> class_LayerGradient(isolate);
    class_LayerGradient.ctor([]() { return new ax::LayerGradient(); })
        .template inherit<ax::LayerColor>()
        .member_function("setCompressedInterpolation", &ax::LayerGradient::setCompressedInterpolation)
        .member_function("isCompressedInterpolation", &ax::LayerGradient::isCompressedInterpolation)
        .member_function("setStartColor", &ax::LayerGradient::setStartColor)
        .member_function("getStartColor", &ax::LayerGradient::getStartColor)
        .member_function("setEndColor", &ax::LayerGradient::setEndColor)
        .member_function("getEndColor", &ax::LayerGradient::getEndColor)
        .member_function("setStartOpacity", &ax::LayerGradient::setStartOpacity)
        .member_function("getStartOpacity", &ax::LayerGradient::getStartOpacity)
        .member_function("setEndOpacity", &ax::LayerGradient::setEndOpacity)
        .member_function("getEndOpacity", &ax::LayerGradient::getEndOpacity)
        .member_function("setVector", &ax::LayerGradient::setVector)
        .member_function("getVector", &ax::LayerGradient::getVector)
        .member_function(
            "initWithColor",
            [](ax::LayerGradient* self, ax::Color32 arg0, ax::Color32 arg1, ax::Vec2 arg2)
            { return self->initWithColor(arg0, arg1, arg2); },
            [](ax::LayerGradient* self, ax::Color32 arg0, ax::Color32 arg1) { return self->initWithColor(arg0, arg1); })
        .static_function(
            "create",
            [](ax::Color32 arg0, ax::Color32 arg1) { return ax::LayerGradient::create(arg0, arg1); },
            []() { return ax::LayerGradient::create(); },
            [](ax::Color32 arg0, ax::Color32 arg1, ax::Vec2 arg2) { return ax::LayerGradient::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("LayerGradient", class_LayerGradient);
}
static void js_register_ax_base_LayerRadialGradient(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::LayerRadialGradient> class_LayerRadialGradient(isolate);
    class_LayerRadialGradient.ctor([]() { return new ax::LayerRadialGradient(); })
        .template inherit<ax::Node>()
        .member_function("setStartOpacity", &ax::LayerRadialGradient::setStartOpacity)
        .member_function("getStartOpacity", &ax::LayerRadialGradient::getStartOpacity)
        .member_function("setEndOpacity", &ax::LayerRadialGradient::setEndOpacity)
        .member_function("getEndOpacity", &ax::LayerRadialGradient::getEndOpacity)
        .member_function("setRadius", &ax::LayerRadialGradient::setRadius)
        .member_function("getRadius", &ax::LayerRadialGradient::getRadius)
        .member_function("setCenter", &ax::LayerRadialGradient::setCenter)
        .member_function("getCenter", &ax::LayerRadialGradient::getCenter)
        .member_function("setExpand", &ax::LayerRadialGradient::setExpand)
        .member_function("getExpand", &ax::LayerRadialGradient::getExpand)
        .member_function("setStartColor", &ax::LayerRadialGradient::setStartColor)
        .member_function("getStartColor", &ax::LayerRadialGradient::getStartColor)
        .member_function("setEndColor", &ax::LayerRadialGradient::setEndColor)
        .member_function("getEndColor", &ax::LayerRadialGradient::getEndColor)
        .member_function("setBlendFunc", &ax::LayerRadialGradient::setBlendFunc)
        .member_function("getBlendFunc", &ax::LayerRadialGradient::getBlendFunc)
        .member_function("initWithColor", &ax::LayerRadialGradient::initWithColor)
        .static_function(
            "create",
            []() { return ax::LayerRadialGradient::create(); },
            [](ax::Color32 arg0, ax::Color32 arg1, float arg2, ax::Vec2 arg3, float arg4)
            { return ax::LayerRadialGradient::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("LayerRadialGradient", class_LayerRadialGradient);
}
static void js_register_ax_base_LayerMultiplex(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::LayerMultiplex> class_LayerMultiplex(isolate);
    class_LayerMultiplex.ctor([]() { return new ax::LayerMultiplex(); })
        .template inherit<ax::Node>()
        .member_function("addLayer", &ax::LayerMultiplex::addLayer)
        .member_function(
            "switchTo",
            [](ax::LayerMultiplex* self, int arg0, bool arg1) { self->switchTo(arg0, arg1); },
            [](ax::LayerMultiplex* self, int arg0) { self->switchTo(arg0); })
        .member_function("switchToAndReleaseMe", &ax::LayerMultiplex::switchToAndReleaseMe)
        .member_function("initWithArray", &ax::LayerMultiplex::initWithArray)
        .auto_wrap_objects(true);
    mod.class_("LayerMultiplex", class_LayerMultiplex);
}
static void js_register_ax_base_MenuItem(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MenuItem> class_MenuItem(isolate);
    class_MenuItem.ctor([]() { return new ax::MenuItem(); })
        .template inherit<ax::Node>()
        .member_function("rect", &ax::MenuItem::rect)
        .member_function("activate", &ax::MenuItem::activate)
        .member_function("selected", &ax::MenuItem::selected)
        .member_function("unselected", &ax::MenuItem::unselected)
        .member_function("isEnabled", &ax::MenuItem::isEnabled)
        .member_function("setEnabled", &ax::MenuItem::setEnabled)
        .member_function("isSelected", &ax::MenuItem::isSelected)
        .member_function("setCallback", &ax::MenuItem::setCallback)
        .member_function(
            "setCallbackSelected",
            [](ax::MenuItem* self) { self->setCallbackSelected(); },
            [](ax::MenuItem* self, std::function<void(ax::Object*)> arg0) { self->setCallbackSelected(arg0); },
            [](ax::MenuItem* self, std::function<void(ax::Object*)> arg0, std::function<void(ax::Object*)> arg1)
            { self->setCallbackSelected(arg0, arg1); })
        .member_function("initWithCallback", &ax::MenuItem::initWithCallback)
        .auto_wrap_objects(true);
    mod.class_("MenuItem", class_MenuItem);
}
static void js_register_ax_base_MenuItemLabel(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MenuItemLabel> class_MenuItemLabel(isolate);
    class_MenuItemLabel.ctor([]() { return new ax::MenuItemLabel(); })
        .template inherit<ax::MenuItem>()
        .member_function("setString", &ax::MenuItemLabel::setString)
        .member_function("getString", &ax::MenuItemLabel::getString)
        .member_function("getDisabledColor", &ax::MenuItemLabel::getDisabledColor)
        .member_function("setDisabledColor", &ax::MenuItemLabel::setDisabledColor)
        .member_function("getLabel", &ax::MenuItemLabel::getLabel)
        .member_function("setLabel", &ax::MenuItemLabel::setLabel)
        .member_function("initWithLabel", &ax::MenuItemLabel::initWithLabel)
        .auto_wrap_objects(true);
    mod.class_("MenuItemLabel", class_MenuItemLabel);
}
static void js_register_ax_base_MenuItemAtlasFont(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MenuItemAtlasFont> class_MenuItemAtlasFont(isolate);
    class_MenuItemAtlasFont.ctor([]() { return new ax::MenuItemAtlasFont(); })
        .template inherit<ax::MenuItemLabel>()
        .member_function("initWithString", &ax::MenuItemAtlasFont::initWithString)
        .auto_wrap_objects(true);
    mod.class_("MenuItemAtlasFont", class_MenuItemAtlasFont);
}
static void js_register_ax_base_MenuItemFont(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MenuItemFont> class_MenuItemFont(isolate);
    class_MenuItemFont.ctor([]() { return new ax::MenuItemFont(); })
        .template inherit<ax::MenuItemLabel>()
        .member_function("setFontSizeObj", &ax::MenuItemFont::setFontSizeObj)
        .member_function("getFontSizeObj", &ax::MenuItemFont::getFontSizeObj)
        .member_function("setFontNameObj", &ax::MenuItemFont::setFontNameObj)
        .member_function("getFontNameObj", &ax::MenuItemFont::getFontNameObj)
        .member_function("initWithString", &ax::MenuItemFont::initWithString)
        .static_function("setFontSize", &ax::MenuItemFont::setFontSize)
        .static_function("getFontSize", &ax::MenuItemFont::getFontSize)
        .static_function("setFontName", &ax::MenuItemFont::setFontName)
        .static_function("getFontName", &ax::MenuItemFont::getFontName)
        .auto_wrap_objects(true);
    mod.class_("MenuItemFont", class_MenuItemFont);
}
static void js_register_ax_base_MenuItemSprite(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MenuItemSprite> class_MenuItemSprite(isolate);
    class_MenuItemSprite.ctor([]() { return new ax::MenuItemSprite(); })
        .template inherit<ax::MenuItem>()
        .member_function("getNormalImage", &ax::MenuItemSprite::getNormalImage)
        .member_function("setNormalImage", &ax::MenuItemSprite::setNormalImage)
        .member_function("getSelectedImage", &ax::MenuItemSprite::getSelectedImage)
        .member_function("setSelectedImage", &ax::MenuItemSprite::setSelectedImage)
        .member_function("getDisabledImage", &ax::MenuItemSprite::getDisabledImage)
        .member_function("setDisabledImage", &ax::MenuItemSprite::setDisabledImage)
        .member_function("selected", &ax::MenuItemSprite::selected)
        .member_function("unselected", &ax::MenuItemSprite::unselected)
        .member_function("setEnabled", &ax::MenuItemSprite::setEnabled)
        .member_function("initWithNormalSprite", &ax::MenuItemSprite::initWithNormalSprite)
        .auto_wrap_objects(true);
    mod.class_("MenuItemSprite", class_MenuItemSprite);
}
static void js_register_ax_base_MenuItemImage(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MenuItemImage> class_MenuItemImage(isolate);
    class_MenuItemImage.ctor([]() { return new ax::MenuItemImage(); })
        .template inherit<ax::MenuItemSprite>()
        .member_function("setNormalSpriteFrame", &ax::MenuItemImage::setNormalSpriteFrame)
        .member_function("setSelectedSpriteFrame", &ax::MenuItemImage::setSelectedSpriteFrame)
        .member_function("setDisabledSpriteFrame", &ax::MenuItemImage::setDisabledSpriteFrame)
        .member_function("init", &ax::MenuItemImage::init)
        .member_function("initWithNormalImage", &ax::MenuItemImage::initWithNormalImage)
        .auto_wrap_objects(true);
    mod.class_("MenuItemImage", class_MenuItemImage);
}
static void js_register_ax_base_MenuItemToggle(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MenuItemToggle> class_MenuItemToggle(isolate);
    class_MenuItemToggle.ctor([]() { return new ax::MenuItemToggle(); })
        .template inherit<ax::MenuItem>()
        .member_function("addSubItem", &ax::MenuItemToggle::addSubItem)
        .member_function("getSelectedItem", &ax::MenuItemToggle::getSelectedItem)
        .member_function("getSelectedIndex", &ax::MenuItemToggle::getSelectedIndex)
        .member_function("setSelectedIndex", &ax::MenuItemToggle::setSelectedIndex)
        .member_function("setSubItems", &ax::MenuItemToggle::setSubItems)
        .member_function("initWithItem", &ax::MenuItemToggle::initWithItem)
        .auto_wrap_objects(true);
    mod.class_("MenuItemToggle", class_MenuItemToggle);
}
static void js_register_ax_base_Menu(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Menu> class_Menu(isolate);
    class_Menu.ctor([]() { return new ax::Menu(); })
        .template inherit<ax::Node>()
        .member_function("alignItemsVertically", &ax::Menu::alignItemsVertically)
        .member_function("alignItemsVerticallyWithPadding", &ax::Menu::alignItemsVerticallyWithPadding)
        .member_function("alignItemsHorizontally", &ax::Menu::alignItemsHorizontally)
        .member_function("alignItemsHorizontallyWithPadding", &ax::Menu::alignItemsHorizontallyWithPadding)
        .member_function("isEnabled", &ax::Menu::isEnabled)
        .member_function("setEnabled", &ax::Menu::setEnabled)
        .member_function("initWithArray", &ax::Menu::initWithArray)
        .auto_wrap_objects(true);
    mod.class_("Menu", class_Menu);
}
static void js_register_ax_base_MotionStreak(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MotionStreak> class_MotionStreak(isolate);
    class_MotionStreak.ctor([]() { return new ax::MotionStreak(); })
        .template inherit<ax::Node>()
        .member_function("getTexture", &ax::MotionStreak::getTexture)
        .member_function("setTexture", &ax::MotionStreak::setTexture)
        .member_function("setBlendFunc", &ax::MotionStreak::setBlendFunc)
        .member_function("getBlendFunc", &ax::MotionStreak::getBlendFunc)
        .member_function("tintWithColor", &ax::MotionStreak::tintWithColor)
        .member_function("reset", &ax::MotionStreak::reset)
        .member_function("isFastMode", &ax::MotionStreak::isFastMode)
        .member_function("setFastMode", &ax::MotionStreak::setFastMode)
        .member_function("getStroke", &ax::MotionStreak::getStroke)
        .member_function("setStroke", &ax::MotionStreak::setStroke)
        .member_function("isStartingPositionInitialized", &ax::MotionStreak::isStartingPositionInitialized)
        .member_function("setStartingPositionInitialized", &ax::MotionStreak::setStartingPositionInitialized)
        .member_function(
            "initWithFade",
            [](ax::MotionStreak* self, float arg0, float arg1, float arg2, ax::Color32 arg3, ax::Texture2D* arg4)
            { return self->initWithFade(arg0, arg1, arg2, arg3, arg4); },
            [](ax::MotionStreak* self, float arg0, float arg1, float arg2, ax::Color32 arg3, std::string_view arg4)
            { return self->initWithFade(arg0, arg1, arg2, arg3, arg4); })
        .static_function(
            "create",
            [](float arg0, float arg1, float arg2, ax::Color32 arg3, ax::Texture2D* arg4)
            { return ax::MotionStreak::create(arg0, arg1, arg2, arg3, arg4); },
            [](float arg0, float arg1, float arg2, ax::Color32 arg3, std::string_view arg4)
            { return ax::MotionStreak::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("MotionStreak", class_MotionStreak);
}
static void js_register_ax_base_NodeGrid(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::NodeGrid> class_NodeGrid(isolate);
    class_NodeGrid.ctor([]() { return new ax::NodeGrid(); })
        .template inherit<ax::Node>()
        .member_function(
            "getGrid", [](ax::NodeGrid* self) { return self->getGrid(); }, [](ax::NodeGrid* self) { return self->getGrid(); })
        .member_function("setGrid", &ax::NodeGrid::setGrid)
        .member_function("setTarget", &ax::NodeGrid::setTarget)
        .member_function("setGridRect", &ax::NodeGrid::setGridRect)
        .member_function("getGridRect", &ax::NodeGrid::getGridRect)
        .static_function(
            "create", [](ax::Rect arg0) { return ax::NodeGrid::create(arg0); }, []() { return ax::NodeGrid::create(); })
        .auto_wrap_objects(true);
    mod.class_("NodeGrid", class_NodeGrid);
}
static void js_register_ax_base_ParticleBatchNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleBatchNode> class_ParticleBatchNode(isolate);
    class_ParticleBatchNode.ctor([]() { return new ax::ParticleBatchNode(); })
        .template inherit<ax::Node>()
        .member_function("insertChild", &ax::ParticleBatchNode::insertChild)
        .member_function("removeChildAtIndex", &ax::ParticleBatchNode::removeChildAtIndex)
        .member_function("removeAllChildrenWithCleanup", &ax::ParticleBatchNode::removeAllChildrenWithCleanup)
        .member_function("disableParticle", &ax::ParticleBatchNode::disableParticle)
        .member_function("getTextureAtlas", &ax::ParticleBatchNode::getTextureAtlas)
        .member_function("setTextureAtlas", &ax::ParticleBatchNode::setTextureAtlas)
        .member_function("getTexture", &ax::ParticleBatchNode::getTexture)
        .member_function("setTexture", &ax::ParticleBatchNode::setTexture)
        .member_function("setBlendFunc", &ax::ParticleBatchNode::setBlendFunc)
        .member_function("getBlendFunc", &ax::ParticleBatchNode::getBlendFunc)
        .member_function("initWithTexture", &ax::ParticleBatchNode::initWithTexture)
        .member_function("initWithFile", &ax::ParticleBatchNode::initWithFile)
        .static_function(
            "createWithTexture",
            [](ax::Texture2D* arg0) { return ax::ParticleBatchNode::createWithTexture(arg0); },
            [](ax::Texture2D* arg0, int arg1) { return ax::ParticleBatchNode::createWithTexture(arg0, arg1); })
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::ParticleBatchNode::create(arg0); },
            [](std::string_view arg0, int arg1) { return ax::ParticleBatchNode::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("ParticleBatchNode", class_ParticleBatchNode);
}
static void js_register_ax_base_SpriteSheet(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SpriteSheet> class_SpriteSheet(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_SpriteSheet.auto_wrap_objects(true);
    mod.class_("SpriteSheet", class_SpriteSheet);
}
static void js_register_ax_base_SpriteFrameCache(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SpriteFrameCache> class_SpriteFrameCache(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_SpriteFrameCache.member_function("init", &ax::SpriteFrameCache::init)
        .member_function(
            "addSpriteFrames",
            [](ax::SpriteFrameCache* self, std::string_view arg0, std::string_view arg1) { self->addSpriteFramesWithFile(arg0, arg1); },
            [](ax::SpriteFrameCache* self, std::string_view arg0, std::string_view arg1, unsigned int arg2)
            { self->addSpriteFramesWithFile(arg0, arg1, arg2); },
            [](ax::SpriteFrameCache* self, std::string_view arg0) { self->addSpriteFramesWithFile(arg0); },
            [](ax::SpriteFrameCache* self, std::string_view arg0, unsigned int arg1) { self->addSpriteFramesWithFile(arg0, arg1); },
            [](ax::SpriteFrameCache* self, std::string_view arg0, ax::Texture2D* arg1) { self->addSpriteFramesWithFile(arg0, arg1); },
            [](ax::SpriteFrameCache* self, std::string_view arg0, ax::Texture2D* arg1, unsigned int arg2)
            { self->addSpriteFramesWithFile(arg0, arg1, arg2); })
        .member_function("addSpriteFrame", &ax::SpriteFrameCache::addSpriteFrame)
        .member_function("isSpriteFramesWithFileLoaded", &ax::SpriteFrameCache::isSpriteFramesWithFileLoaded)
        .member_function("removeSpriteFrames", &ax::SpriteFrameCache::removeSpriteFrames)
        .member_function("removeUnusedSpriteFrames", &ax::SpriteFrameCache::removeUnusedSpriteFrames)
        .member_function("removeUnusedSpriteSheets", &ax::SpriteFrameCache::removeUnusedSpriteSheets)
        .member_function("removeSpriteFrameByName", &ax::SpriteFrameCache::removeSpriteFrameByName)
        .member_function("removeSpriteFramesFromFile", &ax::SpriteFrameCache::removeSpriteFramesFromFile)
        .member_function("removeSpriteFramesFromFileContent", &ax::SpriteFrameCache::removeSpriteFramesFromFileContent)
        .member_function("removeSpriteFramesFromTexture", &ax::SpriteFrameCache::removeSpriteFramesFromTexture)
        .member_function("getSpriteFrame", &ax::SpriteFrameCache::getSpriteFrameByName)
        .member_function("reloadTexture", &ax::SpriteFrameCache::reloadTexture)
        .member_function("getSpriteFrameName", &ax::SpriteFrameCache::getSpriteFrameName)
        .member_function("addSpriteFrameCapInset", &ax::SpriteFrameCache::addSpriteFrameCapInset)
        .member_function("deregisterSpriteSheetLoader", &ax::SpriteFrameCache::deregisterSpriteSheetLoader)
        .member_function("getSpriteSheetLoader", &ax::SpriteFrameCache::getSpriteSheetLoader)
        .static_function("getInstance", &ax::SpriteFrameCache::getInstance)
        .static_function("destroyInstance", &ax::SpriteFrameCache::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("SpriteFrameCache", class_SpriteFrameCache);
}
static void js_register_ax_base_ParticleData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleData> class_ParticleData(isolate);
    class_ParticleData.ctor([]() { return new ax::ParticleData(); })
        .member_function("init", &ax::ParticleData::init)
        .member_function("release", &ax::ParticleData::release)
        .member_function("getMaxCount", &ax::ParticleData::getMaxCount)
        .member_function("copyParticle", &ax::ParticleData::copyParticle)
        .auto_wrap_objects(true);
    mod.class_("ParticleData", class_ParticleData);
}
static void js_register_ax_base_ParticleEmissionMaskCache(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleEmissionMaskCache> class_ParticleEmissionMaskCache(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_ParticleEmissionMaskCache
        .member_function(
            "bakeEmissionMask",
            [](ax::ParticleEmissionMaskCache* self, std::string_view arg0, ax::Image* arg1) { self->bakeEmissionMask(arg0, arg1); },
            [](ax::ParticleEmissionMaskCache* self, std::string_view arg0, ax::Image* arg1, float arg2)
            { self->bakeEmissionMask(arg0, arg1, arg2); },
            [](ax::ParticleEmissionMaskCache* self, std::string_view arg0, ax::Image* arg1, float arg2, bool arg3)
            { self->bakeEmissionMask(arg0, arg1, arg2, arg3); },
            [](ax::ParticleEmissionMaskCache* self, std::string_view arg0, ax::Image* arg1, float arg2, bool arg3, int arg4)
            { self->bakeEmissionMask(arg0, arg1, arg2, arg3, arg4); },
            [](ax::ParticleEmissionMaskCache* self, std::string_view arg0, std::string_view arg1) { self->bakeEmissionMask(arg0, arg1); },
            [](ax::ParticleEmissionMaskCache* self, std::string_view arg0, std::string_view arg1, float arg2)
            { self->bakeEmissionMask(arg0, arg1, arg2); },
            [](ax::ParticleEmissionMaskCache* self, std::string_view arg0, std::string_view arg1, float arg2, bool arg3)
            { self->bakeEmissionMask(arg0, arg1, arg2, arg3); },
            [](ax::ParticleEmissionMaskCache* self, std::string_view arg0, std::string_view arg1, float arg2, bool arg3, int arg4)
            { self->bakeEmissionMask(arg0, arg1, arg2, arg3, arg4); })
        // .member_function(
        //     "getEmissionMask",
        //     [](ax::ParticleEmissionMaskCache* self, std::string_view arg0) { return self->getEmissionMask(arg0); },
        //     [](ax::ParticleEmissionMaskCache* self, unsigned int arg0) { return self->getEmissionMask(arg0); })
        .member_function("removeMask", &ax::ParticleEmissionMaskCache::removeMask)
        .member_function("removeAllMasks", &ax::ParticleEmissionMaskCache::removeAllMasks)
        .static_function("getInstance", &ax::ParticleEmissionMaskCache::getInstance)
        .auto_wrap_objects(true);
    mod.class_("ParticleEmissionMaskCache", class_ParticleEmissionMaskCache);
}
static void js_register_ax_base_ParticleSystem(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleSystem> class_ParticleSystem(isolate);
    class_ParticleSystem.ctor([]() { return new ax::ParticleSystem(); })
        .template inherit<ax::Node>()
        .member_function(
            "addParticles",
            [](ax::ParticleSystem* self, int arg0) { self->addParticles(arg0); },
            [](ax::ParticleSystem* self, int arg0, int arg1) { self->addParticles(arg0, arg1); },
            [](ax::ParticleSystem* self, int arg0, int arg1, int arg2) { self->addParticles(arg0, arg1, arg2); })
        .member_function("stopSystem", &ax::ParticleSystem::stopSystem)
        .member_function("resetSystem", &ax::ParticleSystem::resetSystem)
        .member_function("isFull", &ax::ParticleSystem::isFull)
        .member_function("updateParticleQuads", &ax::ParticleSystem::updateParticleQuads)
        .member_function("postStep", &ax::ParticleSystem::postStep)
        .member_function("updateWithNoTime", &ax::ParticleSystem::updateWithNoTime)
        .member_function("isAutoRemoveOnFinish", &ax::ParticleSystem::isAutoRemoveOnFinish)
        .member_function("setAutoRemoveOnFinish", &ax::ParticleSystem::setAutoRemoveOnFinish)
        .member_function("getGravity", &ax::ParticleSystem::getGravity)
        .member_function("setGravity", &ax::ParticleSystem::setGravity)
        .member_function("getSpeed", &ax::ParticleSystem::getSpeed)
        .member_function("setSpeed", &ax::ParticleSystem::setSpeed)
        .member_function("getSpeedVar", &ax::ParticleSystem::getSpeedVar)
        .member_function("setSpeedVar", &ax::ParticleSystem::setSpeedVar)
        .member_function("getTangentialAccel", &ax::ParticleSystem::getTangentialAccel)
        .member_function("setTangentialAccel", &ax::ParticleSystem::setTangentialAccel)
        .member_function("getTangentialAccelVar", &ax::ParticleSystem::getTangentialAccelVar)
        .member_function("setTangentialAccelVar", &ax::ParticleSystem::setTangentialAccelVar)
        .member_function("getRadialAccel", &ax::ParticleSystem::getRadialAccel)
        .member_function("setRadialAccel", &ax::ParticleSystem::setRadialAccel)
        .member_function("getRadialAccelVar", &ax::ParticleSystem::getRadialAccelVar)
        .member_function("setRadialAccelVar", &ax::ParticleSystem::setRadialAccelVar)
        .member_function("getRotationIsDir", &ax::ParticleSystem::getRotationIsDir)
        .member_function("setRotationIsDir", &ax::ParticleSystem::setRotationIsDir)
        .member_function("getStartRadius", &ax::ParticleSystem::getStartRadius)
        .member_function("setStartRadius", &ax::ParticleSystem::setStartRadius)
        .member_function("getStartRadiusVar", &ax::ParticleSystem::getStartRadiusVar)
        .member_function("setStartRadiusVar", &ax::ParticleSystem::setStartRadiusVar)
        .member_function("getEndRadius", &ax::ParticleSystem::getEndRadius)
        .member_function("setEndRadius", &ax::ParticleSystem::setEndRadius)
        .member_function("getEndRadiusVar", &ax::ParticleSystem::getEndRadiusVar)
        .member_function("setEndRadiusVar", &ax::ParticleSystem::setEndRadiusVar)
        .member_function("getRotatePerSecond", &ax::ParticleSystem::getRotatePerSecond)
        .member_function("setRotatePerSecond", &ax::ParticleSystem::setRotatePerSecond)
        .member_function("getRotatePerSecondVar", &ax::ParticleSystem::getRotatePerSecondVar)
        .member_function("setRotatePerSecondVar", &ax::ParticleSystem::setRotatePerSecondVar)
        .member_function("isActive", &ax::ParticleSystem::isActive)
        .member_function("isBlendAdditive", &ax::ParticleSystem::isBlendAdditive)
        .member_function("setBlendAdditive", &ax::ParticleSystem::setBlendAdditive)
        .member_function("getBatchNode", &ax::ParticleSystem::getBatchNode)
        .member_function("setBatchNode", &ax::ParticleSystem::setBatchNode)
        .member_function("getAtlasIndex", &ax::ParticleSystem::getAtlasIndex)
        .member_function("setAtlasIndex", &ax::ParticleSystem::setAtlasIndex)
        .member_function("getParticleCount", &ax::ParticleSystem::getParticleCount)
        .member_function("getDuration", &ax::ParticleSystem::getDuration)
        .member_function("setDuration", &ax::ParticleSystem::setDuration)
        .member_function("getSourcePosition", &ax::ParticleSystem::getSourcePosition)
        .member_function("setSourcePosition", &ax::ParticleSystem::setSourcePosition)
        .member_function("getPosVar", &ax::ParticleSystem::getPosVar)
        .member_function("setPosVar", &ax::ParticleSystem::setPosVar)
        .member_function("getLife", &ax::ParticleSystem::getLife)
        .member_function("setLife", &ax::ParticleSystem::setLife)
        .member_function("getLifeVar", &ax::ParticleSystem::getLifeVar)
        .member_function("setLifeVar", &ax::ParticleSystem::setLifeVar)
        .member_function("getAngle", &ax::ParticleSystem::getAngle)
        .member_function("setAngle", &ax::ParticleSystem::setAngle)
        .member_function("getAngleVar", &ax::ParticleSystem::getAngleVar)
        .member_function("setAngleVar", &ax::ParticleSystem::setAngleVar)
        .member_function("getEmitterMode", &ax::ParticleSystem::getEmitterMode)
        .member_function("setEmitterMode", &ax::ParticleSystem::setEmitterMode)
        .member_function("getStartSize", &ax::ParticleSystem::getStartSize)
        .member_function("setStartSize", &ax::ParticleSystem::setStartSize)
        .member_function("getStartSizeVar", &ax::ParticleSystem::getStartSizeVar)
        .member_function("setStartSizeVar", &ax::ParticleSystem::setStartSizeVar)
        .member_function("getEndSize", &ax::ParticleSystem::getEndSize)
        .member_function("setEndSize", &ax::ParticleSystem::setEndSize)
        .member_function("getEndSizeVar", &ax::ParticleSystem::getEndSizeVar)
        .member_function("setEndSizeVar", &ax::ParticleSystem::setEndSizeVar)
        .member_function("getStartColor", &ax::ParticleSystem::getStartColor)
        .member_function("setStartColor", &ax::ParticleSystem::setStartColor)
        .member_function("getStartColorVar", &ax::ParticleSystem::getStartColorVar)
        .member_function("setStartColorVar", &ax::ParticleSystem::setStartColorVar)
        .member_function("getEndColor", &ax::ParticleSystem::getEndColor)
        .member_function("setEndColor", &ax::ParticleSystem::setEndColor)
        .member_function("getEndColorVar", &ax::ParticleSystem::getEndColorVar)
        .member_function("setEndColorVar", &ax::ParticleSystem::setEndColorVar)
        .member_function("useHSV", &ax::ParticleSystem::useHSV)
        .member_function("isHSV", &ax::ParticleSystem::isHSV)
        .member_function("getHue", &ax::ParticleSystem::getHue)
        .member_function("setHue", &ax::ParticleSystem::setHue)
        .member_function("getHueVar", &ax::ParticleSystem::getHueVar)
        .member_function("setHueVar", &ax::ParticleSystem::setHueVar)
        .member_function("getHSV", &ax::ParticleSystem::getHSV)
        .member_function("setHSV", &ax::ParticleSystem::setHSV)
        .member_function("getHSVVar", &ax::ParticleSystem::getHSVVar)
        .member_function("setHSVVar", &ax::ParticleSystem::setHSVVar)
        .member_function("getStartSpin", &ax::ParticleSystem::getStartSpin)
        .member_function("setStartSpin", &ax::ParticleSystem::setStartSpin)
        .member_function("getStartSpinVar", &ax::ParticleSystem::getStartSpinVar)
        .member_function("setStartSpinVar", &ax::ParticleSystem::setStartSpinVar)
        .member_function("getEndSpin", &ax::ParticleSystem::getEndSpin)
        .member_function("setEndSpin", &ax::ParticleSystem::setEndSpin)
        .member_function("getEndSpinVar", &ax::ParticleSystem::getEndSpinVar)
        .member_function("setEndSpinVar", &ax::ParticleSystem::setEndSpinVar)
        .member_function("getSpawnAngle", &ax::ParticleSystem::getSpawnAngle)
        .member_function("setSpawnAngle", &ax::ParticleSystem::setSpawnAngle)
        .member_function("getSpawnAngleVar", &ax::ParticleSystem::getSpawnAngleVar)
        .member_function("setSpawnAngleVar", &ax::ParticleSystem::setSpawnAngleVar)
        .member_function("getSpawnFadeIn", &ax::ParticleSystem::getSpawnFadeIn)
        .member_function("setSpawnFadeIn", &ax::ParticleSystem::setSpawnFadeIn)
        .member_function("getSpawnFadeInVar", &ax::ParticleSystem::getSpawnFadeInVar)
        .member_function("setSpawnFadeInVar", &ax::ParticleSystem::setSpawnFadeInVar)
        .member_function("getSpawnScaleIn", &ax::ParticleSystem::getSpawnScaleIn)
        .member_function("setSpawnScaleIn", &ax::ParticleSystem::setSpawnScaleIn)
        .member_function("getSpawnScaleInVar", &ax::ParticleSystem::getSpawnScaleInVar)
        .member_function("setSpawnScaleInVar", &ax::ParticleSystem::setSpawnScaleInVar)
        .member_function("getEmissionRate", &ax::ParticleSystem::getEmissionRate)
        .member_function("setEmissionRate", &ax::ParticleSystem::setEmissionRate)
        .member_function("getTotalParticles", &ax::ParticleSystem::getTotalParticles)
        .member_function("setTotalParticles", &ax::ParticleSystem::setTotalParticles)
        .member_function("setLifeAnimation", &ax::ParticleSystem::setLifeAnimation)
        .member_function("setEmitterAnimation", &ax::ParticleSystem::setEmitterAnimation)
        .member_function("setLoopAnimation", &ax::ParticleSystem::setLoopAnimation)
        .member_function("isLifeAnimated", &ax::ParticleSystem::isLifeAnimated)
        .member_function("isEmitterAnimated", &ax::ParticleSystem::isEmitterAnimated)
        .member_function("isLoopAnimated", &ax::ParticleSystem::isLoopAnimated)
        .member_function("getTotalAnimationIndices", &ax::ParticleSystem::getTotalAnimationIndices)
        .member_function("setAnimationReverse", &ax::ParticleSystem::setAnimationReverse)
        .member_function("isAnimationReversed", &ax::ParticleSystem::isAnimationReversed)
        .member_function("resetAnimationIndices", &ax::ParticleSystem::resetAnimationIndices)
        .member_function("resetAnimationDescriptors", &ax::ParticleSystem::resetAnimationDescriptors)
        .member_function("setMultiAnimationRandomSpecific", &ax::ParticleSystem::setMultiAnimationRandomSpecific)
        .member_function("setMultiAnimationRandom", &ax::ParticleSystem::setMultiAnimationRandom)
        .member_function(
            "setAnimationIndicesAtlas",
            [](ax::ParticleSystem* self, unsigned int arg0) { self->setAnimationIndicesAtlas(arg0); },
            [](ax::ParticleSystem* self, unsigned int arg0, ax::ParticleSystem::TexAnimDir arg1)
            { self->setAnimationIndicesAtlas(arg0, arg1); },
            [](ax::ParticleSystem* self) { self->setAnimationIndicesAtlas(); })
        .member_function(
            "addAnimationIndex",
            [](ax::ParticleSystem* self, unsigned short arg0, std::string_view arg1) { return self->addAnimationIndex(arg0, arg1); },
            [](ax::ParticleSystem* self, std::string_view arg0) { return self->addAnimationIndex(arg0); },
            [](ax::ParticleSystem* self, ax::SpriteFrame* arg0) { return self->addAnimationIndex(arg0); },
            [](ax::ParticleSystem* self, unsigned short arg0, ax::SpriteFrame* arg1) { return self->addAnimationIndex(arg0, arg1); },
            [](ax::ParticleSystem* self, unsigned short arg0, ax::Rect arg1) { return self->addAnimationIndex(arg0, arg1); },
            [](ax::ParticleSystem* self, unsigned short arg0, ax::Rect arg1, bool arg2)
            { return self->addAnimationIndex(arg0, arg1, arg2); })
        .member_function("setRectForUndefinedIndices", &ax::ParticleSystem::setRectForUndefinedIndices)
        .member_function(
            "setAnimationDesc",
            [](ax::ParticleSystem* self, std::vector<unsigned short> arg0) { self->setAnimationDesc(arg0); },
            [](ax::ParticleSystem* self, std::vector<unsigned short> arg0, bool arg1) { self->setAnimationDesc(arg0, arg1); },
            [](ax::ParticleSystem* self, unsigned short arg0, float arg1, float arg2, std::vector<unsigned short> arg3)
            { self->setAnimationDesc(arg0, arg1, arg2, arg3); },
            [](ax::ParticleSystem* self, unsigned short arg0, float arg1, float arg2, std::vector<unsigned short> arg3, bool arg4)
            { self->setAnimationDesc(arg0, arg1, arg2, arg3, arg4); })
        .member_function("setAnimationSpeedTimescaleIndependent", &ax::ParticleSystem::setAnimationSpeedTimescaleIndependent)
        .member_function("isAnimationSpeedTimescaleIndependent", &ax::ParticleSystem::isAnimationSpeedTimescaleIndependent)
        .member_function("setEmissionShapes", &ax::ParticleSystem::setEmissionShapes)
        .member_function("isEmissionShapes", &ax::ParticleSystem::isEmissionShapes)
        .member_function("resetEmissionShapes", &ax::ParticleSystem::resetEmissionShapes)
        .member_function("addEmissionShape", &ax::ParticleSystem::addEmissionShape)
        .member_function("setEmissionShape", &ax::ParticleSystem::setEmissionShape)
        .member_function("getPositionType", &ax::ParticleSystem::getPositionType)
        .member_function("setPositionType", &ax::ParticleSystem::setPositionType)
        .member_function(
            "simulate",
            [](ax::ParticleSystem* self) { self->simulate(); },
            [](ax::ParticleSystem* self, float arg0) { self->simulate(arg0); },
            [](ax::ParticleSystem* self, float arg0, float arg1) { self->simulate(arg0, arg1); })
        .member_function(
            "resimulate",
            [](ax::ParticleSystem* self) { self->resimulate(); },
            [](ax::ParticleSystem* self, float arg0) { self->resimulate(arg0); },
            [](ax::ParticleSystem* self, float arg0, float arg1) { self->resimulate(arg0, arg1); })
        .member_function("getTexture", &ax::ParticleSystem::getTexture)
        .member_function("setTexture", &ax::ParticleSystem::setTexture)
        .member_function("setBlendFunc", &ax::ParticleSystem::setBlendFunc)
        .member_function("getBlendFunc", &ax::ParticleSystem::getBlendFunc)
        .member_function("getResourceFile", &ax::ParticleSystem::getResourceFile)
        .member_function("start", &ax::ParticleSystem::start)
        .member_function("stop", &ax::ParticleSystem::stop)
        .member_function("setSourcePositionCompatible", &ax::ParticleSystem::setSourcePositionCompatible)
        .member_function("isSourcePositionCompatible", &ax::ParticleSystem::isSourcePositionCompatible)
        .member_function("initWithFile", &ax::ParticleSystem::initWithFile)
        .member_function(
            "initWithDictionary",
            [](ax::ParticleSystem* self, ax::ValueMap arg0, std::string_view arg1) { return self->initWithDictionary(arg0, arg1); },
            [](ax::ParticleSystem* self, ax::ValueMap arg0) { return self->initWithDictionary(arg0); })
        .member_function("initWithTotalParticles", &ax::ParticleSystem::initWithTotalParticles)
        .member_function("isPaused", &ax::ParticleSystem::isPaused)
        .member_function("pauseEmissions", &ax::ParticleSystem::pauseEmissions)
        .member_function("resumeEmissions", &ax::ParticleSystem::resumeEmissions)
        .member_function("getFixedFPS", &ax::ParticleSystem::getFixedFPS)
        .member_function(
            "setFixedFPS",
            [](ax::ParticleSystem* self) { self->setFixedFPS(); },
            [](ax::ParticleSystem* self, float arg0) { self->setFixedFPS(arg0); })
        .member_function("getTimeScale", &ax::ParticleSystem::getTimeScale)
        .member_function(
            "setTimeScale",
            [](ax::ParticleSystem* self) { self->setTimeScale(); },
            [](ax::ParticleSystem* self, float arg0) { self->setTimeScale(arg0); })
        .static_function("create", &ax::ParticleSystem::create)
        .static_function("createWithTotalParticles", &ax::ParticleSystem::createWithTotalParticles)
        .static_function("getAllParticleSystems", &ax::ParticleSystem::getAllParticleSystems)
        .static_function(
            "createMaskShape",
            [](std::string_view arg0) { return ax::ParticleSystem::createMaskShape(arg0); },
            [](std::string_view arg0, ax::Vec2 arg1) { return ax::ParticleSystem::createMaskShape(arg0, arg1); },
            [](std::string_view arg0, ax::Vec2 arg1, ax::Vec2 arg2) { return ax::ParticleSystem::createMaskShape(arg0, arg1, arg2); },
            [](std::string_view arg0, ax::Vec2 arg1, ax::Vec2 arg2, ax::Vec2 arg3)
            { return ax::ParticleSystem::createMaskShape(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0, ax::Vec2 arg1, ax::Vec2 arg2, ax::Vec2 arg3, float arg4)
            { return ax::ParticleSystem::createMaskShape(arg0, arg1, arg2, arg3, arg4); })
        .static_function("createPointShape", &ax::ParticleSystem::createPointShape)
        .static_function("createRectShape", &ax::ParticleSystem::createRectShape)
        .static_function("createRectTorusShape", &ax::ParticleSystem::createRectTorusShape)
        .static_function(
            "createCircleShape",
            [](ax::Vec2 arg0, float arg1) { return ax::ParticleSystem::createCircleShape(arg0, arg1); },
            [](ax::Vec2 arg0, float arg1, float arg2) { return ax::ParticleSystem::createCircleShape(arg0, arg1, arg2); })
        .static_function(
            "createConeShape",
            [](ax::Vec2 arg0, float arg1, float arg2, float arg3) { return ax::ParticleSystem::createConeShape(arg0, arg1, arg2, arg3); },
            [](ax::Vec2 arg0, float arg1, float arg2, float arg3, float arg4)
            { return ax::ParticleSystem::createConeShape(arg0, arg1, arg2, arg3, arg4); })
        .static_function(
            "createTorusShape",
            [](ax::Vec2 arg0, float arg1, float arg2) { return ax::ParticleSystem::createTorusShape(arg0, arg1, arg2); },
            [](ax::Vec2 arg0, float arg1, float arg2, float arg3) { return ax::ParticleSystem::createTorusShape(arg0, arg1, arg2, arg3); })
        .static_function(
            "createConeTorusShape",
            [](ax::Vec2 arg0, float arg1, float arg2, float arg3, float arg4)
            { return ax::ParticleSystem::createConeTorusShape(arg0, arg1, arg2, arg3, arg4); },
            [](ax::Vec2 arg0, float arg1, float arg2, float arg3, float arg4, float arg5)
            { return ax::ParticleSystem::createConeTorusShape(arg0, arg1, arg2, arg3, arg4, arg5); })
        .auto_wrap_objects(true);
    mod.class_("ParticleSystem", class_ParticleSystem);
}
static void js_register_ax_base_ParticleSystemQuad(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleSystemQuad> class_ParticleSystemQuad(isolate);
    class_ParticleSystemQuad.ctor([]() { return new ax::ParticleSystemQuad(); })
        .template inherit<ax::ParticleSystem>()
        .member_function("setDisplayFrame", &ax::ParticleSystemQuad::setDisplayFrame)
        .member_function("setTextureWithRect", &ax::ParticleSystemQuad::setTextureWithRect)
        .member_function("listenRendererRecreated", &ax::ParticleSystemQuad::listenRendererRecreated)
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::ParticleSystemQuad::create(arg0); },
            []() { return ax::ParticleSystemQuad::create(); },
            [](ax::ValueMap arg0) { return ax::ParticleSystemQuad::create(arg0); })
        .static_function("createWithTotalParticles", &ax::ParticleSystemQuad::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleSystemQuad", class_ParticleSystemQuad);
}
static void js_register_ax_base_ParticleFire(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleFire> class_ParticleFire(isolate);
    class_ParticleFire.ctor([]() { return new ax::ParticleFire(); })
        .template inherit<ax::ParticleSystemQuad>()
        .static_function("create", &ax::ParticleFire::create)
        .static_function("createWithTotalParticles", &ax::ParticleFire::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleFire", class_ParticleFire);
}
static void js_register_ax_base_ParticleFireworks(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleFireworks> class_ParticleFireworks(isolate);
    class_ParticleFireworks.ctor([]() { return new ax::ParticleFireworks(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleFireworks::init)
        .member_function("initWithTotalParticles", &ax::ParticleFireworks::initWithTotalParticles)
        .static_function("create", &ax::ParticleFireworks::create)
        .static_function("createWithTotalParticles", &ax::ParticleFireworks::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleFireworks", class_ParticleFireworks);
}
static void js_register_ax_base_ParticleSun(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleSun> class_ParticleSun(isolate);
    class_ParticleSun.ctor([]() { return new ax::ParticleSun(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleSun::init)
        .member_function("initWithTotalParticles", &ax::ParticleSun::initWithTotalParticles)
        .static_function("create", &ax::ParticleSun::create)
        .static_function("createWithTotalParticles", &ax::ParticleSun::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleSun", class_ParticleSun);
}
static void js_register_ax_base_ParticleGalaxy(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleGalaxy> class_ParticleGalaxy(isolate);
    class_ParticleGalaxy.ctor([]() { return new ax::ParticleGalaxy(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleGalaxy::init)
        .member_function("initWithTotalParticles", &ax::ParticleGalaxy::initWithTotalParticles)
        .static_function("create", &ax::ParticleGalaxy::create)
        .static_function("createWithTotalParticles", &ax::ParticleGalaxy::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleGalaxy", class_ParticleGalaxy);
}
static void js_register_ax_base_ParticleFlower(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleFlower> class_ParticleFlower(isolate);
    class_ParticleFlower.ctor([]() { return new ax::ParticleFlower(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleFlower::init)
        .member_function("initWithTotalParticles", &ax::ParticleFlower::initWithTotalParticles)
        .static_function("create", &ax::ParticleFlower::create)
        .static_function("createWithTotalParticles", &ax::ParticleFlower::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleFlower", class_ParticleFlower);
}
static void js_register_ax_base_ParticleMeteor(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleMeteor> class_ParticleMeteor(isolate);
    class_ParticleMeteor.ctor([]() { return new ax::ParticleMeteor(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleMeteor::init)
        .member_function("initWithTotalParticles", &ax::ParticleMeteor::initWithTotalParticles)
        .static_function("create", &ax::ParticleMeteor::create)
        .static_function("createWithTotalParticles", &ax::ParticleMeteor::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleMeteor", class_ParticleMeteor);
}
static void js_register_ax_base_ParticleSpiral(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleSpiral> class_ParticleSpiral(isolate);
    class_ParticleSpiral.ctor([]() { return new ax::ParticleSpiral(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleSpiral::init)
        .member_function("initWithTotalParticles", &ax::ParticleSpiral::initWithTotalParticles)
        .static_function("create", &ax::ParticleSpiral::create)
        .static_function("createWithTotalParticles", &ax::ParticleSpiral::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleSpiral", class_ParticleSpiral);
}
static void js_register_ax_base_ParticleExplosion(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleExplosion> class_ParticleExplosion(isolate);
    class_ParticleExplosion.ctor([]() { return new ax::ParticleExplosion(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleExplosion::init)
        .member_function("initWithTotalParticles", &ax::ParticleExplosion::initWithTotalParticles)
        .static_function("create", &ax::ParticleExplosion::create)
        .static_function("createWithTotalParticles", &ax::ParticleExplosion::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleExplosion", class_ParticleExplosion);
}
static void js_register_ax_base_ParticleSmoke(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleSmoke> class_ParticleSmoke(isolate);
    class_ParticleSmoke.ctor([]() { return new ax::ParticleSmoke(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleSmoke::init)
        .member_function("initWithTotalParticles", &ax::ParticleSmoke::initWithTotalParticles)
        .static_function("create", &ax::ParticleSmoke::create)
        .static_function("createWithTotalParticles", &ax::ParticleSmoke::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleSmoke", class_ParticleSmoke);
}
static void js_register_ax_base_ParticleSnow(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleSnow> class_ParticleSnow(isolate);
    class_ParticleSnow.ctor([]() { return new ax::ParticleSnow(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleSnow::init)
        .member_function("initWithTotalParticles", &ax::ParticleSnow::initWithTotalParticles)
        .static_function("create", &ax::ParticleSnow::create)
        .static_function("createWithTotalParticles", &ax::ParticleSnow::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleSnow", class_ParticleSnow);
}
static void js_register_ax_base_ParticleRain(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParticleRain> class_ParticleRain(isolate);
    class_ParticleRain.ctor([]() { return new ax::ParticleRain(); })
        .template inherit<ax::ParticleSystemQuad>()
        .member_function("init", &ax::ParticleRain::init)
        .member_function("initWithTotalParticles", &ax::ParticleRain::initWithTotalParticles)
        .static_function("create", &ax::ParticleRain::create)
        .static_function("createWithTotalParticles", &ax::ParticleRain::createWithTotalParticles)
        .auto_wrap_objects(true);
    mod.class_("ParticleRain", class_ParticleRain);
}
static void js_register_ax_base_ProgressTimer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ProgressTimer> class_ProgressTimer(isolate);
    class_ProgressTimer.ctor([]() { return new ax::ProgressTimer(); })
        .template inherit<ax::Node>()
        .member_function("getType", &ax::ProgressTimer::getType)
        .member_function("getPercentage", &ax::ProgressTimer::getPercentage)
        .member_function("getSprite", &ax::ProgressTimer::getSprite)
        .member_function("setPercentage", &ax::ProgressTimer::setPercentage)
        .member_function("setSprite", &ax::ProgressTimer::setSprite)
        .member_function("setType", &ax::ProgressTimer::setType)
        .member_function("isReverseDirection", &ax::ProgressTimer::isReverseDirection)
        .member_function("setReverseDirection", &ax::ProgressTimer::setReverseDirection)
        .member_function("setMidpoint", &ax::ProgressTimer::setMidpoint)
        .member_function("getMidpoint", &ax::ProgressTimer::getMidpoint)
        .member_function("setBarChangeRate", &ax::ProgressTimer::setBarChangeRate)
        .member_function("getBarChangeRate", &ax::ProgressTimer::getBarChangeRate)
        .member_function("initWithSprite", &ax::ProgressTimer::initWithSprite)
        .static_function("create", &ax::ProgressTimer::create)
        .auto_wrap_objects(true);
    mod.class_("ProgressTimer", class_ProgressTimer);
}
static void js_register_ax_base_ProtectedNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ProtectedNode> class_ProtectedNode(isolate);
    class_ProtectedNode.ctor([]() { return new ax::ProtectedNode(); })
        .template inherit<ax::Node>()
        .member_function(
            "addProtectedChild",
            [](ax::ProtectedNode* self, ax::Node* arg0, int arg1) { self->addProtectedChild(arg0, arg1); },
            [](ax::ProtectedNode* self, ax::Node* arg0) { self->addProtectedChild(arg0); },
            [](ax::ProtectedNode* self, ax::Node* arg0, int arg1, int arg2) { self->addProtectedChild(arg0, arg1, arg2); })
        .member_function("getProtectedChildByTag", &ax::ProtectedNode::getProtectedChildByTag)
        .member_function("getProtectedChildByName", &ax::ProtectedNode::getProtectedChildByName)
        .member_function(
            "removeProtectedChild",
            [](ax::ProtectedNode* self, ax::Node* arg0) { self->removeProtectedChild(arg0); },
            [](ax::ProtectedNode* self, ax::Node* arg0, bool arg1) { self->removeProtectedChild(arg0, arg1); })
        .member_function(
            "removeProtectedChildByTag",
            [](ax::ProtectedNode* self, int arg0) { self->removeProtectedChildByTag(arg0); },
            [](ax::ProtectedNode* self, int arg0, bool arg1) { self->removeProtectedChildByTag(arg0, arg1); })
        .member_function("removeAllProtectedChildren", &ax::ProtectedNode::removeAllProtectedChildren)
        .member_function("removeAllProtectedChildrenWithCleanup", &ax::ProtectedNode::removeAllProtectedChildrenWithCleanup)
        .member_function("reorderProtectedChild", &ax::ProtectedNode::reorderProtectedChild)
        .member_function("sortAllProtectedChildren", &ax::ProtectedNode::sortAllProtectedChildren)
        .member_function("getProtectedChildren", &ax::ProtectedNode::getProtectedChildren)
        .member_function("disableCascadeColor", &ax::ProtectedNode::disableCascadeColor)
        .member_function("disableCascadeOpacity", &ax::ProtectedNode::disableCascadeOpacity)
        .static_function("create", &ax::ProtectedNode::create)
        .auto_wrap_objects(true);
    mod.class_("ProtectedNode", class_ProtectedNode);
}
static void js_register_ax_base_RenderTexture(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::RenderTexture> class_RenderTexture(isolate);
    class_RenderTexture.ctor([]() { return new ax::RenderTexture(); })
        .template inherit<ax::Node>()
        .member_function("begin", &ax::RenderTexture::begin)
        .member_function(
            "beginWithClear",
            [](ax::RenderTexture* self, float arg0, float arg1, float arg2, float arg3, float arg4)
            { self->beginWithClear(arg0, arg1, arg2, arg3, arg4); },
            [](ax::RenderTexture* self, float arg0, float arg1, float arg2, float arg3) { self->beginWithClear(arg0, arg1, arg2, arg3); },
            [](ax::RenderTexture* self, float arg0, float arg1, float arg2, float arg3, float arg4, int arg5)
            { self->beginWithClear(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function("end", &ax::RenderTexture::end)
        .member_function("clear", &ax::RenderTexture::clear)
        .member_function("clearDepth", &ax::RenderTexture::clearDepth)
        .member_function("clearStencil", &ax::RenderTexture::clearStencil)
        .member_function(
            "saveToFileAsNonPMA",
            [](ax::RenderTexture* self,
               std::string_view arg0,
               ax::Image::Format arg1,
               bool arg2,
               std::function<void(ax::RenderTexture*, std::string_view)> arg3) { return self->saveToFileAsNonPMA(arg0, arg1, arg2, arg3); },
            [](ax::RenderTexture* self, std::string_view arg0) { return self->saveToFileAsNonPMA(arg0); },
            [](ax::RenderTexture* self, std::string_view arg0, bool arg1) { return self->saveToFileAsNonPMA(arg0, arg1); },
            [](ax::RenderTexture* self, std::string_view arg0, bool arg1, std::function<void(ax::RenderTexture*, std::string_view)> arg2)
            { return self->saveToFileAsNonPMA(arg0, arg1, arg2); })
        .member_function(
            "saveToFile",
            [](ax::RenderTexture* self, std::string_view arg0, ax::Image::Format arg1) { return self->saveToFile(arg0, arg1); },
            [](ax::RenderTexture* self, std::string_view arg0, ax::Image::Format arg1, bool arg2)
            { return self->saveToFile(arg0, arg1, arg2); },
            [](ax::RenderTexture* self,
               std::string_view arg0,
               ax::Image::Format arg1,
               bool arg2,
               std::function<void(ax::RenderTexture*, std::string_view)> arg3) { return self->saveToFile(arg0, arg1, arg2, arg3); },
            [](ax::RenderTexture* self, std::string_view arg0) { return self->saveToFile(arg0); },
            [](ax::RenderTexture* self, std::string_view arg0, bool arg1) { return self->saveToFile(arg0, arg1); },
            [](ax::RenderTexture* self, std::string_view arg0, bool arg1, std::function<void(ax::RenderTexture*, std::string_view)> arg2)
            { return self->saveToFile(arg0, arg1, arg2); })
        .member_function("getClearFlags", &ax::RenderTexture::getClearFlags)
        .member_function("setClearFlags", &ax::RenderTexture::setClearFlags)
        .member_function("getClearColor", &ax::RenderTexture::getClearColor)
        .member_function("setClearColor", &ax::RenderTexture::setClearColor)
        .member_function("getClearDepth", &ax::RenderTexture::getClearDepth)
        .member_function("setClearDepth", &ax::RenderTexture::setClearDepth)
        .member_function("getClearStencil", &ax::RenderTexture::getClearStencil)
        .member_function("setClearStencil", &ax::RenderTexture::setClearStencil)
        .member_function("isAutoDraw", &ax::RenderTexture::isAutoDraw)
        .member_function("setAutoDraw", &ax::RenderTexture::setAutoDraw)
        .member_function("getSprite", &ax::RenderTexture::getSprite)
        .member_function("getRenderTarget", &ax::RenderTexture::getRenderTarget)
        .member_function("setKeepMatrix", &ax::RenderTexture::setKeepMatrix)
        .member_function("setVirtualViewport", &ax::RenderTexture::setVirtualViewport)
        .member_function("isSharedRenderTarget", &ax::RenderTexture::isSharedRenderTarget)
        .member_function(
            "initWithWidthAndHeight",
            [](ax::RenderTexture* self, int arg0, int arg1, ax::rhi::PixelFormat arg2, ax::rhi::PixelFormat arg3)
            { return self->initWithWidthAndHeight(arg0, arg1, arg2, arg3); },
            [](ax::RenderTexture* self, int arg0, int arg1, ax::rhi::PixelFormat arg2, ax::rhi::PixelFormat arg3, bool arg4)
            { return self->initWithWidthAndHeight(arg0, arg1, arg2, arg3, arg4); },
            [](ax::RenderTexture* self, int arg0, int arg1, ax::rhi::PixelFormat arg2)
            { return self->initWithWidthAndHeight(arg0, arg1, arg2); },
            [](ax::RenderTexture* self, int arg0, int arg1, ax::rhi::PixelFormat arg2, bool arg3)
            { return self->initWithWidthAndHeight(arg0, arg1, arg2, arg3); })
        .static_function("applySpriteFlippedY", &ax::RenderTexture::applySpriteFlippedY)
        .static_function(
            "create",
            [](int arg0, int arg1, ax::rhi::PixelFormat arg2) { return ax::RenderTexture::create(arg0, arg1, arg2); },
            [](int arg0, int arg1, ax::rhi::PixelFormat arg2, bool arg3) { return ax::RenderTexture::create(arg0, arg1, arg2, arg3); },
            [](int arg0, int arg1, ax::rhi::PixelFormat arg2, ax::rhi::PixelFormat arg3)
            { return ax::RenderTexture::create(arg0, arg1, arg2, arg3); },
            [](int arg0, int arg1, ax::rhi::PixelFormat arg2, ax::rhi::PixelFormat arg3, bool arg4)
            { return ax::RenderTexture::create(arg0, arg1, arg2, arg3, arg4); },
            [](int arg0, int arg1) { return ax::RenderTexture::create(arg0, arg1); },
            [](int arg0, int arg1, bool arg2) { return ax::RenderTexture::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("RenderTexture", class_RenderTexture);
}
static void js_register_ax_base_TransitionEaseScene(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionEaseScene> class_TransitionEaseScene(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_TransitionEaseScene.member_function("easeActionWithAction", &ax::TransitionEaseScene::easeActionWithAction)
        .auto_wrap_objects(true);
    mod.class_("TransitionEaseScene", class_TransitionEaseScene);
}
static void js_register_ax_base_TransitionScene(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionScene> class_TransitionScene(isolate);
    class_TransitionScene.ctor([]() { return new ax::TransitionScene(); })
        .template inherit<ax::Scene>()
        .member_function("finish", &ax::TransitionScene::finish)
        .member_function("hideOutShowIn", &ax::TransitionScene::hideOutShowIn)
        .member_function("getInScene", &ax::TransitionScene::getInScene)
        .member_function("getDuration", &ax::TransitionScene::getDuration)
        .member_function("initWithDuration", &ax::TransitionScene::initWithDuration)
        .static_function("create", &ax::TransitionScene::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionScene", class_TransitionScene);
}
static void js_register_ax_base_TransitionSceneOriented(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionSceneOriented> class_TransitionSceneOriented(isolate);
    class_TransitionSceneOriented.ctor([]() { return new ax::TransitionSceneOriented(); })
        .template inherit<ax::TransitionScene>()
        .member_function("initWithDuration", &ax::TransitionSceneOriented::initWithDuration)
        .static_function("create", &ax::TransitionSceneOriented::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionSceneOriented", class_TransitionSceneOriented);
}
static void js_register_ax_base_TransitionRotoZoom(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionRotoZoom> class_TransitionRotoZoom(isolate);
    class_TransitionRotoZoom.ctor([]() { return new ax::TransitionRotoZoom(); })
        .template inherit<ax::TransitionScene>()
        .static_function("create", &ax::TransitionRotoZoom::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionRotoZoom", class_TransitionRotoZoom);
}
static void js_register_ax_base_TransitionJumpZoom(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionJumpZoom> class_TransitionJumpZoom(isolate);
    class_TransitionJumpZoom.ctor([]() { return new ax::TransitionJumpZoom(); })
        .template inherit<ax::TransitionScene>()
        .static_function("create", &ax::TransitionJumpZoom::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionJumpZoom", class_TransitionJumpZoom);
}
static void js_register_ax_base_TransitionMoveInL(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionMoveInL> class_TransitionMoveInL(isolate);
    class_TransitionMoveInL.ctor([]() { return new ax::TransitionMoveInL(); })
        .template inherit<ax::TransitionScene>()
        .member_function("action", &ax::TransitionMoveInL::action)
        .member_function("easeActionWithAction", &ax::TransitionMoveInL::easeActionWithAction)
        .static_function("create", &ax::TransitionMoveInL::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionMoveInL", class_TransitionMoveInL);
}
static void js_register_ax_base_TransitionMoveInR(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionMoveInR> class_TransitionMoveInR(isolate);
    class_TransitionMoveInR.ctor([]() { return new ax::TransitionMoveInR(); })
        .template inherit<ax::TransitionMoveInL>()
        .static_function("create", &ax::TransitionMoveInR::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionMoveInR", class_TransitionMoveInR);
}
static void js_register_ax_base_TransitionMoveInT(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionMoveInT> class_TransitionMoveInT(isolate);
    class_TransitionMoveInT.ctor([]() { return new ax::TransitionMoveInT(); })
        .template inherit<ax::TransitionMoveInL>()
        .static_function("create", &ax::TransitionMoveInT::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionMoveInT", class_TransitionMoveInT);
}
static void js_register_ax_base_TransitionMoveInB(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionMoveInB> class_TransitionMoveInB(isolate);
    class_TransitionMoveInB.ctor([]() { return new ax::TransitionMoveInB(); })
        .template inherit<ax::TransitionMoveInL>()
        .static_function("create", &ax::TransitionMoveInB::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionMoveInB", class_TransitionMoveInB);
}
static void js_register_ax_base_TransitionSlideInL(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionSlideInL> class_TransitionSlideInL(isolate);
    class_TransitionSlideInL.ctor([]() { return new ax::TransitionSlideInL(); })
        .template inherit<ax::TransitionScene>()
        .member_function("easeActionWithAction", &ax::TransitionSlideInL::easeActionWithAction)
        .member_function("action", &ax::TransitionSlideInL::action)
        .static_function("create", &ax::TransitionSlideInL::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionSlideInL", class_TransitionSlideInL);
}
static void js_register_ax_base_TransitionSlideInR(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionSlideInR> class_TransitionSlideInR(isolate);
    class_TransitionSlideInR.ctor([]() { return new ax::TransitionSlideInR(); })
        .template inherit<ax::TransitionSlideInL>()
        .static_function("create", &ax::TransitionSlideInR::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionSlideInR", class_TransitionSlideInR);
}
static void js_register_ax_base_TransitionSlideInB(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionSlideInB> class_TransitionSlideInB(isolate);
    class_TransitionSlideInB.ctor([]() { return new ax::TransitionSlideInB(); })
        .template inherit<ax::TransitionSlideInL>()
        .static_function("create", &ax::TransitionSlideInB::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionSlideInB", class_TransitionSlideInB);
}
static void js_register_ax_base_TransitionSlideInT(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionSlideInT> class_TransitionSlideInT(isolate);
    class_TransitionSlideInT.ctor([]() { return new ax::TransitionSlideInT(); })
        .template inherit<ax::TransitionSlideInL>()
        .static_function("create", &ax::TransitionSlideInT::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionSlideInT", class_TransitionSlideInT);
}
static void js_register_ax_base_TransitionShrinkGrow(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionShrinkGrow> class_TransitionShrinkGrow(isolate);
    class_TransitionShrinkGrow.ctor([]() { return new ax::TransitionShrinkGrow(); })
        .template inherit<ax::TransitionScene>()
        .member_function("easeActionWithAction", &ax::TransitionShrinkGrow::easeActionWithAction)
        .static_function("create", &ax::TransitionShrinkGrow::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionShrinkGrow", class_TransitionShrinkGrow);
}
static void js_register_ax_base_TransitionFlipX(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionFlipX> class_TransitionFlipX(isolate);
    class_TransitionFlipX.ctor([]() { return new ax::TransitionFlipX(); })
        .template inherit<ax::TransitionSceneOriented>()
        .static_function(
            "create",
            [](float arg0, ax::Scene* arg1) { return ax::TransitionFlipX::create(arg0, arg1); },
            [](float arg0, ax::Scene* arg1, ax::TransitionScene::Orientation arg2)
            { return ax::TransitionFlipX::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("TransitionFlipX", class_TransitionFlipX);
}
static void js_register_ax_base_TransitionFlipY(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionFlipY> class_TransitionFlipY(isolate);
    class_TransitionFlipY.ctor([]() { return new ax::TransitionFlipY(); })
        .template inherit<ax::TransitionSceneOriented>()
        .static_function(
            "create",
            [](float arg0, ax::Scene* arg1) { return ax::TransitionFlipY::create(arg0, arg1); },
            [](float arg0, ax::Scene* arg1, ax::TransitionScene::Orientation arg2)
            { return ax::TransitionFlipY::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("TransitionFlipY", class_TransitionFlipY);
}
static void js_register_ax_base_TransitionFlipAngular(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionFlipAngular> class_TransitionFlipAngular(isolate);
    class_TransitionFlipAngular.ctor([]() { return new ax::TransitionFlipAngular(); })
        .template inherit<ax::TransitionSceneOriented>()
        .static_function(
            "create",
            [](float arg0, ax::Scene* arg1) { return ax::TransitionFlipAngular::create(arg0, arg1); },
            [](float arg0, ax::Scene* arg1, ax::TransitionScene::Orientation arg2)
            { return ax::TransitionFlipAngular::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("TransitionFlipAngular", class_TransitionFlipAngular);
}
static void js_register_ax_base_TransitionZoomFlipX(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionZoomFlipX> class_TransitionZoomFlipX(isolate);
    class_TransitionZoomFlipX.ctor([]() { return new ax::TransitionZoomFlipX(); })
        .template inherit<ax::TransitionSceneOriented>()
        .static_function(
            "create",
            [](float arg0, ax::Scene* arg1) { return ax::TransitionZoomFlipX::create(arg0, arg1); },
            [](float arg0, ax::Scene* arg1, ax::TransitionScene::Orientation arg2)
            { return ax::TransitionZoomFlipX::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("TransitionZoomFlipX", class_TransitionZoomFlipX);
}
static void js_register_ax_base_TransitionZoomFlipY(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionZoomFlipY> class_TransitionZoomFlipY(isolate);
    class_TransitionZoomFlipY.ctor([]() { return new ax::TransitionZoomFlipY(); })
        .template inherit<ax::TransitionSceneOriented>()
        .static_function(
            "create",
            [](float arg0, ax::Scene* arg1) { return ax::TransitionZoomFlipY::create(arg0, arg1); },
            [](float arg0, ax::Scene* arg1, ax::TransitionScene::Orientation arg2)
            { return ax::TransitionZoomFlipY::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("TransitionZoomFlipY", class_TransitionZoomFlipY);
}
static void js_register_ax_base_TransitionZoomFlipAngular(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionZoomFlipAngular> class_TransitionZoomFlipAngular(isolate);
    class_TransitionZoomFlipAngular.ctor([]() { return new ax::TransitionZoomFlipAngular(); })
        .template inherit<ax::TransitionSceneOriented>()
        .static_function(
            "create",
            [](float arg0, ax::Scene* arg1) { return ax::TransitionZoomFlipAngular::create(arg0, arg1); },
            [](float arg0, ax::Scene* arg1, ax::TransitionScene::Orientation arg2)
            { return ax::TransitionZoomFlipAngular::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("TransitionZoomFlipAngular", class_TransitionZoomFlipAngular);
}
static void js_register_ax_base_TransitionFade(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionFade> class_TransitionFade(isolate);
    class_TransitionFade.ctor([]() { return new ax::TransitionFade(); })
        .template inherit<ax::TransitionScene>()
        .member_function(
            "initWithDuration",
            [](ax::TransitionFade* self, float arg0, ax::Scene* arg1) { return self->initWithDuration(arg0, arg1); },
            [](ax::TransitionFade* self, float arg0, ax::Scene* arg1, ax::Color32 arg2)
            { return self->initWithDuration(arg0, arg1, arg2); })
        .static_function(
            "create",
            [](float arg0, ax::Scene* arg1) { return ax::TransitionFade::create(arg0, arg1); },
            [](float arg0, ax::Scene* arg1, ax::Color32 arg2) { return ax::TransitionFade::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("TransitionFade", class_TransitionFade);
}
static void js_register_ax_base_TransitionCrossFade(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionCrossFade> class_TransitionCrossFade(isolate);
    class_TransitionCrossFade.ctor([]() { return new ax::TransitionCrossFade(); })
        .template inherit<ax::TransitionScene>()
        .static_function("create", &ax::TransitionCrossFade::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionCrossFade", class_TransitionCrossFade);
}
static void js_register_ax_base_TransitionTurnOffTiles(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionTurnOffTiles> class_TransitionTurnOffTiles(isolate);
    class_TransitionTurnOffTiles.ctor([]() { return new ax::TransitionTurnOffTiles(); })
        .template inherit<ax::TransitionScene>()
        .member_function("easeActionWithAction", &ax::TransitionTurnOffTiles::easeActionWithAction)
        .static_function("create", &ax::TransitionTurnOffTiles::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionTurnOffTiles", class_TransitionTurnOffTiles);
}
static void js_register_ax_base_TransitionSplitCols(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionSplitCols> class_TransitionSplitCols(isolate);
    class_TransitionSplitCols.ctor([]() { return new ax::TransitionSplitCols(); })
        .template inherit<ax::TransitionScene>()
        .member_function("action", &ax::TransitionSplitCols::action)
        .member_function("easeActionWithAction", &ax::TransitionSplitCols::easeActionWithAction)
        .static_function("create", &ax::TransitionSplitCols::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionSplitCols", class_TransitionSplitCols);
}
static void js_register_ax_base_TransitionSplitRows(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionSplitRows> class_TransitionSplitRows(isolate);
    class_TransitionSplitRows.ctor([]() { return new ax::TransitionSplitRows(); })
        .template inherit<ax::TransitionSplitCols>()
        .static_function("create", &ax::TransitionSplitRows::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionSplitRows", class_TransitionSplitRows);
}
static void js_register_ax_base_TransitionFadeTR(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionFadeTR> class_TransitionFadeTR(isolate);
    class_TransitionFadeTR.ctor([]() { return new ax::TransitionFadeTR(); })
        .template inherit<ax::TransitionScene>()
        .member_function("actionWithSize", &ax::TransitionFadeTR::actionWithSize)
        .member_function("easeActionWithAction", &ax::TransitionFadeTR::easeActionWithAction)
        .static_function("create", &ax::TransitionFadeTR::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionFadeTR", class_TransitionFadeTR);
}
static void js_register_ax_base_TransitionFadeBL(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionFadeBL> class_TransitionFadeBL(isolate);
    class_TransitionFadeBL.ctor([]() { return new ax::TransitionFadeBL(); })
        .template inherit<ax::TransitionFadeTR>()
        .static_function("create", &ax::TransitionFadeBL::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionFadeBL", class_TransitionFadeBL);
}
static void js_register_ax_base_TransitionFadeUp(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionFadeUp> class_TransitionFadeUp(isolate);
    class_TransitionFadeUp.ctor([]() { return new ax::TransitionFadeUp(); })
        .template inherit<ax::TransitionFadeTR>()
        .static_function("create", &ax::TransitionFadeUp::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionFadeUp", class_TransitionFadeUp);
}
static void js_register_ax_base_TransitionFadeDown(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionFadeDown> class_TransitionFadeDown(isolate);
    class_TransitionFadeDown.ctor([]() { return new ax::TransitionFadeDown(); })
        .template inherit<ax::TransitionFadeTR>()
        .static_function("create", &ax::TransitionFadeDown::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionFadeDown", class_TransitionFadeDown);
}
static void js_register_ax_base_TransitionPageTurn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionPageTurn> class_TransitionPageTurn(isolate);
    class_TransitionPageTurn.ctor([]() { return new ax::TransitionPageTurn(); })
        .template inherit<ax::TransitionScene>()
        .member_function("initWithDuration", &ax::TransitionPageTurn::initWithDuration)
        .member_function("actionWithSize", &ax::TransitionPageTurn::actionWithSize)
        .static_function("create", &ax::TransitionPageTurn::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionPageTurn", class_TransitionPageTurn);
}
static void js_register_ax_base_TransitionProgress(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionProgress> class_TransitionProgress(isolate);
    class_TransitionProgress.ctor([]() { return new ax::TransitionProgress(); })
        .template inherit<ax::TransitionScene>()
        .static_function("create", &ax::TransitionProgress::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionProgress", class_TransitionProgress);
}
static void js_register_ax_base_TransitionProgressRadialCCW(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionProgressRadialCCW> class_TransitionProgressRadialCCW(isolate);
    class_TransitionProgressRadialCCW.ctor([]() { return new ax::TransitionProgressRadialCCW(); })
        .template inherit<ax::TransitionProgress>()
        .static_function("create", &ax::TransitionProgressRadialCCW::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionProgressRadialCCW", class_TransitionProgressRadialCCW);
}
static void js_register_ax_base_TransitionProgressRadialCW(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionProgressRadialCW> class_TransitionProgressRadialCW(isolate);
    class_TransitionProgressRadialCW.ctor([]() { return new ax::TransitionProgressRadialCW(); })
        .template inherit<ax::TransitionProgress>()
        .static_function("create", &ax::TransitionProgressRadialCW::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionProgressRadialCW", class_TransitionProgressRadialCW);
}
static void js_register_ax_base_TransitionProgressHorizontal(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionProgressHorizontal> class_TransitionProgressHorizontal(isolate);
    class_TransitionProgressHorizontal.ctor([]() { return new ax::TransitionProgressHorizontal(); })
        .template inherit<ax::TransitionProgress>()
        .static_function("create", &ax::TransitionProgressHorizontal::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionProgressHorizontal", class_TransitionProgressHorizontal);
}
static void js_register_ax_base_TransitionProgressVertical(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionProgressVertical> class_TransitionProgressVertical(isolate);
    class_TransitionProgressVertical.ctor([]() { return new ax::TransitionProgressVertical(); })
        .template inherit<ax::TransitionProgress>()
        .static_function("create", &ax::TransitionProgressVertical::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionProgressVertical", class_TransitionProgressVertical);
}
static void js_register_ax_base_TransitionProgressInOut(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionProgressInOut> class_TransitionProgressInOut(isolate);
    class_TransitionProgressInOut.ctor([]() { return new ax::TransitionProgressInOut(); })
        .template inherit<ax::TransitionProgress>()
        .static_function("create", &ax::TransitionProgressInOut::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionProgressInOut", class_TransitionProgressInOut);
}
static void js_register_ax_base_TransitionProgressOutIn(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TransitionProgressOutIn> class_TransitionProgressOutIn(isolate);
    class_TransitionProgressOutIn.ctor([]() { return new ax::TransitionProgressOutIn(); })
        .template inherit<ax::TransitionProgress>()
        .static_function("create", &ax::TransitionProgressOutIn::create)
        .auto_wrap_objects(true);
    mod.class_("TransitionProgressOutIn", class_TransitionProgressOutIn);
}
static void js_register_ax_base_Camera(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Camera> class_Camera(isolate);
    class_Camera.ctor([]() { return new ax::Camera(); })
        .template inherit<ax::Node>()
        .member_function("getCameraFlag", &ax::Camera::getCameraFlag)
        .member_function("setCameraFlag", &ax::Camera::setCameraFlag)
        .member_function(
            "lookAt",
            [](ax::Camera* self, ax::Vec3 arg0) { self->lookAt(arg0); },
            [](ax::Camera* self, ax::Vec3 arg0, ax::Vec3 arg1) { self->lookAt(arg0, arg1); })
        .member_function("getProjectionMatrix", &ax::Camera::getProjectionMatrix)
        .member_function("getViewMatrix", &ax::Camera::getViewMatrix)
        .member_function("getViewProjectionMatrix", &ax::Camera::getViewProjectionMatrix)
        .member_function("project", &ax::Camera::project)
        .member_function("projectGL", &ax::Camera::projectGL)
        .member_function("isVisibleInFrustum", &ax::Camera::isVisibleInFrustum)
        .member_function("getDepthInView", &ax::Camera::getDepthInView)
        .member_function("setDepth", &ax::Camera::setDepth)
        .member_function("getDepth", &ax::Camera::getDepth)
        .member_function("getRenderOrder", &ax::Camera::getRenderOrder)
        .member_function("getFOV", &ax::Camera::getFOV)
        .member_function("setFOV", &ax::Camera::setFOV)
        .member_function("getFarPlane", &ax::Camera::getFarPlane)
        .member_function("setFarPlane", &ax::Camera::setFarPlane)
        .member_function("getNearPlane", &ax::Camera::getNearPlane)
        .member_function("setNearPlane", &ax::Camera::setNearPlane)
        .member_function("getZoom", &ax::Camera::getZoom)
        .member_function("setZoom", &ax::Camera::setZoom)
        .member_function("applyZoom", &ax::Camera::applyZoom)
        .member_function("clearBackground", &ax::Camera::clearBackground)
        .member_function("apply", &ax::Camera::apply)
        .member_function("isViewProjectionUpdated", &ax::Camera::isViewProjectionUpdated)
        .member_function("setBackgroundBrush", &ax::Camera::setBackgroundBrush)
        .member_function("getBackgroundBrush", &ax::Camera::getBackgroundBrush)
        .member_function("isBrushValid", &ax::Camera::isBrushValid)
        .member_function("setScene", &ax::Camera::setScene)
        .member_function("setAdditionalProjection", &ax::Camera::setAdditionalProjection)
        .member_function("initDefault", &ax::Camera::initDefault)
        .member_function("initPerspective", &ax::Camera::initPerspective)
        .member_function("initOrthographic", &ax::Camera::initOrthographic)
        .member_function("applyViewport", &ax::Camera::applyViewport)
        .static_function("createPerspective", &ax::Camera::createPerspective)
        .static_function("createOrthographic", &ax::Camera::createOrthographic)
        .static_function("create", &ax::Camera::create)
        .static_function("getVisitingCamera", &ax::Camera::getVisitingCamera)
        .static_function("getDefaultViewport", &ax::Camera::getDefaultViewport)
        .static_function("setDefaultViewport", &ax::Camera::setDefaultViewport)
        .static_function("getDefaultCamera", &ax::Camera::getDefaultCamera)
        .auto_wrap_objects(true);
    mod.class_("Camera", class_Camera);
}
static void js_register_ax_base_CameraBackgroundBrush(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CameraBackgroundBrush> class_CameraBackgroundBrush(isolate);
    class_CameraBackgroundBrush.ctor([]() { return new ax::CameraBackgroundBrush(); })
        .template inherit<ax::Object>()
        .member_function("getBrushType", &ax::CameraBackgroundBrush::getBrushType)
        .member_function("drawBackground", &ax::CameraBackgroundBrush::drawBackground)
        .member_function("isValid", &ax::CameraBackgroundBrush::isValid)
        .member_function("init", &ax::CameraBackgroundBrush::init)
        .static_function("createNoneBrush", &ax::CameraBackgroundBrush::createNoneBrush)
        .static_function(
            "createDepthBrush",
            []() { return ax::CameraBackgroundBrush::createDepthBrush(); },
            [](float arg0) { return ax::CameraBackgroundBrush::createDepthBrush(arg0); })
        .static_function("createColorBrush", &ax::CameraBackgroundBrush::createColorBrush)
        .static_function("createSkyboxBrush", &ax::CameraBackgroundBrush::createSkyboxBrush)
        .auto_wrap_objects(true);
    mod.class_("CameraBackgroundBrush", class_CameraBackgroundBrush);
}
static void js_register_ax_base_CameraBackgroundDepthBrush(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CameraBackgroundDepthBrush> class_CameraBackgroundDepthBrush(isolate);
    class_CameraBackgroundDepthBrush.ctor([]() { return new ax::CameraBackgroundDepthBrush(); })
        .template inherit<ax::CameraBackgroundBrush>()
        .member_function("setDepth", &ax::CameraBackgroundDepthBrush::setDepth)
        .static_function("create", &ax::CameraBackgroundDepthBrush::create)
        .auto_wrap_objects(true);
    mod.class_("CameraBackgroundDepthBrush", class_CameraBackgroundDepthBrush);
}
static void js_register_ax_base_CameraBackgroundColorBrush(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CameraBackgroundColorBrush> class_CameraBackgroundColorBrush(isolate);
    class_CameraBackgroundColorBrush.ctor([]() { return new ax::CameraBackgroundColorBrush(); })
        .template inherit<ax::CameraBackgroundDepthBrush>()
        .member_function("setColor", &ax::CameraBackgroundColorBrush::setColor)
        .static_function("create", &ax::CameraBackgroundColorBrush::create)
        .auto_wrap_objects(true);
    mod.class_("CameraBackgroundColorBrush", class_CameraBackgroundColorBrush);
}
static void js_register_ax_base_CameraBackgroundSkyBoxBrush(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CameraBackgroundSkyBoxBrush> class_CameraBackgroundSkyBoxBrush(isolate);
    class_CameraBackgroundSkyBoxBrush.ctor([]() { return new ax::CameraBackgroundSkyBoxBrush(); })
        .template inherit<ax::CameraBackgroundBrush>()
        .member_function("setTexture", &ax::CameraBackgroundSkyBoxBrush::setTexture)
        .member_function("getTexture", &ax::CameraBackgroundSkyBoxBrush::getTexture)
        .member_function("isActived", &ax::CameraBackgroundSkyBoxBrush::isActived)
        .member_function("setActived", &ax::CameraBackgroundSkyBoxBrush::setActived)
        .member_function("setTextureValid", &ax::CameraBackgroundSkyBoxBrush::setTextureValid)
        .static_function(
            "create",
            []() { return ax::CameraBackgroundSkyBoxBrush::create(); },
            [](std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4,
               std::string_view arg5) { return ax::CameraBackgroundSkyBoxBrush::create(arg0, arg1, arg2, arg3, arg4, arg5); })
        .auto_wrap_objects(true);
    mod.class_("CameraBackgroundSkyBoxBrush", class_CameraBackgroundSkyBoxBrush);
}
static void js_register_ax_base_GridBase(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::GridBase> class_GridBase(isolate);
    class_GridBase.template inherit<ax::Object>()
        .member_function("beforeBlit", &ax::GridBase::beforeBlit)
        .member_function("afterBlit", &ax::GridBase::afterBlit)
        .member_function("blit", &ax::GridBase::blit)
        .member_function("reuse", &ax::GridBase::reuse)
        .member_function("calculateVertexPoints", &ax::GridBase::calculateVertexPoints)
        .member_function(
            "initWithSize",
            [](ax::GridBase* self, ax::Vec2 arg0, ax::Rect arg1) { return self->initWithSize(arg0, arg1); },
            [](ax::GridBase* self, ax::Vec2 arg0) { return self->initWithSize(arg0); },
            [](ax::GridBase* self, ax::Vec2 arg0, ax::Texture2D* arg1, bool arg2) { return self->initWithSize(arg0, arg1, arg2); },
            [](ax::GridBase* self, ax::Vec2 arg0, ax::Texture2D* arg1, bool arg2, ax::Rect arg3)
            { return self->initWithSize(arg0, arg1, arg2, arg3); })
        .member_function("isActive", &ax::GridBase::isActive)
        .member_function("setActive", &ax::GridBase::setActive)
        .member_function("getReuseGrid", &ax::GridBase::getReuseGrid)
        .member_function("setReuseGrid", &ax::GridBase::setReuseGrid)
        .member_function("getGridSize", &ax::GridBase::getGridSize)
        .member_function("setGridSize", &ax::GridBase::setGridSize)
        .member_function("getStep", &ax::GridBase::getStep)
        .member_function("setStep", &ax::GridBase::setStep)
        .member_function("isTextureFlipped", &ax::GridBase::isTextureFlipped)
        .member_function("setTextureFlipped", &ax::GridBase::setTextureFlipped)
        .member_function("beforeDraw", &ax::GridBase::beforeDraw)
        .member_function("afterDraw", &ax::GridBase::afterDraw)
        .member_function("set2DProjection", &ax::GridBase::set2DProjection)
        .member_function("setGridRect", &ax::GridBase::setGridRect)
        .member_function("getGridRect", &ax::GridBase::getGridRect)
        .auto_wrap_objects(true);
    mod.class_("GridBase", class_GridBase);
}
static void js_register_ax_base_Grid3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Grid3D> class_Grid3D(isolate);
    class_Grid3D.ctor([]() { return new ax::Grid3D(); })
        .template inherit<ax::GridBase>()
        .member_function("setNeedDepthTestForBlit", &ax::Grid3D::setNeedDepthTestForBlit)
        .member_function("getNeedDepthTestForBlit", &ax::Grid3D::getNeedDepthTestForBlit)
        .static_function(
            "create",
            [](ax::Vec2 arg0, ax::Rect arg1) { return ax::Grid3D::create(arg0, arg1); },
            [](ax::Vec2 arg0) { return ax::Grid3D::create(arg0); },
            [](ax::Vec2 arg0, ax::Texture2D* arg1, bool arg2) { return ax::Grid3D::create(arg0, arg1, arg2); },
            [](ax::Vec2 arg0, ax::Texture2D* arg1, bool arg2, ax::Rect arg3) { return ax::Grid3D::create(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("Grid3D", class_Grid3D);
}
static void js_register_ax_base_TiledGrid3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TiledGrid3D> class_TiledGrid3D(isolate);
    class_TiledGrid3D.template inherit<ax::GridBase>()
        .static_function(
            "create",
            [](ax::Vec2 arg0, ax::Rect arg1) { return ax::TiledGrid3D::create(arg0, arg1); },
            [](ax::Vec2 arg0) { return ax::TiledGrid3D::create(arg0); },
            [](ax::Vec2 arg0, ax::Texture2D* arg1, bool arg2) { return ax::TiledGrid3D::create(arg0, arg1, arg2); },
            [](ax::Vec2 arg0, ax::Texture2D* arg1, bool arg2, ax::Rect arg3) { return ax::TiledGrid3D::create(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("TiledGrid3D", class_TiledGrid3D);
}
static void js_register_ax_base_BaseLight(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::BaseLight> class_BaseLight(isolate);
    class_BaseLight.template inherit<ax::Node>()
        .member_function("getLightType", &ax::BaseLight::getLightType)
        .member_function("getIntensity", &ax::BaseLight::getIntensity)
        .member_function("setIntensity", &ax::BaseLight::setIntensity)
        .member_function("getLightFlag", &ax::BaseLight::getLightFlag)
        .member_function("setLightFlag", &ax::BaseLight::setLightFlag)
        .member_function("setEnabled", &ax::BaseLight::setEnabled)
        .member_function("isEnabled", &ax::BaseLight::isEnabled)
        .auto_wrap_objects(true);
    mod.class_("BaseLight", class_BaseLight);
}
static void js_register_ax_base_DirectionLight(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::DirectionLight> class_DirectionLight(isolate);
    class_DirectionLight.ctor([]() { return new ax::DirectionLight(); })
        .template inherit<ax::BaseLight>()
        .member_function("setDirection", &ax::DirectionLight::setDirection)
        .member_function("getDirection", &ax::DirectionLight::getDirection)
        .member_function("getDirectionInWorld", &ax::DirectionLight::getDirectionInWorld)
        .static_function("create", &ax::DirectionLight::create)
        .auto_wrap_objects(true);
    mod.class_("DirectionLight", class_DirectionLight);
}
static void js_register_ax_base_PointLight(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::PointLight> class_PointLight(isolate);
    class_PointLight.ctor([]() { return new ax::PointLight(); })
        .template inherit<ax::BaseLight>()
        .member_function("getRange", &ax::PointLight::getRange)
        .member_function("setRange", &ax::PointLight::setRange)
        .static_function("create", &ax::PointLight::create)
        .auto_wrap_objects(true);
    mod.class_("PointLight", class_PointLight);
}
static void js_register_ax_base_SpotLight(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SpotLight> class_SpotLight(isolate);
    class_SpotLight.ctor([]() { return new ax::SpotLight(); })
        .template inherit<ax::BaseLight>()
        .member_function("setDirection", &ax::SpotLight::setDirection)
        .member_function("getDirection", &ax::SpotLight::getDirection)
        .member_function("getDirectionInWorld", &ax::SpotLight::getDirectionInWorld)
        .member_function("setRange", &ax::SpotLight::setRange)
        .member_function("getRange", &ax::SpotLight::getRange)
        .member_function("setInnerAngle", &ax::SpotLight::setInnerAngle)
        .member_function("getInnerAngle", &ax::SpotLight::getInnerAngle)
        .member_function("getCosInnerAngle", &ax::SpotLight::getCosInnerAngle)
        .member_function("setOuterAngle", &ax::SpotLight::setOuterAngle)
        .member_function("getOuterAngle", &ax::SpotLight::getOuterAngle)
        .member_function("getCosOuterAngle", &ax::SpotLight::getCosOuterAngle)
        .static_function("create", &ax::SpotLight::create)
        .auto_wrap_objects(true);
    mod.class_("SpotLight", class_SpotLight);
}
static void js_register_ax_base_AmbientLight(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::AmbientLight> class_AmbientLight(isolate);
    class_AmbientLight.ctor([]() { return new ax::AmbientLight(); })
        .template inherit<ax::BaseLight>()
        .static_function("create", &ax::AmbientLight::create)
        .auto_wrap_objects(true);
    mod.class_("AmbientLight", class_AmbientLight);
}
static void js_register_ax_base_RenderState(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::RenderState> class_RenderState(isolate);
    class_RenderState.template inherit<ax::Object>()
        .member_function("getName", &ax::RenderState::getName)
        .member_function("bindPass", &ax::RenderState::bindPass)
        .auto_wrap_objects(true);
    mod.class_("RenderState", class_RenderState);
}
static void js_register_ax_base_Technique(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Technique> class_Technique(isolate);
    class_Technique.template inherit<ax::Object>()
        .member_function("addPass", &ax::Technique::addPass)
        .member_function("getName", &ax::Technique::getName)
        .member_function("getPassByIndex", &ax::Technique::getPassByIndex)
        .member_function("getPassCount", &ax::Technique::getPassCount)
        .member_function("getPasses", &ax::Technique::getPasses)
        .member_function("clone", &ax::Technique::clone)
        .member_function("setMaterial", &ax::Technique::setMaterial)
        .static_function("createWithProgramState", &ax::Technique::createWithProgramState)
        .static_function("create", &ax::Technique::create)
        .auto_wrap_objects(true);
    mod.class_("Technique", class_Technique);
}
static void js_register_ax_base_Material(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Material> class_Material(isolate);
    class_Material.template inherit<ax::Object>()
        .member_function("draw", &ax::Material::draw)
        .member_function("getName", &ax::Material::getName)
        .member_function("setName", &ax::Material::setName)
        .member_function("getTechniqueByName", &ax::Material::getTechniqueByName)
        .member_function("getTechniqueByIndex", &ax::Material::getTechniqueByIndex)
        .member_function("getTechnique", &ax::Material::getTechnique)
        .member_function("getTechniques", &ax::Material::getTechniques)
        .member_function("getTechniqueCount", &ax::Material::getTechniqueCount)
        .member_function("addTechnique", &ax::Material::addTechnique)
        .member_function("setTechnique", &ax::Material::setTechnique)
        .member_function("clone", &ax::Material::clone)
        .member_function("getRenderState", &ax::Material::getRenderState)
        .member_function("setPrimitiveType", &ax::Material::setPrimitiveType)
        .member_function("getPrimitiveType", &ax::Material::getPrimitiveType)
        .member_function("setTransparent", &ax::Material::setTransparent)
        .member_function("isTransparent", &ax::Material::isTransparent)
        .member_function("setForce2DQueue", &ax::Material::setForce2DQueue)
        .member_function("isForce2DQueue", &ax::Material::isForce2DQueue)
        .static_function("createWithFilename", &ax::Material::createWithFilename)
        .static_function("createWithProgramState", &ax::Material::createWithProgramState)
        .static_function("createWithProperties", &ax::Material::createWithProperties)
        .auto_wrap_objects(true);
    mod.class_("Material", class_Material);
}
static void js_register_ax_base_Pass(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Pass> class_Pass(isolate);
    class_Pass.template inherit<ax::Object>()
        .member_function("getProgramState", &ax::Pass::getProgramState)
        .member_function("draw", &ax::Pass::draw)
        .member_function("setVertexInputBinding", &ax::Pass::setVertexInputBinding)
        .member_function("getVertexAttributeBinding", &ax::Pass::getVertexAttributeBinding)
        .member_function("setName", &ax::Pass::setName)
        .member_function("getName", &ax::Pass::getName)
        .member_function("clone", &ax::Pass::clone)
        .member_function("setTechnique", &ax::Pass::setTechnique)
        .member_function("updateMVPUniform", &ax::Pass::updateMVPUniform)
        .member_function("setUniformTexture", &ax::Pass::setUniformTexture)
        .member_function("setUniformNormTexture", &ax::Pass::setUniformNormTexture)
        .member_function("setUniformColor", &ax::Pass::setUniformColor)
        .member_function("setUniformMatrixPalette", &ax::Pass::setUniformMatrixPalette)
        .member_function("setUniformDirLightColor", &ax::Pass::setUniformDirLightColor)
        .member_function("setUniformDirLightDir", &ax::Pass::setUniformDirLightDir)
        .member_function("setUniformPointLightColor", &ax::Pass::setUniformPointLightColor)
        .member_function("setUniformPointLightPosition", &ax::Pass::setUniformPointLightPosition)
        .member_function("setUniformPointLightRangeInverse", &ax::Pass::setUniformPointLightRangeInverse)
        .member_function("setUniformSpotLightColor", &ax::Pass::setUniformSpotLightColor)
        .member_function("setUniformSpotLightPosition", &ax::Pass::setUniformSpotLightPosition)
        .member_function("setUniformSpotLightDir", &ax::Pass::setUniformSpotLightDir)
        .member_function("setUniformSpotLightInnerAngleCos", &ax::Pass::setUniformSpotLightInnerAngleCos)
        .member_function("setUniformSpotLightOuterAngleCos", &ax::Pass::setUniformSpotLightOuterAngleCos)
        .member_function("setUniformSpotLightRangeInverse", &ax::Pass::setUniformSpotLightRangeInverse)
        .member_function("setUniformAmbientLigthColor", &ax::Pass::setUniformAmbientLigthColor)
        .static_function("createWithProgramState", &ax::Pass::createWithProgramState)
        .static_function("create", &ax::Pass::create)
        .auto_wrap_objects(true);
    mod.class_("Pass", class_Pass);
}
static void js_register_ax_base_ProgramManager(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ProgramManager> class_ProgramManager(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_ProgramManager.member_function("getBuiltinProgram", &ax::ProgramManager::getBuiltinProgram)
        .member_function(
            "registerCustomProgram",
            [](ax::ProgramManager* self, std::string_view arg0, std::string_view arg1) { return self->registerCustomProgram(arg0, arg1); },
            [](ax::ProgramManager* self, std::string_view arg0, std::string_view arg1, ax::rhi::VertexLayoutKind arg2)
            { return self->registerCustomProgram(arg0, arg1, arg2); },
            [](ax::ProgramManager* self, std::string_view arg0, std::string_view arg1, ax::rhi::VertexLayoutKind arg2, bool arg3)
            { return self->registerCustomProgram(arg0, arg1, arg2, arg3); })
        .member_function(
            "loadProgram",
            [](ax::ProgramManager* self, std::string_view arg0, std::string_view arg1) { return self->loadProgram(arg0, arg1); },
            [](ax::ProgramManager* self, std::string_view arg0, std::string_view arg1, ax::rhi::VertexLayoutKind arg2)
            { return self->loadProgram(arg0, arg1, arg2); },
            [](ax::ProgramManager* self, unsigned long long arg0) { return self->loadProgram(arg0); })
        .member_function("unloadProgram", &ax::ProgramManager::unloadProgram)
        .member_function("unloadUnusedPrograms", &ax::ProgramManager::unloadUnusedPrograms)
        .member_function("unloadAllPrograms", &ax::ProgramManager::unloadAllPrograms)
        .static_function("getInstance", &ax::ProgramManager::getInstance)
        .static_function("destroyInstance", &ax::ProgramManager::destroyInstance)
        .static_function("chooseSpriteProgramType", &ax::ProgramManager::chooseSpriteProgramType)
        .auto_wrap_objects(true);
    mod.class_("ProgramManager", class_ProgramManager);
}
static void js_register_ax_base_Renderer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Renderer> class_Renderer(isolate);
    class_Renderer.ctor([]() { return new ax::Renderer(); })
        .member_function("init", &ax::Renderer::init)
        .member_function(
            "addCallbackCommand",
            [](ax::Renderer* self, std::function<void()> arg0) { self->addCallbackCommand(arg0); },
            [](ax::Renderer* self, std::function<void()> arg0, float arg1) { self->addCallbackCommand(arg0, arg1); })
        .member_function(
            "addCommand",
            [](ax::Renderer* self, ax::RenderCommand* arg0, int arg1) { self->addCommand(arg0, arg1); },
            [](ax::Renderer* self, ax::RenderCommand* arg0) { self->addCommand(arg0); })
        .member_function("getNextGroupCommand", &ax::Renderer::getNextGroupCommand)
        .member_function("pushGroup", &ax::Renderer::pushGroup)
        .member_function("popGroup", &ax::Renderer::popGroup)
        .member_function("createRenderQueue", &ax::Renderer::createRenderQueue)
        .member_function("render", &ax::Renderer::render)
        .member_function("clean", &ax::Renderer::clean)
        .member_function("getDrawnBatches", &ax::Renderer::getDrawnBatches)
        .member_function("addDrawnBatches", &ax::Renderer::addDrawnBatches)
        .member_function("getDrawnVertices", &ax::Renderer::getDrawnVertices)
        .member_function("addDrawnVertices", &ax::Renderer::addDrawnVertices)
        .member_function("clearDrawStats", &ax::Renderer::clearDrawStats)
        .member_function("getRenderTarget", &ax::Renderer::getRenderTarget)
        .member_function("setRenderTarget", &ax::Renderer::setRenderTarget)
        .member_function("getDefaultRenderTarget", &ax::Renderer::getDefaultRenderTarget)
        .member_function("getOffscreenRenderTarget", &ax::Renderer::getOffscreenRenderTarget)
        .member_function("clear", &ax::Renderer::clear)
        .member_function("getClearColor", &ax::Renderer::getClearColor)
        .member_function("getClearDepth", &ax::Renderer::getClearDepth)
        .member_function("getClearStencil", &ax::Renderer::getClearStencil)
        .member_function("getClearFlag", &ax::Renderer::getClearFlag)
        .member_function("setDepthTest", &ax::Renderer::setDepthTest)
        .member_function("setDepthWrite", &ax::Renderer::setDepthWrite)
        .member_function("setDepthCompareFunc", &ax::Renderer::setDepthCompareFunc)
        .member_function("getDepthTest", &ax::Renderer::getDepthTest)
        .member_function("getDepthWrite", &ax::Renderer::getDepthWrite)
        .member_function("getDepthCompareFunc", &ax::Renderer::getDepthCompareFunc)
        .member_function("setStencilTest", &ax::Renderer::setStencilTest)
        .member_function("setStencilCompareFunc", &ax::Renderer::setStencilCompareFunc)
        .member_function("setStencilOp", &ax::Renderer::setStencilOp)
        .member_function("setStencilWriteMask", &ax::Renderer::setStencilWriteMask)
        .member_function("getStencilTest", &ax::Renderer::getStencilTest)
        .member_function("getStencilFailureOp", &ax::Renderer::getStencilFailureOp)
        .member_function("getStencilPassDepthFailureOp", &ax::Renderer::getStencilPassDepthFailureOp)
        .member_function("getStencilDepthPassOp", &ax::Renderer::getStencilDepthPassOp)
        .member_function("getStencilCompareFunc", &ax::Renderer::getStencilCompareFunc)
        .member_function("getStencilReadMask", &ax::Renderer::getStencilReadMask)
        .member_function("getStencilWriteMask", &ax::Renderer::getStencilWriteMask)
        .member_function("getStencilReferenceValue", &ax::Renderer::getStencilReferenceValue)
        .member_function("setCullMode", &ax::Renderer::setCullMode)
        .member_function("getCullMode", &ax::Renderer::getCullMode)
        .member_function("setWinding", &ax::Renderer::setWinding)
        .member_function("getWinding", &ax::Renderer::getWinding)
        .member_function("setViewport", &ax::Renderer::setViewport)
        .member_function("getViewport", &ax::Renderer::getViewport)
        .member_function("setScissorTest", &ax::Renderer::setScissorTest)
        .member_function("setScissorRect", &ax::Renderer::setScissorRect)
        .member_function("getScissorTest", &ax::Renderer::getScissorTest)
        .member_function("getScissorRect", &ax::Renderer::getScissorRect)
        .member_function("checkVisibility", &ax::Renderer::checkVisibility)
        .member_function("readPixels", &ax::Renderer::readPixels)
        .member_function("beginRenderPass", &ax::Renderer::beginRenderPass)
        .member_function("endRenderPass", &ax::Renderer::endRenderPass)
        .member_function("nextCallbackCommand", &ax::Renderer::nextCallbackCommand)
        .auto_wrap_objects(true);
    mod.class_("Renderer", class_Renderer);
}
static void js_register_ax_base_TextureCache(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TextureCache> class_TextureCache(isolate);
    class_TextureCache.ctor([]() { return new ax::TextureCache(); })
        .template inherit<ax::Object>()
        .member_function("getDescription", &ax::TextureCache::getDescription)
        .member_function(
            "getWhiteTexture",
            [](ax::TextureCache* self, std::string_view arg0, uint16_t arg1) { return self->getWhiteTexture(arg0, arg1); },
            [](ax::TextureCache* self) { return self->getWhiteTexture(); })
        .member_function("getDummyTexture", &ax::TextureCache::getDummyTexture)
        .member_function(
            "addImage",
            [](ax::TextureCache* self, std::string_view arg0, ax::rhi::PixelFormat arg1) { return self->addImage(arg0, arg1); },
            [](ax::TextureCache* self, std::string_view arg0, ax::rhi::PixelFormat arg1, bool arg2)
            { return self->addImage(arg0, arg1, arg2); },
            [](ax::TextureCache* self, std::string_view arg0) { return self->addImage(arg0); },
            [](ax::TextureCache* self, std::string_view arg0, bool arg1) { return self->addImage(arg0, arg1); },
            [](ax::TextureCache* self, ax::Image* arg0, std::string_view arg1) { return self->addImage(arg0, arg1); },
            [](ax::TextureCache* self, ax::Image* arg0, std::string_view arg1, ax::rhi::PixelFormat arg2)
            { return self->addImage(arg0, arg1, arg2); },
            [](ax::TextureCache* self, ax::Data arg0, std::string_view arg1) { return self->addImage(arg0, arg1); })
        .member_function("unbindImageAsync", &ax::TextureCache::unbindImageAsync)
        .member_function("unbindAllImageAsync", &ax::TextureCache::unbindAllImageAsync)
        .member_function("getTextureForKey", &ax::TextureCache::getTextureForKey)
        .member_function("reloadTexture", &ax::TextureCache::reloadTexture)
        .member_function("removeAllTextures", &ax::TextureCache::removeAllTextures)
        .member_function("removeUnusedTextures", &ax::TextureCache::removeUnusedTextures)
        .member_function("removeTexture", &ax::TextureCache::removeTexture)
        .member_function("removeTextureForKey", &ax::TextureCache::removeTextureForKey)
        .member_function("getCachedTextureInfo", &ax::TextureCache::getCachedTextureInfo)
        .member_function("waitForQuit", &ax::TextureCache::waitForQuit)
        .member_function("getTextureFilePath", &ax::TextureCache::getTextureFilePath)
        .member_function("renameTextureWithKey", &ax::TextureCache::renameTextureWithKey)
        .static_function("setETC1AlphaFileSuffix", &ax::TextureCache::setETC1AlphaFileSuffix)
        .static_function("getETC1AlphaFileSuffix", &ax::TextureCache::getETC1AlphaFileSuffix)
        .static_function("checkETC1AlphaFile", &ax::TextureCache::checkETC1AlphaFile)
        .auto_wrap_objects(true);
    mod.class_("TextureCache", class_TextureCache);
}
static void js_register_ax_base_Device(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Device> class_Device(isolate,
                                          [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_Device.static_function("getDPI", &ax::Device::getDPI)
        .static_function("getPixelRatio", &ax::Device::getPixelRatio)
        .static_function("setAccelerometerEnabled", &ax::Device::setAccelerometerEnabled)
        .static_function("setAccelerometerInterval", &ax::Device::setAccelerometerInterval)
        .static_function("setKeepScreenOn", &ax::Device::setKeepScreenOn)
        .static_function("vibrate", &ax::Device::vibrate)
        .static_function("prepareImpactFeedbackGenerator", &ax::Device::prepareImpactFeedbackGenerator)
        .static_function("impactOccurred", &ax::Device::impactOccurred)
        .static_function("prepareNotificationFeedbackGenerator", &ax::Device::prepareNotificationFeedbackGenerator)
        .static_function("notificationOccurred", &ax::Device::notificationOccurred)
        .static_function("prepareSelectionFeedbackGenerator", &ax::Device::prepareSelectionFeedbackGenerator)
        .static_function("selectionChanged", &ax::Device::selectionChanged)
        .static_function("setPreferredOrientation", &ax::Device::setPreferredOrientation)
        .static_function("getPreferredOrientation", &ax::Device::getPreferredOrientation)
        .static_function("getSupportedOrientations", &ax::Device::getSupportedOrientations)
        .static_function("getCurrentOrientation", &ax::Device::getCurrentOrientation)
        .static_function("getPhysicalOrientation", &ax::Device::getPhysicalOrientation)
        .static_function("resolveOrientation", &ax::Device::resolveOrientation)
        .static_function("getDisplayRefreshRate", &ax::Device::getDisplayRefreshRate)
        .auto_wrap_objects(true);
    mod.class_("Device", class_Device);
}
static void js_register_ax_base_Application(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Application> class_Application(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_Application.member_function("setAnimationInterval", &ax::Application::setAnimationInterval)
        .member_function("getCurrentLanguage", &ax::Application::getCurrentLanguage)
        .member_function("getCurrentLanguageCode", &ax::Application::getCurrentLanguageCode)
        .member_function("getTargetPlatform", &ax::Application::getTargetPlatform)
        .member_function("getVersion", &ax::Application::getVersion)
        .member_function("openURL", &ax::Application::openURL)
        .static_function("getInstance", &ax::Application::getInstance)
        .auto_wrap_objects(true);
    mod.class_("Application", class_Application);
}
static void js_register_ax_base_RenderViewImpl(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::RenderViewImpl> class_RenderViewImpl(isolate);
    class_RenderViewImpl.template inherit<ax::RenderView>()
        .static_function(
            "createWithRect",
            [](std::string_view arg0, ax::Rect arg1) { return ax::RenderViewImpl::createWithRect(arg0, arg1); },
            [](std::string_view arg0, ax::Rect arg1, float arg2) { return ax::RenderViewImpl::createWithRect(arg0, arg1, arg2); },
            [](std::string_view arg0, ax::Rect arg1, float arg2, bool arg3)
            { return ax::RenderViewImpl::createWithRect(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("RenderViewImpl", class_RenderViewImpl);
}
static void js_register_ax_base_AnimationCache(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::AnimationCache> class_AnimationCache(isolate);
    class_AnimationCache.ctor([]() { return new ax::AnimationCache(); })
        .member_function("init", &ax::AnimationCache::init)
        .member_function("addAnimation", &ax::AnimationCache::addAnimation)
        .member_function("removeAnimation", &ax::AnimationCache::removeAnimation)
        .member_function("getAnimation", &ax::AnimationCache::getAnimation)
        .member_function("addAnimationsWithDictionary", &ax::AnimationCache::addAnimationsWithDictionary)
        .member_function("addAnimations", &ax::AnimationCache::addAnimationsWithFile)
        .static_function("getInstance", &ax::AnimationCache::getInstance)
        .static_function("destroyInstance", &ax::AnimationCache::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("AnimationCache", class_AnimationCache);
}
static void js_register_ax_base_SpriteBatchNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::SpriteBatchNode> class_SpriteBatchNode(isolate);
    class_SpriteBatchNode.ctor([]() { return new ax::SpriteBatchNode(); })
        .template inherit<ax::Node>()
        .member_function("getTextureAtlas", &ax::SpriteBatchNode::getTextureAtlas)
        .member_function("setTextureAtlas", &ax::SpriteBatchNode::setTextureAtlas)
        .member_function("increaseAtlasCapacity", &ax::SpriteBatchNode::increaseAtlasCapacity)
        .member_function("removeChildAtIndex", &ax::SpriteBatchNode::removeChildAtIndex)
        .member_function("appendChild", &ax::SpriteBatchNode::appendChild)
        .member_function("removeSpriteFromAtlas", &ax::SpriteBatchNode::removeSpriteFromAtlas)
        .member_function("rebuildIndexInOrder", &ax::SpriteBatchNode::rebuildIndexInOrder)
        .member_function("highestAtlasIndexInChild", &ax::SpriteBatchNode::highestAtlasIndexInChild)
        .member_function("lowestAtlasIndexInChild", &ax::SpriteBatchNode::lowestAtlasIndexInChild)
        .member_function("atlasIndexForChild", &ax::SpriteBatchNode::atlasIndexForChild)
        .member_function("reorderBatch", &ax::SpriteBatchNode::reorderBatch)
        .member_function("getTexture", &ax::SpriteBatchNode::getTexture)
        .member_function("setTexture", &ax::SpriteBatchNode::setTexture)
        .member_function("setBlendFunc", &ax::SpriteBatchNode::setBlendFunc)
        .member_function("getBlendFunc", &ax::SpriteBatchNode::getBlendFunc)
        .member_function("removeAllChildrenWithCleanup", &ax::SpriteBatchNode::removeAllChildrenWithCleanup)
        .member_function("insertQuadFromSprite", &ax::SpriteBatchNode::insertQuadFromSprite)
        .member_function("addSpriteWithoutQuad", &ax::SpriteBatchNode::addSpriteWithoutQuad)
        .member_function("reserveCapacity", &ax::SpriteBatchNode::reserveCapacity)
        .member_function(
            "initWithTexture",
            [](ax::SpriteBatchNode* self, ax::Texture2D* arg0) { return self->initWithTexture(arg0); },
            [](ax::SpriteBatchNode* self, ax::Texture2D* arg0, ssize_t arg1) { return self->initWithTexture(arg0, arg1); })
        .member_function(
            "initWithFile",
            [](ax::SpriteBatchNode* self, std::string_view arg0) { return self->initWithFile(arg0); },
            [](ax::SpriteBatchNode* self, std::string_view arg0, ssize_t arg1) { return self->initWithFile(arg0, arg1); })
        .static_function(
            "createWithTexture",
            [](ax::Texture2D* arg0) { return ax::SpriteBatchNode::createWithTexture(arg0); },
            [](ax::Texture2D* arg0, ssize_t arg1) { return ax::SpriteBatchNode::createWithTexture(arg0, arg1); })
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::SpriteBatchNode::create(arg0); },
            [](std::string_view arg0, ssize_t arg1) { return ax::SpriteBatchNode::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("SpriteBatchNode", class_SpriteBatchNode);
}
static void js_register_ax_base_ParallaxNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ParallaxNode> class_ParallaxNode(isolate);
    class_ParallaxNode.ctor([]() { return new ax::ParallaxNode(); })
        .template inherit<ax::Node>()
        .member_function("removeAllChildrenWithCleanup", &ax::ParallaxNode::removeAllChildrenWithCleanup)
        .static_function("create", &ax::ParallaxNode::create)
        .auto_wrap_objects(true);
    mod.class_("ParallaxNode", class_ParallaxNode);
}
static void js_register_ax_base_TMXObjectGroup(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TMXObjectGroup> class_TMXObjectGroup(isolate);
    class_TMXObjectGroup.ctor([]() { return new ax::TMXObjectGroup(); })
        .template inherit<ax::Object>()
        .member_function("getGroupName", &ax::TMXObjectGroup::getGroupName)
        .member_function("setGroupName", &ax::TMXObjectGroup::setGroupName)
        .member_function("getProperty", &ax::TMXObjectGroup::getProperty)
        .member_function("getObject", &ax::TMXObjectGroup::getObject)
        .member_function("getPositionOffset", &ax::TMXObjectGroup::getPositionOffset)
        .member_function("setPositionOffset", &ax::TMXObjectGroup::setPositionOffset)
        .member_function(
            "getProperties",
            [](ax::TMXObjectGroup* self) { return self->getProperties(); },
            [](ax::TMXObjectGroup* self) { return self->getProperties(); })
        .member_function("setProperties", &ax::TMXObjectGroup::setProperties)
        .member_function(
            "getObjects",
            [](ax::TMXObjectGroup* self) { return self->getObjects(); },
            [](ax::TMXObjectGroup* self) { return self->getObjects(); })
        .member_function("setObjects", &ax::TMXObjectGroup::setObjects)
        .auto_wrap_objects(true);
    mod.class_("TMXObjectGroup", class_TMXObjectGroup);
}
static void js_register_ax_base_TMXLayerInfo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TMXLayerInfo> class_TMXLayerInfo(isolate);
    class_TMXLayerInfo.ctor([]() { return new ax::TMXLayerInfo(); })
        .template inherit<ax::Object>()
        .member_function("setProperties", &ax::TMXLayerInfo::setProperties)
        .member_function("getProperties", &ax::TMXLayerInfo::getProperties)
        .auto_wrap_objects(true);
    mod.class_("TMXLayerInfo", class_TMXLayerInfo);
}
static void js_register_ax_base_TMXTilesetInfo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TMXTilesetInfo> class_TMXTilesetInfo(isolate);
    class_TMXTilesetInfo.ctor([]() { return new ax::TMXTilesetInfo(); })
        .template inherit<ax::Object>()
        .member_function("getRectForGID", &ax::TMXTilesetInfo::getRectForGID)
        .auto_wrap_objects(true);
    mod.class_("TMXTilesetInfo", class_TMXTilesetInfo);
}
static void js_register_ax_base_TMXMapInfo(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TMXMapInfo> class_TMXMapInfo(isolate);
    class_TMXMapInfo.ctor([]() { return new ax::TMXMapInfo(); })
        .member_function("initWithTMXFile", &ax::TMXMapInfo::initWithTMXFile)
        .member_function("initWithXML", &ax::TMXMapInfo::initWithXML)
        .member_function("parseXMLFile", &ax::TMXMapInfo::parseXMLFile)
        .member_function("parseXMLString", &ax::TMXMapInfo::parseXMLString)
        .member_function("getTileProperties", &ax::TMXMapInfo::getTileProperties)
        .member_function("setTileProperties", &ax::TMXMapInfo::setTileProperties)
        .member_function("getOrientation", &ax::TMXMapInfo::getOrientation)
        .member_function("setOrientation", &ax::TMXMapInfo::setOrientation)
        .member_function("getStaggerAxis", &ax::TMXMapInfo::getStaggerAxis)
        .member_function("setStaggerAxis", &ax::TMXMapInfo::setStaggerAxis)
        .member_function("getStaggerIndex", &ax::TMXMapInfo::getStaggerIndex)
        .member_function("setStaggerIndex", &ax::TMXMapInfo::setStaggerIndex)
        .member_function("getHexSideLength", &ax::TMXMapInfo::getHexSideLength)
        .member_function("setHexSideLength", &ax::TMXMapInfo::setHexSideLength)
        .member_function("getMapSize", &ax::TMXMapInfo::getMapSize)
        .member_function("setMapSize", &ax::TMXMapInfo::setMapSize)
        .member_function("getTileSize", &ax::TMXMapInfo::getTileSize)
        .member_function("setTileSize", &ax::TMXMapInfo::setTileSize)
        .member_function(
            "getLayers", [](ax::TMXMapInfo* self) { return self->getLayers(); }, [](ax::TMXMapInfo* self) { return self->getLayers(); })
        .member_function("setLayers", &ax::TMXMapInfo::setLayers)
        .member_function(
            "getTilesets",
            [](ax::TMXMapInfo* self) { return self->getTilesets(); },
            [](ax::TMXMapInfo* self) { return self->getTilesets(); })
        .member_function("setTilesets", &ax::TMXMapInfo::setTilesets)
        .member_function(
            "getObjectGroups",
            [](ax::TMXMapInfo* self) { return self->getObjectGroups(); },
            [](ax::TMXMapInfo* self) { return self->getObjectGroups(); })
        .member_function("setObjectGroups", &ax::TMXMapInfo::setObjectGroups)
        .member_function("getParentElement", &ax::TMXMapInfo::getParentElement)
        .member_function("setParentElement", &ax::TMXMapInfo::setParentElement)
        .member_function("getParentGID", &ax::TMXMapInfo::getParentGID)
        .member_function("setParentGID", &ax::TMXMapInfo::setParentGID)
        .member_function("getLayerAttribs", &ax::TMXMapInfo::getLayerAttribs)
        .member_function("setLayerAttribs", &ax::TMXMapInfo::setLayerAttribs)
        .member_function("isStoringCharacters", &ax::TMXMapInfo::isStoringCharacters)
        .member_function("setStoringCharacters", &ax::TMXMapInfo::setStoringCharacters)
        .member_function(
            "getProperties",
            [](ax::TMXMapInfo* self) { return self->getProperties(); },
            [](ax::TMXMapInfo* self) { return self->getProperties(); })
        .member_function("setProperties", &ax::TMXMapInfo::setProperties)
        .member_function("getCurrentString", &ax::TMXMapInfo::getCurrentString)
        .member_function("setCurrentString", &ax::TMXMapInfo::setCurrentString)
        .member_function("getTMXFileName", &ax::TMXMapInfo::getTMXFileName)
        .member_function("setTMXFileName", &ax::TMXMapInfo::setTMXFileName)
        .member_function("getExternalTilesetFileName", &ax::TMXMapInfo::getExternalTilesetFileName)
        .static_function("create", &ax::TMXMapInfo::create)
        .static_function("createWithXML", &ax::TMXMapInfo::createWithXML)
        .auto_wrap_objects(true);
    mod.class_("TMXMapInfo", class_TMXMapInfo);
}
static void js_register_ax_base_TileMapAtlas(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TileMapAtlas> class_TileMapAtlas(isolate);
    class_TileMapAtlas.ctor([]() { return new ax::TileMapAtlas(); })
        .template inherit<ax::AtlasNode>()
        .member_function("initWithTileFile", &ax::TileMapAtlas::initWithTileFile)
        .member_function("getTileAt", &ax::TileMapAtlas::getTileAt)
        .member_function("setTile", &ax::TileMapAtlas::setTile)
        .member_function("releaseMap", &ax::TileMapAtlas::releaseMap)
        .static_function("create", &ax::TileMapAtlas::create)
        .auto_wrap_objects(true);
    mod.class_("TileMapAtlas", class_TileMapAtlas);
}
static void js_register_ax_base_FastTMXLayer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FastTMXLayer> class_FastTMXLayer(isolate);
    class_FastTMXLayer.ctor([]() { return new ax::FastTMXLayer(); })
        .template inherit<ax::Node>()
        .member_function(
            "setTileGID",
            [](ax::FastTMXLayer* self, int arg0, ax::Vec2 arg1, ax::TMXTileFlags_ arg2) { self->setTileGID(arg0, arg1, arg2); },
            [](ax::FastTMXLayer* self, int arg0, ax::Vec2 arg1) { self->setTileGID(arg0, arg1); })
        .member_function("removeTileAt", &ax::FastTMXLayer::removeTileAt)
        .member_function("getPositionAt", &ax::FastTMXLayer::getPositionAt)
        .member_function("getProperty", &ax::FastTMXLayer::getProperty)
        .member_function("setupTiles", &ax::FastTMXLayer::setupTiles)
        .member_function("getLayerName", &ax::FastTMXLayer::getLayerName)
        .member_function("setLayerName", &ax::FastTMXLayer::setLayerName)
        .member_function("getLayerSize", &ax::FastTMXLayer::getLayerSize)
        .member_function("setLayerSize", &ax::FastTMXLayer::setLayerSize)
        .member_function("getMapTileSize", &ax::FastTMXLayer::getMapTileSize)
        .member_function("setMapTileSize", &ax::FastTMXLayer::setMapTileSize)
        .member_function("getTileSet", &ax::FastTMXLayer::getTileSet)
        .member_function("setTileSet", &ax::FastTMXLayer::setTileSet)
        .member_function("getLayerOrientation", &ax::FastTMXLayer::getLayerOrientation)
        .member_function("setLayerOrientation", &ax::FastTMXLayer::setLayerOrientation)
        .member_function(
            "getProperties",
            [](ax::FastTMXLayer* self) { return self->getProperties(); },
            [](ax::FastTMXLayer* self) { return self->getProperties(); })
        .member_function("setProperties", &ax::FastTMXLayer::setProperties)
        .member_function("getTileAt", &ax::FastTMXLayer::getTileAt)
        .member_function("setupTileSprite", &ax::FastTMXLayer::setupTileSprite)
        .member_function("hasTileAnimation", &ax::FastTMXLayer::hasTileAnimation)
        .member_function("getTileAnimManager", &ax::FastTMXLayer::getTileAnimManager)
        .member_function("initWithTilesetInfo", &ax::FastTMXLayer::initWithTilesetInfo)
        .static_function("create", &ax::FastTMXLayer::create)
        .auto_wrap_objects(true);
    mod.class_("FastTMXLayer", class_FastTMXLayer);
}
static void js_register_ax_base_TMXTileAnimTask(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TMXTileAnimTask> class_TMXTileAnimTask(isolate);
    class_TMXTileAnimTask
        .ctor([](ax::FastTMXLayer* arg0, ax::TMXTileAnimInfo* arg1, ax::Vec2 arg2) { return new ax::TMXTileAnimTask(arg0, arg1, arg2); },
              [](ax::FastTMXLayer* arg0, ax::TMXTileAnimInfo* arg1, ax::Vec2 arg2, unsigned int arg3)
              { return new ax::TMXTileAnimTask(arg0, arg1, arg2, arg3); })
        .template inherit<ax::Object>()
        .member_function("start", &ax::TMXTileAnimTask::start)
        .member_function("stop", &ax::TMXTileAnimTask::stop)
        .member_function("isRunning", &ax::TMXTileAnimTask::isRunning)
        .static_function(
            "create",
            [](ax::FastTMXLayer* arg0, ax::TMXTileAnimInfo* arg1, ax::Vec2 arg2) { return ax::TMXTileAnimTask::create(arg0, arg1, arg2); },
            [](ax::FastTMXLayer* arg0, ax::TMXTileAnimInfo* arg1, ax::Vec2 arg2, unsigned int arg3)
            { return ax::TMXTileAnimTask::create(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("TMXTileAnimTask", class_TMXTileAnimTask);
}
static void js_register_ax_base_TMXTileAnimManager(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TMXTileAnimManager> class_TMXTileAnimManager(isolate);
    class_TMXTileAnimManager.ctor([](ax::FastTMXLayer* arg0) { return new ax::TMXTileAnimManager(arg0); })
        .template inherit<ax::Object>()
        .member_function("startAll", &ax::TMXTileAnimManager::startAll)
        .member_function("stopAll", &ax::TMXTileAnimManager::stopAll)
        .member_function("getTasks", &ax::TMXTileAnimManager::getTasks)
        .static_function("create", &ax::TMXTileAnimManager::create)
        .auto_wrap_objects(true);
    mod.class_("TMXTileAnimManager", class_TMXTileAnimManager);
}
static void js_register_ax_base_FastTMXTiledMap(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::FastTMXTiledMap> class_FastTMXTiledMap(isolate);
    class_FastTMXTiledMap.ctor([]() { return new ax::FastTMXTiledMap(); })
        .template inherit<ax::Node>()
        .member_function("getLayer", &ax::FastTMXTiledMap::getLayer)
        .member_function("getObjectGroup", &ax::FastTMXTiledMap::getObjectGroup)
        .member_function("getProperty", &ax::FastTMXTiledMap::getProperty)
        .member_function("getPropertiesForGID", &ax::FastTMXTiledMap::getPropertiesForGID)
        .member_function("getMapSize", &ax::FastTMXTiledMap::getMapSize)
        .member_function("setMapSize", &ax::FastTMXTiledMap::setMapSize)
        .member_function("getTileSize", &ax::FastTMXTiledMap::getTileSize)
        .member_function("setTileSize", &ax::FastTMXTiledMap::setTileSize)
        .member_function("getMapOrientation", &ax::FastTMXTiledMap::getMapOrientation)
        .member_function("setMapOrientation", &ax::FastTMXTiledMap::setMapOrientation)
        .member_function(
            "getObjectGroups",
            [](ax::FastTMXTiledMap* self) { return self->getObjectGroups(); },
            [](ax::FastTMXTiledMap* self) { return self->getObjectGroups(); })
        .member_function("setObjectGroups", &ax::FastTMXTiledMap::setObjectGroups)
        .member_function("getProperties", &ax::FastTMXTiledMap::getProperties)
        .member_function("setProperties", &ax::FastTMXTiledMap::setProperties)
        .member_function("setTileAnimEnabled", &ax::FastTMXTiledMap::setTileAnimEnabled)
        .member_function("getLayerCount", &ax::FastTMXTiledMap::getLayerCount)
        .member_function("getResourceFile", &ax::FastTMXTiledMap::getResourceFile)
        .member_function("getMapInfo", &ax::FastTMXTiledMap::getMapInfo)
        .member_function("getTilesetInfo", &ax::FastTMXTiledMap::getTilesetInfo)
        .member_function("getLayers", &ax::FastTMXTiledMap::getLayers)
        .member_function(
            "initWithTMXFile",
            [](ax::FastTMXTiledMap* self, std::string_view arg0) { return self->initWithTMXFile(arg0); },
            [](ax::FastTMXTiledMap* self, std::string_view arg0, bool arg1) { return self->initWithTMXFile(arg0, arg1); })
        .member_function(
            "initWithXML",
            [](ax::FastTMXTiledMap* self, std::string_view arg0, std::string_view arg1) { return self->initWithXML(arg0, arg1); },
            [](ax::FastTMXTiledMap* self, std::string_view arg0, std::string_view arg1, bool arg2)
            { return self->initWithXML(arg0, arg1, arg2); })
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::FastTMXTiledMap::create(arg0); },
            [](std::string_view arg0, bool arg1) { return ax::FastTMXTiledMap::create(arg0, arg1); })
        .static_function(
            "createWithXML",
            [](std::string_view arg0, std::string_view arg1) { return ax::FastTMXTiledMap::createWithXML(arg0, arg1); },
            [](std::string_view arg0, std::string_view arg1, bool arg2) { return ax::FastTMXTiledMap::createWithXML(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("FastTMXTiledMap", class_FastTMXTiledMap);
}
static void js_register_ax_base_MotionStreak3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MotionStreak3D> class_MotionStreak3D(isolate);
    class_MotionStreak3D.ctor([]() { return new ax::MotionStreak3D(); })
        .template inherit<ax::Node>()
        .member_function("tintWithColor", &ax::MotionStreak3D::tintWithColor)
        .member_function("reset", &ax::MotionStreak3D::reset)
        .member_function("getStroke", &ax::MotionStreak3D::getStroke)
        .member_function("setStroke", &ax::MotionStreak3D::setStroke)
        .member_function("isStartingPositionInitialized", &ax::MotionStreak3D::isStartingPositionInitialized)
        .member_function("setStartingPositionInitialized", &ax::MotionStreak3D::setStartingPositionInitialized)
        .member_function("getTexture", &ax::MotionStreak3D::getTexture)
        .member_function("setTexture", &ax::MotionStreak3D::setTexture)
        .member_function("setBlendFunc", &ax::MotionStreak3D::setBlendFunc)
        .member_function("getBlendFunc", &ax::MotionStreak3D::getBlendFunc)
        .member_function("setSweepAxis", &ax::MotionStreak3D::setSweepAxis)
        .member_function("getSweepAxis", &ax::MotionStreak3D::getSweepAxis)
        .member_function(
            "initWithFade",
            [](ax::MotionStreak3D* self, float arg0, float arg1, float arg2, ax::Color32 arg3, ax::Texture2D* arg4)
            { return self->initWithFade(arg0, arg1, arg2, arg3, arg4); },
            [](ax::MotionStreak3D* self, float arg0, float arg1, float arg2, ax::Color32 arg3, std::string_view arg4)
            { return self->initWithFade(arg0, arg1, arg2, arg3, arg4); })
        .static_function(
            "create",
            [](float arg0, float arg1, float arg2, ax::Color32 arg3, ax::Texture2D* arg4)
            { return ax::MotionStreak3D::create(arg0, arg1, arg2, arg3, arg4); },
            [](float arg0, float arg1, float arg2, ax::Color32 arg3, std::string_view arg4)
            { return ax::MotionStreak3D::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("MotionStreak3D", class_MotionStreak3D);
}
void js_register_all_ax_base(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_base_Object(mod);
    js_register_ax_base_Touch(mod);
    js_register_ax_base_Event(mod);
    js_register_ax_base_EventTouch(mod);
    js_register_ax_base_EventKeyboard(mod);
    js_register_ax_base_Action(mod);
    js_register_ax_base_FiniteTimeAction(mod);
    js_register_ax_base_Speed(mod);
    js_register_ax_base_Follow(mod);
    js_register_ax_base_ShaderCache(mod);
    js_register_ax_base_Texture2D(mod);
    js_register_ax_base_Component(mod);
    js_register_ax_base_Node(mod);
    js_register_ax_base_Image(mod);
    js_register_ax_base_PolygonInfo(mod);
    js_register_ax_base_AutoPolygon(mod);
    js_register_ax_base_SpriteFrame(mod);
    js_register_ax_base_AnimationFrame(mod);
    js_register_ax_base_Animation(mod);
    js_register_ax_base_ActionInterval(mod);
    js_register_ax_base_Sequence(mod);
    js_register_ax_base_Repeat(mod);
    js_register_ax_base_RepeatForever(mod);
    js_register_ax_base_Spawn(mod);
    js_register_ax_base_RotateTo(mod);
    js_register_ax_base_RotateBy(mod);
    js_register_ax_base_MoveBy(mod);
    js_register_ax_base_MoveTo(mod);
    js_register_ax_base_SkewTo(mod);
    js_register_ax_base_SkewBy(mod);
    js_register_ax_base_JumpBy(mod);
    js_register_ax_base_JumpTo(mod);
    js_register_ax_base_BezierBy(mod);
    js_register_ax_base_BezierTo(mod);
    js_register_ax_base_ScaleTo(mod);
    js_register_ax_base_ScaleBy(mod);
    js_register_ax_base_Blink(mod);
    js_register_ax_base_FadeTo(mod);
    js_register_ax_base_FadeIn(mod);
    js_register_ax_base_FadeOut(mod);
    js_register_ax_base_TintTo(mod);
    js_register_ax_base_TintBy(mod);
    js_register_ax_base_DelayTime(mod);
    js_register_ax_base_Animate(mod);
    js_register_ax_base_TargetedAction(mod);
    js_register_ax_base_Scene(mod);
    js_register_ax_base_RenderView(mod);
    js_register_ax_base_Director(mod);
    js_register_ax_base_Timer(mod);
    js_register_ax_base_Scheduler(mod);
    js_register_ax_base_UserDefault(mod);
    js_register_ax_base_FileUtils(mod);
    js_register_ax_base_EventAcceleration(mod);
    js_register_ax_base_EventCustom(mod);
    js_register_ax_base_EventDispatcher(mod);
    js_register_ax_base_EventFocus(mod);
    js_register_ax_base_EventMouse(mod);
    js_register_ax_base_EventController(mod);
    js_register_ax_base_ActionCamera(mod);
    js_register_ax_base_OrbitCamera(mod);
    js_register_ax_base_CardinalSplineTo(mod);
    js_register_ax_base_CardinalSplineBy(mod);
    js_register_ax_base_CatmullRomTo(mod);
    js_register_ax_base_CatmullRomBy(mod);
    js_register_ax_base_ActionEase(mod);
    js_register_ax_base_EaseRateAction(mod);
    js_register_ax_base_EaseExponentialIn(mod);
    js_register_ax_base_EaseExponentialOut(mod);
    js_register_ax_base_EaseExponentialInOut(mod);
    js_register_ax_base_EaseSineIn(mod);
    js_register_ax_base_EaseSineOut(mod);
    js_register_ax_base_EaseSineInOut(mod);
    js_register_ax_base_EaseBounce(mod);
    js_register_ax_base_EaseBounceIn(mod);
    js_register_ax_base_EaseBounceOut(mod);
    js_register_ax_base_EaseBounceInOut(mod);
    js_register_ax_base_EaseBackIn(mod);
    js_register_ax_base_EaseBackOut(mod);
    js_register_ax_base_EaseBackInOut(mod);
    js_register_ax_base_EaseQuadraticActionIn(mod);
    js_register_ax_base_EaseQuadraticActionOut(mod);
    js_register_ax_base_EaseQuadraticActionInOut(mod);
    js_register_ax_base_EaseQuarticActionIn(mod);
    js_register_ax_base_EaseQuarticActionOut(mod);
    js_register_ax_base_EaseQuarticActionInOut(mod);
    js_register_ax_base_EaseQuinticActionIn(mod);
    js_register_ax_base_EaseQuinticActionOut(mod);
    js_register_ax_base_EaseQuinticActionInOut(mod);
    js_register_ax_base_EaseCircleActionIn(mod);
    js_register_ax_base_EaseCircleActionOut(mod);
    js_register_ax_base_EaseCircleActionInOut(mod);
    js_register_ax_base_EaseCubicActionIn(mod);
    js_register_ax_base_EaseCubicActionOut(mod);
    js_register_ax_base_EaseCubicActionInOut(mod);
    js_register_ax_base_EaseIn(mod);
    js_register_ax_base_EaseOut(mod);
    js_register_ax_base_EaseInOut(mod);
    js_register_ax_base_EaseElastic(mod);
    js_register_ax_base_EaseElasticIn(mod);
    js_register_ax_base_EaseElasticOut(mod);
    js_register_ax_base_EaseElasticInOut(mod);
    js_register_ax_base_EaseBezierAction(mod);
    js_register_ax_base_ActionInstant(mod);
    js_register_ax_base_Show(mod);
    js_register_ax_base_Hide(mod);
    js_register_ax_base_ToggleVisibility(mod);
    js_register_ax_base_RemoveSelf(mod);
    js_register_ax_base_FlipX(mod);
    js_register_ax_base_FlipY(mod);
    js_register_ax_base_Place(mod);
    js_register_ax_base_CallFunc(mod);
    js_register_ax_base_GridAction(mod);
    js_register_ax_base_Grid3DAction(mod);
    js_register_ax_base_TiledGrid3DAction(mod);
    js_register_ax_base_StopGrid(mod);
    js_register_ax_base_ReuseGrid(mod);
    js_register_ax_base_Waves3D(mod);
    js_register_ax_base_FlipX3D(mod);
    js_register_ax_base_FlipY3D(mod);
    js_register_ax_base_Lens3D(mod);
    js_register_ax_base_Ripple3D(mod);
    js_register_ax_base_Shaky3D(mod);
    js_register_ax_base_Liquid(mod);
    js_register_ax_base_Waves(mod);
    js_register_ax_base_Twirl(mod);
    js_register_ax_base_ActionManager(mod);
    js_register_ax_base_PageTurn3D(mod);
    js_register_ax_base_ProgressTo(mod);
    js_register_ax_base_ProgressFromTo(mod);
    js_register_ax_base_ShakyTiles3D(mod);
    js_register_ax_base_ShatteredTiles3D(mod);
    js_register_ax_base_ShuffleTiles(mod);
    js_register_ax_base_FadeOutTRTiles(mod);
    js_register_ax_base_FadeOutBLTiles(mod);
    js_register_ax_base_FadeOutUpTiles(mod);
    js_register_ax_base_FadeOutDownTiles(mod);
    js_register_ax_base_TurnOffTiles(mod);
    js_register_ax_base_WavesTiles3D(mod);
    js_register_ax_base_JumpTiles3D(mod);
    js_register_ax_base_SplitRows(mod);
    js_register_ax_base_SplitCols(mod);
    js_register_ax_base_ActionTween(mod);
    js_register_ax_base_AtlasNode(mod);
    js_register_ax_base_ClippingNode(mod);
    js_register_ax_base_ClippingRectangleNode(mod);
    js_register_ax_base_DrawNode(mod);
    js_register_ax_base_Label(mod);
    js_register_ax_base_LabelAtlas(mod);
    js_register_ax_base_Sprite(mod);
    js_register_ax_base_Layer(mod);
    js_register_ax_base_LayerColor(mod);
    js_register_ax_base_LayerGradient(mod);
    js_register_ax_base_LayerRadialGradient(mod);
    js_register_ax_base_LayerMultiplex(mod);
    js_register_ax_base_MenuItem(mod);
    js_register_ax_base_MenuItemLabel(mod);
    js_register_ax_base_MenuItemAtlasFont(mod);
    js_register_ax_base_MenuItemFont(mod);
    js_register_ax_base_MenuItemSprite(mod);
    js_register_ax_base_MenuItemImage(mod);
    js_register_ax_base_MenuItemToggle(mod);
    js_register_ax_base_Menu(mod);
    js_register_ax_base_MotionStreak(mod);
    js_register_ax_base_NodeGrid(mod);
    js_register_ax_base_ParticleBatchNode(mod);
    js_register_ax_base_SpriteSheet(mod);
    js_register_ax_base_SpriteFrameCache(mod);
    js_register_ax_base_ParticleData(mod);
    js_register_ax_base_ParticleEmissionMaskCache(mod);
    js_register_ax_base_ParticleSystem(mod);
    js_register_ax_base_ParticleSystemQuad(mod);
    js_register_ax_base_ParticleFire(mod);
    js_register_ax_base_ParticleFireworks(mod);
    js_register_ax_base_ParticleSun(mod);
    js_register_ax_base_ParticleGalaxy(mod);
    js_register_ax_base_ParticleFlower(mod);
    js_register_ax_base_ParticleMeteor(mod);
    js_register_ax_base_ParticleSpiral(mod);
    js_register_ax_base_ParticleExplosion(mod);
    js_register_ax_base_ParticleSmoke(mod);
    js_register_ax_base_ParticleSnow(mod);
    js_register_ax_base_ParticleRain(mod);
    js_register_ax_base_ProgressTimer(mod);
    js_register_ax_base_ProtectedNode(mod);
    js_register_ax_base_RenderTexture(mod);
    js_register_ax_base_TransitionEaseScene(mod);
    js_register_ax_base_TransitionScene(mod);
    js_register_ax_base_TransitionSceneOriented(mod);
    js_register_ax_base_TransitionRotoZoom(mod);
    js_register_ax_base_TransitionJumpZoom(mod);
    js_register_ax_base_TransitionMoveInL(mod);
    js_register_ax_base_TransitionMoveInR(mod);
    js_register_ax_base_TransitionMoveInT(mod);
    js_register_ax_base_TransitionMoveInB(mod);
    js_register_ax_base_TransitionSlideInL(mod);
    js_register_ax_base_TransitionSlideInR(mod);
    js_register_ax_base_TransitionSlideInB(mod);
    js_register_ax_base_TransitionSlideInT(mod);
    js_register_ax_base_TransitionShrinkGrow(mod);
    js_register_ax_base_TransitionFlipX(mod);
    js_register_ax_base_TransitionFlipY(mod);
    js_register_ax_base_TransitionFlipAngular(mod);
    js_register_ax_base_TransitionZoomFlipX(mod);
    js_register_ax_base_TransitionZoomFlipY(mod);
    js_register_ax_base_TransitionZoomFlipAngular(mod);
    js_register_ax_base_TransitionFade(mod);
    js_register_ax_base_TransitionCrossFade(mod);
    js_register_ax_base_TransitionTurnOffTiles(mod);
    js_register_ax_base_TransitionSplitCols(mod);
    js_register_ax_base_TransitionSplitRows(mod);
    js_register_ax_base_TransitionFadeTR(mod);
    js_register_ax_base_TransitionFadeBL(mod);
    js_register_ax_base_TransitionFadeUp(mod);
    js_register_ax_base_TransitionFadeDown(mod);
    js_register_ax_base_TransitionPageTurn(mod);
    js_register_ax_base_TransitionProgress(mod);
    js_register_ax_base_TransitionProgressRadialCCW(mod);
    js_register_ax_base_TransitionProgressRadialCW(mod);
    js_register_ax_base_TransitionProgressHorizontal(mod);
    js_register_ax_base_TransitionProgressVertical(mod);
    js_register_ax_base_TransitionProgressInOut(mod);
    js_register_ax_base_TransitionProgressOutIn(mod);
    js_register_ax_base_Camera(mod);
    js_register_ax_base_CameraBackgroundBrush(mod);
    js_register_ax_base_CameraBackgroundDepthBrush(mod);
    js_register_ax_base_CameraBackgroundColorBrush(mod);
    js_register_ax_base_CameraBackgroundSkyBoxBrush(mod);
    js_register_ax_base_GridBase(mod);
    js_register_ax_base_Grid3D(mod);
    js_register_ax_base_TiledGrid3D(mod);
    js_register_ax_base_BaseLight(mod);
    js_register_ax_base_DirectionLight(mod);
    js_register_ax_base_PointLight(mod);
    js_register_ax_base_SpotLight(mod);
    js_register_ax_base_AmbientLight(mod);
    js_register_ax_base_RenderState(mod);
    js_register_ax_base_Technique(mod);
    js_register_ax_base_Material(mod);
    js_register_ax_base_Pass(mod);
    js_register_ax_base_ProgramManager(mod);
    js_register_ax_base_Renderer(mod);
    js_register_ax_base_TextureCache(mod);
    js_register_ax_base_Device(mod);
    js_register_ax_base_Application(mod);
    js_register_ax_base_RenderViewImpl(mod);
    js_register_ax_base_AnimationCache(mod);
    js_register_ax_base_SpriteBatchNode(mod);
    js_register_ax_base_ParallaxNode(mod);
    js_register_ax_base_TMXObjectGroup(mod);
    js_register_ax_base_TMXLayerInfo(mod);
    js_register_ax_base_TMXTilesetInfo(mod);
    js_register_ax_base_TMXMapInfo(mod);
    js_register_ax_base_TileMapAtlas(mod);
    js_register_ax_base_FastTMXLayer(mod);
    js_register_ax_base_TMXTileAnimTask(mod);
    js_register_ax_base_TMXTileAnimManager(mod);
    js_register_ax_base_FastTMXTiledMap(mod);
    js_register_ax_base_MotionStreak3D(mod);
}
