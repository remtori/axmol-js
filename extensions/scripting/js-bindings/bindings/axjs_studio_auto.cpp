#include "js-bindings/bindings/axjs_studio_auto.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/ComExtensionData.h"
#include "js-bindings/manual/JSConversions.h"
static void js_register_ax_studio_ActionFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ActionFrame> class_ActionFrame(isolate);
    class_ActionFrame.ctor([]() { return new cocostudio::ActionFrame(); })
        .template inherit<ax::Object>()
        .member_function("setFrameIndex", &cocostudio::ActionFrame::setFrameIndex)
        .member_function("getFrameIndex", &cocostudio::ActionFrame::getFrameIndex)
        .member_function("setFrameTime", &cocostudio::ActionFrame::setFrameTime)
        .member_function("getFrameTime", &cocostudio::ActionFrame::getFrameTime)
        .member_function("setFrameType", &cocostudio::ActionFrame::setFrameType)
        .member_function("getFrameType", &cocostudio::ActionFrame::getFrameType)
        .member_function("setEasingType", &cocostudio::ActionFrame::setEasingType)
        .member_function("getEasingType", &cocostudio::ActionFrame::getEasingType)
        .member_function(
            "getAction",
            [](cocostudio::ActionFrame* self, float arg0, cocostudio::ActionFrame* arg1) { return self->getAction(arg0, arg1); },
            [](cocostudio::ActionFrame* self, float arg0) { return self->getAction(arg0); })
        .member_function("setEasingParameter", [](cocostudio::ActionFrame* self, std::vector<float> arg0) {
            self->setEasingParameter(arg0);
        })
        .auto_wrap_objects(true);
    mod.class_("ActionFrame", class_ActionFrame);
}
static void js_register_ax_studio_ActionMoveFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ActionMoveFrame> class_ActionMoveFrame(isolate);
    class_ActionMoveFrame.ctor([]() { return new cocostudio::ActionMoveFrame(); })
        .template inherit<cocostudio::ActionFrame>()
        .member_function("setPosition", &cocostudio::ActionMoveFrame::setPosition)
        .member_function("getPosition", &cocostudio::ActionMoveFrame::getPosition)
        .member_function("getAction", &cocostudio::ActionMoveFrame::getAction)
        .auto_wrap_objects(true);
    mod.class_("ActionMoveFrame", class_ActionMoveFrame);
}
static void js_register_ax_studio_ActionScaleFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ActionScaleFrame> class_ActionScaleFrame(isolate);
    class_ActionScaleFrame.ctor([]() { return new cocostudio::ActionScaleFrame(); })
        .template inherit<cocostudio::ActionFrame>()
        .member_function("setScaleX", &cocostudio::ActionScaleFrame::setScaleX)
        .member_function("getScaleX", &cocostudio::ActionScaleFrame::getScaleX)
        .member_function("setScaleY", &cocostudio::ActionScaleFrame::setScaleY)
        .member_function("getScaleY", &cocostudio::ActionScaleFrame::getScaleY)
        .member_function("getAction", &cocostudio::ActionScaleFrame::getAction)
        .auto_wrap_objects(true);
    mod.class_("ActionScaleFrame", class_ActionScaleFrame);
}
static void js_register_ax_studio_ActionRotationFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ActionRotationFrame> class_ActionRotationFrame(isolate);
    class_ActionRotationFrame.ctor([]() { return new cocostudio::ActionRotationFrame(); })
        .template inherit<cocostudio::ActionFrame>()
        .member_function("setRotation", &cocostudio::ActionRotationFrame::setRotation)
        .member_function("getRotation", &cocostudio::ActionRotationFrame::getRotation)
        .member_function(
            "getAction",
            [](cocostudio::ActionRotationFrame* self, float arg0, cocostudio::ActionFrame* arg1) { return self->getAction(arg0, arg1); },
            [](cocostudio::ActionRotationFrame* self, float arg0) { return self->getAction(arg0); })
        .auto_wrap_objects(true);
    mod.class_("ActionRotationFrame", class_ActionRotationFrame);
}
static void js_register_ax_studio_ActionFadeFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ActionFadeFrame> class_ActionFadeFrame(isolate);
    class_ActionFadeFrame.ctor([]() { return new cocostudio::ActionFadeFrame(); })
        .template inherit<cocostudio::ActionFrame>()
        .member_function("setOpacity", &cocostudio::ActionFadeFrame::setOpacity)
        .member_function("getOpacity", &cocostudio::ActionFadeFrame::getOpacity)
        .member_function("getAction", &cocostudio::ActionFadeFrame::getAction)
        .auto_wrap_objects(true);
    mod.class_("ActionFadeFrame", class_ActionFadeFrame);
}
static void js_register_ax_studio_ActionTintFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ActionTintFrame> class_ActionTintFrame(isolate);
    class_ActionTintFrame.ctor([]() { return new cocostudio::ActionTintFrame(); })
        .template inherit<cocostudio::ActionFrame>()
        .member_function("setColor", &cocostudio::ActionTintFrame::setColor)
        .member_function("getColor", &cocostudio::ActionTintFrame::getColor)
        .member_function("getAction", &cocostudio::ActionTintFrame::getAction)
        .auto_wrap_objects(true);
    mod.class_("ActionTintFrame", class_ActionTintFrame);
}
static void js_register_ax_studio_ActionObject(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ActionObject> class_ActionObject(isolate);
    class_ActionObject.ctor([]() { return new cocostudio::ActionObject(); })
        .template inherit<ax::Object>()
        .member_function("setName", &cocostudio::ActionObject::setName)
        .member_function("getName", &cocostudio::ActionObject::getName)
        .member_function("setLoop", &cocostudio::ActionObject::setLoop)
        .member_function("getLoop", &cocostudio::ActionObject::getLoop)
        .member_function("setUnitTime", &cocostudio::ActionObject::setUnitTime)
        .member_function("getUnitTime", &cocostudio::ActionObject::getUnitTime)
        .member_function("setCurrentTime", &cocostudio::ActionObject::setCurrentTime)
        .member_function("getCurrentTime", &cocostudio::ActionObject::getCurrentTime)
        .member_function("getTotalTime", &cocostudio::ActionObject::getTotalTime)
        .member_function("isPlaying", &cocostudio::ActionObject::isPlaying)
        .member_function(
            "play",
            [](cocostudio::ActionObject* self, ax::CallFunc* arg0) { self->play(arg0); },
            [](cocostudio::ActionObject* self) { self->play(); })
        .member_function("pause", &cocostudio::ActionObject::pause)
        .member_function("stop", &cocostudio::ActionObject::stop)
        .member_function("addActionNode", &cocostudio::ActionObject::addActionNode)
        .member_function("removeActionNode", &cocostudio::ActionObject::removeActionNode)
        .member_function("updateToFrameByTime", &cocostudio::ActionObject::updateToFrameByTime)
        .member_function("simulationActionUpdate", &cocostudio::ActionObject::simulationActionUpdate)
        .auto_wrap_objects(true);
    mod.class_("ActionObject", class_ActionObject);
}
static void js_register_ax_studio_ActionManagerEx(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ActionManagerEx> class_ActionManagerEx(isolate);
    class_ActionManagerEx.template inherit<ax::Object>()
        .member_function("getActionByName", &cocostudio::ActionManagerEx::getActionByName)
        .member_function(
            "playActionByName",
            [](cocostudio::ActionManagerEx* self, const char* arg0, const char* arg1, ax::CallFunc* arg2)
            { return self->playActionByName(arg0, arg1, arg2); },
            [](cocostudio::ActionManagerEx* self, const char* arg0, const char* arg1) { return self->playActionByName(arg0, arg1); })
        .member_function("stopActionByName", &cocostudio::ActionManagerEx::stopActionByName)
        .member_function("releaseActions", &cocostudio::ActionManagerEx::releaseActions)
        .member_function("getStudioVersionNumber", &cocostudio::ActionManagerEx::getStudioVersionNumber)
        .static_function("getInstance", &cocostudio::ActionManagerEx::getInstance)
        .static_function("destroyInstance", &cocostudio::ActionManagerEx::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("ActionManagerEx", class_ActionManagerEx);
}
static void js_register_ax_studio_BaseData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::BaseData> class_BaseData(isolate);
    class_BaseData.ctor([]() { return new cocostudio::BaseData(); })
        .template inherit<ax::Object>()
        .member_function("setColor", &cocostudio::BaseData::setColor)
        .member_function("getColor", &cocostudio::BaseData::getColor)
        .static_function("create", &cocostudio::BaseData::create)
        .auto_wrap_objects(true);
    mod.class_("BaseData", class_BaseData);
}
static void js_register_ax_studio_DisplayData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::DisplayData> class_DisplayData(isolate);
    class_DisplayData.ctor([]() { return new cocostudio::DisplayData(); })
        .template inherit<ax::Object>()
        .member_function("copy", &cocostudio::DisplayData::copy)
        .static_function("create", &cocostudio::DisplayData::create)
        .static_function("changeDisplayToTexture", &cocostudio::DisplayData::changeDisplayToTexture)
        .auto_wrap_objects(true);
    mod.class_("DisplayData", class_DisplayData);
}
static void js_register_ax_studio_SpriteDisplayData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::SpriteDisplayData> class_SpriteDisplayData(isolate);
    class_SpriteDisplayData.ctor([]() { return new cocostudio::SpriteDisplayData(); })
        .template inherit<cocostudio::DisplayData>()
        .member_function("copy", &cocostudio::SpriteDisplayData::copy)
        .static_function("create", &cocostudio::SpriteDisplayData::create)
        .auto_wrap_objects(true);
    mod.class_("SpriteDisplayData", class_SpriteDisplayData);
}
static void js_register_ax_studio_ArmatureDisplayData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ArmatureDisplayData> class_ArmatureDisplayData(isolate);
    class_ArmatureDisplayData.ctor([]() { return new cocostudio::ArmatureDisplayData(); })
        .template inherit<cocostudio::DisplayData>()
        .static_function("create", &cocostudio::ArmatureDisplayData::create)
        .auto_wrap_objects(true);
    mod.class_("ArmatureDisplayData", class_ArmatureDisplayData);
}
static void js_register_ax_studio_ParticleDisplayData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ParticleDisplayData> class_ParticleDisplayData(isolate);
    class_ParticleDisplayData.ctor([]() { return new cocostudio::ParticleDisplayData(); })
        .template inherit<cocostudio::DisplayData>()
        .static_function("create", &cocostudio::ParticleDisplayData::create)
        .auto_wrap_objects(true);
    mod.class_("ParticleDisplayData", class_ParticleDisplayData);
}
static void js_register_ax_studio_BoneData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::BoneData> class_BoneData(isolate);
    class_BoneData.ctor([]() { return new cocostudio::BoneData(); })
        .template inherit<cocostudio::BaseData>()
        .member_function("init", &cocostudio::BoneData::init)
        .member_function("addDisplayData", &cocostudio::BoneData::addDisplayData)
        .member_function("getDisplayData", &cocostudio::BoneData::getDisplayData)
        .static_function("create", &cocostudio::BoneData::create)
        .auto_wrap_objects(true);
    mod.class_("BoneData", class_BoneData);
}
static void js_register_ax_studio_ArmatureData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ArmatureData> class_ArmatureData(isolate);
    class_ArmatureData.ctor([]() { return new cocostudio::ArmatureData(); })
        .template inherit<ax::Object>()
        .member_function("init", &cocostudio::ArmatureData::init)
        .member_function("addBoneData", &cocostudio::ArmatureData::addBoneData)
        .member_function("getBoneData", &cocostudio::ArmatureData::getBoneData)
        .static_function("create", &cocostudio::ArmatureData::create)
        .auto_wrap_objects(true);
    mod.class_("ArmatureData", class_ArmatureData);
}
static void js_register_ax_studio_FrameData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::FrameData> class_FrameData(isolate);
    class_FrameData.ctor([]() { return new cocostudio::FrameData(); })
        .template inherit<cocostudio::BaseData>()
        .member_function("copy", &cocostudio::FrameData::copy)
        .static_function("create", &cocostudio::FrameData::create)
        .auto_wrap_objects(true);
    mod.class_("FrameData", class_FrameData);
}
static void js_register_ax_studio_MovementBoneData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::MovementBoneData> class_MovementBoneData(isolate);
    class_MovementBoneData.ctor([]() { return new cocostudio::MovementBoneData(); })
        .template inherit<ax::Object>()
        .member_function("init", &cocostudio::MovementBoneData::init)
        .member_function("addFrameData", &cocostudio::MovementBoneData::addFrameData)
        .member_function("getFrameData", &cocostudio::MovementBoneData::getFrameData)
        .static_function("create", &cocostudio::MovementBoneData::create)
        .auto_wrap_objects(true);
    mod.class_("MovementBoneData", class_MovementBoneData);
}
static void js_register_ax_studio_MovementData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::MovementData> class_MovementData(isolate);
    class_MovementData.ctor([]() { return new cocostudio::MovementData(); })
        .template inherit<ax::Object>()
        .member_function("addMovementBoneData", &cocostudio::MovementData::addMovementBoneData)
        .member_function("getMovementBoneData", &cocostudio::MovementData::getMovementBoneData)
        .static_function("create", &cocostudio::MovementData::create)
        .auto_wrap_objects(true);
    mod.class_("MovementData", class_MovementData);
}
static void js_register_ax_studio_AnimationData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::AnimationData> class_AnimationData(isolate);
    class_AnimationData.ctor([]() { return new cocostudio::AnimationData(); })
        .template inherit<ax::Object>()
        .member_function("addMovement", &cocostudio::AnimationData::addMovement)
        .member_function("getMovement", &cocostudio::AnimationData::getMovement)
        .member_function("getMovementCount", &cocostudio::AnimationData::getMovementCount)
        .static_function("create", &cocostudio::AnimationData::create)
        .auto_wrap_objects(true);
    mod.class_("AnimationData", class_AnimationData);
}
static void js_register_ax_studio_ContourData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ContourData> class_ContourData(isolate);
    class_ContourData.ctor([]() { return new cocostudio::ContourData(); })
        .template inherit<ax::Object>()
        .member_function("init", &cocostudio::ContourData::init)
        .member_function("addVertex", [](cocostudio::ContourData* self, ax::Vec2 vertex) { self->addVertex(vertex); })
        .static_function("create", &cocostudio::ContourData::create)
        .auto_wrap_objects(true);
    mod.class_("ContourData", class_ContourData);
}
static void js_register_ax_studio_TextureData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::TextureData> class_TextureData(isolate);
    class_TextureData.ctor([]() { return new cocostudio::TextureData(); })
        .template inherit<ax::Object>()
        .member_function("init", &cocostudio::TextureData::init)
        .member_function("addContourData", &cocostudio::TextureData::addContourData)
        .member_function("getContourData", &cocostudio::TextureData::getContourData)
        .static_function("create", &cocostudio::TextureData::create)
        .auto_wrap_objects(true);
    mod.class_("TextureData", class_TextureData);
}
static void js_register_ax_studio_Tween(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::Tween> class_Tween(isolate);
    class_Tween.ctor([]() { return new cocostudio::Tween(); })
        .template inherit<cocostudio::ProcessBase>()
        .member_function("init", &cocostudio::Tween::init)
        // .member_function("play", &cocostudio::Tween::play)
        .member_function("setAnimation", &cocostudio::Tween::setAnimation)
        .member_function("getAnimation", &cocostudio::Tween::getAnimation)
        .member_function("gotoAndPlay", &cocostudio::Tween::gotoAndPlay)
        .member_function("gotoAndPause", &cocostudio::Tween::gotoAndPause)
        .static_function("create", &cocostudio::Tween::create)
        .auto_wrap_objects(true);
    mod.class_("Tween", class_Tween);
}
static void js_register_ax_studio_DisplayManager(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::DisplayManager> class_DisplayManager(isolate);
    class_DisplayManager.ctor([]() { return new cocostudio::DisplayManager(); })
        .template inherit<ax::Object>()
        .member_function("init", &cocostudio::DisplayManager::init)
        .member_function(
            "addDisplay",
            [](cocostudio::DisplayManager* self, ax::Node* arg0, int arg1) { self->addDisplay(arg0, arg1); },
            [](cocostudio::DisplayManager* self, cocostudio::DisplayData* arg0, int arg1) { self->addDisplay(arg0, arg1); })
        .member_function("removeDisplay", &cocostudio::DisplayManager::removeDisplay)
        .member_function("getDecorativeDisplayList", &cocostudio::DisplayManager::getDecorativeDisplayList)
        .member_function("changeDisplayWithIndex", &cocostudio::DisplayManager::changeDisplayWithIndex)
        .member_function("changeDisplayWithName", &cocostudio::DisplayManager::changeDisplayWithName)
        .member_function("getDisplayRenderNode", &cocostudio::DisplayManager::getDisplayRenderNode)
        .member_function("getDisplayRenderNodeType", &cocostudio::DisplayManager::getDisplayRenderNodeType)
        .member_function("getCurrentDisplayIndex", &cocostudio::DisplayManager::getCurrentDisplayIndex)
        .member_function("setVisible", &cocostudio::DisplayManager::setVisible)
        .member_function("isVisible", &cocostudio::DisplayManager::isVisible)
        .member_function("getContentSize", &cocostudio::DisplayManager::getContentSize)
        .member_function("getBoundingBox", &cocostudio::DisplayManager::getBoundingBox)
        .member_function("getAnchorPoint", &cocostudio::DisplayManager::getAnchorPoint)
        .member_function("getAnchorPointInPoints", &cocostudio::DisplayManager::getAnchorPointInPoints)
        .member_function(
            "containPoint",
            [](cocostudio::DisplayManager* self, float arg0, float arg1) { return self->containPoint(arg0, arg1); },
            [](cocostudio::DisplayManager* self, ax::Vec2 arg0) { return self->containPoint(arg0); })
        .member_function("setForceChangeDisplay", &cocostudio::DisplayManager::setForceChangeDisplay)
        .member_function("isForceChangeDisplay", &cocostudio::DisplayManager::isForceChangeDisplay)
        .static_function("create", &cocostudio::DisplayManager::create)
        .auto_wrap_objects(true);
    mod.class_("DisplayManager", class_DisplayManager);
}
static void js_register_ax_studio_Bone(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::Bone> class_Bone(isolate);
    class_Bone.ctor([]() { return new cocostudio::Bone(); })
        .template inherit<ax::Node>()
        // .member_function("init", &cocostudio::Bone::init)
        .member_function(
            "addDisplay",
            [](cocostudio::Bone* self, ax::Node* arg0, int arg1) { self->addDisplay(arg0, arg1); },
            [](cocostudio::Bone* self, cocostudio::DisplayData* arg0, int arg1) { self->addDisplay(arg0, arg1); })
        .member_function("removeDisplay", &cocostudio::Bone::removeDisplay)
        .member_function("changeDisplayWithIndex", &cocostudio::Bone::changeDisplayWithIndex)
        .member_function("changeDisplayWithName", &cocostudio::Bone::changeDisplayWithName)
        .member_function("addChildBone", &cocostudio::Bone::addChildBone)
        .member_function("setParentBone", &cocostudio::Bone::setParentBone)
        .member_function("getParentBone", &cocostudio::Bone::getParentBone)
        // .member_function("removeFromParent", &cocostudio::Bone::removeFromParent)
        .member_function("removeChildBone", &cocostudio::Bone::removeChildBone)
        .member_function("updateColor", &cocostudio::Bone::updateColor)
        .member_function("updateZOrder", &cocostudio::Bone::updateZOrder)
        .member_function("getTween", &cocostudio::Bone::getTween)
        .member_function("setTransformDirty", &cocostudio::Bone::setTransformDirty)
        .member_function("isTransformDirty", &cocostudio::Bone::isTransformDirty)
        .member_function("getNodeToArmatureTransform", &cocostudio::Bone::getNodeToArmatureTransform)
        .member_function("getDisplayRenderNode", &cocostudio::Bone::getDisplayRenderNode)
        .member_function("getDisplayRenderNodeType", &cocostudio::Bone::getDisplayRenderNodeType)
        .member_function("getColliderDetector", &cocostudio::Bone::getColliderDetector)
        .member_function("setBoneData", &cocostudio::Bone::setBoneData)
        .member_function("getBoneData", &cocostudio::Bone::getBoneData)
        .member_function("setArmature", &cocostudio::Bone::setArmature)
        .member_function("getArmature", &cocostudio::Bone::getArmature)
        .member_function("setChildArmature", &cocostudio::Bone::setChildArmature)
        .member_function("getChildArmature", &cocostudio::Bone::getChildArmature)
        .member_function("getDisplayManager", &cocostudio::Bone::getDisplayManager)
        .member_function("setIgnoreMovementBoneData", &cocostudio::Bone::setIgnoreMovementBoneData)
        .member_function("isIgnoreMovementBoneData", &cocostudio::Bone::isIgnoreMovementBoneData)
        .member_function("setBlendFunc", &cocostudio::Bone::setBlendFunc)
        .member_function("getBlendFunc", &cocostudio::Bone::getBlendFunc)
        .member_function("setBlendDirty", &cocostudio::Bone::setBlendDirty)
        .member_function("isBlendDirty", &cocostudio::Bone::isBlendDirty)
        .member_function("getTweenData", &cocostudio::Bone::getTweenData)
        .member_function("getWorldInfo", &cocostudio::Bone::getWorldInfo)
        .static_function(
            "create", [](std::string_view arg0) { return cocostudio::Bone::create(arg0); }, []() { return cocostudio::Bone::create(); })
        .auto_wrap_objects(true);
    mod.class_("Bone", class_Bone);
}
static void js_register_ax_studio_BatchNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::BatchNode> class_BatchNode(isolate);
    class_BatchNode.template inherit<ax::Node>().static_function("create", &cocostudio::BatchNode::create).auto_wrap_objects(true);
    mod.class_("BatchNode", class_BatchNode);
}
static void js_register_ax_studio_ArmatureAnimation(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ArmatureAnimation> class_ArmatureAnimation(isolate);
    class_ArmatureAnimation.ctor([]() { return new cocostudio::ArmatureAnimation(); })
        .template inherit<cocostudio::ProcessBase>()
        .member_function("init", &cocostudio::ArmatureAnimation::init)
        .member_function("setSpeedScale", &cocostudio::ArmatureAnimation::setSpeedScale)
        .member_function("getSpeedScale", &cocostudio::ArmatureAnimation::getSpeedScale)
        .member_function(
            "play",
            [](cocostudio::ArmatureAnimation* self, std::string_view arg0) { self->play(arg0); },
            [](cocostudio::ArmatureAnimation* self, std::string_view arg0, int arg1) { self->play(arg0, arg1); },
            [](cocostudio::ArmatureAnimation* self, std::string_view arg0, int arg1, int arg2) { self->play(arg0, arg1, arg2); })
        .member_function(
            "playWithIndex",
            [](cocostudio::ArmatureAnimation* self, int arg0) { self->playWithIndex(arg0); },
            [](cocostudio::ArmatureAnimation* self, int arg0, int arg1) { self->playWithIndex(arg0, arg1); },
            [](cocostudio::ArmatureAnimation* self, int arg0, int arg1, int arg2) { self->playWithIndex(arg0, arg1, arg2); })
        .member_function(
            "playWithNames",
            [](cocostudio::ArmatureAnimation* self, std::vector<std::string> arg0) { self->playWithNames(arg0); },
            [](cocostudio::ArmatureAnimation* self, std::vector<std::string> arg0, int arg1) { self->playWithNames(arg0, arg1); },
            [](cocostudio::ArmatureAnimation* self, std::vector<std::string> arg0, int arg1, bool arg2)
            { self->playWithNames(arg0, arg1, arg2); })
        .member_function(
            "playWithIndexes",
            [](cocostudio::ArmatureAnimation* self, std::vector<int> arg0) { self->playWithIndexes(arg0); },
            [](cocostudio::ArmatureAnimation* self, std::vector<int> arg0, int arg1) { self->playWithIndexes(arg0, arg1); },
            [](cocostudio::ArmatureAnimation* self, std::vector<int> arg0, int arg1, bool arg2)
            { self->playWithIndexes(arg0, arg1, arg2); })
        .member_function("gotoAndPlay", &cocostudio::ArmatureAnimation::gotoAndPlay)
        .member_function("gotoAndPause", &cocostudio::ArmatureAnimation::gotoAndPause)
        .member_function("getMovementCount", &cocostudio::ArmatureAnimation::getMovementCount)
        .member_function("getCurrentMovementID", &cocostudio::ArmatureAnimation::getCurrentMovementID)
        .member_function("setAnimationData", &cocostudio::ArmatureAnimation::setAnimationData)
        .member_function("getAnimationData", &cocostudio::ArmatureAnimation::getAnimationData)
        .static_function("create", &cocostudio::ArmatureAnimation::create)
        .auto_wrap_objects(true);
    mod.class_("ArmatureAnimation", class_ArmatureAnimation);
}
static void js_register_ax_studio_ArmatureDataManager(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ArmatureDataManager> class_ArmatureDataManager(isolate);
    class_ArmatureDataManager.template inherit<ax::Object>()
        .member_function("init", &cocostudio::ArmatureDataManager::init)
        .member_function(
            "addArmatureData",
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, cocostudio::ArmatureData* arg1)
            { self->addArmatureData(arg0, arg1); },
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, cocostudio::ArmatureData* arg1, std::string_view arg2)
            { self->addArmatureData(arg0, arg1, arg2); })
        .member_function("getArmatureData", &cocostudio::ArmatureDataManager::getArmatureData)
        .member_function("removeArmatureData", &cocostudio::ArmatureDataManager::removeArmatureData)
        .member_function(
            "addAnimationData",
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, cocostudio::AnimationData* arg1)
            { self->addAnimationData(arg0, arg1); },
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, cocostudio::AnimationData* arg1, std::string_view arg2)
            { self->addAnimationData(arg0, arg1, arg2); })
        .member_function("getAnimationData", &cocostudio::ArmatureDataManager::getAnimationData)
        .member_function("removeAnimationData", &cocostudio::ArmatureDataManager::removeAnimationData)
        .member_function(
            "addTextureData",
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, cocostudio::TextureData* arg1)
            { self->addTextureData(arg0, arg1); },
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, cocostudio::TextureData* arg1, std::string_view arg2)
            { self->addTextureData(arg0, arg1, arg2); })
        .member_function("getTextureData", &cocostudio::ArmatureDataManager::getTextureData)
        .member_function("removeTextureData", &cocostudio::ArmatureDataManager::removeTextureData)
        .member_function(
            "addArmatureFileInfo",
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, std::string_view arg1, std::string_view arg2)
            { self->addArmatureFileInfo(arg0, arg1, arg2); },
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0) { self->addArmatureFileInfo(arg0); })
        .member_function(
            "addSpriteFrameFromFile",
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, std::string_view arg1)
            { self->addSpriteFrameFromFile(arg0, arg1); },
            [](cocostudio::ArmatureDataManager* self, std::string_view arg0, std::string_view arg1, std::string_view arg2)
            { self->addSpriteFrameFromFile(arg0, arg1, arg2); })
        .member_function("removeArmatureFileInfo", &cocostudio::ArmatureDataManager::removeArmatureFileInfo)
        .member_function("isAutoLoadSpriteFile", &cocostudio::ArmatureDataManager::isAutoLoadSpriteFile)
        .member_function("getArmatureDatas", &cocostudio::ArmatureDataManager::getArmatureDatas)
        .member_function("getAnimationDatas", &cocostudio::ArmatureDataManager::getAnimationDatas)
        .member_function("getTextureDatas", &cocostudio::ArmatureDataManager::getTextureDatas)
        .member_function("addRelativeData", &cocostudio::ArmatureDataManager::addRelativeData)
        .member_function("getRelativeData", &cocostudio::ArmatureDataManager::getRelativeData)
        .static_function("getInstance", &cocostudio::ArmatureDataManager::getInstance)
        .static_function("destroyInstance", &cocostudio::ArmatureDataManager::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("ArmatureDataManager", class_ArmatureDataManager);
}
static void js_register_ax_studio_Armature(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::Armature> class_Armature(isolate);
    class_Armature.ctor([]() { return new cocostudio::Armature(); })
        .template inherit<ax::Node>()
        .member_function(
            "init",
            [](cocostudio::Armature* self, std::string_view arg0, cocostudio::Bone* arg1) { return self->init(arg0, arg1); },
            [](cocostudio::Armature* self, std::string_view arg0) { return self->init(arg0); })
        .member_function("addBone", &cocostudio::Armature::addBone)
        .member_function("getBone", &cocostudio::Armature::getBone)
        .member_function("changeBoneParent", &cocostudio::Armature::changeBoneParent)
        .member_function("removeBone", &cocostudio::Armature::removeBone)
        .member_function("getBoneDic", &cocostudio::Armature::getBoneDic)
        .member_function("getBoneAtPoint", &cocostudio::Armature::getBoneAtPoint)
        .member_function("setBlendFunc", &cocostudio::Armature::setBlendFunc)
        .member_function("getBlendFunc", &cocostudio::Armature::getBlendFunc)
        .member_function("updateOffsetPoint", &cocostudio::Armature::updateOffsetPoint)
        .member_function("getOffsetPoints", &cocostudio::Armature::getOffsetPoints)
        .member_function("setAnimation", &cocostudio::Armature::setAnimation)
        .member_function("getAnimation", &cocostudio::Armature::getAnimation)
        .member_function("getArmatureTransformDirty", &cocostudio::Armature::getArmatureTransformDirty)
        .member_function("setArmatureData", &cocostudio::Armature::setArmatureData)
        .member_function("getArmatureData", &cocostudio::Armature::getArmatureData)
        .member_function("setParentBone", &cocostudio::Armature::setParentBone)
        .member_function("getParentBone", &cocostudio::Armature::getParentBone)
        .member_function("setVersion", &cocostudio::Armature::setVersion)
        .member_function("getVersion", &cocostudio::Armature::getVersion)
        .member_function("setBatchNode", &cocostudio::Armature::setBatchNode)
        .member_function("getBatchNode", &cocostudio::Armature::getBatchNode)
        .static_function(
            "create",
            [](std::string_view arg0) { return cocostudio::Armature::create(arg0); },
            []() { return cocostudio::Armature::create(); },
            [](std::string_view arg0, cocostudio::Bone* arg1) { return cocostudio::Armature::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("Armature", class_Armature);
}
static void js_register_ax_studio_Skin(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::Skin> class_Skin(isolate);
    class_Skin.ctor([]() { return new cocostudio::Skin(); })
        .template inherit<ax::Sprite>()
        .member_function("updateArmatureTransform", &cocostudio::Skin::updateArmatureTransform)
        .member_function("getNodeToWorldTransformAR", &cocostudio::Skin::getNodeToWorldTransformAR)
        .member_function("setBone", &cocostudio::Skin::setBone)
        .member_function("getBone", &cocostudio::Skin::getBone)
        .member_function("getDisplayName", &cocostudio::Skin::getDisplayName)
        .static_function(
            "create", [](std::string_view arg0) { return cocostudio::Skin::create(arg0); }, []() { return cocostudio::Skin::create(); })
        .static_function("createWithSpriteFrameName", &cocostudio::Skin::createWithSpriteFrameName)
        .auto_wrap_objects(true);
    mod.class_("Skin", class_Skin);
}
static void js_register_ax_studio_ComAttribute(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ComAttribute> class_ComAttribute(isolate);
    class_ComAttribute.template inherit<ax::Component>()
        .member_function("setInt", &cocostudio::ComAttribute::setInt)
        .member_function("setFloat", &cocostudio::ComAttribute::setFloat)
        .member_function("setBool", &cocostudio::ComAttribute::setBool)
        .member_function("setString", &cocostudio::ComAttribute::setString)
        .member_function(
            "getInt",
            [](cocostudio::ComAttribute* self, std::string_view arg0) { return self->getInt(arg0); },
            [](cocostudio::ComAttribute* self, std::string_view arg0, int arg1) { return self->getInt(arg0, arg1); })
        .member_function(
            "getFloat",
            [](cocostudio::ComAttribute* self, std::string_view arg0) { return self->getFloat(arg0); },
            [](cocostudio::ComAttribute* self, std::string_view arg0, float arg1) { return self->getFloat(arg0, arg1); })
        .member_function(
            "getBool",
            [](cocostudio::ComAttribute* self, std::string_view arg0) { return self->getBool(arg0); },
            [](cocostudio::ComAttribute* self, std::string_view arg0, bool arg1) { return self->getBool(arg0, arg1); })
        .member_function(
            "getString",
            [](cocostudio::ComAttribute* self, std::string_view arg0) { return self->getString(arg0); },
            [](cocostudio::ComAttribute* self, std::string_view arg0, std::string_view arg1) { return self->getString(arg0, arg1); })
        .member_function("parse", &cocostudio::ComAttribute::parse)
        .static_function("createInstance", &cocostudio::ComAttribute::createInstance)
        .static_function("create", &cocostudio::ComAttribute::create)
        .auto_wrap_objects(true);
    mod.class_("ComAttribute", class_ComAttribute);
}
static void js_register_ax_studio_ComAudio(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ComAudio> class_ComAudio(isolate);
    class_ComAudio.template inherit<ax::Component>()
        .member_function("end", &cocostudio::ComAudio::end)
        .member_function("preloadBackgroundMusic", &cocostudio::ComAudio::preloadBackgroundMusic)
        .member_function(
            "playBackgroundMusic",
            [](cocostudio::ComAudio* self, const char* arg0) { self->playBackgroundMusic(arg0); },
            [](cocostudio::ComAudio* self, const char* arg0, bool arg1) { self->playBackgroundMusic(arg0, arg1); },
            [](cocostudio::ComAudio* self) { self->playBackgroundMusic(); })
        .member_function(
            "stopBackgroundMusic",
            [](cocostudio::ComAudio* self) { self->stopBackgroundMusic(); },
            [](cocostudio::ComAudio* self, bool arg0) { self->stopBackgroundMusic(arg0); })
        .member_function("pauseBackgroundMusic", &cocostudio::ComAudio::pauseBackgroundMusic)
        .member_function("resumeBackgroundMusic", &cocostudio::ComAudio::resumeBackgroundMusic)
        .member_function("rewindBackgroundMusic", &cocostudio::ComAudio::rewindBackgroundMusic)
        .member_function("willPlayBackgroundMusic", &cocostudio::ComAudio::willPlayBackgroundMusic)
        .member_function("isBackgroundMusicPlaying", &cocostudio::ComAudio::isBackgroundMusicPlaying)
        .member_function("getBackgroundMusicVolume", &cocostudio::ComAudio::getBackgroundMusicVolume)
        .member_function("setBackgroundMusicVolume", &cocostudio::ComAudio::setBackgroundMusicVolume)
        .member_function("getEffectsVolume", &cocostudio::ComAudio::getEffectsVolume)
        .member_function("setEffectsVolume", &cocostudio::ComAudio::setEffectsVolume)
        .member_function(
            "playEffect",
            [](cocostudio::ComAudio* self, const char* arg0) { return self->playEffect(arg0); },
            [](cocostudio::ComAudio* self, const char* arg0, bool arg1) { return self->playEffect(arg0, arg1); },
            [](cocostudio::ComAudio* self) { return self->playEffect(); })
        .member_function("pauseEffect", &cocostudio::ComAudio::pauseEffect)
        .member_function("pauseAllEffects", &cocostudio::ComAudio::pauseAllEffects)
        .member_function("resumeEffect", &cocostudio::ComAudio::resumeEffect)
        .member_function("resumeAllEffects", &cocostudio::ComAudio::resumeAllEffects)
        .member_function("stopEffect", &cocostudio::ComAudio::stopEffect)
        .member_function("stopAllEffects", &cocostudio::ComAudio::stopAllEffects)
        .member_function("preloadEffect", &cocostudio::ComAudio::preloadEffect)
        .member_function("unloadEffect", &cocostudio::ComAudio::unloadEffect)
        .member_function("setFile", &cocostudio::ComAudio::setFile)
        .member_function("getFile", &cocostudio::ComAudio::getFile)
        .member_function("setLoop", &cocostudio::ComAudio::setLoop)
        .member_function("isLoop", &cocostudio::ComAudio::isLoop)
        .member_function("start", &cocostudio::ComAudio::start)
        .member_function("stop", &cocostudio::ComAudio::stop)
        .static_function("createInstance", &cocostudio::ComAudio::createInstance)
        .static_function("create", &cocostudio::ComAudio::create)
        .auto_wrap_objects(true);
    mod.class_("ComAudio", class_ComAudio);
}
static void js_register_ax_studio_ComController(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ComController> class_ComController(isolate);
    class_ComController.ctor([]() { return new cocostudio::ComController(); })
        .template inherit<ax::Component>()
        .static_function("createInstance", &cocostudio::ComController::createInstance)
        .static_function("create", &cocostudio::ComController::create)
        .auto_wrap_objects(true);
    mod.class_("ComController", class_ComController);
}
static void js_register_ax_studio_ComRender(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ComRender> class_ComRender(isolate);
    class_ComRender.template inherit<ax::Component>()
        .member_function("getNode", &cocostudio::ComRender::getNode)
        .member_function("setNode", &cocostudio::ComRender::setNode)
        .static_function("createInstance", &cocostudio::ComRender::createInstance)
        .static_function(
            "create",
            [](ax::Node* arg0, const char* arg1) { return cocostudio::ComRender::create(arg0, arg1); },
            []() { return cocostudio::ComRender::create(); })
        .auto_wrap_objects(true);
    mod.class_("ComRender", class_ComRender);
}
static void js_register_ax_studio_GUIReader(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::GUIReader> class_GUIReader(isolate);
    class_GUIReader.template inherit<ax::Object>()
        .member_function("widgetFromJsonFile", &cocostudio::GUIReader::widgetFromJsonFile)
        .member_function("widgetFromBinaryFile", &cocostudio::GUIReader::widgetFromBinaryFile)
        .member_function("getVersionInteger", &cocostudio::GUIReader::getVersionInteger)
        .member_function("setFilePath", &cocostudio::GUIReader::setFilePath)
        .member_function("getFilePath", &cocostudio::GUIReader::getFilePath)
        .static_function("getInstance", &cocostudio::GUIReader::getInstance)
        .static_function("destroyInstance", &cocostudio::GUIReader::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("GUIReader", class_GUIReader);
}
static void js_register_ax_studio_SceneReader(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::SceneReader> class_SceneReader(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_SceneReader
        .member_function(
            "createNodeWithSceneFile",
            [](cocostudio::SceneReader* self, std::string_view arg0) { return self->createNodeWithSceneFile(arg0); },
            [](cocostudio::SceneReader* self, std::string_view arg0, cocostudio::SceneReader::AttachComponentType arg1)
            { return self->createNodeWithSceneFile(arg0, arg1); })
        .member_function("setTarget", &cocostudio::SceneReader::setTarget)
        .member_function("getNodeByTag", &cocostudio::SceneReader::getNodeByTag)
        .member_function("getAttachComponentType", &cocostudio::SceneReader::getAttachComponentType)
        .static_function("getInstance", &cocostudio::SceneReader::getInstance)
        .static_function("destroyInstance", &cocostudio::SceneReader::destroyInstance)
        .static_function("sceneReaderVersion", &cocostudio::SceneReader::sceneReaderVersion)
        .auto_wrap_objects(true);
    mod.class_("SceneReader", class_SceneReader);
}
static void js_register_ax_studio_ActionTimelineCache(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::ActionTimelineCache> class_ActionTimelineCache(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_ActionTimelineCache.member_function("init", &cocostudio::timeline::ActionTimelineCache::init)
        .member_function("removeAction", &cocostudio::timeline::ActionTimelineCache::removeAction)
        .member_function("createActionFromJson", &cocostudio::timeline::ActionTimelineCache::createActionFromJson)
        .member_function("createActionFromContent", &cocostudio::timeline::ActionTimelineCache::createActionFromContent)
        .member_function("loadAnimationActionWithFile", &cocostudio::timeline::ActionTimelineCache::loadAnimationActionWithFile)
        .member_function("loadAnimationActionWithContent", &cocostudio::timeline::ActionTimelineCache::loadAnimationActionWithContent)
        .member_function("createActionWithFlatBuffersFile", &cocostudio::timeline::ActionTimelineCache::createActionWithFlatBuffersFile)
        .member_function("loadAnimationActionWithFlatBuffersFile",
                         &cocostudio::timeline::ActionTimelineCache::loadAnimationActionWithFlatBuffersFile)
        .member_function("createActionWithFlatBuffersForSimulator",
                         &cocostudio::timeline::ActionTimelineCache::createActionWithFlatBuffersForSimulator)
        .static_function("destroyInstance", &cocostudio::timeline::ActionTimelineCache::destroyInstance)
        .static_function("createAction", &cocostudio::timeline::ActionTimelineCache::createAction)
        .auto_wrap_objects(true);
    mod.class_("ActionTimelineCache", class_ActionTimelineCache);
}
static void js_register_ax_studio_Frame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::Frame> class_Frame(isolate);
    class_Frame.template inherit<ax::Object>()
        .member_function("setFrameIndex", &cocostudio::timeline::Frame::setFrameIndex)
        .member_function("getFrameIndex", &cocostudio::timeline::Frame::getFrameIndex)
        .member_function("setTimeline", &cocostudio::timeline::Frame::setTimeline)
        .member_function("getTimeline", &cocostudio::timeline::Frame::getTimeline)
        .member_function("setNode", &cocostudio::timeline::Frame::setNode)
        .member_function("getNode", &cocostudio::timeline::Frame::getNode)
        .member_function("setTween", &cocostudio::timeline::Frame::setTween)
        .member_function("isTween", &cocostudio::timeline::Frame::isTween)
        .member_function("setTweenType", &cocostudio::timeline::Frame::setTweenType)
        .member_function("getTweenType", &cocostudio::timeline::Frame::getTweenType)
        .member_function("setEasingParams", &cocostudio::timeline::Frame::setEasingParams)
        .member_function("getEasingParams", &cocostudio::timeline::Frame::getEasingParams)
        .member_function("isEnterWhenPassed", &cocostudio::timeline::Frame::isEnterWhenPassed)
        .member_function("apply", &cocostudio::timeline::Frame::apply)
        .member_function("clone", &cocostudio::timeline::Frame::clone)
        .auto_wrap_objects(true);
    mod.class_("Frame", class_Frame);
}
static void js_register_ax_studio_VisibleFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::VisibleFrame> class_VisibleFrame(isolate);
    class_VisibleFrame.ctor([]() { return new cocostudio::timeline::VisibleFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setVisible", &cocostudio::timeline::VisibleFrame::setVisible)
        .member_function("isVisible", &cocostudio::timeline::VisibleFrame::isVisible)
        .static_function("create", &cocostudio::timeline::VisibleFrame::create)
        .auto_wrap_objects(true);
    mod.class_("VisibleFrame", class_VisibleFrame);
}
static void js_register_ax_studio_TextureFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::TextureFrame> class_TextureFrame(isolate);
    class_TextureFrame.ctor([]() { return new cocostudio::timeline::TextureFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setTextureName", &cocostudio::timeline::TextureFrame::setTextureName)
        .member_function("getTextureName", &cocostudio::timeline::TextureFrame::getTextureName)
        .static_function("create", &cocostudio::timeline::TextureFrame::create)
        .auto_wrap_objects(true);
    mod.class_("TextureFrame", class_TextureFrame);
}
static void js_register_ax_studio_RotationFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::RotationFrame> class_RotationFrame(isolate);
    class_RotationFrame.ctor([]() { return new cocostudio::timeline::RotationFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setRotation", &cocostudio::timeline::RotationFrame::setRotation)
        .member_function("getRotation", &cocostudio::timeline::RotationFrame::getRotation)
        .static_function("create", &cocostudio::timeline::RotationFrame::create)
        .auto_wrap_objects(true);
    mod.class_("RotationFrame", class_RotationFrame);
}
static void js_register_ax_studio_SkewFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::SkewFrame> class_SkewFrame(isolate);
    class_SkewFrame.ctor([]() { return new cocostudio::timeline::SkewFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setSkewX", &cocostudio::timeline::SkewFrame::setSkewX)
        .member_function("getSkewX", &cocostudio::timeline::SkewFrame::getSkewX)
        .member_function("setSkewY", &cocostudio::timeline::SkewFrame::setSkewY)
        .member_function("getSkewY", &cocostudio::timeline::SkewFrame::getSkewY)
        .static_function("create", &cocostudio::timeline::SkewFrame::create)
        .auto_wrap_objects(true);
    mod.class_("SkewFrame", class_SkewFrame);
}
static void js_register_ax_studio_RotationSkewFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::RotationSkewFrame> class_RotationSkewFrame(isolate);
    class_RotationSkewFrame.ctor([]() { return new cocostudio::timeline::RotationSkewFrame(); })
        .template inherit<cocostudio::timeline::SkewFrame>()
        .static_function("create", &cocostudio::timeline::RotationSkewFrame::create)
        .auto_wrap_objects(true);
    mod.class_("RotationSkewFrame", class_RotationSkewFrame);
}
static void js_register_ax_studio_PositionFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::PositionFrame> class_PositionFrame(isolate);
    class_PositionFrame.ctor([]() { return new cocostudio::timeline::PositionFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setPosition", &cocostudio::timeline::PositionFrame::setPosition)
        .member_function("getPosition", &cocostudio::timeline::PositionFrame::getPosition)
        .member_function("setX", &cocostudio::timeline::PositionFrame::setX)
        .member_function("setY", &cocostudio::timeline::PositionFrame::setY)
        .member_function("getX", &cocostudio::timeline::PositionFrame::getX)
        .member_function("getY", &cocostudio::timeline::PositionFrame::getY)
        .static_function("create", &cocostudio::timeline::PositionFrame::create)
        .auto_wrap_objects(true);
    mod.class_("PositionFrame", class_PositionFrame);
}
static void js_register_ax_studio_ScaleFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::ScaleFrame> class_ScaleFrame(isolate);
    class_ScaleFrame.ctor([]() { return new cocostudio::timeline::ScaleFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setScale", &cocostudio::timeline::ScaleFrame::setScale)
        .member_function("setScaleX", &cocostudio::timeline::ScaleFrame::setScaleX)
        .member_function("getScaleX", &cocostudio::timeline::ScaleFrame::getScaleX)
        .member_function("setScaleY", &cocostudio::timeline::ScaleFrame::setScaleY)
        .member_function("getScaleY", &cocostudio::timeline::ScaleFrame::getScaleY)
        .static_function("create", &cocostudio::timeline::ScaleFrame::create)
        .auto_wrap_objects(true);
    mod.class_("ScaleFrame", class_ScaleFrame);
}
static void js_register_ax_studio_AnchorPointFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::AnchorPointFrame> class_AnchorPointFrame(isolate);
    class_AnchorPointFrame.ctor([]() { return new cocostudio::timeline::AnchorPointFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setAnchorPoint", &cocostudio::timeline::AnchorPointFrame::setAnchorPoint)
        .member_function("getAnchorPoint", &cocostudio::timeline::AnchorPointFrame::getAnchorPoint)
        .static_function("create", &cocostudio::timeline::AnchorPointFrame::create)
        .auto_wrap_objects(true);
    mod.class_("AnchorPointFrame", class_AnchorPointFrame);
}
static void js_register_ax_studio_InnerActionFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::InnerActionFrame> class_InnerActionFrame(isolate);
    class_InnerActionFrame.ctor([]() { return new cocostudio::timeline::InnerActionFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setInnerActionType", &cocostudio::timeline::InnerActionFrame::setInnerActionType)
        .member_function("getInnerActionType", &cocostudio::timeline::InnerActionFrame::getInnerActionType)
        .member_function("setEnterWithName", &cocostudio::timeline::InnerActionFrame::setEnterWithName)
        .member_function("setStartFrameIndex", &cocostudio::timeline::InnerActionFrame::setStartFrameIndex)
        .member_function("getStartFrameIndex", &cocostudio::timeline::InnerActionFrame::getStartFrameIndex)
        .member_function("setEndFrameIndex", &cocostudio::timeline::InnerActionFrame::setEndFrameIndex)
        .member_function("getEndFrameIndex", &cocostudio::timeline::InnerActionFrame::getEndFrameIndex)
        .member_function("setAnimationName", &cocostudio::timeline::InnerActionFrame::setAnimationName)
        .member_function("setSingleFrameIndex", &cocostudio::timeline::InnerActionFrame::setSingleFrameIndex)
        .member_function("getSingleFrameIndex", &cocostudio::timeline::InnerActionFrame::getSingleFrameIndex)
        .static_function("create", &cocostudio::timeline::InnerActionFrame::create)
        .auto_wrap_objects(true);
    mod.class_("InnerActionFrame", class_InnerActionFrame);
}
static void js_register_ax_studio_ColorFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::ColorFrame> class_ColorFrame(isolate);
    class_ColorFrame.ctor([]() { return new cocostudio::timeline::ColorFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setColor", &cocostudio::timeline::ColorFrame::setColor)
        .member_function("getColor", &cocostudio::timeline::ColorFrame::getColor)
        .static_function("create", &cocostudio::timeline::ColorFrame::create)
        .auto_wrap_objects(true);
    mod.class_("ColorFrame", class_ColorFrame);
}
static void js_register_ax_studio_AlphaFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::AlphaFrame> class_AlphaFrame(isolate);
    class_AlphaFrame.ctor([]() { return new cocostudio::timeline::AlphaFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setAlpha", &cocostudio::timeline::AlphaFrame::setAlpha)
        .member_function("getAlpha", &cocostudio::timeline::AlphaFrame::getAlpha)
        .static_function("create", &cocostudio::timeline::AlphaFrame::create)
        .auto_wrap_objects(true);
    mod.class_("AlphaFrame", class_AlphaFrame);
}
static void js_register_ax_studio_EventFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::EventFrame> class_EventFrame(isolate);
    class_EventFrame.ctor([]() { return new cocostudio::timeline::EventFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("init", &cocostudio::timeline::EventFrame::init)
        .member_function("setEvent", &cocostudio::timeline::EventFrame::setEvent)
        .member_function("getEvent", &cocostudio::timeline::EventFrame::getEvent)
        .static_function("create", &cocostudio::timeline::EventFrame::create)
        .auto_wrap_objects(true);
    mod.class_("EventFrame", class_EventFrame);
}
static void js_register_ax_studio_ZOrderFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::ZOrderFrame> class_ZOrderFrame(isolate);
    class_ZOrderFrame.ctor([]() { return new cocostudio::timeline::ZOrderFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("setZOrder", &cocostudio::timeline::ZOrderFrame::setZOrder)
        .member_function("getZOrder", &cocostudio::timeline::ZOrderFrame::getZOrder)
        .static_function("create", &cocostudio::timeline::ZOrderFrame::create)
        .auto_wrap_objects(true);
    mod.class_("ZOrderFrame", class_ZOrderFrame);
}
static void js_register_ax_studio_BlendFuncFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::BlendFuncFrame> class_BlendFuncFrame(isolate);
    class_BlendFuncFrame.ctor([]() { return new cocostudio::timeline::BlendFuncFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("getBlendFunc", &cocostudio::timeline::BlendFuncFrame::getBlendFunc)
        .member_function("setBlendFunc", &cocostudio::timeline::BlendFuncFrame::setBlendFunc)
        .static_function("create", &cocostudio::timeline::BlendFuncFrame::create)
        .auto_wrap_objects(true);
    mod.class_("BlendFuncFrame", class_BlendFuncFrame);
}
static void js_register_ax_studio_PlayableFrame(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::PlayableFrame> class_PlayableFrame(isolate);
    class_PlayableFrame.ctor([]() { return new cocostudio::timeline::PlayableFrame(); })
        .template inherit<cocostudio::timeline::Frame>()
        .member_function("getPlayableAct", &cocostudio::timeline::PlayableFrame::getPlayableAct)
        .member_function("setPlayableAct", &cocostudio::timeline::PlayableFrame::setPlayableAct)
        .static_function("create", &cocostudio::timeline::PlayableFrame::create)
        .auto_wrap_objects(true);
    mod.class_("PlayableFrame", class_PlayableFrame);
}
static void js_register_ax_studio_Timeline(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::Timeline> class_Timeline(isolate);
    class_Timeline.ctor([]() { return new cocostudio::timeline::Timeline(); })
        .template inherit<ax::Object>()
        .member_function("gotoFrame", &cocostudio::timeline::Timeline::gotoFrame)
        .member_function("stepToFrame", &cocostudio::timeline::Timeline::stepToFrame)
        .member_function("getFrames", &cocostudio::timeline::Timeline::getFrames)
        .member_function("addFrame", &cocostudio::timeline::Timeline::addFrame)
        .member_function("insertFrame", &cocostudio::timeline::Timeline::insertFrame)
        .member_function("removeFrame", &cocostudio::timeline::Timeline::removeFrame)
        .member_function("setActionTag", &cocostudio::timeline::Timeline::setActionTag)
        .member_function("getActionTag", &cocostudio::timeline::Timeline::getActionTag)
        .member_function("setNode", &cocostudio::timeline::Timeline::setNode)
        .member_function("getNode", &cocostudio::timeline::Timeline::getNode)
        .member_function("setActionTimeline", &cocostudio::timeline::Timeline::setActionTimeline)
        .member_function("getActionTimeline", &cocostudio::timeline::Timeline::getActionTimeline)
        .member_function("clone", &cocostudio::timeline::Timeline::clone)
        .static_function("create", &cocostudio::timeline::Timeline::create)
        .auto_wrap_objects(true);
    mod.class_("Timeline", class_Timeline);
}
static void js_register_ax_studio_ActionTimelineData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::ActionTimelineData> class_ActionTimelineData(isolate);
    class_ActionTimelineData.ctor([]() { return new cocostudio::timeline::ActionTimelineData(); })
        .template inherit<ax::Object>()
        .member_function("setActionTag", &cocostudio::timeline::ActionTimelineData::setActionTag)
        .member_function("getActionTag", &cocostudio::timeline::ActionTimelineData::getActionTag)
        .member_function("init", &cocostudio::timeline::ActionTimelineData::init)
        .static_function("create", &cocostudio::timeline::ActionTimelineData::create)
        .auto_wrap_objects(true);
    mod.class_("ActionTimelineData", class_ActionTimelineData);
}
static void js_register_ax_studio_ActionTimeline(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::ActionTimeline> class_ActionTimeline(isolate);
    class_ActionTimeline.ctor([]() { return new cocostudio::timeline::ActionTimeline(); })
        .template inherit<ax::Action>()
        .member_function("play", &cocostudio::timeline::ActionTimeline::play)
        .member_function("init", &cocostudio::timeline::ActionTimeline::init)
        .member_function(
            "gotoFrameAndPlay",
            [](cocostudio::timeline::ActionTimeline* self, int arg0, bool arg1) { self->gotoFrameAndPlay(arg0, arg1); },
            [](cocostudio::timeline::ActionTimeline* self, int arg0) { self->gotoFrameAndPlay(arg0); },
            [](cocostudio::timeline::ActionTimeline* self, int arg0, int arg1, bool arg2) { self->gotoFrameAndPlay(arg0, arg1, arg2); },
            [](cocostudio::timeline::ActionTimeline* self, int arg0, int arg1, int arg2, bool arg3)
            { self->gotoFrameAndPlay(arg0, arg1, arg2, arg3); })
        .member_function("gotoFrameAndPause", &cocostudio::timeline::ActionTimeline::gotoFrameAndPause)
        .member_function("pause", &cocostudio::timeline::ActionTimeline::pause)
        .member_function("resume", &cocostudio::timeline::ActionTimeline::resume)
        .member_function("isPlaying", &cocostudio::timeline::ActionTimeline::isPlaying)
        .member_function("setTimeSpeed", &cocostudio::timeline::ActionTimeline::setTimeSpeed)
        .member_function("getTimeSpeed", &cocostudio::timeline::ActionTimeline::getTimeSpeed)
        .member_function("setDuration", &cocostudio::timeline::ActionTimeline::setDuration)
        .member_function("getDuration", &cocostudio::timeline::ActionTimeline::getDuration)
        .member_function("getStartFrame", &cocostudio::timeline::ActionTimeline::getStartFrame)
        .member_function("getEndFrame", &cocostudio::timeline::ActionTimeline::getEndFrame)
        .member_function("setCurrentFrame", &cocostudio::timeline::ActionTimeline::setCurrentFrame)
        .member_function("getCurrentFrame", &cocostudio::timeline::ActionTimeline::getCurrentFrame)
        .member_function("addTimeline", &cocostudio::timeline::ActionTimeline::addTimeline)
        .member_function("removeTimeline", &cocostudio::timeline::ActionTimeline::removeTimeline)
        .member_function("getTimelines", &cocostudio::timeline::ActionTimeline::getTimelines)
        .member_function("addAnimationInfo", &cocostudio::timeline::ActionTimeline::addAnimationInfo)
        .member_function("removeAnimationInfo", &cocostudio::timeline::ActionTimeline::removeAnimationInfo)
        .member_function("IsAnimationInfoExists", &cocostudio::timeline::ActionTimeline::IsAnimationInfoExists)
        .member_function("getAnimationInfo", &cocostudio::timeline::ActionTimeline::getAnimationInfo)
        .member_function("setAnimationEndCallFunc", &cocostudio::timeline::ActionTimeline::setAnimationEndCallFunc)
        .member_function("clearFrameEventCallFunc", &cocostudio::timeline::ActionTimeline::clearFrameEventCallFunc)
        .member_function("setLastFrameCallFunc", &cocostudio::timeline::ActionTimeline::setLastFrameCallFunc)
        .member_function("clearLastFrameCallFunc", &cocostudio::timeline::ActionTimeline::clearLastFrameCallFunc)
        .member_function("addFrameEndCallFunc", &cocostudio::timeline::ActionTimeline::addFrameEndCallFunc)
        .member_function("removeFrameEndCallFunc", &cocostudio::timeline::ActionTimeline::removeFrameEndCallFunc)
        .member_function("removeFrameEndCallFuncs", &cocostudio::timeline::ActionTimeline::removeFrameEndCallFuncs)
        .member_function("clearFrameEndCallFuncs", &cocostudio::timeline::ActionTimeline::clearFrameEndCallFuncs)
        .member_function("start", &cocostudio::timeline::ActionTimeline::start)
        .static_function("create", &cocostudio::timeline::ActionTimeline::create)
        .auto_wrap_objects(true);
    mod.class_("ActionTimeline", class_ActionTimeline);
}
static void js_register_ax_studio_ActionTimelineNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::ActionTimelineNode> class_ActionTimelineNode(isolate);
    class_ActionTimelineNode.ctor([]() { return new cocostudio::timeline::ActionTimelineNode(); })
        .template inherit<ax::Node>()
        // .member_function("init", &cocostudio::timeline::ActionTimelineNode::init)
        .member_function("setRoot", &cocostudio::timeline::ActionTimelineNode::setRoot)
        .member_function("getRoot", &cocostudio::timeline::ActionTimelineNode::getRoot)
        .member_function("setActionTimeline", &cocostudio::timeline::ActionTimelineNode::setActionTimeline)
        .member_function("getActionTimeline", &cocostudio::timeline::ActionTimelineNode::getActionTimeline)
        .static_function("create", &cocostudio::timeline::ActionTimelineNode::create)
        .auto_wrap_objects(true);
    mod.class_("ActionTimelineNode", class_ActionTimelineNode);
}
static void js_register_ax_studio_BoneNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::BoneNode> class_BoneNode(isolate);
    class_BoneNode.ctor([]() { return new cocostudio::timeline::BoneNode(); })
        .template inherit<ax::Node>()
        .member_function(
            "getChildBones",
            [](cocostudio::timeline::BoneNode* self) { return self->getChildBones(); },
            [](cocostudio::timeline::BoneNode* self) { return self->getChildBones(); })
        .member_function("getRootSkeletonNode", &cocostudio::timeline::BoneNode::getRootSkeletonNode)
        .member_function("getAllSubBones", &cocostudio::timeline::BoneNode::getAllSubBones)
        .member_function(
            "addSkin",
            [](cocostudio::timeline::BoneNode* self, ax::Node* arg0, bool arg1, bool arg2) { self->addSkin(arg0, arg1, arg2); },
            [](cocostudio::timeline::BoneNode* self, ax::Node* arg0, bool arg1) { self->addSkin(arg0, arg1); })
        .member_function(
            "displaySkin",
            [](cocostudio::timeline::BoneNode* self, std::string_view arg0, bool arg1) { self->displaySkin(arg0, arg1); },
            [](cocostudio::timeline::BoneNode* self, ax::Node* arg0, bool arg1) { self->displaySkin(arg0, arg1); })
        .member_function("getVisibleSkins", &cocostudio::timeline::BoneNode::getVisibleSkins)
        .member_function(
            "getSkins",
            [](cocostudio::timeline::BoneNode* self) { return self->getSkins(); },
            [](cocostudio::timeline::BoneNode* self) { return self->getSkins(); })
        .member_function("getAllSubSkins", &cocostudio::timeline::BoneNode::getAllSubSkins)
        .member_function("setBlendFunc", &cocostudio::timeline::BoneNode::setBlendFunc)
        .member_function("getBlendFunc", &cocostudio::timeline::BoneNode::getBlendFunc)
        .member_function("setDebugDrawEnabled", &cocostudio::timeline::BoneNode::setDebugDrawEnabled)
        .member_function("isDebugDrawEnabled", &cocostudio::timeline::BoneNode::isDebugDrawEnabled)
        .member_function("setDebugDrawLength", &cocostudio::timeline::BoneNode::setDebugDrawLength)
        .member_function("getDebugDrawLength", &cocostudio::timeline::BoneNode::getDebugDrawLength)
        .member_function("setDebugDrawWidth", &cocostudio::timeline::BoneNode::setDebugDrawWidth)
        .member_function("getDebugDrawWidth", &cocostudio::timeline::BoneNode::getDebugDrawWidth)
        .member_function("setDebugDrawColor", &cocostudio::timeline::BoneNode::setDebugDrawColor)
        .member_function("getDebugDrawColor", &cocostudio::timeline::BoneNode::getDebugDrawColor)
        .member_function("getVisibleSkinsRect", &cocostudio::timeline::BoneNode::getVisibleSkinsRect)
        .static_function(
            "create",
            [](int arg0) { return cocostudio::timeline::BoneNode::create(arg0); },
            []() { return cocostudio::timeline::BoneNode::create(); })
        .auto_wrap_objects(true);
    mod.class_("BoneNode", class_BoneNode);
}
static void js_register_ax_studio_SkeletonNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::timeline::SkeletonNode> class_SkeletonNode(isolate);
    class_SkeletonNode.ctor([]() { return new cocostudio::timeline::SkeletonNode(); })
        .template inherit<cocostudio::timeline::BoneNode>()
        .member_function("getBoneNode", &cocostudio::timeline::SkeletonNode::getBoneNode)
        .member_function("getAllSubBonesMap", &cocostudio::timeline::SkeletonNode::getAllSubBonesMap)
        .member_function(
            "changeSkins",
            [](cocostudio::timeline::SkeletonNode* self, std::string_view arg0) { self->changeSkins(arg0); },
            [](cocostudio::timeline::SkeletonNode* self, tsl::robin_map<std::string, std::string, axstd::string_hash, axstd::equal_to> arg0)
            { self->changeSkins(arg0); })
        .member_function("addSkinGroup", &cocostudio::timeline::SkeletonNode::addSkinGroup)
        .static_function("create", &cocostudio::timeline::SkeletonNode::create)
        .auto_wrap_objects(true);
    mod.class_("SkeletonNode", class_SkeletonNode);
}
static void js_register_ax_studio_ComExtensionData(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<cocostudio::ComExtensionData> class_ComExtensionData(isolate);
    class_ComExtensionData.ctor([]() { return new cocostudio::ComExtensionData(); })
        .template inherit<ax::Component>()
        .member_function("setCustomProperty", &cocostudio::ComExtensionData::setCustomProperty)
        .member_function("getCustomProperty", &cocostudio::ComExtensionData::getCustomProperty)
        .member_function("setActionTag", &cocostudio::ComExtensionData::setActionTag)
        .member_function("getActionTag", &cocostudio::ComExtensionData::getActionTag)
        .static_function("createInstance", &cocostudio::ComExtensionData::createInstance)
        .static_function("create", &cocostudio::ComExtensionData::create)
        .auto_wrap_objects(true);
    mod.class_("ComExtensionData", class_ComExtensionData);
}
void js_register_all_ax_studio(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ccs");
    js_register_ax_studio_ActionFrame(mod);
    js_register_ax_studio_ActionMoveFrame(mod);
    js_register_ax_studio_ActionScaleFrame(mod);
    js_register_ax_studio_ActionRotationFrame(mod);
    js_register_ax_studio_ActionFadeFrame(mod);
    js_register_ax_studio_ActionTintFrame(mod);
    js_register_ax_studio_ActionObject(mod);
    js_register_ax_studio_ActionManagerEx(mod);
    js_register_ax_studio_BaseData(mod);
    js_register_ax_studio_DisplayData(mod);
    js_register_ax_studio_SpriteDisplayData(mod);
    js_register_ax_studio_ArmatureDisplayData(mod);
    js_register_ax_studio_ParticleDisplayData(mod);
    js_register_ax_studio_BoneData(mod);
    js_register_ax_studio_ArmatureData(mod);
    js_register_ax_studio_FrameData(mod);
    js_register_ax_studio_MovementBoneData(mod);
    js_register_ax_studio_MovementData(mod);
    js_register_ax_studio_AnimationData(mod);
    js_register_ax_studio_ContourData(mod);
    js_register_ax_studio_TextureData(mod);
    js_register_ax_studio_Tween(mod);
    js_register_ax_studio_DisplayManager(mod);
    js_register_ax_studio_Bone(mod);
    js_register_ax_studio_BatchNode(mod);
    js_register_ax_studio_ArmatureAnimation(mod);
    js_register_ax_studio_ArmatureDataManager(mod);
    js_register_ax_studio_Armature(mod);
    js_register_ax_studio_Skin(mod);
    js_register_ax_studio_ComAttribute(mod);
    js_register_ax_studio_ComAudio(mod);
    js_register_ax_studio_ComController(mod);
    js_register_ax_studio_ComRender(mod);
    js_register_ax_studio_GUIReader(mod);
    js_register_ax_studio_SceneReader(mod);
    js_register_ax_studio_ActionTimelineCache(mod);
    js_register_ax_studio_Frame(mod);
    js_register_ax_studio_VisibleFrame(mod);
    js_register_ax_studio_TextureFrame(mod);
    js_register_ax_studio_RotationFrame(mod);
    js_register_ax_studio_SkewFrame(mod);
    js_register_ax_studio_RotationSkewFrame(mod);
    js_register_ax_studio_PositionFrame(mod);
    js_register_ax_studio_ScaleFrame(mod);
    js_register_ax_studio_AnchorPointFrame(mod);
    js_register_ax_studio_InnerActionFrame(mod);
    js_register_ax_studio_ColorFrame(mod);
    js_register_ax_studio_AlphaFrame(mod);
    js_register_ax_studio_EventFrame(mod);
    js_register_ax_studio_ZOrderFrame(mod);
    js_register_ax_studio_BlendFuncFrame(mod);
    js_register_ax_studio_PlayableFrame(mod);
    js_register_ax_studio_Timeline(mod);
    js_register_ax_studio_ActionTimelineData(mod);
    js_register_ax_studio_ActionTimeline(mod);
    js_register_ax_studio_ActionTimelineNode(mod);
    js_register_ax_studio_BoneNode(mod);
    js_register_ax_studio_SkeletonNode(mod);
    js_register_ax_studio_ComExtensionData(mod);
}
