jsb.sprite3DCache = cc.MeshRendererCache.getInstance();

jsb.Sprite3D = cc.MeshRenderer;

jsb.Sprite3D.prototype._setBlendFunc = jsb.Sprite3D.prototype.setBlendFunc;
jsb.Sprite3D.prototype.setBlendFunc = templateSetBlendFunc;

jsb.Sprite3D.prototype._ctor = function (modelPath, texturePath) {
    if (modelPath === undefined) {
        this.init();
    } else {
        if (modelPath.length < 4) {
            console.log("invalid filename for Sprite3D");
            return;
        }

        this.initWithFile(modelPath);

        const bb = this.getBoundingBox();
        this.setContentSize(cc.size(bb.width, bb.height));
        if (texturePath !== undefined)
            this.setTexture(texturePath);
    }
};

jsb.Mesh = cc.Mesh;
jsb.Mesh.prototype._setBlendFunc = jsb.Mesh.prototype.setBlendFunc;
jsb.Mesh.prototype.setBlendFunc = templateSetBlendFunc;
