//------------------------------------------------------------------------------
// Gspr.cpp - Sprites with animations, depend on a gatl for images
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

#include "assets/AssetTypes.h"
#include "assets/Gatl.h"
#include "assets/Gspr.h"

namespace gaen
{

const char * Gspr::kMagic = "gspr";
const u32 Gspr::kMagic4cc = AssetTypes::ext_to_4cc(Gspr::kMagic);

static u32 anim_toc_offset(size_t atlasPathLen)
{
    return (u32)align(sizeof(Gspr) + atlasPathLen + 1, 8);
}

bool Gspr::is_valid(const void * pBuffer, u64 size)
{
    if (size < sizeof(Gspr))
        return false;

    const Gspr * pAssetData = reinterpret_cast<const Gspr*>(pBuffer);

    if (0 != strncmp(kMagic, pAssetData->mMagic, 4))
        return false;

    if (size != pAssetData->mSize)
        return false;

    if (pAssetData->mFrameWidth == 0 ||
        pAssetData->mFrameHeight == 0)
        return false;

    if (pAssetData->mAnimCount == 0 ||
        pAssetData->mAnimTocOffset == 0)
        return false;

    size_t atlasPathLen = strlen(pAssetData->atlasPath());
    if (pAssetData->mAnimTocOffset != reinterpret_cast<const char*>(pAssetData) + anim_toc_offset(atlasPathLen) - reinterpret_cast<const char*>(pAssetData))
        return false;

    const AnimInfo * pAnims = pAssetData->anims();
    if ((char*)pAnims <= (char*)(pAssetData+1) || (char*)pAnims > (char*)pAssetData->framesEnd())
        return false;

    u32 frameCount = 0;
    for (u32 animIdx = 0; animIdx < pAssetData->mAnimCount; ++animIdx)
    {
        const AnimInfo & anim = pAssetData->anims()[animIdx];

        if (anim.animHash == 0)
            return false;
        if (anim.firstFrame != frameCount)
            return false;
        frameCount += anim.frameCount;
    }

    u64 calcSize = (anim_toc_offset(atlasPathLen) +
                    pAssetData->mAnimCount * sizeof(AnimInfo) +
                    frameCount * sizeof(u32));

    if (calcSize != size)
        return false;

    if (reinterpret_cast<const char*>(pAssetData->framesEnd()) - reinterpret_cast<const char*>(pAssetData) != calcSize)
        return false;

    if (required_size(pAssetData->atlasPath(), pAssetData->mAnimCount, frameCount) != size)
        return false;

    return true;
}

Gspr * Gspr::instance(void * pBuffer, u64 size)
{
    if (!is_valid(pBuffer, size))
    {
        PANIC("Invalid Gspr buffer");
        return nullptr;
    }

    return reinterpret_cast<Gspr*>(pBuffer);
}

const Gspr * Gspr::instance(const void * pBuffer, u64 size)
{
    return instance(const_cast<void*>(pBuffer), size);
}

u64 Gspr::required_size(const char * atlasPath, u32 animCount, u32 totalFrameCount)
{
    return (anim_toc_offset(strlen(atlasPath)) +
            animCount * sizeof(AnimInfo) +
            totalFrameCount * sizeof(u32));

    return 0;
}

Gspr * Gspr::create(u32 frameWidth,
                    u32 frameHeight,
                    const char * atlasPath,
                    u32 animCount,
                    u32 totalFrameCount)
{
    u64 size = Gspr::required_size(atlasPath, animCount, totalFrameCount);
    Gspr * pGspr = (Gspr*)GALLOC(kMEM_Texture, size);

    ASSERT(strlen(kMagic) == 4);
    strncpy(pGspr->mMagic, kMagic, 4);

    PANIC_IF(frameWidth == 0 || frameHeight == 0, "Invalid frameWidth or frameHeight");
    PANIC_IF(animCount == 0 || totalFrameCount == 0, "Invalid animCount or totalFrameCount");

    pGspr->mFrameWidth = frameWidth;
    pGspr->mFrameHeight = frameHeight;

    ASSERT(atlasPath);
    u64 atlasPathLen = strlen(atlasPath);

    strncpy(reinterpret_cast<char*>(pGspr+1), atlasPath, atlasPathLen);
    reinterpret_cast<char*>(pGspr+1)[atlasPathLen] = '\0'; // null terminate

    pGspr->mAnimCount = animCount;
    pGspr->mAnimTocOffset = anim_toc_offset(atlasPathLen);

    pGspr->mSize = size;

    pGspr->pAtlas = nullptr;

    // zero out memory for good measure
    memset(reinterpret_cast<char*>(pGspr) + pGspr->mAnimTocOffset,
           0,
           animCount * sizeof(AnimInfo) + totalFrameCount * sizeof(u32));

    return pGspr;
}

const AnimInfo * Gspr::getAnim(u32 animHash) const
{
    const AnimInfo * pAnims = anims();
    for (u32 i = 0; i < mAnimCount; ++i)
    {
        if (pAnims[i].animHash == animHash)
            return &pAnims[i];
    }
    ERR("Failed to find animHash: %u", animHash);
    return pAnims;
}

const GlyphCoords & Gspr::getFrame(const AnimInfo * pAnim, u32 frameIdx) const
{
    ASSERT(pAtlas);

    ASSERT(pAnim);
    ASSERT(pAnim > anims() && pAnim < anims() + mAnimCount);

    // roll frameIdx around if it's greater than max
    frameIdx = frameIdx % pAnim->frameCount;

    u32 frame = frames()[pAnim->firstFrame];

    ASSERT(frame < pAtlas->glyphCount());
    return pAtlas->coords(frame);
}

AnimInfo * Gspr::anims()
{
    return reinterpret_cast<AnimInfo*>(reinterpret_cast<char*>(this) + mAnimTocOffset);
}

const AnimInfo * Gspr::anims() const
{
    return const_cast<Gspr*>(this)->anims();
}

u32 * Gspr::frames()
{
    return reinterpret_cast<u32*>(anims() + mAnimCount);
}

const u32 * Gspr::frames() const
{
    return const_cast<Gspr*>(this)->frames();
}

u32 * Gspr::framesEnd()
{
    return reinterpret_cast<u32*>(reinterpret_cast<char*>(this) + mSize);
}

const u32 * Gspr::framesEnd() const
{
    return const_cast<Gspr*>(this)->framesEnd();
}


} // namespace gaen

