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
    UIPanel() {};
    ~UIPanel() override = default;
    void Init() override;

    // Overrides from UIElement
    void Update(float deltaTime) override {};
    void Draw() override;

    void HandleMouseMove(float mouse_x, float mouse_y) override;
    void HandleMouseClick(float mouse_x, float mouse_y) override;
    //-----------------------------------------------------------------------------

    void AddElement(const std::shared_ptr<UIElement>& element);
    void RemoveElement(const std::shared_ptr<UIElement>& element);


protected:
    std::vector<std::shared_ptr<UIElement>> m_elements;
};
