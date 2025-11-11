#include "js-bindings/bindings/axjs_3d_auto.hpp"
#if defined(AX_ENABLE_3D)
#    include "axmol/axmol.h"
#    include "axmol/3d/Bundle3D.h"
#    include "js-bindings/manual/JSConversions.h"
static void js_register_ax_3d_Animation3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Animation3D> class_Animation3D(isolate);
    class_Animation3D.ctor([]() { return new ax::Animation3D(); })
        .template inherit<ax::Object>()
        .member_function("getDuration", &ax::Animation3D::getDuration)
        .member_function("init", &ax::Animation3D::init)
        .member_function("initWithFile", &ax::Animation3D::initWithFile)
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::Animation3D::create(arg0); },
            [](std::string_view arg0, std::string_view arg1) { return ax::Animation3D::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("Animation3D", class_Animation3D);
}
static void js_register_ax_3d_Animate3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Animate3D> class_Animate3D(isolate);
    class_Animate3D.ctor([]() { return new ax::Animate3D(); })
        .template inherit<ax::ActionInterval>()
        .member_function("getSpeed", &ax::Animate3D::getSpeed)
        .member_function("setSpeed", &ax::Animate3D::setSpeed)
        .member_function("getWeight", &ax::Animate3D::getWeight)
        .member_function("setWeight", &ax::Animate3D::setWeight)
        .member_function("setOriginInterval", &ax::Animate3D::setOriginInterval)
        .member_function("getOriginInterval", &ax::Animate3D::getOriginInterval)
        .member_function("setQuality", &ax::Animate3D::setQuality)
        .member_function("getQuality", &ax::Animate3D::getQuality)
        .member_function("setKeyFrameUserInfo", &ax::Animate3D::setKeyFrameUserInfo)
        .member_function("removeFromMap", &ax::Animate3D::removeFromMap)
        .member_function(
            "init",
            [](ax::Animate3D* self, ax::Animation3D* arg0, float arg1, float arg2) { return self->init(arg0, arg1, arg2); },
            [](ax::Animate3D* self, ax::Animation3D* arg0) { return self->init(arg0); })
        .member_function("initWithFrames", &ax::Animate3D::initWithFrames)
        .static_function(
            "create",
            [](ax::Animation3D* arg0, float arg1, float arg2) { return ax::Animate3D::create(arg0, arg1, arg2); },
            [](ax::Animation3D* arg0) { return ax::Animate3D::create(arg0); })
        .static_function(
            "createWithFrames",
            [](ax::Animation3D* arg0, int arg1, int arg2) { return ax::Animate3D::createWithFrames(arg0, arg1, arg2); },
            [](ax::Animation3D* arg0, int arg1, int arg2, float arg3) { return ax::Animate3D::createWithFrames(arg0, arg1, arg2, arg3); })
        .static_function("getTransitionTime", &ax::Animate3D::getTransitionTime)
        .static_function("setTransitionTime", &ax::Animate3D::setTransitionTime)
        .auto_wrap_objects(true);
    mod.class_("Animate3D", class_Animate3D);
}
static void js_register_ax_3d_TextureCube(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::TextureCube> class_TextureCube(isolate);
    class_TextureCube.ctor([]() { return new ax::TextureCube(); })
        .template inherit<ax::Object>()
        .member_function("setTexParameters", &ax::TextureCube::setTexParameters)
        .member_function("getRHITexture", &ax::TextureCube::getRHITexture)
        .member_function("getImagePaths", &ax::TextureCube::getImagePaths)
        .member_function("reloadTexture", &ax::TextureCube::reloadTexture)
        .static_function("create", &ax::TextureCube::create)
        .auto_wrap_objects(true);
    mod.class_("TextureCube", class_TextureCube);
}
static void js_register_ax_3d_AttachNode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::AttachNode> class_AttachNode(isolate);
    class_AttachNode.ctor([]() { return new ax::AttachNode(); })
        .template inherit<ax::Node>()
        .static_function("create", &ax::AttachNode::create)
        .auto_wrap_objects(true);
    mod.class_("AttachNode", class_AttachNode);
}
static void js_register_ax_3d_BillBoard(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::BillBoard> class_BillBoard(isolate);
    class_BillBoard.ctor([]() { return new ax::BillBoard(); })
        .template inherit<ax::Sprite>()
        .member_function("setMode", &ax::BillBoard::setMode)
        .member_function("getMode", &ax::BillBoard::getMode)
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::BillBoard::create(arg0); },
            [](std::string_view arg0, ax::BillBoard::Mode arg1) { return ax::BillBoard::create(arg0, arg1); },
            []() { return ax::BillBoard::create(); },
            [](ax::BillBoard::Mode arg0) { return ax::BillBoard::create(arg0); },
            [](std::string_view arg0, ax::Rect arg1) { return ax::BillBoard::create(arg0, arg1); },
            [](std::string_view arg0, ax::Rect arg1, ax::BillBoard::Mode arg2) { return ax::BillBoard::create(arg0, arg1, arg2); })
        .static_function(
            "createWithTexture",
            [](ax::Texture2D* arg0) { return ax::BillBoard::createWithTexture(arg0); },
            [](ax::Texture2D* arg0, ax::BillBoard::Mode arg1) { return ax::BillBoard::createWithTexture(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("BillBoard", class_BillBoard);
}
static void js_register_ax_3d_Mesh(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Mesh> class_Mesh(isolate);
    class_Mesh.ctor([]() { return new ax::Mesh(); })
        .template inherit<ax::Object>()
        .member_function("getMeshVertexAttribCount", &ax::Mesh::getMeshVertexAttribCount)
        .member_function("getMeshVertexAttribute", &ax::Mesh::getMeshVertexAttribute)
        .member_function("getVertexSizeInBytes", &ax::Mesh::getVertexSizeInBytes)
        .member_function("setVisible", &ax::Mesh::setVisible)
        .member_function("isVisible", &ax::Mesh::isVisible)
        .member_function("getProgramState", &ax::Mesh::getProgramState)
        .member_function("getName", &ax::Mesh::getName)
        .member_function("setBlendFunc", &ax::Mesh::setBlendFunc)
        .member_function("getBlendFunc", &ax::Mesh::getBlendFunc)
        .member_function("setIndexFormat", &ax::Mesh::setIndexFormat)
        .member_function("setProgramState", &ax::Mesh::setProgramState)
        .member_function("setMaterial", &ax::Mesh::setMaterial)
        .member_function("getMaterial", &ax::Mesh::getMaterial)
        .member_function("draw", &ax::Mesh::draw)
        .member_function("setSkin", &ax::Mesh::setSkin)
        .member_function("setMeshIndexData", &ax::Mesh::setMeshIndexData)
        .member_function("setName", &ax::Mesh::setName)
        .member_function("calculateAABB", &ax::Mesh::calculateAABB)
        .member_function(
            "setInstanceCount",
            [](ax::Mesh* self) { self->setInstanceCount(); },
            [](ax::Mesh* self, int arg0) { self->setInstanceCount(arg0); })
        .member_function(
            "enableInstancing",
            [](ax::Mesh* self, bool arg0) { self->enableInstancing(arg0); },
            [](ax::Mesh* self, bool arg0, int arg1) { self->enableInstancing(arg0, arg1); })
        .member_function("setDynamicInstancing", &ax::Mesh::setDynamicInstancing)
        .member_function("addInstanceChild", &ax::Mesh::addInstanceChild)
        .member_function("shrinkToFitInstances", &ax::Mesh::shrinkToFitInstances)
        .member_function("rebuildInstances", &ax::Mesh::rebuildInstances)
        .auto_wrap_objects(true);
    mod.class_("Mesh", class_Mesh);
}
static void js_register_ax_3d_Skeleton3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Skeleton3D> class_Skeleton3D(isolate);
    class_Skeleton3D.ctor([]() { return new ax::Skeleton3D(); })
        .template inherit<ax::Object>()
        .member_function("getBoneCount", &ax::Skeleton3D::getBoneCount)
        .member_function("getBoneByIndex", &ax::Skeleton3D::getBoneByIndex)
        .member_function("getBoneByName", &ax::Skeleton3D::getBoneByName)
        .member_function("getRootCount", &ax::Skeleton3D::getRootCount)
        .member_function("getRootBone", &ax::Skeleton3D::getRootBone)
        .member_function("getBoneIndex", &ax::Skeleton3D::getBoneIndex)
        .member_function("updateBoneMatrix", &ax::Skeleton3D::updateBoneMatrix)
        .member_function("removeAllBones", &ax::Skeleton3D::removeAllBones)
        .member_function("addBone", &ax::Skeleton3D::addBone)
        .auto_wrap_objects(true);
    mod.class_("Skeleton3D", class_Skeleton3D);
}
static void js_register_ax_3d_Skybox(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Skybox> class_Skybox(isolate);
    class_Skybox.ctor([]() { return new ax::Skybox(); })
        .template inherit<ax::Node>()
        .member_function("setTexture", &ax::Skybox::setTexture)
        .member_function("reload", &ax::Skybox::reload)
        .static_function(
            "create",
            [](std::string_view arg0,
               std::string_view arg1,
               std::string_view arg2,
               std::string_view arg3,
               std::string_view arg4,
               std::string_view arg5) { return ax::Skybox::create(arg0, arg1, arg2, arg3, arg4, arg5); },
            []() { return ax::Skybox::create(); })
        .auto_wrap_objects(true);
    mod.class_("Skybox", class_Skybox);
}
static void js_register_ax_3d_MeshMaterial(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MeshMaterial> class_MeshMaterial(isolate);
    class_MeshMaterial.template inherit<ax::Material>()
        .member_function("getMaterialType", &ax::MeshMaterial::getMaterialType)
        .static_function(
            "createBuiltInMaterial",
            []() { ax::MeshMaterial::createBuiltInMaterial(); },
            [](ax::MeshMaterial::MaterialType arg0, bool arg1) { return ax::MeshMaterial::createBuiltInMaterial(arg0, arg1); })
        .static_function("createWithFilename", &ax::MeshMaterial::createWithFilename)
        .static_function("createWithProgramState", &ax::MeshMaterial::createWithProgramState)
        .static_function("releaseBuiltInMaterial", &ax::MeshMaterial::releaseBuiltInMaterial)
        .static_function("releaseCachedMaterial", &ax::MeshMaterial::releaseCachedMaterial)
        .auto_wrap_objects(true);
    mod.class_("MeshMaterial", class_MeshMaterial);
}
static void js_register_ax_3d_MeshRenderer(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MeshRenderer> class_MeshRenderer(isolate);
    class_MeshRenderer.template inherit<ax::Node>()
        .member_function(
            "setTexture",
            [](ax::MeshRenderer* self, ax::Texture2D* arg0) { self->setTexture(arg0); },
            [](ax::MeshRenderer* self, std::string_view arg0) { self->setTexture(arg0); })
        .member_function("getMeshByIndex", &ax::MeshRenderer::getMeshByIndex)
        .member_function("getMeshByName", &ax::MeshRenderer::getMeshByName)
        .member_function("getMesh", &ax::MeshRenderer::getMesh)
        .member_function("getMeshCount", &ax::MeshRenderer::getMeshCount)
        .member_function("getSkeleton", &ax::MeshRenderer::getSkeleton)
        .member_function("getAttachNode", &ax::MeshRenderer::getAttachNode)
        .member_function("removeAttachNode", &ax::MeshRenderer::removeAttachNode)
        .member_function("removeAllAttachNode", &ax::MeshRenderer::removeAllAttachNode)
        .member_function("setBlendFunc", &ax::MeshRenderer::setBlendFunc)
        .member_function("getBlendFunc", &ax::MeshRenderer::getBlendFunc)
        .member_function("setForceDepthWrite", &ax::MeshRenderer::setForceDepthWrite)
        .member_function("isForceDepthWrite", &ax::MeshRenderer::isForceDepthWrite)
        .member_function("setCullFace", &ax::MeshRenderer::setCullFace)
        .member_function("setCullFaceEnabled", &ax::MeshRenderer::setCullFaceEnabled)
        .member_function("setLightMask", &ax::MeshRenderer::setLightMask)
        .member_function("getLightMask", &ax::MeshRenderer::getLightMask)
        .member_function("setWireframe", &ax::MeshRenderer::setWireframe)
        .member_function("isWireframe", &ax::MeshRenderer::isWireframe)
        .member_function(
            "setMaterial",
            [](ax::MeshRenderer* self, ax::Material* arg0, int arg1) { self->setMaterial(arg0, arg1); },
            [](ax::MeshRenderer* self, ax::Material* arg0) { self->setMaterial(arg0); })
        .member_function(
            "getMaterial",
            [](ax::MeshRenderer* self) { return self->getMaterial(); },
            [](ax::MeshRenderer* self, int arg0) { return self->getMaterial(arg0); })
        .member_function("getMeshes", &ax::MeshRenderer::getMeshes)
        .member_function(
            "genMaterial",
            [](ax::MeshRenderer* self) { self->genMaterial(); },
            [](ax::MeshRenderer* self, bool arg0) { self->genMaterial(arg0); })
        .member_function(
            "enableInstancing",
            [](ax::MeshRenderer* self, ax::MeshMaterial* arg0) { self->enableInstancing(arg0); },
            [](ax::MeshRenderer* self, ax::MeshMaterial* arg0, int arg1) { self->enableInstancing(arg0, arg1); },
            [](ax::MeshRenderer* self, ax::MeshMaterial::InstanceMaterialType arg0) { self->enableInstancing(arg0); },
            [](ax::MeshRenderer* self, ax::MeshMaterial::InstanceMaterialType arg0, int arg1) { self->enableInstancing(arg0, arg1); })
        .member_function("disableInstancing", &ax::MeshRenderer::disableInstancing)
        .member_function("setDynamicInstancing", &ax::MeshRenderer::setDynamicInstancing)
        .member_function(
            "addInstanceChild",
            [](ax::MeshRenderer* self, ax::Node* arg0) { self->addInstanceChild(arg0); },
            [](ax::MeshRenderer* self, ax::Node* arg0, bool arg1) { self->addInstanceChild(arg0, arg1); })
        .member_function("shrinkToFitInstances", &ax::MeshRenderer::shrinkToFitInstances)
        .member_function("rebuildInstances", &ax::MeshRenderer::rebuildInstances)
        .static_function(
            "create",
            [](std::string_view arg0) { return ax::MeshRenderer::create(arg0); },
            []() { return ax::MeshRenderer::create(); },
            [](std::string_view arg0, std::string_view arg1) { return ax::MeshRenderer::create(arg0, arg1); })
        .auto_wrap_objects(true);
    mod.class_("MeshRenderer", class_MeshRenderer);
}
static void js_register_ax_3d_MeshRendererCache(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::MeshRendererCache> class_MeshRendererCache(isolate);
    class_MeshRendererCache.ctor([]() { return new ax::MeshRendererCache(); })
        .member_function("removeMeshRenderData", &ax::MeshRendererCache::removeMeshRenderData)
        .member_function("removeAllMeshRenderData", &ax::MeshRendererCache::removeAllMeshRenderData)
        .static_function("getInstance", &ax::MeshRendererCache::getInstance)
        .static_function("destroyInstance", &ax::MeshRendererCache::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("MeshRendererCache", class_MeshRendererCache);
}
static void js_register_ax_3d_Terrain(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Terrain> class_Terrain(isolate);
    class_Terrain.ctor([]() { return new ax::Terrain(); })
        .template inherit<ax::Node>()
        .member_function("setLightMap", &ax::Terrain::setLightMap)
        .member_function("setLightDir", &ax::Terrain::setLightDir)
        .member_function("initProperties", &ax::Terrain::initProperties)
        .member_function("initHeightMap", &ax::Terrain::initHeightMap)
        .member_function("initTextures", &ax::Terrain::initTextures)
        .member_function("getNormal", &ax::Terrain::getNormal)
        .member_function("getImageHeight", &ax::Terrain::getImageHeight)
        .member_function("setDrawWire", &ax::Terrain::setDrawWire)
        .member_function("setLODDistance", &ax::Terrain::setLODDistance)
        .member_function("setIsEnableFrustumCull", &ax::Terrain::setIsEnableFrustumCull)
        .member_function("setAlphaMap", &ax::Terrain::setAlphaMap)
        .member_function("setDetailMap", &ax::Terrain::setDetailMap)
        .member_function("setMaxDetailMapAmount", &ax::Terrain::setMaxDetailMapAmount)
        .member_function("convertToTerrainSpace", &ax::Terrain::convertToTerrainSpace)
        .member_function("resetHeightMap", &ax::Terrain::resetHeightMap)
        .member_function("getMinHeight", &ax::Terrain::getMinHeight)
        .member_function("getMaxHeight", &ax::Terrain::getMaxHeight)
        .member_function("setSkirtHeightRatio", &ax::Terrain::setSkirtHeightRatio)
        .member_function("reload", &ax::Terrain::reload)
        .member_function("getTerrainSize", &ax::Terrain::getTerrainSize)
        .member_function("getHeightData", &ax::Terrain::getHeightData)
        .member_function("initWithTerrainData", &ax::Terrain::initWithTerrainData)
        .auto_wrap_objects(true);
    mod.class_("Terrain", class_Terrain);
}
static void js_register_ax_3d_Bundle3D(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::Bundle3D> class_Bundle3D(isolate);
    class_Bundle3D.ctor([]() { return new ax::Bundle3D(); })
        .member_function("clear", &ax::Bundle3D::clear)
        .member_function("load", &ax::Bundle3D::load)
        .member_function("loadSkinData", &ax::Bundle3D::loadSkinData)
        .member_function("loadAnimationData", &ax::Bundle3D::loadAnimationData)
        .member_function("loadNodes", &ax::Bundle3D::loadNodes)
        .member_function("loadMaterials", &ax::Bundle3D::loadMaterials)
        .static_function("createBundle", &ax::Bundle3D::createBundle)
        .static_function("destroyBundle", &ax::Bundle3D::destroyBundle)
        .static_function("parseGLDataType", &ax::Bundle3D::parseGLDataType)
        .static_function("parseSamplerAddressMode", &ax::Bundle3D::parseSamplerAddressMode)
        .auto_wrap_objects(true);
    mod.class_("Bundle3D", class_Bundle3D);
}
void js_register_all_ax_3d(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("ax");
    js_register_ax_3d_Animation3D(mod);
    js_register_ax_3d_Animate3D(mod);
    js_register_ax_3d_TextureCube(mod);
    js_register_ax_3d_AttachNode(mod);
    js_register_ax_3d_BillBoard(mod);
    js_register_ax_3d_Mesh(mod);
    js_register_ax_3d_Skeleton3D(mod);
    js_register_ax_3d_Skybox(mod);
    js_register_ax_3d_MeshMaterial(mod);
    js_register_ax_3d_MeshRenderer(mod);
    js_register_ax_3d_MeshRendererCache(mod);
    js_register_ax_3d_Terrain(mod);
    js_register_ax_3d_Bundle3D(mod);
}
#endif
