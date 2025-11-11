#include "js-bindings/bindings/axjs_rhi_auto.hpp"
#include "axmol/rhi/RHITypes.h"
#include "axmol/rhi/ProgramState.h"
#include "axmol/rhi/Texture.h"
#include "axmol/rhi/VertexLayout.h"
#include "axmol/rhi/DriverBase.h"
#include "axmol/rhi/RenderTarget.h"
#include "js-bindings/manual/JSConversions.h"
static int js_register_ax_rhi_BufferUsage(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_BufferUsage(isolate);
    module_BufferUsage.const_("STATIC", 0).const_("DYNAMIC", 1).const_("IMMUTABLE", 2);
    mod.submodule("BufferUsage", module_BufferUsage);
    return 1;
}
static int js_register_ax_rhi_BufferType(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_BufferType(isolate);
    module_BufferType.const_("ARRAY_BUFFER", 0)
        .const_("ELEMENT_ARRAY_BUFFER", 1)
        .const_("UNIFORM_BUFFER", 2)
        .const_("PIXEL_PACK_BUFFER", 3)
        .const_("COUNT", 4)
        .const_("VERTEX", 0)
        .const_("INDEX", 1)
        .const_("UNIFORM", 2);
    mod.submodule("BufferType", module_BufferType);
    return 1;
}
static int js_register_ax_rhi_ShaderStage(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_ShaderStage(isolate);
    module_ShaderStage.const_("UNKNOWN", -1).const_("FRAGMENT", 0).const_("VERTEX", 1).const_("DEFAULT", 0);
    mod.submodule("ShaderStage", module_ShaderStage);
    return 1;
}
static int js_register_ax_rhi_VertexFormat(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_VertexFormat(isolate);
    module_VertexFormat.const_("FLOAT4", 0)
        .const_("FLOAT3", 1)
        .const_("FLOAT2", 2)
        .const_("FLOAT", 3)
        .const_("INT4", 4)
        .const_("INT3", 5)
        .const_("INT2", 6)
        .const_("INT", 7)
        .const_("USHORT4", 8)
        .const_("USHORT2", 9)
        .const_("UBYTE4", 10)
        .const_("MAT4", 11)
        .const_("COUNT", 12);
    mod.submodule("VertexFormat", module_VertexFormat);
    return 1;
}
static int js_register_ax_rhi_PixelFormat(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_PixelFormat(isolate);
    module_PixelFormat.const_("PVRTC4", 0)
        .const_("PVRTC4A", 1)
        .const_("PVRTC2", 2)
        .const_("PVRTC2A", 3)
        .const_("ETC1", 4)
        .const_("ETC2_RGB", 5)
        .const_("ETC2_RGBA", 6)
        .const_("S3TC_DXT1", 7)
        .const_("S3TC_DXT3", 8)
        .const_("S3TC_DXT5", 9)
        .const_("ATC_RGB", 10)
        .const_("ATC_EXPLICIT_ALPHA", 11)
        .const_("ATC_INTERPOLATED_ALPHA", 12)
        .const_("ASTC4x4", 13)
        .const_("ASTC5x4", 14)
        .const_("ASTC5x5", 15)
        .const_("ASTC6x5", 16)
        .const_("ASTC6x6", 17)
        .const_("ASTC8x5", 18)
        .const_("ASTC8x6", 19)
        .const_("ASTC8x8", 20)
        .const_("ASTC10x5", 21)
        .const_("ASTC10x6", 22)
        .const_("ASTC10x8", 23)
        .const_("ASTC10x10", 24)
        .const_("ASTC12x10", 25)
        .const_("ASTC12x12", 26)
        .const_("RGBA8", 27)
        .const_("BGRA8", 28)
        .const_("RGB8", 29)
        .const_("RGB565", 30)
        .const_("RGBA4", 31)
        .const_("RGB5A1", 32)
        .const_("R8", 33)
        .const_("RG8", 34)
        .const_("RGBA32F", 35)
        .const_("D24S8", 36)
        .const_("COUNT", 37)
        .const_("NONE", -1);
    mod.submodule("PixelFormat", module_PixelFormat);
    return 1;
}
static int js_register_ax_rhi_TextureUsage(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_TextureUsage(isolate);
    module_TextureUsage.const_("READ", 0).const_("WRITE", 1).const_("RENDER_TARGET", 2);
    mod.submodule("TextureUsage", module_TextureUsage);
    return 1;
}
static int js_register_ax_rhi_IndexFormat(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_IndexFormat(isolate);
    module_IndexFormat.const_("U_SHORT", 1).const_("U_INT", 2);
    mod.submodule("IndexFormat", module_IndexFormat);
    return 1;
}
static int js_register_ax_rhi_PrimitiveType(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_PrimitiveType(isolate);
    module_PrimitiveType.const_("POINT", 0)
        .const_("LINE", 1)
        .const_("LINE_LOOP", 2)
        .const_("LINE_STRIP", 3)
        .const_("TRIANGLE", 4)
        .const_("TRIANGLE_STRIP", 5);
    mod.submodule("PrimitiveType", module_PrimitiveType);
    return 1;
}
static int js_register_ax_rhi_BlendFactor(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_BlendFactor(isolate);
    module_BlendFactor.const_("ZERO", 0)
        .const_("ONE", 1)
        .const_("SRC_COLOR", 2)
        .const_("ONE_MINUS_SRC_COLOR", 3)
        .const_("SRC_ALPHA", 4)
        .const_("ONE_MINUS_SRC_ALPHA", 5)
        .const_("DST_COLOR", 6)
        .const_("ONE_MINUS_DST_COLOR", 7)
        .const_("DST_ALPHA", 8)
        .const_("ONE_MINUS_DST_ALPHA", 9)
        .const_("CONSTANT_ALPHA", 10)
        .const_("SRC_ALPHA_SATURATE", 11)
        .const_("ONE_MINUS_CONSTANT_ALPHA", 12)
        .const_("BLEND_COLOR", 13);
    mod.submodule("BlendFactor", module_BlendFactor);
    return 1;
}
static int js_register_ax_rhi_ColorWriteMask(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_ColorWriteMask(isolate);
    module_ColorWriteMask.const_("RED_BIT", 0)
        .const_("GREEN_BIT", 1)
        .const_("BLUE_BIT", 2)
        .const_("ALPHA_BIT", 3)
        .const_("NONE", 0)
        .const_("RED", 1)
        .const_("GREEN", 2)
        .const_("BLUE", 4)
        .const_("ALPHA", 8)
        .const_("ALL", 15);
    mod.submodule("ColorWriteMask", module_ColorWriteMask);
    return 1;
}
static int js_register_ax_rhi_CullMode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_CullMode(isolate);
    module_CullMode.const_("NONE", 0).const_("BACK", 1).const_("FRONT", 2);
    mod.submodule("CullMode", module_CullMode);
    return 1;
}
static int js_register_ax_rhi_Winding(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_Winding(isolate);
    module_Winding.const_("CLOCK_WISE", 0).const_("COUNTER_CLOCK_WISE", 1);
    mod.submodule("Winding", module_Winding);
    return 1;
}
static int js_register_ax_rhi_TextureType(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_TextureType(isolate);
    module_TextureType.const_("TEXTURE_2D", 0).const_("TEXTURE_CUBE", 1);
    mod.submodule("TextureType", module_TextureType);
    return 1;
}
static int js_register_ax_rhi_SamplerAddressMode(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_SamplerAddressMode(isolate);
    module_SamplerAddressMode.const_("REPEAT", 0).const_("MIRROR", 1).const_("CLAMP", 2).const_("BORDER", 3).const_("CLAMP_TO_EDGE", 2);
    mod.submodule("SamplerAddressMode", module_SamplerAddressMode);
    return 1;
}
static int js_register_ax_rhi_SamplerFilter(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_SamplerFilter(isolate);
    module_SamplerFilter.const_("MIN_NEAREST", 0)
        .const_("MIN_LINEAR", 1)
        .const_("MIN_ANISOTROPIC", 2)
        .const_("MAG_NEAREST", 0)
        .const_("MAG_LINEAR", 1)
        .const_("MIP_NEAREST", 0)
        .const_("MIP_LINEAR", 1)
        .const_("MIP_DEFAULT", 3)
        .const_("NEAREST", 0)
        .const_("LINEAR", 1);
    mod.submodule("SamplerFilter", module_SamplerFilter);
    return 1;
}
static int js_register_ax_rhi_TextureCubeFace(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::module module_TextureCubeFace(isolate);
    module_TextureCubeFace.const_("POSITIVE_X", 0)
        .const_("NEGATIVE_X", 1)
        .const_("POSITIVE_Y", 2)
        .const_("NEGATIVE_Y", 3)
        .const_("POSITIVE_Z", 4)
        .const_("NEGATIVE_Z", 5);
    mod.submodule("TextureCubeFace", module_TextureCubeFace);
    return 1;
}
static void js_register_ax_rhi_Program(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::rhi::Program> class_Program(isolate);
    class_Program.template inherit<ax::Object>()
        .member_function(
            "getUniformLocation",
            [](ax::rhi::Program* self, ax::rhi::Uniform arg0) { return self->getUniformLocation(arg0); },
            [](ax::rhi::Program* self, std::string_view arg0) { return self->getUniformLocation(arg0); })
        .member_function(
            "getVertexInputDesc",
            [](ax::rhi::Program* self, ax::rhi::VertexInputKind arg0) { return self->getVertexInputDesc(arg0); },
            [](ax::rhi::Program* self, std::string_view arg0) { return self->getVertexInputDesc(arg0); })
        .member_function("getMaxVertexLocation", &ax::rhi::Program::getMaxVertexLocation)
        .member_function("getMaxFragmentLocation", &ax::rhi::Program::getMaxFragmentLocation)
        .member_function("getVertexShaderSource", &ax::rhi::Program::getVertexShaderSource)
        .member_function("getFragmentShaderSource", &ax::rhi::Program::getFragmentShaderSource)
        .member_function("getProgramType", &ax::rhi::Program::getProgramType)
        .member_function("getProgramId", &ax::rhi::Program::getProgramId)
        .member_function("getUniformBufferSize", &ax::rhi::Program::getUniformBufferSize)
        .member_function("getVertexLayout", &ax::rhi::Program::getVertexLayout)
        .auto_wrap_objects(true);
    mod.class_("Program", class_Program);
}
static void js_register_ax_rhi_VertexLayout(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::rhi::VertexLayout> class_VertexLayout(isolate);
    class_VertexLayout.template inherit<ax::Object>()
        .member_function("getDesc", &ax::rhi::VertexLayout::getDesc)
        .member_function("getStride", &ax::rhi::VertexLayout::getStride)
        .member_function("getInstanceStride", &ax::rhi::VertexLayout::getInstanceStride)
        .member_function("getHash", &ax::rhi::VertexLayout::getHash)
        .member_function("getBuiltinId", &ax::rhi::VertexLayout::getBuiltinId)
        .auto_wrap_objects(true);
    mod.class_("VertexLayout", class_VertexLayout);
}
static void js_register_ax_rhi_ProgramState(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::rhi::ProgramState> class_ProgramState(isolate);
    class_ProgramState.ctor([](ax::rhi::Program* arg0) { return new ax::rhi::ProgramState(arg0); })
        .template inherit<ax::Object>()
        .member_function("clone", &ax::rhi::ProgramState::clone)
        .member_function("getProgram", &ax::rhi::ProgramState::getProgram)
        .member_function(
            "getVertexInputDesc",
            [](ax::rhi::ProgramState* self, ax::rhi::VertexInputKind arg0) { return self->getVertexInputDesc(arg0); },
            [](ax::rhi::ProgramState* self, std::string_view arg0) { return self->getVertexInputDesc(arg0); })
        .member_function(
            "setTexture",
            [](ax::rhi::ProgramState* self, ax::rhi::UniformLocation arg0, int arg1, ax::rhi::Texture* arg2)
            { self->setTexture(arg0, arg1, arg2); },
            [](ax::rhi::ProgramState* self, ax::rhi::Texture* arg0) { self->setTexture(arg0); })
        .member_function("setParameterAutoBinding", &ax::rhi::ProgramState::setParameterAutoBinding)
        .member_function("getBuiltinVertexLayout", &ax::rhi::ProgramState::getBuiltinVertexLayout)
        .member_function("getBatchId", &ax::rhi::ProgramState::getBatchId)
        .member_function("isBatchable", &ax::rhi::ProgramState::isBatchable)
        .member_function("updateBatchId", &ax::rhi::ProgramState::updateBatchId)
        .auto_wrap_objects(true);
    mod.class_("ProgramState", class_ProgramState);
}
static void js_register_ax_rhi_Texture(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::rhi::Texture> class_Texture(isolate);
    class_Texture.template inherit<ax::Object>()
        .member_function("updateSamplerDesc", &ax::rhi::Texture::updateSamplerDesc)
        .member_function("getPixelFormat", &ax::rhi::Texture::getPixelFormat)
        .member_function("getTextureUsage", &ax::rhi::Texture::getTextureUsage)
        .member_function("getTextureType", &ax::rhi::Texture::getTextureType)
        .member_function("hasMipmaps", &ax::rhi::Texture::hasMipmaps)
        .member_function("getWidth", &ax::rhi::Texture::getWidth)
        .member_function("getHeight", &ax::rhi::Texture::getHeight)
        .member_function("updateData", &ax::rhi::Texture::updateData)
        .member_function("updateSubData", &ax::rhi::Texture::updateSubData)
        .member_function("updateFaceData", &ax::rhi::Texture::updateFaceData)
        .member_function(
            "shouldGenMipmaps",
            [](ax::rhi::Texture* self) { return self->shouldGenMipmaps(); },
            [](ax::rhi::Texture* self, int arg0) { return self->shouldGenMipmaps(arg0); })
        .auto_wrap_objects(true);
    mod.class_("Texture", class_Texture);
}
static void js_register_ax_rhi_DriverBase(v8pp::module& mod)
{
    v8::Isolate* isolate = mod.isolate();
    v8pp::class_<ax::rhi::DriverBase> class_DriverBase(
        isolate, [](v8::Isolate*, const auto&) { /* No constructor class will not be destroyed by script */ });
    class_DriverBase.member_function("createDefaultRenderTarget", &ax::rhi::DriverBase::createDefaultRenderTarget)
        .member_function(
            "createRenderTarget",
            [](ax::rhi::DriverBase* self) { return self->createRenderTarget(); },
            [](ax::rhi::DriverBase* self, ax::rhi::Texture* arg0) { return self->createRenderTarget(arg0); },
            [](ax::rhi::DriverBase* self, ax::rhi::Texture* arg0, ax::rhi::Texture* arg1) { return self->createRenderTarget(arg0, arg1); })
        .member_function("createProgram", &ax::rhi::DriverBase::createProgram)
        .member_function("resetState", &ax::rhi::DriverBase::resetState)
        .member_function("getVendor", &ax::rhi::DriverBase::getVendor)
        .member_function("getRenderer", &ax::rhi::DriverBase::getRenderer)
        .member_function("getVersion", &ax::rhi::DriverBase::getVersion)
        .member_function("getShaderVersion", &ax::rhi::DriverBase::getShaderVersion)
        .member_function("hasExtension", &ax::rhi::DriverBase::hasExtension)
        .member_function("dumpExtensions", &ax::rhi::DriverBase::dumpExtensions)
        .member_function("checkForFeatureSupported", &ax::rhi::DriverBase::checkForFeatureSupported)
        .member_function("getMaxTextureSize", &ax::rhi::DriverBase::getMaxTextureSize)
        .member_function("getMaxAttributes", &ax::rhi::DriverBase::getMaxAttributes)
        .member_function("getMaxTextureUnits", &ax::rhi::DriverBase::getMaxTextureUnits)
        .member_function("getMaxSamplesAllowed", &ax::rhi::DriverBase::getMaxSamplesAllowed)
        .static_function("getInstance", &ax::rhi::DriverBase::getInstance)
        .static_function("destroyInstance", &ax::rhi::DriverBase::destroyInstance)
        .auto_wrap_objects(true);
    mod.class_("DriverBase", class_DriverBase);
}
void js_register_all_ax_rhi(JsRegistry& registry)
{
    v8pp::module& mod = registry.module("axrhi");
    js_register_ax_rhi_BufferUsage(mod);
    js_register_ax_rhi_BufferType(mod);
    js_register_ax_rhi_ShaderStage(mod);
    js_register_ax_rhi_VertexFormat(mod);
    js_register_ax_rhi_PixelFormat(mod);
    js_register_ax_rhi_TextureUsage(mod);
    js_register_ax_rhi_IndexFormat(mod);
    js_register_ax_rhi_PrimitiveType(mod);
    js_register_ax_rhi_BlendFactor(mod);
    js_register_ax_rhi_ColorWriteMask(mod);
    js_register_ax_rhi_CullMode(mod);
    js_register_ax_rhi_Winding(mod);
    js_register_ax_rhi_TextureType(mod);
    js_register_ax_rhi_SamplerAddressMode(mod);
    js_register_ax_rhi_SamplerFilter(mod);
    js_register_ax_rhi_TextureCubeFace(mod);
    js_register_ax_rhi_Program(mod);
    js_register_ax_rhi_VertexLayout(mod);
    js_register_ax_rhi_ProgramState(mod);
    js_register_ax_rhi_Texture(mod);
    js_register_ax_rhi_DriverBase(mod);
}
