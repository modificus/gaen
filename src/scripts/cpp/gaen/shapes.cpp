//------------------------------------------------------------------------------
// shapes.cpp - Auto-generated from shapes.cmp
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

// HASH: 5c88c24e8da7a2b5acd9f5ce81b16c25
#include "engine/hashes.h"
#include "engine/Block.h"
#include "engine/BlockMemory.h"
#include "engine/MessageWriter.h"
#include "engine/Task.h"
#include "engine/Handle.h"
#include "engine/Registry.h"
#include "engine/Component.h"
#include "engine/Entity.h"

// system_api declarations
#include "engine/shapes.h"
#include "engine/system_api.h"

namespace gaen
{

namespace comp
{

class gaen__shapes__Box : public Component
{
public:
    static Component * construct(void * place, Entity * pEntity)
    {
        return new (place) gaen__shapes__Box(pEntity);
    }

    template <typename T>
    MessageResult message(const T & msgAcc)
    {
        const Message & _msg = msgAcc.message();
        switch(_msg.msgId)
        {
        case HASH::init_data__:
            ASSERT(initStatus() < kIS_InitData);

            size() = glm::vec3(1.00000000e+00f, 1.00000000e+00f, 1.00000000e+00f);
            diffuse() = Color(255, 0, 0, 255);
            model() = nullptr;
            modelUid() = system_api::renderer_gen_uid(entity());

            setInitStatus(kIS_InitData);
            return MessageResult::Consumed;
        case HASH::init_assets__:
            ASSERT(initStatus() < kIS_InitAssets);


            setInitStatus(kIS_InitAssets);
            return MessageResult::Consumed;
        case HASH::set_property:
            switch (_msg.payload.u)
            {
            case HASH::diffuse:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&diffuse())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::size:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&size())[0].cells[0] = msgAcc[0].cells[0];
                    reinterpret_cast<Block*>(&size())[0].cells[1] = msgAcc[0].cells[1];
                    reinterpret_cast<Block*>(&size())[0].cells[2] = msgAcc[0].cells[2];
                    return MessageResult::Consumed;
                }
                break;
            }
            }
            return MessageResult::Propogate; // Invalid property
        case HASH::init:
        {
            // Params look compatible, message body follows
            model() = system_api::create_shape_box(size(), diffuse(), entity());
            system_api::renderer_insert_model_instance(modelUid(), model(), entity());
            return MessageResult::Consumed;
        }
        case HASH::update_transform:
        {
            // Params look compatible, message body follows
            system_api::renderer_transform_model_instance(modelUid(), transform(), entity());
            return MessageResult::Consumed;
        }
        }
        return MessageResult::Propogate;
}

private:
    gaen__shapes__Box(Entity * pEntity)
      : Component(pEntity)
    {
        mScriptTask = Task::create(this, HASH::gaen__shapes__Box);
        mBlockCount = 2;
    }
    gaen__shapes__Box(const gaen__shapes__Box&)              = delete;
    gaen__shapes__Box(gaen__shapes__Box&&)                   = delete;
    gaen__shapes__Box & operator=(const gaen__shapes__Box&)  = delete;
    gaen__shapes__Box & operator=(gaen__shapes__Box&&)       = delete;

    glm::vec3& size()
    {
        return *reinterpret_cast<glm::vec3*>(&mpBlocks[0].qCell);
    }

    Color& diffuse()
    {
        return mpBlocks[0].cells[3].color;
    }

    HandleP& model()
    {
        return *reinterpret_cast<HandleP*>(&mpBlocks[1].cells[0]);
    }

    u32& modelUid()
    {
        return mpBlocks[1].cells[2].u;
    }


}; // class gaen__shapes__Box

} // namespace comp

void register_component__gaen__shapes__Box(Registry & registry)
{
    if (!registry.registerComponentConstructor(HASH::gaen__shapes__Box, comp::gaen__shapes__Box::construct))
        PANIC("Unable to register component: gaen__shapes__Box");
}

namespace comp
{

class gaen__shapes__Cone : public Component
{
public:
    static Component * construct(void * place, Entity * pEntity)
    {
        return new (place) gaen__shapes__Cone(pEntity);
    }

    template <typename T>
    MessageResult message(const T & msgAcc)
    {
        const Message & _msg = msgAcc.message();
        switch(_msg.msgId)
        {
        case HASH::init_data__:
            ASSERT(initStatus() < kIS_InitData);

            size() = glm::vec3(1.00000000e+00f, 1.00000000e+00f, 1.00000000e+00f);
            slices() = 16;
            diffuse() = Color(255, 0, 0, 255);
            model() = nullptr;
            modelUid() = system_api::renderer_gen_uid(entity());

            setInitStatus(kIS_InitData);
            return MessageResult::Consumed;
        case HASH::init_assets__:
            ASSERT(initStatus() < kIS_InitAssets);


            setInitStatus(kIS_InitAssets);
            return MessageResult::Consumed;
        case HASH::set_property:
            switch (_msg.payload.u)
            {
            case HASH::diffuse:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&diffuse())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::size:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&size())[0].cells[0] = msgAcc[0].cells[0];
                    reinterpret_cast<Block*>(&size())[0].cells[1] = msgAcc[0].cells[1];
                    reinterpret_cast<Block*>(&size())[0].cells[2] = msgAcc[0].cells[2];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::slices:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&slices())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            }
            return MessageResult::Propogate; // Invalid property
        case HASH::init:
        {
            // Params look compatible, message body follows
            model() = system_api::create_shape_cone(size(), slices(), diffuse(), entity());
            system_api::renderer_insert_model_instance(modelUid(), model(), entity());
            return MessageResult::Consumed;
        }
        case HASH::update_transform:
        {
            // Params look compatible, message body follows
            system_api::renderer_transform_model_instance(modelUid(), transform(), entity());
            return MessageResult::Consumed;
        }
        }
        return MessageResult::Propogate;
}

private:
    gaen__shapes__Cone(Entity * pEntity)
      : Component(pEntity)
    {
        mScriptTask = Task::create(this, HASH::gaen__shapes__Cone);
        mBlockCount = 2;
    }
    gaen__shapes__Cone(const gaen__shapes__Cone&)              = delete;
    gaen__shapes__Cone(gaen__shapes__Cone&&)                   = delete;
    gaen__shapes__Cone & operator=(const gaen__shapes__Cone&)  = delete;
    gaen__shapes__Cone & operator=(gaen__shapes__Cone&&)       = delete;

    glm::vec3& size()
    {
        return *reinterpret_cast<glm::vec3*>(&mpBlocks[0].qCell);
    }

    u32& slices()
    {
        return mpBlocks[0].cells[3].u;
    }

    Color& diffuse()
    {
        return mpBlocks[1].cells[2].color;
    }

    HandleP& model()
    {
        return *reinterpret_cast<HandleP*>(&mpBlocks[1].cells[0]);
    }

    u32& modelUid()
    {
        return mpBlocks[1].cells[3].u;
    }


}; // class gaen__shapes__Cone

} // namespace comp

void register_component__gaen__shapes__Cone(Registry & registry)
{
    if (!registry.registerComponentConstructor(HASH::gaen__shapes__Cone, comp::gaen__shapes__Cone::construct))
        PANIC("Unable to register component: gaen__shapes__Cone");
}

namespace comp
{

class gaen__shapes__Cylinder : public Component
{
public:
    static Component * construct(void * place, Entity * pEntity)
    {
        return new (place) gaen__shapes__Cylinder(pEntity);
    }

    template <typename T>
    MessageResult message(const T & msgAcc)
    {
        const Message & _msg = msgAcc.message();
        switch(_msg.msgId)
        {
        case HASH::init_data__:
            ASSERT(initStatus() < kIS_InitData);

            size() = glm::vec3(1.00000000e+00f, 1.00000000e+00f, 1.00000000e+00f);
            slices() = 16;
            diffuse() = Color(255, 0, 0, 255);
            model() = nullptr;
            modelUid() = system_api::renderer_gen_uid(entity());

            setInitStatus(kIS_InitData);
            return MessageResult::Consumed;
        case HASH::init_assets__:
            ASSERT(initStatus() < kIS_InitAssets);


            setInitStatus(kIS_InitAssets);
            return MessageResult::Consumed;
        case HASH::set_property:
            switch (_msg.payload.u)
            {
            case HASH::diffuse:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&diffuse())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::size:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&size())[0].cells[0] = msgAcc[0].cells[0];
                    reinterpret_cast<Block*>(&size())[0].cells[1] = msgAcc[0].cells[1];
                    reinterpret_cast<Block*>(&size())[0].cells[2] = msgAcc[0].cells[2];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::slices:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&slices())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            }
            return MessageResult::Propogate; // Invalid property
        case HASH::init:
        {
            // Params look compatible, message body follows
            model() = system_api::create_shape_cylinder(size(), slices(), diffuse(), entity());
            system_api::renderer_insert_model_instance(modelUid(), model(), entity());
            return MessageResult::Consumed;
        }
        case HASH::update_transform:
        {
            // Params look compatible, message body follows
            system_api::renderer_transform_model_instance(modelUid(), transform(), entity());
            return MessageResult::Consumed;
        }
        }
        return MessageResult::Propogate;
}

private:
    gaen__shapes__Cylinder(Entity * pEntity)
      : Component(pEntity)
    {
        mScriptTask = Task::create(this, HASH::gaen__shapes__Cylinder);
        mBlockCount = 2;
    }
    gaen__shapes__Cylinder(const gaen__shapes__Cylinder&)              = delete;
    gaen__shapes__Cylinder(gaen__shapes__Cylinder&&)                   = delete;
    gaen__shapes__Cylinder & operator=(const gaen__shapes__Cylinder&)  = delete;
    gaen__shapes__Cylinder & operator=(gaen__shapes__Cylinder&&)       = delete;

    glm::vec3& size()
    {
        return *reinterpret_cast<glm::vec3*>(&mpBlocks[0].qCell);
    }

    u32& slices()
    {
        return mpBlocks[0].cells[3].u;
    }

    Color& diffuse()
    {
        return mpBlocks[1].cells[2].color;
    }

    HandleP& model()
    {
        return *reinterpret_cast<HandleP*>(&mpBlocks[1].cells[0]);
    }

    u32& modelUid()
    {
        return mpBlocks[1].cells[3].u;
    }


}; // class gaen__shapes__Cylinder

} // namespace comp

void register_component__gaen__shapes__Cylinder(Registry & registry)
{
    if (!registry.registerComponentConstructor(HASH::gaen__shapes__Cylinder, comp::gaen__shapes__Cylinder::construct))
        PANIC("Unable to register component: gaen__shapes__Cylinder");
}

namespace comp
{

class gaen__shapes__Sphere : public Component
{
public:
    static Component * construct(void * place, Entity * pEntity)
    {
        return new (place) gaen__shapes__Sphere(pEntity);
    }

    template <typename T>
    MessageResult message(const T & msgAcc)
    {
        const Message & _msg = msgAcc.message();
        switch(_msg.msgId)
        {
        case HASH::init_data__:
            ASSERT(initStatus() < kIS_InitData);

            size() = glm::vec3(1.00000000e+00f, 1.00000000e+00f, 1.00000000e+00f);
            sections() = 16;
            slices() = 16;
            diffuse() = Color(255, 0, 0, 255);
            model() = nullptr;
            modelUid() = system_api::renderer_gen_uid(entity());

            setInitStatus(kIS_InitData);
            return MessageResult::Consumed;
        case HASH::init_assets__:
            ASSERT(initStatus() < kIS_InitAssets);


            setInitStatus(kIS_InitAssets);
            return MessageResult::Consumed;
        case HASH::set_property:
            switch (_msg.payload.u)
            {
            case HASH::diffuse:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&diffuse())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::sections:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&sections())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::size:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&size())[0].cells[0] = msgAcc[0].cells[0];
                    reinterpret_cast<Block*>(&size())[0].cells[1] = msgAcc[0].cells[1];
                    reinterpret_cast<Block*>(&size())[0].cells[2] = msgAcc[0].cells[2];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::slices:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&slices())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            }
            return MessageResult::Propogate; // Invalid property
        case HASH::init:
        {
            // Params look compatible, message body follows
            model() = system_api::create_shape_sphere(size(), slices(), sections(), diffuse(), entity());
            system_api::renderer_insert_model_instance(modelUid(), model(), entity());
            return MessageResult::Consumed;
        }
        case HASH::update_transform:
        {
            // Params look compatible, message body follows
            system_api::renderer_transform_model_instance(modelUid(), transform(), entity());
            return MessageResult::Consumed;
        }
        }
        return MessageResult::Propogate;
}

private:
    gaen__shapes__Sphere(Entity * pEntity)
      : Component(pEntity)
    {
        mScriptTask = Task::create(this, HASH::gaen__shapes__Sphere);
        mBlockCount = 3;
    }
    gaen__shapes__Sphere(const gaen__shapes__Sphere&)              = delete;
    gaen__shapes__Sphere(gaen__shapes__Sphere&&)                   = delete;
    gaen__shapes__Sphere & operator=(const gaen__shapes__Sphere&)  = delete;
    gaen__shapes__Sphere & operator=(gaen__shapes__Sphere&&)       = delete;

    glm::vec3& size()
    {
        return *reinterpret_cast<glm::vec3*>(&mpBlocks[0].qCell);
    }

    u32& sections()
    {
        return mpBlocks[0].cells[3].u;
    }

    u32& slices()
    {
        return mpBlocks[1].cells[2].u;
    }

    Color& diffuse()
    {
        return mpBlocks[1].cells[3].color;
    }

    HandleP& model()
    {
        return *reinterpret_cast<HandleP*>(&mpBlocks[1].cells[0]);
    }

    u32& modelUid()
    {
        return mpBlocks[2].cells[0].u;
    }


}; // class gaen__shapes__Sphere

} // namespace comp

void register_component__gaen__shapes__Sphere(Registry & registry)
{
    if (!registry.registerComponentConstructor(HASH::gaen__shapes__Sphere, comp::gaen__shapes__Sphere::construct))
        PANIC("Unable to register component: gaen__shapes__Sphere");
}

namespace comp
{

class gaen__shapes__QuadSphere : public Component
{
public:
    static Component * construct(void * place, Entity * pEntity)
    {
        return new (place) gaen__shapes__QuadSphere(pEntity);
    }

    template <typename T>
    MessageResult message(const T & msgAcc)
    {
        const Message & _msg = msgAcc.message();
        switch(_msg.msgId)
        {
        case HASH::init_data__:
            ASSERT(initStatus() < kIS_InitData);

            size() = glm::vec3(1.00000000e+00f, 1.00000000e+00f, 1.00000000e+00f);
            sections() = 16;
            diffuse() = Color(255, 0, 0, 255);
            model() = nullptr;
            modelUid() = system_api::renderer_gen_uid(entity());

            setInitStatus(kIS_InitData);
            return MessageResult::Consumed;
        case HASH::init_assets__:
            ASSERT(initStatus() < kIS_InitAssets);


            setInitStatus(kIS_InitAssets);
            return MessageResult::Consumed;
        case HASH::set_property:
            switch (_msg.payload.u)
            {
            case HASH::diffuse:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&diffuse())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::sections:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&sections())[0].cells[0] = msgAcc[0].cells[0];
                    return MessageResult::Consumed;
                }
                break;
            }
            case HASH::size:
            {
                u32 requiredBlockCount = 1;
                if (_msg.blockCount >= requiredBlockCount)
                {
                    reinterpret_cast<Block*>(&size())[0].cells[0] = msgAcc[0].cells[0];
                    reinterpret_cast<Block*>(&size())[0].cells[1] = msgAcc[0].cells[1];
                    reinterpret_cast<Block*>(&size())[0].cells[2] = msgAcc[0].cells[2];
                    return MessageResult::Consumed;
                }
                break;
            }
            }
            return MessageResult::Propogate; // Invalid property
        case HASH::init:
        {
            // Params look compatible, message body follows
            model() = system_api::create_shape_quad_sphere(size(), sections(), diffuse(), entity());
            system_api::renderer_insert_model_instance(modelUid(), model(), entity());
            return MessageResult::Consumed;
        }
        case HASH::update_transform:
        {
            // Params look compatible, message body follows
            system_api::renderer_transform_model_instance(modelUid(), transform(), entity());
            return MessageResult::Consumed;
        }
        }
        return MessageResult::Propogate;
}

private:
    gaen__shapes__QuadSphere(Entity * pEntity)
      : Component(pEntity)
    {
        mScriptTask = Task::create(this, HASH::gaen__shapes__QuadSphere);
        mBlockCount = 2;
    }
    gaen__shapes__QuadSphere(const gaen__shapes__QuadSphere&)              = delete;
    gaen__shapes__QuadSphere(gaen__shapes__QuadSphere&&)                   = delete;
    gaen__shapes__QuadSphere & operator=(const gaen__shapes__QuadSphere&)  = delete;
    gaen__shapes__QuadSphere & operator=(gaen__shapes__QuadSphere&&)       = delete;

    glm::vec3& size()
    {
        return *reinterpret_cast<glm::vec3*>(&mpBlocks[0].qCell);
    }

    u32& sections()
    {
        return mpBlocks[0].cells[3].u;
    }

    Color& diffuse()
    {
        return mpBlocks[1].cells[2].color;
    }

    HandleP& model()
    {
        return *reinterpret_cast<HandleP*>(&mpBlocks[1].cells[0]);
    }

    u32& modelUid()
    {
        return mpBlocks[1].cells[3].u;
    }


}; // class gaen__shapes__QuadSphere

} // namespace comp

void register_component__gaen__shapes__QuadSphere(Registry & registry)
{
    if (!registry.registerComponentConstructor(HASH::gaen__shapes__QuadSphere, comp::gaen__shapes__QuadSphere::construct))
        PANIC("Unable to register component: gaen__shapes__QuadSphere");
}

} // namespace gaen

