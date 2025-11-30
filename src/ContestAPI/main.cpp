///////////////////////////////////////////////////////////////////////////////
// Filename: Main.cpp
///////////////////////////////////////////////////////////////////////////////

#if BUILD_PLATFORM_WINDOWS
#include <windows.h>  // for MS Windows
#endif

#if BUILD_PLATFORM_APPLE
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_gamepad.h"
#endif

//---------------------------------------------------------------------------------
#include <cstdio>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <list>
//---------------------------------------------------------------------------------
#include "app.h"
#include "SimpleSound.h"
#include "SimpleController.h"

//---------------------------------------------------------------------------------
// User implemented methods.
//---------------------------------------------------------------------------------
extern void Init();
extern void Update(const float deltaTime);
extern void Render();
extern void Shutdown();

//---------------------------------------------------------------------------------
// Platform-specific functions
//---------------------------------------------------------------------------------
void StartCounter();
double GetCounter();

//---------------------------------------------------------------------------------
// Initial setup globals.
//---------------------------------------------------------------------------------
int WINDOW_WIDTH = APP_INIT_WINDOW_WIDTH;
int WINDOW_HEIGHT = APP_INIT_WINDOW_HEIGHT;

#if BUILD_PLATFORM_WINDOWS
HWND MAIN_WINDOW_HANDLE = nullptr;
#endif

//---------------------------------------------------------------------------------
static const double UPDATE_MAX = ((1.0 / APP_MAX_FRAME_RATE)*1000.0);
double gLastTime = 0;


class CProfiler
{
public:
	CProfiler() : m_startTime(0), m_elapsedTime(0)
	{		
	}
	void Start()
	{
		m_startTime = GetCounter();
	}
	double Stop()
	{ 
		m_elapsedTime = GetCounter() - m_startTime;
		return m_elapsedTime;
	}
	void Print(float x, float y, const char *text)
	{
		char textBuffer[64];
		snprintf(textBuffer, sizeof(textBuffer), "%s: %0.4f ms", text,m_elapsedTime);
		App::Print(x, y, textBuffer,1.0f,0.0f,1.0f, GLUT_BITMAP_HELVETICA_10);
	}
private:	
	double m_startTime;
	double m_elapsedTime;
};

CProfiler	gUserRenderProfiler;
CProfiler	gUserUpdateProfiler;
CProfiler	gUpdateDeltaTime;
bool		gRenderUpdateTimes = APP_RENDER_UPDATE_TIMES;

/* Initialize OpenGL Graphics */
void InitGL()
{
	StartCounter();
	gLastTime = GetCounter();
	// Set "clearing" or background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

//---------------------------------------------------------------------------------
// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted. */
//---------------------------------------------------------------------------------
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

	gUserRenderProfiler.Start();	
	Render();						// Call user defined render.
	gUserRenderProfiler.Stop();
	if (gRenderUpdateTimes)
	{
		gUpdateDeltaTime.Print	 (10, 40, "Update");
		gUserRenderProfiler.Print(10, 25, "User Render");
		gUserUpdateProfiler.Print(10, 10, "User Update");
	}
	glFlush();  // Render now						 
}

//---------------------------------------------------------------------------------
// Update from glut. Called when no more event handling.
//---------------------------------------------------------------------------------
void Idle()
{	
	static double prevTime = GetCounter();
	double tick = GetCounter() - prevTime;
	double currentTime = GetCounter();
	double deltaTime = currentTime - gLastTime;
	// Update.
	if (deltaTime > UPDATE_MAX)
	{	
		gUpdateDeltaTime.Stop();
		glutPostRedisplay(); //every time you are done
		CSimpleControllers::GetInstance().Update();

		gUserUpdateProfiler.Start();
		Update((float)deltaTime);				// Call user defined update.
		gUserUpdateProfiler.Stop();
		
		WINDOW_WIDTH = glutGet(GLUT_WINDOW_WIDTH);
		WINDOW_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);

		gLastTime = currentTime;

#if BUILD_PLATFORM_WINDOWS

		if (App::GetController().CheckButton(APP_ENABLE_DEBUG_INFO_BUTTON) )
		{
			gRenderUpdateTimes = !gRenderUpdateTimes;
		}

		if (App::IsKeyPressed(APP_QUIT_KEY))
		{		
			glutLeaveMainLoop();
		}
#endif //BUILD_PLATFORM_WINDOWS
		gUpdateDeltaTime.Start();
	}
}


//---------------------------------------------------------------------------------
// GLUT Mouse function callbacks
//---------------------------------------------------------------------------------

int gMouseButtonState[3] = { GLUT_UP };
int gMouseX = 0, gMouseY = 0;

void GlutMouse(int button, int state, int x,int y)
{
	//Button is one of GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON. 
	//State is either GLUT_UP or GLUT_DOWN
	gMouseButtonState[button] = state;
}

void GlutMouseMotion(int x, int y)
{
	gMouseX = x;
	gMouseY = y;
}

//---------------------------------------------------------------------------------
// GLUT keyboard callbacks
//---------------------------------------------------------------------------------

constexpr int KEY_UP = 0;
constexpr int KEY_DOWN = 1;

int gKeyboardState[256] = {0};

void GlutKeyboardDown(unsigned char key, int x, int y)
{
	gKeyboardState[key] = KEY_DOWN;
}

void GlutKeyboardUp(unsigned char key, int x, int y)
{
	gKeyboardState[key] = KEY_UP;
}

int gSpecialKeyboardState[256] = {0};

void GlutSpecialKeyboardDown(int key, int x, int y)
{
	gSpecialKeyboardState[key] = KEY_DOWN;
}

void GlutSpecialKeyboardUp(int key, int x, int y)
{
	gSpecialKeyboardState[key] = KEY_UP;
}

//---------------------------------------------------------------------------------
// Internal functions for making app interface easy to implement
// Have to split keys & special keys because GLUT has 2 different APIs
//---------------------------------------------------------------------------------
namespace Internal
{

	bool IsKeyPressed(int key)
	{
		return gKeyboardState[key] == KEY_DOWN;
	}

	bool IsSpecialKeyPressed(int key)
	{
		return gSpecialKeyboardState[key] == KEY_DOWN;
	}

	void GetMousePos(float& x, float& y)
	{
		x = (float) gMouseX;
		y = (float) gMouseY;
	}

	bool IsMousePressed(int button)
	{
		return gMouseButtonState[button] == GLUT_DOWN;
	}

}

int SetupGlutAndCreateWindow(int argc, char** argv)
{
	// Setup glut.
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	return glutCreateWindow(APP_WINDOW_TITLE);	
}

void ConfigureGlutAndRunMainLoop()
{

	glutIdleFunc(Idle);
	glutDisplayFunc(Display);       // Register callback handler for window re-paint event	
	
	glutMouseFunc(GlutMouse); //Mouse clicks
	glutMotionFunc(GlutMouseMotion); //Mouse moving while clicked
	glutPassiveMotionFunc(GlutMouseMotion); //Mouse moving while NOT clicked

	glutKeyboardFunc(GlutKeyboardDown);
	glutKeyboardUpFunc(GlutKeyboardUp);

	glutSpecialFunc(GlutSpecialKeyboardDown);
	glutSpecialUpFunc(GlutSpecialKeyboardUp);

#if BUILD_PLATFORM_WINDOWS
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
#endif

	InitGL();                       // Our own OpenGL initialization

	// Init sounds system.
	CSimpleSound::GetInstance().Initialize();
	
	// Call user defined init.
	Init();

	// Enter glut the event-processing loop				
	glutMainLoop();
	
	// Call user shutdown.
	Shutdown();	

	// Shutdown sound system.
	CSimpleSound::GetInstance().Shutdown();
}

//---------------------------------------------------------------------------------
#if BUILD_PLATFORM_WINDOWS

//---------------------------------------------------------------------------------
// Internal globals for timing.
double gPCFreq = 0.0;
__int64 gCounterStart = 0;


//---------------------------------------------------------------------------------
void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
	{
		printf("Failed to init performance counters.");
	}
	gPCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	gCounterStart = li.QuadPart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return (double(li.QuadPart - gCounterStart) / gPCFreq);
}

// Break here and use the diagnostics debug view to check for user mem leaks.
void CheckMemCallback()
{
}


//---------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 	_In_opt_ HINSTANCE hPrevInstance,	_In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{	
	int argc = 0;	char* argv = "";

	// Exit handler to check memory on exit.
	const int result_1 = std::atexit(CheckMemCallback);

	int glutWind = SetupGlutAndCreateWindow(argc, &argv);	

	HDC dc = wglGetCurrentDC();
	MAIN_WINDOW_HANDLE = WindowFromDC(dc);
	
	ConfigureGlutAndRunMainLoop();

	// And we are done.
	return 0;
}

#elif BUILD_PLATFORM_APPLE

// Internal globals for timing.
std::chrono::nanoseconds gCounterStart;

void StartCounter()
{
	gCounterStart = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}

double GetCounter()
{
	std::chrono::nanoseconds now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	
	return (double) std::chrono::duration_cast<std::chrono::milliseconds>(now - gCounterStart).count();
}

int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_GAMEPAD);
	//Load custom game controller mappings for SDL. Allows setting up correct axes, buttons and inversions
	SDL_AddGamepadMappingsFromFile("./data/ContestAPIConfig/gamecontrollermappings.txt");

	int glutWind = SetupGlutAndCreateWindow(argc, argv);

	ConfigureGlutAndRunMainLoop();

	return 0;
}

#endif //BUILD_PLATFORM_WINDOWS

