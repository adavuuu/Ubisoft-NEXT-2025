#include <iostream>
#include "UIElement.h"

UIElement::UIElement()
    : m_xpos(0.0f)
    , m_ypos(0.0f)
    , m_width(0.0f)
    , m_height(0.0f)
    , m_visible(true)
{
}

void UIElement::Initialize()
{
    return;
}

void UIElement::HandleMouseMove(float mouse_x, float mouse_y)
{
    bool inside = IsMouseInside(mouse_x, mouse_y);

     if (inside)
    {
        this->OnHover();
    }
    else
    {
        this->OnUnhover();
    }
}

void UIElement::HandleMouseClick(float mouse_x, float mouse_y)
{
    this->OnClick();
    this->OnRelease();
}

bool UIElement::IsMouseInside(float mouse_x, float mouse_y) const
{
    return mouse_x >= m_xpos &&
           mouse_x <= m_xpos + m_width &&
           mouse_y >= m_ypos &&
           mouse_y <= m_ypos + m_height;
}
