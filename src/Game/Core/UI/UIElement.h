//-----------------------------------------------------------------------------
// UIElement.h
// Provides necessary data for drawing and updating all UI elements.
// All UI elements (UIText, UIButton, UIPanel, etc.) should inherit from this class.
//-----------------------------------------------------------------------------
#pragma once

class UIElement 
{
public:

    UIElement();
    virtual ~UIElement() = default;
    virtual bool Initialize();

    void SetPosition(float x, float y) { m_xpos = x; m_ypos = y; };
    void SetSize(float width, float height) { m_width = width; m_height = height; };
    void SetVisibile(bool visible) { m_visible = visible; }

    float GetX() const { return m_xpos; }
    float GetY() const { return m_ypos; }
    float GetWidth() const { return m_width; }
    float GetHeight() const { return m_height; }

    // Virtual functions for subclass override
    virtual void Draw() {};
    virtual void Update(float deltaTime) {};

    virtual void OnHover() {};
    virtual void OnUnhover() {};
    virtual void OnClick() {};
    virtual void OnRelease() {};
    //TODO: OnFocus() and isEnabled() for keyboard inputs when using keys to focus on a button or radio

    bool isVisible() const { return m_visible; }

protected:
    
    float m_xpos;
    float m_ypos;

    float m_width;
    float m_height;

    bool m_visible;

};
