//------------------------------------------------------------------------------
// Shader.h - Base class for shaders
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014-2015 Lachlan Orr
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//   1. The origin of this software must not be misrepresented; you must not
//   claim that you wrote the original software. If you use this software
//   in a product, an acknowledgment in the product documentation would be
//   appreciated but is not required.
//
//   2. Altered source versions must be plainly marked as such, and must not be
//   misrepresented as being the original software.
//
//   3. This notice may not be removed or altered from any source
//   distribution.
//------------------------------------------------------------------------------

#ifndef GAEN_RENDERERGL_SHADERS_SHADER_H
#define GAEN_RENDERERGL_SHADERS_SHADER_H

#include "core/base_defines.h"
#include "engine/math.h"

#include "renderergl/gaen_opengl.h"


namespace gaen
{
namespace shaders
{

class Shader
{
public:
    u32 nameHash() { return mNameHash; }

    void load();
    void unload();

    void use();

    void setUniformVec3(u32 nameHash, const Vec3 & value);
    void setUniformVec4(u32 nameHash, const Vec4 & value);

    void setUniformMat3(u32 nameHash, const Mat3 & value);
    void setUniformMat4(u32 nameHash, const Mat4 & value);

    static bool compile_shader(GLuint * pShader, GLenum type, const char * shaderCode, const char * headerCode = nullptr);

protected:
    struct ShaderCode
    {
        u32 stage;
        const char * filename;
        const char * code;
    };

    struct VariableInfo
    {
        u32 nameHash;
        u32 index:8;
        u32 type:24;
    };

    Shader(u32 nameHash);
    VariableInfo * findUniform(u32 nameHash, u32 type);

    u32 mNameHash;
    GLuint mProgramId;

    u32 mCodeCount;
    u32 mUniformCount;
    u32 mAttributeCount;

    ShaderCode * mpCodes;
    VariableInfo * mpUniforms;
    VariableInfo * mpAttributes;

    bool mIsLoaded = false;

}; // class Shader


} // namespace shaders
} // namespace gaen

#endif // #ifndef GAEN_RENDERERGL_SHADERS_SHADER_H
