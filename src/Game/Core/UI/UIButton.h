//-----------------------------------------------------------------------------
// UIButton.h
// Represents an on-screen button element.
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <functional> 

#include "UIElement.h"

class UIButton : public UIElement 
{
public:
    UIButton(const std::string& text, float x, float y);
    ~UIButton() override = default;

    void SetText(const std::string& text) { m_text = text; };
    void SetTextColor(int r, int g, int b) { m_text_red = r; m_text_green = g; m_text_blue = b; };
    void SetBackgroundColor(int r, int g, int b) { m_bg_red = r; m_bg_green = g; m_bg_blue = b; };
    void SetHoverColor(int r, int g, int b) { m_hover_red = r; m_hover_green = g; m_hover_blue = b; };

    void SetOnClickCallback(std::function<void()> callback) { m_clickCallback = callback; }

    // Overrides from UIElement
    void Update(float deltaTime) override;
    void Draw() override;

    void OnHover() override;
    void OnUnhover() override;
    void OnClick() override;
    void OnRelease() override;
    //TODO: OnFocus() and isFocused() for keyboard inputs when using keys to focus on a button or radio

protected:
    std::string m_text;

    int m_text_red, m_text_green, m_text_blue; // text color
    int m_bg_red, m_bg_green, m_bg_blue; // background color
    int m_hover_red, m_hover_green, m_hover_blue; // hover color

    bool m_isHovered;
    bool m_isPressed;

    std::function<void()> m_clickCallback;
};
