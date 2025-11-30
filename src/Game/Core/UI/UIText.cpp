#include "UIText.h"
#include "../../../ContestAPI/app.h"

UIText::UIText(const std::string& text)
    : m_text(text)
    , m_red(255)
    , m_green(255)
    , m_blue(255)
{
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

