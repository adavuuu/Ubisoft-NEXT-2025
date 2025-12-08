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
    m_screens.clear();
}

void UIManager::Update(float deltaTime)
{
    
}

void UIManager::Draw()
{
    if (m_activeScreen)
    {
        m_activeScreen->Draw();
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
    for (auto& screen : m_screens)
    {
        if (screen.second->isVisible()) 
        {
            screen.second->HandleMouseMove(mouse_x, mouse_y);
        } 
    }
}

void UIManager::HandleMouseClick(float mouse_x, float mouse_y)
{
    for (auto& screen : m_screens) 
    {
        if (screen.second->isVisible()) 
        {
            screen.second->HandleMouseClick(mouse_x, mouse_y);
        }
    }
}
