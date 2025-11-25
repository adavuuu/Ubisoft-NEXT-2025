///////////////////////////////////////////////////////////////////////////////
// Filename: UIText.cpp
// Represents a simple on-screen text element.
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
#include "UIText.h"
#include <iostream>
#include "../../../ContestAPI/app.h"
//-----------------------------------------------------------------------------

CUIText::CUIText()
    : m_text("")
    , m_red(255)
    , m_green(255)
    , m_blue(255)
{
}

CUIText::CUIText(const std::string& text, float x, float y)
    : m_text(text)
    , m_red(255)
    , m_green(255)
    , m_blue(255)
{
    m_xpos = x;
    m_ypos = y;
}

CUIText::~CUIText()
{
}

bool CUIText::Initialize()
{
    // TODO: load fonts here
    return true;
}

void CUIText::Update(float deltaTime)
{
    (void)deltaTime;
    // Placeholder for text animations (fade, typewriter, etc.)
}

void CUIText::Draw()
{
    if (!m_visible)
        return;

    App::Print(m_xpos, m_ypos, m_text.c_str(), m_red, m_green, m_blue);
}

