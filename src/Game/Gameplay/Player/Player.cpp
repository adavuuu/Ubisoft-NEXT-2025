#include "Player.h"

#include "Core/Constants.h"
#include "Core/Input/InputManager.h"

class CSimpleSprite;

void Player::Init()
{
	// Initialize Base Entity
	this->SetPosition(400.0f, 400.0f);
	this->SetVelocity(1.0f, 1.0f);

    //------------------------------------------------------------------------
	// Initialize Player Sprite
	constexpr float animationSpeed = 1.0f / 15.0f; // 15 frames per second
	m_sprite = App::CreateSprite("./data/TestData/Test.bmp", 8, 4);
	m_sprite->SetPosition(this->GetXPos(), this->GetYPos());
	m_sprite->CreateAnimation(Constants::ANIM_BACKWARDS, animationSpeed, { 0,1,2,3,4,5,6,7 });
	m_sprite->CreateAnimation(Constants::ANIM_LEFT, animationSpeed, { 8,9,10,11,12,13,14,15 });
	m_sprite->CreateAnimation(Constants::ANIM_RIGHT, animationSpeed, { 16,17,18,19,20,21,22,23 });
	m_sprite->CreateAnimation(Constants::ANIM_FORWARDS, animationSpeed, { 24,25,26,27,28,29,30,31 });
	m_sprite->SetScale(1.0f);
	//------------------------------------------------------------------------ 
}

void Player::Update(const float deltaTime, InputManager& inputManager)
{
	if (m_sprite != nullptr) {
		//------------------------------------------------------------------------
		// Example Sprite Code....
		float currX, currY;
		const std::pair<float, float> velocity = this->GetVelocity();
		m_sprite->GetPosition(currX, currY);
		m_sprite->Update(deltaTime);
		if (inputManager.IsActionInputted(ACTION_MOVE_RIGHT))
		{
			m_sprite->SetAnimation(Constants::ANIM_RIGHT);
			this->SetPosition(currX + velocity.first, currY);
			m_sprite->SetPosition(this->GetXPos(), this->GetYPos());
		}
		if (inputManager.IsActionInputted(ACTION_MOVE_LEFT))
		{
			m_sprite->SetAnimation(Constants::ANIM_LEFT);
			this->SetPosition(currX - velocity.first, currY);
			m_sprite->SetPosition(this->GetXPos(), this->GetYPos());
		}
		if (inputManager.IsActionInputted(ACTION_MOVE_FORWARD))
		{
			m_sprite->SetAnimation(Constants::ANIM_FORWARDS);
			this->SetPosition(currX, currY + velocity.second);
			m_sprite->SetPosition(this->GetXPos(), this->GetYPos());
		}
		if (inputManager.IsActionInputted(ACTION_MOVE_BACKWARD))
		{
			m_sprite->SetAnimation(Constants::ANIM_BACKWARDS);
			this->SetPosition(currX, currY - velocity.second);
			m_sprite->SetPosition(this->GetXPos(), this->GetYPos());
		}
		if (inputManager.IsActionInputted(ACTION_SCALE_UP))
		{
			m_sprite->SetScale(m_sprite->GetScale() + 0.1f);
		}
		if (inputManager.IsActionInputted(ACTION_SCALE_DOWN))
		{
			m_sprite->SetScale(m_sprite->GetScale() - 0.1f);
		}
		if (inputManager.IsActionInputted(ACTION_ROTATE_LEFT))
		{
			m_sprite->SetAngle(m_sprite->GetAngle() + 0.1f);
		}
		if (inputManager.IsActionInputted(ACTION_ROTATE_RIGHT))
		{
			m_sprite->SetAngle(m_sprite->GetAngle() - 0.1f);
		}
		if (inputManager.IsActionInputted(ACTION_STOP))
		{
			m_sprite->SetAnimation(-1);
		}
	}
}

void Player::Render()
{
    //------------------------------------------------------------------------
	// Example Sprite Code....
	m_sprite->Draw();
	//------------------------------------------------------------------------
}

void Player::Shutdown()
{
    //------------------------------------------------------------------------
	// Example Sprite Code....
	delete m_sprite;
	//------------------------------------------------------------------------
}