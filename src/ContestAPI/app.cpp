///////////////////////////////////////////////////////////////////////////////
// Filename: App.cpp
// Provides a number of basic helper functions that wrap around thing like rendering, sound, and input handling
///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------
#include <string>
#include "main.h"
#include "app.h"
#include "SimpleSound.h"
#include "SimpleController.h"
#include "SimpleSprite.h"

#include <iostream>

//---------------------------------------------------------------------------------
// Utils and externals for system info.

namespace App
{	
	void DrawLine(const float sx, const float sy, const float ex, const float ey, const float r, const float g, const float b)
	{
		float startX = sx;
		float startY = sy;
		float endX = ex;
		float endY = ey;
#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(startX, startY);
		APP_VIRTUAL_TO_NATIVE_COORDS(endX, endY);
#endif
		glBegin(GL_LINES);
		glColor3f(r, g, b); // Yellow
		glVertex2f(startX, startY);
		glVertex2f(endX, endY);
		glEnd();
	}

	void DrawTriangle(const float p1x, const float p1y, const float p2x, const float p2y, const float p3x, const float p3y, const float r, const float g, const float b, const bool wireframe)
	{
		float point1X = p1x;
		float point1Y = p1y;
		
		float point2X = p2x;
		float point2Y = p2y;

		float point3X = p3x;
		float point3Y = p3y;

#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(point1X, point1Y);
		APP_VIRTUAL_TO_NATIVE_COORDS(point2X, point2Y);
		APP_VIRTUAL_TO_NATIVE_COORDS(point3X, point3Y);
#endif
		if (wireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);
		glVertex2f(point1X, point1Y);
		glVertex2f(point2X, point2Y);
		glVertex2f(point3X, point3Y);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	CSimpleSprite *CreateSprite(const char *fileName, const int columns, const int rows)
	{
		return new CSimpleSprite(fileName, columns, rows);
	}

	void GetMousePos(float &x, float &y)
	{
		Internal::GetMousePos(x, y);

		x = (x * 2.0 / WINDOW_WIDTH) - 1.0;
		y = (y * 2.0 / WINDOW_HEIGHT) - 1.0;

#if APP_USE_VIRTUAL_RES
		APP_NATIVE_TO_VIRTUAL_COORDS(x, y);
#endif
	}

	bool IsMousePressed(int button)
	{
		return Internal::IsMousePressed(button);
	}

	void PlayAudio(const char *fileName, const bool looping)
	{
		const SoundFlags flags = (looping) ? SoundFlags::Looping : SoundFlags::None;
		CSimpleSound::GetInstance().StartSound(fileName, flags);
	}

	void StopAudio(const char *fileName)
	{
		CSimpleSound::GetInstance().StopSound(fileName);
	}

	bool IsSoundPlaying(const char *fileName)
	{
		return CSimpleSound::GetInstance().IsPlaying(fileName);
	}

	// This prints a string to the screen
	void Print(const float x, const float y, const char *st, const float r, const float g, const float b, void *font)
	{
		float xPos = x;
		float yPos = y;
#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(xPos, yPos);
#endif		
		// Set location to start printing text
		glColor3f(r, g, b); // Yellow
		glRasterPos2f(xPos, yPos);
		int l = (int)strlen(st);
		for (int i = 0; i < l; i++)
		{
			glutBitmapCharacter(font, st[i]); // Print a character on the screen
		}
	}

	const CController &GetController(const int pad )
	{
		return CSimpleControllers::GetInstance().GetController(pad);
	}

	bool IsKeyPressed(const App::Key key)
	{
		//ASCII keys with on symbol (space, delete, backspace)
		#define HANDLE_ASCII_SPECIAL_KEY(KEYCODE, KEY) \
			case KEYCODE:\
				return Internal::IsKeyPressed(KEY);\
				break;

		//ASCII keys with muliple symbols (letters, numbers, etc)
		#define HANDLE_ASCII_KEY(KEYCODE, KEY, MODIFIED_KEY) \
			case KEYCODE: \
				return Internal::IsKeyPressed(KEY) || Internal::IsKeyPressed(MODIFIED_KEY); \
				break;

		//Special Keys with one symbol
		#define HANDLE_SPECIAL_KEY(KEYCODE, SPECIAL_KEY) \
			case KEYCODE: \
				return Internal::IsSpecialKeyPressed(SPECIAL_KEY); \
				break;
		
		switch(key)
		{
		//Keyboard keys
			HANDLE_ASCII_KEY(KEY_A, 'a', 'A')
			HANDLE_ASCII_KEY(KEY_B, 'b', 'B')
			HANDLE_ASCII_KEY(KEY_C, 'c', 'C')
			HANDLE_ASCII_KEY(KEY_D, 'd', 'D')
			HANDLE_ASCII_KEY(KEY_E, 'e', 'E')
			HANDLE_ASCII_KEY(KEY_F, 'f', 'F')
			HANDLE_ASCII_KEY(KEY_G, 'g', 'G')
			HANDLE_ASCII_KEY(KEY_H, 'h', 'H')
			HANDLE_ASCII_KEY(KEY_I, 'i', 'I')
			HANDLE_ASCII_KEY(KEY_J, 'j', 'J')
			HANDLE_ASCII_KEY(KEY_K, 'k', 'K')
			HANDLE_ASCII_KEY(KEY_L, 'l', 'L')
			HANDLE_ASCII_KEY(KEY_M, 'm', 'M')
			HANDLE_ASCII_KEY(KEY_N, 'n', 'N')
			HANDLE_ASCII_KEY(KEY_O, 'o', 'O')
			HANDLE_ASCII_KEY(KEY_P, 'p', 'P')
			HANDLE_ASCII_KEY(KEY_Q, 'q', 'Q')
			HANDLE_ASCII_KEY(KEY_R, 'r', 'R')
			HANDLE_ASCII_KEY(KEY_S, 's', 'S')
			HANDLE_ASCII_KEY(KEY_T, 't', 'T')
			HANDLE_ASCII_KEY(KEY_U, 'u', 'U')
			HANDLE_ASCII_KEY(KEY_V, 'v', 'V')
			HANDLE_ASCII_KEY(KEY_W, 'w', 'W')
			HANDLE_ASCII_KEY(KEY_X, 'x', 'X')
			HANDLE_ASCII_KEY(KEY_Y, 'y', 'Y')
			HANDLE_ASCII_KEY(KEY_Z, 'z', 'Z')

		//Number keys
			HANDLE_ASCII_KEY(KEY_1, '1', '!')
			HANDLE_ASCII_KEY(KEY_2, '2', '@')
			HANDLE_ASCII_KEY(KEY_3, '3', '#')
			HANDLE_ASCII_KEY(KEY_4, '4', '$')
			HANDLE_ASCII_KEY(KEY_5, '5', '%')
			HANDLE_ASCII_KEY(KEY_6, '6', '^')
			HANDLE_ASCII_KEY(KEY_7, '7', '&')
			HANDLE_ASCII_KEY(KEY_8, '8', '*')
			HANDLE_ASCII_KEY(KEY_9, '9', '(')
			HANDLE_ASCII_KEY(KEY_0, '0', ')')

		//Special Keys
			HANDLE_ASCII_SPECIAL_KEY(KEY_SPACE, ' ')
			HANDLE_ASCII_SPECIAL_KEY(KEY_ESC, 27)
			HANDLE_ASCII_SPECIAL_KEY(KEY_ENTER, '\r')
			HANDLE_ASCII_SPECIAL_KEY(KEY_TAB, '\t')

			HANDLE_SPECIAL_KEY(KEY_LEFT, GLUT_KEY_LEFT)
			HANDLE_SPECIAL_KEY(KEY_RIGHT, GLUT_KEY_RIGHT)
			HANDLE_SPECIAL_KEY(KEY_UP, GLUT_KEY_UP)
			HANDLE_SPECIAL_KEY(KEY_DOWN, GLUT_KEY_DOWN)

			HANDLE_SPECIAL_KEY(KEY_HOME, GLUT_KEY_HOME)
			HANDLE_SPECIAL_KEY(KEY_END, GLUT_KEY_END)
			HANDLE_SPECIAL_KEY(KEY_INSERT, GLUT_KEY_INSERT)

			default:
			return false;
		}

		//Unhandled key
		return false;
	}
}