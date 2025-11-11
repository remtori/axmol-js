const { Helper, CreateBackMenuItem } = require('../helper');

const size = cc.Director.getInstance().getWinSize();
const kTagTileMap = 1;
const kTagSpriteBatchNode = 1;
const kTagNode = 2;
const kTagAnimation1 = 1;
const kTagSpriteLeft = 2;
const kTagSpriteRight = 2;

const kTagSprite1 = 0;
const kTagSprite2 = 1;
const kTagSprite3 = 2;
const kTagSprite4 = 3;
const kTagSprite5 = 4;
const kTagSprite6 = 5;
const kTagSprite7 = 6;
const kTagSprite8 = 7;

let testLayer = null;
let entry = null;

// Sprite1 Test
const Sprite1 = {
    addNewSpriteWithCoords(layer, point) {
        const idx = Math.floor(Math.random() * 1400 / 100);
        const x = Math.floor((idx % 5) * 85);
        const y = Math.floor(idx / 5) * 121;

        const sprite = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(x, y, 85, 121));
        layer.addChild(sprite);

        sprite.setPosition(cc.p(point.x, point.y));

        let action = null;
        const random = Math.random();
        console.log("random = " + random);

        if (random < 0.20) {
            action = cc.ScaleBy.create(3, 2);
        } else if (random < 0.40) {
            action = cc.RotateBy.create(3, 360);
        } else if (random < 0.60) {
            action = cc.Blink.create(1, 3);
        } else if (random < 0.8) {
            action = cc.TintBy.create(2, 0, -255, -255);
        } else {
            action = cc.FadeOut.create(2);
        }

        const action_back = action.reverse();
        const seq = cc.Sequence.create(action, action_back);

        sprite.runAction(cc.RepeatForever.create(seq));
    },

    onTouchesEnd(touches, event) {
        for (let i = 0; i < touches.length; i++) {
            const location = touches[i].getLocation();
            Sprite1.addNewSpriteWithCoords(Helper.currentLayer, location);
        }
    },

    create() {
        console.log("sprite1");
        const layer = cc.Layer.create();
        Helper.initWithLayer(layer);
        Sprite1.addNewSpriteWithCoords(layer, cc.p(size.width / 2, size.height / 2));

        const listener = cc.EventListenerTouchAllAtOnce.create();
        listener.registerScriptHandler(Sprite1.onTouchesEnd, cc.Handler.EVENT_TOUCHES_ENDED);
        const eventDispatcher = layer.getEventDispatcher();
        eventDispatcher.addEventListenerWithSceneGraphPriority(listener, layer);

        Helper.titleLabel.setString("Sprite (tap screen)");

        return layer;
    }
};

// SpriteBatchNode1 Test
const SpriteBatchNode1 = {
    addNewSpriteWithCoords(layer, point) {
        const BatchNode = layer.getChildByTag(kTagSpriteBatchNode);
        const idx = Math.floor(Math.random() * 1400 / 100);
        const x = Math.floor((idx % 5) * 85);
        const y = Math.floor(idx / 5) * 121;

        const sprite = cc.Sprite.createWithTexture(BatchNode.getTexture(), cc.rect(x, y, 85, 121));
        layer.addChild(sprite);

        sprite.setPosition(cc.p(point.x, point.y));

        let action = null;
        const random = Math.random();
        console.log("random = " + random);

        if (random < 0.20) {
            action = cc.ScaleBy.create(3, 2);
        } else if (random < 0.40) {
            action = cc.RotateBy.create(3, 360);
        } else if (random < 0.60) {
            action = cc.Blink.create(1, 3);
        } else if (random < 0.8) {
            action = cc.TintBy.create(2, 0, -255, -255);
        } else {
            action = cc.FadeOut.create(2);
        }

        const action_back = action.reverse();
        const seq = cc.Sequence.create(action, action_back);

        sprite.runAction(cc.RepeatForever.create(seq));
    },

    onTouchesEnd(touches, event) {
        for (let i = 0; i < touches.length; i++) {
            const location = touches[i].getLocation();
            SpriteBatchNode1.addNewSpriteWithCoords(Helper.currentLayer, location);
        }
    },

    create() {
        const layer = cc.Layer.create();
        Helper.initWithLayer(layer);
        const BatchNode = cc.SpriteBatchNode.create("Images/grossini_dance_atlas.png", 50);
        layer.addChild(BatchNode, 0, kTagSpriteBatchNode);

        SpriteBatchNode1.addNewSpriteWithCoords(layer, cc.p(size.width / 2, size.height / 2));

        const listener = cc.EventListenerTouchAllAtOnce.create();
        listener.registerScriptHandler(SpriteBatchNode1.onTouchesEnd, cc.Handler.EVENT_TOUCHES_ENDED);
        const eventDispatcher = layer.getEventDispatcher();
        eventDispatcher.addEventListenerWithSceneGraphPriority(listener, layer);

        Helper.titleLabel.setString("SpriteBatchNode (tap screen)");

        return layer;
    }
};

// SpriteColorOpacity Test
const SpriteColorOpacity = {
    entry: null,

    setLayerSprite(layer) {
        const sprite1 = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(85 * 0, 121 * 1, 85, 121));
        const sprite2 = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(85 * 1, 121 * 1, 85, 121));
        const sprite3 = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(85 * 2, 121 * 1, 85, 121));
        const sprite4 = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(85 * 3, 121 * 1, 85, 121));

        const sprite5 = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(85 * 0, 121 * 1, 85, 121));
        const sprite6 = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(85 * 1, 121 * 1, 85, 121));
        const sprite7 = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(85 * 2, 121 * 1, 85, 121));
        const sprite8 = cc.Sprite.create("Images/grossini_dance_atlas.png", cc.rect(85 * 3, 121 * 1, 85, 121));

        const s = cc.Director.getInstance().getWinSize();
        sprite1.setPosition(cc.p((s.width / 5) * 1, (s.height / 3) * 1));
        sprite2.setPosition(cc.p((s.width / 5) * 2, (s.height / 3) * 1));
        sprite3.setPosition(cc.p((s.width / 5) * 3, (s.height / 3) * 1));
        sprite4.setPosition(cc.p((s.width / 5) * 4, (s.height / 3) * 1));
        sprite5.setPosition(cc.p((s.width / 5) * 1, (s.height / 3) * 2));
        sprite6.setPosition(cc.p((s.width / 5) * 2, (s.height / 3) * 2));
        sprite7.setPosition(cc.p((s.width / 5) * 3, (s.height / 3) * 2));
        sprite8.setPosition(cc.p((s.width / 5) * 4, (s.height / 3) * 2));

        const action = cc.FadeIn.create(2);
        const action_back = action.reverse();
        const fade = cc.RepeatForever.create(cc.Sequence.create(action, action_back));

        const tintred = cc.TintBy.create(2, 0, -255, -255);
        const tintred_back = tintred.reverse();
        const red = cc.RepeatForever.create(cc.Sequence.create(tintred, tintred_back));

        const tintgreen = cc.TintBy.create(2, -255, 0, -255);
        const tintgreen_back = tintgreen.reverse();
        const green = cc.RepeatForever.create(cc.Sequence.create(tintgreen, tintgreen_back));

        const tintblue = cc.TintBy.create(2, -255, -255, 0);
        const tintblue_back = tintblue.reverse();
        const blue = cc.RepeatForever.create(cc.Sequence.create(tintblue, tintblue_back));

        sprite5.runAction(red);
        sprite6.runAction(green);
        sprite7.runAction(blue);
        sprite8.runAction(fade);

        layer.addChild(sprite1, 0, kTagSprite1);
        layer.addChild(sprite2, 0, kTagSprite2);
        layer.addChild(sprite3, 0, kTagSprite3);
        layer.addChild(sprite4, 0, kTagSprite4);
        layer.addChild(sprite5, 0, kTagSprite5);
        layer.addChild(sprite6, 0, kTagSprite6);
        layer.addChild(sprite7, 0, kTagSprite7);
        layer.addChild(sprite8, 0, kTagSprite8);
    },

    create() {
        const layer = cc.Layer.create();
        Helper.initWithLayer(layer);

        SpriteColorOpacity.setLayerSprite(layer);

        Helper.titleLabel.setString("Sprite: Color & Opacity");

        return layer;
    }
};

module.exports = function SpriteTest() {
    console.log('SpriteTest');
    const scene = cc.Scene.create();

    Helper.createFunctionTable = [
        Sprite1.create,
        SpriteBatchNode1.create,
        SpriteColorOpacity.create,
    ];
    Helper.index = 0;

    scene.addChild(Sprite1.create());
    scene.addChild(CreateBackMenuItem());

    return scene;
}