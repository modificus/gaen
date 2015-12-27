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
#include "core/Vector.h"
#include "engine/math.h"
#include "engine/collision.h"
#include "engine/Color.h"

namespace gaen
{

#pragma pack(push, 1)

static_assert(std::numeric_limits<float>::is_iec559, "Must have IEEE 754 floats for AABB collision code");

static const u32 kWorldMaterialCount = 256;
static const u32 kRootMaterialCount = 8;

struct RGB8
{
    u8 r;
    u8 g;
    u8 b;

    RGB8(u8 r, u8 g, u8 b)
        : r(r)
        , g(g)
        , b(b)
    {}

    RGB8(f32 r, f32 g, f32 b)
        : r((u8)(r * 255.0))
        , g((u8)(g * 255.0))
        , b((u8)(b * 255.0))
    {}
};

struct RGBA8
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    RGBA8(u8 r, u8 g, u8 b, u8 a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}
};

struct R32F
{
    f32 r;

    R32F(f32 r)
        : r(r)
    {}
};

struct RG32F
{
    f32 r;
    f32 g;

    RG32F(f32 r, f32 g)
        : r(r)
        , g(g)
    {}
};

struct RGB32F
{
    f32 r;
    f32 g;
    f32 b;

    RGB32F(f32 r, f32 g, f32 b)
        : r(r)
        , g(g)
        , b(b)
    {}
};

struct RGBA32F
{
    f32 r;
    f32 g;
    f32 b;
    f32 a;

    RGBA32F(f32 r, f32 g, f32 b, f32 a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}
};


struct R32I
{
    i32 r;

    R32I(i32 r)
        : r(r)
    {}
};

struct RG32I
{
    i32 r;
    i32 g;

    RG32I(i32 r, i32 g)
        : r(r)
        , g(g)
    {}
};

struct RGB32I
{
    i32 r;
    i32 g;
    i32 b;

    RGB32I(i32 r, i32 g, i32 b)
        : r(r)
        , g(g)
        , b(b)
    {}
};

struct RGBA32I
{
    i32 r;
    i32 g;
    i32 b;
    i32 a;

    RGBA32I(i32 r, i32 g, i32 b, i32 a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}
};


struct R32U
{
    u32 r;

    R32U(u32 r)
        : r(r)
    {}
};

struct RG32U
{
    u32 r;
    u32 g;

    RG32U(u32 r, u32 g)
        : r(r)
        , g(g)
    {}
};

struct RGB32U
{
    u32 r;
    u32 g;
    u32 b;

    RGB32U(u32 r, u32 g, u32 b)
        : r(r)
        , g(g)
        , b(b)
    {}
};

struct RGBA32U
{
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    RGBA32U(u32 r, u32 g, u32 b, u32 a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}
};

class ImageBuffer
{
private:
    u8 * findAddr(u16 x, u16 y)
    {
        return mPixels + (mSize * y * mPixelSize + x * mPixelSize);
    }

    const u8 * findAddr(u16 x, u16 y) const
    {
        return mPixels + (mSize * y * mPixelSize + x * mPixelSize);
    }

    template <typename T>
    T * findLoc(u16 x, u16 y)
    {
        return reinterpret_cast<T*>(findAddr(x, y));
    }

    template <typename T>
    const T * findLoc(u16 x, u16 y) const
    {
        return reinterpret_cast<const T*>(findAddr(x, y));
    }


public:
    ImageBuffer(u16 size, size_t pixelSize);

    template <typename T>
    ImageBuffer(u16 size)
        : ImageBuffer{size, sizeof(T)}
    {
    }

    ~ImageBuffer();

    u16 size() const { return mSize; }
    u8 pixelSize() const { return mPixelSize; }
    u64 bufferSize() const { return mSize * mSize * mPixelSize; }

    template<typename T>
    void imageStore2d(u16 x, u16 y, const T & color)
    {
        ASSERT(mPixelSize == sizeof(T));
        ASSERT(x < mSize && y < mSize);
        *findLoc<T>(x, y) = color;
    }

    template<typename T>
    void imageStore(u32 i, const T & color)
    {
        ASSERT(mPixelSize == sizeof(T));
        ASSERT(i < (u32)(mSize * mSize));
        T * p = reinterpret_cast<T*>(mPixels) + i;
        *p = color;
    }

    template<typename T>
    T imageLoad2d(u16 x, u16 y) const
    {
        ASSERT(mPixelSize == sizeof(T));
        ASSERT(x < mSize && y < mSize);
        return *findLoc<T>(x, y);
    }

    template<typename T>
    T imageLoad(u32 i) const
    {
        ASSERT(mPixelSize == sizeof(T));
        ASSERT(i < (u32)(mSize * mSize));
        return *(reinterpret_cast<const T*>(mPixels) + i);
    }

    u8 * buffer() { return mPixels; }
    const u8 * buffer() const { return mPixels; }

    template <typename T>
    T * buffer() { ASSERT(sizeof(T) == mPixelSize); return reinterpret_cast<T*>(mPixels); }

    template <typename T>
    const T * buffer() const { ASSERT(sizeof(T) == mPixelSize); return reinterpret_cast<const T*>(mPixels); }

    void copy(const ImageBuffer & sourceBuffer);

private:
    u16 mSize;
    u8 mPixelSize;

    u8 * mPixels;
};


struct VoxelMaterial
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

enum VoxelType
{
    kVT_TerminalEmpty = 0,
    kVT_TerminalFull  = 1,
    kVT_NonTerminal   = 2
};

enum VoxelNeighbor
{
    kVN_LeftBottomBack     =  0,
    kVN_LeftBottomMiddle   =  1,
    kVN_LeftBottomFront    =  2,

    kVN_LeftMiddleBack     =  3,
    kVN_LeftMiddleMiddle   =  4,
    kVN_LeftMiddleFront    =  5,

    kVN_LeftTopBack        =  6,
    kVN_LeftTopMiddle      =  7,
    kVN_LeftTopFront       =  8,

    kVN_MiddleBottomBack   =  9,
    kVN_MiddleBottomMiddle = 10,
    kVN_MiddleBottomFront  = 11,

    kVN_MiddleMiddleBack   = 12,
    //kVN_MiddleMiddleMiddle,
    kVN_MiddleMiddleFront  = 13,

    kVN_MiddleTopBack      = 14,
    kVN_MiddleTopMiddle    = 15,
    kVN_MiddleTopFront     = 16,

    kVN_RightBottomBack    = 17,
    kVN_RightBottomMiddle  = 18,
    kVN_RightBottomFront   = 19,

    kVN_RightMiddleBack    = 20,
    kVN_RightMiddleMiddle  = 21,
    kVN_RightMiddleFront   = 22,

    kVN_RightTopBack       = 23,
    kVN_RightTopMiddle     = 24,
    kVN_RightTopFront      = 25
};

struct VoxelRef
{
    u64 type:2;      // Voxel type
    u64 material:10; // Index into VoxelWorld material array
    u64 imageIdx:3;  // Index into images of VoxelWorld
    u64 voxelIdx:23; // Index into image, converted to x/y coords during retrieval from image. 23 bits supports 8192x8192x8byte 64 byte voxels
    u64 filledNeighbors:26;

    bool isTerminalEmpty() const { return type == kVT_TerminalEmpty; }
    bool isTerminalFull() const { return type == kVT_TerminalFull; }

    VoxelRef()
    {
        u64 * pThis = reinterpret_cast<u64*>(this);
        *pThis = 0;
    }

    VoxelRef(VoxelType type, u16 material, u32 imageIdx, u32 voxelIdx)
      : type{type}
      , material{material}
      , imageIdx{imageIdx}
      , voxelIdx{voxelIdx}
      , filledNeighbors{0}
    {}

    static VoxelRef terminal_empty()
    {
        return VoxelRef(kVT_TerminalEmpty, 0, 0, 0);
    }

    static VoxelRef terminal_full(u16 material)
    {
        return VoxelRef(kVT_TerminalFull, material, 0, 0);
    }
};
static_assert(sizeof(VoxelRef) == 8, "VoxelRef not 8 bytes");

struct VoxelRoot
{
    Vec3 pos;           // position    12 bytes - 12
    Mat3 rot;           // rotation    36 bytes - 48
    f32 rad;            // radius       4 bytes - 52
    u32 _PADDING;
    VoxelRef children;  // children     8 bytes - 60
};
static_assert(sizeof(VoxelRoot) == 64, "VoxelRoot not 64 bytes");

enum class SubVoxel : u8
{
    // in binary, xyz, x is most sig bit
    
    LeftBottomBack   = 0,  // 000
    LeftBottomFront  = 1,  // 001
    LeftTopBack      = 2,  // 010
    LeftTopFront     = 3,  // 011

    RightBottomBack  = 4,  // 100
    RightBottomFront = 5,  // 101
    RightTopBack     = 6,  // 110
    RightTopFront    = 7   // 111
};

enum class VoxelFace : u8
{
    None   = 0,
    Left   = 1,
    Right  = 2,
    Bottom = 3,
    Top    = 4,
    Back   = 5,
    Front  = 6
};



struct Voxel
{
    VoxelRef children[8]; // children     4 bytes each
    VoxelRef & operator[] (SubVoxel idx)
    {
        return children[(u32)idx];
    }
    const VoxelRef & operator[] (SubVoxel idx) const
    {
        return children[(u32)idx];
    }
};
static_assert(sizeof(Voxel) == 64, "Voxel not 64 bytes");
// since both are 64 bytes, we can simplify our memory allocator to only support
// 64 byte allocations.
static_assert(sizeof(VoxelRoot) == sizeof(Voxel), "VoxelRoot and Voxel differ in size");

class VoxelWorld
{
public:
    static const u32 kImageCount = 16; // max is 16 since 4 bits in VoxelRef for imageIdx
    static const u32 kImageSize = 8192;
    static const u32 kPixelSize = sizeof(RG32U); // 8
    static const u32 kPixelsPerVoxel = sizeof(Voxel) / kPixelSize;
    static const u32 kVoxelRefsPerPixel = kPixelSize / sizeof(VoxelRef);
    static const u32 kMaxVoxelIndex = 8388608; // 2 ** 23, we have 23 bits for index, which fits perfectly into 8192x8192x8byte image

    static_assert(sizeof(Voxel) % kPixelSize == 0, "sizeof(Voxel) not a multiple of kPixelSize");
    static_assert(kPixelSize % sizeof(VoxelRef) == 0, "kPixelSize not a multiple of sizeof(VoxelRef)");
    static_assert(kVoxelRefsPerPixel == 1, "kVoxelRefsPerPixel is not 1");

    VoxelWorld();

    u8 * imageBuffer(u32 imageIdx)
    {
        ASSERT(imageIdx < mImages.size());
        return mImages[imageIdx].buffer();
    }

    u64 imageBufferSize(u32 imageIdx)
    {
        ASSERT(imageIdx < mImages.size());
        return mImages[imageIdx].bufferSize();
    }

    const ImageBuffer * voxelImage(u32 imageIdx) const
    {
        ASSERT(imageIdx < mImages.size());
        return &mImages[imageIdx];
    }

    ImageBuffer * voxelRoots()
    {
        return &mVoxelRoots;
    }

    u32 voxelRootCount()
    {
        return mVoxelRootCount;
    }

    void imageCoords(u16 * pX, u16 * pY, u32 voxelIdx, SubVoxel subVoxel) const
    {
        u32 pixOffset = voxelIdx * kPixelsPerVoxel;

        pixOffset += (u32)subVoxel;

        *pY = pixOffset / kImageSize;
        *pX = pixOffset % kImageSize;
    }

    VoxelRef voxelRef(u32 imageIdx, u32 voxelIdx, SubVoxel subVoxel) const
    {
        ASSERT(imageIdx < mImages.size());
        ASSERT(voxelIdx < kMaxVoxelIndex);

        u16 x, y;
        imageCoords(&x, &y, voxelIdx, subVoxel);

        RG32U pix = mImages[imageIdx].imageLoad2d<RG32U>(x, y);

        const VoxelRef* ret = reinterpret_cast<const VoxelRef*>(&pix);

        return *ret;
    }

    void setVoxelRef(u32 imageIdx, u32 voxelIdx, SubVoxel subVoxel, const VoxelRef & voxel)
    {
        ASSERT(imageIdx < mImages.size());
        ASSERT(voxelIdx < kMaxVoxelIndex);

        u16 x, y;
        imageCoords(&x, &y, voxelIdx, subVoxel);

        RG32U pix = *reinterpret_cast<const RG32U*>(&voxel);
        mImages[imageIdx].imageStore2d(x, y, pix);
    }

    void addVoxelRoot(const VoxelRoot & voxelRoot);

private:
    VoxelMaterial mMatPalette[kWorldMaterialCount];

    ImageBuffer mVoxelRoots;
    u32 mVoxelRootCount = 0;

    Vector<kMEM_Voxel, ImageBuffer> mImages;
};

class SphereHitTest
{
public:
    SphereHitTest(f32 radius)
      : mRadius(radius) {}

    bool operator()(const AABB_MinMax & aabb) const
    {
        f32 aabbLen = aabb.center().length();
        return aabbLen < mRadius || abs(aabbLen - mRadius) <= (aabb.max.x() - aabb.min.x()) / 1.5f;
    }
private:
    f32 mRadius;
};

template <class HitTestType>
static VoxelRef set_shape_recursive(VoxelWorld & voxelWorld, u32 imageIdx, u32 & voxelIdx, u32 depth, const AABB_MinMax & aabb, HitTestType hitTest)
{
    if (depth == 0)
    {
        if (hitTest(aabb))
            return VoxelRef::terminal_full(1);
        else
            return VoxelRef::terminal_empty();
    }

    AABB_MinMax aabbLbb = voxel_subspace(aabb, SubVoxel::LeftBottomBack);
    AABB_MinMax aabbLbf = voxel_subspace(aabb, SubVoxel::LeftBottomFront);
    AABB_MinMax aabbLtb = voxel_subspace(aabb, SubVoxel::LeftTopBack);
    AABB_MinMax aabbLtf = voxel_subspace(aabb, SubVoxel::LeftTopFront);
    AABB_MinMax aabbRbb = voxel_subspace(aabb, SubVoxel::RightBottomBack);
    AABB_MinMax aabbRbf = voxel_subspace(aabb, SubVoxel::RightBottomFront);
    AABB_MinMax aabbRtb = voxel_subspace(aabb, SubVoxel::RightTopBack);
    AABB_MinMax aabbRtf = voxel_subspace(aabb, SubVoxel::RightTopFront);

    bool lbbIn = hitTest(aabbLbb);
    bool lbfIn = hitTest(aabbLbf);
    bool ltbIn = hitTest(aabbLtb);
    bool ltfIn = hitTest(aabbLtf);
    bool rbbIn = hitTest(aabbRbb);
    bool rbfIn = hitTest(aabbRbf);
    bool rtbIn = hitTest(aabbRtb);
    bool rtfIn = hitTest(aabbRtf);

    VoxelRef lbb = lbbIn ? set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth-1, aabbLbb, hitTest) : VoxelRef::terminal_empty();
    VoxelRef lbf = lbfIn ? set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth-1, aabbLbf, hitTest) : VoxelRef::terminal_empty();
    VoxelRef ltb = ltbIn ? set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth-1, aabbLtb, hitTest) : VoxelRef::terminal_empty();
    VoxelRef ltf = ltfIn ? set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth-1, aabbLtf, hitTest) : VoxelRef::terminal_empty();
    VoxelRef rbb = rbbIn ? set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth-1, aabbRbb, hitTest) : VoxelRef::terminal_empty();
    VoxelRef rbf = rbfIn ? set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth-1, aabbRbf, hitTest) : VoxelRef::terminal_empty();
    VoxelRef rtb = rtbIn ? set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth-1, aabbRtb, hitTest) : VoxelRef::terminal_empty();
    VoxelRef rtf = rtfIn ? set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth-1, aabbRtf, hitTest) : VoxelRef::terminal_empty();


    voxelWorld.setVoxelRef(imageIdx, voxelIdx, SubVoxel::LeftBottomBack,   lbb);
    voxelWorld.setVoxelRef(imageIdx, voxelIdx, SubVoxel::LeftBottomFront,  lbf);
    voxelWorld.setVoxelRef(imageIdx, voxelIdx, SubVoxel::LeftTopBack,      ltb);
    voxelWorld.setVoxelRef(imageIdx, voxelIdx, SubVoxel::LeftTopFront,     ltf);
    voxelWorld.setVoxelRef(imageIdx, voxelIdx, SubVoxel::RightBottomBack,  rbb);
    voxelWorld.setVoxelRef(imageIdx, voxelIdx, SubVoxel::RightBottomFront, rbf);
    voxelWorld.setVoxelRef(imageIdx, voxelIdx, SubVoxel::RightTopBack,     rtb);
    voxelWorld.setVoxelRef(imageIdx, voxelIdx, SubVoxel::RightTopFront,    rtf);

    VoxelRef ret = VoxelRef(kVT_NonTerminal, 1, imageIdx, voxelIdx);
    voxelIdx++;
    return ret;
}

template <class HitTestType>
static VoxelRoot set_shape_generic(VoxelWorld & voxelWorld, u32 imageIdx, u32 voxelIdx, u32 depth, const Vec3 & pos, f32 rad, const Mat3 & rot, HitTestType hitTest)
{
    VoxelRoot voxelRoot;
    voxelRoot.pos = pos;
    voxelRoot.rad = rad;
    voxelRoot.rot = rot;
    voxelRoot.children = set_shape_recursive(voxelWorld, imageIdx, voxelIdx, depth, AABB_MinMax(rad), hitTest);

    voxelWorld.addVoxelRoot(voxelRoot);
    
    return voxelRoot;
}


AABB_MinMax voxel_subspace(const AABB_MinMax & pSpace, SubVoxel subIndex);

bool test_ray_voxel(VoxelRef * pVoxelRef, Vec3 * pNormal, f32 * pZDepth, VoxelFace * pFace, Vec2 * pFaceUv, const VoxelWorld & voxelWorld, const Vec3 & rayPos, const Vec3 & rayDir, const VoxelRoot & root, u32 maxDepth);
bool test_ray_voxel_gpu(VoxelRef * pVoxelRef, Vec3 * pNormal, f32 * pZDepth, VoxelFace * pFace, Vec2 * pFaceUv, const VoxelWorld & voxelWorld, const Vec3 & rayPos, const Vec3 & rayDir, const VoxelRoot & root, u32 maxDepth);

Vec3 voxel_neighbor_offset(VoxelNeighbor vn);

#pragma pack(pop)


} // namespace gaen



#endif // #ifndef GAEN_ENGINE_VOXELS_H

