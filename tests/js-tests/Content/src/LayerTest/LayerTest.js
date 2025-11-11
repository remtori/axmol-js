const { Helper, CreateBackMenuItem } = require('../helper');

const scheduler = cc.Director.getInstance().getScheduler();
const kTagLayer = 1;

function createLayerDemoLayer(title, subtitle) {
    const layer = cc.Layer.create();
    Helper.initWithLayer(layer);
    const titleStr = title == null ? "No title" : title;
    const subTitleStr = subtitle == null ? "" : subtitle;
    Helper.titleLabel.setString(titleStr);
    Helper.subtitleLabel.setString(subTitleStr);

    return layer;
}

// Cascading support extensions
function setEnableRecursiveCascading(node, enable) {
    if (node == null) {
        return;
    }

    if (node.setCascadeColorEnabled != null && node.setCascadeOpacityEnabled != null) {
        node.setCascadeColorEnabled(enable);
        node.setCascadeOpacityEnabled(enable);
    }

    const children = node.getChildren();
    if (children == null) {
        console.log("children is null");
        return;
    }

    const len = children.length;
    for (let i = 0; i < len; i++) {
        setEnableRecursiveCascading(children[i], enable);
    }
}

// LayerTestCascadingOpacityA
function LayerTestCascadingOpacityA() {
    const ret = createLayerDemoLayer("Layer: cascading opacity");
    const s = cc.Director.getInstance().getWinSize();
    const layer1 = cc.Layer.create();

    const sister1 = cc.Sprite.create("Images/grossinis_sister1.png");
    const sister2 = cc.Sprite.create("Images/grossinis_sister2.png");
    const label = cc.Label.createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    label.setAnchorPoint(cc.p(0.5, 0.5));

    layer1.addChild(sister1);
    layer1.addChild(sister2);
    layer1.addChild(label);
    ret.addChild(layer1, 0, kTagLayer);

    sister1.setPosition(cc.p(s.width * 1 / 3, s.height / 2));
    sister2.setPosition(cc.p(s.width * 2 / 3, s.height / 2));
    label.setPosition(cc.p(s.width / 2, s.height / 2));

    layer1.runAction(cc.RepeatForever.create(cc.Sequence.create(
        cc.FadeTo.create(4, 0),
        cc.FadeTo.create(4, 255),
        cc.DelayTime.create(1)
    )));

    sister1.runAction(cc.RepeatForever.create(cc.Sequence.create(
        cc.FadeTo.create(2, 0),
        cc.FadeTo.create(2, 255),
        cc.FadeTo.create(2, 0),
        cc.FadeTo.create(2, 255),
        cc.DelayTime.create(1)
    )));

    // Enable cascading in scene
    setEnableRecursiveCascading(ret, true);
    return ret;
}

// LayerTestCascadingOpacityB
function LayerTestCascadingOpacityB() {
    const ret = createLayerDemoLayer("CCLayerColor: cascading opacity");

    const s = cc.Director.getInstance().getWinSize();
    const layer1 = cc.LayerColor.create(cc.c4b(192, 0, 0, 255), s.width, s.height / 2);
    layer1.setCascadeColorEnabled(false);

    layer1.setPosition(cc.p(0, s.height / 2));

    const sister1 = cc.Sprite.create("Images/grossinis_sister1.png");
    const sister2 = cc.Sprite.create("Images/grossinis_sister2.png");
    const label = cc.Label.createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    label.setAnchorPoint(cc.p(0.5, 0.5));

    layer1.addChild(sister1);
    layer1.addChild(sister2);
    layer1.addChild(label);
    ret.addChild(layer1, 0, kTagLayer);

    sister1.setPosition(cc.p(s.width * 1 / 3, 0));
    sister2.setPosition(cc.p(s.width * 2 / 3, 0));
    label.setPosition(cc.p(s.width / 2, 0));

    layer1.runAction(cc.RepeatForever.create(cc.Sequence.create(
        cc.FadeTo.create(4, 0),
        cc.FadeTo.create(4, 255),
        cc.DelayTime.create(1)
    )));

    sister1.runAction(cc.RepeatForever.create(cc.Sequence.create(
        cc.FadeTo.create(2, 0),
        cc.FadeTo.create(2, 255),
        cc.FadeTo.create(2, 0),
        cc.FadeTo.create(2, 255),
        cc.DelayTime.create(1)
    )));

    // Enable cascading in scene
    setEnableRecursiveCascading(ret, true);
    return ret;
}

// LayerTestCascadingOpacityC
function LayerTestCascadingOpacityC() {
    const ret = createLayerDemoLayer("LayerColor: non-cascading opacity");

    const s = cc.Director.getInstance().getWinSize();
    const layer1 = cc.LayerColor.create(cc.c4b(192, 0, 0, 255), s.width, s.height / 2);
    layer1.setCascadeColorEnabled(false);
    layer1.setCascadeOpacityEnabled(false);

    layer1.setPosition(cc.p(0, s.height / 2));

    const sister1 = cc.Sprite.create("Images/grossinis_sister1.png");
    const sister2 = cc.Sprite.create("Images/grossinis_sister2.png");
    const label = cc.Label.createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    label.setAnchorPoint(cc.p(0.5, 0.5));

    layer1.addChild(sister1);
    layer1.addChild(sister2);
    layer1.addChild(label);
    ret.addChild(layer1, 0, kTagLayer);

    sister1.setPosition(cc.p(s.width * 1 / 3, 0));
    sister2.setPosition(cc.p(s.width * 2 / 3, 0));
    label.setPosition(cc.p(s.width / 2, 0));

    layer1.runAction(cc.RepeatForever.create(cc.Sequence.create(
        cc.FadeTo.create(4, 0),
        cc.FadeTo.create(4, 255),
        cc.DelayTime.create(1)
    )));

    sister1.runAction(cc.RepeatForever.create(cc.Sequence.create(
        cc.FadeTo.create(2, 0),
        cc.FadeTo.create(2, 255),
        cc.FadeTo.create(2, 0),
        cc.FadeTo.create(2, 255),
        cc.DelayTime.create(1)
    )));

    return ret;
}

// LayerTestCascadingColorA
function LayerTestCascadingColorA() {
    const ret = createLayerDemoLayer("Layer: cascading color");

    const s = cc.Director.getInstance().getWinSize();
    const layer1 = cc.Layer.create();

    const sister1 = cc.Sprite.create("Images/grossinis_sister1.png");
    const sister2 = cc.Sprite.create("Images/grossinis_sister2.png");
    const label = cc.Label.createWithBMFont("fonts/bitmapFontTest.fnt", "Test");
    label.setAnchorPoint(cc.p(0.5, 0.5));

    layer1.addChild(sister1);
    layer1.addChild(sister2);
    layer1.addChild(label);
    ret.addChild(layer1, 0, kTagLayer);

    sister1.setPosition(cc.p(s.width * 1 / 3, s.height / 2));
    sister2.setPosition(cc.p(s.width * 2 / 3, s.height / 2));
    label.setPosition(cc.p(s.width / 2, s.height / 2));

    layer1.runAction(cc.RepeatForever.create(cc.Sequence.create(
        cc.TintTo.create(6, 255, 0, 255),
        cc.TintTo.create(6, 255, 255, 255),
        cc.DelayTime.create(1)
    )));

    sister1.runAction(cc.RepeatForever.create(cc.Sequence.create(
        cc.TintTo.create(2, 255, 255, 0),
        cc.TintTo.create(2, 255, 255, 255),
        cc.TintTo.create(2, 0, 255, 255),
        cc.TintTo.create(2, 255, 255, 255),
        cc.DelayTime.create(1)
    )));

    // Enable cascading in scene
    setEnableRecursiveCascading(ret, true);
    return ret;
}

module.exports = function LayerTest() {
    console.log('LayerTest');
    const scene = cc.Scene.create();

    Helper.createFunctionTable = [
        LayerTestCascadingOpacityA,
        LayerTestCascadingOpacityB,
        LayerTestCascadingOpacityC,
        LayerTestCascadingColorA,
    ];
    Helper.index = 0;

    scene.addChild(LayerTestCascadingOpacityA());
    scene.addChild(CreateBackMenuItem());

    return scene;
}