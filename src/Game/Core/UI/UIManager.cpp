#include <iostream>

#include "UIManager.h"
#include "../../../ContestAPI/app.h"

UIManager::UIManager()
{
}

bool UIManager::Initialize()
{
    return true; 
}

void UIManager::Shutdown()
{
    m_elements.clear();
}

void UIManager::Update(float deltaTime)
{
    for (auto& element : m_elements)
    {
        if (element && element->isVisible())
        {
            element->Update(deltaTime);
        }
    }
}

void UIManager::Draw()
{
    for (auto& element : m_elements)
    {
        if (element && element->isVisible())
        {
            element->Draw();
        }
    }
}

void UIManager::AddElement(const std::shared_ptr<UIElement>& element)
{
    if (!element)
        return;

    element->Initialize();
    m_elements.push_back(element);
}

void UIManager::RemoveElement(const std::shared_ptr<UIElement>& element)
{
    auto it = std::find(m_elements.begin(), m_elements.end(), element);
    if (it != m_elements.end())
    {
        m_elements.erase(it); // shared_ptr handles deletion
    }
}

void UIManager::HandleMouseMove(float mouse_x, float mouse_y)
{
    for (auto& element : m_elements)
    {
        if (!element->isVisible()) 
        {
            continue;
        }

        element->HandleMouseMove(mouse_x, mouse_y);
    }
}

void UIManager::HandleMouseClick(float mouse_x, float mouse_y)
{
    for (auto& element : m_elements)
    {
        if (element->isVisible() && element->IsMouseInside(mouse_x, mouse_y))
        {
            element->HandleMouseClick(mouse_x, mouse_y);
        }
    }
}
