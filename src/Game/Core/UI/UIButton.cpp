#include <iostream>

#include "UIButton.h"
#include "../../../ContestAPI/app.h"

UIButton::UIButton(const std::string& text)
    : m_text(text)
    , m_text_red(255), m_text_green(255), m_text_blue(255)
    , m_bg_red(50),  m_bg_green(50),  m_bg_blue(50)
    , m_hover_red(70), m_hover_green(70), m_hover_blue(70)
    , m_isHovered(false)
    , m_isPressed(false)
{
}

void UIButton::Update(float deltaTime)
{
    // TODO: Placeholder for text animations (fade, typewriter, etc.)
    (void)deltaTime;
}

void UIButton::Draw()
{
    if (!m_visible)
        return;

    App::Print(m_xpos, m_ypos, m_text.c_str(), m_text_red, m_text_green, m_text_blue);

}

void UIButton::OnHover()
{
    m_isHovered = true;
}

void UIButton::OnUnhover()
{
    m_isHovered = false;
}

void UIButton::OnClick()
{
    m_isPressed = true;
}

void UIButton::OnRelease()
{
    // Fire callback only if release happens on the button
    if (m_isPressed && m_isHovered && m_clickCallback)
    {
        m_clickCallback();
    }

    m_isPressed = false;
}
