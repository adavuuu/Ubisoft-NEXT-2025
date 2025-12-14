#include "Player.h"

#include "Core/Input/InputManager.h"

class CSimpleSprite;

void Player::Init()
{
    //------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite = App::CreateSprite("./data/TestData/Test.bmp", 8, 4);
	testSprite->SetPosition(400.0f, 400.0f);
	const float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(1.0f);
	//------------------------------------------------------------------------ 
}

void Player::Update(const float deltaTime, InputManager& inputManager)
{
	if (testSprite != nullptr) {
		//------------------------------------------------------------------------
		// Example Sprite Code....
		testSprite->Update(deltaTime);
		if (inputManager.IsActionInputted(ACTION_MOVE_RIGHT))
		{
			testSprite->SetAnimation(ANIM_RIGHT);
			float x, y;
			testSprite->GetPosition(x, y);
			x += 1.0f;
			testSprite->SetPosition(x, y);
		}
		if (inputManager.IsActionInputted(ACTION_MOVE_LEFT))
		{
			testSprite->SetAnimation(ANIM_LEFT);
			float x, y;
			testSprite->GetPosition(x, y);
			x -= 1.0f;
			testSprite->SetPosition(x, y);
		}
		if (inputManager.IsActionInputted(ACTION_MOVE_FORWARD))
		{
			testSprite->SetAnimation(ANIM_FORWARDS);
			float x, y;
			testSprite->GetPosition(x, y);
			y += 1.0f;
			testSprite->SetPosition(x, y);
		}
		if (inputManager.IsActionInputted(ACTION_MOVE_BACKWARD))
		{
			testSprite->SetAnimation(ANIM_BACKWARDS);
			float x, y;
			testSprite->GetPosition(x, y);
			y -= 1.0f;
			testSprite->SetPosition(x, y);
		}
		if (inputManager.IsActionInputted(ACTION_SCALE_UP))
		{
			testSprite->SetScale(testSprite->GetScale() + 0.1f);
		}
		if (inputManager.IsActionInputted(ACTION_SCALE_DOWN))
		{
			testSprite->SetScale(testSprite->GetScale() - 0.1f);
		}
		if (inputManager.IsActionInputted(ACTION_ROTATE_LEFT))
		{
			testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
		}
		if (inputManager.IsActionInputted(ACTION_ROTATE_RIGHT))
		{
			testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
		}
		if (inputManager.IsActionInputted(ACTION_STOP))
		{
			testSprite->SetAnimation(-1);
		}
	}
}

void Player::Render()
{
    //------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite->Draw();
	//------------------------------------------------------------------------
}

void Player::Shutdown()
{
    //------------------------------------------------------------------------
	// Example Sprite Code....
	delete testSprite;
	//------------------------------------------------------------------------
}