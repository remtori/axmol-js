const {
    s_arialPath,
    s_thonburiPath,
    s_pPathB1,
    s_pPathB2,
    s_pPathR1,
    s_pPathR2,
    s_pPathF1,
    s_pPathF2,
} = require("./testResource");
const { createTestMenu } = require('./mainMenu');

exports.AX_CONTENT_SCALE_FACTOR = function () {
    return cc.Director.getInstance().getContentScaleFactor();
};

exports.AX_POINT_PIXELS_TO_POINTS = function (pixels) {
    return cc.p(
        pixels.x / AX_CONTENT_SCALE_FACTOR(),
        pixels.y / AX_CONTENT_SCALE_FACTOR()
    );
};

exports.AX_POINT_POINTS_TO_PIXELS = function (points) {
    return cc.p(
        points.x * AX_CONTENT_SCALE_FACTOR(),
        points.y * AX_CONTENT_SCALE_FACTOR()
    );
};

exports.cclog = function (...args) {
    console.log(...args);
};

const Helper = new (class {
    index = 1;
    createFunctionTable = null;
    currentLayer = null;
    titleLabel = null;
    subtitleLabel = null;
    restartTestItem = null;

    nextAction() {
        this.index = this.index + 1;
        if (this.index >= this.createFunctionTable.length) {
            this.index = 0;
        }

        return this.newScene();
    }

    backAction() {
        this.index = this.index - 1;
        if (this.index == -1) {
            this.index = this.createFunctionTable.length - 1;
        }

        return this.newScene();
    }

    restartAction() {
        return this.newScene();
    }

    newScene() {
        let scene;
        if (this.usePhysics) {
            scene = cc.Scene.createWithPhysics();
        } else {
            scene = cc.Scene.create();
        }

        this.currentLayer = this.createFunctionTable[this.index]();
        scene.addChild(this.currentLayer);
        scene.addChild(CreateBackMenuItem());

        cc.Director.getInstance().replaceScene(scene);
    }

    initWithLayer(layer) {
        this.currentLayer = layer;

        const size = cc.Director.getInstance().getGLView().getVisibleRect();
        this.titleLabel = cc.Label.createWithTTF("", s_arialPath, 28);
        this.titleLabel.setAnchorPoint(cc.p(0.5, 0.5));
        layer.addChild(this.titleLabel, 1);
        this.titleLabel.setPosition(size.width / 2, size.height - 50);

        this.subtitleLabel = cc.Label.createWithTTF("", s_thonburiPath, 16);
        this.subtitleLabel.setAnchorPoint(cc.p(0.5, 0.5));
        layer.addChild(this.subtitleLabel, 1);
        this.subtitleLabel.setPosition(size.width / 2, size.height - 80);

        // menu
        const item1 = cc.MenuItemImage.create(s_pPathB1, s_pPathB2, this.backAction.bind(this));
        const item2 = cc.MenuItemImage.create(s_pPathR1, s_pPathR2, this.restartAction.bind(this));
        const item3 = cc.MenuItemImage.create(s_pPathF1, s_pPathF2, this.nextAction.bind(this));
        this.restartTestItem = item2;

        const menu = cc.Menu.create();
        menu.addChild(item1);
        menu.addChild(item2);
        menu.addChild(item3);
        menu.setPosition(cc.p(0, 0));
        item1.setPosition(
            cc.p(
                size.width / 2 - item2.getContentSize().width * 2,
                size.y + item2.getContentSize().height / 2
            )
        );
        item2.setPosition(
            cc.p(size.width / 2, size.y + item2.getContentSize().height / 2)
        );
        item3.setPosition(
            cc.p(
                size.width / 2 + item2.getContentSize().width * 2,
                size.y + item2.getContentSize().height / 2
            )
        );
        layer.addChild(menu, 1);

        const background = cc.Layer.create();
        layer.addChild(background, -10);
    }
});
exports.Helper = Helper;

// back menu callback
function MainMenuCallback() {
    const scene = cc.Scene.create();
    scene.addChild(createTestMenu());
    Helper.usePhysics = false;
    cc.Director.getInstance().getRenderer().setDepthTest(false);
    cc.Director.getInstance().replaceScene(scene);
}

// add the menu item for back to main menu
function CreateBackMenuItem() {
    const label = cc.Label.createWithTTF("MainMenu", s_arialPath, 20);
    label.setAnchorPoint(cc.p(0.5, 0.5));
    const MenuItem = cc.MenuItemLabel.create(label, MainMenuCallback);

    const s = cc.Director.getInstance().getGLView().getVisibleRect();
    const Menu = cc.Menu.create();
    Menu.addChild(MenuItem);
    Menu.setPosition(cc.p(0, 0));
    MenuItem.setPosition(s.width - 50, s.y + 25);

    return Menu;
}
exports.CreateBackMenuItem = CreateBackMenuItem;

exports.createTestLayer = function (title, subtitle) {
    const layer = cc.Layer.create();
    Helper.initWithLayer(layer);
    const titleStr = title || "No title";
    const subTitleStr = subtitle || "";
    Helper.titleLabel.setString(titleStr);
    Helper.subtitleLabel.setString(subTitleStr);
    return layer;
};

exports.TestCastScene = {
    index: 1,
    createFunctionTable: null,
    titleLabel: null,
    subtitleLabel: null,

    nextAction() {
        this.index = this.index + 1;
        if (this.index >= this.createFunctionTable.length) {
            this.index = 0;
        }

        return this.newScene();
    },

    backAction() {
        this.index = this.index - 1;
        if (this.index == -1) {
            this.index = this.createFunctionTable.length - 1;
        }

        return this.newScene();
    },

    restartAction() {
        return this.newScene();
    },

    newScene() {
        const scene = this.createFunctionTable[this.index]();
        scene.addChild(CreateBackMenuItem());
        cc.Director.getInstance().replaceScene(scene);
    },

    initWithLayer(scene) {
        const size = cc.Director.getInstance().getVisibleSize();
        const origin = cc.Director.getInstance().getVisibleOrigin();

        this.titleLabel = cc.Label.createWithTTF("", s_arialPath, 28);
        this.titleLabel.setAnchorPoint(cc.p(0.5, 0.5));
        scene.addChild(this.titleLabel, 1);
        this.titleLabel.setPosition(origin.x + size.width / 2, origin.y + size.height - 50);

        this.subtitleLabel = cc.Label.createWithTTF("", s_thonburiPath, 16);
        this.subtitleLabel.setAnchorPoint(cc.p(0.5, 0.5));
        scene.addChild(this.subtitleLabel, 1);
        this.subtitleLabel.setPosition(origin.x + size.width / 2, origin.y + size.height - 80);

        // menu
        const item1 = cc.MenuItemImage.create(s_pPathB1, s_pPathB2, this.backAction);
        const item2 = cc.MenuItemImage.create(s_pPathR1, s_pPathR2, this.restartAction);
        const item3 = cc.MenuItemImage.create(s_pPathF1, s_pPathF2, this.nextAction);

        const menu = cc.Menu.create();
        menu.addChild(item1);
        menu.addChild(item2);
        menu.addChild(item3);
        menu.setPosition(cc.p(0, 0));
        item1.setPosition(cc.p(size.width / 2 - item2.getContentSize().width * 2, size.y + item2.getContentSize().height / 2));
        item2.setPosition(cc.p(size.width / 2, size.y + item2.getContentSize().height / 2));
        item3.setPosition(cc.p(size.width / 2 + item2.getContentSize().width * 2, size.y + item2.getContentSize().height / 2));
        scene.addChild(menu, 1);

        const background = cc.Layer.create();
        scene.addChild(background, -10);
    },
};
