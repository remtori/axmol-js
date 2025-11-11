const { s_MenuItem, s_SendScore, s_PressSendScore } = require('../testResource');
const { Helper, CreateBackMenuItem } = require('../helper');

const kTagMenu = 1;
const kTagMenu0 = 0;
const kTagMenu1 = 1;

const MID_CALLBACK = 1000;
const MID_CALLBACK2 = 1001;
const MID_DISABLED = 1002;
const MID_ENABLE = 1003;
const MID_CONFIG = 1004;
const MID_QUIT = 1005;
const MID_OPACITY = 1006;
const MID_ALIGN = 1007;
const MID_CALLBACK3 = 1008;
const MID_BACKCALLBACK = 1009;

// MenuLayerMainMenu
function MenuLayerMainMenu() {
    let m_disabledItem = null;

    const ret = cc.Layer.create();

    // Font Item
    const spriteNormal = cc.Sprite.create(s_MenuItem, cc.rect(0, 23 * 2, 115, 23));
    const spriteSelected = cc.Sprite.create(s_MenuItem, cc.rect(0, 23 * 1, 115, 23));
    const spriteDisabled = cc.Sprite.create(s_MenuItem, cc.rect(0, 23 * 0, 115, 23));

    const item1 = cc.MenuItemSprite.create(spriteNormal, spriteSelected, spriteDisabled);

    function menuCallback(sender) {
        console.log("menuCallback...");
        ret.getParent().switchTo(1, false);
    }

    item1.registerScriptTapHandler(menuCallback);

    // Image Item
    function menuCallback2(sender) {
        ret.getParent().switchTo(2, false);
    }

    const item2 = cc.MenuItemImage.create(s_SendScore, s_PressSendScore);
    item2.registerScriptTapHandler(menuCallback2);

    let schedulerEntry = null;
    const scheduler = cc.Director.getInstance().getScheduler();

    function allowTouches(dt) {
        const pDirector = cc.Director.getInstance();
        if (schedulerEntry !== null) {
            scheduler.unscheduleScriptEntry(schedulerEntry);
            schedulerEntry = null;
        }
        console.log("TOUCHES ALLOWED AGAIN");
    }

    function menuCallbackDisabled(sender) {
        // hijack all touch events for 5 seconds
        const pDirector = cc.Director.getInstance();
        schedulerEntry = scheduler.scheduleScriptFunc(allowTouches, 5, false);
        console.log("TOUCHES DISABLED FOR 5 SECONDS");
    }

    // Label Item (LabelAtlas)
    const labelAtlas = cc.LabelAtlas._create("0123456789", "fonts/labelatlas.png", 16, 24, ".".charCodeAt(0));
    const item3 = cc.MenuItemLabel.create(labelAtlas);
    item3.registerScriptTapHandler(menuCallbackDisabled);
    item3.setDisabledColor(cc.c3b(32, 32, 64));
    item3.setColor(cc.c3b(200, 200, 255));

    function menuCallbackEnable(sender) {
        m_disabledItem.setEnabled(!m_disabledItem.isEnabled());
    }

    // Font Item
    const item4 = cc.MenuItemFont.create("I toggle enable items");
    item4.registerScriptTapHandler(menuCallbackEnable);

    item4.setFontSizeObj(20);
    cc.MenuItemFont.setFontName("Marker Felt");

    function menuCallbackConfig(sender) {
        ret.getParent().switchTo(3, false);
    }

    // Label Item (cc.LabelBMFont)
    const label = cc.Label.createWithBMFont("fonts/bitmapFontTest3.fnt", "configuration");
    label.setAnchorPoint(cc.p(0.5, 0.5));
    const item5 = cc.MenuItemLabel.create(label);
    item5.registerScriptTapHandler(menuCallbackConfig);

    // Testing issue #500
    item5.setScale(0.8);

    // Events
    cc.MenuItemFont.setFontName("Marker Felt");

    function menuCallbackBugsTest(pSender) {
        ret.getParent().switchTo(4, false);
    }

    // Bugs Item
    const item6 = cc.MenuItemFont.create("Bugs");
    item6.registerScriptTapHandler(menuCallbackBugsTest);

    function onQuit(sender) {
        console.log("onQuit item is clicked.");
    }

    // Font Item
    const item7 = cc.MenuItemFont.create("Quit");
    item7.registerScriptTapHandler(onQuit);

    function menuMovingCallback(pSender) {
        ret.getParent().switchTo(5, false);
    }

    const item8 = cc.MenuItemFont.create("Remove menu item when moving");
    item8.registerScriptTapHandler(menuMovingCallback);

    const color_action = cc.TintBy.create(0.5, 0, -255, -255);
    const color_back = color_action.reverse();
    const seq = cc.Sequence.create(color_action, color_back);
    item7.runAction(cc.RepeatForever.create(seq));

    const menu = cc.Menu.create();

    menu.addChild(item1);
    menu.addChild(item2);
    menu.addChild(item3);
    menu.addChild(item4);
    menu.addChild(item5);
    menu.addChild(item6);
    menu.addChild(item7);
    menu.addChild(item8);

    menu.alignItemsVertically();

    // elastic effect
    const s = cc.Director.getInstance().getWinSize();

    const pArray = menu.getChildren();
    const len = pArray.length;

    for (let i = 0; i < len; i++) {
        const child = pArray[i];
        if (child === null) {
            break;
        }

        const [dstPointX, dstPointY] = child.getPosition();
        let offset = s.width / 2 + 50;
        if (i % 2 === 0) {
            offset = 0 - offset;
        }
        child.setPosition(cc.p(dstPointX + offset, dstPointY));
        child.runAction(cc.EaseElasticOut.create(cc.MoveBy.create(2, cc.p(dstPointX - offset, 0)), 0.35));
    }

    m_disabledItem = item3;
    item3.retain();

    m_disabledItem.setEnabled(false);

    ret.addChild(menu);
    menu.setPosition(cc.p(s.width / 2, s.height / 2));

    function onNodeEvent(event) {
        if (event === "exit") {
            if (schedulerEntry !== null) {
                scheduler.unscheduleScriptEntry(schedulerEntry);
            }
            if (m_disabledItem !== null) {
                // m_disabledItem.release(); // might not be needed in JS
            }
        }
    }

    ret.registerScriptHandler(onNodeEvent);

    return ret;
}

// MenuLayer2 (simplified for this initial port)
function MenuLayer2() {
    const ret = cc.Layer.create();
    let m_centeredMenu = null;
    let m_alignedH = false;

    Helper.initWithLayer(ret);
    Helper.titleLabel.setString("Menu Layer 2");

    return ret;
}

module.exports = function MenuTest() {
    console.log('MenuTest');
    const scene = cc.Scene.create();

    Helper.createFunctionTable = [
        MenuLayerMainMenu,
        MenuLayer2,
    ];
    Helper.index = 0;

    scene.addChild(MenuLayerMainMenu());
    scene.addChild(CreateBackMenuItem());

    return scene;
}