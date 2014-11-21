//------------------------------------------------------------------------------'
// system_api_meta.cpp - Autogenerated with codegen.py from system_api.h
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
#include "engine/stdafx.h"

#include "compose/system_api_meta.h"

namespace gaen
{

ApiSignature gApiSignatures[] = {
                                    { HASH::print, kDT_void, { CONST_DT(kDT_string) } },
                                    { HASH::insert_task, kDT_void, { CONST_DT(kDT_uint) } },
                                    { HASH::radians, kDT_float, { CONST_DT(kDT_float) } },
                                    { HASH::degrees, kDT_float, { CONST_DT(kDT_float) } },
                                    { HASH::create_shape_box, kDT_handle, { CONST_DT(kDT_vec3), CONST_DT(kDT_color) } },
                                    { HASH::watch_input_state, kDT_void, { CONST_DT(kDT_uint), CONST_DT(kDT_uint), CONST_DT(kDT_uint) } },
                                    { HASH::transform_rotate, kDT_mat34, { CONST_DT(kDT_vec3) } },
                                    { HASH::renderer_gen_uid, kDT_uint, {  } },
                                    { HASH::renderer_insert_model_instance, kDT_void, { CONST_DT(kDT_uint), kDT_handle } },
                                    { HASH::renderer_transform_model_instance, kDT_void, { CONST_DT(kDT_uint), CONST_DT(kDT_mat34) } },
                                    { HASH::renderer_remove_model_instance, kDT_void, { CONST_DT(kDT_uint) } },
                                    { HASH::renderer_insert_light_directional, kDT_void, { CONST_DT(kDT_uint), CONST_DT(kDT_vec3), CONST_DT(kDT_color) } },
                                    { HASH::renderer_remove_light_directional, kDT_void, { CONST_DT(kDT_uint) } },

                                    { 0 }
                                };

} // namespace gaen
