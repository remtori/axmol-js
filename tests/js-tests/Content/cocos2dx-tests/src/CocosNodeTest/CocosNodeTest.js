/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

var TAG_SPRITE1 = 1;
var TAG_SPRITE2 = 2;
var TAG_SPRITE3 = 3;
var TAG_SLIDER = 4;
var nodeTestSceneIdx = -1;
var MAX_LAYER = 9;
var TestNodeDemo = class extends cc.Layer {
  constructor() {
    super();
    this.init();
  }
  title() {
    return "No title";
  }
  subtitle() {
    return "";
  }
  onRestartCallback(sender) {
    var s = new NodeTestScene();
    s.addChild(restartNodeTest());
    director.runScene(s);
  }
  onNextCallback(sender) {
    var s = new NodeTestScene();
    s.addChild(nextNodeTest());
    director.runScene(s);
  }
  onBackCallback(sender) {
    var s = new NodeTestScene();
    s.addChild(previousNodeTest());
    director.runScene(s);
  }
  numberOfPendingTests() {
    return arrayOfNodeTest.length - 1 - nodeTestSceneIdx;
  }
  getTestNumber() {
    return nodeTestSceneIdx;
  }
  onEnter() {
    super.onEnter();
    var s = director.getWinSize();
    var label = new cc.LabelTTF(this.title(), "Arial", 24);
    this.addChild(label);
    label.x = s.width / 2;
    label.y = s.height - 50;
    var subTitle = this.subtitle();
    if (subTitle && subTitle !== "") {
      var l = new cc.LabelTTF(subTitle, "Thonburi", 16);
      this.addChild(l, 1);
      l.x = s.width / 2;
      l.y = s.height - 80;
    }
    var item1 = new cc.MenuItemImage(s_pathB1, s_pathB2, this.onBackCallback, this);
    var item2 = new cc.MenuItemImage(s_pathR1, s_pathR2, this.onRestartCallback, this);
    var item3 = new cc.MenuItemImage(s_pathF1, s_pathF2, this.onNextCallback, this);
    var menu = new cc.Menu(item1, item2, item3);
    menu.x = 0;
    menu.y = 0;
    item1.x = s.width / 2 - 100;
    item1.y = 30;
    item2.x = s.width / 2;
    item2.y = 30;
    item3.x = s.width / 2 + 100;
    item3.y = 30;
    this.addChild(menu, 1);
  }
};
var CCNodeTest2 = class extends TestNodeDemo {
  onEnter() {
    //----start0----onEnter
    super.onEnter();
    var sp1 = new cc.Sprite(s_pathSister1);
    var sp2 = new cc.Sprite(s_pathSister2);
    var sp3 = new cc.Sprite(s_pathSister1);
    var sp4 = new cc.Sprite(s_pathSister2);
    sp1.x = winSize.width / 4;
    sp1.y = winSize.height / 2;
    sp2.x = winSize.width / 4 * 3;
    sp2.y = winSize.height / 2;
    this.addChild(sp1);
    this.addChild(sp2);
    sp3.scale = 0.25;
    sp4.scale = 0.25;
    sp1.addChild(sp3);
    sp2.addChild(sp4);
    var a1 = cc.rotateBy(2, 360);
    var a2 = cc.scaleBy(2, 2);
    var delay = cc.delayTime(0.2);
    var action1 = cc.sequence(a1, a2, delay, a2.reverse()).repeatForever();
    var action2 = cc.sequence(a1.clone(), a2.clone(), delay.clone(), a2.reverse()).repeatForever();
    sp2.anchorX = 0;
    sp2.anchorY = 0;
    sp1.runAction(action1);
    sp2.runAction(action2);
    //----end0----
  }
  title() {
    return "anchorPoint and children";
  }
  testDuration = 4.1;
  pixel1 = {
    "0": 255,
    "1": 230,
    "2": 204,
    "3": 255
  };
  pixel2 = {
    "0": 204,
    "1": 153,
    "2": 102,
    "3": 255
  };
  getExpectedResult() {
    var ret = {
      "pixel1": "yes",
      "pixel2": "yes"
    };
    return JSON.stringify(ret);
  }
  getCurrentResult() {
    var ret1 = this.readPixels(winSize.width / 4 - 54, winSize.height / 2 - 146, 5, 5);
    var ret2 = this.readPixels(winSize.width / 4 * 3 + 93, winSize.height / 2 + 113, 5, 5);
    var ret = {
      "pixel1": this.containsPixel(ret1, this.pixel1, true, 5) ? "yes" : "no",
      "pixel2": this.containsPixel(ret2, this.pixel2, true, 5) ? "yes" : "no"
    };
    return JSON.stringify(ret);
  }
};
var SID_DELAY2 = 1;
var SID_DELAY4 = 2;
var CCNodeTest4 = class extends TestNodeDemo {
  constructor() {
    //----start1----ctor
    super();
    var sp1 = new cc.Sprite(s_pathSister1);
    var sp2 = new cc.Sprite(s_pathSister2);
    sp1.x = 150;
    sp1.y = winSize.height / 2;
    sp2.x = winSize.width - 150;
    sp2.y = winSize.height / 2;
    this.addChild(sp1, 0, 2);
    this.addChild(sp2, 0, 3);
    this.schedule(this.delay2, 2.0);
    this.schedule(this.delay4, 4.0);

    //Automation param
    this.autoParam = sp1;
    //----end1----
  }
  delay2(dt) {
    //----start1----delay2
    var node = this.getChildByTag(2);
    var action1 = cc.rotateBy(1, 360);
    node.runAction(action1);
    //----end1----
  }
  delay4(dt) {
    //----start1----delay4
    this.unschedule(this.delay4);
    this.removeChildByTag(3, false);
    //----end1----
  }
  title() {
    return "tags";
  }
  testDuration = 1;
  getExpectedResult() {
    return this.autoParam;
  }
  getCurrentResult() {
    var node = this.getChildByTag(2);
    return node;
  }
};
var CCNodeTest5 = class extends TestNodeDemo {
  constructor() {
    //----start2----ctor
    super();
    var sp1 = new cc.Sprite(s_pathSister1);
    var sp2 = new cc.Sprite(s_pathSister2);
    sp1.x = 150;
    sp1.y = winSize.height / 2;
    sp2.x = winSize.width - 150;
    sp2.y = winSize.height / 2;
    var rot = cc.rotateBy(2, 360);
    var rot_back = rot.reverse();
    var forever = cc.sequence(rot, rot_back).repeatForever();
    var forever2 = forever.clone();
    forever.tag = 101;
    forever2.tag = 102;
    this.addChild(sp1, 0, TAG_SPRITE1);
    this.addChild(sp2, 0, TAG_SPRITE2);
    sp1.runAction(forever);
    sp2.runAction(forever2);
    this.schedule(this.onAddAndRemove, 2.0);
    //----end2----
  }
  onAddAndRemove(dt) {
    //----start2----onAddAndRemove
    var sp1 = this.getChildByTag(TAG_SPRITE1);
    var sp2 = this.getChildByTag(TAG_SPRITE2);

    // hack for JSB.
    sp1.retain();
    sp2.retain();
    this.removeChild(sp1, false);
    this.removeChild(sp2, true);
    this.testSP1 = this.getChildByTag(TAG_SPRITE1);
    this.testSP2 = this.getChildByTag(TAG_SPRITE2);
    this.addChild(sp1, 0, TAG_SPRITE1);
    this.addChild(sp2, 0, TAG_SPRITE2);

    // hack for JSB.
    sp1.release();
    sp2.release();
    //----end2----
  }
  title() {
    return "remove and cleanup";
  }
  testDuration = 2.5;
  testSP1 = null;
  testSP2 = null;
  pixel1 = {
    "0": 0,
    "1": 0,
    "2": 0,
    "3": 255
  };
  pixel2 = {
    "0": 51,
    "1": 0,
    "2": 0,
    "3": 255
  };
  getExpectedResult() {
    var ret = {
      "sp1": null,
      "sp2": null,
      "pixel1": "yes",
      "pixel2": "yes"
    };
    return JSON.stringify(ret);
  }
  getCurrentResult() {
    var ret1 = this.readPixels(134, 164, 5, 5);
    var ret2 = this.readPixels(winSize.width - 148, winSize.height / 2 + 51, 5, 5);
    var ret = {
      "sp1": this.testSP1,
      "sp2": this.testSP2,
      "pixel1": this.containsPixel(ret1, this.pixel1, false) ? "yes" : "no",
      "pixel2": this.containsPixel(ret2, this.pixel2, true, 3) ? "yes" : "no"
    };
    return JSON.stringify(ret);
  }
};
var CCNodeTest6 = class extends TestNodeDemo {
  constructor() {
    //----start3----ctor
    super();
    var sp1 = new cc.Sprite(s_pathSister1);
    var sp11 = new cc.Sprite(s_pathSister1);
    var sp2 = new cc.Sprite(s_pathSister2);
    var sp21 = new cc.Sprite(s_pathSister2);
    sp1.x = 150;
    sp1.y = winSize.height / 2;
    sp2.x = winSize.width - 150;
    sp2.y = winSize.height / 2;
    var rot = cc.rotateBy(2, 360);
    var rot_back = rot.reverse();
    var forever1 = cc.sequence(rot, rot_back).repeatForever();
    var forever11 = forever1.clone();
    var forever2 = forever1.clone();
    var forever21 = forever1.clone();
    this.addChild(sp1, 0, TAG_SPRITE1);
    sp1.addChild(sp11, 11);
    this.addChild(sp2, 0, TAG_SPRITE2);
    sp2.addChild(sp21, 21);
    sp1.runAction(forever1);
    sp11.runAction(forever11);
    sp2.runAction(forever2);
    sp21.runAction(forever21);
    this.schedule(this.onAddAndRemove, 2.0);
    //----end3----
  }
  onAddAndRemove(dt) {
    //----start3----onAddAndRemove
    var sp1 = this.getChildByTag(TAG_SPRITE1);
    var sp2 = this.getChildByTag(TAG_SPRITE2);

    // hack for JSB.
    sp1.retain();
    sp2.retain();
    this.removeChild(sp1, false);
    this.removeChild(sp2, true);

    //Automation parameters
    this.autoParam1 = sp1.getChildByTag(11);
    this.autoParam2 = sp2.getChildByTag(21);
    this.addChild(sp1, 0, TAG_SPRITE1);
    this.addChild(sp2, 0, TAG_SPRITE2);

    // hack for JSB.
    sp1.release();
    sp2.release();
    //----end3----
  }
  title() {
    return "remove/cleanup with children";
  }
  testDuration = 2.1;
  getExpectedResult() {
    var ret = [null, null];
    return JSON.stringify(ret);
  }
  getCurrentResult() {
    var ret = [this.autoParam1, this.autoParam2];
    return JSON.stringify(ret);
  }
};
var StressTest1 = class extends TestNodeDemo {
  constructor() {
    //----start4----ctor
    super();
    var sp1 = new cc.Sprite(s_pathSister1);
    this.addChild(sp1, 0, TAG_SPRITE1);
    this.width = 0;
    this.height = 0;
    sp1.x = winSize.width / 2;
    sp1.y = winSize.height / 2;
    this.schedule(this.onShouldNotCrash, 1.0);
    //----end4----
  }
  onShouldNotCrash(dt) {
    //----start4----onShouldNotCrash
    this.unschedule(this.onShouldNotCrash);

    // if the node has timers, it crashes
    var explosion = new cc.ParticleSun();
    explosion.texture = cc.textureCache.addImage(s_fire);
    explosion.x = winSize.width / 2;
    explosion.y = winSize.height / 2;
    this.runAction(cc.sequence(cc.rotateBy(2, 360), cc.callFunc(this.onRemoveMe, this)));
    this.addChild(explosion);
    //----end4----
  }
  onRemoveMe(node) {
    //----start4----onRemoveMe
    if (autoTestEnabled) {
      this.testPass = true;
      return;
    }
    this.parent.removeChild(node, true);
    this.onNextCallback(this);
    //----end4----
  }
  title() {
    return "stress test #1: no crashes";
  }
  testDuration = 3.2;
  testPass = false;
  getExpectedResult() {
    var ret = {
      "pass": true
    };
    return JSON.stringify(ret);
  }
  getCurrentResult() {
    var ret = {
      "pass": this.testPass
    };
    return JSON.stringify(ret);
  }
};
var StressTest2 = class extends TestNodeDemo {
  constructor() {
    //----start5----ctor
    super();
    var sublayer = new cc.Layer();
    var sp1 = new cc.Sprite(s_pathSister1);
    sp1.x = 80;
    sp1.y = winSize.height / 2;
    var move = cc.moveBy(3, cc.p(350, 0));
    var move_ease_inout3 = move.clone().easing(cc.easeInOut(2.0));
    var move_ease_inout_back3 = move_ease_inout3.reverse();
    var seq3 = cc.sequence(move_ease_inout3, move_ease_inout_back3);
    sp1.runAction(seq3.repeatForever());
    sublayer.addChild(sp1, 1);
    var fire = new cc.ParticleFire();
    fire.texture = cc.textureCache.addImage(s_fire);
    fire.x = 80;
    fire.y = winSize.height / 2 - 50;
    var copy_seq3 = seq3.clone();
    fire.runAction(copy_seq3.repeatForever());
    sublayer.addChild(fire, 2);
    this.schedule(this.shouldNotLeak, 6.0);
    this.addChild(sublayer, 0, TAG_SPRITE1);
    //----end5----
  }
  shouldNotLeak(dt) {
    //----start5----shouleNotLeak
    this.unschedule(this.shouldNotLeak);
    var sublayer = this.getChildByTag(TAG_SPRITE1);
    sublayer.removeAllChildren();
    //----end5----
  }
  title() {
    return "stress test #2: no leaks";
  }
};
var NodeToWorld = class extends TestNodeDemo {
  constructor() {
    //----start6----ctor
    // This code tests that nodeToParent works OK:
    //  - It tests different anchor Points
    //  - It tests different children anchor points
    super();
    var back = new cc.Sprite(s_back3);
    this.addChild(back, 5);
    back.anchorX = 0;
    back.anchorY = 0;
    var item = new cc.MenuItemImage(s_playNormal, s_playSelect, this.onClicked);
    var menu = new cc.Menu(item);
    menu.alignItemsVertically();
    menu.x = back.width / 2;
    menu.y = back.height / 2;
    back.addChild(menu);
    var rot = cc.rotateBy(3, 360);
    var delay = cc.delayTime(0.3);
    var fe = cc.sequence(rot, delay).repeatForever();
    item.runAction(fe);
    var move = cc.moveBy(3, cc.p(200, 0));
    var move_back = move.reverse();
    var seq = cc.sequence(move, delay.clone(), move_back);
    var fe2 = seq.repeatForever();
    back.runAction(fe2);

    //Automation parameters
    this.autoParam = item;
    //----end6----
  }
  onClicked() {
    //----start6----ctor
    cc.log("On clicked");
    //----end6----
  }
  title() {
    return "nodeToParent transform";
  }
  testDuration = 3.1;
  getExpectedResult() {
    var ret = {
      "a": 1,
      "b": "0.00",
      "c": "-0.00",
      "d": 1,
      "tx": "378",
      "ty": "139"
    };
    return JSON.stringify(ret);
  }
  getCurrentResult() {
    var ret = this.autoParam.nodeToWorldTransform();
    ret.b = ret.b.toFixed(2);
    ret.c = ret.c.toFixed(2);
    ret.tx = ret.tx.toFixed(0);
    ret.ty = ret.ty.toFixed(0);
    return JSON.stringify(ret);
  }
};
var CameraOrbitTest = class extends TestNodeDemo {
  _preProjection = null;
  constructor() {
    super();
    this.init();
  }
  onEnter() {
    super.onEnter();
    var p = new cc.Sprite(s_back3);
    this.addChild(p, 0);
    p.x = winSize.width / 2;
    p.y = winSize.height / 2;
    p.opacity = 128;

    // LEFT
    var sw = p.getContentSize().width,
      sh = p.getContentSize().height;
    var sprite = new cc.Sprite(s_pathGrossini);
    sprite.scale = 0.5;
    p.addChild(sprite, 0);
    sprite.x = sw / 4;
    sprite.y = sh / 2;
    var orbit = cc.orbitCamera(2, 1, 0, 0, 360, 0, 0);
    sprite.runAction(orbit.repeatForever());

    // CENTER
    sprite = new cc.Sprite(s_pathGrossini);
    sprite.scale = 1.0;
    p.addChild(sprite, 0);
    sprite.x = sw / 4 * 2;
    sprite.y = sh / 2;
    orbit = cc.orbitCamera(2, 1, 0, 0, 360, 45, 0);
    sprite.runAction(orbit.repeatForever());

    // RIGHT
    sprite = new cc.Sprite(s_pathGrossini);
    sprite.scale = 2.0;
    p.addChild(sprite, 0);
    sprite.x = sw / 4 * 3;
    sprite.y = sh / 2;
    orbit = cc.orbitCamera(2, 1, 0, 0, 360, 90, -45);
    sprite.runAction(orbit.repeatForever());

    // PARENT
    orbit = cc.orbitCamera(10, 1, 0, 0, 360, 0, 90);
    p.runAction(orbit.repeatForever());
    this.scale = 1;
    //----end11----
    this._preProjection = director.getProjection();
    director.setDepthTest(true);
    director.setProjection(cc.Director.PROJECTION_3D);
    //----end11----
  }
  onExit() {
    //----start11----onExit
    director.setDepthTest(false);
    director.setProjection(this._preProjection);
    super.onExit();
    //----end11----
  }
  title() {
    return "Camera Orbit test";
  }
};
var CameraZoomTest = class extends TestNodeDemo {
  _z = 0;
  constructor() {
    //----start12----ctor
    super();

    // LEFT
    var sprite = new cc.Sprite(s_pathGrossini);
    this.addChild(sprite, 0);
    sprite.x = winSize.width / 4;
    sprite.y = winSize.height / 2;
    if ("opengl" in cc.sys.capabilities) {
      var cam = sprite.getCamera();
      cam.setEye(0, 0, 415 / 2);
      cam.setCenter(0, 0, 0);
    }

    // CENTER
    sprite = new cc.Sprite(s_pathGrossini);
    this.addChild(sprite, 0, 40);
    sprite.x = winSize.width / 4 * 2;
    sprite.y = winSize.height / 2;
    //cam = [sprite camera);
    //[cam setEyeX:0 eyeY:0 eyeZ:415/2);

    // RIGHT
    sprite = new cc.Sprite(s_pathGrossini);
    this.addChild(sprite, 0, 20);
    sprite.x = winSize.width / 4 * 3;
    sprite.y = winSize.height / 2;
    //cam = [sprite camera);
    //[cam setEyeX:0 eyeY:0 eyeZ:-485);
    //[cam setCenterX:0 centerY:0 centerZ:0);

    this._z = 0;
    this.scheduleUpdate();

    //Automation parameters
    this.autoParam = sprite;
    //----end12----
  }
  update(dt) {
    //----start12----update
    if (!("opengl" in cc.sys.capabilities)) return;
    this._z += dt * 100;
    var sprite = this.getChildByTag(20);
    var cam = sprite.getCamera();
    cam.setEye(0, 0, this._z);
    if (!cc.sys.isNative) sprite.setNodeDirty();
    sprite = this.getChildByTag(40);
    cam = sprite.getCamera();
    cam.setEye(0, 0, -this._z);
    if (!cc.sys.isNative) sprite.setNodeDirty();
    //----end12----
  }
  onEnter() {
    //TODO
    //----start12----onEnter
    super.onEnter();
    director.setProjection(cc.Director.PROJECTION_3D);
    //----end12----
  }
  onExit() {
    //TODO
    //----start12----onExit
    director.setProjection(cc.Director.PROJECTION_2D);
    super.onExit();
    //----end12----
  }
  title() {
    return "Camera Zoom test";
  }
  testDuration = 1.1;
  pixel = {
    "0": 115,
    "1": 0,
    "2": 115,
    "3": 255
  };
  getExpectedResult() {
    var ret1 = {
      "z": this._z.toFixed(2)
    };
    var ret2 = {
      "pixel": "yes"
    };
    return JSON.stringify([ret1, ret2]);
  }
  getCurrentResult() {
    var ret1 = {
      "z": this.autoParam.getCamera().getEye().z.toFixed(2)
    };
    var readPixel = this.readPixels(winSize.width / 4 * 3, winSize.height / 2, 5, 5);
    var ret2 = {
      "pixel": !this.containsPixel(readPixel, this.pixel, false) ? "yes" : "no"
    };
    return JSON.stringify([ret1, ret2]);
  }
};
var CameraCenterTest = class extends TestNodeDemo {
  constructor() {
    //----start10----ctor
    super();

    // LEFT-TOP
    var sprite = new cc.Sprite(s_texture512);
    this.addChild(sprite, 0);
    sprite.x = winSize.width / 5;
    sprite.y = winSize.height / 5;
    sprite.color = cc.color.RED;
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    var orbit = cc.orbitCamera(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(orbit.repeatForever());

    // LEFT-BOTTOM
    sprite = new cc.Sprite(s_texture512);
    this.addChild(sprite, 0, 40);
    sprite.x = winSize.width / 5;
    sprite.y = winSize.height / 5 * 4;
    sprite.color = cc.color.BLUE;
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    orbit = cc.orbitCamera(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(orbit.repeatForever());

    // RIGHT-TOP
    sprite = new cc.Sprite(s_texture512);
    this.addChild(sprite, 0);
    sprite.x = winSize.width / 5 * 4;
    sprite.y = winSize.height / 5;
    sprite.color = cc.color.YELLOW;
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    orbit = cc.orbitCamera(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(orbit.repeatForever());

    // RIGHT-BOTTOM
    sprite = new cc.Sprite(s_texture512);
    this.addChild(sprite, 0, 40);
    sprite.x = winSize.width / 5 * 4;
    sprite.y = winSize.height / 5 * 4;
    sprite.color = cc.color.GREEN;
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    orbit = cc.orbitCamera(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(orbit.repeatForever());

    // CENTER
    sprite = new cc.Sprite(s_texture512);
    this.addChild(sprite, 0, 40);
    sprite.x = winSize.width / 2;
    sprite.y = winSize.height / 2;
    sprite.color = cc.color.WHITE;
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    orbit = cc.orbitCamera(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(orbit.repeatForever());
    //----end10----
  }
  onEnter() {
    //----start10----onEnter
    super.onEnter();
    cc.director.setProjection(cc.Director.PROJECTION_3D);
    //----end10----
  }
  onExit() {
    //----start10----onExit
    cc.director.setProjection(cc.Director.PROJECTION_2D);
    super.onExit();
    //----end10----
  }
  title() {
    return "Camera Center test";
  }
  subtitle() {
    return "Sprites should rotate at the same speed";
  }
  testDuration = 2.6;
  pixel1 = {
    "0": 255,
    "1": 255,
    "2": 255,
    "3": 255
  };
  pixel2 = {
    "0": 255,
    "1": 255,
    "2": 255,
    "3": 255
  };
  pixel3 = {
    "0": 255,
    "1": 255,
    "2": 255,
    "3": 255
  };
  getExpectedResult() {
    var ret = {
      "pixel1": "yes",
      "pixel2": "yes",
      "pixel3": "yes"
    };
    return JSON.stringify(ret);
  }
  getCurrentResult() {
    var ret1 = this.readPixels(winSize.width / 2, winSize.height / 2, 5, 5);
    var ret2 = this.readPixels(winSize.width / 2 - 25, winSize.height / 2, 5, 5);
    var ret3 = this.readPixels(winSize.width / 2 + 20, winSize.height / 2, 5, 5);
    var ret = {
      "pixel1": this.containsPixel(ret1, this.pixel1, false) ? "yes" : "no",
      "pixel2": !this.containsPixel(ret2, this.pixel2, false) ? "yes" : "no",
      "pixel3": !this.containsPixel(ret3, this.pixel3, false) ? "yes" : "no"
    };
    return JSON.stringify(ret);
  }
};

//
// ConvertToNode
//
var ConvertToNode = class extends TestNodeDemo {
  constructor() {
    //----start9----ctor
    super();
    if ('touches' in cc.sys.capabilities) {
      cc.eventManager.addListener(cc.EventListener.create({
        event: cc.EventListener.TOUCH_ALL_AT_ONCE,
        onTouchesEnded: function (touches, event) {
          var target = event.getCurrentTarget();
          for (var it = 0; it < touches.length; it++) {
            var touch = touches[it];
            var location = touch.getLocation();
            target.processEvent(location);
          }
        }
      }), this);
    } else if ('mouse' in cc.sys.capabilities) cc.eventManager.addListener({
      event: cc.EventListener.MOUSE,
      onMouseUp: function (event) {
        event.getCurrentTarget().processEvent(event.getLocation());
      }
    }, this);
    var rotate = cc.rotateBy(10, 360);
    var action = rotate.repeatForever();
    for (var i = 0; i < 3; i++) {
      var sprite = new cc.Sprite(s_pathGrossini);
      sprite.x = winSize.width / 4 * (i + 1);
      sprite.y = winSize.height / 2;
      var point = new cc.Sprite(s_pathR1);
      point.scale = 0.25;
      point.x = sprite.x;
      point.y = sprite.y;
      this.addChild(point, 10, 100 + i);
      switch (i) {
        case 0:
          sprite.anchorX = 0;
          sprite.anchorY = 0;
          break;
        case 1:
          sprite.anchorX = 0.5;
          sprite.anchorY = 0.5;
          break;
        case 2:
          sprite.anchorX = 1;
          sprite.anchorY = 1;
          break;
      }
      point.x = sprite.x;
      point.y = sprite.y;
      var copy = action.clone();
      sprite.runAction(copy);
      this.addChild(sprite, i);
    }
    //----end9----
  }
  processEvent(location) {
    //----start9----processEvent
    this.testP1 = [];
    this.testP2 = [];
    for (var i = 0; i < 3; i++) {
      var node = this.getChildByTag(100 + i);
      var p1 = node.convertToNodeSpaceAR(location);
      var p2 = node.convertToNodeSpace(location);
      cc.log("AR: x=" + p1.x.toFixed(2) + ", y=" + p1.y.toFixed(2) + " -- Not AR: x=" + p2.x.toFixed(2) + ", y=" + p2.y.toFixed(2));
      this.testP1.push({
        "x": p1.x,
        "y": p1.y
      });
      this.testP2.push({
        "x": p2.x,
        "y": p2.y
      });
    }
    //----end9----
  }
  title() {
    return "Convert To Node Space";
  }
  subtitle() {
    return "testing convertToNodeSpace / AR. Touch and see console";
  }
  testDuration = 1;
  testP1 = [];
  expectedP1 = [];
  testP2 = [];
  expectedP2 = [];
  setupAutomation() {
    this.expectedP1.push({
      "x": -winSize.width,
      "y": -winSize.height * 2
    });
    this.expectedP1.push({
      "x": -winSize.width * 2,
      "y": -winSize.height * 2
    });
    this.expectedP1.push({
      "x": -winSize.width * 3,
      "y": -winSize.height * 2
    });
    this.expectedP2.push({
      "x": -winSize.width + 24.5,
      "y": -winSize.height * 2 + 23.5
    });
    this.expectedP2.push({
      "x": -winSize.width * 2 + 24.5,
      "y": -winSize.height * 2 + 23.5
    });
    this.expectedP2.push({
      "x": -winSize.width * 3 + 24.5,
      "y": -winSize.height * 2 + 23.5
    });
  }
  getExpectedResult() {
    return JSON.stringify({
      "p1": this.expectedP1,
      "p2": this.expectedP2
    });
  }
  getCurrentResult() {
    this.processEvent(cc.p(0, 0));
    var ret = {
      "p1": this.testP1,
      "p2": this.testP2
    };
    return JSON.stringify(ret);
  }
};

//
// BoundingBox Test
//
var BoundingBoxTest = class extends TestNodeDemo {
  constructor() {
    //----start8----ctor
    super();
    var sprite = new cc.Sprite(s_pathGrossini);
    this.addChild(sprite);
    sprite.x = winSize.width / 2;
    sprite.y = winSize.height / 2;
    var bb = sprite.getBoundingBox();
    cc.log('BoundingBox:');
    //for( var i in bb )
    //    cc.log( i + " = " + bb[i] );
    cc.log('origin = [ ' + bb.x + "," + bb.y + "]");
    cc.log('size = [ ' + bb.width + "," + bb.height + "]");
    this.testBB = bb;
    //----end8----
  }
  title() {
    return "Bounding Box Test";
  }
  subtitle() {
    return "Testing getBoundingBox(). See console";
  }
  testDuration = 0.5;
  testBB = null;
  getExpectedResult() {
    var ret = {
      "x": 0 | winSize.width / 2 - 42.5,
      "y": 0 | winSize.height / 2 - 60.5,
      "w": 85,
      "h": 121
    };
    return JSON.stringify(ret);
  }
  getCurrentResult() {
    var ret = {
      "x": 0 | this.testBB.x,
      "y": 0 | this.testBB.y,
      "w": this.testBB.width,
      "h": this.testBB.height
    };
    return JSON.stringify(ret);
  }
};
var SchedulerTest1 = class extends TestNodeDemo {
  constructor() {
    //----start7----ctor
    super();
    var layer = new cc.Layer();
    //UXLOG("retain count after init is %d", layer->retainCount());
    // 1

    this.addChild(layer, 0);
    //UXLOG("retain count after addChild is %d", layer->retainCount());
    // 2

    layer.schedule(this.doSomething);
    //UXLOG("retain count after schedule is %d", layer->retainCount());
    // 3 : (object-c viersion), but win32 version is still 2, because CCTimer class don't save target.

    layer.unschedule(this.doSomething);
    //UXLOG("retain count after unschedule is %d", layer->retainCount());
    // STILL 3!  (win32 is '2')
    //----end7----
  }
  doSomething(dt) {
    //----start7----doSomething
    this.testBool = false;
    //----end7----
  }
  title() {
    return "cocosnode scheduler test #1";
  }
  testDuration = 0.5;
  testBool = true;
  getExpectedResult() {
    return true;
  }
  getCurrentResult() {
    return this.testBool;
  }
};
var NodeOpaqueTest = class extends TestNodeDemo {
  constructor() {
    //----start13----ctor
    super();
    var winSize = cc.director.getWinSize();
    var background;
    for (var i = 0; i < 50; i++) {
      background = new cc.Sprite(s_back1);
      background.setBlendFunc(cc.ONE, cc.ONE_MINUS_SRC_ALPHA);
      background.x = winSize.width / 2;
      background.y = winSize.height / 2;
      this.addChild(background);
    }
    //----end13----
  }
  title() {
    return "Node Opaque Test";
  }
  subtitle() {
    return "Node rendered with GL_BLEND disabled";
  }
};
var NodeNonOpaqueTest = class extends TestNodeDemo {
  constructor() {
    //----start14----ctor
    super();
    var winSize = cc.director.getWinSize();
    var background;
    for (var i = 0; i < 50; i++) {
      background = new cc.Sprite(s_back1);
      background.setBlendFunc(cc.ONE, cc.ZERO);
      background.x = winSize.width / 2;
      background.y = winSize.height / 2;
      this.addChild(background);
    }
    //----end14----
  }
  title() {
    return "Node Non Opaque Test";
  }
  subtitle() {
    return "Node rendered with GL_BLEND enabled";
  }
};

//
// MAIN ENTRY POINT
//
var NodeTestScene = class extends TestScene {
  runThisTest(num) {
    nodeTestSceneIdx = num || num == 0 ? num - 1 : -1;
    MAX_LAYER = 9;
    var layer = nextNodeTest();
    this.addChild(layer);
    director.runScene(this);
  }
};

//
// Flow control
//
var arrayOfNodeTest = [CCNodeTest2, CCNodeTest4, CCNodeTest5, CCNodeTest6, StressTest1, StressTest2, NodeToWorld, SchedulerTest1, BoundingBoxTest, ConvertToNode];
if ('opengl' in cc.sys.capabilities) {
  cc.sys.isNative || arrayOfNodeTest.push(CameraCenterTest);
  arrayOfNodeTest.push(CameraOrbitTest);
  cc.sys.isNative || arrayOfNodeTest.push(CameraZoomTest);
  arrayOfNodeTest.push(NodeOpaqueTest);
  arrayOfNodeTest.push(NodeNonOpaqueTest);
}
var nextNodeTest = function () {
  nodeTestSceneIdx++;
  nodeTestSceneIdx = nodeTestSceneIdx % arrayOfNodeTest.length;
  if (window.sideIndexBar) {
    nodeTestSceneIdx = window.sideIndexBar.changeTest(nodeTestSceneIdx, 24);
  }
  return new arrayOfNodeTest[nodeTestSceneIdx]();
};
var previousNodeTest = function () {
  nodeTestSceneIdx--;
  if (nodeTestSceneIdx < 0) nodeTestSceneIdx += arrayOfNodeTest.length;
  if (window.sideIndexBar) {
    nodeTestSceneIdx = window.sideIndexBar.changeTest(nodeTestSceneIdx, 24);
  }
  return new arrayOfNodeTest[nodeTestSceneIdx]();
};
var restartNodeTest = function () {
  return new arrayOfNodeTest[nodeTestSceneIdx]();
};
new RegExp();