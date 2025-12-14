#include <iostream>

#include "World.h"

#include "../Player/Player.h"
#include "../../Core/UI/UIManager.h"
#include "../../Core/UI/UIText.h"
#include "../../Core/UI/UIButton.h"
#include "../../Core/UI/UIPanel.h"
#include "../../Core/UI/UIScreen.h"
#include "../../Core/Input/InputManager.h"

#include "../../Screens/MainMenu.h"
#include "../../Screens/Options.h"


void World::Init()
{
	player = new Player();
	player->Init();

	//------------------------------------------------------------------------
	// EXAMPLE PANEL (TEXT & BUTTON)
	ui_manager = new UIManager();

	ui_manager->Init();

	auto mainMenu = std::make_shared<MainMenu>(ui_manager);
    ui_manager->AddScreen("MainMenu", mainMenu);
	ui_manager->SetActiveScreen("MainMenu");
	auto options = std::make_shared<Options>(ui_manager);
    ui_manager->AddScreen("Options", options);

	// m_uiScreen = std::make_shared<UIScreen>();

	// // Example panel
	// auto panel = std::make_shared<UIPanel>();
	// panel->SetPosition(0, 50);
	// panel->SetSize(500, 500);
	// ui_manager->AddElement(panel);

    // // Example text
    // auto title = std::make_shared<UIText>("Hello UI System!");
    // title->SetPosition(50, 50);
    // title->SetColor(255, 255, 0);
	// ui_manager->AddElement(title);
    // panel->AddChildElement(title);

    // // Example button
    // auto button = std::make_shared<UIButton>("Start Game");
    // button->SetPosition(50, 120);
    // button->SetSize(200, 200);
    // button->SetText("Start Game");
    // button->SetOnClickCallback([]() {
    //     std::cout << "Button pressed" << std::endl;
    // });
	// ui_manager->AddElement(button);
    // panel->AddChildElement(button);

	// m_uiScreen->AddPanel(panel);
	// m_uiScreen->Init();

	//------------------------------------------------------------------------
	input_manager = new InputManager();
	input_manager->Init();
}

void World::Update(const float deltaTime)
{
	player->Update(deltaTime, *input_manager);

	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (input_manager->IsActionInputted(ACTION_PLAY))
	{
		App::PlayAudio("./Data/TestData/Test.wav", true);
	}
	if (input_manager->IsActionInputted(ACTION_PAUSE))
	{
		App::StopAudio("./Data/TestData/Test.wav");
	}

	//------------------------------------------------------------------------
	// EXAMPLE TEXT & BUTTON
	float mouseX = input_manager->GetMousePosX();
	float mouseY = input_manager->GetMousePosY();

	ui_manager->HandleMouseMove(mouseX, mouseY);

	if (input_manager->IsActionInputted(ACTION_SELECT))
	{
		ui_manager->HandleMouseClick(mouseX, mouseY);
	}
	//------------------------------------------------------------------------

}

void World::Render()
{
	player->Render();

	// //------------------------------------------------------------------------
	// // Example Line Drawing.
	// //------------------------------------------------------------------------
	// static float a = 0.0f;
	// const float r = 1.0f;
	// float g = 1.0f;
	// float b = 1.0f;
	// a += 0.1f;
	// for (int i = 0; i < 20; i++)
	// {

	// 	const float sx = 200 + sinf(a + i * 0.1f) * 60.0f;
	// 	const float sy = 200 + cosf(a + i * 0.1f) * 60.0f;
	// 	const float ex = 700 - sinf(a + i * 0.1f) * 60.0f;
	// 	const float ey = 700 - cosf(a + i * 0.1f) * 60.0f;
	// 	g = (float)i / 20.0f;
	// 	b = (float)i / 20.0f;
	// 	App::DrawLine(sx, sy, ex, ey, r, g, b);
	// }

	// //------------------------------------------------------------------------
	// // Example Triangle Drawing.
	// //------------------------------------------------------------------------
	// App::DrawTriangle(600.0f, 300.0f, 650.0f, 400.0f, 700.0f, 300.0f, 0.0f, 1.0f, 1.0f);
	// App::DrawTriangle(800.0f, 300.0f, 850.0f, 400.0f, 900.0f, 300.0f, 0.0f, 1.0f, 1.0f, true);

	ui_manager->Draw();
}

void World::Shutdown()
{
	player->Shutdown();
	ui_manager->Shutdown();
	input_manager->Shutdown();

	delete player;
	delete ui_manager;
	delete input_manager;
}