//-----------------------------------------------------------------------------
// UIText.h
// Represents a simple on-screen text element.
//-----------------------------------------------------------------------------
#pragma once

#include <string>

#include "UIElement.h"

class UIText : public UIElement
{
public:

    UIText(const std::string& text);
    ~UIText() override = default;

    void SetText(const std::string& text) { m_text = text; };
    void SetColor(unsigned char r, unsigned char g, unsigned char b) { m_red = r; m_green = g; m_blue = b; };

     // Overrides from UIElement
    void Update(float deltaTime) override;
    void Draw() override;

protected:
    std::string m_text;

    unsigned char m_red, m_green, m_blue; // color
};
