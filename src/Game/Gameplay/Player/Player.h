//-----------------------------------------------------------------------------
// Player.h
// Represents a player in the game
//-----------------------------------------------------------------------------
#pragma once

#include "../../../ContestAPI/app.h"

class Player
{

public:
    void Init();
    void Update(const float deltaTime);
    void Render();
    void Shutdown();

private:
    CSimpleSprite *testSprite = nullptr;
    enum
    {
	    ANIM_FORWARDS,
	    ANIM_BACKWARDS,
	    ANIM_LEFT,
	    ANIM_RIGHT,
    };
};