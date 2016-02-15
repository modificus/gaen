//------------------------------------------------------------------------------
// compute_test.h - Auto-generated shader from compute_test.shd
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014-2016 Lachlan Orr
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
#ifndef GAEN_RENDERERGL_SHADERS_COMPUTE_TEST_H
#define GAEN_RENDERERGL_SHADERS_COMPUTE_TEST_H
#include "renderergl/shaders/Shader.h"
namespace gaen
{
namespace shaders
{

class compute_test : Shader
{
public:
    static Shader * construct();

private:
    compute_test() : Shader(0x62ad79eb /* HASH::compute_test */) {}

    static const u32 kCodeCount = 1;
    static const u32 kUniformCount = 1;

    Shader::ShaderCode mCodes[kCodeCount];
    Shader::VariableInfo mUniforms[kUniformCount];
}; // class compute_test

} // namespace shaders
} // namespace gaen
#endif // #ifdef GAEN_RENDERERGL_SHADERS_COMPUTE_TEST_H
