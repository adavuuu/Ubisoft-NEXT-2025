///////////////////////////////////////////////////////////////////////////////
// Filename: UIElement.cpp
// Provides necessary data for drawing and updating all UI elements.
// All UI elements (UIText, UIButton, UIPanel, etc.) should inherit from this class.
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
#include "UIElement.h"
//-----------------------------------------------------------------------------

CUIElement::CUIElement()
    : m_xpos(0.0f)
    , m_ypos(0.0f)
    , m_width(0.0f)
    , m_height(0.0f)
    , m_visible(true)
{
}


CUIElement::~CUIElement()
{
}

bool CUIElement::Initialize()
{
    return true;
}

void CUIElement::Draw()
{
    // Base class has no rendering — override in derived classes.
}

void CUIElement::Update(float deltaTime)
{
    // Base class has no updating — override in derived classes.
    (void)deltaTime;
}
