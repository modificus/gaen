//------------------------------------------------------------------------------
// AssetTypes.h - Mapping of asset extension to various asset properties
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

#ifndef GAEN_ENGINE_ASSET_TYPES_H
#define GAEN_ENGINE_ASSET_TYPES_H

#include "core/mem.h"
#include "core/HashMap.h"

#include "assets/AssetType.h"

namespace gaen
{

class AssetTypes
{
public:
    AssetTypes();

    void registerAssetType(AssetType * assetType);

    void registerProjectAssetTypes();

    const AssetType * assetTypeFromExt(const char * ext) const;

    // Dealing with 4 character codes can be endian dangerous, but we
    // only do this within a running process, these 4 character codes
    // are never persisted between processes.
    static u32 ext_to_4cc(const char * ext)
    {
        return *reinterpret_cast<const u32*>(ext);
    }

private:
    HashMap<kMEM_Engine, u32, UniquePtr<AssetType>> mExtToAssetTypeMap;
};

} // namespace gaen

#endif // #ifndef GAEN_ENGINE_ASSET_TYPES_H


