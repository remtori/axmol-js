const { s_pPathSister1, s_pPathSister2 } = require('../testResource');
const { Helper, CreateBackMenuItem } = require('../helper');

const kTagSprite1 = 1;
const kTagSprite2 = 2;
const kTagSprite3 = 3;
const kTagSlider = 4;

const s = cc.Director.getInstance().getWinSize();
const scheduler = cc.Director.getInstance().getScheduler();

function getBaseLayer() {
    const layer = cc.Layer.create();
    Helper.initWithLayer(layer);
    return layer;
}

// CameraCenterTest
function CameraCenterTest() {
    const layer = getBaseLayer();

    // LEFT-TOP
    let sprite = cc.Sprite.create("Images/white-512x512.png");
    layer.addChild(sprite, 0);
    sprite.setPosition(cc.p(s.width / 5 * 1, s.height / 5 * 1));
    sprite.setColor(cc.c3b(255, 0, 0));
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    let orbit = cc.OrbitCamera.create(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(cc.RepeatForever.create(orbit));

    // LEFT-BOTTOM
    sprite = cc.Sprite.create("Images/white-512x512.png");
    layer.addChild(sprite, 0, 40);
    sprite.setPosition(cc.p(s.width / 5 * 1, s.height / 5 * 4));
    sprite.setColor(cc.c3b(0, 0, 255));
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    orbit = cc.OrbitCamera.create(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(cc.RepeatForever.create(orbit));

    // RIGHT-TOP
    sprite = cc.Sprite.create("Images/white-512x512.png");
    layer.addChild(sprite, 0);
    sprite.setPosition(cc.p(s.width / 5 * 4, s.height / 5 * 1));
    sprite.setColor(cc.c3b(255, 255, 0));
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    orbit = cc.OrbitCamera.create(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(cc.RepeatForever.create(orbit));

    // RIGHT-BOTTOM
    sprite = cc.Sprite.create("Images/white-512x512.png");
    layer.addChild(sprite, 0, 40);
    sprite.setPosition(cc.p(s.width / 5 * 4, s.height / 5 * 4));
    sprite.setColor(cc.c3b(0, 255, 0));
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    orbit = cc.OrbitCamera.create(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(cc.RepeatForever.create(orbit));

    // CENTER
    sprite = cc.Sprite.create("Images/white-512x512.png");
    layer.addChild(sprite, 0, 40);
    sprite.setPosition(cc.p(s.width / 2, s.height / 2));
    sprite.setColor(cc.c3b(255, 255, 255));
    sprite.setTextureRect(cc.rect(0, 0, 120, 50));
    orbit = cc.OrbitCamera.create(10, 1, 0, 0, 360, 0, 0);
    sprite.runAction(cc.RepeatForever.create(orbit));

    Helper.titleLabel.setString("Camera Center test");
    Helper.subtitleLabel.setString("Sprites should rotate at the same speed");
    return layer;
}

// Test2
function Test2() {
    const layer = getBaseLayer();

    const sp1 = cc.Sprite.create(s_pPathSister1);
    const sp2 = cc.Sprite.create(s_pPathSister2);
    const sp3 = cc.Sprite.create(s_pPathSister1);
    const sp4 = cc.Sprite.create(s_pPathSister2);

    sp1.setPosition(cc.p(100, s.height / 2));
    sp2.setPosition(cc.p(380, s.height / 2));
    layer.addChild(sp1);
    layer.addChild(sp2);

    sp3.setScale(0.25);
    sp4.setScale(0.25);
    sp1.addChild(sp3);
    sp2.addChild(sp4);

    const a1 = cc.RotateBy.create(2, 360);
    const a2 = cc.ScaleBy.create(2, 2);

    const action1 = cc.RepeatForever.create(cc.Sequence.create(a1, a2, a2.reverse()));
    const action2 = cc.RepeatForever.create(cc.Sequence.create(a1.clone(), a2.clone(), a2.reverse()));

    sp2.setAnchorPoint(cc.p(0, 0));

    sp1.runAction(action1);
    sp2.runAction(action2);

    Helper.titleLabel.setString("anchorPoint and children");
    return layer;
}

// Test4
let Test4_layer = null;
let Test4_delay2Entry = null;
let Test4_delay4Entry = null;

function delay2(dt) {
    const node = Test4_layer.getChildByTag(2);
    const action1 = cc.RotateBy.create(1, 360);
    node.runAction(action1);
}

function delay4(dt) {
    scheduler.unscheduleScriptEntry(Test4_delay4Entry);
    Test4_layer.removeChildByTag(3, false);
}

class Test4LayerClass extends cc.Layer {
    onEnter() {
        Test4_delay2Entry = scheduler.scheduleScriptFunc(delay2, 2.0, false);
        Test4_delay4Entry = scheduler.scheduleScriptFunc(delay4, 4.0, false);
    }

    onExit() {
        scheduler.unscheduleScriptEntry(Test4_delay2Entry);
        scheduler.unscheduleScriptEntry(Test4_delay4Entry);
    }
}

function Test4() {
    Test4_layer = getBaseLayer();
    Test4_layer.__proto__ = Test4LayerClass.prototype;

    const sp1 = cc.Sprite.create(s_pPathSister1);
    const sp2 = cc.Sprite.create(s_pPathSister2);
    sp1.setPosition(cc.p(100, 160));
    sp2.setPosition(cc.p(380, 160));

    Test4_layer.addChild(sp1, 0, 2);
    Test4_layer.addChild(sp2, 0, 3);

    Helper.titleLabel.setString("tags");
    return Test4_layer;
}

// Test5
let Test5_entry = null;
let Test5_layer = null;

function Test5_addAndRemove(dt) {
    const sp1 = Test5_layer.getChildByTag(kTagSprite1);
    const sp2 = Test5_layer.getChildByTag(kTagSprite2);

    sp1.retain();
    sp2.retain();

    Test5_layer.removeChild(sp1, false);
    Test5_layer.removeChild(sp2, true);

    Test5_layer.addChild(sp1, 0, kTagSprite1);
    Test5_layer.addChild(sp2, 0, kTagSprite2);

    sp1.release();
    sp2.release();
}

function Test5_onEnterOrExit(tag) {
    if (tag === "enter") {
        Test5_entry = scheduler.scheduleScriptFunc(Test5_addAndRemove, 2.0, false);
    } else if (tag === "exit") {
        scheduler.unscheduleScriptEntry(Test5_entry);
    }
}

function Test5() {
    Test5_layer = getBaseLayer();

    const sp1 = cc.Sprite.create(s_pPathSister1);
    const sp2 = cc.Sprite.create(s_pPathSister2);

    sp1.setPosition(cc.p(100, 160));
    sp2.setPosition(cc.p(380, 160));

    const rot = cc.RotateBy.create(2, 360);
    const rot_back = rot.reverse();
    const forever = cc.RepeatForever.create(cc.Sequence.create(rot, rot_back));

    const rot2 = cc.RotateBy.create(2, 360);
    const rot2_back = rot2.reverse();
    const forever2 = cc.RepeatForever.create(cc.Sequence.create(rot2, rot2_back));

    sp1.runAction(forever);
    sp2.runAction(forever2);

    Test5_layer.addChild(sp1, 0, kTagSprite1);
    Test5_layer.addChild(sp2, 0, kTagSprite2);

    Test5_layer.registerScriptHandler(Test5_onEnterOrExit);

    Helper.titleLabel.setString("remove and cleanup");
    return Test5_layer;
}

module.exports = function NodeTest() {
    console.log('NodeTest');
    const scene = cc.Scene.create();

    Helper.createFunctionTable = [
        CameraCenterTest,
        Test2,
        Test4,
        Test5,
    ];
    Helper.index = 0;

    scene.addChild(CameraCenterTest());
    scene.addChild(CreateBackMenuItem());

    return scene;
}