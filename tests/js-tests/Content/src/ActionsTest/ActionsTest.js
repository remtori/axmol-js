const { s_pPathGrossini, s_pPathSister1, s_pPathSister2 } = require('../testResource');
const { Helper, CreateBackMenuItem } = require('../helper');

const size = cc.Director.getInstance().getWinSize();

let grossini = null;
let tamara = null;
let kathia = null;

function initWithLayer(layer) {
    grossini = cc.Sprite.create(s_pPathGrossini);
    tamara = cc.Sprite.create(s_pPathSister1);
    kathia = cc.Sprite.create(s_pPathSister2);

    layer.addChild(grossini, 1);
    layer.addChild(tamara, 2);
    layer.addChild(kathia, 3);

    grossini.setPosition(cc.p(size.width / 2, size.height / 3));
    tamara.setPosition(cc.p(size.width / 2, 2 * size.height / 3));
    kathia.setPosition(cc.p(size.width / 2, size.height / 2));

    Helper.initWithLayer(layer);
}

function centerSprites(numberOfSprites) {
    if (numberOfSprites == 0) {
        tamara.setVisible(false);
        kathia.setVisible(false);
        grossini.setVisible(false);
    } else if (numberOfSprites == 1) {
        tamara.setVisible(false);
        kathia.setVisible(false);
        grossini.setPosition(cc.p(size.width / 2, size.height / 2));
    } else if (numberOfSprites == 2) {
        kathia.setPosition(cc.p(size.width / 3, size.height / 2));
        tamara.setPosition(cc.p(2 * size.width / 3, size.height / 2));
        grossini.setVisible(false);
    } else if (numberOfSprites == 3) {
        grossini.setPosition(cc.p(size.width / 2, size.height / 2));
        tamara.setPosition(cc.p(size.width / 4, size.height / 2));
        kathia.setPosition(cc.p(3 * size.width / 4, size.height / 2));
    }
}

function alignSpritesLeft(numberOfSprites) {
    if (numberOfSprites == 1) {
        tamara.setVisible(false);
        kathia.setVisible(false);
        grossini.setPosition(cc.p(60, size.height / 2));
    } else if (numberOfSprites == 2) {
        kathia.setPosition(cc.p(60, size.height / 3));
        tamara.setPosition(cc.p(60, 2 * size.height / 3));
        grossini.setVisible(false);
    } else if (numberOfSprites == 3) {
        grossini.setPosition(cc.p(60, size.height / 2));
        tamara.setPosition(cc.p(60, 2 * size.height / 3));
        kathia.setPosition(cc.p(60, size.height / 3));
    }
}

function ActionManual() {
    const layer = cc.Layer.create();
    initWithLayer(layer);

    tamara.setScaleX(2.5);
    tamara.setScaleY(-1.0);
    tamara.setPosition(cc.p(100, 70));
    tamara.setOpacity(128);

    grossini.setRotation(120);
    grossini.setPosition(cc.p(size.width / 2, size.height / 2));
    grossini.setColor(cc.c3b(255, 0, 0));

    kathia.setPosition(cc.p(size.width - 100, size.height / 2));
    kathia.setColor(cc.c3b(0, 0, 255));

    Helper.subtitleLabel.setString('Manual Transformation');
    return layer;
}

function ActionMove() {
    const layer = cc.Layer.create();
    initWithLayer(layer);

    centerSprites(3);
    const actionBy = cc.MoveBy.create(2, cc.p(80, 80));
    const actionByBack = actionBy.reverse();

    tamara.runAction(cc.MoveTo.create(2, cc.p(size.width - 40, size.height - 40)));
    grossini.runAction(cc.Sequence.create(actionBy, actionByBack));
    kathia.runAction(cc.MoveTo.create(1, cc.p(40, 40)));

    Helper.subtitleLabel.setString('MoveTo / MoveBy');
    return layer;
}

function ActionScale() {
    const layer = cc.Layer.create();
    initWithLayer(layer);

    centerSprites(3);

    const actionTo = cc.ScaleTo.create(2.0, 0.5);
    const actionBy = cc.ScaleBy.create(2.0, 1.0, 10.0);
    const actionBy2 = cc.ScaleBy.create(2.0, 5.0, 1.0);

    grossini.runAction(actionTo);
    tamara.runAction(cc.Sequence.create(actionBy, actionBy.reverse()));
    kathia.runAction(cc.Sequence.create(actionBy2, actionBy2.reverse()));

    Helper.subtitleLabel.setString('ScaleTo / ScaleBy');
    return layer;
}

function ActionRotate() {
    const layer = cc.Layer.create();
    initWithLayer(layer);

    centerSprites(3);

    const actionTo = cc.RotateTo.create(2, 45);
    const actionTo2 = cc.RotateTo.create(2, -45);
    const actionTo0 = cc.RotateTo.create(2, 0);
    tamara.runAction(cc.Sequence.create(actionTo, actionTo0));

    const actionBy = cc.RotateBy.create(2, 360);
    const actionByBack = actionBy.reverse();
    grossini.runAction(cc.Sequence.create(actionBy, actionByBack));

    const action0Retain = cc.RotateTo.create(2, 0);
    kathia.runAction(cc.Sequence.create(actionTo2, action0Retain));

    Helper.subtitleLabel.setString('RotateTo / RotateBy');
    return layer;
}

module.exports = function ActionsTest() {
    console.log('ActionsTest');
    const scene = cc.Scene.create();

    Helper.createFunctionTable = [
        ActionManual,
        ActionMove,
        ActionScale,
        ActionRotate,
    ];
    Helper.index = 0;

    scene.addChild(ActionManual());
    scene.addChild(CreateBackMenuItem());

    return scene;
}
