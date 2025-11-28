//-----------------------------------------------------------------------------
// World.h
// Represents the world and everything in it
//-----------------------------------------------------------------------------
#pragma once

#include "../../../ContestAPI/app.h"

class Player;

class World
{
public:
    void Init();
    void Update(const float deltaTime);
    void Render();
    void Shutdown();

private:
    Player* player = nullptr;
};