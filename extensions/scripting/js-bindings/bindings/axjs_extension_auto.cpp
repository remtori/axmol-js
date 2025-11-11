#include "js-bindings/bindings/axjs_extension_auto.hpp"
#include "extensions/cocos-ext.h"
#include "js-bindings/manual/JSConversions.h"
static void js_register_ax_extension_ScrollView(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::extension::ScrollView> class_ScrollView(isolate);
    class_ScrollView.ctor([]() { return new ax::extension::ScrollView(); })
        .template inherit<ax::Layer>()
        .member_function(
            "initWithViewSize",
            [](ax::extension::ScrollView* self, ax::Size arg0) { return self->initWithViewSize(arg0); },
            [](ax::extension::ScrollView* self, ax::Size arg0, ax::Node* arg1) { return self->initWithViewSize(arg0, arg1); })
        .member_function(
            "setContentOffset",
            [](ax::extension::ScrollView* self, ax::Vec2 arg0) { self->setContentOffset(arg0); },
            [](ax::extension::ScrollView* self, ax::Vec2 arg0, bool arg1) { self->setContentOffset(arg0, arg1); })
        .member_function("getContentOffset", &ax::extension::ScrollView::getContentOffset)
        .member_function("setContentOffsetInDuration", &ax::extension::ScrollView::setContentOffsetInDuration)
        .member_function("stopAnimatedContentOffset", &ax::extension::ScrollView::stopAnimatedContentOffset)
        .member_function(
            "setZoomScale",
            [](ax::extension::ScrollView* self, float arg0, bool arg1) { self->setZoomScale(arg0, arg1); },
            [](ax::extension::ScrollView* self, float arg0) { self->setZoomScale(arg0); })
        .member_function("getZoomScale", &ax::extension::ScrollView::getZoomScale)
        .member_function("setZoomScaleInDuration", &ax::extension::ScrollView::setZoomScaleInDuration)
        .member_function("setMinScale", &ax::extension::ScrollView::setMinScale)
        .member_function("setMaxScale", &ax::extension::ScrollView::setMaxScale)
        .member_function("minContainerOffset", &ax::extension::ScrollView::minContainerOffset)
        .member_function("maxContainerOffset", &ax::extension::ScrollView::maxContainerOffset)
        .member_function("isNodeVisible", &ax::extension::ScrollView::isNodeVisible)
        .member_function("setTouchEnabled", &ax::extension::ScrollView::setTouchEnabled)
        .member_function("isTouchEnabled", &ax::extension::ScrollView::isTouchEnabled)
        .member_function("setSwallowTouches", &ax::extension::ScrollView::setSwallowTouches)
        .member_function("isDragging", &ax::extension::ScrollView::isDragging)
        .member_function("isTouchMoved", &ax::extension::ScrollView::isTouchMoved)
        .member_function("isBounceable", &ax::extension::ScrollView::isBounceable)
        .member_function("setBounceable", &ax::extension::ScrollView::setBounceable)
        .member_function("getViewSize", &ax::extension::ScrollView::getViewSize)
        .member_function("setViewSize", &ax::extension::ScrollView::setViewSize)
        .member_function("getContainer", &ax::extension::ScrollView::getContainer)
        .member_function("setContainer", &ax::extension::ScrollView::setContainer)
        .member_function("getDirection", &ax::extension::ScrollView::getDirection)
        .member_function("setDirection", &ax::extension::ScrollView::setDirection)
        .member_function("updateInset", &ax::extension::ScrollView::updateInset)
        .member_function("isClippingToBounds", &ax::extension::ScrollView::isClippingToBounds)
        .member_function("setClippingToBounds", &ax::extension::ScrollView::setClippingToBounds)
        .member_function("onTouchBegan", &ax::extension::ScrollView::onTouchBegan)
        .member_function("onTouchMoved", &ax::extension::ScrollView::onTouchMoved)
        .member_function("onTouchEnded", &ax::extension::ScrollView::onTouchEnded)
        .member_function("onTouchCancelled", &ax::extension::ScrollView::onTouchCancelled)
        .member_function("updateTweenAction", &ax::extension::ScrollView::updateTweenAction)
        .member_function("hasVisibleParents", &ax::extension::ScrollView::hasVisibleParents)
        .static_function(
            "create",
            []() { return ax::extension::ScrollView::create(); },
            [](ax::Size arg0) { return ax::extension::ScrollView::create(arg0); },
            [](ax::Size arg0, ax::Node* arg1) { return ax::extension::ScrollView::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("ScrollView", class_ScrollView);
}
static void js_register_ax_extension_TableViewCell(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::extension::TableViewCell> class_TableViewCell(isolate);
    class_TableViewCell.ctor([]() { return new ax::extension::TableViewCell(); })
        .template inherit<ax::Node>()
        .member_function("getIdx", &ax::extension::TableViewCell::getIdx)
        .member_function("setIdx", &ax::extension::TableViewCell::setIdx)
        .member_function("reset", &ax::extension::TableViewCell::reset)
        .static_function("create", &ax::extension::TableViewCell::create)
        .auto_wrap_objects(true);
    mod.class_("TableViewCell", class_TableViewCell);
}
static void js_register_ax_extension_TableView(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::extension::TableView> class_TableView(isolate);
    class_TableView.ctor([]() { return new ax::extension::TableView(); })
        .template inherit<ax::extension::ScrollView>()
        .member_function(
            "initWithViewSize",
            [](ax::extension::TableView* self, ax::Size arg0) { return self->initWithViewSize(arg0); },
            [](ax::extension::TableView* self, ax::Size arg0, ax::Node* arg1) { return self->initWithViewSize(arg0, arg1); })
        .member_function("setVerticalFillOrder", &ax::extension::TableView::setVerticalFillOrder)
        .member_function("getVerticalFillOrder", &ax::extension::TableView::getVerticalFillOrder)
        .member_function("updateCellAtIndex", &ax::extension::TableView::updateCellAtIndex)
        .member_function("insertCellAtIndex", &ax::extension::TableView::insertCellAtIndex)
        .member_function("removeCellAtIndex", &ax::extension::TableView::removeCellAtIndex)
        .member_function("reloadData", &ax::extension::TableView::reloadData)
        .member_function("dequeueCell", &ax::extension::TableView::dequeueCell)
        .member_function("cellAtIndex", &ax::extension::TableView::cellAtIndex)
        .member_function("scrollViewDidScroll", &ax::extension::TableView::scrollViewDidScroll)
        .member_function("scrollViewDidZoom", &ax::extension::TableView::scrollViewDidZoom)
        .member_function("_updateContentSize", &ax::extension::TableView::_updateContentSize)
        .auto_wrap_objects(true);
    mod.class_("TableView", class_TableView);
}
static void js_register_ax_extension_AssetsManager(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::extension::AssetsManager> class_AssetsManager(isolate);
    class_AssetsManager
        .ctor([]() { return new ax::extension::AssetsManager(); },
              [](const char* arg0) { return new ax::extension::AssetsManager(arg0); },
              [](const char* arg0, const char* arg1) { return new ax::extension::AssetsManager(arg0, arg1); },
              [](const char* arg0, const char* arg1, const char* arg2) { return new ax::extension::AssetsManager(arg0, arg1, arg2); })
        .template inherit<ax::Node>()
        .member_function("checkUpdate", &ax::extension::AssetsManager::checkUpdate)
        .member_function("getPackageUrl", &ax::extension::AssetsManager::getPackageUrl)
        .member_function("setPackageUrl", &ax::extension::AssetsManager::setPackageUrl)
        .member_function("getVersionFileUrl", &ax::extension::AssetsManager::getVersionFileUrl)
        .member_function("setVersionFileUrl", &ax::extension::AssetsManager::setVersionFileUrl)
        .member_function("getVersion", &ax::extension::AssetsManager::getVersion)
        .member_function("deleteVersion", &ax::extension::AssetsManager::deleteVersion)
        .member_function("getStoragePath", &ax::extension::AssetsManager::getStoragePath)
        .member_function("setStoragePath", &ax::extension::AssetsManager::setStoragePath)
        .member_function("setConnectionTimeout", &ax::extension::AssetsManager::setConnectionTimeout)
        .member_function("getConnectionTimeout", &ax::extension::AssetsManager::getConnectionTimeout)
        .static_function("create", &ax::extension::AssetsManager::create)
        .auto_wrap_objects(true);
    mod.class_("AssetsManager", class_AssetsManager);
}
static void js_register_ax_extension_EventAssetsManagerEx(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::extension::EventAssetsManagerEx> class_EventAssetsManagerEx(isolate);
    class_EventAssetsManagerEx
        .ctor(
            [](std::string_view arg0, ax::extension::AssetsManagerEx* arg1, ax::extension::EventAssetsManagerEx::EventCode arg2)
            { return new ax::extension::EventAssetsManagerEx(arg0, arg1, arg2); },
            [](std::string_view arg0, ax::extension::AssetsManagerEx* arg1, ax::extension::EventAssetsManagerEx::EventCode arg2, float arg3)
            { return new ax::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3); },
            [](std::string_view arg0,
               ax::extension::AssetsManagerEx* arg1,
               ax::extension::EventAssetsManagerEx::EventCode arg2,
               float arg3,
               float arg4) { return new ax::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4); },
            [](std::string_view arg0,
               ax::extension::AssetsManagerEx* arg1,
               ax::extension::EventAssetsManagerEx::EventCode arg2,
               float arg3,
               float arg4,
               std::string_view arg5) { return new ax::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](std::string_view arg0,
               ax::extension::AssetsManagerEx* arg1,
               ax::extension::EventAssetsManagerEx::EventCode arg2,
               float arg3,
               float arg4,
               std::string_view arg5,
               std::string_view arg6) { return new ax::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4, arg5, arg6); },
            [](std::string_view arg0,
               ax::extension::AssetsManagerEx* arg1,
               ax::extension::EventAssetsManagerEx::EventCode arg2,
               float arg3,
               float arg4,
               std::string_view arg5,
               std::string_view arg6,
               int arg7) { return new ax::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); },
            [](std::string_view arg0,
               ax::extension::AssetsManagerEx* arg1,
               ax::extension::EventAssetsManagerEx::EventCode arg2,
               float arg3,
               float arg4,
               std::string_view arg5,
               std::string_view arg6,
               int arg7,
               int arg8) { return new ax::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); })
        .template inherit<ax::EventCustom>()
        .member_function("getEventCode", &ax::extension::EventAssetsManagerEx::getEventCode)
        .member_function("getCURLECode", &ax::extension::EventAssetsManagerEx::getCURLECode)
        .member_function("getCURLMCode", &ax::extension::EventAssetsManagerEx::getCURLMCode)
        .member_function("getMessage", &ax::extension::EventAssetsManagerEx::getMessage)
        .member_function("getAssetId", &ax::extension::EventAssetsManagerEx::getAssetId)
        .member_function("getAssetsManagerEx", &ax::extension::EventAssetsManagerEx::getAssetsManagerEx)
        .member_function("getPercent", &ax::extension::EventAssetsManagerEx::getPercent)
        .member_function("getPercentByFile", &ax::extension::EventAssetsManagerEx::getPercentByFile)
        .auto_wrap_objects(true);
    mod.class_("EventAssetsManagerEx", class_EventAssetsManagerEx);
}
static void js_register_ax_extension_Manifest(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::extension::Manifest> class_Manifest(isolate);
    class_Manifest.template inherit<ax::Object>()
        .member_function("isVersionLoaded", &ax::extension::Manifest::isVersionLoaded)
        .member_function("isLoaded", &ax::extension::Manifest::isLoaded)
        .member_function("getPackageUrl", &ax::extension::Manifest::getPackageUrl)
        .member_function("getManifestFileUrl", &ax::extension::Manifest::getManifestFileUrl)
        .member_function("getVersionFileUrl", &ax::extension::Manifest::getVersionFileUrl)
        .member_function("getVersion", &ax::extension::Manifest::getVersion)
        .member_function("getSearchPaths", &ax::extension::Manifest::getSearchPaths)
        .auto_wrap_objects(true);
    mod.class_("Manifest", class_Manifest);
}
static void js_register_ax_extension_AssetsManagerEx(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::extension::AssetsManagerEx> class_AssetsManagerEx(isolate);
    class_AssetsManagerEx.ctor([](std::string_view arg0, std::string_view arg1) { return new ax::extension::AssetsManagerEx(arg0, arg1); })
        .template inherit<ax::Object>()
        .member_function("checkUpdate", &ax::extension::AssetsManagerEx::checkUpdate)
        .member_function("update", &ax::extension::AssetsManagerEx::update)
        .member_function("downloadFailedAssets", &ax::extension::AssetsManagerEx::downloadFailedAssets)
        .member_function("getState", &ax::extension::AssetsManagerEx::getState)
        .member_function("getStoragePath", &ax::extension::AssetsManagerEx::getStoragePath)
        .member_function("getLocalManifest", &ax::extension::AssetsManagerEx::getLocalManifest)
        .member_function("getRemoteManifest", &ax::extension::AssetsManagerEx::getRemoteManifest)
        .member_function("getMaxConcurrentTask", &ax::extension::AssetsManagerEx::getMaxConcurrentTask)
        .member_function("setMaxConcurrentTask", &ax::extension::AssetsManagerEx::setMaxConcurrentTask)
        .member_function("setVersionCompareHandle", &ax::extension::AssetsManagerEx::setVersionCompareHandle)
        .member_function("setVerifyCallback", &ax::extension::AssetsManagerEx::setVerifyCallback)
        .static_function("create", &ax::extension::AssetsManagerEx::create)
        .auto_wrap_objects(true);
    mod.class_("AssetsManagerEx", class_AssetsManagerEx);
}
void js_register_all_ax_extension(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_extension_ScrollView(mod);
    js_register_ax_extension_TableViewCell(mod);
    js_register_ax_extension_TableView(mod);
    js_register_ax_extension_AssetsManager(mod);
    js_register_ax_extension_EventAssetsManagerEx(mod);
    js_register_ax_extension_Manifest(mod);
    js_register_ax_extension_AssetsManagerEx(mod);
}
