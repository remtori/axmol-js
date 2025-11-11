const { s_pPathClose, s_arialPath } = require("./testResource");
const { VisibleRect } = require("./VisibleRect");

const LINE_SPACE = 40;

let audioEngineSupported = false;
const targetPlatform = cc.Application.getInstance().getTargetPlatform();
if (
    cc.PLATFORM_OS_WINDOWS == targetPlatform ||
    cc.PLATFORM_OS_MAC == targetPlatform ||
    cc.PLATFORM_OS_IPHONE == targetPlatform ||
    cc.PLATFORM_OS_IPAD == targetPlatform ||
    cc.PLATFORM_OS_ANDROID == targetPlatform
) {
    audioEngineSupported = true;
}

let assetManagerSupported = true;
if (targetPlatform == cc.PLATFORM_OS_TIZEN) {
    assetManagerSupported = false;
}

const _allTests = [
    { isSupported: true, name: 'Cocos2d-x v3 Tests', loadTest: () => require('./cocos2dx-tests') },
    { isSupported: true, name: 'ActionsTest', loadTest: () => require('./ActionsTest/ActionsTest') },
    { isSupported: true, name: 'LayerTest', loadTest: () => require('./LayerTest/LayerTest') },
    { isSupported: true, name: 'NodeTest', loadTest: () => require('./NodeTest/NodeTest') },
    { isSupported: true, name: 'SceneTest', loadTest: () => require('./SceneTest/SceneTest') },
    { isSupported: true, name: 'SpriteTest', loadTest: () => require('./SpriteTest/SpriteTest') },
    { isSupported: true, name: 'WasmTest', loadTest: () => require('./WasmTest/WasmTest') },
    { isSupported: true, name: 'Cocos2d-x Tests', loadTest: () => {
        sys.sessionStorage.setItem("__defaultResourceRootPath__", jsb.fileUtils.getDefaultResourceRootPath() + 'cocos2dx-tests');
        cc.director.restart();
    } },
    { isSupported: true, name: 'Zingplay Tests', loadTest: () => {
        sys.sessionStorage.setItem("__defaultResourceRootPath__", jsb.fileUtils.getDefaultResourceRootPath() + 'zp-tests');
        cc.director.restart();
    } },
];

const TESTS_COUNT = _allTests.length;

function createTestScene(nIdx) {
    cc.Director.getInstance().purgeCachedData();
    const testModule = _allTests[nIdx].loadTest();
    const scene = testModule();
    return scene;
}

exports.createTestMenu = function() {
    const menuLayer = new cc.LayerGradient(cc.color(0, 0, 0, 255), cc.color(0x46, 0x82, 0xb4, 255));
    menuLayer.setAnchorPoint(0.5, 0.5);

    function closeCallback() {
        cc.Director.getInstance().end();
    }

    function menuCallback(obj) {
        console.log('menuCallback', obj);
        const Idx = obj.getTag() - 10000;
        const testScene = createTestScene(Idx);
        if (testScene) {
            cc.Director.getInstance().replaceScene(testScene);
        }
    }

    // add close menu
    const s = cc.Director.getInstance().getWinSize();
    const closeItem = cc.MenuItemImage.create(s_pPathClose, s_pPathClose, closeCallback);
    closeItem.setAnchorPoint(1, 1);
    closeItem.setPosition(VisibleRect.rightTop());

    const closeMenu = cc.Menu.create();
    closeMenu.setPosition(0, 0);
    closeMenu.addChild(closeItem);
    menuLayer.addChild(closeMenu);

    // add menu items for tests
    const mainMenu = cc.Menu.create();
    for (let index = 0; index < TESTS_COUNT; index++) {
        const obj = _allTests[index];
        const testLabel = cc.Label.createWithTTF(obj.name, s_arialPath, 24);
        testLabel.setAnchorPoint(0.5, 0.5);

        const testMenuItem = cc.MenuItemLabel.create(testLabel, menuCallback);
        if (!obj.isSupported) {
            testMenuItem.setEnabled(false);
        }

        if (obj.name == 'Physics3DTest' && !cc.Physics3DComponent) {
            testMenuItem.setEnabled(false);
        }

        testMenuItem.setPosition(cc.p(s.width / 2, (s.height - (index) * LINE_SPACE)));
        console.log('add menu item', obj.name, testMenuItem);
        mainMenu.addChild(testMenuItem, index + 10000, index + 10000);
    }

    mainMenu.setContentSize(cc.size(s.width, (TESTS_COUNT + 1) * (LINE_SPACE)));
    mainMenu.setPosition(0, -LINE_SPACE * 5);
    menuLayer.addChild(mainMenu);

    // handling touch events
    // const listener = cc.EventListenerTouchOneByOne.create();
    // listener.registerScriptHandler()

    // const eventDispatcher = menuLayer.getEventDispatcher();
    // eventDispatcher.addEventListenerWithSceneGraphPriority(listener, menuLayer);

    return menuLayer;
}