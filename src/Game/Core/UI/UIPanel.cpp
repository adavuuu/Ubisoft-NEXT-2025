#include <iostream>

#include "UIPanel.h"
#include "../../../ContestAPI/app.h"

void UIPanel::Init()
{
    for (auto& element : m_elements)
    {
        element->Init();
    }

    return;
}

void UIPanel::Draw()
{
    if (!m_visible) return;

    App::DrawLine(m_xpos, m_ypos, m_xpos + m_width, m_ypos, 0.2f, 0.2f, 0.2f);
    App::DrawLine(m_xpos + m_width, m_ypos, m_xpos + m_width, m_ypos + m_height, 0.2f, 0.2f, 0.2f);
    App::DrawLine(m_xpos + m_width, m_ypos + m_height, m_xpos, m_ypos + m_height, 0.2f, 0.2f, 0.2f);
    App::DrawLine(m_xpos, m_ypos + m_height, m_xpos, m_ypos, 0.2f, 0.2f, 0.2f);

    for (auto& element : m_elements)
    {
        element->Draw();
    }
}

void UIPanel::HandleMouseMove(float mouse_x, float mouse_y)
{
    if (!m_visible) return;

    for (auto& element : m_elements)
    {
        element->HandleMouseMove(mouse_x, mouse_y);
    }
}

void UIPanel::HandleMouseClick(float mouse_x, float mouse_y)
{
    if (!m_visible) return;

    if (!IsMouseInside(mouse_x, mouse_y)) return;

    for (auto& element : m_elements)
    {
        element->HandleMouseClick(mouse_x, mouse_y);
    }
}

void UIPanel::AddElement(const std::shared_ptr<UIElement> &element)
{
    if (!element) return;

    m_elements.push_back(element);
}

void UIPanel::RemoveElement(const std::shared_ptr<UIElement> &element)
{
    m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), element), m_elements.end());
}
