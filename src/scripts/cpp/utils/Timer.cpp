//------------------------------------------------------------------------------
// Timer.cpp - Auto-generated from Timer.cmp
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

// HASH: 67752663b8b4ecc9d4231b7037ad568d
#include "engine/Task.h"
#include "engine/Registry.h"
#include "engine/Component.h"
#include "engine/hashes.h"

namespace gaen
{

namespace comp
{

class Timer : public Component
{
public:
    static Component construct(ComponentDesc * pCompDesc)
    {
        Timer comp(pCompDesc);
        return comp;
    }
    
    void update(float) {} // LORRTEMP
    template <typename T>
    MessageResult message(const Message & msg, T msgAcc) { return MessageResult::Propogate; }

private:
    Timer(ComponentDesc * pCompDesc)
      : Component(pCompDesc)
    {
        pCompDesc->task = Task::createUpdatable(this, HASH::Timer);
    }
    Timer(const Timer&)      = delete;
    Timer(const Timer&&)     = delete;
    Timer & operator=(const Timer&)  = delete;
    Timer & operator=(const Timer&&) = delete;
};

namespace
{
bool isRegistered = ComponentRegistry::register_constructor(HASH::Timer, Timer::construct);
}

} // namespace comp
 
} // namespace gaen

