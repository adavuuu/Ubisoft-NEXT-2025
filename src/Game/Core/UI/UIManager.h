//-----------------------------------------------------------------------------
// UIManager.h
// Manages all UI elements: initialization, updating, and drawing.
//-----------------------------------------------------------------------------
#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

#include <vector>
#include "UIElement.h"

//-----------------------------------------------------------------------------
// CUIManager
//-----------------------------------------------------------------------------
class CUIManager
{
public:

    CUIManager();
    ~CUIManager();

    bool Initialize();
    void Shutdown();

    void AddElement(CUIElement* element);
    void RemoveElement(CUIElement* element);

    void Update(float deltaTime);
    void Draw();

private:
    std::vector<CUIElement*> m_elements;
};

#endif