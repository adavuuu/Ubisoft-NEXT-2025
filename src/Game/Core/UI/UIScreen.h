//-----------------------------------------------------------------------------
// UIScreen.h
// Represents a collection of UIPanels to make up a screen.
// ex. Main Menu, Pause Menu, Options/Settings
//-----------------------------------------------------------------------------
#pragma once

#include <vector>

#include "UIElement.h"
#include "UIPanel.h"

class UIScreen
{
public:
    UIScreen() {};
    ~UIScreen() = default;

    void Init();
    void Update(float deltaTime) {};
    void Draw();

    void SetVisible(bool visible) { m_visible = visible; }

    void AddPanel(const std::shared_ptr<UIPanel>& panel);
    void RemovePanel(const std::shared_ptr<UIPanel>& panel);

    void HandleMouseMove(float mouse_x, float mouse_y);
    void HandleMouseClick(float mouse_x, float mouse_y);

    bool isVisible() const { return m_visible; }

protected:
    bool m_visible = true;

    std::vector<std::shared_ptr<UIPanel>> m_panels;
};
