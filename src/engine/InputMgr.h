//------------------------------------------------------------------------------
// InputMgr.h - Maintains input state for TaskMasters
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

#ifndef GAEN_ENGINE_INPUT_MGR_H
#define GAEN_ENGINE_INPUT_MGR_H

#include <glm/vec4.hpp>

#include "core/HashMap.h"
#include "core/Vector.h"

#include "engine/MessageAccessor.h"
#include "engine/input.h"

namespace gaen
{

class InputMgr
{
public:
    InputMgr(bool isPrimary);

    template <typename T>
    MessageResult message(const T& msgAcc);

    u32 mode() { return mpActiveMode ? mpActiveMode->nameHash : 0; }
    void setMode(u32 modeHash);

    u32 queryState(u32 player, u32 stateHash, glm::vec4 * pMeasure);

private:
    struct CtrlState
    {
        // LORRTODO: Define controller
        u32 placeholder__;

        void zeroState()
        {
            placeholder__ = 0;
        }
    };

    struct MouseState
    {
        i32 xPos;
        i32 yPos;
        i32 wheel;

        void zeroState()
        {
            xPos = 0;
            yPos = 0;
            wheel = 0;
        }
    };

    struct InputMode
    {
        u32 nameHash;

        HashMap<kMEM_Engine, u32, glm::uvec4> keyboard;
        HashMap<kMEM_Engine, u32, glm::uvec4> mouseButtons;
        u32 mouseMove;

        HashMap<kMEM_Engine, u32, glm::uvec4> ctrlButtons;
        u32 ctrlLTrigger;
        u32 ctrlRTrigger;
        u32 ctrlLStick;
        u32 ctrlRStick;

        InputMode()
          : nameHash(0)
          , mouseMove(0)
          , ctrlLTrigger(0)
          , ctrlRTrigger(0)
          , ctrlLStick(0)
          , ctrlRStick(0)
        {}
    };

    bool queryKeyCode(KeyCode keyCode);
    u32 queryState(const glm::uvec4 & keys);

    void processKeyInput(const KeyInput & keyInput);
    void processMouseMoveInput(const MouseInput::Movement & moveInput);
    void processMouseWheelInput(i32 delta);

    void zeroState();

    bool mIsPrimary;

    glm::uvec4 mPressedKeys;

    MouseState mMouseState;

    static const u32 kMaxPlayers = 4;
    CtrlState mCtrlState[kMaxPlayers];

    InputMode * mpActiveMode;
    HashMap<kMEM_Engine, u32, InputMode> mModes;
};

} // namespace gaen

#endif // #ifndef GAEN_ENGINE_INPUT_MGR_H
