//-----------------------------------------------------------------------------
// UIText.h
// Represents a simple on-screen text element.
//-----------------------------------------------------------------------------
#ifndef _UITEXT_H_
#define _UITEXT_H_

#include "UIElement.h"
#include <string>

//-----------------------------------------------------------------------------
// CUIText
//-----------------------------------------------------------------------------
class CUIText : public CUIElement
{
public:

    CUIText();
    CUIText(const std::string& text, float x, float y);
    virtual ~CUIText();

    virtual bool Initialize() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void SetText(const std::string& text) { m_text = text; };
    void SetColor(unsigned char r, unsigned char g, unsigned char b) { m_red = r; m_green = g; m_blue = b; };

protected:
    std::string m_text;
    unsigned char m_red, m_green, m_blue; // color
};

#endif