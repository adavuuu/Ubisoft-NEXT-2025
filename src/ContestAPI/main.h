//-----------------------------------------------------------------------------
// Main.h
//-----------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

#if BUILD_PLATFORM_WINDOWS

#include <Windows.h>

extern HWND MAIN_WINDOW_HANDLE;

#endif //BUILD_PLATFORM_WINDOWS

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

namespace Internal
{

    //Checks if ascii key is pressed
    bool IsKeyPressed(int key);

    //Checks if special key is pressed
    bool IsSpecialKeyPressed(int specialKey);

    void GetMousePos(float& x, float& y);

    bool IsMousePressed(int button);

}

#endif