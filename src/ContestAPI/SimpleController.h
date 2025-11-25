//-----------------------------------------------------------------------------
// SimpleController.h
// Provides a simple way to query input from keyboard+mouse and/or controllers via XINPUT.
//-----------------------------------------------------------------------------
#ifndef _SIMPLECONTROLLER_H
#define _SIMPLECONTROLLER_H

#if BUILD_PLATFORM_WINDOWS
#if (_WIN32_WINNT >= 0x0604 /*_WIN32_WINNT_WIN8*/)
#include <XInput.h>
#pragma comment(lib,"xinput.lib")
#else
#include <XInput.h>
#pragma comment(lib,"xinput9_1_0.lib")
#endif
#endif //BUILD_PLATFORM_WINDOWS

#define MAX_CONTROLLERS 4  // XInput handles up to 4 controllers 
#define THUMB_STICK_MAX_RANGE 32768.0f
#define TRIGGER_MAX_RANGE 255.0f

#include <memory>

namespace App
{
	enum GamepadButton
	{
		BTN_A =				0x0001,
		BTN_B =				0x0002,
		BTN_X =				0x0004,
		BTN_Y =				0x0008,

		BTN_START =			0x0010,
		BTN_BACK =			0x0020,

		BTN_LBUMPER =		0x0040,
		BTN_LSTICK =		0x0080,
		BTN_RBUMPER =		0x0100,
		BTN_RSTICK =		0x0200,

		BTN_DPAD_LEFT =		0x0400,
		BTN_DPAD_RIGHT =	0x0800,
		BTN_DPAD_UP =		0x1000,
		BTN_DPAD_DOWN =		0x2000
	};
}

//-----------------------------------------------------------------------------
// CController
//-----------------------------------------------------------------------------

class CController
{
public:
	friend class CSimpleControllers;

	CController(){}
	virtual ~CController(){}

	virtual bool CheckButton(const App::GamepadButton button, const bool onPress = true) const = 0;

	virtual float GetLeftThumbStickX() const= 0 ;
	virtual float GetLeftThumbStickY() const = 0;
	virtual float GetRightThumbStickX() const = 0;
	virtual float GetRightThumbStickY() const = 0;
	virtual float GetLeftTrigger() const = 0;
	virtual float GetRightTrigger() const = 0;	
};

#if BUILD_PLATFORM_WINDOWS

class CControllerWindows : public CController
{
public:
	friend class CSimpleControllers;

	CControllerWindows();

	virtual bool CheckButton(const App::GamepadButton button, const bool onPress = true) const override;

	float GetLeftThumbStickX() const override ;
	float GetLeftThumbStickY() const override;
	float GetRightThumbStickX() const override;
	float GetRightThumbStickY() const override;
	float GetLeftTrigger() const override;
	float GetRightTrigger() const override;	

protected:
	XINPUT_STATE m_state;
	WORD m_lastButtons = 0;
	WORD m_debouncedButtons = 0;
	bool m_bConnected = false;
};

using TController = CControllerWindows;

#elif BUILD_PLATFORM_APPLE

class CControllerApple : public CController
{
public:
	friend class CSimpleControllers;

	CControllerApple();

	virtual bool CheckButton(const App::GamepadButton button, const bool onPress = true) const override;

	float GetLeftThumbStickX() const override;
	float GetLeftThumbStickY() const override;
	float GetRightThumbStickX() const override;
	float GetRightThumbStickY() const override;
	float GetLeftTrigger() const override;
	float GetRightTrigger() const override;	

protected:
	struct State
	{
		short m_leftStickX;
		short  m_leftStickY;
		short  m_rightStickX;
		short  m_rightStickY;
		short m_leftTrigger;
		short m_rightTrigger;

		unsigned int m_buttons;
		unsigned int m_lastButtons;
	};

	bool m_bConnected;
	State m_state;
};

using TController = CControllerApple;

#else

static_assert(false, "Controllers not implemented for this platform")

using TController = void;

#endif

//-----------------------------------------------------------------------------
// CSimpleControllers
//-----------------------------------------------------------------------------

class CSimpleControllers
{
public:
	static CSimpleControllers &GetInstance();
	
	void Update();
	
	const CController &GetController(const int pad = 0)
	{
		const int padNum = (pad >= MAX_CONTROLLERS) ? 0 : pad;
		return m_Controllers[padNum];
	}
private:
	TController m_Controllers[MAX_CONTROLLERS];
};
#endif