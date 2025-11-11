(function (window) {
  var message = "";
  var appendMessage = function (tail) {
    message += "\n" + tail;
    cc.log(tail);
  };
  var ScrollViewExtended = class extends ccui.ScrollView {
    onEnter() {
      super.onEnter();
      appendMessage("3. ScrollViewExtended: onEnter");
    }
    onExit() {
      appendMessage("E-3. ScrollViewExtended: onExit");
      super.onExit();
    }
  };
  var ButtonExtended = class extends ccui.Button {
    onEnter() {
      super.onEnter();
      appendMessage("4. ButtonExtended: onEnter");
    }
    onExit() {
      appendMessage("E-4. ButtonExtended: onExit");
      super.onExit();
    }
  };
  var ImageViewExtended = class extends ccui.ImageView {
    onEnter() {
      super.onEnter();
      appendMessage("5. ImageViewExtended: onEnter");
    }
    onExit() {
      appendMessage("E-5. ImageViewExtended: onExit");
      super.onExit();
    }
  };
  var LayerExtended = class extends cc.Layer {
    onEnter() {
      super.onEnter();
      appendMessage("2. LayerExtended: onEnter");

      //add main node
      var scale = cc.winSize.height / 320;
      this.attr({
        anchorX: 0,
        anchorY: 0,
        scale: scale,
        x: (cc.winSize.width - 480 * scale) / 2,
        y: (cc.winSize.height - 320 * scale) / 2
      });
      var json = ccs.load("ccs-res/cocosui/UITest/UITest.json");
      var widget = json.node;
      this.addChild(widget, -1);
      var widgetSize = widget.getContentSize();
      var background = widget.getChildByName("background_Panel");
      background.y += 50;

      // Create the scrollview
      var scrollView = new ScrollViewExtended();
      scrollView.setDirection(ccui.ScrollView.DIR_VERTICAL);
      scrollView.setTouchEnabled(true);
      scrollView.setContentSize(cc.size(280, 150));
      scrollView.x = (widgetSize.width - background.width) / 2 + (background.width - scrollView.width) / 2;
      scrollView.y = background.y;
      this.addChild(scrollView);
      var imageView = new ImageViewExtended();
      imageView.loadTexture("ccs-res/cocosui/ccicon.png");
      var innerWidth = scrollView.width;
      var innerHeight = scrollView.height + imageView.height;
      scrollView.setInnerContainerSize(cc.size(innerWidth, innerHeight));
      var button = new ButtonExtended();
      button.setTouchEnabled(true);
      button.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
      button.x = innerWidth / 2;
      button.y = scrollView.getInnerContainerSize().height - button.height / 2;
      scrollView.addChild(button);
      var textButton = new ccui.Button();
      textButton.setTouchEnabled(true);
      textButton.loadTextures("ccs-res/cocosui/backtotopnormal.png", "ccs-res/cocosui/backtotoppressed.png", "");
      textButton.setTitleText("Remove UI");
      textButton.x = innerWidth / 2;
      textButton.y = button.getBottomBoundary() - button.height;
      textButton.addTouchEventListener(this.exit, this);
      scrollView.addChild(textButton);
      imageView.x = innerWidth / 2;
      imageView.y = textButton.getBottomBoundary() - imageView.height;
      scrollView.addChild(imageView);
      widget.getChildByName("UItest").string = "Please click 'Remove UI' button";
      widget.removeChild(widget.getChildByName("back"));
      widget.removeChild(widget.getChildByName("left_Button"));
      widget.removeChild(widget.getChildByName("middle_Button"));
      widget.removeChild(widget.getChildByName("right_Button"));
    }
    onExitTransitionDidStart() {
      super.onExitTransitionDidStart();
      appendMessage("E-1. LayerExtended: onExitTransitionDidStart");
    }
    onExit() {
      appendMessage("E-2. LayerExtended: onExit");
      super.onExit();
    }
    exit() {
      this.parent.removeUI();
    }
  };
  window.JSBExtendTest = class extends cc.Scene {
    label = null;
    ui = null;
    onEnter() {
      message = "";
      super.onEnter();
      appendMessage("1. SceneExtended: onEnter");
      this.ui = new LayerExtended();
      this.addChild(this.ui);
      var scale = cc.winSize.height / 320;
      this.label = new cc.LabelTTF(message);
      this.label.x = cc.winSize.width / 2;
      this.label.y = (cc.winSize.height - 320 * scale / 2) / 2;
      this.addChild(this.label);
      var back = new cc.LabelTTF("Back", "Arial", 20);
      var menuItem = new cc.MenuItemLabel(back, this.toNativeTest, this);
      var menu = new cc.Menu(menuItem);
      menu.x = 0;
      menu.y = 0;
      menuItem.x = winSize.width - 50;
      menuItem.y = 25;
      this.addChild(menu, 1);
    }
    removeUI() {
      this.removeChild(this.ui, true);
      this.label.y = cc.winSize.height / 2;
      this.label.string = message;
    }
    toNativeTest() {
      var scene = new NativeTestScene();
      scene.runThisTest();
    }
  };
})(window);