//-----------------------------------------------------------------------------
// UIManager.h
// Manages all UI elements: initialization, updating, and drawing.
//-----------------------------------------------------------------------------
#pragma once

#include <vector>

#include "UIElement.h"
#include "UIScreen.h"

class UIManager
{
public:

    UIManager();
    ~UIManager() = default;

    void Init();
    void Shutdown();

    void Update(float deltaTime);
    void Draw();

    // UIScreens (Menus)
    void AddScreen(const std::string& name, std::shared_ptr<UIScreen> screen);
    void SetActiveScreen(const std::string& name);
    void ClearActiveScreen();

    // Input
    void HandleMouseMove(float mouse_x, float mouse_y);
    void HandleMouseClick(float mouse_x, float mouse_y);

private:
    std::unordered_map<std::string, std::shared_ptr<UIScreen>> m_screens;
    std::shared_ptr<UIScreen> m_activeScreen = nullptr;
};
