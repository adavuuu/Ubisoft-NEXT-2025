///////////////////////////////////////////////////////////////////////////////
// Filename: UIManager.cpp
// Manages all UI elements: initialization, updating, and drawing.
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
#include "UIManager.h"
#include "../../../ContestAPI/app.h"
//-----------------------------------------------------------------------------

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
    Shutdown();
}

bool CUIManager::Initialize()
{
    return true; 
}

void CUIManager::Shutdown()
{
    for (auto* element : m_elements)
    {
        if (element)
        {
            delete element;
        }
    }

    m_elements.clear();
}

void CUIManager::AddElement(CUIElement* element)
{
    if (!element)
        return;

    element->Initialize();
    m_elements.push_back(element);
}

void CUIManager::RemoveElement(CUIElement *element)
{
    for (auto it = m_elements.begin(); it != m_elements.end(); ++it)
    {
        if (*it == element)
        {
            delete *it;
            m_elements.erase(it);
            break;
        }
    }
}

void CUIManager::Update(float deltaTime)
{
    for (auto* element : m_elements)
    {
        if (element->isVisible())
            element->Update(deltaTime);
    }
}

void CUIManager::Draw()
{
    for (auto* element : m_elements)
    {
        if (element->isVisible())
            element->Draw();
    }
}
