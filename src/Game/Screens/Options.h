//-----------------------------------------------------------------------------
// Options.h
// Options UI screen holding all its UI Elements (settings)
//-----------------------------------------------------------------------------
#pragma once

#include "../Core/UI/UIScreen.h"
#include "../Core/UI/UIPanel.h"
#include "../Core/UI/UIElement.h"
#include "../Core/UI/UIText.h"
#include "../Core/UI/UIButton.h"

class UIManager;

class Options : public UIScreen
{
public:
     Options(UIManager* owner);
    ~Options() override = default;

private:
    std::shared_ptr<UIPanel> m_panel;

    UIManager* m_UIManager;
};
