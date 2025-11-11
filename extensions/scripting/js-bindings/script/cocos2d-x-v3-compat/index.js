const ops = require('internal/ops');
const path = require('path');

function requireInGlobalContext(requirePath) {
    ops.op_cocos_require(path.join(__dirname, requirePath));
}

requireInGlobalContext('./jsb_prepare.js');

/**
 *  <p>Properties configuration function </br>
 *  All properties in attrs will be set to the node, </br>
 *  when the setter of the node is available, </br>
 *  the property will be set via setter function.</br>
 *  </p>
 * @param {Object} attrs Properties to be set to node
 */
cc.Node.prototype.attr = function(attrs) {
    for(var key in attrs) {
        this[key] = attrs[key];
    }
};

cc.log = console.log;

requireInGlobalContext('./jsb_audioengine.js');

requireInGlobalContext('./jsb_boot.js');

requireInGlobalContext('./jsb_common.js');
requireInGlobalContext('./jsb_create_apis.js');
requireInGlobalContext('./jsb_cocos2d_constants.js');

requireInGlobalContext('./jsb_opengl_constants.js');
requireInGlobalContext('./jsb_opengl.js');

requireInGlobalContext('./jsb_cocos2d.js');

if (window.ccs) {
    // requireInGlobalContext('./studio/jsb_studio_boot.js');
    // requireInGlobalContext('./studio/jsb_cocos2d_studio.js');
    // requireInGlobalContext('./studio/jsb_studio_property_apis.js');
    // requireInGlobalContext('./studio/jsb_studio_create_apis.js');

    // requireInGlobalContext('./studio/jsb_studio_load.js');
    // requireInGlobalContext('./studio/parsers/action-1.x.js');
    // requireInGlobalContext('./studio/parsers/action-2.x.js');
    // requireInGlobalContext('./studio/parsers/scene-1.x.js');
    // requireInGlobalContext('./studio/parsers/timelineParser-1.x.js');
    // requireInGlobalContext('./studio/parsers/timelineParser-2.x.js');
    // requireInGlobalContext('./studio/parsers/uiParser-1.x.js');
    // requireInGlobalContext('./studio/parsers/compatible.js');
}

if (window.ccui) {
    requireInGlobalContext('./ccui/jsb_cocos2d_ui.js');
    requireInGlobalContext('./ccui/jsb_ccui_property_apis.js');
    requireInGlobalContext('./ccui/jsb_ccui_create_apis.js');
    requireInGlobalContext('./ccui/jsb_ccui_deprecated.js');
}

if (cc.MeshRenderer) {
    requireInGlobalContext('./jsb_cocos2d_3d.js');
}

if (cc.ControlButton) {
    requireInGlobalContext('./extension/jsb_cocos2d_extension.js');
    // requireInGlobalContext('./extension/jsb_ext_property_apis.js');
    // requireInGlobalContext('./extension/jsb_ext_create_apis.js');
}

if (cc.PhysicsSprite) {
    requireInGlobalContext('./physicsSprite/jsb_physicsSprite.js');
}

if (window.cp) {
    // chipmunk
    requireInGlobalContext('./chipmunk/jsb_chipmunk_constants.js');
    requireInGlobalContext('./chipmunk/jsb_chipmunk.js');
}

if (cc.BuilderAnimationManager) {
    requireInGlobalContext('./jsb_cocosbuilder.js');
}

if (window.sp) {
    // requireInGlobalContext('./jsb_spine.js');
}

requireInGlobalContext('./jsb_loaders.js');
requireInGlobalContext('./jsb_pool.js');
