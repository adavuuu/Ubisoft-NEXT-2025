#include <iostream>
#include "Options.h"
#include "../Core/UI/UIManager.h"
#include "../../ContestAPI/app.h"

Options::Options(UIManager* owner)
    : UIScreen(owner)
    , m_UIManager(owner)
{
    // --- Create root panel ---
    m_panel = std::make_shared<UIPanel>();
    m_panel->SetPosition(100, 100);
    m_panel->SetSize(600, 400);

    // --- Title text ---
    auto title = std::make_shared<UIText>("OPTIONS");
    title->SetPosition(150, 350);
    title->SetColor(1.0f, 1.0f, 0.0f); // yellow
    m_panel->AddElement(title);

    // --- Start button ---
    auto volumeBtn = std::make_shared<UIButton>("Volume");
    volumeBtn->SetPosition(150, 250);
    volumeBtn->SetSize(300, 50);
    volumeBtn->SetOnClickCallback([]() {
        std::cout << "Volume pressed" << std::endl;
    });

    m_panel->AddElement(volumeBtn);

    // --- Start button ---
    auto keybindBtn = std::make_shared<UIButton>("Keybinds");
    keybindBtn->SetPosition(150, 215);
    keybindBtn->SetSize(300, 50);
    keybindBtn->SetOnClickCallback([]() {
        std::cout << "Keybinds pressed" << std::endl;
    });

    m_panel->AddElement(keybindBtn);

    // --- Quit button ---
    auto backBtn = std::make_shared<UIButton>("Back");
    backBtn->SetPosition(150, 180);
    backBtn->SetSize(300, 50);
    backBtn->SetOnClickCallback([this]()
    {
        m_UIManager->SetActiveScreen("MainMenu");
    });

    m_panel->AddElement(backBtn);

    // Add the panel to this screen
    AddPanel(m_panel);
}