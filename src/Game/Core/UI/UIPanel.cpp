#include <iostream>

#include "UIPanel.h"
#include "../../../ContestAPI/app.h"

UIPanel::UIPanel()
{
}

void UIPanel::Initialize()
{
    for (auto& element : m_childElements)
    {
        element->Initialize();
    }

    return;
}

void UIPanel::AddChildElement(const std::shared_ptr<UIElement> &element)
{
    if (!element) return;

    m_childElements.push_back(element);
}

void UIPanel::RemoveChildElement(const std::shared_ptr<UIElement> &element)
{
    m_childElements.erase(std::remove(m_childElements.begin(), m_childElements.end(), element), m_childElements.end());
}

void UIPanel::Draw()
{
    if (!m_visible) return;

    App::DrawLine(m_xpos, m_ypos, m_xpos + m_width, m_ypos, 0.2f, 0.2f, 0.2f);
    App::DrawLine(m_xpos + m_width, m_ypos, m_xpos + m_width, m_ypos + m_height, 0.2f, 0.2f, 0.2f);
    App::DrawLine(m_xpos + m_width, m_ypos + m_height, m_xpos, m_ypos + m_height, 0.2f, 0.2f, 0.2f);
    App::DrawLine(m_xpos, m_ypos + m_height, m_xpos, m_ypos, 0.2f, 0.2f, 0.2f);

    for (auto& element : m_childElements)
    {
        element->Draw();
    }
}

void UIPanel::HandleMouseMove(float mouse_x, float mouse_y)
{
    if (!m_visible) return;

    for (auto& element : m_childElements)
    {
        element->HandleMouseMove(mouse_x, mouse_y);
    }
}

void UIPanel::HandleMouseClick(float mouse_x, float mouse_y)
{
    if (!m_visible) return;

    if (!IsMouseInside(mouse_x, mouse_y)) return;

    for (auto& element : m_childElements)
    {
        element->HandleMouseClick(mouse_x, mouse_y);
    }
}