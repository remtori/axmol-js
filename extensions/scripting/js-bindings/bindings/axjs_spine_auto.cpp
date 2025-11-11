#include "js-bindings/bindings/axjs_spine_auto.hpp"
#include "spine/spine-cocos2dx.h"
#include "js-bindings/manual/JSConversions.h"
static void js_register_ax_spine_SkeletonRenderer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<spine::SkeletonRenderer> class_SkeletonRenderer(isolate);
    class_SkeletonRenderer
        .ctor([](spine::Skeleton* arg0) { return new spine::SkeletonRenderer(arg0); },
              [](spine::Skeleton* arg0, bool arg1) { return new spine::SkeletonRenderer(arg0, arg1); },
              [](spine::Skeleton* arg0, bool arg1, bool arg2) { return new spine::SkeletonRenderer(arg0, arg1, arg2); },
              [](spine::Skeleton* arg0, bool arg1, bool arg2, bool arg3) { return new spine::SkeletonRenderer(arg0, arg1, arg2, arg3); },
              []() { return new spine::SkeletonRenderer(); },
              [](spine::SkeletonData* arg0) { return new spine::SkeletonRenderer(arg0); },
              [](spine::SkeletonData* arg0, bool arg1) { return new spine::SkeletonRenderer(arg0, arg1); },
              [](std::string arg0, spine::Atlas* arg1) { return new spine::SkeletonRenderer(arg0, arg1); },
              [](std::string arg0, spine::Atlas* arg1, float arg2) { return new spine::SkeletonRenderer(arg0, arg1, arg2); },
              [](std::string arg0, std::string arg1) { return new spine::SkeletonRenderer(arg0, arg1); },
              [](std::string arg0, std::string arg1, float arg2) { return new spine::SkeletonRenderer(arg0, arg1, arg2); })
        .template inherit<ax::Node>()
        .member_function("getSkeleton", &spine::SkeletonRenderer::getSkeleton)
        .member_function("setTimeScale", &spine::SkeletonRenderer::setTimeScale)
        .member_function("getTimeScale", &spine::SkeletonRenderer::getTimeScale)
        .member_function("setDebugSlotsEnabled", &spine::SkeletonRenderer::setDebugSlotsEnabled)
        .member_function("getDebugSlotsEnabled", &spine::SkeletonRenderer::getDebugSlotsEnabled)
        .member_function("setDebugBonesEnabled", &spine::SkeletonRenderer::setDebugBonesEnabled)
        .member_function("getDebugBonesEnabled", &spine::SkeletonRenderer::getDebugBonesEnabled)
        .member_function("setDebugMeshesEnabled", &spine::SkeletonRenderer::setDebugMeshesEnabled)
        .member_function("getDebugMeshesEnabled", &spine::SkeletonRenderer::getDebugMeshesEnabled)
        .member_function("setDebugBoundingRectEnabled", &spine::SkeletonRenderer::setDebugBoundingRectEnabled)
        .member_function("getDebugBoundingRectEnabled", &spine::SkeletonRenderer::getDebugBoundingRectEnabled)
        .member_function("setToSetupPose", &spine::SkeletonRenderer::setToSetupPose)
        .member_function("setBonesToSetupPose", &spine::SkeletonRenderer::setBonesToSetupPose)
        .member_function("setSlotsToSetupPose", &spine::SkeletonRenderer::setSlotsToSetupPose)
        .member_function(
            "setSkin",
            [](spine::SkeletonRenderer* self, const char* arg0) { self->setSkin(arg0); },
            [](spine::SkeletonRenderer* self, std::string arg0) { self->setSkin(arg0); })
        .member_function(
            "setAttachment",
            [](spine::SkeletonRenderer* self, std::string arg0, const char* arg1) { return self->setAttachment(arg0, arg1); },
            [](spine::SkeletonRenderer* self, std::string arg0, std::string arg1) { return self->setAttachment(arg0, arg1); })
        .member_function("setTwoColorTint", &spine::SkeletonRenderer::setTwoColorTint)
        .member_function("isTwoColorTint", &spine::SkeletonRenderer::isTwoColorTint)
        .member_function("setSlotsRange", &spine::SkeletonRenderer::setSlotsRange)
        .member_function("setBlendFunc", &spine::SkeletonRenderer::setBlendFunc)
        .member_function("getBlendFunc", &spine::SkeletonRenderer::getBlendFunc)
        .member_function(
            "initWithSkeleton",
            [](spine::SkeletonRenderer* self, spine::Skeleton* arg0) { self->initWithSkeleton(arg0); },
            [](spine::SkeletonRenderer* self, spine::Skeleton* arg0, bool arg1) { self->initWithSkeleton(arg0, arg1); },
            [](spine::SkeletonRenderer* self, spine::Skeleton* arg0, bool arg1, bool arg2) { self->initWithSkeleton(arg0, arg1, arg2); },
            [](spine::SkeletonRenderer* self, spine::Skeleton* arg0, bool arg1, bool arg2, bool arg3)
            { self->initWithSkeleton(arg0, arg1, arg2, arg3); })
        .member_function(
            "initWithData",
            [](spine::SkeletonRenderer* self, spine::SkeletonData* arg0) { self->initWithData(arg0); },
            [](spine::SkeletonRenderer* self, spine::SkeletonData* arg0, bool arg1) { self->initWithData(arg0, arg1); })
        .member_function(
            "initWithJsonFile",
            [](spine::SkeletonRenderer* self, std::string arg0, std::string arg1) { self->initWithJsonFile(arg0, arg1); },
            [](spine::SkeletonRenderer* self, std::string arg0, std::string arg1, float arg2) { self->initWithJsonFile(arg0, arg1, arg2); },
            [](spine::SkeletonRenderer* self, std::string arg0, spine::Atlas* arg1) { self->initWithJsonFile(arg0, arg1); },
            [](spine::SkeletonRenderer* self, std::string arg0, spine::Atlas* arg1, float arg2)
            { self->initWithJsonFile(arg0, arg1, arg2); })
        .member_function(
            "initWithBinaryFile",
            [](spine::SkeletonRenderer* self, std::string arg0, std::string arg1) { self->initWithBinaryFile(arg0, arg1); },
            [](spine::SkeletonRenderer* self, std::string arg0, std::string arg1, float arg2)
            { self->initWithBinaryFile(arg0, arg1, arg2); },
            [](spine::SkeletonRenderer* self, std::string arg0, spine::Atlas* arg1) { self->initWithBinaryFile(arg0, arg1); },
            [](spine::SkeletonRenderer* self, std::string arg0, spine::Atlas* arg1, float arg2)
            { self->initWithBinaryFile(arg0, arg1, arg2); })
        .member_function("initialize", &spine::SkeletonRenderer::initialize)
        .static_function("create", &spine::SkeletonRenderer::create)
        .static_function(
            "createWithSkeleton",
            [](spine::Skeleton* arg0) { return spine::SkeletonRenderer::createWithSkeleton(arg0); },
            [](spine::Skeleton* arg0, bool arg1) { return spine::SkeletonRenderer::createWithSkeleton(arg0, arg1); },
            [](spine::Skeleton* arg0, bool arg1, bool arg2) { return spine::SkeletonRenderer::createWithSkeleton(arg0, arg1, arg2); })
        .static_function(
            "createWithFile",
            [](std::string arg0, std::string arg1) { return spine::SkeletonRenderer::createWithFile(arg0, arg1); },
            [](std::string arg0, std::string arg1, float arg2) { return spine::SkeletonRenderer::createWithFile(arg0, arg1, arg2); },
            [](std::string arg0, spine::Atlas* arg1) { return spine::SkeletonRenderer::createWithFile(arg0, arg1); },
            [](std::string arg0, spine::Atlas* arg1, float arg2) { return spine::SkeletonRenderer::createWithFile(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("SkeletonRenderer", class_SkeletonRenderer);
}
static void js_register_ax_spine_SkeletonAnimation(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<spine::SkeletonAnimation> class_SkeletonAnimation(isolate);
    class_SkeletonAnimation.template inherit<spine::SkeletonRenderer>()
        .member_function("setMix", &spine::SkeletonAnimation::setMix)
        .member_function("setEmptyAnimation", &spine::SkeletonAnimation::setEmptyAnimation)
        .member_function("setEmptyAnimations", &spine::SkeletonAnimation::setEmptyAnimations)
        .member_function(
            "addEmptyAnimation",
            [](spine::SkeletonAnimation* self, int arg0, float arg1) { return self->addEmptyAnimation(arg0, arg1); },
            [](spine::SkeletonAnimation* self, int arg0, float arg1, float arg2) { return self->addEmptyAnimation(arg0, arg1, arg2); })
        .member_function("findAnimation", &spine::SkeletonAnimation::findAnimation)
        .member_function("clearTracks", &spine::SkeletonAnimation::clearTracks)
        .member_function(
            "clearTrack",
            [](spine::SkeletonAnimation* self) { self->clearTrack(); },
            [](spine::SkeletonAnimation* self, int arg0) { self->clearTrack(arg0); })
        .member_function("setStartListener", &spine::SkeletonAnimation::setStartListener)
        .member_function("setInterruptListener", &spine::SkeletonAnimation::setInterruptListener)
        .member_function("setEndListener", &spine::SkeletonAnimation::setEndListener)
        .member_function("setDisposeListener", &spine::SkeletonAnimation::setDisposeListener)
        .member_function("setCompleteListener", &spine::SkeletonAnimation::setCompleteListener)
        .member_function("setEventListener", &spine::SkeletonAnimation::setEventListener)
        .member_function("setPreUpdateWorldTransformsListener", &spine::SkeletonAnimation::setPreUpdateWorldTransformsListener)
        .member_function("setPostUpdateWorldTransformsListener", &spine::SkeletonAnimation::setPostUpdateWorldTransformsListener)
        .member_function("setTrackStartListener", &spine::SkeletonAnimation::setTrackStartListener)
        .member_function("setTrackInterruptListener", &spine::SkeletonAnimation::setTrackInterruptListener)
        .member_function("setTrackEndListener", &spine::SkeletonAnimation::setTrackEndListener)
        .member_function("setTrackDisposeListener", &spine::SkeletonAnimation::setTrackDisposeListener)
        .member_function("setTrackCompleteListener", &spine::SkeletonAnimation::setTrackCompleteListener)
        .member_function("setTrackEventListener", &spine::SkeletonAnimation::setTrackEventListener)
        .member_function("setUpdateOnlyIfVisible", &spine::SkeletonAnimation::setUpdateOnlyIfVisible)
        .static_function("create", &spine::SkeletonAnimation::create)
        .static_function(
            "createWithJsonFile",
            [](std::string arg0, std::string arg1) { return spine::SkeletonAnimation::createWithJsonFile(arg0, arg1); },
            [](std::string arg0, std::string arg1, float arg2) { return spine::SkeletonAnimation::createWithJsonFile(arg0, arg1, arg2); },
            [](std::string arg0, spine::Atlas* arg1) { return spine::SkeletonAnimation::createWithJsonFile(arg0, arg1); },
            [](std::string arg0, spine::Atlas* arg1, float arg2) { return spine::SkeletonAnimation::createWithJsonFile(arg0, arg1, arg2); })
        .static_function(
            "createWithBinaryFile",
            [](std::string arg0, std::string arg1) { return spine::SkeletonAnimation::createWithBinaryFile(arg0, arg1); },
            [](std::string arg0, std::string arg1, float arg2) { return spine::SkeletonAnimation::createWithBinaryFile(arg0, arg1, arg2); },
            [](std::string arg0, spine::Atlas* arg1) { return spine::SkeletonAnimation::createWithBinaryFile(arg0, arg1); },
            [](std::string arg0, spine::Atlas* arg1, float arg2)
            { return spine::SkeletonAnimation::createWithBinaryFile(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("SkeletonAnimation", class_SkeletonAnimation);
}
void js_register_all_ax_spine(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("sp");
    js_register_ax_spine_SkeletonRenderer(mod);
    js_register_ax_spine_SkeletonAnimation(mod);
}
