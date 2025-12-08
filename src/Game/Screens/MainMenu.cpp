#include <iostream>
#include "MainMenu.h"
#include "../../ContestAPI/app.h"

MainMenu::MainMenu()
{
    // --- Create root panel ---
    m_panel = std::make_shared<UIPanel>();
    m_panel->SetPosition(100, 100);
    m_panel->SetSize(600, 400);

    // --- Title text ---
    auto title = std::make_shared<UIText>("MAIN MENU");
    title->SetPosition(150, 350);
    title->SetColor(1.0f, 1.0f, 0.0f); // yellow
    m_panel->AddElement(title);

    // --- Start button ---
    auto startBtn = std::make_shared<UIButton>("Start");
    startBtn->SetPosition(150, 250);
    startBtn->SetSize(300, 50);
    startBtn->SetText("Start Game");
    startBtn->SetOnClickCallback([]() {
        std::cout << "Button pressed" << std::endl;
    });

    // startBtn->SetOnClickCallback([]()
    // {
    //     App::Print(200, 200, "Starting Game...");
    // });

    m_panel->AddElement(startBtn);

    // --- Quit button ---
    auto quitBtn = std::make_shared<UIButton>("Quit");
    quitBtn->SetPosition(150, 180);
    quitBtn->SetSize(300, 50);
    quitBtn->SetText("Quit");

    quitBtn->SetOnClickCallback([]()
    {
        App::Print(200, 150, "Quitting...");
    });

    m_panel->AddElement(quitBtn);

    // Add the panel to this screen
    AddPanel(m_panel);
}