//------------------------------------------------------------------------------
// ViewController.mm - ViewController routine for iOS gaen app
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

#import <GLKit/GLKit.h>

#include "renderergl/gaen_opengl.h"

#include "engine/renderer_api.h"
#include "engine/input.h"
#include "renderergl/Renderer.h"
#include "gaen/gaen.h"

#import "ViewController.h"

gaen::RendererType * g_pRenderer = nullptr;

@interface ViewController ()

@end

@implementation ViewController
- (void)viewDidLoad
{
    using namespace gaen;

    [super viewDidLoad];

    // Create an OpenGL ES context and assign it to the view loaded from storyboard
    GLKView *view = (GLKView *)self.view;

    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    // Configure renderbuffers created by the view
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    
    // Enable multisampling
    view.drawableMultisample = GLKViewDrawableMultisample4X;

    CGRect screenRect = [[UIScreen mainScreen] bounds];
    CGFloat screenWidth = screenRect.size.width;
    CGFloat screenHeight = screenRect.size.height;

    g_pRenderer = GNEW(kMEM_Renderer, RendererType);
    g_pRenderer->init(nullptr, (__bridge void*)view.context, screenWidth, screenHeight);
    Task rendererTask = Task::create(g_pRenderer, HASH::renderer);
    set_renderer(rendererTask);

    start_game_loops();
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
