//-----------------------------------------------------------------------------
// MainMenu.h
// Main Menu UI holding all its UI Elements
//-----------------------------------------------------------------------------
#pragma once

#include "../Core/UI/UIScreen.h"
#include "../Core/UI/UIPanel.h"
#include "../Core/UI/UIElement.h"
#include "../Core/UI/UIText.h"
#include "../Core/UI/UIButton.h"

class MainMenu : public UIScreen
{
public:
     MainMenu();
    ~MainMenu() override = default;

private:
    std::shared_ptr<UIPanel> m_panel;
};
