//-----------------------------------------------------------------------------
// AppSettings.h
// Provides a variety of basic predefined variables and functions.
//-----------------------------------------------------------------------------
#ifndef _APP_SETTINGS_H
#define _APP_SETTINGS_H

// We can use two coordinate systems. NATIVE and VIRTUAL.
// VIRTUAL has coords from 0.0f to APP_VIRTUAL_[WIDTH/HEIGHT].
// NATIVE has coords from -1.0f to 1.0f with 0.0f,0.0f as the center of the window.
#define APP_USE_VIRTUAL_RES		true					// Set true to use virtual coords.					
#define APP_VIRTUAL_WIDTH		(1024)					// This will be the effective x resolution regardless of actual screen/window res.
#define APP_VIRTUAL_HEIGHT		(768)					// This will be the effective y resolution regardless of actual screen/window res.

#define APP_MAX_FRAME_RATE		(60.0f)					// Maximum update rate.
#define APP_INIT_WINDOW_WIDTH	(APP_VIRTUAL_WIDTH)		// Initial window width.
#define APP_INIT_WINDOW_HEIGHT	(APP_VIRTUAL_HEIGHT)	// Initial window height.
#define APP_WINDOW_TITLE		("Game")

#define APP_ENABLE_DEBUG_INFO_BUTTON		(App::BTN_DPAD_UP)
#define APP_QUIT_KEY						(App::KEY_Q)

// Pad emulation. (Uses keyboard if no pad is present) Maps the following keys to the pad inputs.
// Note analog inputs are either 0 or 1 when emulated. 
#define APP_PAD_EMUL_LEFT_THUMB_LEFT	(App::KEY_A)
#define APP_PAD_EMUL_LEFT_THUMB_RIGHT	(App::KEY_D)
#define APP_PAD_EMUL_LEFT_THUMB_UP		(App::KEY_W)
#define APP_PAD_EMUL_LEFT_THUMB_DOWN	(App::KEY_S)
#define APP_PAD_EMUL_BUTTON_ALT_A		(App::KEY_SPACE)
#define APP_PAD_EMUL_START				(App::KEY_7)

#define APP_PAD_EMUL_RIGHT_THUMB_LEFT	(App::KEY_LEFT)
#define APP_PAD_EMUL_RIGHT_THUMB_RIGHT	(App::KEY_RIGHT)
#define APP_PAD_EMUL_RIGHT_THUMB_UP		(App::KEY_UP)
#define APP_PAD_EMUL_RIGHT_THUMB_DOWN	(App::KEY_DOWN)

#define APP_PAD_EMUL_DPAD_UP			(App::KEY_I)
#define APP_PAD_EMUL_DPAD_DOWN			(App::KEY_K)
#define APP_PAD_EMUL_DPAD_LEFT			(App::KEY_J)
#define APP_PAD_EMUL_DPAD_RIGHT			(App::KEY_L)
	
#define APP_PAD_EMUL_BUTTON_BACK		(App::KEY_6)
#define APP_PAD_EMUL_BUTTON_A			(App::KEY_T)
#define APP_PAD_EMUL_BUTTON_B			(App::KEY_Y)
#define APP_PAD_EMUL_BUTTON_X			(App::KEY_G)
#define APP_PAD_EMUL_BUTTON_Y			(App::KEY_H)

#define APP_PAD_EMUL_LEFT_TRIGGER		    (App::KEY_1)
#define APP_PAD_EMUL_BUTTON_LEFT_THUMB		(App::KEY_2)
#define APP_PAD_EMUL_BUTTON_LEFT_SHOULDER	(App::KEY_3)

#define APP_PAD_EMUL_RIGHT_TRIGGER		    (App::KEY_8)
#define APP_PAD_EMUL_BUTTON_RIGHT_THUMB		(App::KEY_9)
#define APP_PAD_EMUL_BUTTON_RIGHT_SHOULDER	(App::KEY_0)

#ifdef _DEBUG
#define APP_RENDER_UPDATE_TIMES				true
#else
#define APP_RENDER_UPDATE_TIMES				false
#endif

#define FRAND	(static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
#define FRAND_RANGE(_MIN_, _MAX_ ) (FRAND * ((_MAX_)-(_MIN_)) + (_MIN_))
#define PI		(3.14159265359f)

#endif
