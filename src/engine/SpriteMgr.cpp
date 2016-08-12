//------------------------------------------------------------------------------
// SpriteMgr.cpp - Management of Sprite lifetimes, animations and collisions
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

#include "engine/stdafx.h"

#include "assets/Gspr.h"

#include "engine/Handle.h"
#include "engine/Asset.h"
#include "engine/Entity.h"
#include "engine/glm_ext.h"

#include "engine/messages/SpriteInstance.h"
#include "engine/messages/SpritePlayAnim.h"
#include "engine/messages/SpriteVelocity.h"
#include "engine/messages/Transform.h"

#include "engine/SpriteMgr.h"

namespace gaen
{

SpriteMgr::~SpriteMgr()
{
    // LORRTODO: Cleanup is causing crash on exit... need to redesign how we release assets
    //for (auto & spritePair : mSpriteMap)
    //{
    //    SpriteInstance::send_sprite_destroy(kSpriteMgrTaskId, kRendererTaskId, spritePair.second->sprite().uid());
    //}
}

void SpriteMgr::update(f32 delta)
{
    for (auto & spritePair : mSpriteMap)
    {
        SpriteInstance * pSpriteInst = spritePair.second.get();
        if (pSpriteInst->mVelocity != glm::vec2{0.0})
        {
            glm::vec3 offset = glm::vec3(pSpriteInst->mVelocity * delta, 0.0f);
            pSpriteInst->mTransform = glm::to_mat4x3(glm::translate(glm::mat4(1.0f), offset) * glm::mat4(pSpriteInst->mTransform));
            SpriteInstance::send_sprite_transform(kSpriteMgrTaskId, kRendererTaskId, pSpriteInst->sprite().uid(), pSpriteInst->mTransform);
            {
                messages::TransformQW msgw(HASH::transform, kMessageFlag_None, kSpriteMgrTaskId, pSpriteInst->sprite().mOwner, false);
                msgw.setTransform(pSpriteInst->mTransform);
            }
        }
        if (pSpriteInst->mIsAnimating && pSpriteInst->advanceAnim(delta))
        {
            // update renderer with new frame
            SpriteInstance::send_sprite_anim(kSpriteMgrTaskId,
                                             kRendererTaskId,
                                             pSpriteInst->sprite().uid(),
                                             pSpriteInst->mAnimHash,
                                             pSpriteInst->mAnimFrameIdx);
        }
    }
}

template <typename T>
MessageResult SpriteMgr::message(const T & msgAcc)
{
    const Message & msg = msgAcc.message();

    switch (msg.msgId)
    {
    case HASH::sprite_insert:
    {
        messages::SpriteInstanceR<T> msgr(msgAcc);

        SpriteInstance * pSpriteInst = msgr.spriteInstance();
        ASSERT(pSpriteInst);
        ASSERT(mSpriteMap.find(pSpriteInst->sprite().uid()) == mSpriteMap.end());
        mSpriteMap.emplace(pSpriteInst->sprite().uid(), pSpriteInst);
        mSpriteOwners[pSpriteInst->sprite().owner()].push_back(pSpriteInst->sprite().uid());

        // Send a copy to the renderer
        Sprite * pSpriteRenderer = GNEW(kMEM_Renderer, Sprite, pSpriteInst->sprite());
        SpriteInstance * pSpriteInstRenderer = GNEW(kMEM_Renderer, SpriteInstance, pSpriteRenderer, pSpriteInst->mTransform);
        SpriteInstance::send_sprite_insert(kSpriteMgrTaskId, kRendererTaskId, pSpriteInstRenderer);

        return MessageResult::Consumed;
    }
    case HASH::sprite_play_anim:
    {
        messages::SpritePlayAnimR<T> msgr(msgAcc);

        auto spritePair = mSpriteMap.find(msgr.uid());
        if (spritePair != mSpriteMap.end())
        {
            spritePair->second->playAnim(msgr.animHash(), msgr.duration());
        }
        else
        {
            ERR("sprite_play_anim for unknown animation, uid: %u", msgr.uid());
        }
        return MessageResult::Consumed;
    }
    case HASH::sprite_set_velocity:
    {
        messages::SpriteVelocityR<T> msgr(msgAcc);
        auto spritePair = mSpriteMap.find(msgr.uid());
        if (spritePair != mSpriteMap.end())
        {
            spritePair->second->mVelocity = msgr.velocity();
        }
        else
        {
            ERR("sprite_set_velocity for unknown animation, uid: %u", msgr.uid());
        }
        return MessageResult::Consumed;
    }
	case HASH::remove_task:
	{
        task_id taskIdToRemove = msg.payload.u;
        auto itL = mSpriteOwners.find(taskIdToRemove);
        // It's ok if we don't find it, it just means this task had no sprites
        if (itL != mSpriteOwners.end())
        {
            for (u32 uid : itL->second)
            {
                // send sprite_destroy to renderer who in turn will send it back to us once
                SpriteInstance::send_sprite_destroy(kSpriteMgrTaskId, kRendererTaskId, uid);
            }
            mSpriteOwners.erase(itL);
        }
        return MessageResult::Consumed;
	}
    case HASH::sprite_destroy:
    {
        u32 uid = msg.payload.u;

        auto spritePair = mSpriteMap.find(uid);
        if (spritePair != mSpriteMap.end())
        {
            spritePair->second->desroySprite();
            mSpriteMap.erase(spritePair);
        }
        else
        {
            ERR("sprite_destroy for unknown animation, uid: %u", uid);
        }
        return MessageResult::Consumed;
    }
    default:
        PANIC("Unknown SpriteMgr message: %d", msg.msgId);
    }
    return MessageResult::Consumed;
}

// Template decls so we can define message func here in the .cpp
template MessageResult SpriteMgr::message<MessageQueueAccessor>(const MessageQueueAccessor & msgAcc);

namespace system_api
{

static void handle_sprite_remove(Handle & handle)
{
    SpriteInstance::send_sprite_destroy(handle.owner(), kSpriteMgrTaskId, handle.nameOrId());
    GDELETE(&handle);
}

HandleP sprite_create(AssetHandleP pAssetHandle, const glm::mat4x3 & transform, Entity & caller)
{
    ASSERT(pAssetHandle->typeHash() == HASH::asset);
    const Asset * pAsset = reinterpret_cast<const Asset*>(pAssetHandle->data());

    Sprite * pSprite = GNEW(kMEM_Engine, Sprite, caller.task().id(), pAsset);
    SpriteInstance * pSpriteInst = GNEW(kMEM_Engine, SpriteInstance, pSprite, transform);

    SpriteInstance::send_sprite_insert(caller.task().id(), kSpriteMgrTaskId, pSpriteInst);

    HandleP pHandle = GNEW(kMEM_Engine, Handle, HASH::sprite, pSprite->uid(), caller.task().id(), nullptr, handle_sprite_remove);
    return pHandle;
}

void sprite_play_anim(HandleP pSpriteHandle, u32 animHash, f32 duration, Entity & caller)
{
    messages::SpritePlayAnimQW msgw(HASH::sprite_play_anim, kMessageFlag_None, pSpriteHandle->owner(), kSpriteMgrTaskId, pSpriteHandle->nameOrId());
    msgw.setAnimHash(animHash);
    msgw.setDuration(duration);
}

void sprite_set_velocity(HandleP pSpriteHandle, const glm::vec2 & velocity, Entity & caller)
{
    messages::SpriteVelocityQW msgw(HASH::sprite_set_velocity, kMessageFlag_None, pSpriteHandle->owner(), kSpriteMgrTaskId, pSpriteHandle->nameOrId());
    msgw.setVelocity(velocity);
}


} // namespace system_api

} // namespace gaen
