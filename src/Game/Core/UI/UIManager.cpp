#include "UIManager.h"
#include "../../../ContestAPI/app.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
    Shutdown();
}

bool UIManager::Initialize()
{
    return true; 
}

void UIManager::Shutdown()
{
    m_elements.clear();
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

void UIManager::Update(float deltaTime)
{
    for (auto& element : m_elements)
    {
        if (element && element->isVisible())
            element->Update(deltaTime);
    }
}

void UIManager::Draw()
{
    for (auto& element : m_elements)
    {
        if (element && element->isVisible())
            element->Draw();
    }
}
