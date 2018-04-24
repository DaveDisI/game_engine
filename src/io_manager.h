#pragma once

#include <stdio.h>
#include <vector>

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
	struct WindowTag {
		unsigned int window;
		void* context;
	};
	static IOManager* instance;
	std::vector<WindowTag> windows;
	void* currentWindow;
	static void* controller1;
	static void* controller2;
	IOManager();

public:
	static bool QUIT;

	static const int ESC_KEY;
	static const int ENTER_KEY;
	static const int UP_KEY;
	static const int DOWN_KEY;
	static const int LEFT_KEY;
	static const int RIGHT_KEY;
	static const int LEFT_SHIFT_KEY;
	static const int SPACE_KEY;
	static const int F1_KEY;
	static const int F2_KEY;
	static const int F3_KEY;
	static const int F4_KEY;
	static const int F5_KEY;
	static const int F6_KEY;
	static const int F7_KEY;
	static const int F8_KEY;
	static const int F9_KEY;
	static const int F10_KEY;
	static const int F11_KEY;
	static const int F12_KEY;
	static const int NUM_0_KEY;
	static const int NUM_1_KEY;
	static const int NUM_2_KEY;
	static const int NUM_3_KEY;
	static const int NUM_4_KEY;
	static const int NUM_5_KEY;
	static const int NUM_6_KEY;
	static const int NUM_7_KEY;
	static const int NUM_8_KEY;
	static const int NUM_9_KEY;
	static const int A_KEY;
	static const int D_KEY;
	static const int E_KEY;
	static const int F_KEY;
	static const int Q_KEY;
	static const int R_KEY;
	static const int S_KEY;
	static const int W_KEY;
	static const int LEFT_MOUSE_BUTTON;
	static const int RIGHT_MOUSE_BUTTON;
	static const int MIDDLE_MOUSE_BUTTON;
	static const int CONTROLLER_A_BUTTON;
	static const int CONTROLLER_B_BUTTON;
	static const int CONTROLLER_Y_BUTTON;
	static const int CONTROLLER_X_BUTTON;
	static const int CONTROLLER_DOWN_BUTTON;
	static const int CONTROLLER_LEFT_BUTTON;
	static const int CONTROLLER_RIGHT_BUTTON;
	static const int CONTROLLER_UP_BUTTON;
	static const int CONTROLLER_BACK_BUTTON;
	static const int CONTROLLER_START_BUTTON;
	static const int CONTROLLER_LEFT_STICK_BUTTON;
	static const int CONTROLLER_RIGHT_STICK_BUTTON;
	static const int CONTROLLER_LEFT_BUMPER_BUTTON;
	static const int CONTROLLER_RIGHT_BUMPER_BUTTON;
	static const int CONTROLLER_LEFT_X_AXIS;
	static const int CONTROLLER_LEFT_Y_AXIS;
	static const int CONTROLLER_RIGHT_X_AXIS;
	static const int CONTROLLER_RIGHT_Y_AXIS;
	static const int CONTROLLER_LEFT_TRIGGER;
	static const int CONTROLLER_RIGHT_TRIGGER;

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
