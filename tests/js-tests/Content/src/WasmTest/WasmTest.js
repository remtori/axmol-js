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

function WasmAddTwo() {
    const ret = createLayerDemoLayer("WASM: Add two");
    const s = cc.Director.getInstance().getWinSize();

    const wasmData = jsb.fileUtils.getDataFromFile('WasmTest/add-two.wasm');
    console.log(wasmData);

    const wasmModule = new WebAssembly.Module(wasmData);
    console.log(wasmModule);
    const wasmInstance = new WebAssembly.Instance(wasmModule);
    console.log(wasmInstance);
    const addTwo = wasmInstance.exports.addTwo;
    console.log('addTwo(1, 2) = ', addTwo(1, 2));

    const label = cc.Label.create();
    label.setString('addTwo(1, 2) = ' + addTwo(1, 2));
    label.setPosition(cc.p(s.width / 2, s.height / 2));
    ret.addChild(label);

    return ret;
}

module.exports = function WasmTest() {
    console.log('WasmTest');
    const scene = cc.Scene.create();

    Helper.createFunctionTable = [
        WasmAddTwo,
    ];
    Helper.index = 0;

    scene.addChild(WasmAddTwo());
    scene.addChild(CreateBackMenuItem());

    return scene;
}