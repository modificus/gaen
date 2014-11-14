//------------------------------------------------------------------------------
// BlockMemory.h - Simple memory manager for entity dynamic data types
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

#ifndef GAEN_ENGINE_BLOCKMEMORY_H
#define GAEN_ENGINE_BLOCKMEMORY_H

#include "core/base_defines.h"
#include "engine/Block.h"

namespace gaen
{

enum BlockType
{
    kBKTY_Uninitialized = 0,

    kBKTY_String        = 1,

};

// 12 characters left after string header data in first BlockData
static const u32 kCharsInFirstBlock = 12;

struct BlockString
{
    u16 charCount;
    char chars[kCharsInFirstBlock];

    const char * c_str() const
    {
        ASSERT(chars[charCount-1] == '\0');
        return &chars[0];
    }
private:
};

struct BlockData
{
    static const u16 kMaxRefCount = 15;

    u16 type:4;
    u16 blockCount:6;  // changing this affects kBlocksPerChunk
    u16 isAllocated:1;
    u16 isInitial:1;   // is the initial block of an allocated series of blocks
    u16 refCount:4;

    union
    {
        BlockString string;
      
        // add additional types here, like "list" and "dict"
    } data;

    static BlockData * from_string(BlockString * pString);

    void init() { *reinterpret_cast<u16*>(this) = 0; }
};

static_assert(sizeof(BlockData) == sizeof(Block), "BlockData must be same size as a Block");
static_assert(sizeof(BlockData) == 16, "BlockData must be same size as a Block");

//------------------------------------------------------------------------------

struct ChunkHeader
{
    u32 magic;
    u8 freeCount;
    u8 chunkIdx;
    bool needsCollection;
    u8 PADDING[9];
};

static_assert(sizeof(ChunkHeader) == sizeof(Block), "ChunkHeader must be same size as a Block");

class Chunk
{
public:
    static const u32 kBlocksPerChunk = 63; // changing this affects BlockData::blockCount

    Chunk(u8 chunkIdx);

    u8 chunkIdx() { return mHeader.chunkIdx; }

    // Allocate and return u16 block data index.
    // Returns Address::kInvalidIdx if no space.
    u8 alloc(u8 blockCount);
    void free(u8 blockIdx);

    BlockData & blockData(u8 blockIdx)
    {
        ASSERT(blockIdx < kBlocksPerChunk);
        return mBlocks[blockIdx];
    }

    static Chunk * from_block_data(BlockData * pBd);
    u8 indexFromBlockData(BlockData * pBd);

    void addRef(u8 blockIdx);
    void release(u8 blockIdx);

    bool needsCollection() { return mHeader.needsCollection; }
    void collect();

    u32 availableBlocks();
    u32 usedBlocks();
    u32 totalBlocks();
private:
    static const u32 kMagic = 0xb70cb70c;

    ChunkHeader mHeader;
    BlockData mBlocks[kBlocksPerChunk];
};

// max string is length of chunk
static const u32 kMaxStringLength = (Chunk::kBlocksPerChunk - 1) * kBlockSize + kCharsInFirstBlock - 1; // -1 for null terminator

//------------------------------------------------------------------------------

struct Address
{
    static const u8 kInvalidIdx = 255;

    u8 chunkIdx;
    u8 blockIdx;

    Address()
      : chunkIdx(kInvalidIdx)
      , blockIdx(kInvalidIdx) {}

    Address(u8 chunkIdx, u8 blockIdx)
      : chunkIdx(chunkIdx)
      , blockIdx(blockIdx) {}

};

//------------------------------------------------------------------------------

class CmpString
{
    friend class BlockMemory;
public:
    CmpString(BlockData * pBlockData)
      : mpBlockData(pBlockData) { ASSERT(pBlockData->type == kBKTY_String); }

    char * c_str() { return &mpBlockData->data.string.chars[0]; }
    const char * c_str() const { return &mpBlockData->data.string.chars[0]; }
    u16 size() { return mpBlockData->data.string.charCount; }

private:
    BlockData * mpBlockData;
};

//------------------------------------------------------------------------------

class BlockMemory
{
public:
    static const u32 kChunkCount = 16;

    BlockMemory();
    ~BlockMemory();

    CmpString stringAlloc(u16 charCount);
    CmpString stringAlloc(const char * val);
    
    Address alloc(u8 blockCount);
    void free(Address addr);

    void addRef(Address addr);
    void release(Address addr);
    void addRef(const CmpString & str);
    void release(const CmpString & str);

    void collect();

    u32 availableBlocks();
    u32 usedBlocks();
    u32 totalBlocks();
private:
    BlockData & blockData(Address & addr);

    bool mNeedsCollection;
    Chunk * mChunks[kChunkCount];
};

} // namespace gaen

#endif // #ifndef GAEN_ENGINE_BLOCKMEMORY_H