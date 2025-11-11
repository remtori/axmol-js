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

var armatureSceneIdx = -1;
var ArmatureTestScene = class extends TestScene {
  onEnter() {
    super.onEnter();
  }
  runThisTest() {
    armatureSceneIdx = -1;
    this.addChild(nextArmatureTest());
    director.runScene(this);
  }
  onMainMenuCallback() {
    this.removeAllChildren();
    ccs.armatureDataManager.clear();
    var scene = new CocoStudioTestScene();
    scene.runThisTest();
  }
  onExit() {
    super.onExit();
  }
};
var armatureSceneArr = [function () {
  return new TestAsynchronousLoading();
}, function () {
  return new TestDirectLoading();
}, function () {
  return new TestCSWithSkeleton();
}, function () {
  return new TestDragonBones20();
}, function () {
  return new TestPerformance();
}, function () {
  return new TestChangeZorder();
}, function () {
  return new TestAnimationEvent();
}, function () {
  return new TestFrameEvent();
}, function () {
  return new TestParticleDisplay();
}, function () {
  return new TestUseMutiplePicture();
}, function () {
  return new TestBoundingBox();
}, function () {
  return new TestAnchorPoint();
}, function () {
  return new TestArmatureNesting();
}, function () {
  return new TestArmatureNesting2();
}, function () {
  return new TestPlaySeveralMovement();
}, function () {
  return new TestEasing();
}, function () {
  return new TestCalculatedVertex();
}];
if (!cc.sys.isNative) {
  armatureSceneArr.push(function () {
    return new TestColliderDetector();
  });
} else {
  //armatureSceneArr.push( function () { return new TestPerformanceBatchNode();} );
  armatureSceneArr.push(function () {
    return new TestChangeAnimationInternal();
  });
}
var nextArmatureTest = function () {
  armatureSceneIdx++;
  armatureSceneIdx = armatureSceneIdx % armatureSceneArr.length;
  return armatureSceneArr[armatureSceneIdx]();
};
var backArmatureTest = function () {
  armatureSceneIdx--;
  if (armatureSceneIdx < 0) armatureSceneIdx += armatureSceneArr.length;
  return armatureSceneArr[armatureSceneIdx]();
};
var restartArmatureTest = function () {
  return armatureSceneArr[armatureSceneIdx]();
};
var ArmatureTestLayer = class extends BaseTestLayer {
  constructor() {
    if (arguments.length === 0) {
      super(cc.color(0, 0, 0, 255), cc.color(98, 99, 117, 255));
    } else {
      this._super.apply(this, arguments);
    }
  }
  onRestartCallback(sender) {
    var s = new ArmatureTestScene();
    s.addChild(restartArmatureTest());
    director.runScene(s);
  }
  onNextCallback(sender) {
    var s = new ArmatureTestScene();
    s.addChild(nextArmatureTest());
    director.runScene(s);
  }
  onBackCallback(sender) {
    var s = new ArmatureTestScene();
    s.addChild(backArmatureTest());
    director.runScene(s);
  }
};

//------------------------------------------------------------------
//
// TestAsynchronousLoading
//
//------------------------------------------------------------------
var TestAsynchronousLoading = class extends ArmatureTestLayer {
  onEnter() {
    super.onEnter();
    this.setMenuItemEnabled(false);
    var armatureDataManager = ccs.armatureDataManager;
    armatureDataManager.addArmatureFileInfoAsync(s_knight_png, s_knight_plist, s_knight_xml, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_weapon_png, s_weapon_plist, s_weapon_xml, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_robot_png, s_robot_plist, s_robot_xml, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_cyborg_png, s_cyborg_plist, s_cyborg_xml, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_Dragon_png, s_Dragon_plist, s_Dragon_xml, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_Cowboy_json, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_hero_json, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_horse_json, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_bear_json, this.dataLoaded, this);
    armatureDataManager.addArmatureFileInfoAsync(s_HeroAnimation_json, this.dataLoaded, this);
  }
  setMenuItemEnabled(bool) {
    var menu = this.getChildByTag(BASE_TEST_MENU_TAG);
    var backItem = menu.getChildByTag(BASE_TEST_MENUITEM_PREV_TAG);
    var restartItem = menu.getChildByTag(BASE_TEST_MENUITEM_RESET_TAG);
    var nextItem = menu.getChildByTag(BASE_TEST_MENUITEM_NEXT_TAG);
    backItem.enabled = bool;
    restartItem.enabled = bool;
    nextItem.enabled = bool;
  }
  title() {
    return "Test Asynchronous Loading";
  }
  subtitle() {
    return "current percent : 0";
  }
  restartCallback(sender) {
    ccs.armatureDataManager.clear();
    super.restartCallback(sender);
  }
  dataLoaded(percent) {
    cc.log("percent:" + percent);
    var subTile = this.getChildByTag(BASE_TEST_SUBTITLE_TAG);
    subTile.setString("current percent : " + percent.toFixed(2) * 100);
    if (percent >= 1) {
      this.setMenuItemEnabled(true);
    }
  }
};

//------------------------------------------------------------------
//
// TestDirectLoading
//
//------------------------------------------------------------------
var TestDirectLoading = class extends ArmatureTestLayer {
  onEnter() {
    super.onEnter();
    // remove sigle resource
    ccs.armatureDataManager.removeArmatureFileInfo(s_bear_json);
    // load resource directly
    ccs.armatureDataManager.addArmatureFileInfo(s_bear_json);
    var armature = new ccs.Armature("bear");
    armature.getAnimation().playWithIndex(0);
    armature.anchorX = 0.5;
    armature.anchorY = 0.5;
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2;
    armature.runAction(cc.sequence(cc.tintTo(5, 200, 100, 0), cc.tintTo(5, 255, 255, 255)));
    this.addChild(armature);
  }
  title() {
    return "Test Direct Loading";
  }
};

//------------------------------------------------------------------
//
// TestCSWithSkeleton
//
//------------------------------------------------------------------
var TestCSWithSkeleton = class extends ArmatureTestLayer {
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    var armature = new ccs.Armature("Cowboy");
    armature.getAnimation().playWithIndex(0);
    armature.scale = 0.2;
    armature.anchorX = 0.5;
    armature.anchorY = 0.5;
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2;
    this.addChild(armature);
  }
  title() {
    return "Test Export From CocoStudio With Skeleton Effect";
  }
};

//------------------------------------------------------------------
//
// TestDragonBones20
//
//------------------------------------------------------------------
var TestDragonBones20 = class extends ArmatureTestLayer {
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_Dragon_png, s_Dragon_plist, s_Dragon_xml);
    var armature = new ccs.Armature("Dragon");
    armature.getAnimation().playWithIndex(0);
    armature.getAnimation().setSpeedScale(0.4);
    armature.scale = 0.6;
    armature.anchorX = 0.5;
    armature.anchorY = 0.5;
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2;
    this.addChild(armature);
  }
  title() {
    return "Test Export From DragonBones version 2.0";
  }
};

//------------------------------------------------------------------
//
// TestPerformance
//
//------------------------------------------------------------------
var ArmaturePerformanceTag = 20000;
var TestPerformance = class extends ArmatureTestLayer {
  armatureCount = 0;
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_knight_png, s_knight_plist, s_knight_xml);
    cc.MenuItemFont.setFontSize(65);
    var decrease = new cc.MenuItemFont(" - ", this.onDecrease, this);
    decrease.color = cc.color(0, 200, 20);
    var increase = new cc.MenuItemFont(" + ", this.onIncrease, this);
    increase.color = cc.color(0, 200, 20);
    var menu = new cc.Menu(decrease, increase);
    menu.alignItemsHorizontally();
    menu.x = cc.visibleRect.width / 2;
    menu.y = cc.visibleRect.height - 100;
    this.addChild(menu, 10000);
  }
  title() {
    return "Test Performance";
  }
  subtitle() {
    return "Current CCArmature Count :";
  }
  onIncrease(sender) {
    this.addArmature(20);
  }
  onDecrease(sender) {
    if (this.armatureCount == 0) return;
    for (var i = 0; i < 20; i++) {
      this.removeArmatureFromParent(ArmaturePerformanceTag + this.armatureCount);
      this.armatureCount--;
      this.refreshTitile();
    }
  }
  addArmature(number) {
    for (var i = 0; i < number; i++) {
      this.armatureCount++;
      var armature = new ccs.Armature("Knight_f/Knight");
      armature.getAnimation().playWithIndex(0);
      armature.x = 50 + this.armatureCount * 2;
      armature.y = 150;
      armature.scale = 0.6;
      this.addArmatureToParent(armature);
    }
    this.refreshTitile();
  }
  addArmatureToParent(armature) {
    this.addChild(armature, 0, ArmaturePerformanceTag + this.armatureCount);
  }
  removeArmatureFromParent(tag) {
    this.removeChildByTag(tag);
  }
  refreshTitile() {
    var subTile = this.getChildByTag(BASE_TEST_SUBTITLE_TAG);
    subTile.setString(this.subtitle() + this.armatureCount);
  }
};

//------------------------------------------------------------------
//
// TestPerformanceBatchNode
//
//------------------------------------------------------------------
var TestPerformanceBatchNode = class extends TestPerformance {
  batchNode = null;
  onEnter() {
    super.onEnter();
    this.batchNode = new ccs.BatchNode();
    this.addChild(this.batchNode);
  }
  title() {
    return "Test Performance of using CCBatchNode";
  }
  addArmatureToParent(armature) {
    this.batchNode.addChild(armature, 0, ArmaturePerformanceTag + this.armatureCount);
  }
  removeArmatureFromParent(tag) {
    this.batchNode.removeChildByTag(tag);
  }
};

//------------------------------------------------------------------
//
// TestChangeZorder
//
//------------------------------------------------------------------
var TestChangeZorder = class extends ArmatureTestLayer {
  currentTag = 0;
  onEnter() {
    super.onEnter();
    var armature = null;
    var armatureDataManager = ccs.armatureDataManager;
    armatureDataManager.addArmatureFileInfo(s_knight_png, s_knight_plist, s_knight_xml);
    armature = new ccs.Armature("Knight_f/Knight");
    armature.getAnimation().playWithIndex(0);
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2 - 100;
    armature.scale = 0.6;
    this.addChild(armature, 0, 0);
    armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    armature = new ccs.Armature("Cowboy");
    armature.getAnimation().playWithIndex(0);
    armature.scale = 0.24;
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2 - 100;
    this.addChild(armature, 1, 1);
    armatureDataManager.addArmatureFileInfo(s_Dragon_png, s_Dragon_plist, s_Dragon_xml);
    armature = new ccs.Armature("Dragon");
    armature.getAnimation().playWithIndex(0);
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2 - 100;
    armature.scale = 0.6;
    this.addChild(armature, 2, 2);
    this.schedule(this.changeZorder, 1);
  }
  title() {
    return "Test Change ZOrder Of Different CCArmature";
  }
  changeZorder(dt) {
    var node = this.getChildByTag(this.currentTag);
    node.zIndex = Math.random() * 3;
    this.currentTag++;
    this.currentTag = this.currentTag % 3;
  }
};

//------------------------------------------------------------------
//
// TestAnimationEvent
//
//------------------------------------------------------------------
var TestAnimationEvent = class extends ArmatureTestLayer {
  _armature = null;
  _direction = 1;
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    this._armature = new ccs.Armature("Cowboy");
    this._armature.getAnimation().play("Fire");
    this._armature.scaleX = -0.25;
    this._armature.scaleY = 0.25;
    this._armature.x = winSize.width / 2 - 150;
    this._armature.y = winSize.height / 2;
    var self = this;
    this._armature.getAnimation().setMovementEventCallFunc(function (armature, movementType, movementID) {
      self.animationEvent(armature, movementType, movementID);
    });
    this.addChild(this._armature);
    this._direction = 1;
  }
  title() {
    return "Test Armature Animation Event";
  }
  animationEvent(armature, movementType, movementID) {
    if (movementType == ccs.MovementEventType.loopComplete) {
      if (movementID == "Fire") {
        var moveBy = cc.moveBy(2, cc.p(300 * this._direction, 0));
        this._armature.stopAllActions();
        this._armature.runAction(cc.sequence(moveBy, cc.callFunc(this.callback, this)));
        this._armature.getAnimation().play("Walk");
        this._direction *= -1;
      }
    }
  }
  callback() {
    this._armature.runAction(cc.scaleTo(0.3, 0.25 * this._direction * -1, 0.25));
    this._armature.getAnimation().play("Fire", 10);
  }
};

//------------------------------------------------------------------
//
// TestAnimationEvent
//
//------------------------------------------------------------------

var FRAME_EVENT_ACTION_TAG = 10000;
var TestFrameEvent = class extends ArmatureTestLayer {
  _nodeGrid = null;
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_HeroAnimation_json);
    var armature = new ccs.Armature("HeroAnimation");
    armature.getAnimation().play("attack");
    armature.getAnimation().setSpeedScale(0.5);
    var center = cc.visibleRect.center;
    armature.x = center.x - 50;
    armature.y = center.y - 100;
    this._nodeGrid = new cc.NodeGrid();
    this._nodeGrid.addChild(armature);
    this.addChild(this._nodeGrid);
    /*
     * Set armature's frame event callback function
     * To disconnect this event, just setFrameEventCallFunc(NULL, NULL);
     */
    var self = this;
    armature.getAnimation().setFrameEventCallFunc(function (bone, evt, originFrameIndex, currentFrameIndex) {
      self.onFrameEvent(bone, evt, originFrameIndex, currentFrameIndex);
    });
    this.schedule(this.checkAction);
  }
  title() {
    return "Test Frame Event";
  }
  onFrameEvent(bone, evt, originFrameIndex, currentFrameIndex) {
    cc.log("(" + bone.getName() + ") emit a frame event (" + evt + ") at frame index (" + currentFrameIndex + ").");
    if (!this.getActionByTag(FRAME_EVENT_ACTION_TAG) || this.getActionByTag(FRAME_EVENT_ACTION_TAG).isDone()) {
      if ("opengl" in cc.sys.capabilities) {
        this.stopAllActions();
        var action = cc.shatteredTiles3D(0.2, cc.size(16, 12), 5, false);
        action.tag = FRAME_EVENT_ACTION_TAG;
        this._nodeGrid.runAction(action);
      }
    }
  }
  checkAction(dt) {
    if ("opengl" in cc.sys.capabilities) {
      if (this._nodeGrid.getNumberOfRunningActions() == 0 && this._nodeGrid.grid != null) this._nodeGrid.grid = null;
    }
  }
};

//------------------------------------------------------------------
//
// TestParticleDisplay
//
//------------------------------------------------------------------
var TestParticleDisplay = class extends ArmatureTestLayer {
  animationID = 0;
  armature = null;
  constructor() {
    super();
    cc.eventManager.addListener({
      event: cc.EventListener.TOUCH_ALL_AT_ONCE,
      onTouchesEnded: function (touches, event) {
        var target = event.getCurrentTarget();
        ++target.animationID;
        target.animationID = target.animationID % target.armature.getAnimation().getMovementCount();
        target.armature.getAnimation().playWithIndex(target.animationID, 10);
        return false;
      }
    }, this);
  }
  onEnter() {
    super.onEnter();
    this.animationID = 0;
    ccs.armatureDataManager.addArmatureFileInfo(s_robot_png, s_robot_plist, s_robot_xml);
    this.armature = new ccs.Armature("robot");
    this.armature.getAnimation().playWithIndex(4);
    var center = cc.visibleRect.center;
    this.armature.x = center.x;
    this.armature.y = center.y;
    this.armature.scale = 0.48;
    this.armature.getAnimation().setSpeedScale(0.5);
    this.addChild(this.armature);
    var p1 = new cc.ParticleSystem("Particles/SmallSun.plist");
    p1.setTotalParticles(30);
    var p2 = new cc.ParticleSystem("Particles/SmallSun.plist");
    p2.setTotalParticles(30);
    var bone = new ccs.Bone("p1");
    bone.addDisplay(p1, 0);
    bone.changeDisplayWithIndex(0, true);
    bone.setIgnoreMovementBoneData(true);
    bone.zIndex = 100;
    bone.scale = 1.2;
    this.armature.addBone(bone, "bady-a3");
    bone = new ccs.Bone("p2");
    bone.addDisplay(p2, 0);
    bone.changeDisplayWithIndex(0, true);
    bone.setIgnoreMovementBoneData(true);
    bone.zIndex = 100;
    bone.scale = 1.2;
    this.armature.addBone(bone, "bady-a30");
  }
  title() {
    return "Test Particle Display";
  }
  subtitle() {
    return "Touch to change animation";
  }
};

//------------------------------------------------------------------
//
// TestUseMutiplePicture
//
//------------------------------------------------------------------
var TestUseMutiplePicture = class extends ArmatureTestLayer {
  displayIndex = 0;
  armature = null;
  constructor() {
    super();
    cc.eventManager.addListener({
      event: cc.EventListener.TOUCH_ALL_AT_ONCE,
      onTouchesEnded: this.onTouchesEnded.bind(this)
    }, this);
  }
  onEnter() {
    super.onEnter();
    this.displayIndex = 0;
    var armatureDataManager = ccs.armatureDataManager;
    armatureDataManager.addArmatureFileInfo(s_knight_png, s_knight_plist, s_knight_xml);
    armatureDataManager.addArmatureFileInfo(s_weapon_png, s_weapon_plist, s_weapon_xml);
    this.armature = new ccs.Armature("Knight_f/Knight");
    this.armature.getAnimation().playWithIndex(0);
    this.armature.x = winSize.width / 2;
    this.armature.y = winSize.height / 2;
    this.armature.scale = 1.2;
    this.addChild(this.armature);
    var weapon = ["weapon_f-sword.png", "weapon_f-sword2.png", "weapon_f-sword3.png", "weapon_f-sword4.png", "weapon_f-sword5.png", "weapon_f-knife.png", "weapon_f-hammer.png"];

    //add skin
    for (var i = 0; i < 7; i++) {
      var skin = ccs.Skin.createWithSpriteFrameName(weapon[i]);
      this.armature.getBone("weapon").addDisplay(skin, i);
    }

    //add label
    var label = new cc.LabelTTF("This is a weapon!", "Arial", 18);
    label.anchorX = 0.2;
    label.anchorY = 0.5;
    this.armature.getBone("weapon").addDisplay(label, 7);
  }
  title() {
    return "Test One CCArmature Use Different Picture";
  }
  subtitle() {
    return "Tap Screen";
  }
  onTouchesEnded(touch, event) {
    ++this.displayIndex;
    this.displayIndex = this.displayIndex % 8;
    this.armature.getBone("weapon").changeDisplayWithIndex(this.displayIndex, true);
    return false;
  }
};

//------------------------------------------------------------------
//
// TestColliderDetector
//
//------------------------------------------------------------------
var TestColliderDetector = class extends ArmatureTestLayer {
  armature1 = null;
  armature2 = null;
  bullet = null;
  space = null;
  enemyTag = 1;
  bulletTag = 2;
  onEnter() {
    super.onEnter();
    ccs.ENABLE_PHYSICS_CHIPMUNK_DETECT = true;
    ccs.armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    this.armature1 = new ccs.Armature("Cowboy");
    this.armature1.getAnimation().play("FireWithoutBullet");
    this.armature1.getAnimation().setSpeedScale(0.2);
    this.armature1.scaleX = -0.2;
    this.armature1.scaleY = 0.2;
    this.armature1.x = 170;
    this.armature1.y = winSize.height / 2;

    /*
     * Set armature's frame event callback function
     * To disconnect this event, just setFrameEventCallFunc(nul, null);
     */
    this.armature1.getAnimation().setFrameEventCallFunc(this.onFrameEvent, this);
    this.addChild(this.armature1);
    this.armature2 = new ccs.Armature("Cowboy");
    this.armature2.getAnimation().play("Walk");
    this.armature2.scaleX = -0.2;
    this.armature2.scaleY = 0.2;
    this.armature2.x = winSize.width - 160;
    this.armature2.y = winSize.height / 2;
    this.addChild(this.armature2);
    this.bullet = new cc.PhysicsSprite("#25.png");
    this.addChild(this.bullet);
    this.initWorld();
    this.scheduleUpdate();
  }
  initWorld() {
    this.space = new cp.Space();
    this.space.gravity = cp.v(0, 0);

    // Physics debug layer
    var debugLayer = new cc.PhysicsDebugNode(this.space);
    this.addChild(debugLayer, 9999);

    //init bullet body
    var width = this.bullet.width,
      height = this.bullet.height;
    var verts = [-width / 2, -height / 2, -width / 2, height / 2, width / 2, height / 2, width / 2, -height / 2];
    var body = new cp.Body(1, cp.momentForPoly(1, verts, cp.vzero));
    this.space.addBody(body);
    var shape = new cp.PolyShape(body, verts, cp.vzero);
    shape.collision_type = this.bulletTag;
    this.space.addShape(shape);
    this.bullet.setBody(body);
    this.bullet.x = -100;
    this.bullet.y = -100;

    //init armature body
    body = new cp.Body(Infinity, Infinity);
    this.space.addBody(body);
    this.armature2.setBody(body);
    var filter = new ccs.ColliderFilter(this.enemyTag);
    this.armature2.setColliderFilter(filter);
    //init collision handler
    this.space.addCollisionHandler(this.enemyTag, this.bulletTag, this.beginHit.bind(this), null, null, this.endHit.bind(this));
  }
  onFrameEvent(bone, evt, originFrameIndex, currentFrameIndex) {
    cc.log("(" + bone.getName() + ") emit a frame event (" + evt + ") at frame index (" + currentFrameIndex + ").");
    /*
     * originFrameIndex is the frame index editted in Action Editor
     * currentFrameIndex is the current index animation played to
     * frame event may be delay emit, so originFrameIndex may be different from currentFrameIndex.
     */
    var p = this.armature1.getBone("Layer126").getDisplayRenderNode().convertToWorldSpaceAR(cc.p(0, 0));
    this.bullet.x = p.x + 60;
    this.bullet.y = p.y;
    this.bullet.stopAllActions();
    this.bullet.runAction(cc.moveBy(1.5, cc.p(800, 0)));
  }
  beginHit(arbiter, space) {
    var shapes = arbiter.getShapes();
    var shapeA = shapes[0];
    var shapeB = shapes[1];
    var bone;
    if (shapeA.collision_type == this.enemyTag) bone = shapeA.data;
    if (shapeB.collision_type == this.enemyTag) bone = shapeB.data;
    if (bone) bone.getArmature().visible = false;
  }
  endHit(arbiter, space) {
    var shapes = arbiter.getShapes();
    var shapeA = shapes[0];
    var shapeB = shapes[1];
    var bone;
    if (shapeA.collision_type == this.enemyTag) bone = shapeA.data;
    if (shapeB.collision_type == this.enemyTag) bone = shapeB.data;
    if (bone) bone.getArmature().visible = true;
  }
  update(dt) {
    this.space.step(dt);
  }
  title() {
    return "Test Collider Detector";
  }
  onExit() {
    super.onExit();
    var shapeList = this.armature2.getShapeList();
    for (var i = 0; i < shapeList.length; i++) {
      this.space.removeShape(shapeList[i]);
    }
    this.space.removeBody(this.armature2.getBody());
    this.space.removeBody(this.bullet.getBody());
    ccs.ENABLE_PHYSICS_CHIPMUNK_DETECT = false;
  }
};

//------------------------------------------------------------------
//
// TestCalculatedVertex
//
//------------------------------------------------------------------
var TestCalculatedVertex = class extends ArmatureTestLayer {
  armature1 = null;
  armature2 = null;
  bullet = null;
  space = null;
  enemyTag = 1;
  bulletTag = 2;
  onEnter() {
    super.onEnter();
    ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX = true;
    ccs.armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    this.armature1 = new ccs.Armature("Cowboy");
    this.armature1.getAnimation().play("FireWithoutBullet");
    this.armature1.getAnimation().setSpeedScale(0.2);
    this.armature1.scaleX = -0.2;
    this.armature1.scaleY = 0.2;
    this.armature1.x = 170;
    this.armature1.y = winSize.height / 2;

    /*
     * Set armature's frame event callback function
     * To disconnect this event, just setFrameEventCallFunc(nul, null);
     */
    this.armature1.getAnimation().setFrameEventCallFunc(this.onFrameEvent, this);
    this.addChild(this.armature1);
    this.armature2 = new ccs.Armature("Cowboy");
    this.armature2.getAnimation().play("Walk");
    this.armature2.scaleX = -0.2;
    this.armature2.scaleY = 0.2;
    this.armature2.x = winSize.width - 160;
    this.armature2.y = winSize.height / 2;
    this.addChild(this.armature2);
    this.bullet = new cc.Sprite("#25.png");
    this.addChild(this.bullet);
    this.scheduleUpdate();
  }
  onFrameEvent(bone, evt, originFrameIndex, currentFrameIndex) {
    cc.log("(" + bone.getName() + ") emit a frame event (" + evt + ") at frame index (" + currentFrameIndex + ").");
    /*
     * originFrameIndex is the frame index editted in Action Editor
     * currentFrameIndex is the current index animation played to
     * frame event may be delay emit, so originFrameIndex may be different from currentFrameIndex.
     */
    var p = this.armature1.getBone("Layer126").getDisplayRenderNode().convertToWorldSpaceAR(cc.p(0, 0));
    this.bullet.x = p.x + 60;
    this.bullet.y = p.y;
    this.bullet.stopAllActions();
    this.bullet.runAction(cc.moveBy(1.5, cc.p(800, 0)));
  }
  update(dt) {
    this.armature2.visible = true;
    var rect = this.bullet.getBoundingBox();

    // This code is just telling how to get the vertex.
    // For a more accurate collider detection, you need to implemente yourself.

    var dict = this.armature2.getBoneDic();
    for (var key in dict) {
      var bone = dict[key];
      var bodyList = bone.getColliderBodyList() || [];
      for (var i = 0; i < bodyList.length; i++) {
        var body = bodyList[i];
        var vertexList = body.getCalculatedVertexList();
        var minx = miny = maxx = maxy = 0;
        for (var j = 0; j < vertexList.length; j++) {
          var vertex = vertexList[j];
          if (j == 0) {
            minx = maxx = vertex.x;
            miny = maxy = vertex.y;
          } else {
            minx = vertex.x < minx ? vertex.x : minx;
            miny = vertex.y < miny ? vertex.y : miny;
            maxx = vertex.x > maxx ? vertex.x : maxx;
            maxy = vertex.y > maxy ? vertex.y : maxy;
          }
        }
        var temp = cc.rect(minx, miny, maxx - minx, maxy - miny);
        if (cc.rectContainsRect(temp, rect)) {
          this.armature2.visible = false;
        }
      }
    }
  }
  draw() {
    this.armature2.drawContour();
  }
  title() {
    return "Test calculated vertex";
  }
  onExit() {
    super.onExit();
    ccs.ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX = false;
  }
};

//------------------------------------------------------------------
//
// TestBoundingBox
//
//------------------------------------------------------------------
var TestBoundingBox = class extends ArmatureTestLayer {
  armature = null;
  drawNode = null;
  onEnter() {
    var _this = this;
    _this._super();
    _this.drawNode = new cc.DrawNode();
    _this.drawNode.setDrawColor(cc.color(100, 100, 100, 255));
    _this.addChild(_this.drawNode);
    ccs.armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    _this.armature = new ccs.Armature("Cowboy");
    _this.armature.getAnimation().playWithIndex(0);
    _this.armature.x = winSize.width / 2;
    _this.armature.y = winSize.height / 2;
    _this.armature.scale = 0.2;
    _this.addChild(_this.armature);
    _this.scheduleUpdate();
  }
  title() {
    return "Test BoundingBox";
  }
  update() {
    var rect = this.armature.getBoundingBox();
    this.drawNode.clear();
    this.drawNode.drawRect(cc.p(rect.x, rect.y), cc.p(cc.rectGetMaxX(rect), cc.rectGetMaxY(rect)));
  }
};

//------------------------------------------------------------------
//
// TestAnchorPoint
//
//------------------------------------------------------------------
var TestAnchorPoint = class extends ArmatureTestLayer {
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    for (var i = 0; i < 5; i++) {
      var armature = new ccs.Armature("Cowboy");
      armature.getAnimation().playWithIndex(0);
      armature.x = winSize.width / 2;
      armature.y = winSize.height / 2;
      armature.scale = 0.2;
      this.addChild(armature, 0, i);
    }
    this.getChildByTag(0).anchorX = 0;
    this.getChildByTag(0).anchorY = 0;
    this.getChildByTag(1).anchorX = 0;
    this.getChildByTag(1).anchorY = 1;
    this.getChildByTag(2).anchorX = 1;
    this.getChildByTag(2).anchorY = 0;
    this.getChildByTag(3).anchorX = 1;
    this.getChildByTag(3).anchorY = 1;
    this.getChildByTag(4).anchorX = 0.5;
    this.getChildByTag(4).anchorY = 0.5;
  }
  title() {
    return "Test Set AnchorPoint";
  }
};

//------------------------------------------------------------------
//
// TestArmatureNesting
//
//------------------------------------------------------------------
var TestArmatureNesting = class extends ArmatureTestLayer {
  armature = null;
  weaponIndex = 0;
  constructor() {
    super();
    cc.eventManager.addListener({
      event: cc.EventListener.TOUCH_ALL_AT_ONCE,
      onTouchesEnded: this.onTouchesEnded.bind(this)
    }, this);
  }
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_cyborg_png, s_cyborg_plist, s_cyborg_xml);
    this.armature = new ccs.Armature("cyborg");
    this.armature.getAnimation().playWithIndex(1);
    this.armature.x = winSize.width / 2;
    this.armature.y = winSize.height / 2;
    this.armature.scale = 1.2;
    this.armature.getAnimation().setSpeedScale(0.4);
    this.addChild(this.armature);
    this.weaponIndex = 0;
  }
  title() {
    return "Test CCArmature Nesting";
  }
  onTouchesEnded(touch, event) {
    ++this.weaponIndex;
    this.weaponIndex = this.weaponIndex % 4;
    this.armature.getBone("armInside").getChildArmature().getAnimation().playWithIndex(this.weaponIndex);
    this.armature.getBone("armOutside").getChildArmature().getAnimation().playWithIndex(this.weaponIndex);
  }
};

//------------------------------------------------------------------
//
// TestArmatureNesting2
//
//------------------------------------------------------------------
var Hero = class extends ccs.Armature {
  _mount = null;
  _layer = null;
  constructor() {
    super();
    this._mount = null;
    this._layer = null;
  }
  changeMount(armature) {
    if (armature == null) {
      this.retain();
      this.playWithIndex(0);
      //Remove hero from display list
      this._mount.getBone("hero").removeDisplay(0);
      this._mount.stopAllActions();

      //Set position to current position
      this.x = this._mount.x;
      this.y = this._mount.y;
      //Add to layer
      this._layer.addChild(this);
      this._mount = armature;
    } else {
      this._mount = armature;
      this.retain();
      //Remove from layer
      this.removeFromParent(false);

      //Get the hero bone
      var bone = armature.getBone("hero");
      //Add hero as a display to this bone
      bone.addDisplay(this, 0);
      //Change this bone's display
      bone.changeDisplayWithIndex(0, true);
      bone.setIgnoreMovementBoneData(true);
      this.x = 0;
      this.y = 0;
      //Change animation
      this.playWithIndex(1);
      this.scale = 1;
    }
  }
  playWithIndex(index) {
    this.getAnimation().playWithIndex(index);
    if (this._mount) {
      this._mount.getAnimation().playWithIndex(index);
    }
  }
  setLayer(layer) {
    this._layer = layer;
  }
  getLayer() {
    return this._layer;
  }
  setMount(mount) {
    this._mount = mount;
  }
  getMount() {
    return this._mount;
  }
};
Hero.create = function (name) {
  var hero = new Hero();
  if (hero && hero.init(name)) {
    return hero;
  }
  return null;
};
var TestArmatureNesting2 = class extends ArmatureTestLayer {
  _hero = null;
  _horse = null;
  _horse2 = null;
  _bear = null;
  _touchedMenu = false;
  constructor() {
    super();
    cc.eventManager.addListener({
      event: cc.EventListener.TOUCH_ALL_AT_ONCE,
      onTouchesEnded: this.onTouchesEnded.bind(this)
    }, this);
  }
  onEnter() {
    super.onEnter();
    this._touchedMenu = false;
    var label = new cc.LabelTTF("Change Mount", "Arial", 20);
    var menuItem = new cc.MenuItemLabel(label, this.changeMountCallback, this);
    var menu = new cc.Menu(menuItem);
    menu.x = 0;
    menu.y = 0;
    menuItem.x = cc.visibleRect.right.x - 67;
    menuItem.y = cc.visibleRect.bottom.y + 50;
    this.addChild(menu, 2);

    //Create a hero
    var hero = Hero.create("hero");
    hero.setLayer(this);
    hero.playWithIndex(0);
    hero.x = cc.visibleRect.left.x + 20;
    hero.y = cc.visibleRect.left.y;
    this.addChild(hero);
    this._hero = hero;

    //Create 3 mount
    this._horse = this.createMount("horse", cc.visibleRect.center);
    this._horse2 = this.createMount("horse", cc.p(120, 200));
    this._horse2.opacity = 200;
    this._bear = this.createMount("bear", cc.p(300, 70));
  }
  title() {
    return "Test CCArmature Nesting 2";
  }
  subtitle() {
    return "Move to a mount and press the ChangeMount Button.";
  }
  onTouchesEnded(touches, event) {
    var point = touches[0].getLocation();
    var armature = this._hero.getMount() == null ? this._hero : this._hero.getMount();
    //Set armature direction
    if (point.x < armature.x) {
      armature.scaleX = -1;
    } else {
      armature.scaleX = 1;
    }
    var move = cc.moveTo(2, point);
    armature.stopAllActions();
    armature.runAction(move);
    return false;
  }
  changeMountCallback(sender) {
    this._hero.stopAllActions();
    if (this._hero.getMount()) {
      this._hero.changeMount(null);
    } else {
      var heroPos = cc.p(this._hero.x, this._hero.y);
      var horsePos = cc.p(this._horse.x, this._horse.y);
      var horse2Pos = cc.p(this._horse2.x, this._horse2.y);
      var bearPos = cc.p(this._bear.x, this._bear.y);
      if (cc.pDistance(heroPos, horsePos) < 20) {
        this._hero.changeMount(this._horse);
      } else if (cc.pDistance(heroPos, horse2Pos) < 20) {
        this._hero.changeMount(this._horse2);
      } else if (cc.pDistance(heroPos, bearPos) < 30) {
        this._hero.changeMount(this._bear);
      }
    }
  }
  createMount(name, position) {
    var armature = new ccs.Armature(name);
    armature.getAnimation().playWithIndex(0);
    armature.x = position.x;
    armature.y = position.y;
    this.addChild(armature);
    return armature;
  }
};

//------------------------------------------------------------------
//
// TestPlaySeveralMovement
//
//------------------------------------------------------------------
var TestPlaySeveralMovement = class extends ArmatureTestLayer {
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    var armature = new ccs.Armature("Cowboy");
    armature.getAnimation().playWithNames(["Walk", "FireMax", "Fire"], 10, true);
    armature.scale = 0.2;
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2;
    this.addChild(armature);
  }
  title() {
    return "Test play several movement";
  }
  subtitle() {
    return "Movement is played one by one";
  }
};

//------------------------------------------------------------------
//
// TestChangeAnimationInternal
//
//------------------------------------------------------------------
var TestChangeAnimationInternal = class extends ArmatureTestLayer {
  constructor() {
    super();
    cc.eventManager.addListener({
      event: cc.EventListener.TOUCH_ALL_AT_ONCE,
      onTouchesEnded: this.onTouchesEnded.bind(this)
    }, this);
  }
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_Cowboy_json);
    var armature = new ccs.Armature("Cowboy");
    armature.getAnimation().playWithIndex(0);
    armature.scale = 0.2;
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2;
    this.addChild(armature);
  }
  title() {
    return "Test change animation internal";
  }
  subtitle() {
    return "Touch to change animation internal";
  }
  onTouchesEnded(touch, event) {
    if (cc.director.getAnimationInterval() == 1 / 30) {
      cc.director.setAnimationInterval(1 / 60);
    } else {
      cc.director.setAnimationInterval(1 / 30);
    }
    return false;
  }
  onExit() {
    super.onExit();
    cc.director.setAnimationInterval(1 / 60);
  }
};

//------------------------------------------------------------------
//
// TestChangeAnimationInternal
//
//------------------------------------------------------------------
var TestEasing = class extends ArmatureTestLayer {
  animationID = 0;
  armature = null;
  constructor() {
    super();
    cc.eventManager.addListener({
      event: cc.EventListener.TOUCH_ALL_AT_ONCE,
      onTouchesEnded: this.onTouchesEnded.bind(this)
    }, this);
  }
  onEnter() {
    super.onEnter();
    ccs.armatureDataManager.addArmatureFileInfo(s_testEasing_json);
    var armature = new ccs.Armature("testEasing");
    armature.getAnimation().playWithIndex(0);
    armature.scale = 0.8;
    armature.x = winSize.width / 2;
    armature.y = winSize.height / 2;
    this.addChild(armature);
    this.armature = armature;
    this.updateSubTitle();
  }
  title() {
    return "Test easing effect";
  }
  subtitle() {
    return "Current easing :";
  }
  onTouchesEnded(touch, event) {
    this.animationID++;
    this.animationID = this.animationID % this.armature.getAnimation().getMovementCount();
    this.armature.getAnimation().playWithIndex(this.animationID);
    this.updateSubTitle();
    return false;
  }
  updateSubTitle() {
    var str = this.subtitle() + this.armature.getAnimation().getCurrentMovementID();
    var label = this.getChildByTag(BASE_TEST_SUBTITLE_TAG);
    label.setString(str);
  }
};
var runArmatureTestScene = function () {
  var pScene = new ArmatureTestScene();
  if (pScene) {
    pScene.runThisTest();
  }
};