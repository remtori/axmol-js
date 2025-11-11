#include "js-bindings/bindings/axjs_webview_auto.hpp"
#include "axmol/ui/UIWebView/UIWebView.h"
#include "js-bindings/manual/JSConversions.h"
static void js_register_ax_webview_WebView(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::WebView> class_WebView(isolate);
    class_WebView.ctor([]() { return new ax::ui::WebView(); })
        .template inherit<ax::ui::Widget>()
        .member_function("setJavascriptInterfaceScheme", &ax::ui::WebView::setJavascriptInterfaceScheme)
        .member_function(
            "loadHTMLString",
            [](ax::ui::WebView* self, std::string_view arg0) { self->loadHTMLString(arg0); },
            [](ax::ui::WebView* self, std::string_view arg0, std::string_view arg1) { self->loadHTMLString(arg0, arg1); })
        .member_function(
            "loadURL",
            [](ax::ui::WebView* self, std::string_view arg0, bool arg1) { self->loadURL(arg0, arg1); },
            [](ax::ui::WebView* self, std::string_view arg0) { self->loadURL(arg0); })
        .member_function("loadFile", &ax::ui::WebView::loadFile)
        .member_function("stopLoading", &ax::ui::WebView::stopLoading)
        .member_function("reload", &ax::ui::WebView::reload)
        .member_function("canGoBack", &ax::ui::WebView::canGoBack)
        .member_function("canGoForward", &ax::ui::WebView::canGoForward)
        .member_function("goBack", &ax::ui::WebView::goBack)
        .member_function("goForward", &ax::ui::WebView::goForward)
        .member_function("evaluateJS", &ax::ui::WebView::evaluateJS)
        .member_function("setScalesPageToFit", &ax::ui::WebView::setScalesPageToFit)
        .member_function("getOnJSCallback", &ax::ui::WebView::getOnJSCallback)
        .member_function("setBounces", &ax::ui::WebView::setBounces)
        .member_function("setOpacityWebView", &ax::ui::WebView::setOpacityWebView)
        .member_function("getOpacityWebView", &ax::ui::WebView::getOpacityWebView)
        .member_function("setBackgroundTransparent", &ax::ui::WebView::setBackgroundTransparent)
        .static_function("create", &ax::ui::WebView::create)
        .auto_wrap_objects(true);
    mod.class_("WebView", class_WebView);
}
void js_register_all_ax_webview(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("axui");
    js_register_ax_webview_WebView(mod);
}
