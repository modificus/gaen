//------------------------------------------------------------------------------
// RendererGL.h - OpenGL Renderer
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014 Lachlan Orr
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

#ifndef GAEN_RENDERERGL_RENDERERGL_H
#define GAEN_RENDERERGL_RENDERERGL_H

#if IS_PLATFORM_WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
namespace gaen
{
typedef HDC RenderDevice;
typedef HGLRC RenderGLDevice;
}
#else
#error Need to implement a similar concept on other platforms
#endif


namespace gaen
{

class RendererGL
{
public:
    void render();

    // Set some OS specific device values
    void setRenderDevice(RenderDevice renderDevice, RenderGLDevice renderGLDevice);

};


} // namespace gaen

#endif // #ifndef GAEN_RENDERERGL_RENDERERGL_H

