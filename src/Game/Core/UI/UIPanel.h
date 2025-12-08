//-----------------------------------------------------------------------------
// UIPanel.h
// Represents a collection of UIElements in an on-screen frame.
//-----------------------------------------------------------------------------
#pragma once

#include <vector>

#include "UIElement.h"

class UIPanel : public UIElement
{
public:
    UIPanel();
    ~UIPanel() override = default;
    void Initialize() override;

    void AddChildElement(const std::shared_ptr<UIElement>& element);
    void RemoveChildElement(const std::shared_ptr<UIElement>& element);

    // Overrides from UIElement
    void Draw() override;

    void HandleMouseMove(float mouse_x, float mouse_y) override;
    void HandleMouseClick(float mouse_x, float mouse_y) override;


protected:
    std::vector<std::shared_ptr<UIElement>> m_childElements;
};
