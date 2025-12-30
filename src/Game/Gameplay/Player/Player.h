//-----------------------------------------------------------------------------
// Player.h
// Represents a player in the game
//-----------------------------------------------------------------------------
#pragma once

#include "../Game/Core/Entity/Entity.h"

class InputManager;
class CSimpleSprite;

class Player : public Entity
{
public:
	~Player() override = default;

    void Init() override;
    void Update(float deltaTime, InputManager& inputManager) override;
    void Render() override;
    void Shutdown() override;

private:
    CSimpleSprite* m_sprite = nullptr;
};