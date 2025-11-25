//-----------------------------------------------------------------------------
// UIElement.h
// Provides necessary data for drawing and updating all UI elements.
// All UI elements (UIText, UIButton, UIPanel, etc.) should inherit from this class.
//-----------------------------------------------------------------------------
#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

//-----------------------------------------------------------------------------
// CUIElement
//-----------------------------------------------------------------------------

class CUIElement 
{
public:

    CUIElement();
    virtual ~CUIElement();

    virtual bool Initialize();
    virtual void Draw();
    virtual void Update(float deltaTime);

    void SetPosition(float x, float y) { m_xpos = x; m_ypos = y; };
    void SetSize(float width, float height) { m_width = width; m_height = height; };

    float GetX() const { return m_xpos; }
    float GetY() const { return m_ypos; }
    float GetWidth() const { return m_width; }
    float GetHeight() const { return m_height; }

    void SetVisibile(bool visible) { m_visible = visible; }
    bool isVisible() const { return m_visible; }

protected:
    
    float m_xpos;
    float m_ypos;

    float m_width;
    float m_height;

    bool m_visible;

};

#endif