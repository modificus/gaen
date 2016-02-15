//------------------------------------------------------------------------------
// gaen_opengl.h - Win32 opengl function pointers
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

#ifndef GAEN_GAEN_OPENGL_H
#define GAEN_GAEN_OPENGL_H

#include "core/base_defines.h"

#if IS_PLATFORM_WIN32
 #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
 #endif // #ifndef WIN32_LEAN_AND_MEAN
 #include <windows.h>
 #include "renderergl/win32gl.h"
 namespace gaen
 {
 typedef HDC device_context;
 typedef HGLRC render_context;
 }
 #define OPENGL3 HAS_X
 #define GL_CLEAR_DEPTH glClearDepth
 #define SHADER_HEADER "#version 430 core\n#define OPENGL3\n"
#elif IS_PLATFORM_OSX
 #include <OpenGL/gl3.h>
 namespace gaen
 {
 typedef void* device_context;
 typedef void* render_context;
 }
 #define OPENGL3 HAS__
 #define GL_CLEAR_DEPTH glClearDepth
 #define SHADER_HEADER ""
#elif IS_PLATFORM_IOS
 #include <OpenGLES/ES3/gl.h>
 namespace gaen
 {
 typedef void* device_context;
 typedef void* render_context;
 }
 #define OPENGL3 HAS__
 #define GL_CLEAR_DEPTH glClearDepthf
 #define SHADER_HEADER "#define PLATFORM_IOS\n"
#else
#error Need to implement a similar concepts on other platforms
#endif

#endif // #ifndef GAEN_GAEN_OPENGL_H

