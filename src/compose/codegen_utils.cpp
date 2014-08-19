//------------------------------------------------------------------------------
// codegen_utils.cpp - Shared utilities used during code generation
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

#include <algorithm>

#include "engine/Block.h"
#include "compose/codegen_utils.h"

namespace gaen
{

bool is_update_message_def(const Ast * pAst)
{
    return (pAst->type == kAST_MessageDef &&
            pAst->pSymRec &&
            0 == strcmp(pAst->pSymRec->name, "update"));
}

const Ast * find_update_message_def(const Ast * pAst)
{
    for (Ast * pChild : pAst->pChildren->nodes)
    {
        if (is_update_message_def(pChild))
        {
            return pChild;
        }
    }
    return nullptr;
}


u32 data_type_cell_count(DataType dataType)
{
    switch (dataType)
    {
    case kDT_int:
    case kDT_uint:
    case kDT_float:
    case kDT_bool:
    case kDT_char:
        return 1;
    case kDT_vec3:
        return 3;
    case kDT_vec4:
        return 4;
    case kDT_mat3:
        return 9;
    case kDT_mat34:
        return 12;
    case kDT_mat4:
        return 16;
    default:
        return 0;
    }
}


u32 props_and_fields_count(const Ast * pAst)
{
    u32 count = 0;
    for (Ast *pChild : pAst->pChildren->nodes)
    {
        if (is_prop_or_field(pChild->pSymRec))
            count++;
    }
    return count;
}

static BlockInfo * find_next_fit(CompVector<BlockInfo> & items,
                                 u32 currCell)
{
    ASSERT(currCell < kCellsPerBlock);

    u32 cellsRemaining = kCellsPerBlock - currCell;
    
    for (BlockInfo & item : items)
    {
        if (item.isAssigned)
            continue;

        if (item.cellCount > 1 && currCell != 0)
            continue;

        return &item;
    }
    return nullptr;
}

void block_pack_items(BlockInfos * pBlockInfos)
{
    std::sort(pBlockInfos->items.begin(),
              pBlockInfos->items.end(),
              [](const BlockInfo & a, const BlockInfo & b)
              { return a.cellCount < b.cellCount; });

    u32 unassignedItemCount = (u32)pBlockInfos->items.size();

    u32 currBlock = 0;
    u32 currCell = 0;

    while (unassignedItemCount > 0)
    {
        BlockInfo * pItem = find_next_fit(pBlockInfos->items, currCell);

        if (!pItem)
        {
            // no more items will fit in this block
            currBlock++;
            currCell = 0;
        }
        else
        {
            pItem->isAssigned = true;
            unassignedItemCount--;
            pItem->cellCount = data_type_cell_count(pItem->pAst->pSymRec->dataType);
            pItem->blockIndex = currBlock;
            pItem->cellIndex = currCell;

            currBlock += pItem->cellCount / kCellsPerBlock;
            currCell += pItem->cellCount % kCellsPerBlock;

            ASSERT(currCell <= kCellsPerBlock);
            if (currCell >= kCellsPerBlock)
            {
                currBlock++;
                currCell = 0;
            }
        }
    }

    pBlockInfos->blockCount = currCell == 0 ? currBlock : currBlock + 1;;
}

BlockInfos * block_pack_props_and_fields(Ast *pAst)
{
    ASSERT(pAst->type == kAST_ComponentDef ||
           pAst->type == kAST_EntityDef);

    u32 count = props_and_fields_count(pAst);

    BlockInfos * pBlockInfos = COMP_NEW(BlockInfos);
    pBlockInfos->items.reserve(count);

    for (Ast *pChild : pAst->pChildren->nodes)
    {
        if (is_prop_or_field(pChild->pSymRec))
        {
            pBlockInfos->items.emplace_back(pChild);
        }
    }

    block_pack_items(pBlockInfos);

    return pBlockInfos;
}



} // namespace gaen


