//------------------------------------------------------------------------------
// registration.cpp - Autogenerated from script Entities and Components
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

#include "engine/Registry.h"

namespace gaen
{

extern void register_component__gaen__lights__Directional(Registry & registry);
extern void register_component__gaen__shapes__Box(Registry & registry);
extern void register_component__gaen__shapes__Cone(Registry & registry);
extern void register_component__gaen__shapes__Cylinder(Registry & registry);
extern void register_component__gaen__shapes__QuadSphere(Registry & registry);
extern void register_component__gaen__shapes__Sphere(Registry & registry);
extern void register_component__gaen__utils__Timer(Registry & registry);
extern void register_component__gaen__utils__WasdCamera(Registry & registry);
extern void register_component__gaen__utils__WasdRot(Registry & registry);
extern void register_component__test__TestComp(Registry & registry);
extern void register_component__test__TestCompEmpty(Registry & registry);
extern void register_entity__init__Camera(Registry & registry);
extern void register_entity__init__Light(Registry & registry);
extern void register_entity__init__Shape(Registry & registry);
extern void register_entity__init__Start(Registry & registry);
extern void register_entity__test__Test(Registry & registry);

void register_all_entities_and_components(Registry & registry)
{
    register_component__gaen__lights__Directional(registry);
    register_component__gaen__shapes__Box(registry);
    register_component__gaen__shapes__Cone(registry);
    register_component__gaen__shapes__Cylinder(registry);
    register_component__gaen__shapes__QuadSphere(registry);
    register_component__gaen__shapes__Sphere(registry);
    register_component__gaen__utils__Timer(registry);
    register_component__gaen__utils__WasdCamera(registry);
    register_component__gaen__utils__WasdRot(registry);
    register_component__test__TestComp(registry);
    register_component__test__TestCompEmpty(registry);
    register_entity__init__Camera(registry);
    register_entity__init__Light(registry);
    register_entity__init__Shape(registry);
    register_entity__init__Start(registry);
    register_entity__test__Test(registry);
}

} // namespace gaen
