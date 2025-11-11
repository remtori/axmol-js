const { s_pPathGrossini } = require('../testResource');
const { CreateBackMenuItem } = require('../helper');

const MID_PUSHSCENE = 100;
const MID_PUSHSCENETRAN = 101;
const MID_QUIT = 102;
const MID_REPLACESCENE = 103;
const MID_REPLACESCENETRAN = 104;
const MID_GOBACK = 105;

let SceneTestLayer1 = null;
let SceneTestLayer2 = null;
let SceneTestLayer3 = null;

// SceneTestLayer1
SceneTestLayer1 = function() {
    const ret = cc.Layer.create();

    function onPushScene(tag, pSender) {
        const scene = cc.Scene.create();
        const layer = SceneTestLayer2();
        scene.addChild(layer, 0);
        scene.addChild(CreateBackMenuItem());
        cc.Director.getInstance().pushScene(scene);
    }

    function onPushSceneTran(tag, pSender) {
        const scene = cc.Scene.create();
        const layer = SceneTestLayer2();
        scene.addChild(layer, 0);
        scene.addChild(CreateBackMenuItem());
        cc.Director.getInstance().pushScene(cc.TransitionSlideInT.create(1, scene));
    }

    function onQuit(tag, pSender) {
        console.log("onQuit");
    }

    const item1 = cc.MenuItemFont.create("Test pushScene");
    item1.registerScriptTapHandler(onPushScene);
    const item2 = cc.MenuItemFont.create("Test pushScene w/transition");
    item2.registerScriptTapHandler(onPushSceneTran);
    const item3 = cc.MenuItemFont.create("Quit");
    item3.registerScriptTapHandler(onQuit);

    const menu = cc.Menu.create(item1, item2, item3);
    menu.alignItemsVertically();

    ret.addChild(menu);

    const s = cc.Director.getInstance().getWinSize();
    const sprite = cc.Sprite.create(s_pPathGrossini);
    ret.addChild(sprite);
    sprite.setPosition(cc.p(s.width - 40, s.height / 2));
    const rotate = cc.RotateBy.create(2, 360);
    const repeatAction = cc.RepeatForever.create(rotate);
    sprite.runAction(repeatAction);

    function onNodeEvent(event) {
        if (event === "enter") {
            console.log("SceneTestLayer1#onEnter");
        } else if (event === "enterTransitionFinish") {
            console.log("SceneTestLayer1#onEnterTransitionDidFinish");
        }
    }

    ret.registerScriptHandler(onNodeEvent);
    return ret;
};

// SceneTestLayer2
SceneTestLayer2 = function() {
    const ret = cc.Layer.create();
    let m_timeCounter = 0;

    function onGoBack(tag, pSender) {
        cc.Director.getInstance().popScene();
    }

    function onReplaceScene(tag, pSender) {
        const scene = cc.Scene.create();
        const layer = SceneTestLayer3();
        scene.addChild(layer, 0);
        scene.addChild(CreateBackMenuItem());
        cc.Director.getInstance().replaceScene(scene);
    }

    function onReplaceSceneTran(tag, pSender) {
        const scene = cc.Scene.create();
        const layer = SceneTestLayer3();
        scene.addChild(layer, 0);
        scene.addChild(CreateBackMenuItem());
        cc.Director.getInstance().replaceScene(cc.TransitionFlipX.create(2, scene));
    }

    const item1 = cc.MenuItemFont.create("replaceScene");
    item1.registerScriptTapHandler(onReplaceScene);
    const item2 = cc.MenuItemFont.create("replaceScene w/transition");
    item2.registerScriptTapHandler(onReplaceSceneTran);
    const item3 = cc.MenuItemFont.create("Go Back");
    item3.registerScriptTapHandler(onGoBack);
    const menu = cc.Menu.create(item1, item2, item3);
    menu.alignItemsVertically();

    ret.addChild(menu);

    const s = cc.Director.getInstance().getWinSize();
    const sprite = cc.Sprite.create(s_pPathGrossini);
    ret.addChild(sprite);
    sprite.setPosition(cc.p(s.width - 40, s.height / 2));
    const rotate = cc.RotateBy.create(2, 360);
    const repeat_action = cc.RepeatForever.create(rotate);
    sprite.runAction(repeat_action);

    return ret;
};

// SceneTestLayer3
SceneTestLayer3 = function() {
    const ret = cc.LayerColor.create(cc.c4b(0, 0, 255, 255));
    const s = cc.Director.getInstance().getWinSize();

    function item0Clicked(tag, pSender) {
        const newScene = cc.Scene.create();
        newScene.addChild(SceneTestLayer3());
        cc.Director.getInstance().pushScene(cc.TransitionFade.create(0.5, newScene, cc.c3b(0, 255, 255)));
    }

    function item1Clicked(tag, pSender) {
        cc.Director.getInstance().popScene();
    }

    function item2Clicked(tag, pSender) {
        cc.Director.getInstance().popToRootScene();
    }

    const item0 = cc.MenuItemFont.create("Touch to pushScene (self)");
    item0.registerScriptTapHandler(item0Clicked);
    const item1 = cc.MenuItemFont.create("Touch to popScene");
    item1.registerScriptTapHandler(item1Clicked);
    const item2 = cc.MenuItemFont.create("Touch to popToRootScene");
    item2.registerScriptTapHandler(item2Clicked);

    const menu = cc.Menu.create(item0, item1, item2);
    ret.addChild(menu);
    menu.alignItemsVertically();

    const sprite = cc.Sprite.create(s_pPathGrossini);
    ret.addChild(sprite);
    sprite.setPosition(cc.p(s.width / 2, 40));
    const rotate = cc.RotateBy.create(2, 360);
    const repeatAction = cc.RepeatForever.create(rotate);
    sprite.runAction(repeatAction);
    return ret;
};

function SceneTestMain() {
    console.log("SceneTestMain");
    const scene = cc.Scene.create();
    const layer = SceneTestLayer1();
    scene.addChild(layer, 0);
    scene.addChild(CreateBackMenuItem());
    return scene;
}

module.exports = function SceneTest() {
    console.log('SceneTest');
    return SceneTestMain();
}