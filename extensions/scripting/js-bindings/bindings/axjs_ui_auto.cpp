#include "js-bindings/bindings/axjs_ui_auto.hpp"
#include "axmol/ui/CocosGUI.h"
#include "js-bindings/manual/JSConversions.h"
static void js_register_ax_ui_LayoutParameter(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::LayoutParameter> class_LayoutParameter(isolate);
    class_LayoutParameter.ctor([]() { return new ax::ui::LayoutParameter(); })
        .template inherit<ax::Object>()
        .member_function("getLayoutType", &ax::ui::LayoutParameter::getLayoutType)
        .member_function("clone", &ax::ui::LayoutParameter::clone)
        .member_function("createCloneInstance", &ax::ui::LayoutParameter::createCloneInstance)
        .member_function("copyProperties", &ax::ui::LayoutParameter::copyProperties)
        .static_function("create", &ax::ui::LayoutParameter::create)
        .auto_wrap_objects(true);
    mod.class_("LayoutParameter", class_LayoutParameter);
}
static void js_register_ax_ui_LinearLayoutParameter(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::LinearLayoutParameter> class_LinearLayoutParameter(isolate);
    class_LinearLayoutParameter.ctor([]() { return new ax::ui::LinearLayoutParameter(); })
        .template inherit<ax::ui::LayoutParameter>()
        .member_function("setGravity", &ax::ui::LinearLayoutParameter::setGravity)
        .member_function("getGravity", &ax::ui::LinearLayoutParameter::getGravity)
        .static_function("create", &ax::ui::LinearLayoutParameter::create)
        .auto_wrap_objects(true);
    mod.class_("LinearLayoutParameter", class_LinearLayoutParameter);
}
static void js_register_ax_ui_RelativeLayoutParameter(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RelativeLayoutParameter> class_RelativeLayoutParameter(isolate);
    class_RelativeLayoutParameter.ctor([]() { return new ax::ui::RelativeLayoutParameter(); })
        .template inherit<ax::ui::LayoutParameter>()
        .member_function("setAlign", &ax::ui::RelativeLayoutParameter::setAlign)
        .member_function("getAlign", &ax::ui::RelativeLayoutParameter::getAlign)
        .member_function("setRelativeToWidgetName", &ax::ui::RelativeLayoutParameter::setRelativeToWidgetName)
        .member_function("getRelativeToWidgetName", &ax::ui::RelativeLayoutParameter::getRelativeToWidgetName)
        .member_function("setRelativeName", &ax::ui::RelativeLayoutParameter::setRelativeName)
        .member_function("getRelativeName", &ax::ui::RelativeLayoutParameter::getRelativeName)
        .static_function("create", &ax::ui::RelativeLayoutParameter::create)
        .auto_wrap_objects(true);
    mod.class_("RelativeLayoutParameter", class_RelativeLayoutParameter);
}
static void js_register_ax_ui_Widget(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::Widget> class_Widget(isolate);
    class_Widget.ctor([]() { return new ax::ui::Widget(); })
        .template inherit<ax::ProtectedNode>()
        .member_function("setEnabled", &ax::ui::Widget::setEnabled)
        .member_function("isEnabled", &ax::ui::Widget::isEnabled)
        .member_function("setBright", &ax::ui::Widget::setBright)
        .member_function("isBright", &ax::ui::Widget::isBright)
        .member_function("setTouchEnabled", &ax::ui::Widget::setTouchEnabled)
        .member_function("setBrightStyle", &ax::ui::Widget::setBrightStyle)
        .member_function("setMouseEnabled", &ax::ui::Widget::setMouseEnabled)
        .member_function("isTouchEnabled", &ax::ui::Widget::isTouchEnabled)
        .member_function("isMouseEnabled", &ax::ui::Widget::isMouseEnabled)
        .member_function("isHighlighted", &ax::ui::Widget::isHighlighted)
        .member_function("setHighlighted", &ax::ui::Widget::setHighlighted)
        .member_function("getLeftBoundary", &ax::ui::Widget::getLeftBoundary)
        .member_function("getBottomBoundary", &ax::ui::Widget::getBottomBoundary)
        .member_function("getRightBoundary", &ax::ui::Widget::getRightBoundary)
        .member_function("getTopBoundary", &ax::ui::Widget::getTopBoundary)
        .member_function("setPositionPercent", &ax::ui::Widget::setPositionPercent)
        .member_function("getPositionPercent", &ax::ui::Widget::getPositionPercent)
        .member_function("setPositionType", &ax::ui::Widget::setPositionType)
        .member_function("getPositionType", &ax::ui::Widget::getPositionType)
        .member_function("setFlippedX", &ax::ui::Widget::setFlippedX)
        .member_function("isFlippedX", &ax::ui::Widget::isFlippedX)
        .member_function("setFlippedY", &ax::ui::Widget::setFlippedY)
        .member_function("isFlippedY", &ax::ui::Widget::isFlippedY)
        .member_function("isClippingParentContainsPoint", &ax::ui::Widget::isClippingParentContainsPoint)
        .member_function("getTouchBeganPosition", &ax::ui::Widget::getTouchBeganPosition)
        .member_function("getTouchMovePosition", &ax::ui::Widget::getTouchMovePosition)
        .member_function("getTouchEndPosition", &ax::ui::Widget::getTouchEndPosition)
        .member_function("setSizePercent", &ax::ui::Widget::setSizePercent)
        .member_function("setSizeType", &ax::ui::Widget::setSizeType)
        .member_function("getSizeType", &ax::ui::Widget::getSizeType)
        .member_function("getCustomSize", &ax::ui::Widget::getCustomSize)
        .member_function("getLayoutSize", &ax::ui::Widget::getLayoutSize)
        .member_function("getSizePercent", &ax::ui::Widget::getSizePercent)
        .member_function("onMouseUp", &ax::ui::Widget::onMouseUp)
        .member_function("onMouseDown", &ax::ui::Widget::onMouseDown)
        .member_function("onMouseMove", &ax::ui::Widget::onMouseMove)
        .member_function("onMouseScroll", &ax::ui::Widget::onMouseScroll)
        .member_function("setLayoutParameter", &ax::ui::Widget::setLayoutParameter)
        .member_function("getLayoutParameter", &ax::ui::Widget::getLayoutParameter)
        .member_function("ignoreContentAdaptWithSize", &ax::ui::Widget::ignoreContentAdaptWithSize)
        .member_function("isIgnoreContentAdaptWithSize", &ax::ui::Widget::isIgnoreContentAdaptWithSize)
        .member_function("getVirtualRenderer", &ax::ui::Widget::getVirtualRenderer)
        .member_function("getVirtualRendererSize", &ax::ui::Widget::getVirtualRendererSize)
        .member_function("clone", &ax::ui::Widget::clone)
        .member_function(
            "updateSizeAndPosition",
            [](ax::ui::Widget* self, ax::Vec2 arg0) { self->updateSizeAndPosition(arg0); },
            [](ax::ui::Widget* self) { self->updateSizeAndPosition(); })
        .member_function("setActionTag", &ax::ui::Widget::setActionTag)
        .member_function("getActionTag", &ax::ui::Widget::getActionTag)
        .member_function("setPropagateTouchEvents", &ax::ui::Widget::setPropagateTouchEvents)
        .member_function("isPropagateTouchEvents", &ax::ui::Widget::isPropagateTouchEvents)
        .member_function("setSwallowTouches", &ax::ui::Widget::setSwallowTouches)
        .member_function("isSwallowTouches", &ax::ui::Widget::isSwallowTouches)
        .member_function("setSwallowMouse", &ax::ui::Widget::setSwallowMouse)
        .member_function("isSwallowMouse", &ax::ui::Widget::isSwallowMouse)
        .member_function("isFocused", &ax::ui::Widget::isFocused)
        .member_function("setFocused", &ax::ui::Widget::setFocused)
        .member_function("isFocusEnabled", &ax::ui::Widget::isFocusEnabled)
        .member_function("setFocusEnabled", &ax::ui::Widget::setFocusEnabled)
        .member_function("findNextFocusedWidget", &ax::ui::Widget::findNextFocusedWidget)
        .member_function("requestFocus", &ax::ui::Widget::requestFocus)
        .member_function("setUnifySizeEnabled", &ax::ui::Widget::setUnifySizeEnabled)
        .member_function("isUnifySizeEnabled", &ax::ui::Widget::isUnifySizeEnabled)
        .member_function("setCallbackName", &ax::ui::Widget::setCallbackName)
        .member_function("getCallbackName", &ax::ui::Widget::getCallbackName)
        .member_function("setCallbackType", &ax::ui::Widget::setCallbackType)
        .member_function("getCallbackType", &ax::ui::Widget::getCallbackType)
        .member_function("setLayoutComponentEnabled", &ax::ui::Widget::setLayoutComponentEnabled)
        .member_function("isLayoutComponentEnabled", &ax::ui::Widget::isLayoutComponentEnabled)
        .member_function("interceptTouchEvent", &ax::ui::Widget::interceptTouchEvent)
        .member_function("propagateTouchEvent", &ax::ui::Widget::propagateTouchEvent)
        .member_function("onFocusChange", &ax::ui::Widget::onFocusChange)
        .member_function("dispatchFocusEvent", &ax::ui::Widget::dispatchFocusEvent)
        .static_function("create", &ax::ui::Widget::create)
        .static_function("getCurrentFocusedWidget", &ax::ui::Widget::getCurrentFocusedWidget)
        .static_function("enableDpadNavigation", &ax::ui::Widget::enableDpadNavigation)
        .auto_wrap_objects(true);
    mod.class_("Widget", class_Widget);
}
static void js_register_ax_ui_Layout(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::Layout> class_Layout(isolate);
    class_Layout.ctor([]() { return new ax::ui::Layout(); })
        .template inherit<ax::ui::Widget>()
        .member_function(
            "setBackGroundImage",
            [](ax::ui::Layout* self, std::string_view arg0) { self->setBackGroundImage(arg0); },
            [](ax::ui::Layout* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->setBackGroundImage(arg0, arg1); })
        .member_function("setBackGroundImageCapInsets", &ax::ui::Layout::setBackGroundImageCapInsets)
        .member_function("getBackGroundImageCapInsets", &ax::ui::Layout::getBackGroundImageCapInsets)
        .member_function("setBackGroundColorType", &ax::ui::Layout::setBackGroundColorType)
        .member_function("getBackGroundColorType", &ax::ui::Layout::getBackGroundColorType)
        .member_function("setBackGroundImageScale9Enabled", &ax::ui::Layout::setBackGroundImageScale9Enabled)
        .member_function("isBackGroundImageScale9Enabled", &ax::ui::Layout::isBackGroundImageScale9Enabled)
        .member_function(
            "setBackGroundColor",
            [](ax::ui::Layout* self, ax::Color32 arg0, ax::Color32 arg1) { self->setBackGroundColor(arg0, arg1); },
            [](ax::ui::Layout* self, ax::Color32 arg0) { self->setBackGroundColor(arg0); })
        .member_function("getBackGroundColor", &ax::ui::Layout::getBackGroundColor)
        .member_function("getBackGroundStartColor", &ax::ui::Layout::getBackGroundStartColor)
        .member_function("getBackGroundEndColor", &ax::ui::Layout::getBackGroundEndColor)
        .member_function("setBackGroundColorOpacity", &ax::ui::Layout::setBackGroundColorOpacity)
        .member_function("getBackGroundColorOpacity", &ax::ui::Layout::getBackGroundColorOpacity)
        .member_function("setBackGroundColorVector", &ax::ui::Layout::setBackGroundColorVector)
        .member_function("getBackGroundColorVector", &ax::ui::Layout::getBackGroundColorVector)
        .member_function("setBackGroundImageColor", &ax::ui::Layout::setBackGroundImageColor)
        .member_function("setBackGroundImageOpacity", &ax::ui::Layout::setBackGroundImageOpacity)
        .member_function("getBackGroundImageColor", &ax::ui::Layout::getBackGroundImageColor)
        .member_function("getBackGroundImageOpacity", &ax::ui::Layout::getBackGroundImageOpacity)
        .member_function("removeBackGroundImage", &ax::ui::Layout::removeBackGroundImage)
        .member_function("getBackGroundImageTextureSize", &ax::ui::Layout::getBackGroundImageTextureSize)
        .member_function("setClippingEnabled", &ax::ui::Layout::setClippingEnabled)
        .member_function("setClippingType", &ax::ui::Layout::setClippingType)
        .member_function("getClippingType", &ax::ui::Layout::getClippingType)
        .member_function("isClippingEnabled", &ax::ui::Layout::isClippingEnabled)
        .member_function("setLayoutType", &ax::ui::Layout::setLayoutType)
        .member_function("getLayoutType", &ax::ui::Layout::getLayoutType)
        .member_function("forceDoLayout", &ax::ui::Layout::forceDoLayout)
        .member_function("requestDoLayout", &ax::ui::Layout::requestDoLayout)
        .member_function("setLoopFocus", &ax::ui::Layout::setLoopFocus)
        .member_function("isLoopFocus", &ax::ui::Layout::isLoopFocus)
        .member_function("setPassFocusToChild", &ax::ui::Layout::setPassFocusToChild)
        .member_function("isPassFocusToChild", &ax::ui::Layout::isPassFocusToChild)
        .member_function("getRenderFile", &ax::ui::Layout::getRenderFile)
        .static_function("createInstance", &ax::ui::Layout::createInstance)
        .static_function("create", &ax::ui::Layout::create)
        .auto_wrap_objects(true);
    mod.class_("Layout", class_Layout);
}
static void js_register_ax_ui_Button(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::Button> class_Button(isolate);
    class_Button.ctor([]() { return new ax::ui::Button(); })
        .template inherit<ax::ui::Widget>()
        .member_function(
            "loadTextures",
            [](ax::ui::Button* self, std::string_view arg0, std::string_view arg1) { self->loadTextures(arg0, arg1); },
            [](ax::ui::Button* self, std::string_view arg0, std::string_view arg1, std::string_view arg2)
            { self->loadTextures(arg0, arg1, arg2); },
            [](ax::ui::Button* self,
               std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               ax::ui::Widget::TextureResType arg3) { self->loadTextures(arg0, arg1, arg2, arg3); })
        .member_function(
            "loadTextureNormal",
            [](ax::ui::Button* self, std::string_view arg0) { self->loadTextureNormal(arg0); },
            [](ax::ui::Button* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->loadTextureNormal(arg0, arg1); })
        .member_function(
            "loadTexturePressed",
            [](ax::ui::Button* self, std::string_view arg0) { self->loadTexturePressed(arg0); },
            [](ax::ui::Button* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->loadTexturePressed(arg0, arg1); })
        .member_function(
            "loadTextureDisabled",
            [](ax::ui::Button* self, std::string_view arg0) { self->loadTextureDisabled(arg0); },
            [](ax::ui::Button* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->loadTextureDisabled(arg0, arg1); })
        .member_function("setCapInsets", &ax::ui::Button::setCapInsets)
        .member_function("setCapInsetsNormalRenderer", &ax::ui::Button::setCapInsetsNormalRenderer)
        .member_function("getCapInsetsNormalRenderer", &ax::ui::Button::getCapInsetsNormalRenderer)
        .member_function("setCapInsetsPressedRenderer", &ax::ui::Button::setCapInsetsPressedRenderer)
        .member_function("getCapInsetsPressedRenderer", &ax::ui::Button::getCapInsetsPressedRenderer)
        .member_function("setCapInsetsDisabledRenderer", &ax::ui::Button::setCapInsetsDisabledRenderer)
        .member_function("getCapInsetsDisabledRenderer", &ax::ui::Button::getCapInsetsDisabledRenderer)
        .member_function("setScale9Enabled", &ax::ui::Button::setScale9Enabled)
        .member_function("isScale9Enabled", &ax::ui::Button::isScale9Enabled)
        .member_function("setPressedActionEnabled", &ax::ui::Button::setPressedActionEnabled)
        .member_function("getTitleRenderer", &ax::ui::Button::getTitleRenderer)
        .member_function("setTitleText", &ax::ui::Button::setTitleText)
        .member_function("getTitleText", &ax::ui::Button::getTitleText)
        .member_function("setTitleColor", &ax::ui::Button::setTitleColor)
        .member_function("getTitleColor", &ax::ui::Button::getTitleColor)
        .member_function("setTitleFontSize", &ax::ui::Button::setTitleFontSize)
        .member_function("getTitleFontSize", &ax::ui::Button::getTitleFontSize)
        .member_function("setTitleFontName", &ax::ui::Button::setTitleFontName)
        .member_function("getTitleFontName", &ax::ui::Button::getTitleFontName)
        .member_function(
            "setTitleAlignment",
            [](ax::ui::Button* self, ax::TextHAlignment arg0, ax::TextVAlignment arg1) { self->setTitleAlignment(arg0, arg1); },
            [](ax::ui::Button* self, ax::TextHAlignment arg0) { self->setTitleAlignment(arg0); })
        .member_function("setTitleLabel", &ax::ui::Button::setTitleLabel)
        .member_function("getTitleLabel", &ax::ui::Button::getTitleLabel)
        .member_function("setZoomScale", &ax::ui::Button::setZoomScale)
        .member_function("getZoomScale", &ax::ui::Button::getZoomScale)
        .member_function("getRendererNormal", &ax::ui::Button::getRendererNormal)
        .member_function("getRendererClicked", &ax::ui::Button::getRendererClicked)
        .member_function("getRendererDisabled", &ax::ui::Button::getRendererDisabled)
        .member_function("resetNormalRender", &ax::ui::Button::resetNormalRender)
        .member_function("resetPressedRender", &ax::ui::Button::resetPressedRender)
        .member_function("resetDisabledRender", &ax::ui::Button::resetDisabledRender)
        .member_function("getNormalFile", &ax::ui::Button::getNormalFile)
        .member_function("getPressedFile", &ax::ui::Button::getPressedFile)
        .member_function("getDisabledFile", &ax::ui::Button::getDisabledFile)
        .member_function(
            "init",
            [](ax::ui::Button* self, std::string_view arg0) { return self->init(arg0); },
            [](ax::ui::Button* self, std::string_view arg0, std::string_view arg1) { return self->init(arg0, arg1); },
            [](ax::ui::Button* self, std::string_view arg0, std::string_view arg1, std::string_view arg2)
            { return self->init(arg0, arg1, arg2); },
            [](ax::ui::Button* self,
               std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               ax::ui::Widget::TextureResType arg3) { return self->init(arg0, arg1, arg2, arg3); })
        .member_function("getNormalTextureSize", &ax::ui::Button::getNormalTextureSize)
        .static_function("createInstance", &ax::ui::Button::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::ui::Button::create(arg0); },
            [](std::string_view arg0, std::string_view arg1) { return ax::ui::Button::create(arg0, arg1); },
            [](std::string_view arg0, std::string_view arg1, std::string_view arg2) { return ax::ui::Button::create(arg0, arg1, arg2); },
            [](std::string_view arg0, std::string_view arg1, std::string_view arg2, ax::ui::Widget::TextureResType arg3)
            { return ax::ui::Button::create(arg0, arg1, arg2, arg3); },
            []() { return ax::ui::Button::create(); })
        .auto_wrap_objects(true);
    mod.class_("Button", class_Button);
}
static void js_register_ax_ui_AbstractCheckButton(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::AbstractCheckButton> class_AbstractCheckButton(isolate);
    class_AbstractCheckButton.template inherit<ax::ui::Widget>()
        .member_function(
            "loadTextures",
            [](ax::ui::AbstractCheckButton* self,
               std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4) { self->loadTextures(arg0, arg1, arg2, arg3, arg4); },
            [](ax::ui::AbstractCheckButton* self,
               std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4,
               ax::ui::Widget::TextureResType arg5) { self->loadTextures(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function(
            "loadTextureBackGround",
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0) { self->loadTextureBackGround(arg0); },
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadTextureBackGround(arg0, arg1); })
        .member_function(
            "loadTextureBackGroundSelected",
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0) { self->loadTextureBackGroundSelected(arg0); },
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadTextureBackGroundSelected(arg0, arg1); })
        .member_function(
            "loadTextureFrontCross",
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0) { self->loadTextureFrontCross(arg0); },
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadTextureFrontCross(arg0, arg1); })
        .member_function(
            "loadTextureBackGroundDisabled",
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0) { self->loadTextureBackGroundDisabled(arg0); },
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadTextureBackGroundDisabled(arg0, arg1); })
        .member_function(
            "loadTextureFrontCrossDisabled",
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0) { self->loadTextureFrontCrossDisabled(arg0); },
            [](ax::ui::AbstractCheckButton* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadTextureFrontCrossDisabled(arg0, arg1); })
        .member_function("isSelected", &ax::ui::AbstractCheckButton::isSelected)
        .member_function("setSelected", &ax::ui::AbstractCheckButton::setSelected)
        .member_function("setZoomScale", &ax::ui::AbstractCheckButton::setZoomScale)
        .member_function("getZoomScale", &ax::ui::AbstractCheckButton::getZoomScale)
        .member_function("getRendererBackground", &ax::ui::AbstractCheckButton::getRendererBackground)
        .member_function("getRendererBackgroundSelected", &ax::ui::AbstractCheckButton::getRendererBackgroundSelected)
        .member_function("getRendererFrontCross", &ax::ui::AbstractCheckButton::getRendererFrontCross)
        .member_function("getRendererBackgroundDisabled", &ax::ui::AbstractCheckButton::getRendererBackgroundDisabled)
        .member_function("getRendererFrontCrossDisabled", &ax::ui::AbstractCheckButton::getRendererFrontCrossDisabled)
        .member_function("getBackNormalFile", &ax::ui::AbstractCheckButton::getBackNormalFile)
        .member_function("getBackPressedFile", &ax::ui::AbstractCheckButton::getBackPressedFile)
        .member_function("getBackDisabledFile", &ax::ui::AbstractCheckButton::getBackDisabledFile)
        .member_function("getCrossNormalFile", &ax::ui::AbstractCheckButton::getCrossNormalFile)
        .member_function("getCrossDisabledFile", &ax::ui::AbstractCheckButton::getCrossDisabledFile)
        .member_function(
            "init",
            [](ax::ui::AbstractCheckButton* self,
               std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4) { return self->init(arg0, arg1, arg2, arg3, arg4); },
            [](ax::ui::AbstractCheckButton* self,
               std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4,
               ax::ui::Widget::TextureResType arg5) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5); })
        .auto_wrap_objects(true);
    mod.class_("AbstractCheckButton", class_AbstractCheckButton);
}
static void js_register_ax_ui_CheckBox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::CheckBox> class_CheckBox(isolate);
    class_CheckBox.ctor([]() { return new ax::ui::CheckBox(); })
        .template inherit<ax::ui::AbstractCheckButton>()
        .member_function("addEventListener", &ax::ui::CheckBox::addEventListener)
        .static_function("createInstance", &ax::ui::CheckBox::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0, std::string_view arg1, std::string_view arg2, std::string_view arg3, std::string_view arg4)
            { return ax::ui::CheckBox::create(arg0, arg1, arg2, arg3, arg4); },
            [](std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4,
               ax::ui::Widget::TextureResType arg5) { return ax::ui::CheckBox::create(arg0, arg1, arg2, arg3, arg4, arg5); },
            []() { return ax::ui::CheckBox::create(); },
            [](std::string_view arg0, std::string_view arg1) { return ax::ui::CheckBox::create(arg0, arg1); },
            [](std::string_view arg0, std::string_view arg1, ax::ui::Widget::TextureResType arg2)
            { return ax::ui::CheckBox::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("CheckBox", class_CheckBox);
}
static void js_register_ax_ui_RadioButton(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RadioButton> class_RadioButton(isolate);
    class_RadioButton.ctor([]() { return new ax::ui::RadioButton(); })
        .template inherit<ax::ui::AbstractCheckButton>()
        .member_function("addEventListener", &ax::ui::RadioButton::addEventListener)
        .static_function("createInstance", &ax::ui::RadioButton::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0, std::string_view arg1, std::string_view arg2, std::string_view arg3, std::string_view arg4)
            { return ax::ui::RadioButton::create(arg0, arg1, arg2, arg3, arg4); },
            [](std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4,
               ax::ui::Widget::TextureResType arg5) { return ax::ui::RadioButton::create(arg0, arg1, arg2, arg3, arg4, arg5); },
            []() { return ax::ui::RadioButton::create(); },
            [](std::string_view arg0, std::string_view arg1) { return ax::ui::RadioButton::create(arg0, arg1); },
            [](std::string_view arg0, std::string_view arg1, ax::ui::Widget::TextureResType arg2)
            { return ax::ui::RadioButton::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("RadioButton", class_RadioButton);
}
static void js_register_ax_ui_RadioButtonGroup(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RadioButtonGroup> class_RadioButtonGroup(isolate);
    class_RadioButtonGroup.ctor([]() { return new ax::ui::RadioButtonGroup(); })
        .template inherit<ax::ui::Widget>()
        .member_function("addEventListener", &ax::ui::RadioButtonGroup::addEventListener)
        .member_function("getSelectedButtonIndex", &ax::ui::RadioButtonGroup::getSelectedButtonIndex)
        .member_function(
            "setSelectedButton",
            [](ax::ui::RadioButtonGroup* self, ax::ui::RadioButton* arg0) { self->setSelectedButton(arg0); },
            [](ax::ui::RadioButtonGroup* self, int arg0) { self->setSelectedButton(arg0); })
        .member_function(
            "setSelectedButtonWithoutEvent",
            [](ax::ui::RadioButtonGroup* self, ax::ui::RadioButton* arg0) { self->setSelectedButtonWithoutEvent(arg0); },
            [](ax::ui::RadioButtonGroup* self, int arg0) { self->setSelectedButtonWithoutEvent(arg0); })
        .member_function("addRadioButton", &ax::ui::RadioButtonGroup::addRadioButton)
        .member_function("removeRadioButton", &ax::ui::RadioButtonGroup::removeRadioButton)
        .member_function("removeAllRadioButtons", &ax::ui::RadioButtonGroup::removeAllRadioButtons)
        .member_function("getNumberOfRadioButtons", &ax::ui::RadioButtonGroup::getNumberOfRadioButtons)
        .member_function("getRadioButtonByIndex", &ax::ui::RadioButtonGroup::getRadioButtonByIndex)
        .member_function("setAllowedNoSelection", &ax::ui::RadioButtonGroup::setAllowedNoSelection)
        .member_function("isAllowedNoSelection", &ax::ui::RadioButtonGroup::isAllowedNoSelection)
        .static_function("create", &ax::ui::RadioButtonGroup::create)
        .auto_wrap_objects(true);
    mod.class_("RadioButtonGroup", class_RadioButtonGroup);
}
static void js_register_ax_ui_ImageView(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::ImageView> class_ImageView(isolate);
    class_ImageView.ctor([]() { return new ax::ui::ImageView(); })
        .template inherit<ax::ui::Widget>()
        .member_function(
            "loadTexture",
            [](ax::ui::ImageView* self, std::string_view arg0) { self->loadTexture(arg0); },
            [](ax::ui::ImageView* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->loadTexture(arg0, arg1); })
        .member_function("setTextureRect", &ax::ui::ImageView::setTextureRect)
        .member_function("setScale9Enabled", &ax::ui::ImageView::setScale9Enabled)
        .member_function("isScale9Enabled", &ax::ui::ImageView::isScale9Enabled)
        .member_function("setCapInsets", &ax::ui::ImageView::setCapInsets)
        .member_function("getCapInsets", &ax::ui::ImageView::getCapInsets)
        .member_function("setBlendFunc", &ax::ui::ImageView::setBlendFunc)
        .member_function("getBlendFunc", &ax::ui::ImageView::getBlendFunc)
        .member_function("getRenderFile", &ax::ui::ImageView::getRenderFile)
        .member_function(
            "init",
            [](ax::ui::ImageView* self, std::string_view arg0) { return self->init(arg0); },
            [](ax::ui::ImageView* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { return self->init(arg0, arg1); })
        .static_function("createInstance", &ax::ui::ImageView::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::ui::ImageView::create(arg0); },
            [](std::string_view arg0, ax::ui::Widget::TextureResType arg1) { return ax::ui::ImageView::create(arg0, arg1); },
            []() { return ax::ui::ImageView::create(); })
        .auto_wrap_objects(true);
    mod.class_("ImageView", class_ImageView);
}
static void js_register_ax_ui_Text(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::Text> class_Text(isolate);
    class_Text.ctor([]() { return new ax::ui::Text(); })
        .template inherit<ax::ui::Widget>()
        .member_function("setString", &ax::ui::Text::setString)
        .member_function("getString", &ax::ui::Text::getString)
        .member_function("getStringLength", &ax::ui::Text::getStringLength)
        .member_function("setFontSize", &ax::ui::Text::setFontSize)
        .member_function("getFontSize", &ax::ui::Text::getFontSize)
        .member_function("setFontName", &ax::ui::Text::setFontName)
        .member_function("getFontName", &ax::ui::Text::getFontName)
        .member_function("getType", &ax::ui::Text::getType)
        .member_function("setTouchScaleChangeEnabled", &ax::ui::Text::setTouchScaleChangeEnabled)
        .member_function("isTouchScaleChangeEnabled", &ax::ui::Text::isTouchScaleChangeEnabled)
        .member_function("getAutoRenderSize", &ax::ui::Text::getAutoRenderSize)
        .member_function("setTextAreaSize", &ax::ui::Text::setTextAreaSize)
        .member_function("getTextAreaSize", &ax::ui::Text::getTextAreaSize)
        .member_function("setTextHorizontalAlignment", &ax::ui::Text::setTextHorizontalAlignment)
        .member_function("getTextHorizontalAlignment", &ax::ui::Text::getTextHorizontalAlignment)
        .member_function("setTextVerticalAlignment", &ax::ui::Text::setTextVerticalAlignment)
        .member_function("getTextVerticalAlignment", &ax::ui::Text::getTextVerticalAlignment)
        .member_function("setTextColor", &ax::ui::Text::setTextColor)
        .member_function("getTextColor", &ax::ui::Text::getTextColor)
        .member_function(
            "enableShadow",
            [](ax::ui::Text* self) { self->enableShadow(); },
            [](ax::ui::Text* self, ax::Color32 arg0) { self->enableShadow(arg0); },
            [](ax::ui::Text* self, ax::Color32 arg0, ax::Vec2 arg1) { self->enableShadow(arg0, arg1); },
            [](ax::ui::Text* self, ax::Color32 arg0, ax::Vec2 arg1, int arg2) { self->enableShadow(arg0, arg1, arg2); })
        .member_function(
            "enableOutline",
            [](ax::ui::Text* self, ax::Color32 arg0) { self->enableOutline(arg0); },
            [](ax::ui::Text* self, ax::Color32 arg0, int arg1) { self->enableOutline(arg0, arg1); })
        .member_function("enableGlow", &ax::ui::Text::enableGlow)
        .member_function(
            "disableEffect",
            [](ax::ui::Text* self, ax::LabelEffect arg0) { self->disableEffect(arg0); },
            [](ax::ui::Text* self) { self->disableEffect(); })
        .member_function("isShadowEnabled", &ax::ui::Text::isShadowEnabled)
        .member_function("getShadowOffset", &ax::ui::Text::getShadowOffset)
        .member_function("getShadowBlurRadius", &ax::ui::Text::getShadowBlurRadius)
        .member_function("getShadowColor", &ax::ui::Text::getShadowColor)
        .member_function("getOutlineSize", &ax::ui::Text::getOutlineSize)
        .member_function("getLabelEffectType", &ax::ui::Text::getLabelEffectType)
        .member_function("getEffectColor", &ax::ui::Text::getEffectColor)
        .member_function("getLetter", &ax::ui::Text::getLetter)
        .member_function("setBlendFunc", &ax::ui::Text::setBlendFunc)
        .member_function("getBlendFunc", &ax::ui::Text::getBlendFunc)
        .static_function("createInstance", &ax::ui::Text::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0, std::string_view arg1, float arg2) { return ax::ui::Text::create(arg0, arg1, arg2); },
            []() { return ax::ui::Text::create(); })
        .auto_wrap_objects(true);
    mod.class_("Text", class_Text);
}
static void js_register_ax_ui_TextAtlas(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::TextAtlas> class_TextAtlas(isolate);
    class_TextAtlas.ctor([]() { return new ax::ui::TextAtlas(); })
        .template inherit<ax::ui::Widget>()
        .member_function("setProperty", &ax::ui::TextAtlas::setProperty)
        .member_function("setString", &ax::ui::TextAtlas::setString)
        .member_function("getString", &ax::ui::TextAtlas::getString)
        .member_function("getStringLength", &ax::ui::TextAtlas::getStringLength)
        .member_function("adaptRenderers", &ax::ui::TextAtlas::adaptRenderers)
        .member_function("getRenderFile", &ax::ui::TextAtlas::getRenderFile)
        .static_function("createInstance", &ax::ui::TextAtlas::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0, std::string_view arg1, int arg2, int arg3, std::string_view arg4)
            { return ax::ui::TextAtlas::create(arg0, arg1, arg2, arg3, arg4); },
            []() { return ax::ui::TextAtlas::create(); })
        .auto_wrap_objects(true);
    mod.class_("TextAtlas", class_TextAtlas);
}
static void js_register_ax_ui_LoadingBar(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::LoadingBar> class_LoadingBar(isolate);
    class_LoadingBar.ctor([]() { return new ax::ui::LoadingBar(); })
        .template inherit<ax::ui::Widget>()
        .member_function("setDirection", &ax::ui::LoadingBar::setDirection)
        .member_function("getDirection", &ax::ui::LoadingBar::getDirection)
        .member_function(
            "loadTexture",
            [](ax::ui::LoadingBar* self, std::string_view arg0) { self->loadTexture(arg0); },
            [](ax::ui::LoadingBar* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->loadTexture(arg0, arg1); })
        .member_function("setPercent", &ax::ui::LoadingBar::setPercent)
        .member_function("getPercent", &ax::ui::LoadingBar::getPercent)
        .member_function("setScale9Enabled", &ax::ui::LoadingBar::setScale9Enabled)
        .member_function("isScale9Enabled", &ax::ui::LoadingBar::isScale9Enabled)
        .member_function("setCapInsets", &ax::ui::LoadingBar::setCapInsets)
        .member_function("getCapInsets", &ax::ui::LoadingBar::getCapInsets)
        .member_function("getRenderFile", &ax::ui::LoadingBar::getRenderFile)
        .static_function("createInstance", &ax::ui::LoadingBar::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::ui::LoadingBar::create(arg0); },
            [](std::string_view arg0, float arg1) { return ax::ui::LoadingBar::create(arg0, arg1); },
            []() { return ax::ui::LoadingBar::create(); },
            [](std::string_view arg0, ax::ui::Widget::TextureResType arg1) { return ax::ui::LoadingBar::create(arg0, arg1); },
            [](std::string_view arg0, ax::ui::Widget::TextureResType arg1, float arg2)
            { return ax::ui::LoadingBar::create(arg0, arg1, arg2); })
        .auto_wrap_objects(true);
    mod.class_("LoadingBar", class_LoadingBar);
}
static void js_register_ax_ui_ScrollView(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::ScrollView> class_ScrollView(isolate);
    class_ScrollView.ctor([]() { return new ax::ui::ScrollView(); })
        .template inherit<ax::ui::Layout>()
        .member_function("setDirection", &ax::ui::ScrollView::setDirection)
        .member_function("getDirection", &ax::ui::ScrollView::getDirection)
        .member_function("getInnerContainer", &ax::ui::ScrollView::getInnerContainer)
        .member_function("stopScroll", &ax::ui::ScrollView::stopScroll)
        .member_function("stopAutoScroll", &ax::ui::ScrollView::stopAutoScroll)
        .member_function("stopOverallScroll", &ax::ui::ScrollView::stopOverallScroll)
        .member_function("scrollToBottom", &ax::ui::ScrollView::scrollToBottom)
        .member_function("scrollToTop", &ax::ui::ScrollView::scrollToTop)
        .member_function("scrollToLeft", &ax::ui::ScrollView::scrollToLeft)
        .member_function("scrollToRight", &ax::ui::ScrollView::scrollToRight)
        .member_function("scrollToTopLeft", &ax::ui::ScrollView::scrollToTopLeft)
        .member_function("scrollToTopRight", &ax::ui::ScrollView::scrollToTopRight)
        .member_function("scrollToBottomLeft", &ax::ui::ScrollView::scrollToBottomLeft)
        .member_function("scrollToBottomRight", &ax::ui::ScrollView::scrollToBottomRight)
        .member_function("scrollToPercentVertical", &ax::ui::ScrollView::scrollToPercentVertical)
        .member_function("scrollToPercentHorizontal", &ax::ui::ScrollView::scrollToPercentHorizontal)
        .member_function("scrollToPercentBothDirection", &ax::ui::ScrollView::scrollToPercentBothDirection)
        .member_function("getScrolledPercentVertical", &ax::ui::ScrollView::getScrolledPercentVertical)
        .member_function("getScrolledPercentHorizontal", &ax::ui::ScrollView::getScrolledPercentHorizontal)
        .member_function("getScrolledPercentBothDirection", &ax::ui::ScrollView::getScrolledPercentBothDirection)
        .member_function("jumpToBottom", &ax::ui::ScrollView::jumpToBottom)
        .member_function("jumpToTop", &ax::ui::ScrollView::jumpToTop)
        .member_function("jumpToLeft", &ax::ui::ScrollView::jumpToLeft)
        .member_function("jumpToRight", &ax::ui::ScrollView::jumpToRight)
        .member_function("jumpToTopLeft", &ax::ui::ScrollView::jumpToTopLeft)
        .member_function("jumpToTopRight", &ax::ui::ScrollView::jumpToTopRight)
        .member_function("jumpToBottomLeft", &ax::ui::ScrollView::jumpToBottomLeft)
        .member_function("jumpToBottomRight", &ax::ui::ScrollView::jumpToBottomRight)
        .member_function("jumpToPercentVertical", &ax::ui::ScrollView::jumpToPercentVertical)
        .member_function("jumpToPercentHorizontal", &ax::ui::ScrollView::jumpToPercentHorizontal)
        .member_function("jumpToPercentBothDirection", &ax::ui::ScrollView::jumpToPercentBothDirection)
        .member_function("setInnerContainerSize", &ax::ui::ScrollView::setInnerContainerSize)
        .member_function("getInnerContainerSize", &ax::ui::ScrollView::getInnerContainerSize)
        .member_function("setInnerContainerPosition", &ax::ui::ScrollView::setInnerContainerPosition)
        .member_function("getInnerContainerPosition", &ax::ui::ScrollView::getInnerContainerPosition)
        .member_function("addEventListener", &ax::ui::ScrollView::addEventListener)
        .member_function("setBounceEnabled", &ax::ui::ScrollView::setBounceEnabled)
        .member_function("isBounceEnabled", &ax::ui::ScrollView::isBounceEnabled)
        .member_function("setInertiaScrollEnabled", &ax::ui::ScrollView::setInertiaScrollEnabled)
        .member_function("isInertiaScrollEnabled", &ax::ui::ScrollView::isInertiaScrollEnabled)
        .member_function("setScrollBarEnabled", &ax::ui::ScrollView::setScrollBarEnabled)
        .member_function("isScrollBarEnabled", &ax::ui::ScrollView::isScrollBarEnabled)
        .member_function("setScrollBarPositionFromCorner", &ax::ui::ScrollView::setScrollBarPositionFromCorner)
        .member_function("setScrollBarPositionFromCornerForVertical", &ax::ui::ScrollView::setScrollBarPositionFromCornerForVertical)
        .member_function("getScrollBarPositionFromCornerForVertical", &ax::ui::ScrollView::getScrollBarPositionFromCornerForVertical)
        .member_function("setScrollBarPositionFromCornerForHorizontal", &ax::ui::ScrollView::setScrollBarPositionFromCornerForHorizontal)
        .member_function("getScrollBarPositionFromCornerForHorizontal", &ax::ui::ScrollView::getScrollBarPositionFromCornerForHorizontal)
        .member_function("setScrollBarWidth", &ax::ui::ScrollView::setScrollBarWidth)
        .member_function("getScrollBarWidth", &ax::ui::ScrollView::getScrollBarWidth)
        .member_function("setScrollBarColor", &ax::ui::ScrollView::setScrollBarColor)
        .member_function("getScrollBarColor", &ax::ui::ScrollView::getScrollBarColor)
        .member_function("setScrollBarOpacity", &ax::ui::ScrollView::setScrollBarOpacity)
        .member_function("getScrollBarOpacity", &ax::ui::ScrollView::getScrollBarOpacity)
        .member_function("setScrollBarAutoHideEnabled", &ax::ui::ScrollView::setScrollBarAutoHideEnabled)
        .member_function("isScrollBarAutoHideEnabled", &ax::ui::ScrollView::isScrollBarAutoHideEnabled)
        .member_function("setScrollBarAutoHideTime", &ax::ui::ScrollView::setScrollBarAutoHideTime)
        .member_function("getScrollBarAutoHideTime", &ax::ui::ScrollView::getScrollBarAutoHideTime)
        .member_function("setTouchTotalTimeThreshold", &ax::ui::ScrollView::setTouchTotalTimeThreshold)
        .member_function("getTouchTotalTimeThreshold", &ax::ui::ScrollView::getTouchTotalTimeThreshold)
        .member_function("setScrollDuration", &ax::ui::ScrollView::setScrollDuration)
        .member_function("getScrollDuration", &ax::ui::ScrollView::getScrollDuration)
        .member_function("isScrolling", &ax::ui::ScrollView::isScrolling)
        .member_function("isAutoScrolling", &ax::ui::ScrollView::isAutoScrolling)
        .member_function(
            "scrollToItem",
            [](ax::ui::ScrollView* self, ax::Node* arg0, ax::Vec2 arg1, ax::Vec2 arg2, float arg3)
            { self->scrollToItem(arg0, arg1, arg2, arg3); },
            [](ax::ui::ScrollView* self, ax::Node* arg0, ax::Vec2 arg1, ax::Vec2 arg2) { self->scrollToItem(arg0, arg1, arg2); })
        .static_function("createInstance", &ax::ui::ScrollView::createInstance)
        .static_function("create", &ax::ui::ScrollView::create)
        .static_function("calculateItemPositionWithAnchor", &ax::ui::ScrollView::calculateItemPositionWithAnchor)
        .auto_wrap_objects(true);
    mod.class_("ScrollView", class_ScrollView);
}
static void js_register_ax_ui_ListView(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::ListView> class_ListView(isolate);
    class_ListView.ctor([]() { return new ax::ui::ListView(); })
        .template inherit<ax::ui::ScrollView>()
        .member_function("setItemModel", &ax::ui::ListView::setItemModel)
        .member_function("pushBackDefaultItem", &ax::ui::ListView::pushBackDefaultItem)
        .member_function("insertDefaultItem", &ax::ui::ListView::insertDefaultItem)
        .member_function("pushBackCustomItem", &ax::ui::ListView::pushBackCustomItem)
        .member_function("insertCustomItem", &ax::ui::ListView::insertCustomItem)
        .member_function("removeLastItem", &ax::ui::ListView::removeLastItem)
        .member_function("removeItem", &ax::ui::ListView::removeItem)
        .member_function("removeAllItems", &ax::ui::ListView::removeAllItems)
        .member_function("getItem", &ax::ui::ListView::getItem)
        .member_function("getItems", &ax::ui::ListView::getItems)
        .member_function("getIndex", &ax::ui::ListView::getIndex)
        .member_function("setGravity", &ax::ui::ListView::setGravity)
        .member_function("setMagneticType", &ax::ui::ListView::setMagneticType)
        .member_function("getMagneticType", &ax::ui::ListView::getMagneticType)
        .member_function("setMagneticAllowedOutOfBoundary", &ax::ui::ListView::setMagneticAllowedOutOfBoundary)
        .member_function("getMagneticAllowedOutOfBoundary", &ax::ui::ListView::getMagneticAllowedOutOfBoundary)
        .member_function("setItemsMargin", &ax::ui::ListView::setItemsMargin)
        .member_function("getItemsMargin", &ax::ui::ListView::getItemsMargin)
        .member_function("setPadding", &ax::ui::ListView::setPadding)
        .member_function("setLeftPadding", &ax::ui::ListView::setLeftPadding)
        .member_function("setTopPadding", &ax::ui::ListView::setTopPadding)
        .member_function("setRightPadding", &ax::ui::ListView::setRightPadding)
        .member_function("setBottomPadding", &ax::ui::ListView::setBottomPadding)
        .member_function("getLeftPadding", &ax::ui::ListView::getLeftPadding)
        .member_function("getTopPadding", &ax::ui::ListView::getTopPadding)
        .member_function("getRightPadding", &ax::ui::ListView::getRightPadding)
        .member_function("getBottomPadding", &ax::ui::ListView::getBottomPadding)
        .member_function("doLayout", &ax::ui::ListView::doLayout)
        .member_function("getClosestItemToPosition", &ax::ui::ListView::getClosestItemToPosition)
        .member_function("getClosestItemToPositionInCurrentView", &ax::ui::ListView::getClosestItemToPositionInCurrentView)
        .member_function("getCenterItemInCurrentView", &ax::ui::ListView::getCenterItemInCurrentView)
        .member_function("getLeftmostItemInCurrentView", &ax::ui::ListView::getLeftmostItemInCurrentView)
        .member_function("getRightmostItemInCurrentView", &ax::ui::ListView::getRightmostItemInCurrentView)
        .member_function("getTopmostItemInCurrentView", &ax::ui::ListView::getTopmostItemInCurrentView)
        .member_function("getBottommostItemInCurrentView", &ax::ui::ListView::getBottommostItemInCurrentView)
        .member_function("jumpToItem", &ax::ui::ListView::jumpToItem)
        .member_function(
            "scrollToItem",
            [](ax::ui::ListView* self, ssize_t arg0, ax::Vec2 arg1, ax::Vec2 arg2, float arg3)
            { self->scrollToItem(arg0, arg1, arg2, arg3); },
            [](ax::ui::ListView* self, ssize_t arg0, ax::Vec2 arg1, ax::Vec2 arg2) { self->scrollToItem(arg0, arg1, arg2); })
        .member_function("getCurSelectedIndex", &ax::ui::ListView::getCurSelectedIndex)
        .member_function("setCurSelectedIndex", &ax::ui::ListView::setCurSelectedIndex)
        // .member_function("addEventListener", &ax::ui::ListView::addEventListener)
        .static_function("createInstance", &ax::ui::ListView::createInstance)
        .static_function("create", &ax::ui::ListView::create)
        .auto_wrap_objects(true);
    mod.class_("ListView", class_ListView);
}
static void js_register_ax_ui_Slider(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::Slider> class_Slider(isolate);
    class_Slider.ctor([]() { return new ax::ui::Slider(); })
        .template inherit<ax::ui::Widget>()
        .member_function(
            "loadBarTexture",
            [](ax::ui::Slider* self, std::string_view arg0) { self->loadBarTexture(arg0); },
            [](ax::ui::Slider* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->loadBarTexture(arg0, arg1); })
        .member_function("setScale9Enabled", &ax::ui::Slider::setScale9Enabled)
        .member_function("isScale9Enabled", &ax::ui::Slider::isScale9Enabled)
        .member_function("setCapInsets", &ax::ui::Slider::setCapInsets)
        .member_function("setCapInsetsBarRenderer", &ax::ui::Slider::setCapInsetsBarRenderer)
        .member_function("getCapInsetsBarRenderer", &ax::ui::Slider::getCapInsetsBarRenderer)
        .member_function("setCapInsetProgressBarRenderer", &ax::ui::Slider::setCapInsetProgressBarRenderer)
        .member_function("getCapInsetsProgressBarRenderer", &ax::ui::Slider::getCapInsetsProgressBarRenderer)
        .member_function(
            "loadSlidBallTextures",
            [](ax::ui::Slider* self, std::string_view arg0) { self->loadSlidBallTextures(arg0); },
            [](ax::ui::Slider* self, std::string_view arg0, std::string_view arg1) { self->loadSlidBallTextures(arg0, arg1); },
            [](ax::ui::Slider* self, std::string_view arg0, std::string_view arg1, std::string_view arg2)
            { self->loadSlidBallTextures(arg0, arg1, arg2); },
            [](ax::ui::Slider* self,
               std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               ax::ui::Widget::TextureResType arg3) { self->loadSlidBallTextures(arg0, arg1, arg2, arg3); })
        .member_function(
            "loadSlidBallTextureNormal",
            [](ax::ui::Slider* self, std::string_view arg0) { self->loadSlidBallTextureNormal(arg0); },
            [](ax::ui::Slider* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadSlidBallTextureNormal(arg0, arg1); })
        .member_function(
            "loadSlidBallTexturePressed",
            [](ax::ui::Slider* self, std::string_view arg0) { self->loadSlidBallTexturePressed(arg0); },
            [](ax::ui::Slider* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadSlidBallTexturePressed(arg0, arg1); })
        .member_function(
            "loadSlidBallTextureDisabled",
            [](ax::ui::Slider* self, std::string_view arg0) { self->loadSlidBallTextureDisabled(arg0); },
            [](ax::ui::Slider* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadSlidBallTextureDisabled(arg0, arg1); })
        .member_function(
            "loadProgressBarTexture",
            [](ax::ui::Slider* self, std::string_view arg0) { self->loadProgressBarTexture(arg0); },
            [](ax::ui::Slider* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadProgressBarTexture(arg0, arg1); })
        .member_function("setPercent", &ax::ui::Slider::setPercent)
        .member_function("updateVisualSlider", &ax::ui::Slider::updateVisualSlider)
        .member_function("getPercent", &ax::ui::Slider::getPercent)
        .member_function("setMaxPercent", &ax::ui::Slider::setMaxPercent)
        .member_function("getMaxPercent", &ax::ui::Slider::getMaxPercent)
        .member_function("addEventListener", &ax::ui::Slider::addEventListener)
        .member_function("setZoomScale", &ax::ui::Slider::setZoomScale)
        .member_function("getZoomScale", &ax::ui::Slider::getZoomScale)
        .member_function("getSlidBallNormalRenderer", &ax::ui::Slider::getSlidBallNormalRenderer)
        .member_function("getSlidBallPressedRenderer", &ax::ui::Slider::getSlidBallPressedRenderer)
        .member_function("getSlidBallDisabledRenderer", &ax::ui::Slider::getSlidBallDisabledRenderer)
        .member_function("getSlidBallRenderer", &ax::ui::Slider::getSlidBallRenderer)
        .member_function("getBackFile", &ax::ui::Slider::getBackFile)
        .member_function("getProgressBarFile", &ax::ui::Slider::getProgressBarFile)
        .member_function("getBallNormalFile", &ax::ui::Slider::getBallNormalFile)
        .member_function("getBallPressedFile", &ax::ui::Slider::getBallPressedFile)
        .member_function("getBallDisabledFile", &ax::ui::Slider::getBallDisabledFile)
        .static_function("createInstance", &ax::ui::Slider::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0, std::string_view arg1) { return ax::ui::Slider::create(arg0, arg1); },
            [](std::string_view arg0, std::string_view arg1, ax::ui::Widget::TextureResType arg2)
            { return ax::ui::Slider::create(arg0, arg1, arg2); },
            []() { return ax::ui::Slider::create(); })
        .auto_wrap_objects(true);
    mod.class_("Slider", class_Slider);
}
static void js_register_ax_ui_TextField(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::TextField> class_TextField(isolate);
    class_TextField.ctor([]() { return new ax::ui::TextField(); })
        .template inherit<ax::ui::Widget>()
        .member_function("setTouchSize", &ax::ui::TextField::setTouchSize)
        .member_function("getTouchSize", &ax::ui::TextField::getTouchSize)
        .member_function("setTouchAreaEnabled", &ax::ui::TextField::setTouchAreaEnabled)
        .member_function("setPlaceHolder", &ax::ui::TextField::setPlaceHolder)
        .member_function("getPlaceHolder", &ax::ui::TextField::getPlaceHolder)
        .member_function("getPlaceHolderColor", &ax::ui::TextField::getPlaceHolderColor)
        .member_function("setPlaceHolderColor", &ax::ui::TextField::setPlaceHolderColor)
        .member_function("getTextColor", &ax::ui::TextField::getTextColor)
        .member_function("setTextColor", &ax::ui::TextField::setTextColor)
        .member_function("setFontSize", &ax::ui::TextField::setFontSize)
        .member_function("getFontSize", &ax::ui::TextField::getFontSize)
        .member_function("setFontName", &ax::ui::TextField::setFontName)
        .member_function("getFontName", &ax::ui::TextField::getFontName)
        .member_function("didNotSelectSelf", &ax::ui::TextField::didNotSelectSelf)
        .member_function("setString", &ax::ui::TextField::setString)
        .member_function("getString", &ax::ui::TextField::getString)
        .member_function("setMaxLengthEnabled", &ax::ui::TextField::setMaxLengthEnabled)
        .member_function("isMaxLengthEnabled", &ax::ui::TextField::isMaxLengthEnabled)
        .member_function("setMaxLength", &ax::ui::TextField::setMaxLength)
        .member_function("getMaxLength", &ax::ui::TextField::getMaxLength)
        .member_function("getStringLength", &ax::ui::TextField::getStringLength)
        .member_function("setPasswordEnabled", &ax::ui::TextField::setPasswordEnabled)
        .member_function("isPasswordEnabled", &ax::ui::TextField::isPasswordEnabled)
        .member_function("setPasswordStyleText", &ax::ui::TextField::setPasswordStyleText)
        .member_function("getPasswordStyleText", &ax::ui::TextField::getPasswordStyleText)
        .member_function("getAttachWithIME", &ax::ui::TextField::getAttachWithIME)
        .member_function("setAttachWithIME", &ax::ui::TextField::setAttachWithIME)
        .member_function("getDetachWithIME", &ax::ui::TextField::getDetachWithIME)
        .member_function("setDetachWithIME", &ax::ui::TextField::setDetachWithIME)
        .member_function("getInsertText", &ax::ui::TextField::getInsertText)
        .member_function("setInsertText", &ax::ui::TextField::setInsertText)
        .member_function("getDeleteBackward", &ax::ui::TextField::getDeleteBackward)
        .member_function("setDeleteBackward", &ax::ui::TextField::setDeleteBackward)
        .member_function("addEventListener", &ax::ui::TextField::addEventListener)
        .member_function("getAutoRenderSize", &ax::ui::TextField::getAutoRenderSize)
        .member_function("attachWithIME", &ax::ui::TextField::attachWithIME)
        .member_function("detachWithIME", &ax::ui::TextField::detachWithIME)
        .member_function("setTextAreaSize", &ax::ui::TextField::setTextAreaSize)
        .member_function("setTextHorizontalAlignment", &ax::ui::TextField::setTextHorizontalAlignment)
        .member_function("getTextHorizontalAlignment", &ax::ui::TextField::getTextHorizontalAlignment)
        .member_function("setTextVerticalAlignment", &ax::ui::TextField::setTextVerticalAlignment)
        .member_function("getTextVerticalAlignment", &ax::ui::TextField::getTextVerticalAlignment)
        .member_function("setCursorEnabled", &ax::ui::TextField::setCursorEnabled)
        .member_function("setCursorChar", &ax::ui::TextField::setCursorChar)
        .member_function("setCursorFromPoint", &ax::ui::TextField::setCursorFromPoint)
        .static_function("createInstance", &ax::ui::TextField::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0, std::string_view arg1, int arg2) { return ax::ui::TextField::create(arg0, arg1, arg2); },
            []() { return ax::ui::TextField::create(); })
        .auto_wrap_objects(true);
    mod.class_("TextField", class_TextField);
}
static void js_register_ax_ui_TextBMFont(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::TextBMFont> class_TextBMFont(isolate);
    class_TextBMFont.ctor([]() { return new ax::ui::TextBMFont(); })
        .template inherit<ax::ui::Widget>()
        .member_function("setFntFile", &ax::ui::TextBMFont::setFntFile)
        .member_function("setString", &ax::ui::TextBMFont::setString)
        .member_function("getString", &ax::ui::TextBMFont::getString)
        .member_function("getStringLength", &ax::ui::TextBMFont::getStringLength)
        .member_function("getRenderFile", &ax::ui::TextBMFont::getRenderFile)
        .member_function("resetRender", &ax::ui::TextBMFont::resetRender)
        .static_function("createInstance", &ax::ui::TextBMFont::createInstance)
        .static_function(
            "create",
            [](std::string_view arg0, std::string_view arg1) { return ax::ui::TextBMFont::create(arg0, arg1); },
            []() { return ax::ui::TextBMFont::create(); })
        .auto_wrap_objects(true);
    mod.class_("TextBMFont", class_TextBMFont);
}
static void js_register_ax_ui_PageView(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::PageView> class_PageView(isolate);
    class_PageView.ctor([]() { return new ax::ui::PageView(); })
        .template inherit<ax::ui::ListView>()
        .member_function("addPage", &ax::ui::PageView::addPage)
        .member_function("insertPage", &ax::ui::PageView::insertPage)
        .member_function("removePage", &ax::ui::PageView::removePage)
        .member_function("removePageAtIndex", &ax::ui::PageView::removePageAtIndex)
        .member_function("removeAllPages", &ax::ui::PageView::removeAllPages)
        .member_function(
            "scrollToPage",
            [](ax::ui::PageView* self, ssize_t arg0, float arg1) { self->scrollToPage(arg0, arg1); },
            [](ax::ui::PageView* self, ssize_t arg0) { self->scrollToPage(arg0); })
        .member_function(
            "scrollToItem",
            [](ax::ui::PageView* self, ssize_t arg0, float arg1) { self->scrollToItem(arg0, arg1); },
            [](ax::ui::PageView* self, ssize_t arg0) { self->scrollToItem(arg0); })
        .member_function("getCurrentPageIndex", &ax::ui::PageView::getCurrentPageIndex)
        .member_function("setCurrentPageIndex", &ax::ui::PageView::setCurrentPageIndex)
        // .member_function("addEventListener", &ax::ui::PageView::addEventListener)
        .member_function("setIndicatorEnabled", &ax::ui::PageView::setIndicatorEnabled)
        .member_function("getIndicatorEnabled", &ax::ui::PageView::getIndicatorEnabled)
        .member_function("setIndicatorPositionAsAnchorPoint", &ax::ui::PageView::setIndicatorPositionAsAnchorPoint)
        .member_function("getIndicatorPositionAsAnchorPoint", &ax::ui::PageView::getIndicatorPositionAsAnchorPoint)
        .member_function("setIndicatorPosition", &ax::ui::PageView::setIndicatorPosition)
        .member_function("getIndicatorPosition", &ax::ui::PageView::getIndicatorPosition)
        .member_function("setIndicatorSpaceBetweenIndexNodes", &ax::ui::PageView::setIndicatorSpaceBetweenIndexNodes)
        .member_function("getIndicatorSpaceBetweenIndexNodes", &ax::ui::PageView::getIndicatorSpaceBetweenIndexNodes)
        .member_function("setIndicatorSelectedIndexColor", &ax::ui::PageView::setIndicatorSelectedIndexColor)
        .member_function("getIndicatorSelectedIndexColor", &ax::ui::PageView::getIndicatorSelectedIndexColor)
        .member_function("setIndicatorIndexNodesColor", &ax::ui::PageView::setIndicatorIndexNodesColor)
        .member_function("getIndicatorIndexNodesColor", &ax::ui::PageView::getIndicatorIndexNodesColor)
        .member_function("setIndicatorSelectedIndexOpacity", &ax::ui::PageView::setIndicatorSelectedIndexOpacity)
        .member_function("getIndicatorSelectedIndexOpacity", &ax::ui::PageView::getIndicatorSelectedIndexOpacity)
        .member_function("setIndicatorIndexNodesOpacity", &ax::ui::PageView::setIndicatorIndexNodesOpacity)
        .member_function("getIndicatorIndexNodesOpacity", &ax::ui::PageView::getIndicatorIndexNodesOpacity)
        .member_function("setIndicatorIndexNodesScale", &ax::ui::PageView::setIndicatorIndexNodesScale)
        .member_function(
            "setIndicatorIndexNodesTexture",
            [](ax::ui::PageView* self, std::string_view arg0) { self->setIndicatorIndexNodesTexture(arg0); },
            [](ax::ui::PageView* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->setIndicatorIndexNodesTexture(arg0, arg1); })
        .member_function("getIndicatorIndexNodesScale", &ax::ui::PageView::getIndicatorIndexNodesScale)
        .member_function("setAutoScrollStopEpsilon", &ax::ui::PageView::setAutoScrollStopEpsilon)
        .static_function("createInstance", &ax::ui::PageView::createInstance)
        .static_function("create", &ax::ui::PageView::create)
        .auto_wrap_objects(true);
    mod.class_("PageView", class_PageView);
}
static void js_register_ax_ui_Helper(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::Helper> class_Helper(isolate,
                                              [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_Helper.static_function("seekWidgetByTag", &ax::ui::Helper::seekWidgetByTag)
        .static_function("seekWidgetByName", &ax::ui::Helper::seekWidgetByName)
        .static_function("seekActionWidgetByActionTag", &ax::ui::Helper::seekActionWidgetByActionTag)
        .static_function("doLayout", &ax::ui::Helper::doLayout)
        .static_function("changeLayoutSystemActiveState", &ax::ui::Helper::changeLayoutSystemActiveState)
        .static_function("restrictCapInsetRect", &ax::ui::Helper::restrictCapInsetRect)
        .static_function("convertBoundingBoxToScreen", &ax::ui::Helper::convertBoundingBoxToScreen)
        .auto_wrap_objects(true);
    mod.class_("Helper", class_Helper);
}
static void js_register_ax_ui_RichElement(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RichElement> class_RichElement(isolate);
    class_RichElement.template inherit<ax::Object>()
        .member_function("init", &ax::ui::RichElement::init)
        .member_function("equalType", &ax::ui::RichElement::equalType)
        .member_function("setColor", &ax::ui::RichElement::setColor)
        .auto_wrap_objects(true);
    mod.class_("RichElement", class_RichElement);
}
static void js_register_ax_ui_RichElementText(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RichElementText> class_RichElementText(isolate);
    class_RichElementText.ctor([]() { return new ax::ui::RichElementText(); })
        .template inherit<ax::ui::RichElement>()
        .member_function(
            "init",
            [](ax::ui::RichElementText* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6); },
            [](ax::ui::RichElementText* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); },
            [](ax::ui::RichElementText* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); },
            [](ax::ui::RichElementText* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); },
            [](ax::ui::RichElementText* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9,
               ax::Vec2 arg10) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); },
            [](ax::ui::RichElementText* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9,
               ax::Vec2 arg10,
               int arg11) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11); },
            [](ax::ui::RichElementText* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9,
               ax::Vec2 arg10,
               int arg11,
               ax::Color32 arg12) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12); },
            [](ax::ui::RichElementText* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9,
               ax::Vec2 arg10,
               int arg11,
               ax::Color32 arg12,
               std::string_view arg13)
            { return self->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13); })
        .static_function(
            "create",
            [](int arg0, ax::Color32 arg1, std::string_view arg2, std::string_view arg3, float arg4)
            { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4); },
            [](int arg0, ax::Color32 arg1, std::string_view arg2, std::string_view arg3, float arg4, unsigned int arg5)
            { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6) { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7) { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8) { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9) { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9,
               ax::Vec2 arg10)
            { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9,
               ax::Vec2 arg10,
               int arg11)
            { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9,
               ax::Vec2 arg10,
               int arg11,
               ax::Color32 arg12)
            { return ax::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               float arg4,
               unsigned int arg5,
               std::string_view arg6,
               ax::Color32 arg7,
               int arg8,
               ax::Color32 arg9,
               ax::Vec2 arg10,
               int arg11,
               ax::Color32 arg12,
               std::string_view arg13)
            {
                return ax::ui::RichElementText::create(
                    arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
            })
        .auto_wrap_objects(true);
    mod.class_("RichElementText", class_RichElementText);
}
static void js_register_ax_ui_RichElementImage(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RichElementImage> class_RichElementImage(isolate);
    class_RichElementImage.ctor([]() { return new ax::ui::RichElementImage(); })
        .template inherit<ax::ui::RichElement>()
        .member_function(
            "init",
            [](ax::ui::RichElementImage* self, int arg0, ax::Color32 arg1, std::string_view arg2) { return self->init(arg0, arg1, arg2); },
            [](ax::ui::RichElementImage* self, int arg0, ax::Color32 arg1, std::string_view arg2, std::string_view arg3)
            { return self->init(arg0, arg1, arg2, arg3); },
            [](ax::ui::RichElementImage* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               ax::ui::Widget::TextureResType arg4) { return self->init(arg0, arg1, arg2, arg3, arg4); },
            [](ax::ui::RichElementImage* self,
               int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               ax::ui::Widget::TextureResType arg4,
               std::string_view arg5) { return self->init(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function("setWidth", &ax::ui::RichElementImage::setWidth)
        .member_function("setHeight", &ax::ui::RichElementImage::setHeight)
        .member_function("setScale", &ax::ui::RichElementImage::setScale)
        .member_function("setScaleX", &ax::ui::RichElementImage::setScaleX)
        .member_function("setScaleY", &ax::ui::RichElementImage::setScaleY)
        .member_function("setUrl", &ax::ui::RichElementImage::setUrl)
        .member_function("setId", &ax::ui::RichElementImage::setId)
        .static_function(
            "create",
            [](int arg0, ax::Color32 arg1, std::string_view arg2) { return ax::ui::RichElementImage::create(arg0, arg1, arg2); },
            [](int arg0, ax::Color32 arg1, std::string_view arg2, std::string_view arg3)
            { return ax::ui::RichElementImage::create(arg0, arg1, arg2, arg3); },
            [](int arg0, ax::Color32 arg1, std::string_view arg2, std::string_view arg3, ax::ui::Widget::TextureResType arg4)
            { return ax::ui::RichElementImage::create(arg0, arg1, arg2, arg3, arg4); },
            [](int arg0,
               ax::Color32 arg1,
               std::string_view arg2,
               std::string_view arg3,
               ax::ui::Widget::TextureResType arg4,
               std::string_view arg5) { return ax::ui::RichElementImage::create(arg0, arg1, arg2, arg3, arg4, arg5); })
        .auto_wrap_objects(true);
    mod.class_("RichElementImage", class_RichElementImage);
}
static void js_register_ax_ui_RichElementCustomNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RichElementCustomNode> class_RichElementCustomNode(isolate);
    class_RichElementCustomNode.ctor([]() { return new ax::ui::RichElementCustomNode(); })
        .template inherit<ax::ui::RichElement>()
        .member_function(
            "init",
            [](ax::ui::RichElementCustomNode* self, int arg0, ax::Color32 arg1, ax::Node* arg2) { return self->init(arg0, arg1, arg2); },
            [](ax::ui::RichElementCustomNode* self, int arg0, ax::Color32 arg1, ax::Node* arg2, std::string_view arg3)
            { return self->init(arg0, arg1, arg2, arg3); })
        .static_function(
            "create",
            [](int arg0, ax::Color32 arg1, ax::Node* arg2) { return ax::ui::RichElementCustomNode::create(arg0, arg1, arg2); },
            [](int arg0, ax::Color32 arg1, ax::Node* arg2, std::string_view arg3)
            { return ax::ui::RichElementCustomNode::create(arg0, arg1, arg2, arg3); })
        .auto_wrap_objects(true);
    mod.class_("RichElementCustomNode", class_RichElementCustomNode);
}
static void js_register_ax_ui_RichElementNewLine(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RichElementNewLine> class_RichElementNewLine(isolate);
    class_RichElementNewLine
        .ctor([]() { return new ax::ui::RichElementNewLine(); }, [](int arg0) { return new ax::ui::RichElementNewLine(arg0); })
        .template inherit<ax::ui::RichElement>()
        .static_function(
            "create",
            [](int arg0, int arg1, ax::Color32 arg2) { return ax::ui::RichElementNewLine::create(arg0, arg1, arg2); },
            [](int arg0, ax::Color32 arg1) { return ax::ui::RichElementNewLine::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("RichElementNewLine", class_RichElementNewLine);
}
static void js_register_ax_ui_RichText(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RichText> class_RichText(isolate);
    class_RichText.ctor([]() { return new ax::ui::RichText(); })
        .template inherit<ax::ui::Widget>()
        .member_function("insertElement", &ax::ui::RichText::insertElement)
        .member_function("pushBackElement", &ax::ui::RichText::pushBackElement)
        .member_function(
            "removeElement",
            [](ax::ui::RichText* self, ax::ui::RichElement* arg0) { self->removeElement(arg0); },
            [](ax::ui::RichText* self, int arg0) { self->removeElement(arg0); })
        .member_function("setVerticalSpace", &ax::ui::RichText::setVerticalSpace)
        .member_function(
            "formatText",
            [](ax::ui::RichText* self) { self->formatText(); },
            [](ax::ui::RichText* self, bool arg0) { self->formatText(arg0); })
        .member_function("setWrapMode", &ax::ui::RichText::setWrapMode)
        .member_function("getWrapMode", &ax::ui::RichText::getWrapMode)
        .member_function("setHorizontalAlignment", &ax::ui::RichText::setHorizontalAlignment)
        .member_function("getHorizontalAlignment", &ax::ui::RichText::getHorizontalAlignment)
        .member_function("setVerticalAlignment", &ax::ui::RichText::setVerticalAlignment)
        .member_function("getVerticalAlignment", &ax::ui::RichText::getVerticalAlignment)
        .member_function("setFontColor", &ax::ui::RichText::setFontColor)
        .member_function("getFontColor", &ax::ui::RichText::getFontColor)
        .member_function("getFontColor32", &ax::ui::RichText::getFontColor32)
        .member_function("setFontSize", &ax::ui::RichText::setFontSize)
        .member_function("getFontSize", &ax::ui::RichText::getFontSize)
        .member_function("setFontFace", &ax::ui::RichText::setFontFace)
        .member_function("getFontFace", &ax::ui::RichText::getFontFace)
        .member_function("setAnchorFontColor", &ax::ui::RichText::setAnchorFontColor)
        .member_function("getAnchorFontColor", &ax::ui::RichText::getAnchorFontColor)
        .member_function("getAnchorFontColor32", &ax::ui::RichText::getAnchorFontColor32)
        .member_function("setAnchorTextBold", &ax::ui::RichText::setAnchorTextBold)
        .member_function("isAnchorTextBoldEnabled", &ax::ui::RichText::isAnchorTextBoldEnabled)
        .member_function("setAnchorTextItalic", &ax::ui::RichText::setAnchorTextItalic)
        .member_function("isAnchorTextItalicEnabled", &ax::ui::RichText::isAnchorTextItalicEnabled)
        .member_function("setAnchorTextDel", &ax::ui::RichText::setAnchorTextDel)
        .member_function("isAnchorTextDelEnabled", &ax::ui::RichText::isAnchorTextDelEnabled)
        .member_function("setAnchorTextUnderline", &ax::ui::RichText::setAnchorTextUnderline)
        .member_function("isAnchorTextUnderlineEnabled", &ax::ui::RichText::isAnchorTextUnderlineEnabled)
        .member_function(
            "setAnchorTextOutline",
            [](ax::ui::RichText* self, bool arg0) { self->setAnchorTextOutline(arg0); },
            [](ax::ui::RichText* self, bool arg0, ax::Color32 arg1) { self->setAnchorTextOutline(arg0, arg1); },
            [](ax::ui::RichText* self, bool arg0, ax::Color32 arg1, int arg2) { self->setAnchorTextOutline(arg0, arg1, arg2); })
        .member_function("isAnchorTextOutlineEnabled", &ax::ui::RichText::isAnchorTextOutlineEnabled)
        .member_function("getAnchorTextOutlineColor32", &ax::ui::RichText::getAnchorTextOutlineColor32)
        .member_function("getAnchorTextOutlineSize", &ax::ui::RichText::getAnchorTextOutlineSize)
        .member_function(
            "setAnchorTextShadow",
            [](ax::ui::RichText* self, bool arg0) { self->setAnchorTextShadow(arg0); },
            [](ax::ui::RichText* self, bool arg0, ax::Color32 arg1) { self->setAnchorTextShadow(arg0, arg1); },
            [](ax::ui::RichText* self, bool arg0, ax::Color32 arg1, ax::Vec2 arg2) { self->setAnchorTextShadow(arg0, arg1, arg2); },
            [](ax::ui::RichText* self, bool arg0, ax::Color32 arg1, ax::Vec2 arg2, int arg3)
            { self->setAnchorTextShadow(arg0, arg1, arg2, arg3); })
        .member_function("isAnchorTextShadowEnabled", &ax::ui::RichText::isAnchorTextShadowEnabled)
        .member_function("getAnchorTextShadowColor32", &ax::ui::RichText::getAnchorTextShadowColor32)
        .member_function("getAnchorTextShadowOffset", &ax::ui::RichText::getAnchorTextShadowOffset)
        .member_function("getAnchorTextShadowBlurRadius", &ax::ui::RichText::getAnchorTextShadowBlurRadius)
        .member_function(
            "setAnchorTextGlow",
            [](ax::ui::RichText* self, bool arg0) { self->setAnchorTextGlow(arg0); },
            [](ax::ui::RichText* self, bool arg0, ax::Color32 arg1) { self->setAnchorTextGlow(arg0, arg1); })
        .member_function("isAnchorTextGlowEnabled", &ax::ui::RichText::isAnchorTextGlowEnabled)
        .member_function("getAnchorTextGlowColor32", &ax::ui::RichText::getAnchorTextGlowColor32)
        .member_function("setDefaults", &ax::ui::RichText::setDefaults)
        .member_function("getDefaults", &ax::ui::RichText::getDefaults)
        .member_function("openUrl", &ax::ui::RichText::openUrl)
        .member_function(
            "initWithXML",
            [](ax::ui::RichText* self, std::string_view arg0, ax::ValueMap arg1) { return self->initWithXML(arg0, arg1); },
            [](ax::ui::RichText* self, std::string_view arg0, ax::ValueMap arg1, std::function<void(std::string_view)> arg2)
            { return self->initWithXML(arg0, arg1, arg2); })
        .member_function("setString", &ax::ui::RichText::setString)
        .static_function("create", &ax::ui::RichText::create)
        .static_function(
            "createWithXML",
            [](std::string_view arg0, ax::ValueMap arg1) { return ax::ui::RichText::createWithXML(arg0, arg1); },
            [](std::string_view arg0, ax::ValueMap arg1, std::function<void(std::string_view)> arg2)
            { return ax::ui::RichText::createWithXML(arg0, arg1, arg2); })
        .static_function("parseColor32", &ax::ui::RichText::parseColor32)
        .static_function("formatColor32", &ax::ui::RichText::formatColor32)
        .auto_wrap_objects(true);
    mod.class_("RichText", class_RichText);
}
static void js_register_ax_ui_HBox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::HBox> class_HBox(isolate);
    class_HBox.ctor([]() { return new ax::ui::HBox(); })
        .template inherit<ax::ui::Layout>()
        .member_function("initWithSize", &ax::ui::HBox::initWithSize)
        .static_function(
            "create", [](ax::Vec2 arg0) { return ax::ui::HBox::create(arg0); }, []() { return ax::ui::HBox::create(); })
        .auto_wrap_objects(true);
    mod.class_("HBox", class_HBox);
}
static void js_register_ax_ui_VBox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::VBox> class_VBox(isolate);
    class_VBox.ctor([]() { return new ax::ui::VBox(); })
        .template inherit<ax::ui::Layout>()
        .member_function("initWithSize", &ax::ui::VBox::initWithSize)
        .static_function(
            "create", [](ax::Vec2 arg0) { return ax::ui::VBox::create(arg0); }, []() { return ax::ui::VBox::create(); })
        .auto_wrap_objects(true);
    mod.class_("VBox", class_VBox);
}
static void js_register_ax_ui_RelativeBox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::RelativeBox> class_RelativeBox(isolate);
    class_RelativeBox.ctor([]() { return new ax::ui::RelativeBox(); })
        .template inherit<ax::ui::Layout>()
        .member_function("initWithSize", &ax::ui::RelativeBox::initWithSize)
        .static_function(
            "create", [](ax::Vec2 arg0) { return ax::ui::RelativeBox::create(arg0); }, []() { return ax::ui::RelativeBox::create(); })
        .auto_wrap_objects(true);
    mod.class_("RelativeBox", class_RelativeBox);
}
static void js_register_ax_ui_Scale9Sprite(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::Scale9Sprite> class_Scale9Sprite(isolate);
    class_Scale9Sprite.ctor([]() { return new ax::ui::Scale9Sprite(); })
        .template inherit<ax::Sprite>()
        .member_function(
            "initWithFile",
            [](ax::ui::Scale9Sprite* self, ax::Rect arg0, std::string_view arg1) { return self->initWithFile(arg0, arg1); },
            [](ax::ui::Scale9Sprite* self, std::string_view arg0, ax::Rect arg1, ax::Rect arg2)
            { return self->initWithFile(arg0, arg1, arg2); })
        // .member_function("initWithSpriteFrame", &ax::ui::Scale9Sprite::initWithSpriteFrame)
        // .member_function("initWithSpriteFrameName", &ax::ui::Scale9Sprite::initWithSpriteFrameName)
        .member_function(
            "init",
            [](ax::ui::Scale9Sprite* self, ax::Sprite* arg0, ax::Rect arg1, ax::Rect arg2) { return self->init(arg0, arg1, arg2); },
            [](ax::ui::Scale9Sprite* self, ax::Sprite* arg0, ax::Rect arg1, bool arg2, ax::Rect arg3)
            { return self->init(arg0, arg1, arg2, arg3); },
            [](ax::ui::Scale9Sprite* self, ax::Sprite* arg0, ax::Rect arg1, bool arg2, ax::Vec2 arg3, ax::Vec2 arg4, ax::Rect arg5)
            { return self->init(arg0, arg1, arg2, arg3, arg4, arg5); })
        .member_function("resizableSpriteWithCapInsets", &ax::ui::Scale9Sprite::resizableSpriteWithCapInsets)
        .member_function(
            "updateWithSprite",
            [](ax::ui::Scale9Sprite* self, ax::Sprite* arg0, ax::Rect arg1, bool arg2, ax::Vec2 arg3, ax::Vec2 arg4, ax::Rect arg5)
            { return self->updateWithSprite(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](ax::ui::Scale9Sprite* self, ax::Sprite* arg0, ax::Rect arg1, bool arg2, ax::Rect arg3)
            { return self->updateWithSprite(arg0, arg1, arg2, arg3); })
        // .member_function("setSpriteFrame", &ax::ui::Scale9Sprite::setSpriteFrame)
        .member_function("setState", &ax::ui::Scale9Sprite::setState)
        .member_function("getState", &ax::ui::Scale9Sprite::getState)
        .member_function("getOriginalSize", &ax::ui::Scale9Sprite::getOriginalSize)
        .member_function("setPreferredSize", &ax::ui::Scale9Sprite::setPreferredSize)
        .member_function("getPreferredSize", &ax::ui::Scale9Sprite::getPreferredSize)
        .member_function("setInsetLeft", &ax::ui::Scale9Sprite::setInsetLeft)
        .member_function("getInsetLeft", &ax::ui::Scale9Sprite::getInsetLeft)
        .member_function("setInsetTop", &ax::ui::Scale9Sprite::setInsetTop)
        .member_function("getInsetTop", &ax::ui::Scale9Sprite::getInsetTop)
        .member_function("setInsetRight", &ax::ui::Scale9Sprite::setInsetRight)
        .member_function("getInsetRight", &ax::ui::Scale9Sprite::getInsetRight)
        .member_function("setInsetBottom", &ax::ui::Scale9Sprite::setInsetBottom)
        .member_function("getInsetBottom", &ax::ui::Scale9Sprite::getInsetBottom)
        .member_function("setScale9Enabled", &ax::ui::Scale9Sprite::setScale9Enabled)
        .member_function("isScale9Enabled", &ax::ui::Scale9Sprite::isScale9Enabled)
        .member_function("getSprite", &ax::ui::Scale9Sprite::getSprite)
        .member_function("copyTo", &ax::ui::Scale9Sprite::copyTo)
        .member_function("setRenderingType", &ax::ui::Scale9Sprite::setRenderingType)
        .member_function("getRenderingType", &ax::ui::Scale9Sprite::getRenderingType)
        .member_function("setCapInsets", &ax::ui::Scale9Sprite::setCapInsets)
        .member_function("getCapInsets", &ax::ui::Scale9Sprite::getCapInsets)
        .member_function("resetRender", &ax::ui::Scale9Sprite::resetRender)
        .static_function(
            "create",
            [](std::string_view arg0, ax::Rect arg1, ax::Rect arg2) { return ax::ui::Scale9Sprite::create(arg0, arg1, arg2); },
            []() { return ax::ui::Scale9Sprite::create(); },
            [](ax::Rect arg0, std::string_view arg1) { return ax::ui::Scale9Sprite::create(arg0, arg1); },
            [](std::string_view arg0, ax::Rect arg1) { return ax::ui::Scale9Sprite::create(arg0, arg1); },
            [](std::string_view arg0) { return ax::ui::Scale9Sprite::create(arg0); })
        .static_function(
            "createWithSpriteFrame",
            [](ax::SpriteFrame* arg0, ax::Rect arg1) { return ax::ui::Scale9Sprite::createWithSpriteFrame(arg0, arg1); },
            [](ax::SpriteFrame* arg0) { return ax::ui::Scale9Sprite::createWithSpriteFrame(arg0); })
        .static_function(
            "createWithSpriteFrameName",
            [](std::string_view arg0, ax::Rect arg1) { return ax::ui::Scale9Sprite::createWithSpriteFrameName(arg0, arg1); },
            [](std::string_view arg0) { return ax::ui::Scale9Sprite::createWithSpriteFrameName(arg0); })
        .auto_wrap_objects(true);
    mod.class_("Scale9Sprite", class_Scale9Sprite);
}
static void js_register_ax_ui_EditBox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::EditBox> class_EditBox(isolate);
    class_EditBox.ctor([]() { return new ax::ui::EditBox(); })
        .template inherit<ax::ui::Widget>()
        .member_function(
            "initWithSizeAndBackgroundSprite",
            [](ax::ui::EditBox* self, ax::Size arg0, ax::ui::Scale9Sprite* arg1)
            { return self->initWithSizeAndBackgroundSprite(arg0, arg1); },
            [](ax::ui::EditBox* self, ax::Size arg0, std::string_view arg1) { return self->initWithSizeAndBackgroundSprite(arg0, arg1); },
            [](ax::ui::EditBox* self, ax::Size arg0, std::string_view arg1, ax::ui::Widget::TextureResType arg2)
            { return self->initWithSizeAndBackgroundSprite(arg0, arg1, arg2); },
            [](ax::ui::EditBox* self, ax::Size arg0, ax::ui::Scale9Sprite* arg1, ax::ui::Scale9Sprite* arg2, ax::ui::Scale9Sprite* arg3)
            { return self->initWithSizeAndBackgroundSprite(arg0, arg1, arg2, arg3); })
        .member_function(
            "initWithSizeAndTexture",
            [](ax::ui::EditBox* self, ax::Size arg0, std::string_view arg1) { return self->initWithSizeAndTexture(arg0, arg1); },
            [](ax::ui::EditBox* self, ax::Size arg0, std::string_view arg1, std::string_view arg2)
            { return self->initWithSizeAndTexture(arg0, arg1, arg2); },
            [](ax::ui::EditBox* self, ax::Size arg0, std::string_view arg1, std::string_view arg2, std::string_view arg3)
            { return self->initWithSizeAndTexture(arg0, arg1, arg2, arg3); },
            [](ax::ui::EditBox* self,
               ax::Size arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               ax::ui::Widget::TextureResType arg4) { return self->initWithSizeAndTexture(arg0, arg1, arg2, arg3, arg4); })
        .member_function(
            "loadTextures",
            [](ax::ui::EditBox* self, std::string_view arg0, std::string_view arg1) { self->loadTextures(arg0, arg1); },
            [](ax::ui::EditBox* self, std::string_view arg0, std::string_view arg1, std::string_view arg2)
            { self->loadTextures(arg0, arg1, arg2); },
            [](ax::ui::EditBox* self,
               std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               ax::ui::Widget::TextureResType arg3) { self->loadTextures(arg0, arg1, arg2, arg3); })
        .member_function(
            "loadTextureNormal",
            [](ax::ui::EditBox* self, std::string_view arg0) { self->loadTextureNormal(arg0); },
            [](ax::ui::EditBox* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->loadTextureNormal(arg0, arg1); })
        .member_function(
            "loadTexturePressed",
            [](ax::ui::EditBox* self, std::string_view arg0) { self->loadTexturePressed(arg0); },
            [](ax::ui::EditBox* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1) { self->loadTexturePressed(arg0, arg1); })
        .member_function(
            "loadTextureDisabled",
            [](ax::ui::EditBox* self, std::string_view arg0) { self->loadTextureDisabled(arg0); },
            [](ax::ui::EditBox* self, std::string_view arg0, ax::ui::Widget::TextureResType arg1)
            { self->loadTextureDisabled(arg0, arg1); })
        .member_function("setCapInsets", &ax::ui::EditBox::setCapInsets)
        .member_function("setCapInsetsNormalRenderer", &ax::ui::EditBox::setCapInsetsNormalRenderer)
        .member_function("getCapInsetsNormalRenderer", &ax::ui::EditBox::getCapInsetsNormalRenderer)
        .member_function("setCapInsetsPressedRenderer", &ax::ui::EditBox::setCapInsetsPressedRenderer)
        .member_function("getCapInsetsPressedRenderer", &ax::ui::EditBox::getCapInsetsPressedRenderer)
        .member_function("setCapInsetsDisabledRenderer", &ax::ui::EditBox::setCapInsetsDisabledRenderer)
        .member_function("getCapInsetsDisabledRenderer", &ax::ui::EditBox::getCapInsetsDisabledRenderer)
        .member_function("registerScriptEditBoxHandler", &ax::ui::EditBox::registerScriptEditBoxHandler)
        .member_function("unregisterScriptEditBoxHandler", &ax::ui::EditBox::unregisterScriptEditBoxHandler)
        .member_function("getScriptEditBoxHandler", &ax::ui::EditBox::getScriptEditBoxHandler)
        .member_function("setText", &ax::ui::EditBox::setText)
        .member_function("getText", &ax::ui::EditBox::getText)
        .member_function("setFont", &ax::ui::EditBox::setFont)
        .member_function("setFontName", &ax::ui::EditBox::setFontName)
        .member_function("getFontName", &ax::ui::EditBox::getFontName)
        .member_function("setFontSize", &ax::ui::EditBox::setFontSize)
        .member_function("getFontSize", &ax::ui::EditBox::getFontSize)
        .member_function("setFontColor", &ax::ui::EditBox::setFontColor)
        .member_function("getFontColor", &ax::ui::EditBox::getFontColor)
        .member_function("setPlaceholderFont", &ax::ui::EditBox::setPlaceholderFont)
        .member_function("setPlaceholderFontName", &ax::ui::EditBox::setPlaceholderFontName)
        .member_function("getPlaceholderFontName", &ax::ui::EditBox::getPlaceholderFontName)
        .member_function("setPlaceholderFontSize", &ax::ui::EditBox::setPlaceholderFontSize)
        .member_function("getPlaceholderFontSize", &ax::ui::EditBox::getPlaceholderFontSize)
        .member_function("setPlaceholderFontColor", &ax::ui::EditBox::setPlaceholderFontColor)
        .member_function("getPlaceholderFontColor", &ax::ui::EditBox::getPlaceholderFontColor)
        .member_function("setPlaceHolder", &ax::ui::EditBox::setPlaceHolder)
        .member_function("getPlaceHolder", &ax::ui::EditBox::getPlaceHolder)
        .member_function("setInputMode", &ax::ui::EditBox::setInputMode)
        .member_function("getInputMode", &ax::ui::EditBox::getInputMode)
        .member_function("setMaxLength", &ax::ui::EditBox::setMaxLength)
        .member_function("getMaxLength", &ax::ui::EditBox::getMaxLength)
        .member_function("setInputFlag", &ax::ui::EditBox::setInputFlag)
        .member_function("getInputFlag", &ax::ui::EditBox::getInputFlag)
        .member_function("setReturnType", &ax::ui::EditBox::setReturnType)
        .member_function("getReturnType", &ax::ui::EditBox::getReturnType)
        .member_function("setTextHorizontalAlignment", &ax::ui::EditBox::setTextHorizontalAlignment)
        .member_function("getTextHorizontalAlignment", &ax::ui::EditBox::getTextHorizontalAlignment)
        .member_function("openKeyboard", &ax::ui::EditBox::openKeyboard)
        .member_function("closeKeyboard", &ax::ui::EditBox::closeKeyboard)
        .static_function(
            "create",
            [](ax::Size arg0, std::string_view arg1, ax::ui::Widget::TextureResType arg2)
            { return ax::ui::EditBox::create(arg0, arg1, arg2); },
            [](ax::Size arg0, ax::ui::Scale9Sprite* arg1) { return ax::ui::EditBox::create(arg0, arg1); },
            [](ax::Size arg0, ax::ui::Scale9Sprite* arg1, ax::ui::Scale9Sprite* arg2) { return ax::ui::EditBox::create(arg0, arg1, arg2); },
            [](ax::Size arg0, ax::ui::Scale9Sprite* arg1, ax::ui::Scale9Sprite* arg2, ax::ui::Scale9Sprite* arg3)
            { return ax::ui::EditBox::create(arg0, arg1, arg2, arg3); },
            [](ax::Size arg0, std::string_view arg1) { return ax::ui::EditBox::create(arg0, arg1); },
            [](ax::Size arg0, std::string_view arg1, std::string_view arg2) { return ax::ui::EditBox::create(arg0, arg1, arg2); },
            [](ax::Size arg0, std::string_view arg1, std::string_view arg2, std::string_view arg3)
            { return ax::ui::EditBox::create(arg0, arg1, arg2, arg3); },
            [](ax::Size arg0, std::string_view arg1, std::string_view arg2, std::string_view arg3, ax::ui::Widget::TextureResType arg4)
            { return ax::ui::EditBox::create(arg0, arg1, arg2, arg3, arg4); })
        .auto_wrap_objects(true);
    mod.class_("EditBox", class_EditBox);
}
static void js_register_ax_ui_LayoutComponent(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::LayoutComponent> class_LayoutComponent(isolate);
    class_LayoutComponent.ctor([]() { return new ax::ui::LayoutComponent(); })
        .template inherit<ax::Component>()
        .member_function("setUsingPercentContentSize", &ax::ui::LayoutComponent::setUsingPercentContentSize)
        .member_function("getUsingPercentContentSize", &ax::ui::LayoutComponent::getUsingPercentContentSize)
        .member_function("setPercentContentSize", &ax::ui::LayoutComponent::setPercentContentSize)
        .member_function("getPercentContentSize", &ax::ui::LayoutComponent::getPercentContentSize)
        .member_function("getAnchorPosition", &ax::ui::LayoutComponent::getAnchorPosition)
        .member_function("setAnchorPosition", &ax::ui::LayoutComponent::setAnchorPosition)
        .member_function("getPosition", &ax::ui::LayoutComponent::getPosition)
        .member_function("setPosition", &ax::ui::LayoutComponent::setPosition)
        .member_function("isPositionPercentXEnabled", &ax::ui::LayoutComponent::isPositionPercentXEnabled)
        .member_function("setPositionPercentXEnabled", &ax::ui::LayoutComponent::setPositionPercentXEnabled)
        .member_function("getPositionPercentX", &ax::ui::LayoutComponent::getPositionPercentX)
        .member_function("setPositionPercentX", &ax::ui::LayoutComponent::setPositionPercentX)
        .member_function("isPositionPercentYEnabled", &ax::ui::LayoutComponent::isPositionPercentYEnabled)
        .member_function("setPositionPercentYEnabled", &ax::ui::LayoutComponent::setPositionPercentYEnabled)
        .member_function("getPositionPercentY", &ax::ui::LayoutComponent::getPositionPercentY)
        .member_function("setPositionPercentY", &ax::ui::LayoutComponent::setPositionPercentY)
        .member_function("getHorizontalEdge", &ax::ui::LayoutComponent::getHorizontalEdge)
        .member_function("setHorizontalEdge", &ax::ui::LayoutComponent::setHorizontalEdge)
        .member_function("getVerticalEdge", &ax::ui::LayoutComponent::getVerticalEdge)
        .member_function("setVerticalEdge", &ax::ui::LayoutComponent::setVerticalEdge)
        .member_function("getLeftMargin", &ax::ui::LayoutComponent::getLeftMargin)
        .member_function("setLeftMargin", &ax::ui::LayoutComponent::setLeftMargin)
        .member_function("getRightMargin", &ax::ui::LayoutComponent::getRightMargin)
        .member_function("setRightMargin", &ax::ui::LayoutComponent::setRightMargin)
        .member_function("getTopMargin", &ax::ui::LayoutComponent::getTopMargin)
        .member_function("setTopMargin", &ax::ui::LayoutComponent::setTopMargin)
        .member_function("getBottomMargin", &ax::ui::LayoutComponent::getBottomMargin)
        .member_function("setBottomMargin", &ax::ui::LayoutComponent::setBottomMargin)
        .member_function("getSize", &ax::ui::LayoutComponent::getSize)
        .member_function("setSize", &ax::ui::LayoutComponent::setSize)
        .member_function("isPercentWidthEnabled", &ax::ui::LayoutComponent::isPercentWidthEnabled)
        .member_function("setPercentWidthEnabled", &ax::ui::LayoutComponent::setPercentWidthEnabled)
        .member_function("getSizeWidth", &ax::ui::LayoutComponent::getSizeWidth)
        .member_function("setSizeWidth", &ax::ui::LayoutComponent::setSizeWidth)
        .member_function("getPercentWidth", &ax::ui::LayoutComponent::getPercentWidth)
        .member_function("setPercentWidth", &ax::ui::LayoutComponent::setPercentWidth)
        .member_function("isPercentHeightEnabled", &ax::ui::LayoutComponent::isPercentHeightEnabled)
        .member_function("setPercentHeightEnabled", &ax::ui::LayoutComponent::setPercentHeightEnabled)
        .member_function("getSizeHeight", &ax::ui::LayoutComponent::getSizeHeight)
        .member_function("setSizeHeight", &ax::ui::LayoutComponent::setSizeHeight)
        .member_function("getPercentHeight", &ax::ui::LayoutComponent::getPercentHeight)
        .member_function("setPercentHeight", &ax::ui::LayoutComponent::setPercentHeight)
        .member_function("isStretchWidthEnabled", &ax::ui::LayoutComponent::isStretchWidthEnabled)
        .member_function("setStretchWidthEnabled", &ax::ui::LayoutComponent::setStretchWidthEnabled)
        .member_function("isStretchHeightEnabled", &ax::ui::LayoutComponent::isStretchHeightEnabled)
        .member_function("setStretchHeightEnabled", &ax::ui::LayoutComponent::setStretchHeightEnabled)
        .member_function("setPercentOnlyEnabled", &ax::ui::LayoutComponent::setPercentOnlyEnabled)
        .member_function("setActiveEnabled", &ax::ui::LayoutComponent::setActiveEnabled)
        .member_function("refreshLayout", &ax::ui::LayoutComponent::refreshLayout)
        .static_function("create", &ax::ui::LayoutComponent::create)
        .static_function("bindLayoutComponent", &ax::ui::LayoutComponent::bindLayoutComponent)
        .auto_wrap_objects(true);
    mod.class_("LayoutComponent", class_LayoutComponent);
}
static void js_register_ax_ui_TabHeader(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::TabHeader> class_TabHeader(isolate);
    class_TabHeader.template inherit<ax::ui::AbstractCheckButton>()
        .member_function("getTitleRenderer", &ax::ui::TabHeader::getTitleRenderer)
        .member_function("setTitleText", &ax::ui::TabHeader::setTitleText)
        .member_function("getTitleText", &ax::ui::TabHeader::getTitleText)
        .member_function("setTitleColor", &ax::ui::TabHeader::setTitleColor)
        .member_function("getTitleColor", &ax::ui::TabHeader::getTitleColor)
        .member_function("setTitleFontSize", &ax::ui::TabHeader::setTitleFontSize)
        .member_function("getTitleFontSize", &ax::ui::TabHeader::getTitleFontSize)
        .member_function("setTitleFontName", &ax::ui::TabHeader::setTitleFontName)
        .member_function("getTitleFontName", &ax::ui::TabHeader::getTitleFontName)
        .member_function("getIndexInTabControl", &ax::ui::TabHeader::getIndexInTabControl)
        .static_function(
            "create",
            [](std::string_view arg0, std::string_view arg1, std::string_view arg2) { return ax::ui::TabHeader::create(arg0, arg1, arg2); },
            [](std::string_view arg0, std::string_view arg1, std::string_view arg2, ax::ui::Widget::TextureResType arg3)
            { return ax::ui::TabHeader::create(arg0, arg1, arg2, arg3); },
            []() { return ax::ui::TabHeader::create(); },
            [](std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4,
               std::string_view arg5) { return ax::ui::TabHeader::create(arg0, arg1, arg2, arg3, arg4, arg5); },
            [](std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4,
               std::string_view arg5,
               ax::ui::Widget::TextureResType arg6) { return ax::ui::TabHeader::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6); })
        .auto_wrap_objects(true);
    mod.class_("TabHeader", class_TabHeader);
}
static void js_register_ax_ui_TabControl(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::ui::TabControl> class_TabControl(isolate);
    class_TabControl.template inherit<ax::ui::Widget>()
        .member_function("removeTab", &ax::ui::TabControl::removeTab)
        .member_function(
            "setSelectTab",
            [](ax::ui::TabControl* self, ax::ui::TabHeader* arg0) { self->setSelectTab(arg0); },
            [](ax::ui::TabControl* self, int arg0) { self->setSelectTab(arg0); })
        .member_function("getTabHeader", &ax::ui::TabControl::getTabHeader)
        .member_function("getTabContainer", &ax::ui::TabControl::getTabContainer)
        .member_function("insertTab", &ax::ui::TabControl::insertTab)
        .member_function("getTabCount", &ax::ui::TabControl::getTabCount)
        .member_function("getSelectedTabIndex", &ax::ui::TabControl::getSelectedTabIndex)
        .member_function("indexOfTabHeader", &ax::ui::TabControl::indexOfTabHeader)
        .member_function("setTabChangedEventListener", &ax::ui::TabControl::setTabChangedEventListener)
        .member_function("setHeaderWidth", &ax::ui::TabControl::setHeaderWidth)
        .member_function("getHeaderWidth", &ax::ui::TabControl::getHeaderWidth)
        .member_function("setHeaderHeight", &ax::ui::TabControl::setHeaderHeight)
        .member_function("getHeaderHeight", &ax::ui::TabControl::getHeaderHeight)
        .member_function("ignoreHeadersTextureSize", &ax::ui::TabControl::ignoreHeadersTextureSize)
        .member_function("isIgnoreHeadersTextureSize", &ax::ui::TabControl::isIgnoreHeadersTextureSize)
        .member_function("setHeaderSelectedZoom", &ax::ui::TabControl::setHeaderSelectedZoom)
        .member_function("getHeaderSelectedZoom", &ax::ui::TabControl::getHeaderSelectedZoom)
        .member_function("setHeaderDockPlace", &ax::ui::TabControl::setHeaderDockPlace)
        .member_function("getHeaderDockPlace", &ax::ui::TabControl::getHeaderDockPlace)
        .static_function("create", &ax::ui::TabControl::create)
        .auto_wrap_objects(true);
    mod.class_("TabControl", class_TabControl);
}
void js_register_all_ax_ui(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("axui");
    js_register_ax_ui_LayoutParameter(mod);
    js_register_ax_ui_LinearLayoutParameter(mod);
    js_register_ax_ui_RelativeLayoutParameter(mod);
    js_register_ax_ui_Widget(mod);
    js_register_ax_ui_Layout(mod);
    js_register_ax_ui_Button(mod);
    js_register_ax_ui_AbstractCheckButton(mod);
    js_register_ax_ui_CheckBox(mod);
    js_register_ax_ui_RadioButton(mod);
    js_register_ax_ui_RadioButtonGroup(mod);
    js_register_ax_ui_ImageView(mod);
    js_register_ax_ui_Text(mod);
    js_register_ax_ui_TextAtlas(mod);
    js_register_ax_ui_LoadingBar(mod);
    js_register_ax_ui_ScrollView(mod);
    js_register_ax_ui_ListView(mod);
    js_register_ax_ui_Slider(mod);
    js_register_ax_ui_TextField(mod);
    js_register_ax_ui_TextBMFont(mod);
    js_register_ax_ui_PageView(mod);
    js_register_ax_ui_Helper(mod);
    js_register_ax_ui_RichElement(mod);
    js_register_ax_ui_RichElementText(mod);
    js_register_ax_ui_RichElementImage(mod);
    js_register_ax_ui_RichElementCustomNode(mod);
    js_register_ax_ui_RichElementNewLine(mod);
    js_register_ax_ui_RichText(mod);
    js_register_ax_ui_HBox(mod);
    js_register_ax_ui_VBox(mod);
    js_register_ax_ui_RelativeBox(mod);
    js_register_ax_ui_Scale9Sprite(mod);
    js_register_ax_ui_EditBox(mod);
    js_register_ax_ui_LayoutComponent(mod);
    js_register_ax_ui_TabHeader(mod);
    js_register_ax_ui_TabControl(mod);
}
