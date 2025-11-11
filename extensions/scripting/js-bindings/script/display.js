const director = cc.Director.getInstance();

let view = director.getRenderView();
if (!view) {
    const width = 960;
    const height = 640;
    view = cc.RenderViewImpl.createWithRect("Axmol-JS", cc.rect(0, 0, width, height), 1, false);
    director.setRenderView(view);
}
