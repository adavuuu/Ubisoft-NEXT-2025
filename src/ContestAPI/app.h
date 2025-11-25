//---------------------------------------------------------------------------------
// App.h
// Provides a number of basic helper functions that wrap around thing like rendering, sound, and input handling
//---------------------------------------------------------------------------------
#ifndef _APP_H
#define _APP_H

#if BUILD_PLATFORM_WINDOWS
//Have game project import main function
#pragma comment(linker, "/include:wWinMain")

//---------------------------------------------------------------------------------
#include <windows.h> 
#endif //BUILD_PLATFORM_WINDOWS

//---------------------------------------------------------------------------------
#include "freeglut_config.h"

//---------------------------------------------------------------------------------
#include "AppSettings.h"
#include "SimpleController.h"
#include "SimpleSprite.h"

#define APP_VIRTUAL_TO_NATIVE_COORDS(_x_,_y_)			_x_ = ((_x_ / APP_VIRTUAL_WIDTH )*2.0f) - 1.0f; _y_ = ((_y_ / APP_VIRTUAL_HEIGHT)*2.0f) - 1.0f;
#define APP_NATIVE_TO_VIRTUAL_COORDS(_x_,_y_)			_x_ = ((_x_ + 1.0f) * APP_VIRTUAL_WIDTH) / 2.0f; _y_ = ((_y_ + 1.0f) * APP_VIRTUAL_HEIGHT) / 2.0f;

//---------------------------------------------------------------------------------
// App namespace: These are the IO calls you can use for you game.
//---------------------------------------------------------------------------------
namespace App
{
	//*******************************************************************************************
	// App Keycodes
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// Platform Independent way of managing ascii keys & special keys
	//-------------------------------------------------------------------------------------------
	enum Key
	{
		//Letter Keys
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,

		//Number Keys
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_0,

		//Special Keys
		KEY_SPACE,
		KEY_ESC,
		KEY_ENTER,
		KEY_TAB,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_INSERT,
	};

	//*******************************************************************************************
	// Display Calls.
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// void DrawLine( float sx, float sy, float ex, float ey, float r = 1.0f, float g = 1.0f, float b = 1.0f );
	//-------------------------------------------------------------------------------------------
	// Draw a 2D Line from sx,sy to ex, ey using color r = red, g = green, b=blue.
	//-------------------------------------------------------------------------------------------
	void DrawLine(const float sx, const float sy, const float ex, const float ey, const float r = 1.0f, const float g = 1.0f, const float b = 1.0f);

	//-------------------------------------------------------------------------------------------
	// void DrawTriangle(const float p1x, const float p1y, const float p2x, const float p2y, const float p3x, const float p3y, const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const bool wireframe = false)
	//-------------------------------------------------------------------------------------------
	// Draws a filled 2D Triangle with the 3 points (p1x, p1y), (p2x, p2y), (p3x, p3y), using color r = red, g = green, b=blue. There is also the option to draw the triangle as a wireframe or filled.
	//-------------------------------------------------------------------------------------------
	void DrawTriangle(const float p1x, const float p1y, const float p2x, const float p2y, const float p3x, const float p3y, const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const bool wireframe = false);

	//-------------------------------------------------------------------------------------------
	// void Print(float x, float y, const char *text, float r = 1.0f, float g = 1.0f, float b = 1.0f, void *font = GLUT_BITMAP_HELVETICA_18);
	//-------------------------------------------------------------------------------------------
	// Print text to screen at x,y coordinates using color r = red, g = green, b=blue using the passed GLUT font. 
	// Color values are in the range 0.0f to 1.0f.
	// Available fonts...
	// GLUT_BITMAP_9_BY_15, GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_10, GLUT_BITMAP_TIMES_ROMAN_24
	// GLUT_BITMAP_HELVETICA_10, GLUT_BITMAP_HELVETICA_12, GLUT_BITMAP_HELVETICA_18	
	//-------------------------------------------------------------------------------------------
	void Print(const float x, const float y, const char *text, const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, void *font = GLUT_BITMAP_HELVETICA_18);

	//-------------------------------------------------------------------------------------------
	// CSimpleSprite *CreateSprite(const char *fileName, int columns, int rows)
	//-------------------------------------------------------------------------------------------
	// Creates a sprite object from the given texture file. File must be a 32 bit BMP format.
	// The columns and rows paramaters define the number of columns and rows of sprite animation
	// frames in the given image.
	// You can then use the CSimpleSprite methods to animate/move etc.
	//-------------------------------------------------------------------------------------------
	CSimpleSprite *CreateSprite(const char *fileName, const int columns, const int rows);
		
	//*******************************************************************************************
	// Sound handling.	
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// void PlayAudio(const char *fileName, bool looping = false);
	//-------------------------------------------------------------------------------------------
	// Plays the passed .wav file. Set looping to true if you want the sound to loop.
	// If the sound is already playing it will restart.
	//-------------------------------------------------------------------------------------------
	void PlayAudio(const char *fileName, const bool looping = false);

	//-------------------------------------------------------------------------------------------
	// void StopAudio(const char *fileName);
	//-------------------------------------------------------------------------------------------	
	// Stops the given .wav file from playing.
	//-------------------------------------------------------------------------------------------	
	void StopAudio(const char *fileName);

	//-------------------------------------------------------------------------------------------
	// bool IsSoundPlaying(const char *filename);
	//-------------------------------------------------------------------------------------------	
	// Returns true if the given .wav file is currently playing.
	//-------------------------------------------------------------------------------------------	
	bool IsSoundPlaying(const char *filename);
	
	//*******************************************************************************************
	// Input handling.	
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// bool IsKeyPressed(int key);
	//-------------------------------------------------------------------------------------------
	// Returns true if the given key is currently being pressed. Uses custom App keys
	// Doesn't support extended functions
	// e.g.
	// IsKeyPressed(App:KEY_A); // Is a pressed
	// IsKeyPressed(App::KEY_LEFT; // Is left arrow pressed
	//-------------------------------------------------------------------------------------------
	bool IsKeyPressed(const Key key);

	//-------------------------------------------------------------------------------------------
	// void GetMousePos(float &x, float &y);
	//-------------------------------------------------------------------------------------------
	// Sets the value of the passed in float references to the current position of the mouse pointer.	
	//-------------------------------------------------------------------------------------------
	void GetMousePos(float &x, float &y);

	//-------------------------------------------------------------------------------------------
	// 	bool IsMousePressed(int button);
	//-------------------------------------------------------------------------------------------
	// Checks if mouse button is pressed. Uses GLUT constants
	// e.g.
	// IsMousePressed(GLUT_LEFT_BUTTON)
	//-------------------------------------------------------------------------------------------
	bool IsMousePressed(int button);

	//-------------------------------------------------------------------------------------------
	// const CController &GetController(int pad = 0);
	//-------------------------------------------------------------------------------------------
	// Returns a reference to a game controller. 
	// You can use this object to query gamepad buttons and analog stick positions etc.
	// e.g.
	// GetController(0).CheckButton(XINPUT_GAMEPAD_A, false); Returns true if the A button of pad 0 was pressed and repeat if held.
	// GetController(0).CheckButton(XINPUT_GAMEPAD_A, true); Returns true if the A button of pad 0 was pressed but DO NOT repeat if held.	
	// GetController(0).GetLeftThumbStickX(); Returns a float between -1.0f to 1.0f representing the position of the left thumb sticks X Axis.
	// See SimpleController.h for more info.
	//-------------------------------------------------------------------------------------------
	const CController &GetController(const int pad = 0 );
};
#endif //_APP_H