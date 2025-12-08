#include <iostream>
#include <GL/freeglut.h>

#include "World.h"

#include "../Player/Player.h"
#include "../../Core/UI/UIManager.h"
#include "../../Core/UI/UIText.h"
#include "../../Core/UI/UIButton.h"
#include "../../Core/UI/UIPanel.h"


void World::Init()
{
	player = new Player();
	player->Init();

	//------------------------------------------------------------------------
	// EXAMPLE PANEL (TEXT & BUTTON)
	ui_manager = new UIManager();

	ui_manager->Initialize();

	// Example panel
	auto panel = std::make_shared<UIPanel>();
	panel->SetPosition(0, 50);
	panel->SetSize(500, 500);
	ui_manager->AddElement(panel);

    // Example text
    auto title = std::make_shared<UIText>("Hello UI System!");
    title->SetPosition(50, 50);
    title->SetColor(255, 255, 0);
	ui_manager->AddElement(title);
    panel->AddChildElement(title);

    // Example button
    auto button = std::make_shared<UIButton>("Start Game");
    button->SetPosition(50, 120);
    button->SetSize(200, 200);
    button->SetText("Start Game");
    button->SetOnClickCallback([]() {
        std::cout << "Button pressed" << std::endl;
    });
	ui_manager->AddElement(button);
    panel->AddChildElement(button);
	
	//------------------------------------------------------------------------
}

void World::Update(const float deltaTime)
{
	player->Update(deltaTime);

	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(App::BTN_B, true))
	{
		App::PlayAudio("./Data/TestData/Test.wav", true);
	}
	if (App::GetController().CheckButton(App::BTN_X, true))
	{
		App::StopAudio("./Data/TestData/Test.wav");
	}

	//------------------------------------------------------------------------
	// EXAMPLE TEXT & BUTTON
	float mouseX, mouseY;
	App::GetMousePos(mouseX, mouseY);
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) - mouseY;

	ui_manager->HandleMouseMove(mouseX, mouseY);

	if (App::IsMousePressed(GLUT_LEFT_BUTTON))
	{
		ui_manager->HandleMouseClick(mouseX, mouseY);
	}
	//------------------------------------------------------------------------

}

void World::Render()
{
	player->Render();

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(100, 100, "Sample Text");

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	static float a = 0.0f;
	const float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		const float sx = 200 + sinf(a + i * 0.1f) * 60.0f;
		const float sy = 200 + cosf(a + i * 0.1f) * 60.0f;
		const float ex = 700 - sinf(a + i * 0.1f) * 60.0f;
		const float ey = 700 - cosf(a + i * 0.1f) * 60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey, r, g, b);
	}

	//------------------------------------------------------------------------
	// Example Triangle Drawing.
	//------------------------------------------------------------------------
	App::DrawTriangle(600.0f, 300.0f, 650.0f, 400.0f, 700.0f, 300.0f, 0.0f, 1.0f, 1.0f);
	App::DrawTriangle(800.0f, 300.0f, 850.0f, 400.0f, 900.0f, 300.0f, 0.0f, 1.0f, 1.0f, true);

	ui_manager->Draw();
}

void World::Shutdown()
{
	player->Shutdown();
}