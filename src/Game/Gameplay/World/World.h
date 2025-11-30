//-----------------------------------------------------------------------------
// World.h
// Represents the world and everything in it
//-----------------------------------------------------------------------------
#pragma once

#include "../../../ContestAPI/app.h"
#include <GLUT/glut.h>

class Player;
class UIManager;

class World
{
public:
    void Init();
    void Update(const float deltaTime);
    void Render();
    void Shutdown();

private:
    Player* player = nullptr;
    UIManager* ui_manager = nullptr;
};