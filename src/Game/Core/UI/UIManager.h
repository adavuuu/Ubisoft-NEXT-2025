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

    void AddElement(const std::shared_ptr<UIElement>& element);
    void RemoveElement(const std::shared_ptr<UIElement>& element);

    void Update(float deltaTime);
    void Draw();

private:
    std::vector<std::shared_ptr<UIElement>> m_elements;
};
