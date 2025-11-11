console.log("jsb controller.js", cc.director);

// turn on display FPS
cc.director.setDisplayStats(true);

// set FPS. the default value is 1.0/60 if you don't call this
// cc.director.setAnimationInterval(1.0 / 60);

// cc.sys.dump();

const screenSize = cc.director.getRenderView().getWindowSize();
const addSearchPath = (resPrefix, height) => {
    const searchPaths = jsb.fileUtils.getSearchPaths();
    searchPaths.unshift(resPrefix);
    searchPaths.unshift(resPrefix + "cocosbuilderRes");

    if (height > 320) {
        searchPaths.unshift(resPrefix + "hd");
        searchPaths.unshift(resPrefix + "ccs-res");
        searchPaths.unshift(resPrefix + "ccs-res/hd");
    }

    jsb.fileUtils.setSearchPaths(searchPaths);
};

addSearchPath("res/", screenSize.height);
addSearchPath("", screenSize.height);

const { createTestMenu } = require("./mainMenu");

const scene = cc.Scene.create();
scene.addChild(createTestMenu());
if (cc.director.getRunningScene()) {
    cc.director.replaceScene(scene);
} else {
    cc.director.runWithScene(scene);
}
