class VisibleRect {
    static s_visibleRect = cc.rect(0, 0, 0, 0);

    static lazyInit() {
        if (this.s_visibleRect.width == 0.0 && this.s_visibleRect.height == 0.0) {
            const director = cc.Director.getInstance();
            const origin = director.getVisibleOrigin();
            const visibleSize = director.getVisibleSize();
            this.s_visibleRect.x = origin.x;
            this.s_visibleRect.y = origin.y;
            this.s_visibleRect.width = visibleSize.width;
            this.s_visibleRect.height = visibleSize.height;
        }
    }

    static getVisibleRect() {
        this.lazyInit();
        return cc.rect(this.s_visibleRect.x, this.s_visibleRect.y, this.s_visibleRect.width, this.s_visibleRect.height);
    }

    static left() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x, this.s_visibleRect.y + this.s_visibleRect.height / 2);
    }

    static right() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x + this.s_visibleRect.width, this.s_visibleRect.y + this.s_visibleRect.height / 2);
    }

    static top() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x + this.s_visibleRect.width / 2, this.s_visibleRect.y + this.s_visibleRect.height);
    }

    static bottom() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x + this.s_visibleRect.width / 2, this.s_visibleRect.y);
    }

    static center() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x + this.s_visibleRect.width / 2, this.s_visibleRect.y + this.s_visibleRect.height / 2);
    }

    static leftTop() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x, this.s_visibleRect.y + this.s_visibleRect.height);
    }

    static rightTop() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x + this.s_visibleRect.width, this.s_visibleRect.y + this.s_visibleRect.height);
    }

    static leftBottom() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x, this.s_visibleRect.y);
    }

    static rightBottom() {
        this.lazyInit();
        return cc.p(this.s_visibleRect.x + this.s_visibleRect.width, this.s_visibleRect.y);
    }
}

exports.VisibleRect = VisibleRect;
