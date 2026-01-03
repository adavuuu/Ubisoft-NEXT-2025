//-----------------------------------------------------------------------------
// Entity.cpp
// Base actor class that in-game objects inherit from.
//-----------------------------------------------------------------------------

#include "Entity.h"

const std::pair<float, float>& Entity::GetPosition() const
{
    return m_position;
}

const std::pair<float, float>& Entity::GetVelocity() const
{
    return m_velocity;
}

float Entity::GetXPos() const
{
    return m_position.first;
}

float Entity::GetYPos() const
{
    return m_position.second;
}

float Entity::GetXVelocity() const
{
    return m_velocity.first;
}

float Entity::GetYVelocity() const
{
    return m_velocity.second;
}

void Entity::SetPosition(const float x, const float y)
{
    m_position.first = x;
    m_position.second = y;
}

void Entity::SetVelocity(const float vx, const float vy)
{
    m_velocity.first = vx;
    m_velocity.second = vy;
}

bool Entity::IsAlive() const
{
    return m_alive;
}

void Entity::Destroy()
{
    m_alive = false;
}

