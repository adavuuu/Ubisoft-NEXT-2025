//-----------------------------------------------------------------------------
// World.h
// Represents the world and everything in it
//-----------------------------------------------------------------------------
#pragma once

class Player;
class UIManager;
class InputManager;

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
    InputManager* input_manager = nullptr;
};