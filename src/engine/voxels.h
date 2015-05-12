//------------------------------------------------------------------------------
// voxels.h - CPU side voxel support
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

#ifndef GAEN_ENGINE_VOXELS_H
#define GAEN_ENGINE_VOXELS_H

#include "core/base_defines.h"
#include "core/mem.h"
#include "engine/math.h"
#include "engine/collision.h"

namespace gaen
{

#pragma pack(push, 1)

static_assert(std::numeric_limits<float>::is_iec559, "Must have IEEE 754 floats for AABB collision code");

static const u32 kWorldMaterialCount = 256;
static const u32 kRootMaterialCount = 16;

struct VoxelMaterial
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    
};

struct VoxelWorld
{
    // 8 bit palette of materials
    // referenced by VoxelRoot's
    // Voxel worlds can have 256 unique materials.
    VoxelMaterial matPalette[kWorldMaterialCount];
};

struct VoxelRef
{
    u32 material:4; // index into VoxelRoot matPalette, which in turn indexes into VoxelWorld matPalette
    u32 imageIdx:4; // index into one of the images. 0 means this is a terminal voxel with no children
    u32 imageX:12;  // x pixel coord in image where Voxel struct starts, max 4095
    u32 imageY:12;  // y pixel coord in image where Voxel struct starts, max 4095

    // Terminal empty if imageIdx, imageX and imageY all 0
    bool isTerminalEmpty() const { return (*reinterpret_cast<const u32*>(this)) == 0; }

    // Terminal full if imageIdx == 0, and imageX and imageY are max
    bool isTerminalFull() const { return ((*reinterpret_cast<const u32*>(this)) & 0x0fFFffFF) == 0x00FFffFF; }
};
static_assert(sizeof(VoxelRef) == 4, "VoxelRef not 4 byte");

struct VoxelRoot
{
    Vec3 pos;           // position    12 bytes - 12
    Mat3 rot;           // rotation    36 bytes - 48
    f32 rad;            // radius       4 bytes - 52
    VoxelRef children;  // children     4 bytes - 56
    u8 matPalette[kRootMaterialCount]; // VoxelRoot's can have 16 unique materials, references into VoxelWorld palette
};


enum VoxelIndex
{
    // in binary, xyz, x is most sig bit
    
    kVIX_LeftBottomBack   = 0,  // 000
    kVIX_LeftBottomFront  = 1,  // 001
    KVIX_LeftTopBack      = 2,  // 010
    KVIX_LeftTopFront     = 3,  // 011

    kVIX_RightBottomBack  = 4,  // 100
    kVIX_RightBottomFront = 5,  // 101
    kVIX_RightTopBack     = 6,  // 110
    kVIX_RightTopFront    = 7   // 111
};

struct Voxel
{
    VoxelRef children[8]; // children     4 bytes each
};
static_assert(sizeof(Voxel) == 32, "Voxel not 32 bytes");

void voxel_subspace(AABB_MinMax * pSubSpace, const AABB_MinMax & pSpace, VoxelIndex subIndex);
bool test_ray_voxel(VoxelRef * pVoxelRef, const Vec3 & rayPos, const Vec3 & rayDir, const VoxelRoot & root);


#pragma pack(pop)

} // namespace gaen

#endif // #ifndef GAEN_ENGINE_VOXELS_H
