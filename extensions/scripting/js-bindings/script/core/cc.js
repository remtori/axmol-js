const { op_register_conversion_prototype } = require('internal/ops');

class Vec2 {
    constructor(x, y) {
        this.x = x | 0;
        this.y = y | 0;
    }

    get w() {
        return this.x;
    }

    get h() {
        return this.y;
    }

    set w(value) {
        return (this.x = value);
    }

    set h(value) {
        return (this.y = value);
    }

    get width() {
        return this.x;
    }

    get height() {
        return this.y;
    }

    set width(value) {
        return (this.x = value);
    }

    set height(value) {
        return (this.y = value);
    }

    get u() {
        return this.x;
    }

    get v() {
        return this.v;
    }
}
op_register_conversion_prototype(Vec2);

class Vec3 {
    constructor(x, y, z) {
        this.x = x | 0;
        this.y = y | 0;
        this.z = z | 0;
    }
}
op_register_conversion_prototype(Vec3);

class Vec4 {
    constructor(x, y, z, w) {
        this.x = x | 0;
        this.y = y | 0;
        this.z = z | 0;
        this.w = w | 0;
    }
}
op_register_conversion_prototype(Vec4);

cc.clampf = (value, min_inclusive, max_inclusive) => {
    let temp = 0;
    if (min_inclusive > max_inclusive) {
        temp = min_inclusive;
        min_inclusive = max_inclusive;
        max_inclusive = temp;
    }

    if (value < min_inclusive) {
        return min_inclusive;
    } else if (value < max_inclusive) {
        return value;
    } else {
        return max_inclusive;
    }
};

// Vec2/Point
cc.vec2 = (_x, _y) => {
    if (_y === undefined) {
        return new Vec2(_x.x, _x.y);
    } else {
        return new Vec2(_x, _y);
    }
};

cc.p = cc.vec2;

cc.pAdd = (pt1, pt2) => cc.p(pt1.x + pt2.x, pt1.y + pt2.y);

cc.pSub = (pt1, pt2) => cc.p(pt1.x - pt2.x, pt1.y - pt2.y);

cc.pMul = (pt1, factor) => cc.p(pt1.x * factor, pt1.y * factor);

cc.pMidpoint = (pt1, pt2) => cc.p((pt1.x + pt2.x) / 2.0, (pt1.y + pt2.y) / 2.0);

cc.pForAngle = (a) => cc.p(Math.cos(a), Math.sin(a));

cc.pGetLength = (pt) => Math.sqrt(pt.x * pt.x + pt.y * pt.y);

cc.pNormalize = (pt) => {
    const length = cc.pGetLength(pt);
    if (length === 0) {
        return cc.p(1.0, 0.0);
    }
    return cc.p(pt.x / length, pt.y / length);
};

cc.pCross = (self, other) => self.x * other.y - self.y * other.x;

cc.pDot = (self, other) => self.x * other.x + self.y * other.y;

cc.pToAngleSelf = (self) => Math.atan2(self.y, self.x);

cc.pGetAngle = (self, other) => {
    const a2 = cc.pNormalize(self);
    const b2 = cc.pNormalize(other);
    const angle = Math.atan2(cc.pCross(a2, b2), cc.pDot(a2, b2));
    if (Math.abs(angle) < 1.192092896e-7) {
        return 0.0;
    }
    return angle;
};

cc.pGetDistance = (startP, endP) => cc.pGetLength(cc.pSub(startP, endP));
cc.pDistance = cc.pGetDistance;

cc.pIsLineIntersect = (A, B, C, D, s, t) => {
    if ((A.x === B.x && A.y === B.y) || (C.x === D.x && C.y === D.y)) {
        return { intersect: false, s, t };
    }

    const BAx = B.x - A.x;
    const BAy = B.y - A.y;
    const DCx = D.x - C.x;
    const DCy = D.y - C.y;
    const ACx = A.x - C.x;
    const ACy = A.y - C.y;

    const denom = DCy * BAx - DCx * BAy;
    s = DCx * ACy - DCy * ACx;
    t = BAx * ACy - BAy * ACx;

    if (denom === 0) {
        if (s === 0 || t === 0) {
            return { intersect: true, s, t };
        }
        return { intersect: false, s, t };
    }

    s = s / denom;
    t = t / denom;

    return { intersect: true, s, t };
};

cc.pPerp = (pt) => cc.p(-pt.y, pt.x);

cc.RPerp = (pt) => cc.p(pt.y, -pt.x);

cc.pProject = (pt1, pt2) => {
    const factor = cc.pDot(pt1, pt2) / cc.pDot(pt2, pt2);
    return cc.p(pt2.x * factor, pt2.y * factor);
};

cc.pRotate = (pt1, pt2) =>
    cc.p(pt1.x * pt2.x - pt1.y * pt2.y, pt1.x * pt2.y + pt1.y * pt2.x);

cc.pUnrotate = (pt1, pt2) =>
    cc.p(pt1.x * pt2.x + pt1.y * pt2.y, pt1.y * pt2.x - pt1.x * pt2.y);

// Calculates the square length of pt
cc.pLengthSQ = (pt) => cc.pDot(pt, pt);

// Calculates the square distance between pt1 and pt2
cc.pDistanceSQ = (pt1, pt2) => cc.pLengthSQ(cc.pSub(pt1, pt2));

cc.pGetClampPoint = (pt1, pt2, pt3) =>
    cc.p(cc.clampf(pt1.x, pt2.x, pt3.x), cc.clampf(pt1.y, pt2.y, pt3.y));

cc.pFromSize = (sz) => cc.p(sz.width, sz.height);

cc.pLerp = (pt1, pt2, alpha) =>
    cc.pAdd(cc.pMul(pt1, 1.0 - alpha), cc.pMul(pt2, alpha));

cc.pFuzzyEqual = (pt1, pt2, variance) => {
    if (
        pt1.x - variance <= pt2.x &&
        pt2.x <= pt1.x + variance &&
        pt1.y - variance <= pt2.y &&
        pt2.y <= pt1.y + variance
    ) {
        return true;
    } else {
        return false;
    }
};

cc.pIsSegmentIntersect = (pt1, pt2, pt3, pt4) => {
    const result = cc.pIsLineIntersect(pt1, pt2, pt3, pt4, 0, 0);
    const { s, t, intersect: ret } = result;

    if (ret && s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0) {
        return true;
    }
    return false;
};

cc.pGetIntersectPoint = (pt1, pt2, pt3, pt4) => {
    const result = cc.pIsLineIntersect(pt1, pt2, pt3, pt4, 0, 0);
    const { s, intersect: ret } = result;

    if (ret) {
        return cc.p(pt1.x + s * (pt2.x - pt1.x), pt1.y + s * (pt2.y - pt1.y));
    } else {
        return cc.p(0, 0);
    }
};

// Size
cc.size = cc.vec2;

class Rect {
    constructor(x, y, width, height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }
}
op_register_conversion_prototype(Rect);

// Rect
cc.rect = (x, y, width, height) => new Rect(x, y, width, height);

cc.rectEqualToRect = (rect1, rect2) => {
    if (
        rect1.x >= rect2.x ||
        rect1.y >= rect2.y ||
        rect1.x + rect1.width <= rect2.x + rect2.width ||
        rect1.y + rect1.height <= rect2.y + rect2.height
    ) {
        return false;
    }
    return true;
};

cc.rectGetMaxX = (rect) => rect.x + rect.width;

cc.rectGetMidX = (rect) => rect.x + rect.width / 2.0;

cc.rectGetMinX = (rect) => rect.x;

cc.rectGetMaxY = (rect) => rect.y + rect.height;

cc.rectGetMidY = (rect) => rect.y + rect.height / 2.0;

cc.rectGetMinY = (rect) => rect.y;

cc.rectContainsPoint = (rect, point) => {
    let ret = false;
    if (
        point.x >= rect.x &&
        point.x <= rect.x + rect.width &&
        point.y >= rect.y &&
        point.y <= rect.y + rect.height
    ) {
        ret = true;
    }
    return ret;
};

cc.rectIntersectsRect = (rect1, rect2) => {
    const intersect = !(
        rect1.x > rect2.x + rect2.width ||
        rect1.x + rect1.width < rect2.x ||
        rect1.y > rect2.y + rect2.height ||
        rect1.y + rect1.height < rect2.y
    );
    return intersect;
};

cc.rectUnion = (rect1, rect2) => {
    const rect = cc.rect(0, 0, 0, 0);
    rect.x = Math.min(rect1.x, rect2.x);
    rect.y = Math.min(rect1.y, rect2.y);
    rect.width =
        Math.max(rect1.x + rect1.width, rect2.x + rect2.width) - rect.x;
    rect.height =
        Math.max(rect1.y + rect1.height, rect2.y + rect2.height) - rect.y;
    return rect;
};

cc.rectIntersection = (rect1, rect2) => {
    const intersection = cc.rect(
        Math.max(rect1.x, rect2.x),
        Math.max(rect1.y, rect2.y),
        0,
        0
    );

    intersection.width =
        Math.min(rect1.x + rect1.width, rect2.x + rect2.width) - intersection.x;
    intersection.height =
        Math.min(rect1.y + rect1.height, rect2.y + rect2.height) -
        intersection.y;
    return intersection;
};

// Color3B
cc.c3b = (r, g, b) => ({ r, g, b });

// Color4B
cc.c4b = (r, g, b, a) => ({ r, g, b, a });

// Color4F
cc.c4f = (r, g, b, a) => ({ r, g, b, a });

function isFloatColor(c) {
    return (
        c.r <= 1 &&
        c.g <= 1 &&
        c.b <= 1 &&
        (Math.ceil(c.r) !== c.r ||
            Math.ceil(c.g) !== c.g ||
            Math.ceil(c.b) !== c.b)
    );
}

cc.convertColor = (input, typ) => {
    if (
        !(
            typeof input === "object" &&
            input.r !== undefined &&
            input.g !== undefined &&
            input.b !== undefined
        )
    ) {
        throw new Error("cc.convertColor() - invalid input color");
    }

    let ret;
    if (typ === "3b") {
        if (isFloatColor(input)) {
            ret = {
                r: Math.ceil(input.r * 255),
                g: Math.ceil(input.g * 255),
                b: Math.ceil(input.b * 255),
            };
        } else {
            ret = { r: input.r, g: input.g, b: input.b };
        }
    } else if (typ === "4b") {
        if (isFloatColor(input)) {
            ret = {
                r: Math.ceil(input.r * 255),
                g: Math.ceil(input.g * 255),
                b: Math.ceil(input.b * 255),
            };
        } else {
            ret = { r: input.r, g: input.g, b: input.b };
        }
        if (input.a !== undefined) {
            if (Math.ceil(input.a) !== input.a || input.a <= 1) {
                ret.a = input.a * 255;
            } else {
                ret.a = input.a;
            }
        } else {
            ret.a = 255;
        }
    } else if (typ === "4f") {
        if (isFloatColor(input)) {
            ret = { r: input.r, g: input.g, b: input.b };
        } else {
            ret = { r: input.r / 255, g: input.g / 255, b: input.b / 255 };
        }
        if (input.a !== undefined) {
            if (Math.ceil(input.a) !== input.a || input.a <= 1) {
                ret.a = input.a;
            } else {
                ret.a = input.a / 255;
            }
        } else {
            ret.a = 255;
        }
    } else {
        throw new Error("cc.convertColor() - invalid type " + typ);
    }
    return ret;
};

// Vertex2F
cc.vertex2F = (x, y) => cc.vec2(x, y);

// Vertex3F
cc.Vertex3F = (x, y, z) => cc.vec3(x, y, z);

// Tex2F
cc.tex2F = (u, v) => cc.vec2(u, v);

// PointSprite
cc.PointSprite = (pos, color, size) => ({ pos, color, size });

// Quad2
cc.Quad2 = (tl, tr, bl, br) => ({ tl, tr, bl, br });

// Quad3
cc.Quad3 = (tl, tr, bl, br) => ({ tl, tr, bl, br });

// V2F_C4B_T2F
cc.V2F_C4B_T2F = (vertices, colors, texCoords) => ({
    vertices,
    colors,
    texCoords,
});

// V2F_C4F_T2F
cc.V2F_C4F_T2F = (vertices, colors, texCoords) => ({
    vertices,
    colors,
    texCoords,
});

// V3F_C4B_T2F
cc.V3F_C4B_T2F = (vertices, colors, texCoords) => ({
    vertices,
    colors,
    texCoords,
});

// V2F_C4B_T2F_Quad
cc.V2F_C4B_T2F_Quad = (bl, br, tl, tr) => ({ bl, br, tl, tr });

// V3F_C4B_T2F_Quad
cc.V3F_C4B_T2F_Quad = (tl, bl, tr, br) => ({ tl, bl, tr, br });

// V2F_C4F_T2F_Quad
cc.V2F_C4F_T2F_Quad = (bl, br, tl, tr) => ({ bl, br, tl, tr });

// T2F_Quad
cc.T2F_Quad = (bl, br, tl, tr) => ({ bl, br, tl, tr });

// AnimationFrameData
cc.AnimationFrameData = (texCoords, delay, size) => ({
    texCoords,
    delay,
    size,
});

// PhysicsMaterial
cc.PhysicsMaterial = (density, restitution, friction) => ({
    density,
    restitution,
    friction,
});

cc.math = cc.math || {};

cc.vec3 = (x, y, z) => new Vec3(x, y, z);
cc.math.Vec3 = Vec3;
cc.math.vec3 = cc.vec3;

cc.vec4 = (x, y, z, w) => new Vec4(x, y, z, w);

cc.vec3add = (vec3a, vec3b) =>
    cc.vec3(vec3a.x + vec3b.x, vec3a.y + vec3b.y, vec3a.z + vec3b.z);

cc.vec3sub = (vec3a, vec3b) =>
    cc.vec3(vec3a.x - vec3b.x, vec3a.y - vec3b.y, vec3a.z - vec3b.z);

cc.vec3mul = (vec3, factor) =>
    cc.vec3(vec3.x * factor, vec3.y * factor, vec3.z * factor);

cc.vec3dot = (vec3a, vec3b) =>
    vec3a.x * vec3b.x + vec3a.y * vec3b.y + vec3a.z * vec3b.z;

cc.vec3normalize = (vec3) => {
    let n = cc.vec3dot(vec3, vec3);
    if (n === 1.0) {
        return vec3;
    }

    n = Math.sqrt(n);

    if (n < 2e-37) {
        return vec3;
    }

    return cc.vec3mul(vec3, 1.0 / n);
};

cc.quaternion = cc.vec4;

cc.quaternion_createFromAxisAngle = (axis, angle) => {
    const halfAngle = angle * 0.5;
    const sinHalfAngle = Math.sin(halfAngle);

    const normal = cc.vec3(axis.x, axis.y, axis.z);
    const normalizedAxis = cc.vec3normalize(normal);
    const dst = cc.vec3(0.0, 0.0, 0.0);
    dst.x = normalizedAxis.x * sinHalfAngle;
    dst.y = normalizedAxis.y * sinHalfAngle;
    dst.z = normalizedAxis.z * sinHalfAngle;
    dst.w = Math.cos(halfAngle);

    return dst;
};

cc.blendFunc = (src, dst) => ({ src, dst });
