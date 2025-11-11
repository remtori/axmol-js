const { CreateBackMenuItem } = require('./helper');

module.exports = function Cocos2dxTests() {
    console.log("Cocos2dxTests");

    sys.sessionStorage.setItem("__defaultResourceRootPath__", jsb.fileUtils.getDefaultResourceRootPath() + 'cocos2dx-tests');
    cc.director.restart();

    // Temp scene
    const scene = cc.Scene.create();
    const layer = new WrappedLayer();
    scene.addChild(layer);
    scene.addChild(CreateBackMenuItem());
    return scene;
};

class WrappedLayer extends cc.LayerGradient {
    constructor() {
        super(cc.color(0, 0, 0, 255), cc.color(0x46, 0x82, 0xb4, 255));
    }
}
