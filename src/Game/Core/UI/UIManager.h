//-----------------------------------------------------------------------------
// UIManager.h
// Manages all UI elements: initialization, updating, and drawing.
//-----------------------------------------------------------------------------
#pragma once

#include <vector>

#include "UIElement.h"

class UIManager
{
public:

    UIManager();
    ~UIManager() = default;

    bool Initialize();
    void Shutdown();

    void Update(float deltaTime);
    void Draw();

    void AddElement(const std::shared_ptr<UIElement>& element);
    void RemoveElement(const std::shared_ptr<UIElement>& element);

    void HandleMouseMove(float mouse_x, float mouse_y);
    void HandleMouseClick(float mouse_x, float mouse_y);

private:
    std::vector<std::shared_ptr<UIElement>> m_elements;
};
