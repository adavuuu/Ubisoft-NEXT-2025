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

bool UIElement::Initialize()
{
    return true;
}

bool UIElement::IsMouseInside(float mouse_x, float mouse_y) const
{
    return mouse_x >= m_xpos &&
           mouse_x <= m_xpos + m_width &&
           mouse_y >= m_ypos &&
           mouse_y <= m_ypos + m_height;
}
