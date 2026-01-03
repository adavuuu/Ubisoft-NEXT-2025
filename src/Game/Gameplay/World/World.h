//-----------------------------------------------------------------------------
// World.h
// Represents the world and everything in it
//-----------------------------------------------------------------------------
#pragma once

#include "Core/Entity/Entity.h"

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

    // Template function to spawn any object of type Y, with whatever set of args
    // needed with its constructor
    template <typename T, typename... Args>
    T* spawnEntity(Args&&... args) {
        // Construct entity using args that are passed in
        auto entity = std::make_unique<T>(std::forward<Args>(args)...);

        // Run the entity's init function
        entity->Init();

        // Store the entity and return a raw pointer to it
        T* rawPtr = entity.get();
        m_entities.push_back(std::move(entity));
        return rawPtr;
    }

private:
    Player* player = nullptr;
    UIManager* ui_manager = nullptr;
    InputManager* input_manager = nullptr;

    std::vector<std::unique_ptr<Entity>> m_entities;
};