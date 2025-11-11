#include "js-bindings/bindings/axjs_fairygui_auto.hpp"
#include "fairygui/FairyGUI.h"
#include "fairygui/FairyGUIMacros.h"
#include "fairygui/utils/html/HtmlObject.h"
#include "js-bindings/manual/JSConversions.h"
static void js_register_ax_fairygui_InputEvent(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::InputEvent> class_InputEvent(isolate);
    class_InputEvent.ctor([]() { return new fairygui::InputEvent(); })
        .member_function("getTarget", &fairygui::InputEvent::getTarget)
        .member_function("getX", &fairygui::InputEvent::getX)
        .member_function("getY", &fairygui::InputEvent::getY)
        .member_function("getPosition", &fairygui::InputEvent::getPosition)
        .member_function("getTouch", &fairygui::InputEvent::getTouch)
        .member_function("getTouchId", &fairygui::InputEvent::getTouchId)
        .member_function("isDoubleClick", &fairygui::InputEvent::isDoubleClick)
        .member_function("getButton", &fairygui::InputEvent::getButton)
        .member_function("getKeyCode", &fairygui::InputEvent::getKeyCode)
        .member_function("isCtrlDown", &fairygui::InputEvent::isCtrlDown)
        .member_function("isAltDown", &fairygui::InputEvent::isAltDown)
        .member_function("isShiftDown", &fairygui::InputEvent::isShiftDown)
        .member_function("getMouseWheelDelta", &fairygui::InputEvent::getMouseWheelDelta)
        .member_function("getProcessor", &fairygui::InputEvent::getProcessor)
        .auto_wrap_objects(true);
    mod.class_("InputEvent", class_InputEvent);
}
static void js_register_ax_fairygui_EventContext(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::EventContext> class_EventContext(isolate);
    class_EventContext.ctor([]() { return new fairygui::EventContext(); })
        .member_function("getType", &fairygui::EventContext::getType)
        .member_function("getSender", &fairygui::EventContext::getSender)
        .member_function("getInput", &fairygui::EventContext::getInput)
        .member_function("stopPropagation", &fairygui::EventContext::stopPropagation)
        .member_function("preventDefault", &fairygui::EventContext::preventDefault)
        .member_function("isDefaultPrevented", &fairygui::EventContext::isDefaultPrevented)
        .member_function("captureTouch", &fairygui::EventContext::captureTouch)
        .member_function("uncaptureTouch", &fairygui::EventContext::uncaptureTouch)
        .auto_wrap_objects(true);
    mod.class_("EventContext", class_EventContext);
}
static void js_register_ax_fairygui_UIEventDispatcher(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::UIEventDispatcher> class_UIEventDispatcher(isolate);
    class_UIEventDispatcher.ctor([]() { return new fairygui::UIEventDispatcher(); })
        .template inherit<ax::Object>()
        .member_function("removeEventListeners", &fairygui::UIEventDispatcher::removeEventListeners)
        .member_function(
            "dispatchEvent",
            [](fairygui::UIEventDispatcher* self, int arg0) { return self->dispatchEvent(arg0); },
            [](fairygui::UIEventDispatcher* self, int arg0, void* arg1) { return self->dispatchEvent(arg0, arg1); },
            [](fairygui::UIEventDispatcher* self, int arg0, void* arg1, ax::Value arg2) { return self->dispatchEvent(arg0, arg1, arg2); })
        .member_function(
            "bubbleEvent",
            [](fairygui::UIEventDispatcher* self, int arg0) { return self->bubbleEvent(arg0); },
            [](fairygui::UIEventDispatcher* self, int arg0, void* arg1) { return self->bubbleEvent(arg0, arg1); },
            [](fairygui::UIEventDispatcher* self, int arg0, void* arg1, ax::Value arg2) { return self->bubbleEvent(arg0, arg1, arg2); })
        .member_function("isDispatchingEvent", &fairygui::UIEventDispatcher::isDispatchingEvent)
        .auto_wrap_objects(true);
    mod.class_("UIEventDispatcher", class_UIEventDispatcher);
}
static void js_register_ax_fairygui_GController(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GController> class_GController(isolate);
    class_GController.ctor([]() { return new fairygui::GController(); })
        .template inherit<fairygui::UIEventDispatcher>()
        .member_function("getParent", &fairygui::GController::getParent)
        .member_function("setParent", &fairygui::GController::setParent)
        .member_function("getSelectedIndex", &fairygui::GController::getSelectedIndex)
        .member_function(
            "setSelectedIndex",
            [](fairygui::GController* self, int arg0) { self->setSelectedIndex(arg0); },
            [](fairygui::GController* self, int arg0, bool arg1) { self->setSelectedIndex(arg0, arg1); })
        .member_function("getSelectedPage", &fairygui::GController::getSelectedPage)
        .member_function(
            "setSelectedPage",
            [](fairygui::GController* self, std::string arg0) { self->setSelectedPage(arg0); },
            [](fairygui::GController* self, std::string arg0, bool arg1) { self->setSelectedPage(arg0, arg1); })
        .member_function("getSelectedPageId", &fairygui::GController::getSelectedPageId)
        .member_function(
            "setSelectedPageId",
            [](fairygui::GController* self, std::string arg0) { self->setSelectedPageId(arg0); },
            [](fairygui::GController* self, std::string arg0, bool arg1) { self->setSelectedPageId(arg0, arg1); })
        .member_function("getPrevisousIndex", &fairygui::GController::getPrevisousIndex)
        .member_function("getPreviousPage", &fairygui::GController::getPreviousPage)
        .member_function("getPreviousPageId", &fairygui::GController::getPreviousPageId)
        .member_function("getPageCount", &fairygui::GController::getPageCount)
        .member_function("hasPage", &fairygui::GController::hasPage)
        .member_function("getPageIndexById", &fairygui::GController::getPageIndexById)
        .member_function("getPageNameById", &fairygui::GController::getPageNameById)
        .member_function("getPageId", &fairygui::GController::getPageId)
        .member_function("setOppositePageId", &fairygui::GController::setOppositePageId)
        .member_function("runActions", &fairygui::GController::runActions)
        .auto_wrap_objects(true);
    mod.class_("GController", class_GController);
}
static void js_register_ax_fairygui_GObject(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GObject> class_GObject(isolate);
    class_GObject.ctor([]() { return new fairygui::GObject(); })
        .template inherit<fairygui::UIEventDispatcher>()
        .member_function("getX", &fairygui::GObject::getX)
        .member_function("setX", &fairygui::GObject::setX)
        .member_function("getY", &fairygui::GObject::getY)
        .member_function("setY", &fairygui::GObject::setY)
        .member_function("getPosition", &fairygui::GObject::getPosition)
        .member_function("setPosition", &fairygui::GObject::setPosition)
        .member_function("getXMin", &fairygui::GObject::getXMin)
        .member_function("setXMin", &fairygui::GObject::setXMin)
        .member_function("getYMin", &fairygui::GObject::getYMin)
        .member_function("setYMin", &fairygui::GObject::setYMin)
        .member_function("isPixelSnapping", &fairygui::GObject::isPixelSnapping)
        .member_function("setPixelSnapping", &fairygui::GObject::setPixelSnapping)
        .member_function("getWidth", &fairygui::GObject::getWidth)
        .member_function("setWidth", &fairygui::GObject::setWidth)
        .member_function("getHeight", &fairygui::GObject::getHeight)
        .member_function("setHeight", &fairygui::GObject::setHeight)
        .member_function("getSize", &fairygui::GObject::getSize)
        .member_function(
            "setSize",
            [](fairygui::GObject* self, float arg0, float arg1) { self->setSize(arg0, arg1); },
            [](fairygui::GObject* self, float arg0, float arg1, bool arg2) { self->setSize(arg0, arg1, arg2); })
        .member_function(
            "center", [](fairygui::GObject* self) { self->center(); }, [](fairygui::GObject* self, bool arg0) { self->center(arg0); })
        .member_function("makeFullScreen", &fairygui::GObject::makeFullScreen)
        .member_function("getPivot", &fairygui::GObject::getPivot)
        .member_function(
            "setPivot",
            [](fairygui::GObject* self, float arg0, float arg1) { self->setPivot(arg0, arg1); },
            [](fairygui::GObject* self, float arg0, float arg1, bool arg2) { self->setPivot(arg0, arg1, arg2); })
        .member_function("isPivotAsAnchor", &fairygui::GObject::isPivotAsAnchor)
        .member_function("getScaleX", &fairygui::GObject::getScaleX)
        .member_function("setScaleX", &fairygui::GObject::setScaleX)
        .member_function("getScaleY", &fairygui::GObject::getScaleY)
        .member_function("setScaleY", &fairygui::GObject::setScaleY)
        .member_function("getScale", &fairygui::GObject::getScale)
        .member_function("setScale", &fairygui::GObject::setScale)
        .member_function("getSkewX", &fairygui::GObject::getSkewX)
        .member_function("setSkewX", &fairygui::GObject::setSkewX)
        .member_function("getSkewY", &fairygui::GObject::getSkewY)
        .member_function("setSkewY", &fairygui::GObject::setSkewY)
        .member_function("getRotation", &fairygui::GObject::getRotation)
        .member_function("setRotation", &fairygui::GObject::setRotation)
        .member_function("getAlpha", &fairygui::GObject::getAlpha)
        .member_function("setAlpha", &fairygui::GObject::setAlpha)
        .member_function("isGrayed", &fairygui::GObject::isGrayed)
        .member_function("setGrayed", &fairygui::GObject::setGrayed)
        .member_function("isVisible", &fairygui::GObject::isVisible)
        .member_function("setVisible", &fairygui::GObject::setVisible)
        .member_function("isTouchable", &fairygui::GObject::isTouchable)
        .member_function("setTouchable", &fairygui::GObject::setTouchable)
        .member_function("getSortingOrder", &fairygui::GObject::getSortingOrder)
        .member_function("setSortingOrder", &fairygui::GObject::setSortingOrder)
        .member_function("getGroup", &fairygui::GObject::getGroup)
        .member_function("setGroup", &fairygui::GObject::setGroup)
        .member_function("getText", &fairygui::GObject::getText)
        .member_function("setText", &fairygui::GObject::setText)
        .member_function("getIcon", &fairygui::GObject::getIcon)
        .member_function("setIcon", &fairygui::GObject::setIcon)
        .member_function("getTooltips", &fairygui::GObject::getTooltips)
        .member_function("setTooltips", &fairygui::GObject::setTooltips)
        .member_function("getBlendMode", &fairygui::GObject::getBlendMode)
        .member_function("setBlendMode", &fairygui::GObject::setBlendMode)
        .member_function("setData", &fairygui::GObject::setData)
        .member_function("getCustomData", &fairygui::GObject::getCustomData)
        .member_function("setCustomData", &fairygui::GObject::setCustomData)
        .member_function("isDraggable", &fairygui::GObject::isDraggable)
        .member_function("setDraggable", &fairygui::GObject::setDraggable)
        .member_function("setDragBounds", &fairygui::GObject::setDragBounds)
        .member_function(
            "startDrag",
            [](fairygui::GObject* self) { self->startDrag(); },
            [](fairygui::GObject* self, int arg0) { self->startDrag(arg0); })
        .member_function("stopDrag", &fairygui::GObject::stopDrag)
        .member_function("getResourceURL", &fairygui::GObject::getResourceURL)
        .member_function("getPackageItem", &fairygui::GObject::getPackageItem)
        .member_function(
            "globalToLocal",
            [](fairygui::GObject* self, ax::Rect arg0) { return self->globalToLocal(arg0); },
            [](fairygui::GObject* self, ax::Vec2 arg0) { return self->globalToLocal(arg0); })
        .member_function(
            "localToGlobal",
            [](fairygui::GObject* self, ax::Rect arg0) { return self->localToGlobal(arg0); },
            [](fairygui::GObject* self, ax::Vec2 arg0) { return self->localToGlobal(arg0); })
        .member_function("transformRect", &fairygui::GObject::transformRect)
        .member_function("relations", &fairygui::GObject::relations)
        .member_function(
            "addRelation",
            [](fairygui::GObject* self, fairygui::GObject* arg0, fairygui::RelationType arg1) { self->addRelation(arg0, arg1); },
            [](fairygui::GObject* self, fairygui::GObject* arg0, fairygui::RelationType arg1, bool arg2)
            { self->addRelation(arg0, arg1, arg2); })
        .member_function("removeRelation", &fairygui::GObject::removeRelation)
        .member_function("getGear", &fairygui::GObject::getGear)
        .member_function("checkGearController", &fairygui::GObject::checkGearController)
        .member_function("addDisplayLock", &fairygui::GObject::addDisplayLock)
        .member_function("releaseDisplayLock", &fairygui::GObject::releaseDisplayLock)
        .member_function("getParent", &fairygui::GObject::getParent)
        .member_function("findParent", &fairygui::GObject::findParent)
        .member_function("displayObject", &fairygui::GObject::displayObject)
        .member_function("getRoot", &fairygui::GObject::getRoot)
        .member_function("onStage", &fairygui::GObject::onStage)
        .member_function("removeFromParent", &fairygui::GObject::removeFromParent)
        .member_function("getProp", &fairygui::GObject::getProp)
        .member_function("setProp", &fairygui::GObject::setProp)
        .member_function("constructFromResource", &fairygui::GObject::constructFromResource)
        .member_function("hitTest", &fairygui::GObject::hitTest)
        .member_function("treeNode", &fairygui::GObject::treeNode)
        .static_function("getDraggingObject", &fairygui::GObject::getDraggingObject)
        .static_function("create", &fairygui::GObject::create)
        .auto_wrap_objects(true);
    mod.class_("GObject", class_GObject);
}
static void js_register_ax_fairygui_UIPackage(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::UIPackage> class_UIPackage(isolate);
    class_UIPackage.ctor([]() { return new fairygui::UIPackage(); })
        .template inherit<ax::Object>()
        .member_function("getId", &fairygui::UIPackage::getId)
        .member_function("getName", &fairygui::UIPackage::getName)
        .member_function("getItem", &fairygui::UIPackage::getItem)
        .member_function("getItemByName", &fairygui::UIPackage::getItemByName)
        .static_function("getById", &fairygui::UIPackage::getById)
        .static_function("getByName", &fairygui::UIPackage::getByName)
        .static_function("addPackage", &fairygui::UIPackage::addPackage)
        .static_function("removePackage", &fairygui::UIPackage::removePackage)
        .static_function("removeAllPackages", &fairygui::UIPackage::removeAllPackages)
        .static_function("createObject", &fairygui::UIPackage::createObject)
        .static_function("createObjectFromURL", &fairygui::UIPackage::createObjectFromURL)
        .static_function("getItemURL", &fairygui::UIPackage::getItemURL)
        .static_function("getItemByURL", &fairygui::UIPackage::getItemByURL)
        .static_function("normalizeURL", &fairygui::UIPackage::normalizeURL)
        .static_function("getEmptyTexture", &fairygui::UIPackage::getEmptyTexture)
        .static_function("getBranch", &fairygui::UIPackage::getBranch)
        .static_function("setBranch", &fairygui::UIPackage::setBranch)
        .static_function("getVar", &fairygui::UIPackage::getVar)
        .static_function("setVar", &fairygui::UIPackage::setVar)
        .auto_wrap_objects(true);
    mod.class_("UIPackage", class_UIPackage);
}
static void js_register_ax_fairygui_GImage(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GImage> class_GImage(isolate);
    class_GImage.ctor([]() { return new fairygui::GImage(); })
        .template inherit<fairygui::GObject>()
        .member_function("getFlip", &fairygui::GImage::getFlip)
        .member_function("setFlip", &fairygui::GImage::setFlip)
        .member_function("getColor", &fairygui::GImage::getColor)
        .member_function("setColor", &fairygui::GImage::setColor)
        .member_function("getFillMethod", &fairygui::GImage::getFillMethod)
        .member_function("setFillMethod", &fairygui::GImage::setFillMethod)
        .member_function("getFillOrigin", &fairygui::GImage::getFillOrigin)
        .member_function("setFillOrigin", &fairygui::GImage::setFillOrigin)
        .member_function("isFillClockwise", &fairygui::GImage::isFillClockwise)
        .member_function("setFillClockwise", &fairygui::GImage::setFillClockwise)
        .member_function("getFillAmount", &fairygui::GImage::getFillAmount)
        .member_function("setFillAmount", &fairygui::GImage::setFillAmount)
        .static_function("create", &fairygui::GImage::create)
        .auto_wrap_objects(true);
    mod.class_("GImage", class_GImage);
}
static void js_register_ax_fairygui_GMovieClip(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GMovieClip> class_GMovieClip(isolate);
    class_GMovieClip.ctor([]() { return new fairygui::GMovieClip(); })
        .template inherit<fairygui::GObject>()
        .member_function("isPlaying", &fairygui::GMovieClip::isPlaying)
        .member_function("setPlaying", &fairygui::GMovieClip::setPlaying)
        .member_function("getFrame", &fairygui::GMovieClip::getFrame)
        .member_function("setFrame", &fairygui::GMovieClip::setFrame)
        .member_function("getTimeScale", &fairygui::GMovieClip::getTimeScale)
        .member_function("setTimeScale", &fairygui::GMovieClip::setTimeScale)
        .member_function("advance", &fairygui::GMovieClip::advance)
        .member_function("getFlip", &fairygui::GMovieClip::getFlip)
        .member_function("setFlip", &fairygui::GMovieClip::setFlip)
        .member_function("getColor", &fairygui::GMovieClip::getColor)
        .member_function("setColor", &fairygui::GMovieClip::setColor)
        .static_function("create", &fairygui::GMovieClip::create)
        .auto_wrap_objects(true);
    mod.class_("GMovieClip", class_GMovieClip);
}
static void js_register_ax_fairygui_GTextField(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GTextField> class_GTextField(isolate);
    class_GTextField.template inherit<fairygui::GObject>()
        .member_function("isUBBEnabled", &fairygui::GTextField::isUBBEnabled)
        .member_function("setUBBEnabled", &fairygui::GTextField::setUBBEnabled)
        .member_function("getAutoSize", &fairygui::GTextField::getAutoSize)
        .member_function("setAutoSize", &fairygui::GTextField::setAutoSize)
        .member_function("isSingleLine", &fairygui::GTextField::isSingleLine)
        .member_function("setSingleLine", &fairygui::GTextField::setSingleLine)
        .member_function("getTextFormat", &fairygui::GTextField::getTextFormat)
        .member_function("applyTextFormat", &fairygui::GTextField::applyTextFormat)
        .member_function("getTextSize", &fairygui::GTextField::getTextSize)
        .member_function("getColor", &fairygui::GTextField::getColor)
        .member_function("setColor", &fairygui::GTextField::setColor)
        .member_function("getFontSize", &fairygui::GTextField::getFontSize)
        .member_function("setFontSize", &fairygui::GTextField::setFontSize)
        .member_function("getOutlineColor", &fairygui::GTextField::getOutlineColor)
        .member_function("setOutlineColor", &fairygui::GTextField::setOutlineColor)
        .member_function("setVar", &fairygui::GTextField::setVar)
        .member_function("flushVars", &fairygui::GTextField::flushVars)
        .auto_wrap_objects(true);
    mod.class_("GTextField", class_GTextField);
}
static void js_register_ax_fairygui_GBasicTextField(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GBasicTextField> class_GBasicTextField(isolate);
    class_GBasicTextField.ctor([]() { return new fairygui::GBasicTextField(); })
        .template inherit<fairygui::GTextField>()
        .static_function("create", &fairygui::GBasicTextField::create)
        .auto_wrap_objects(true);
    mod.class_("GBasicTextField", class_GBasicTextField);
}
static void js_register_ax_fairygui_GRichTextField(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GRichTextField> class_GRichTextField(isolate);
    class_GRichTextField.ctor([]() { return new fairygui::GRichTextField(); })
        .template inherit<fairygui::GTextField>()
        .member_function("getControl", &fairygui::GRichTextField::getControl)
        .static_function("create", &fairygui::GRichTextField::create)
        .auto_wrap_objects(true);
    mod.class_("GRichTextField", class_GRichTextField);
}
static void js_register_ax_fairygui_GTextInput(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GTextInput> class_GTextInput(isolate);
    class_GTextInput.ctor([]() { return new fairygui::GTextInput(); })
        .template inherit<fairygui::GTextField>()
        .member_function("setPrompt", &fairygui::GTextInput::setPrompt)
        .member_function("setPassword", &fairygui::GTextInput::setPassword)
        .member_function("setKeyboardType", &fairygui::GTextInput::setKeyboardType)
        .member_function("setMaxLength", &fairygui::GTextInput::setMaxLength)
        .member_function("setRestrict", &fairygui::GTextInput::setRestrict)
        .static_function("create", &fairygui::GTextInput::create)
        .auto_wrap_objects(true);
    mod.class_("GTextInput", class_GTextInput);
}
static void js_register_ax_fairygui_GGraph(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GGraph> class_GGraph(isolate);
    class_GGraph.ctor([]() { return new fairygui::GGraph(); })
        .template inherit<fairygui::GObject>()
        .member_function("drawRect", &fairygui::GGraph::drawRect)
        .member_function("drawEllipse", &fairygui::GGraph::drawEllipse)
        .member_function("isEmpty", &fairygui::GGraph::isEmpty)
        .member_function("getColor", &fairygui::GGraph::getColor)
        .member_function("setColor", &fairygui::GGraph::setColor)
        .static_function("create", &fairygui::GGraph::create)
        .auto_wrap_objects(true);
    mod.class_("GGraph", class_GGraph);
}
static void js_register_ax_fairygui_GLoader(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GLoader> class_GLoader(isolate);
    class_GLoader.ctor([]() { return new fairygui::GLoader(); })
        .template inherit<fairygui::GObject>()
        .member_function("getURL", &fairygui::GLoader::getURL)
        .member_function("setURL", &fairygui::GLoader::setURL)
        .member_function("getAlign", &fairygui::GLoader::getAlign)
        .member_function("setAlign", &fairygui::GLoader::setAlign)
        .member_function("getVerticalAlign", &fairygui::GLoader::getVerticalAlign)
        .member_function("setVerticalAlign", &fairygui::GLoader::setVerticalAlign)
        .member_function("getAutoSize", &fairygui::GLoader::getAutoSize)
        .member_function("setAutoSize", &fairygui::GLoader::setAutoSize)
        .member_function("getFill", &fairygui::GLoader::getFill)
        .member_function("setFill", &fairygui::GLoader::setFill)
        .member_function("isShrinkOnly", &fairygui::GLoader::isShrinkOnly)
        .member_function("setShrinkOnly", &fairygui::GLoader::setShrinkOnly)
        .member_function("getContentSize", &fairygui::GLoader::getContentSize)
        .member_function("getColor", &fairygui::GLoader::getColor)
        .member_function("setColor", &fairygui::GLoader::setColor)
        .member_function("isPlaying", &fairygui::GLoader::isPlaying)
        .member_function("setPlaying", &fairygui::GLoader::setPlaying)
        .member_function("getFrame", &fairygui::GLoader::getFrame)
        .member_function("setFrame", &fairygui::GLoader::setFrame)
        .member_function("getFillMethod", &fairygui::GLoader::getFillMethod)
        .member_function("setFillMethod", &fairygui::GLoader::setFillMethod)
        .member_function("getFillOrigin", &fairygui::GLoader::getFillOrigin)
        .member_function("setFillOrigin", &fairygui::GLoader::setFillOrigin)
        .member_function("isFillClockwise", &fairygui::GLoader::isFillClockwise)
        .member_function("setFillClockwise", &fairygui::GLoader::setFillClockwise)
        .member_function("getFillAmount", &fairygui::GLoader::getFillAmount)
        .member_function("setFillAmount", &fairygui::GLoader::setFillAmount)
        .member_function("getComponent", &fairygui::GLoader::getComponent)
        .static_function("create", &fairygui::GLoader::create)
        .auto_wrap_objects(true);
    mod.class_("GLoader", class_GLoader);
}
static void js_register_ax_fairygui_GGroup(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GGroup> class_GGroup(isolate);
    class_GGroup.ctor([]() { return new fairygui::GGroup(); })
        .template inherit<fairygui::GObject>()
        .member_function("getLayout", &fairygui::GGroup::getLayout)
        .member_function("setLayout", &fairygui::GGroup::setLayout)
        .member_function("getColumnGap", &fairygui::GGroup::getColumnGap)
        .member_function("setColumnGap", &fairygui::GGroup::setColumnGap)
        .member_function("getLineGap", &fairygui::GGroup::getLineGap)
        .member_function("setLineGap", &fairygui::GGroup::setLineGap)
        .member_function("isExcludeInvisibles", &fairygui::GGroup::isExcludeInvisibles)
        .member_function("setExcludeInvisibles", &fairygui::GGroup::setExcludeInvisibles)
        .member_function("isAutoSizeDisabled", &fairygui::GGroup::isAutoSizeDisabled)
        .member_function("setAutoSizeDisabled", &fairygui::GGroup::setAutoSizeDisabled)
        .member_function("getMainGridIndex", &fairygui::GGroup::getMainGridIndex)
        .member_function("setMainGridIndex", &fairygui::GGroup::setMainGridIndex)
        .member_function("getMainGridMinSize", &fairygui::GGroup::getMainGridMinSize)
        .member_function("setMainGridMinSize", &fairygui::GGroup::setMainGridMinSize)
        .member_function(
            "setBoundsChangedFlag",
            [](fairygui::GGroup* self) { self->setBoundsChangedFlag(); },
            [](fairygui::GGroup* self, bool arg0) { self->setBoundsChangedFlag(arg0); })
        .member_function("moveChildren", &fairygui::GGroup::moveChildren)
        .member_function("resizeChildren", &fairygui::GGroup::resizeChildren)
        .static_function("create", &fairygui::GGroup::create)
        .auto_wrap_objects(true);
    mod.class_("GGroup", class_GGroup);
}
static void js_register_ax_fairygui_ScrollPane(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::ScrollPane> class_ScrollPane(isolate);
    class_ScrollPane.ctor([](fairygui::GComponent* arg0) { return new fairygui::ScrollPane(arg0); })
        .template inherit<ax::Object>()
        .member_function("setup", &fairygui::ScrollPane::setup)
        .member_function("getOwner", &fairygui::ScrollPane::getOwner)
        .member_function("getHeader", &fairygui::ScrollPane::getHeader)
        .member_function("getFooter", &fairygui::ScrollPane::getFooter)
        .member_function("getVtScrollBar", &fairygui::ScrollPane::getVtScrollBar)
        .member_function("getHzScrollBar", &fairygui::ScrollPane::getHzScrollBar)
        .member_function("isBouncebackEffect", &fairygui::ScrollPane::isBouncebackEffect)
        .member_function("setBouncebackEffect", &fairygui::ScrollPane::setBouncebackEffect)
        .member_function("isTouchEffect", &fairygui::ScrollPane::isTouchEffect)
        .member_function("setTouchEffect", &fairygui::ScrollPane::setTouchEffect)
        .member_function("isInertiaDisabled", &fairygui::ScrollPane::isInertiaDisabled)
        .member_function("setInertiaDisabled", &fairygui::ScrollPane::setInertiaDisabled)
        .member_function("getScrollStep", &fairygui::ScrollPane::getScrollStep)
        .member_function("setScrollStep", &fairygui::ScrollPane::setScrollStep)
        .member_function("isSnapToItem", &fairygui::ScrollPane::isSnapToItem)
        .member_function("setSnapToItem", &fairygui::ScrollPane::setSnapToItem)
        .member_function("isPageMode", &fairygui::ScrollPane::isPageMode)
        .member_function("setPageMode", &fairygui::ScrollPane::setPageMode)
        .member_function("getPageController", &fairygui::ScrollPane::getPageController)
        .member_function("setPageController", &fairygui::ScrollPane::setPageController)
        .member_function("isMouseWheelEnabled", &fairygui::ScrollPane::isMouseWheelEnabled)
        .member_function("setMouseWheelEnabled", &fairygui::ScrollPane::setMouseWheelEnabled)
        .member_function("getDecelerationRate", &fairygui::ScrollPane::getDecelerationRate)
        .member_function("setDecelerationRate", &fairygui::ScrollPane::setDecelerationRate)
        .member_function("getPosX", &fairygui::ScrollPane::getPosX)
        .member_function(
            "setPosX",
            [](fairygui::ScrollPane* self, float arg0) { self->setPosX(arg0); },
            [](fairygui::ScrollPane* self, float arg0, bool arg1) { self->setPosX(arg0, arg1); })
        .member_function("getPosY", &fairygui::ScrollPane::getPosY)
        .member_function(
            "setPosY",
            [](fairygui::ScrollPane* self, float arg0) { self->setPosY(arg0); },
            [](fairygui::ScrollPane* self, float arg0, bool arg1) { self->setPosY(arg0, arg1); })
        .member_function("getPercX", &fairygui::ScrollPane::getPercX)
        .member_function(
            "setPercX",
            [](fairygui::ScrollPane* self, float arg0) { self->setPercX(arg0); },
            [](fairygui::ScrollPane* self, float arg0, bool arg1) { self->setPercX(arg0, arg1); })
        .member_function("getPercY", &fairygui::ScrollPane::getPercY)
        .member_function(
            "setPercY",
            [](fairygui::ScrollPane* self, float arg0) { self->setPercY(arg0); },
            [](fairygui::ScrollPane* self, float arg0, bool arg1) { self->setPercY(arg0, arg1); })
        .member_function("isBottomMost", &fairygui::ScrollPane::isBottomMost)
        .member_function("isRightMost", &fairygui::ScrollPane::isRightMost)
        .member_function(
            "scrollLeft",
            [](fairygui::ScrollPane* self) { self->scrollLeft(); },
            [](fairygui::ScrollPane* self, float arg0) { self->scrollLeft(arg0); },
            [](fairygui::ScrollPane* self, float arg0, bool arg1) { self->scrollLeft(arg0, arg1); })
        .member_function(
            "scrollRight",
            [](fairygui::ScrollPane* self) { self->scrollRight(); },
            [](fairygui::ScrollPane* self, float arg0) { self->scrollRight(arg0); },
            [](fairygui::ScrollPane* self, float arg0, bool arg1) { self->scrollRight(arg0, arg1); })
        .member_function(
            "scrollUp",
            [](fairygui::ScrollPane* self) { self->scrollUp(); },
            [](fairygui::ScrollPane* self, float arg0) { self->scrollUp(arg0); },
            [](fairygui::ScrollPane* self, float arg0, bool arg1) { self->scrollUp(arg0, arg1); })
        .member_function(
            "scrollDown",
            [](fairygui::ScrollPane* self) { self->scrollDown(); },
            [](fairygui::ScrollPane* self, float arg0) { self->scrollDown(arg0); },
            [](fairygui::ScrollPane* self, float arg0, bool arg1) { self->scrollDown(arg0, arg1); })
        .member_function(
            "scrollTop",
            [](fairygui::ScrollPane* self) { self->scrollTop(); },
            [](fairygui::ScrollPane* self, bool arg0) { self->scrollTop(arg0); })
        .member_function(
            "scrollBottom",
            [](fairygui::ScrollPane* self) { self->scrollBottom(); },
            [](fairygui::ScrollPane* self, bool arg0) { self->scrollBottom(arg0); })
        .member_function(
            "scrollToView",
            [](fairygui::ScrollPane* self, ax::Rect arg0) { self->scrollToView(arg0); },
            [](fairygui::ScrollPane* self, ax::Rect arg0, bool arg1) { self->scrollToView(arg0, arg1); },
            [](fairygui::ScrollPane* self, ax::Rect arg0, bool arg1, bool arg2) { self->scrollToView(arg0, arg1, arg2); },
            [](fairygui::ScrollPane* self, fairygui::GObject* arg0) { self->scrollToView(arg0); },
            [](fairygui::ScrollPane* self, fairygui::GObject* arg0, bool arg1) { self->scrollToView(arg0, arg1); },
            [](fairygui::ScrollPane* self, fairygui::GObject* arg0, bool arg1, bool arg2) { self->scrollToView(arg0, arg1, arg2); })
        .member_function("isChildInView", &fairygui::ScrollPane::isChildInView)
        .member_function("getPageX", &fairygui::ScrollPane::getPageX)
        .member_function(
            "setPageX",
            [](fairygui::ScrollPane* self, int arg0) { self->setPageX(arg0); },
            [](fairygui::ScrollPane* self, int arg0, bool arg1) { self->setPageX(arg0, arg1); })
        .member_function("getPageY", &fairygui::ScrollPane::getPageY)
        .member_function(
            "setPageY",
            [](fairygui::ScrollPane* self, int arg0) { self->setPageY(arg0); },
            [](fairygui::ScrollPane* self, int arg0, bool arg1) { self->setPageY(arg0, arg1); })
        .member_function("getScrollingPosX", &fairygui::ScrollPane::getScrollingPosX)
        .member_function("getScrollingPosY", &fairygui::ScrollPane::getScrollingPosY)
        .member_function("getContentSize", &fairygui::ScrollPane::getContentSize)
        .member_function("getViewSize", &fairygui::ScrollPane::getViewSize)
        .member_function("lockHeader", &fairygui::ScrollPane::lockHeader)
        .member_function("lockFooter", &fairygui::ScrollPane::lockFooter)
        .member_function("cancelDragging", &fairygui::ScrollPane::cancelDragging)
        .static_function("getDraggingPane", &fairygui::ScrollPane::getDraggingPane)
        .auto_wrap_objects(true);
    mod.class_("ScrollPane", class_ScrollPane);
}
static void js_register_ax_fairygui_Transition(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::Transition> class_Transition(isolate);
    class_Transition.ctor([](fairygui::GComponent* arg0) { return new fairygui::Transition(arg0); })
        .template inherit<ax::Object>()
        .member_function("getOwner", &fairygui::Transition::getOwner)
        .member_function("isPlaying", &fairygui::Transition::isPlaying)
        .member_function(
            "playReverse",
            [](fairygui::Transition* self, int arg0, float arg1) { self->playReverse(arg0, arg1); },
            [](fairygui::Transition* self, int arg0, float arg1, std::function<void()> arg2) { self->playReverse(arg0, arg1, arg2); },
            [](fairygui::Transition* self) { self->playReverse(); },
            [](fairygui::Transition* self, std::function<void()> arg0) { self->playReverse(arg0); })
        .member_function("changePlayTimes", &fairygui::Transition::changePlayTimes)
        .member_function(
            "stop",
            [](fairygui::Transition* self, bool arg0, bool arg1) { self->stop(arg0, arg1); },
            [](fairygui::Transition* self) { self->stop(); })
        .member_function("setAutoPlay", &fairygui::Transition::setAutoPlay)
        .member_function("setPaused", &fairygui::Transition::setPaused)
        .member_function("setValue", &fairygui::Transition::setValue)
        .member_function("setHook", &fairygui::Transition::setHook)
        .member_function("clearHooks", &fairygui::Transition::clearHooks)
        .member_function("setTarget", &fairygui::Transition::setTarget)
        .member_function("setDuration", &fairygui::Transition::setDuration)
        .member_function("getLabelTime", &fairygui::Transition::getLabelTime)
        .member_function("getTimeScale", &fairygui::Transition::getTimeScale)
        .member_function("setTimeScale", &fairygui::Transition::setTimeScale)
        .member_function("updateFromRelations", &fairygui::Transition::updateFromRelations)
        .member_function("onOwnerAddedToStage", &fairygui::Transition::onOwnerAddedToStage)
        .member_function("onOwnerRemovedFromStage", &fairygui::Transition::onOwnerRemovedFromStage)
        .auto_wrap_objects(true);
    mod.class_("Transition", class_Transition);
}
static void js_register_ax_fairygui_GComponent(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GComponent> class_GComponent(isolate);
    class_GComponent.ctor([]() { return new fairygui::GComponent(); })
        .template inherit<fairygui::GObject>()
        .member_function("addChild", &fairygui::GComponent::addChild)
        .member_function("addChildAt", &fairygui::GComponent::addChildAt)
        .member_function("removeChild", &fairygui::GComponent::removeChild)
        .member_function("removeChildAt", &fairygui::GComponent::removeChildAt)
        .member_function(
            "removeChildren",
            [](fairygui::GComponent* self, int arg0, int arg1) { self->removeChildren(arg0, arg1); },
            [](fairygui::GComponent* self) { self->removeChildren(); })
        .member_function("getChildAt", &fairygui::GComponent::getChildAt)
        .member_function("getChild", &fairygui::GComponent::getChild)
        .member_function("getChildByPath", &fairygui::GComponent::getChildByPath)
        .member_function("getChildInGroup", &fairygui::GComponent::getChildInGroup)
        .member_function("getChildById", &fairygui::GComponent::getChildById)
        .member_function("getChildren", &fairygui::GComponent::getChildren)
        .member_function("getChildIndex", &fairygui::GComponent::getChildIndex)
        .member_function("setChildIndex", &fairygui::GComponent::setChildIndex)
        .member_function("setChildIndexBefore", &fairygui::GComponent::setChildIndexBefore)
        .member_function("swapChildren", &fairygui::GComponent::swapChildren)
        .member_function("swapChildrenAt", &fairygui::GComponent::swapChildrenAt)
        .member_function("numChildren", &fairygui::GComponent::numChildren)
        .member_function("isAncestorOf", &fairygui::GComponent::isAncestorOf)
        .member_function("isChildInView", &fairygui::GComponent::isChildInView)
        .member_function("getFirstChildInView", &fairygui::GComponent::getFirstChildInView)
        .member_function("addController", &fairygui::GComponent::addController)
        .member_function("getControllerAt", &fairygui::GComponent::getControllerAt)
        .member_function("getController", &fairygui::GComponent::getController)
        .member_function("getControllers", &fairygui::GComponent::getControllers)
        .member_function("removeController", &fairygui::GComponent::removeController)
        .member_function("applyController", &fairygui::GComponent::applyController)
        .member_function("applyAllControllers", &fairygui::GComponent::applyAllControllers)
        .member_function("getTransition", &fairygui::GComponent::getTransition)
        .member_function("getTransitionAt", &fairygui::GComponent::getTransitionAt)
        .member_function("getTransitions", &fairygui::GComponent::getTransitions)
        .member_function("getOpaque", &fairygui::GComponent::getOpaque)
        .member_function("setOpaque", &fairygui::GComponent::setOpaque)
        .member_function("getMargin", &fairygui::GComponent::getMargin)
        .member_function("setMargin", &fairygui::GComponent::setMargin)
        .member_function("getChildrenRenderOrder", &fairygui::GComponent::getChildrenRenderOrder)
        .member_function("setChildrenRenderOrder", &fairygui::GComponent::setChildrenRenderOrder)
        .member_function("getApexIndex", &fairygui::GComponent::getApexIndex)
        .member_function("setApexIndex", &fairygui::GComponent::setApexIndex)
        .member_function("getMask", &fairygui::GComponent::getMask)
        .member_function(
            "setMask",
            [](fairygui::GComponent* self, ax::Node* arg0) { self->setMask(arg0); },
            [](fairygui::GComponent* self, ax::Node* arg0, bool arg1) { self->setMask(arg0, arg1); })
        .member_function("getHitArea", &fairygui::GComponent::getHitArea)
        .member_function("setHitArea", &fairygui::GComponent::setHitArea)
        .member_function("getScrollPane", &fairygui::GComponent::getScrollPane)
        .member_function("getViewWidth", &fairygui::GComponent::getViewWidth)
        .member_function("setViewWidth", &fairygui::GComponent::setViewWidth)
        .member_function("getViewHeight", &fairygui::GComponent::getViewHeight)
        .member_function("setViewHeight", &fairygui::GComponent::setViewHeight)
        .member_function("setBoundsChangedFlag", &fairygui::GComponent::setBoundsChangedFlag)
        .member_function("ensureBoundsCorrect", &fairygui::GComponent::ensureBoundsCorrect)
        .member_function("getSnappingPosition", &fairygui::GComponent::getSnappingPosition)
        .member_function("childSortingOrderChanged", &fairygui::GComponent::childSortingOrderChanged)
        .member_function("childStateChanged", &fairygui::GComponent::childStateChanged)
        .member_function("adjustRadioGroupDepth", &fairygui::GComponent::adjustRadioGroupDepth)
        .static_function("create", &fairygui::GComponent::create)
        .auto_wrap_objects(true);
    mod.class_("GComponent", class_GComponent);
}
static void js_register_ax_fairygui_GButton(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GButton> class_GButton(isolate);
    class_GButton.ctor([]() { return new fairygui::GButton(); })
        .template inherit<fairygui::GComponent>()
        .member_function("getTitle", &fairygui::GButton::getTitle)
        .member_function("setTitle", &fairygui::GButton::setTitle)
        .member_function("getSelectedTitle", &fairygui::GButton::getSelectedTitle)
        .member_function("setSelectedTitle", &fairygui::GButton::setSelectedTitle)
        .member_function("getSelectedIcon", &fairygui::GButton::getSelectedIcon)
        .member_function("setSelectedIcon", &fairygui::GButton::setSelectedIcon)
        .member_function("getTitleColor", &fairygui::GButton::getTitleColor)
        .member_function("setTitleColor", &fairygui::GButton::setTitleColor)
        .member_function("getTitleFontSize", &fairygui::GButton::getTitleFontSize)
        .member_function("setTitleFontSize", &fairygui::GButton::setTitleFontSize)
        .member_function("isSelected", &fairygui::GButton::isSelected)
        .member_function("setSelected", &fairygui::GButton::setSelected)
        .member_function("getRelatedController", &fairygui::GButton::getRelatedController)
        .member_function("setRelatedController", &fairygui::GButton::setRelatedController)
        .member_function("isChangeStateOnClick", &fairygui::GButton::isChangeStateOnClick)
        .member_function("setChangeStateOnClick", &fairygui::GButton::setChangeStateOnClick)
        .member_function("getTextField", &fairygui::GButton::getTextField)
        .static_function("create", &fairygui::GButton::create)
        .auto_wrap_objects(true);
    mod.class_("GButton", class_GButton);
}
static void js_register_ax_fairygui_GObjectPool(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GObjectPool> class_GObjectPool(isolate);
    class_GObjectPool.ctor([]() { return new fairygui::GObjectPool(); })
        .member_function("getObject", &fairygui::GObjectPool::getObject)
        .member_function("returnObject", &fairygui::GObjectPool::returnObject)
        .auto_wrap_objects(true);
    mod.class_("GObjectPool", class_GObjectPool);
}
static void js_register_ax_fairygui_GList(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GList> class_GList(isolate);
    class_GList.ctor([]() { return new fairygui::GList(); })
        .template inherit<fairygui::GComponent>()
        .member_function("getDefaultItem", &fairygui::GList::getDefaultItem)
        .member_function("setDefaultItem", &fairygui::GList::setDefaultItem)
        .member_function("getLayout", &fairygui::GList::getLayout)
        .member_function("setLayout", &fairygui::GList::setLayout)
        .member_function("getLineCount", &fairygui::GList::getLineCount)
        .member_function("setLineCount", &fairygui::GList::setLineCount)
        .member_function("getColumnCount", &fairygui::GList::getColumnCount)
        .member_function("setColumnCount", &fairygui::GList::setColumnCount)
        .member_function("getColumnGap", &fairygui::GList::getColumnGap)
        .member_function("setColumnGap", &fairygui::GList::setColumnGap)
        .member_function("getLineGap", &fairygui::GList::getLineGap)
        .member_function("setLineGap", &fairygui::GList::setLineGap)
        .member_function("getAlign", &fairygui::GList::getAlign)
        .member_function("setAlign", &fairygui::GList::setAlign)
        .member_function("getVerticalAlign", &fairygui::GList::getVerticalAlign)
        .member_function("setVerticalAlign", &fairygui::GList::setVerticalAlign)
        .member_function("getAutoResizeItem", &fairygui::GList::getAutoResizeItem)
        .member_function("setAutoResizeItem", &fairygui::GList::setAutoResizeItem)
        .member_function("getSelectionMode", &fairygui::GList::getSelectionMode)
        .member_function("setSelectionMode", &fairygui::GList::setSelectionMode)
        .member_function("getItemPool", &fairygui::GList::getItemPool)
        .member_function(
            "getFromPool",
            [](fairygui::GList* self, std::string arg0) { return self->getFromPool(arg0); },
            [](fairygui::GList* self) { return self->getFromPool(); })
        .member_function("returnToPool", &fairygui::GList::returnToPool)
        .member_function(
            "addItemFromPool",
            [](fairygui::GList* self, std::string arg0) { return self->addItemFromPool(arg0); },
            [](fairygui::GList* self) { return self->addItemFromPool(); })
        .member_function("removeChildToPoolAt", &fairygui::GList::removeChildToPoolAt)
        .member_function("removeChildToPool", &fairygui::GList::removeChildToPool)
        .member_function(
            "removeChildrenToPool",
            [](fairygui::GList* self, int arg0, int arg1) { self->removeChildrenToPool(arg0, arg1); },
            [](fairygui::GList* self) { self->removeChildrenToPool(); })
        .member_function("getSelectedIndex", &fairygui::GList::getSelectedIndex)
        .member_function("setSelectedIndex", &fairygui::GList::setSelectedIndex)
        .member_function("getSelection", &fairygui::GList::getSelection)
        .member_function("addSelection", &fairygui::GList::addSelection)
        .member_function("removeSelection", &fairygui::GList::removeSelection)
        .member_function("clearSelection", &fairygui::GList::clearSelection)
        .member_function("selectAll", &fairygui::GList::selectAll)
        .member_function("selectReverse", &fairygui::GList::selectReverse)
        .member_function("handleArrowKey", &fairygui::GList::handleArrowKey)
        .member_function(
            "resizeToFit",
            [](fairygui::GList* self, int arg0, int arg1) { self->resizeToFit(arg0, arg1); },
            [](fairygui::GList* self, int arg0) { self->resizeToFit(arg0); })
        .member_function(
            "scrollToView",
            [](fairygui::GList* self, int arg0) { self->scrollToView(arg0); },
            [](fairygui::GList* self, int arg0, bool arg1) { self->scrollToView(arg0, arg1); },
            [](fairygui::GList* self, int arg0, bool arg1, bool arg2) { self->scrollToView(arg0, arg1, arg2); })
        .member_function("getSelectionController", &fairygui::GList::getSelectionController)
        .member_function("setSelectionController", &fairygui::GList::setSelectionController)
        .member_function("setVirtual", &fairygui::GList::setVirtual)
        .member_function("setVirtualAndLoop", &fairygui::GList::setVirtualAndLoop)
        .member_function("isVirtual", &fairygui::GList::isVirtual)
        .member_function("refreshVirtualList", &fairygui::GList::refreshVirtualList)
        .member_function("getNumItems", &fairygui::GList::getNumItems)
        .member_function("setNumItems", &fairygui::GList::setNumItems)
        .member_function("childIndexToItemIndex", &fairygui::GList::childIndexToItemIndex)
        .member_function("itemIndexToChildIndex", &fairygui::GList::itemIndexToChildIndex)
        .static_function("create", &fairygui::GList::create)
        .auto_wrap_objects(true);
    mod.class_("GList", class_GList);
}
static void js_register_ax_fairygui_GComboBox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GComboBox> class_GComboBox(isolate);
    class_GComboBox.ctor([]() { return new fairygui::GComboBox(); })
        .template inherit<fairygui::GComponent>()
        .member_function("getTitle", &fairygui::GComboBox::getTitle)
        .member_function("setTitle", &fairygui::GComboBox::setTitle)
        .member_function("getTitleColor", &fairygui::GComboBox::getTitleColor)
        .member_function("setTitleColor", &fairygui::GComboBox::setTitleColor)
        .member_function("getTitleFontSize", &fairygui::GComboBox::getTitleFontSize)
        .member_function("setTitleFontSize", &fairygui::GComboBox::setTitleFontSize)
        .member_function("getValue", &fairygui::GComboBox::getValue)
        .member_function("setValue", &fairygui::GComboBox::setValue)
        .member_function("getSelectedIndex", &fairygui::GComboBox::getSelectedIndex)
        .member_function("setSelectedIndex", &fairygui::GComboBox::setSelectedIndex)
        .member_function("getSelectionController", &fairygui::GComboBox::getSelectionController)
        .member_function("setSelectionController", &fairygui::GComboBox::setSelectionController)
        .member_function("getItems", &fairygui::GComboBox::getItems)
        .member_function("getIcons", &fairygui::GComboBox::getIcons)
        .member_function("getValues", &fairygui::GComboBox::getValues)
        .member_function("getDropdown", &fairygui::GComboBox::getDropdown)
        .member_function("refresh", &fairygui::GComboBox::refresh)
        .member_function("getTextField", &fairygui::GComboBox::getTextField)
        .static_function("create", &fairygui::GComboBox::create)
        .auto_wrap_objects(true);
    mod.class_("GComboBox", class_GComboBox);
}
static void js_register_ax_fairygui_GProgressBar(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GProgressBar> class_GProgressBar(isolate);
    class_GProgressBar.ctor([]() { return new fairygui::GProgressBar(); })
        .template inherit<fairygui::GComponent>()
        .member_function("getTitleType", &fairygui::GProgressBar::getTitleType)
        .member_function("setTitleType", &fairygui::GProgressBar::setTitleType)
        .member_function("getMin", &fairygui::GProgressBar::getMin)
        .member_function("setMin", &fairygui::GProgressBar::setMin)
        .member_function("getMax", &fairygui::GProgressBar::getMax)
        .member_function("setMax", &fairygui::GProgressBar::setMax)
        .member_function("getValue", &fairygui::GProgressBar::getValue)
        .member_function("setValue", &fairygui::GProgressBar::setValue)
        .member_function("tweenValue", &fairygui::GProgressBar::tweenValue)
        .member_function("update", &fairygui::GProgressBar::update)
        .static_function("create", &fairygui::GProgressBar::create)
        .auto_wrap_objects(true);
    mod.class_("GProgressBar", class_GProgressBar);
}
static void js_register_ax_fairygui_GSlider(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GSlider> class_GSlider(isolate);
    class_GSlider.ctor([]() { return new fairygui::GSlider(); })
        .template inherit<fairygui::GComponent>()
        .member_function("getTitleType", &fairygui::GSlider::getTitleType)
        .member_function("setTitleType", &fairygui::GSlider::setTitleType)
        .member_function("getMin", &fairygui::GSlider::getMin)
        .member_function("setMin", &fairygui::GSlider::setMin)
        .member_function("getMax", &fairygui::GSlider::getMax)
        .member_function("setMax", &fairygui::GSlider::setMax)
        .member_function("getValue", &fairygui::GSlider::getValue)
        .member_function("setValue", &fairygui::GSlider::setValue)
        .member_function("getWholeNumbers", &fairygui::GSlider::getWholeNumbers)
        .member_function("setWholeNumbers", &fairygui::GSlider::setWholeNumbers)
        .static_function("create", &fairygui::GSlider::create)
        .auto_wrap_objects(true);
    mod.class_("GSlider", class_GSlider);
}
static void js_register_ax_fairygui_GScrollBar(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GScrollBar> class_GScrollBar(isolate);
    class_GScrollBar.ctor([]() { return new fairygui::GScrollBar(); })
        .template inherit<fairygui::GComponent>()
        .member_function("setScrollPane", &fairygui::GScrollBar::setScrollPane)
        .member_function("setDisplayPerc", &fairygui::GScrollBar::setDisplayPerc)
        .member_function("setScrollPerc", &fairygui::GScrollBar::setScrollPerc)
        .member_function("getMinSize", &fairygui::GScrollBar::getMinSize)
        .static_function("create", &fairygui::GScrollBar::create)
        .auto_wrap_objects(true);
    mod.class_("GScrollBar", class_GScrollBar);
}
static void js_register_ax_fairygui_Window(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::Window> class_Window(isolate);
    class_Window.ctor([]() { return new fairygui::Window(); })
        .template inherit<fairygui::GComponent>()
        .member_function("show", &fairygui::Window::show)
        .member_function("hide", &fairygui::Window::hide)
        .member_function("hideImmediately", &fairygui::Window::hideImmediately)
        .member_function("toggleStatus", &fairygui::Window::toggleStatus)
        .member_function("bringToFront", &fairygui::Window::bringToFront)
        .member_function("isShowing", &fairygui::Window::isShowing)
        .member_function("isTop", &fairygui::Window::isTop)
        .member_function("isModal", &fairygui::Window::isModal)
        .member_function("setModal", &fairygui::Window::setModal)
        .member_function(
            "showModalWait",
            [](fairygui::Window* self, int arg0) { self->showModalWait(arg0); },
            [](fairygui::Window* self) { self->showModalWait(); })
        .member_function(
            "closeModalWait",
            [](fairygui::Window* self, int arg0) { return self->closeModalWait(arg0); },
            [](fairygui::Window* self) { return self->closeModalWait(); })
        .member_function("initWindow", &fairygui::Window::initWindow)
        .member_function("addUISource", &fairygui::Window::addUISource)
        .member_function("isBringToFrontOnClick", &fairygui::Window::isBringToFrontOnClick)
        .member_function("setBringToFrontOnClick", &fairygui::Window::setBringToFrontOnClick)
        .member_function("getContentPane", &fairygui::Window::getContentPane)
        .member_function("setContentPane", &fairygui::Window::setContentPane)
        .member_function("getFrame", &fairygui::Window::getFrame)
        .member_function("getCloseButton", &fairygui::Window::getCloseButton)
        .member_function("setCloseButton", &fairygui::Window::setCloseButton)
        .member_function("getDragArea", &fairygui::Window::getDragArea)
        .member_function("setDragArea", &fairygui::Window::setDragArea)
        .member_function("getContentArea", &fairygui::Window::getContentArea)
        .member_function("setContentArea", &fairygui::Window::setContentArea)
        .member_function("getModalWaitingPane", &fairygui::Window::getModalWaitingPane)
        .static_function("create", &fairygui::Window::create)
        .auto_wrap_objects(true);
    mod.class_("Window", class_Window);
}
static void js_register_ax_fairygui_GRoot(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GRoot> class_GRoot(isolate);
    class_GRoot.ctor([]() { return new fairygui::GRoot(); })
        .template inherit<fairygui::GComponent>()
        .member_function("showWindow", &fairygui::GRoot::showWindow)
        .member_function("hideWindow", &fairygui::GRoot::hideWindow)
        .member_function("hideWindowImmediately", &fairygui::GRoot::hideWindowImmediately)
        .member_function("bringToFront", &fairygui::GRoot::bringToFront)
        .member_function("showModalWait", &fairygui::GRoot::showModalWait)
        .member_function("closeModalWait", &fairygui::GRoot::closeModalWait)
        .member_function("closeAllExceptModals", &fairygui::GRoot::closeAllExceptModals)
        .member_function("closeAllWindows", &fairygui::GRoot::closeAllWindows)
        .member_function("getTopWindow", &fairygui::GRoot::getTopWindow)
        .member_function("getModalWaitingPane", &fairygui::GRoot::getModalWaitingPane)
        .member_function("getModalLayer", &fairygui::GRoot::getModalLayer)
        .member_function("hasModalWindow", &fairygui::GRoot::hasModalWindow)
        .member_function("isModalWaiting", &fairygui::GRoot::isModalWaiting)
        .member_function("getInputProcessor", &fairygui::GRoot::getInputProcessor)
        .member_function("getTouchPosition", &fairygui::GRoot::getTouchPosition)
        .member_function("getTouchTarget", &fairygui::GRoot::getTouchTarget)
        .member_function("worldToRoot", &fairygui::GRoot::worldToRoot)
        .member_function("rootToWorld", &fairygui::GRoot::rootToWorld)
        .member_function(
            "showPopup",
            [](fairygui::GRoot* self, fairygui::GObject* arg0, fairygui::GObject* arg1, fairygui::PopupDirection arg2)
            { self->showPopup(arg0, arg1, arg2); },
            [](fairygui::GRoot* self, fairygui::GObject* arg0) { self->showPopup(arg0); })
        .member_function(
            "togglePopup",
            [](fairygui::GRoot* self, fairygui::GObject* arg0, fairygui::GObject* arg1, fairygui::PopupDirection arg2)
            { self->togglePopup(arg0, arg1, arg2); },
            [](fairygui::GRoot* self, fairygui::GObject* arg0) { self->togglePopup(arg0); })
        .member_function(
            "hidePopup",
            [](fairygui::GRoot* self, fairygui::GObject* arg0) { self->hidePopup(arg0); },
            [](fairygui::GRoot* self) { self->hidePopup(); })
        .member_function("hasAnyPopup", &fairygui::GRoot::hasAnyPopup)
        .member_function("getPoupPosition", &fairygui::GRoot::getPoupPosition)
        .member_function("showTooltips", &fairygui::GRoot::showTooltips)
        .member_function("showTooltipsWin", &fairygui::GRoot::showTooltipsWin)
        .member_function("hideTooltips", &fairygui::GRoot::hideTooltips)
        .member_function(
            "playSound",
            [](fairygui::GRoot* self, std::string arg0) { self->playSound(arg0); },
            [](fairygui::GRoot* self, std::string arg0, float arg1) { self->playSound(arg0, arg1); })
        .member_function("isSoundEnabled", &fairygui::GRoot::isSoundEnabled)
        .member_function("setSoundEnabled", &fairygui::GRoot::setSoundEnabled)
        .member_function("getSoundVolumeScale", &fairygui::GRoot::getSoundVolumeScale)
        .member_function("setSoundVolumeScale", &fairygui::GRoot::setSoundVolumeScale)
        .static_function(
            "create",
            [](ax::Scene* arg0) { return fairygui::GRoot::create(arg0); },
            [](ax::Scene* arg0, int arg1) { return fairygui::GRoot::create(arg0, arg1); })
        .static_function("getInstance", &fairygui::GRoot::getInstance)
        .auto_wrap_objects(true);
    mod.class_("GRoot", class_GRoot);
}
static void js_register_ax_fairygui_PopupMenu(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::PopupMenu> class_PopupMenu(isolate);
    class_PopupMenu.ctor([]() { return new fairygui::PopupMenu(); })
        .template inherit<ax::Object>()
        .member_function("addItem", &fairygui::PopupMenu::addItem)
        .member_function("addItemAt", &fairygui::PopupMenu::addItemAt)
        .member_function("addSeperator", &fairygui::PopupMenu::addSeperator)
        .member_function("getItemName", &fairygui::PopupMenu::getItemName)
        .member_function("setItemText", &fairygui::PopupMenu::setItemText)
        .member_function("setItemVisible", &fairygui::PopupMenu::setItemVisible)
        .member_function("setItemGrayed", &fairygui::PopupMenu::setItemGrayed)
        .member_function("setItemCheckable", &fairygui::PopupMenu::setItemCheckable)
        .member_function("setItemChecked", &fairygui::PopupMenu::setItemChecked)
        .member_function("isItemChecked", &fairygui::PopupMenu::isItemChecked)
        .member_function("removeItem", &fairygui::PopupMenu::removeItem)
        .member_function("clearItems", &fairygui::PopupMenu::clearItems)
        .member_function("getItemCount", &fairygui::PopupMenu::getItemCount)
        .member_function("getContentPane", &fairygui::PopupMenu::getContentPane)
        .member_function("getList", &fairygui::PopupMenu::getList)
        .member_function(
            "show",
            [](fairygui::PopupMenu* self, fairygui::GObject* arg0, fairygui::PopupDirection arg1) { self->show(arg0, arg1); },
            [](fairygui::PopupMenu* self) { self->show(); })
        .static_function(
            "create", []() { return fairygui::PopupMenu::create(); }, [](std::string arg0) { return fairygui::PopupMenu::create(arg0); })
        .auto_wrap_objects(true);
    mod.class_("PopupMenu", class_PopupMenu);
}
static void js_register_ax_fairygui_UIObjectFactory(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::UIObjectFactory> class_UIObjectFactory(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_UIObjectFactory
        .static_function(
            "newObject",
            [](fairygui::ObjectType arg0) { return fairygui::UIObjectFactory::newObject(arg0); },
            [](fairygui::PackageItem* arg0) { return fairygui::UIObjectFactory::newObject(arg0); })
        .static_function("setLoaderExtension", &fairygui::UIObjectFactory::setLoaderExtension)
        .auto_wrap_objects(true);
    mod.class_("UIObjectFactory", class_UIObjectFactory);
}
static void js_register_ax_fairygui_DragDropManager(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::DragDropManager> class_DragDropManager(isolate);
    class_DragDropManager.ctor([]() { return new fairygui::DragDropManager(); })
        .member_function("getAgent", &fairygui::DragDropManager::getAgent)
        .member_function("isDragging", &fairygui::DragDropManager::isDragging)
        .member_function(
            "startDrag",
            [](fairygui::DragDropManager* self, std::string arg0) { self->startDrag(arg0); },
            [](fairygui::DragDropManager* self, std::string arg0, ax::Value arg1) { self->startDrag(arg0, arg1); },
            [](fairygui::DragDropManager* self, std::string arg0, ax::Value arg1, int arg2) { self->startDrag(arg0, arg1, arg2); })
        .member_function("cancel", &fairygui::DragDropManager::cancel)
        .static_function("getInstance", &fairygui::DragDropManager::getInstance)
        .auto_wrap_objects(true);
    mod.class_("DragDropManager", class_DragDropManager);
}
static void js_register_ax_fairygui_GTweener(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GTweener> class_GTweener(isolate);
    class_GTweener.ctor([]() { return new fairygui::GTweener(); })
        .template inherit<ax::Object>()
        .member_function("setDelay", &fairygui::GTweener::setDelay)
        .member_function("getDelay", &fairygui::GTweener::getDelay)
        .member_function("setDuration", &fairygui::GTweener::setDuration)
        .member_function("getDuration", &fairygui::GTweener::getDuration)
        .member_function("setBreakpoint", &fairygui::GTweener::setBreakpoint)
        .member_function("setEase", &fairygui::GTweener::setEase)
        .member_function("setEasePeriod", &fairygui::GTweener::setEasePeriod)
        .member_function("setEaseOvershootOrAmplitude", &fairygui::GTweener::setEaseOvershootOrAmplitude)
        .member_function(
            "setRepeat",
            [](fairygui::GTweener* self, int arg0) { return self->setRepeat(arg0); },
            [](fairygui::GTweener* self, int arg0, bool arg1) { return self->setRepeat(arg0, arg1); })
        .member_function("getRepeat", &fairygui::GTweener::getRepeat)
        .member_function("setTimeScale", &fairygui::GTweener::setTimeScale)
        .member_function("setSnapping", &fairygui::GTweener::setSnapping)
        .member_function("setTargetAny", &fairygui::GTweener::setTargetAny)
        .member_function(
            "setTarget",
            [](fairygui::GTweener* self, ax::Object* arg0) { return self->setTarget(arg0); },
            [](fairygui::GTweener* self, ax::Object* arg0, fairygui::TweenPropType arg1) { return self->setTarget(arg0, arg1); })
        .member_function("setUserData", &fairygui::GTweener::setUserData)
        .member_function("setPath", &fairygui::GTweener::setPath)
        .member_function("getUserData", &fairygui::GTweener::getUserData)
        .member_function("getNormalizedTime", &fairygui::GTweener::getNormalizedTime)
        .member_function("isCompleted", &fairygui::GTweener::isCompleted)
        .member_function("allCompleted", &fairygui::GTweener::allCompleted)
        .member_function("setPaused", &fairygui::GTweener::setPaused)
        .member_function("seek", &fairygui::GTweener::seek)
        .member_function(
            "kill", [](fairygui::GTweener* self) { self->kill(); }, [](fairygui::GTweener* self, bool arg0) { self->kill(arg0); })
        .auto_wrap_objects(true);
    mod.class_("GTweener", class_GTweener);
}
static void js_register_ax_fairygui_GTween(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<fairygui::GTween> class_GTween(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_GTween.static_function("toFloat", &fairygui::GTween::toFloat)
        .static_function("toVec2", &fairygui::GTween::toVec2)
        .static_function("toVec3", &fairygui::GTween::toVec3)
        .static_function("toVec4", &fairygui::GTween::toVec4)
        .static_function("toColor32", &fairygui::GTween::toColor32)
        .static_function("toDouble", &fairygui::GTween::toDouble)
        .static_function("delayedCall", &fairygui::GTween::delayedCall)
        .static_function("shake", &fairygui::GTween::shake)
        .static_function(
            "isTweening",
            [](ax::Object* arg0) { return fairygui::GTween::isTweening(arg0); },
            [](ax::Object* arg0, fairygui::TweenPropType arg1) { return fairygui::GTween::isTweening(arg0, arg1); })
        .static_function(
            "kill",
            [](ax::Object* arg0) { fairygui::GTween::kill(arg0); },
            [](ax::Object* arg0, fairygui::TweenPropType arg1) { fairygui::GTween::kill(arg0, arg1); },
            [](ax::Object* arg0, fairygui::TweenPropType arg1, bool arg2) { fairygui::GTween::kill(arg0, arg1, arg2); })
        .static_function(
            "getTween",
            [](ax::Object* arg0) { return fairygui::GTween::getTween(arg0); },
            [](ax::Object* arg0, fairygui::TweenPropType arg1) { return fairygui::GTween::getTween(arg0, arg1); })
        .static_function("clean", &fairygui::GTween::clean)
        .auto_wrap_objects(true);
    mod.class_("GTween", class_GTween);
}
void js_register_all_ax_fairygui(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("fgui");
    js_register_ax_fairygui_InputEvent(mod);
    js_register_ax_fairygui_EventContext(mod);
    js_register_ax_fairygui_UIEventDispatcher(mod);
    js_register_ax_fairygui_GController(mod);
    js_register_ax_fairygui_GObject(mod);
    js_register_ax_fairygui_UIPackage(mod);
    js_register_ax_fairygui_GImage(mod);
    js_register_ax_fairygui_GMovieClip(mod);
    js_register_ax_fairygui_GTextField(mod);
    js_register_ax_fairygui_GBasicTextField(mod);
    js_register_ax_fairygui_GRichTextField(mod);
    js_register_ax_fairygui_GTextInput(mod);
    js_register_ax_fairygui_GGraph(mod);
    js_register_ax_fairygui_GLoader(mod);
    js_register_ax_fairygui_GGroup(mod);
    js_register_ax_fairygui_ScrollPane(mod);
    js_register_ax_fairygui_Transition(mod);
    js_register_ax_fairygui_GComponent(mod);
    js_register_ax_fairygui_GButton(mod);
    js_register_ax_fairygui_GObjectPool(mod);
    js_register_ax_fairygui_GList(mod);
    js_register_ax_fairygui_GComboBox(mod);
    js_register_ax_fairygui_GProgressBar(mod);
    js_register_ax_fairygui_GSlider(mod);
    js_register_ax_fairygui_GScrollBar(mod);
    js_register_ax_fairygui_Window(mod);
    js_register_ax_fairygui_GRoot(mod);
    js_register_ax_fairygui_PopupMenu(mod);
    js_register_ax_fairygui_UIObjectFactory(mod);
    js_register_ax_fairygui_DragDropManager(mod);
    js_register_ax_fairygui_GTweener(mod);
    js_register_ax_fairygui_GTween(mod);
}
