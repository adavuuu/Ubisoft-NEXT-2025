#include <iostream>

#include "UIText.h"
#include "../../../ContestAPI/app.h"

UIText::UIText(const std::string& text, float x, float y)
    : m_text(text)
    , m_red(255)
    , m_green(255)
    , m_blue(255)
{
    m_xpos = x;
    m_ypos = y;
}

void UIText::Update(float deltaTime)
{
    // TODO: Placeholder for text animations (fade, typewriter, etc.)
    (void)deltaTime;
}

void UIText::Draw()
{
    if (!m_visible)
        return;

    App::Print(m_xpos, m_ypos, m_text.c_str(), m_red, m_green, m_blue);
}

