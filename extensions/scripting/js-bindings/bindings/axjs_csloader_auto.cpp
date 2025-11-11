#include "js-bindings/bindings/axjs_csloader_auto.hpp"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "js-bindings/manual/JSConversions.h"
static void js_register_ax_csloader_CSLoader(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::CSLoader> class_CSLoader(isolate);
    class_CSLoader.ctor([]() { return new ax::CSLoader(); })
        .member_function("init", &ax::CSLoader::init)
        .member_function("createNodeFromJson", &ax::CSLoader::createNodeFromJson)
        .member_function("loadNodeWithFile", &ax::CSLoader::loadNodeWithFile)
        .member_function("loadNodeWithContent", &ax::CSLoader::loadNodeWithContent)
        .member_function("setRecordJsonPath", &ax::CSLoader::setRecordJsonPath)
        .member_function("isRecordJsonPath", &ax::CSLoader::isRecordJsonPath)
        .member_function("setJsonPath", &ax::CSLoader::setJsonPath)
        .member_function("getJsonPath", &ax::CSLoader::getJsonPath)
        // .member_function("createNodeWithFlatBuffersFile", &ax::CSLoader::createNodeWithFlatBuffersFile)
        .member_function("bindCallback", &ax::CSLoader::bindCallback)
        .member_function("createNodeWithFlatBuffersForSimulator", &ax::CSLoader::createNodeWithFlatBuffersForSimulator)
        .static_function("getInstance", &ax::CSLoader::getInstance)
        .static_function("destroyInstance", &ax::CSLoader::destroyInstance)
        .static_function(
            "createNodeWithVisibleSize",
            [](std::string_view arg0, std::function<void(ax::Object*)> arg1)
            { return ax::CSLoader::createNodeWithVisibleSize(arg0, arg1); },
            [](std::string_view arg0) { return ax::CSLoader::createNodeWithVisibleSize(arg0); })
        .auto_wrap_objects(true);
    mod.class_("CSLoader", class_CSLoader);
}
void js_register_all_ax_csloader(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_csloader_CSLoader(mod);
}
