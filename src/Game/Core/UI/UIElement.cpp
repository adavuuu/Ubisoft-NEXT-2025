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
