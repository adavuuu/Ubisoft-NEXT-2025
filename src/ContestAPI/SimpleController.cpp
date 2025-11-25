///////////////////////////////////////////////////////////////////////////////
// Filename: SimpleController.cpp
// Provides a simple way to query input from keyboard+mouse and/or controllers via XINPUT.
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
#if BUILD_PLATFORM_WINDOWS
#include <windows.h>  // for MS Windows
#include <stdio.h>
#endif
//-----------------------------------------------------------------------------
#include "SimpleController.h"
#include "app.h"

#if BUILD_PLATFORM_WINDOWS
//-----------------------------------------------------------------------------
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
#include <XInput.h>
#pragma comment(lib,"xinput.lib")
#else
#include <XInput.h>
#pragma comment(lib,"xinput9_1_0.lib")
#endif
//-----------------------------------------------------------------------------
#define UPDATE_DZONE		// Define if you want a dead zone on the thumb stick analog inputs.
#define INPUT_DEADZONE  ( 0.10f * FLOAT(0x7FFF) )  // Default to 10% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.
//-----------------------------------------------------------------------------

#elif BUILD_PLATFORM_APPLE

#include "SDL3/SDL_gamepad.h"
#include <iostream>

#endif

#if BUILD_PLATFORM_WINDOWS

CControllerWindows::CControllerWindows()
{
	ZeroMemory(&m_state, sizeof(XINPUT_STATE));
}	

bool CControllerWindows::CheckButton(const App::GamepadButton button, const bool onPress) const
{
	#define HANDLE_XNA_BUTTON(BUTTON, BUTTONCODE) \
		case BUTTON: xnaButton = BUTTONCODE; break;

	int xnaButton = 0;
	switch(button)
	{
		HANDLE_XNA_BUTTON(App::BTN_A, XINPUT_GAMEPAD_A)
		HANDLE_XNA_BUTTON(App::BTN_B, XINPUT_GAMEPAD_B)
		HANDLE_XNA_BUTTON(App::BTN_X, XINPUT_GAMEPAD_X)
		HANDLE_XNA_BUTTON(App::BTN_Y, XINPUT_GAMEPAD_Y)

		HANDLE_XNA_BUTTON(App::BTN_START, XINPUT_GAMEPAD_START)
		HANDLE_XNA_BUTTON(App::BTN_BACK, XINPUT_GAMEPAD_BACK)

		HANDLE_XNA_BUTTON(App::BTN_LBUMPER, XINPUT_GAMEPAD_LEFT_SHOULDER)
		HANDLE_XNA_BUTTON(App::BTN_LSTICK, XINPUT_GAMEPAD_LEFT_THUMB)

		HANDLE_XNA_BUTTON(App::BTN_RBUMPER, XINPUT_GAMEPAD_RIGHT_SHOULDER)
		HANDLE_XNA_BUTTON(App::BTN_RSTICK, XINPUT_GAMEPAD_RIGHT_THUMB)

		HANDLE_XNA_BUTTON(App::BTN_DPAD_LEFT, XINPUT_GAMEPAD_DPAD_LEFT)
		HANDLE_XNA_BUTTON(App::BTN_DPAD_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT)
		HANDLE_XNA_BUTTON(App::BTN_DPAD_UP, XINPUT_GAMEPAD_DPAD_UP)
		HANDLE_XNA_BUTTON(App::BTN_DPAD_DOWN, XINPUT_GAMEPAD_DPAD_DOWN)
	}

	if (onPress)
	{
		return (m_debouncedButtons & xnaButton) != 0;
	}
	else
	{
		return (m_lastButtons & xnaButton) != 0;
	}
}

float CControllerWindows::GetLeftThumbStickX() const
{
	return (float)m_state.Gamepad.sThumbLX / THUMB_STICK_MAX_RANGE;
}
float CControllerWindows::GetLeftThumbStickY() const
{
	return (float)m_state.Gamepad.sThumbLY / THUMB_STICK_MAX_RANGE;
}
float CControllerWindows::GetRightThumbStickX() const
{
	return (float)m_state.Gamepad.sThumbRX / THUMB_STICK_MAX_RANGE;
}
float CControllerWindows::GetRightThumbStickY() const
{
	return (float)m_state.Gamepad.sThumbRY / THUMB_STICK_MAX_RANGE;
}
float CControllerWindows::GetLeftTrigger() const
{
	return (float)m_state.Gamepad.bLeftTrigger / TRIGGER_MAX_RANGE;
}
float CControllerWindows::GetRightTrigger() const
{
	return (float)m_state.Gamepad.bRightTrigger / TRIGGER_MAX_RANGE;
}

#else

CControllerApple::CControllerApple()
{
}	

bool CControllerApple::CheckButton(const App::GamepadButton button, const bool onPress) const
{
	if (onPress)
	{
		return (m_state.m_buttons & button) && !(m_state.m_lastButtons & button);
	}
	else
	{
		return m_state.m_buttons & button;
	}
}

float CControllerApple::GetLeftThumbStickX() const
{
	return m_state.m_leftStickX / THUMB_STICK_MAX_RANGE;
}
float CControllerApple::GetLeftThumbStickY() const
{
	return m_state.m_leftStickY / THUMB_STICK_MAX_RANGE;
}
float CControllerApple::GetRightThumbStickX() const
{
	return m_state.m_rightStickX / THUMB_STICK_MAX_RANGE;
}
float CControllerApple::GetRightThumbStickY() const
{
	return m_state.m_rightStickY / THUMB_STICK_MAX_RANGE;
}
float CControllerApple::GetLeftTrigger() const
{
	return m_state.m_leftTrigger / THUMB_STICK_MAX_RANGE; 
}
float CControllerApple::GetRightTrigger() const
{
	return m_state.m_rightTrigger / THUMB_STICK_MAX_RANGE;
}

#endif


//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------
CSimpleControllers &CSimpleControllers::GetInstance()
{
	static CSimpleControllers theControllers;
	return theControllers;
}

#if BUILD_PLATFORM_WINDOWS
//-----------------------------------------------------------------------------
void CSimpleControllers::Update()
{
	DWORD dwResult;
	int numControllers = 0;
    for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
    {
        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState( i, &m_Controllers[i].m_state );

		if (dwResult == ERROR_SUCCESS)
		{
			m_Controllers[i].m_bConnected = true;
			numControllers++;
		}
        else
            m_Controllers[i].m_bConnected = false;
    }

	if (numControllers == 0)
	{
		m_Controllers[0].m_bConnected = true;
		WORD buttons = 0;
		m_Controllers[0].m_state.Gamepad.sThumbLX = 0;
		m_Controllers[0].m_state.Gamepad.sThumbLY = 0;
		m_Controllers[0].m_state.Gamepad.sThumbRX = 0;
		m_Controllers[0].m_state.Gamepad.sThumbRY = 0;
		m_Controllers[0].m_state.Gamepad.bLeftTrigger = 0;
		m_Controllers[0].m_state.Gamepad.bRightTrigger = 0;		

		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT)) m_Controllers[0].m_state.Gamepad.sThumbLX = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT)) m_Controllers[0].m_state.Gamepad.sThumbLX = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP)) m_Controllers[0].m_state.Gamepad.sThumbLY = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN)) m_Controllers[0].m_state.Gamepad.sThumbLY = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_ALT_A)) buttons |= XINPUT_GAMEPAD_A;
		if (App::IsKeyPressed(APP_PAD_EMUL_START)) buttons |= XINPUT_GAMEPAD_START;
		
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_LEFT)) m_Controllers[0].m_state.Gamepad.sThumbRX = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_RIGHT)) m_Controllers[0].m_state.Gamepad.sThumbRX = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_UP)) m_Controllers[0].m_state.Gamepad.sThumbRY = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_DOWN)) m_Controllers[0].m_state.Gamepad.sThumbRY = 32767;

		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_UP))   buttons |= XINPUT_GAMEPAD_DPAD_UP;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_DOWN)) buttons |= XINPUT_GAMEPAD_DPAD_DOWN;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_LEFT)) buttons |= XINPUT_GAMEPAD_DPAD_LEFT;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_RIGHT))buttons |= XINPUT_GAMEPAD_DPAD_RIGHT;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_BACK)) buttons |= XINPUT_GAMEPAD_BACK;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_A)) buttons |= XINPUT_GAMEPAD_A;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_B)) buttons |= XINPUT_GAMEPAD_B;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_X)) buttons |= XINPUT_GAMEPAD_X;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_Y)) buttons |= XINPUT_GAMEPAD_Y;

		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_TRIGGER)) m_Controllers[0].m_state.Gamepad.bLeftTrigger = 255;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_TRIGGER)) m_Controllers[0].m_state.Gamepad.bRightTrigger = 255;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_LEFT_THUMB)) buttons |= XINPUT_GAMEPAD_LEFT_THUMB;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_RIGHT_THUMB)) buttons |= XINPUT_GAMEPAD_RIGHT_THUMB;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_LEFT_SHOULDER)) buttons |= XINPUT_GAMEPAD_LEFT_SHOULDER;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_RIGHT_SHOULDER)) buttons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;

		m_Controllers[0].m_state.Gamepad.wButtons = buttons;
	}

	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (m_Controllers[i].m_bConnected)
		{
#ifdef UPDATE_DZONE					
			m_Controllers[i].m_debouncedButtons = ~m_Controllers[i].m_lastButtons &m_Controllers[i].m_state.Gamepad.wButtons;
			m_Controllers[i].m_lastButtons = m_Controllers[i].m_state.Gamepad.wButtons;

			// Zero value if thumbsticks are within the dead zone 
			if ((m_Controllers[i].m_state.Gamepad.sThumbLX < INPUT_DEADZONE &&
				m_Controllers[i].m_state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
				(m_Controllers[i].m_state.Gamepad.sThumbLY < INPUT_DEADZONE &&
					m_Controllers[i].m_state.Gamepad.sThumbLY > -INPUT_DEADZONE))
			{
				m_Controllers[i].m_state.Gamepad.sThumbLX = 0;
				m_Controllers[i].m_state.Gamepad.sThumbLY = 0;
			}

			if ((m_Controllers[i].m_state.Gamepad.sThumbRX < INPUT_DEADZONE &&
				m_Controllers[i].m_state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
				(m_Controllers[i].m_state.Gamepad.sThumbRY < INPUT_DEADZONE &&
					m_Controllers[i].m_state.Gamepad.sThumbRY > -INPUT_DEADZONE))
			{
				m_Controllers[i].m_state.Gamepad.sThumbRX = 0;
				m_Controllers[i].m_state.Gamepad.sThumbRY = 0;
			}
#endif		
		}
	}
}
#else
//-----------------------------------------------------------------------------
void CSimpleControllers::Update()
{
	bool hasControllers = SDL_HasGamepad();
	
	// No controllers so lets fake one using keyboard defines.
	if (!hasControllers )
	{
		m_Controllers[0].m_state.m_lastButtons = m_Controllers[0].m_state.m_buttons;

		m_Controllers[0].m_bConnected = true;
		m_Controllers[0].m_state.m_leftStickX = 0;
		m_Controllers[0].m_state.m_leftStickY = 0;
		m_Controllers[0].m_state.m_rightStickX = 0;
		m_Controllers[0].m_state.m_rightStickY = 0;
		m_Controllers[0].m_state.m_leftStickX = 0;
		m_Controllers[0].m_state.m_leftTrigger = 0;
		m_Controllers[0].m_state.m_rightTrigger = 0;
		
		int buttons = 0;

		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT)) m_Controllers[0].m_state.m_leftStickX = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT)) m_Controllers[0].m_state.m_leftStickX = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP)) m_Controllers[0].m_state.m_leftStickY = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN)) m_Controllers[0].m_state.m_leftStickY = -32767;

		//if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_ALT_A)) buttons |= App:BTN_BACK;
		if (App::IsKeyPressed(APP_PAD_EMUL_START)) buttons |= App::BTN_START;
		
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_LEFT)) m_Controllers[0].m_state.m_rightStickX = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_RIGHT)) m_Controllers[0].m_state.m_rightStickX = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_UP)) m_Controllers[0].m_state.m_rightStickY = -32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_THUMB_DOWN)) m_Controllers[0].m_state.m_rightStickY = 32767;

		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_UP))   buttons |= App::BTN_DPAD_UP;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_DOWN)) buttons |= App::BTN_DPAD_DOWN;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_LEFT)) buttons |= App::BTN_DPAD_LEFT;
		if (App::IsKeyPressed(APP_PAD_EMUL_DPAD_RIGHT))buttons |= App::BTN_DPAD_RIGHT;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_BACK)) buttons |= App::BTN_BACK;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_A)) buttons |= App::BTN_A;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_B)) buttons |= App::BTN_B;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_X)) buttons |= App::BTN_X;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_Y)) buttons |= App::BTN_Y;

		if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_TRIGGER)) m_Controllers[0].m_state.m_leftTrigger = 32767;
		if (App::IsKeyPressed(APP_PAD_EMUL_RIGHT_TRIGGER)) m_Controllers[0].m_state.m_rightTrigger = 32767;

		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_LEFT_THUMB)) buttons |= App::BTN_LSTICK;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_RIGHT_THUMB)) buttons |= App::BTN_RSTICK;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_LEFT_SHOULDER)) buttons |= App::BTN_LBUMPER;
		if (App::IsKeyPressed(APP_PAD_EMUL_BUTTON_RIGHT_SHOULDER)) buttons |= App::BTN_RBUMPER;

		m_Controllers[0].m_state.m_buttons = buttons;
	}
	else
	{
		int count;
		SDL_JoystickID * gamepads = SDL_GetGamepads(&count);

		//Reset all controllers, move button & last button forward
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			m_Controllers[i].m_bConnected = false;
			m_Controllers[i].m_state.m_lastButtons = m_Controllers[i].m_state.m_buttons;
		}

		//Fill data
		count = std::min(count, MAX_CONTROLLERS);
		for (int pad = 0; pad < count; pad++)
		{
			SDL_Gamepad * gamepad = SDL_OpenGamepad(gamepads[pad]);

			if (gamepad == nullptr)
			{
				continue;
			}

			SDL_GetGamepadMapping(gamepad);

			m_Controllers[pad].m_bConnected = true;
			unsigned int buttons = 0;

			//Converts SDL Joystick axis to App Axis
#define HANDLE_AXIS(STATE_MEMBER, SDL_AXIS) \
	m_Controllers[pad].m_state. STATE_MEMBER = SDL_GetGamepadAxis(gamepad, SDL_AXIS);

			//Converts SDL Button to App Button
#define HANDLE_BUTTON(SDL_BUTTON, BUTTON) \
	if (SDL_GetGamepadButton(gamepad, SDL_BUTTON)) { buttons |= BUTTON; }

			HANDLE_AXIS(m_leftStickX, SDL_GAMEPAD_AXIS_LEFTX)
			HANDLE_AXIS(m_leftStickY, SDL_GAMEPAD_AXIS_LEFTY)
			HANDLE_AXIS(m_rightStickX, SDL_GAMEPAD_AXIS_RIGHTX)
			HANDLE_AXIS(m_rightStickY, SDL_GAMEPAD_AXIS_RIGHTY)
			HANDLE_AXIS(m_leftTrigger, SDL_GAMEPAD_AXIS_LEFT_TRIGGER)
			HANDLE_AXIS(m_rightTrigger, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER)

			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_SOUTH, App::BTN_A)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_EAST, App::BTN_B)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_WEST, App::BTN_X)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_NORTH, App::BTN_Y)

			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_DPAD_UP, App::BTN_DPAD_UP)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_DPAD_DOWN, App::BTN_DPAD_DOWN)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_DPAD_LEFT, App::BTN_DPAD_LEFT)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_DPAD_RIGHT, App::BTN_DPAD_RIGHT)

			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, App::BTN_LBUMPER)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_LEFT_STICK, App::BTN_LSTICK)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, App::BTN_RBUMPER)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_RIGHT_STICK, App::BTN_RSTICK)

			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_BACK, App::BTN_BACK)
			HANDLE_BUTTON(SDL_GAMEPAD_BUTTON_START, App::BTN_START)

			m_Controllers[pad].m_state.m_buttons = buttons;

			SDL_CloseGamepad(gamepad);
		}
		
		//Some Useful Controller Debug Code that outputs the controller state each frame
		// for (int i = 0; i < MAX_CONTROLLERS; i++)
		// {
		// 	std::cout << "Gamepad " << i;
		// 	std::cout << " Connected: " << m_Controllers[i].m_bConnected;
			
		// 	if (m_Controllers[i].m_bConnected)
		// 	{
		// 		std::cout << "LeftStick: (" << m_Controllers[i].m_state.m_leftStickX << ", "<< m_Controllers[i].m_state.m_leftStickY << ")";
		// 		std::cout << "RightStick: (" << m_Controllers[i].m_state.m_rightStickX << ", "<< m_Controllers[i].m_state.m_rightStickY << ")";
		// 		std::cout << "Triggers: (" << m_Controllers[i].m_state.m_leftTrigger << ", " << m_Controllers[i].m_state.m_rightTrigger << ")";

		// 		std::cout << std::hex << "Buttons: " << m_Controllers[i].m_state.m_buttons << std::dec;
		// 	}

		// 	std::cout << "\n";
		// }

		SDL_free(gamepads);
	}

}
#endif