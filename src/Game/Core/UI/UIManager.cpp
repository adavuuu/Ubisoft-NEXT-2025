#include <iostream>

#include "UIManager.h"
#include "../../../ContestAPI/app.h"

UIManager::UIManager()
{
}

void UIManager::Init()
{
    return; 
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

    if (m_activeScreen)
    {
        m_activeScreen->Draw();
    }
}

void UIManager::AddElement(const std::shared_ptr<UIElement>& element)
{
    if (!element)
        return;

    element->Init();
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

void UIManager::AddScreen(const std::string& name, std::shared_ptr<UIScreen> screen)
{
    m_screens[name] = screen;
}

void UIManager::SetActiveScreen(const std::string& name)
{
    auto it = m_screens.find(name);
    if (it != m_screens.end())
    {
        m_activeScreen = it->second;
        m_activeScreen->Init();
    }
}

void UIManager::ClearActiveScreen()
{
    m_activeScreen = nullptr;
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
