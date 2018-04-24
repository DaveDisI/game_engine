#pragma once

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>

class IOManager {
public:
	static IOManager* getInstance();
	
	bool initialize();
	void initGameControllers();
	void processEvents();
	void swapWindowBuffer();
	void shutdown();
	void stabilizeControllerAxes(float threshHold);
	void makeWindowCurrent(unsigned int win);
	void setWindowDimensions(int w, int h);
	void setWindowPosition(int x, int y);
	void setWindowFullScreen(bool desktopMode);
	void setWindowVSync(bool vSyncEnabled);
	void setWindowResizeable(bool isResizeable);
	void deleteWindow(unsigned int win);
	void delay(unsigned int t);
	void displayMessageBox(const char* title, const char* message, unsigned int flags);
	bool isWindowVSyncEnabled();
	int getWindowPositionX();
	int getWindowPositionY();
	int getWindowWidth();
	int getWindowHeight();
	int getMonitorWidth(int monitor);
	int getMonitorHeight(int monitor);
	unsigned int createWindow(const char* title, int locX, int locY, int width, int height);
	long getTime();
	
private:
	static IOManager* instance;
	static SDL_GameController* controller1;
	static SDL_GameController* controller2;
	IOManager();

public:
	static bool QUIT;

	static const int ESC_KEY = SDL_SCANCODE_ESCAPE;
	static const int ENTER_KEY = SDL_SCANCODE_RETURN;

	static const int UP_KEY = SDL_SCANCODE_UP;
	static const int DOWN_KEY = SDL_SCANCODE_DOWN;
	static const int LEFT_KEY = SDL_SCANCODE_LEFT;
	static const int RIGHT_KEY = SDL_SCANCODE_RIGHT;

	static const int LEFT_SHIFT_KEY = SDL_SCANCODE_LSHIFT;

	static const int SPACE_KEY = SDL_SCANCODE_SPACE;

	static const int F1_KEY = SDL_SCANCODE_F1;
	static const int F2_KEY = SDL_SCANCODE_F2;
	static const int F3_KEY = SDL_SCANCODE_F3;
	static const int F4_KEY = SDL_SCANCODE_F4;
	static const int F5_KEY = SDL_SCANCODE_F5;
	static const int F6_KEY = SDL_SCANCODE_F6;
	static const int F7_KEY = SDL_SCANCODE_F7;
	static const int F8_KEY = SDL_SCANCODE_F8;
	static const int F9_KEY = SDL_SCANCODE_F9;
	static const int F10_KEY = SDL_SCANCODE_F10;
	static const int F11_KEY = SDL_SCANCODE_F11;
	static const int F12_KEY = SDL_SCANCODE_F12;

	static const int NUM_0_KEY = SDL_SCANCODE_0;
	static const int NUM_1_KEY = SDL_SCANCODE_1;
	static const int NUM_2_KEY = SDL_SCANCODE_2;
	static const int NUM_3_KEY = SDL_SCANCODE_3;
	static const int NUM_4_KEY = SDL_SCANCODE_4;
	static const int NUM_5_KEY = SDL_SCANCODE_5;
	static const int NUM_6_KEY = SDL_SCANCODE_6;
	static const int NUM_7_KEY = SDL_SCANCODE_7;
	static const int NUM_8_KEY = SDL_SCANCODE_8;
	static const int NUM_9_KEY = SDL_SCANCODE_9;

	static const int A_KEY = SDL_SCANCODE_A;
	static const int D_KEY = SDL_SCANCODE_D;
	static const int E_KEY = SDL_SCANCODE_E;
	static const int F_KEY = SDL_SCANCODE_F;
	static const int Q_KEY = SDL_SCANCODE_Q;
	static const int R_KEY = SDL_SCANCODE_R;
	static const int S_KEY = SDL_SCANCODE_S;
	static const int W_KEY = SDL_SCANCODE_W;

	static const int LEFT_MOUSE_BUTTON = SDL_BUTTON_LEFT;
	static const int RIGHT_MOUSE_BUTTON = SDL_BUTTON_RIGHT;
	static const int MIDDLE_MOUSE_BUTTON = SDL_BUTTON_MIDDLE;

	static const int CONTROLLER_A_BUTTON = SDL_CONTROLLER_BUTTON_A;
	static const int CONTROLLER_B_BUTTON = SDL_CONTROLLER_BUTTON_B;
	static const int CONTROLLER_Y_BUTTON = SDL_CONTROLLER_BUTTON_Y;
	static const int CONTROLLER_X_BUTTON = SDL_CONTROLLER_BUTTON_X;
	static const int CONTROLLER_DOWN_BUTTON = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
	static const int CONTROLLER_LEFT_BUTTON = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
	static const int CONTROLLER_RIGHT_BUTTON = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
	static const int CONTROLLER_UP_BUTTON = SDL_CONTROLLER_BUTTON_DPAD_UP;
	static const int CONTROLLER_BACK_BUTTON = SDL_CONTROLLER_BUTTON_BACK;
	static const int CONTROLLER_START_BUTTON = SDL_CONTROLLER_BUTTON_START;
	static const int CONTROLLER_LEFT_STICK_BUTTON = SDL_CONTROLLER_BUTTON_LEFTSTICK;
	static const int CONTROLLER_RIGHT_STICK_BUTTON = SDL_CONTROLLER_BUTTON_RIGHTSTICK;
	static const int CONTROLLER_LEFT_BUMPER_BUTTON = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
	static const int CONTROLLER_RIGHT_BUMPER_BUTTON = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;

	static const int CONTROLLER_LEFT_X_AXIS = SDL_CONTROLLER_AXIS_LEFTX;
	static const int CONTROLLER_LEFT_Y_AXIS = SDL_CONTROLLER_AXIS_LEFTY;
	static const int CONTROLLER_RIGHT_X_AXIS = SDL_CONTROLLER_AXIS_RIGHTX;
	static const int CONTROLLER_RIGHT_Y_AXIS = SDL_CONTROLLER_AXIS_RIGHTY;
	static const int CONTROLLER_LEFT_TRIGGER = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
	static const int CONTROLLER_RIGHT_TRIGGER = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;

	static const int TOTAL_KEYS = 256;
	static const int TOTAL_MOUSE_BUTTONS = 8;
	static const int TOTAL_CONTROLLER_BUTTONS = 16;
	static const int TOTAL_CONTROLLER_AXES = 8;

	static bool keys[TOTAL_KEYS];
	static bool mouseButtons[TOTAL_MOUSE_BUTTONS];
	static bool controller1Buttons[TOTAL_CONTROLLER_BUTTONS];
	static bool controller2Buttons[TOTAL_CONTROLLER_BUTTONS];

	static float controller1Axes[TOTAL_CONTROLLER_AXES];
	static float controller2Axes[TOTAL_CONTROLLER_AXES];

	static int mouseCursorX;
	static int mouseCursorY;
	
};
