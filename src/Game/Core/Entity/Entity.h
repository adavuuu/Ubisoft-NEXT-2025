//-----------------------------------------------------------------------------
// Entity.h
// Base actor class that in-game objects inherit from.
//-----------------------------------------------------------------------------

#pragma once
#include <utility>

class InputManager;

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void Init() {}
    virtual void Update(float deltaTime, InputManager& inputManager) {}
    virtual void Render() {}
    virtual void Shutdown() {}

    const std::pair<float, float>& GetPosition() const;
    float GetXPos() const;
    float GetYPos() const;
    const std::pair<float, float>& GetVelocity() const;
    float GetXVelocity() const;
    float GetYVelocity() const;

    void SetPosition(float x, float y);
    void SetVelocity(float vx, float vy);

    bool IsAlive() const;
    void Destroy();

protected:
    bool m_alive = true;

    // 2D Position/Velocity represented as (X, Y) pair
    std::pair<float, float> m_position = {0.0f, 0.0f};
    std::pair<float, float> m_velocity = {0.0f, 0.0f};
};
