cc.PLATFORM_WINDOWS = 1;
cc.PLATFORM_UWP = 2;
cc.PLATFORM_LINUX = 3;
cc.PLATFORM_MAC = 4;
cc.PLATFORM_ANDROID = 5;
cc.PLATFORM_IOS = 6;
cc.PLATFORM_TVOS = 7;
cc.PLATFORM_WASM = 8;

const device = {
    platform: "unknown",
    model: "unknown",
}

const app = cc.Application.getInstance();
const target = app.getTargetPlatform();
if (target === cc.PLATFORM_WINDOWS) {
    device.platform = "windows";
} else if (target === cc.PLATFORM_UWP) {
    device.platform = "uwp";
} else if (target === cc.PLATFORM_UWP_PHONE) {
    device.platform = "uwp phone";
} else if (target === cc.PLATFORM_MAC) {
    device.platform = "mac";
} else if (target === cc.PLATFORM_ANDROID) {
    device.platform = "android";
} else if (target === cc.PLATFORM_IOS) {
    device.platform = "ios";
    const director = cc.Director.getInstance();
    const view = director.getGLView();
    const framesize = view.getFrameSize();
    const w = framesize.width;
    const h = framesize.height;
    if (w === 640 && h === 960) {
        device.model = "iphone 4";
    } else if (w === 640 && h === 1136) {
        device.model = "iphone 5";
    } else if (w === 750 && h === 1334) {
        device.model = "iphone 6";
    } else if (w === 1242 && h === 2208) {
        device.model = "iphone 6 plus";
    } else if (w === 768 && h === 1024) {
        device.model = "ipad";
    } else if (w === 1536 && h === 2048) {
        device.model = "ipad retina";
    }
}

device.writablePath = cc.FileUtils.getInstance().getWritablePath();
device.directorySeparator = "/";
device.pathSeparator = ":";
if (device.platform === "windows") {
    device.directorySeparator = "\\";
    device.pathSeparator = ";";
}

console.log("# device.platform              = " + device.platform);
console.log("# device.model                 = " + device.model);
console.log("# device.writablePath          = " + device.writablePath);
console.log("# device.directorySeparator    = " + device.directorySeparator);
console.log("# device.pathSeparator         = " + device.pathSeparator);
console.log("#");
