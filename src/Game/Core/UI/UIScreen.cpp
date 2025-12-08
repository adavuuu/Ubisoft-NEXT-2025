#include <iostream>

#include "UIScreen.h"
#include "../../../ContestAPI/app.h"

void UIScreen::Init()
{
    for (auto& panel : m_panels)
    {
        panel->Init();
    }

    return;
}

void UIScreen::Draw()
{
    if (!m_visible) return;

    for (auto& panel : m_panels)
    {
        panel->Draw();
    }
}

void UIScreen::AddPanel(const std::shared_ptr<UIPanel> &panel)
{
    if (!panel) return;

    m_panels.push_back(panel);
}

void UIScreen::RemovePanel(const std::shared_ptr<UIPanel> &panel)
{
    m_panels.erase(std::remove(m_panels.begin(), m_panels.end(), panel), m_panels.end());
}

void UIScreen::HandleMouseMove(float mouse_x, float mouse_y)
{
    if (!m_visible) return;

    for (auto& panel : m_panels)
    {
        panel->HandleMouseMove(mouse_x, mouse_y);
    }
}

void UIScreen::HandleMouseClick(float mouse_x, float mouse_y)
{
    if (!m_visible) return;

    for (auto& panel : m_panels)
    {
        panel->HandleMouseClick(mouse_x, mouse_y);
    }
}
