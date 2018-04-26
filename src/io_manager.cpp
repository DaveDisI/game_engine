#include "io_manager.h"

#include <stdio.h>
#include <SDL2/SDL.h>

IOManager* IOManager::instance;

bool IOManager::QUIT = false;
const int IOManager::ESC_KEY = SDL_SCANCODE_ESCAPE;
const int IOManager::ENTER_KEY = SDL_SCANCODE_RETURN;
const int IOManager::UP_KEY = SDL_SCANCODE_UP;
const int IOManager::DOWN_KEY = SDL_SCANCODE_DOWN;
const int IOManager::LEFT_KEY = SDL_SCANCODE_LEFT;
const int IOManager::RIGHT_KEY = SDL_SCANCODE_RIGHT;
const int IOManager::LEFT_SHIFT_KEY = SDL_SCANCODE_LSHIFT;
const int IOManager::SPACE_KEY = SDL_SCANCODE_SPACE;
const int IOManager::F1_KEY = SDL_SCANCODE_F1;
const int IOManager::F2_KEY = SDL_SCANCODE_F2;
const int IOManager::F3_KEY = SDL_SCANCODE_F3;
const int IOManager::F4_KEY = SDL_SCANCODE_F4;
const int IOManager::F5_KEY = SDL_SCANCODE_F5;
const int IOManager::F6_KEY = SDL_SCANCODE_F6;
const int IOManager::F7_KEY = SDL_SCANCODE_F7;
const int IOManager::F8_KEY = SDL_SCANCODE_F8;
const int IOManager::F9_KEY = SDL_SCANCODE_F9;
const int IOManager::F10_KEY = SDL_SCANCODE_F10;
const int IOManager::F11_KEY = SDL_SCANCODE_F11;
const int IOManager::F12_KEY = SDL_SCANCODE_F12;
const int IOManager::NUM_0_KEY = SDL_SCANCODE_0;
const int IOManager::NUM_1_KEY = SDL_SCANCODE_1;
const int IOManager::NUM_2_KEY = SDL_SCANCODE_2;
const int IOManager::NUM_3_KEY = SDL_SCANCODE_3;
const int IOManager::NUM_4_KEY = SDL_SCANCODE_4;
const int IOManager::NUM_5_KEY = SDL_SCANCODE_5;
const int IOManager::NUM_6_KEY = SDL_SCANCODE_6;
const int IOManager::NUM_7_KEY = SDL_SCANCODE_7;
const int IOManager::NUM_8_KEY = SDL_SCANCODE_8;
const int IOManager::NUM_9_KEY = SDL_SCANCODE_9;
const int IOManager::A_KEY = SDL_SCANCODE_A;
const int IOManager::D_KEY = SDL_SCANCODE_D;
const int IOManager::E_KEY = SDL_SCANCODE_E;
const int IOManager::F_KEY = SDL_SCANCODE_F;
const int IOManager::Q_KEY = SDL_SCANCODE_Q;
const int IOManager::R_KEY = SDL_SCANCODE_R;
const int IOManager::S_KEY = SDL_SCANCODE_S;
const int IOManager::W_KEY = SDL_SCANCODE_W;
const int IOManager::LEFT_MOUSE_BUTTON = SDL_BUTTON_LEFT;
const int IOManager::RIGHT_MOUSE_BUTTON = SDL_BUTTON_RIGHT;
const int IOManager::MIDDLE_MOUSE_BUTTON = SDL_BUTTON_MIDDLE;
const int IOManager::CONTROLLER_A_BUTTON = SDL_CONTROLLER_BUTTON_A;
const int IOManager::CONTROLLER_B_BUTTON = SDL_CONTROLLER_BUTTON_B;
const int IOManager::CONTROLLER_Y_BUTTON = SDL_CONTROLLER_BUTTON_Y;
const int IOManager::CONTROLLER_X_BUTTON = SDL_CONTROLLER_BUTTON_X;
const int IOManager::CONTROLLER_DOWN_BUTTON = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
const int IOManager::CONTROLLER_LEFT_BUTTON = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
const int IOManager::CONTROLLER_RIGHT_BUTTON = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
const int IOManager::CONTROLLER_UP_BUTTON = SDL_CONTROLLER_BUTTON_DPAD_UP;
const int IOManager::CONTROLLER_BACK_BUTTON = SDL_CONTROLLER_BUTTON_BACK;
const int IOManager::CONTROLLER_START_BUTTON = SDL_CONTROLLER_BUTTON_START;
const int IOManager::CONTROLLER_LEFT_STICK_BUTTON = SDL_CONTROLLER_BUTTON_LEFTSTICK;
const int IOManager::CONTROLLER_RIGHT_STICK_BUTTON = SDL_CONTROLLER_BUTTON_RIGHTSTICK;
const int IOManager::CONTROLLER_LEFT_BUMPER_BUTTON = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
const int IOManager::CONTROLLER_RIGHT_BUMPER_BUTTON = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
const int IOManager::CONTROLLER_LEFT_X_AXIS = SDL_CONTROLLER_AXIS_LEFTX;
const int IOManager::CONTROLLER_LEFT_Y_AXIS = SDL_CONTROLLER_AXIS_LEFTY;
const int IOManager::CONTROLLER_RIGHT_X_AXIS = SDL_CONTROLLER_AXIS_RIGHTX;
const int IOManager::CONTROLLER_RIGHT_Y_AXIS = SDL_CONTROLLER_AXIS_RIGHTY;
const int IOManager::CONTROLLER_LEFT_TRIGGER = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
const int IOManager::CONTROLLER_RIGHT_TRIGGER = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;

static const float AXIS_MIN = -32768.0f;
static const float AXIS_MAX = 32767.0f;

bool IOManager::keys[TOTAL_KEYS];
bool IOManager::mouseButtons[TOTAL_MOUSE_BUTTONS];
bool IOManager::controller1Buttons[TOTAL_CONTROLLER_BUTTONS];
bool IOManager::controller2Buttons[TOTAL_CONTROLLER_BUTTONS];
float IOManager::controller1Axes[TOTAL_CONTROLLER_AXES];
float IOManager::controller2Axes[TOTAL_CONTROLLER_AXES];
int IOManager::mouseCursorX;
int IOManager::mouseCursorY;

void* IOManager::controller1;
void* IOManager::controller2;


IOManager::IOManager() {
	initialize();
}

IOManager* IOManager::getInstance(){
	if (!instance) {
		instance = new IOManager();
	}
	return instance;
}

bool IOManager::initialize(){
	if(!AXIS_MAX && !AXIS_MIN){ printf(""); } //stupid warning suppressor

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	return true;
}

void IOManager::initGameControllers() {
	SDL_Init(SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			if (controller1 == NULL) {
				controller1 = (SDL_GameController*)SDL_GameControllerOpen(i);
			}
			else if (controller2 == NULL) {
				controller2 = (SDL_GameController*)SDL_GameControllerOpen(i);
			}
			else {
				break;
			}
		}
	}
}

void IOManager::processEvents() {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:{
				QUIT = true;
		}
		case SDL_KEYDOWN: {
			keys[e.key.keysym.scancode] = true;
			break;
		}
		case SDL_KEYUP: {
			keys[e.key.keysym.scancode] = false;
			break;
		}
		case SDL_MOUSEMOTION: {
			SDL_GetMouseState(&mouseCursorX, &mouseCursorY);
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			mouseButtons[e.button.button] = true;
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			mouseButtons[e.button.button] = false;
			break;
		}
		case SDL_CONTROLLERBUTTONDOWN: {
			if (e.cbutton.which == 0) {
				controller1Buttons[e.cbutton.button] = true;
			}
			else {
				controller2Buttons[e.cbutton.button] = true;
			}
			break;
		}
		case SDL_CONTROLLERBUTTONUP: {
			if (e.cbutton.which == 0) {
				controller1Buttons[e.cbutton.button] = false;
			}
			else {
				controller2Buttons[e.cbutton.button] = false;
			}
			break;
		}
		case SDL_CONTROLLERAXISMOTION: {
			if (e.cbutton.which == 0) {
				controller1Axes[e.caxis.axis] = e.caxis.value / AXIS_MAX;
			}
			else {
				controller2Axes[e.caxis.axis] = e.caxis.value / AXIS_MAX;
			}
			break;
		}
		}
	}
}

void IOManager::swapWindowBuffer() {
	SDL_GL_SwapWindow((SDL_Window*)currentWindow);
}

void IOManager::shutdown() {


	if (instance) {
		size_t sz = windows.size();

		for (unsigned int i = 0; i < sz; i++) {
			SDL_GL_DeleteContext(windows[i].context);
			SDL_DestroyWindow(SDL_GetWindowFromID(windows[i].window));
			windows.erase(windows.begin() + i);
		}

		SDL_Quit();

		delete instance;
		instance = nullptr;
	}


}

void IOManager::stabilizeControllerAxes(float threshHold) {
	if (controller1Axes[CONTROLLER_LEFT_X_AXIS] < threshHold && controller1Axes[CONTROLLER_LEFT_X_AXIS] > -threshHold) {
		controller1Axes[CONTROLLER_LEFT_X_AXIS] = 0.0;
	}
	if (controller1Axes[CONTROLLER_LEFT_Y_AXIS] < threshHold && controller1Axes[CONTROLLER_LEFT_Y_AXIS] > -threshHold) {
		controller1Axes[CONTROLLER_LEFT_Y_AXIS] = 0.0;
	}
	if (controller1Axes[CONTROLLER_RIGHT_X_AXIS] < threshHold && controller1Axes[CONTROLLER_RIGHT_X_AXIS] > -threshHold) {
		controller1Axes[CONTROLLER_RIGHT_X_AXIS] = 0.0;
	}
	if (controller1Axes[CONTROLLER_RIGHT_Y_AXIS] < threshHold && controller1Axes[CONTROLLER_RIGHT_Y_AXIS] > -threshHold) {
		controller1Axes[CONTROLLER_RIGHT_Y_AXIS] = 0.0;
	}
	if (controller2Axes[CONTROLLER_LEFT_X_AXIS] < threshHold && controller2Axes[CONTROLLER_LEFT_X_AXIS] > -threshHold) {
		controller2Axes[CONTROLLER_LEFT_X_AXIS] = 0.0;
	}
	if (controller2Axes[CONTROLLER_LEFT_Y_AXIS] < threshHold && controller2Axes[CONTROLLER_LEFT_Y_AXIS] > -threshHold) {
		controller2Axes[CONTROLLER_LEFT_Y_AXIS] = 0.0;
	}
	if (controller2Axes[CONTROLLER_RIGHT_X_AXIS] < threshHold && controller2Axes[CONTROLLER_RIGHT_X_AXIS] > -threshHold) {
		controller2Axes[CONTROLLER_RIGHT_X_AXIS] = 0.0;
	}
	if (controller2Axes[CONTROLLER_RIGHT_Y_AXIS] < threshHold && controller2Axes[CONTROLLER_RIGHT_Y_AXIS] > -threshHold) {
		controller2Axes[CONTROLLER_RIGHT_Y_AXIS] = 0.0;
	}
}

void IOManager::makeWindowCurrent(unsigned int win) {
	size_t sz = windows.size();
	for (unsigned int i = 0; i < sz; i++) {
		if (windows[i].window == win) {
			currentWindow = (SDL_Window*)SDL_GetWindowFromID(win);
			SDL_GL_MakeCurrent((SDL_Window*)currentWindow, windows[i].context);
			break;
		}
	}

}

void IOManager::setWindowDimensions(int w, int h) {
	SDL_SetWindowSize((SDL_Window*)currentWindow, w, h);
}

void IOManager::setWindowPosition(int x, int y) {
	SDL_SetWindowPosition((SDL_Window*)currentWindow, x, y);
}

void IOManager::setWindowFullScreen(bool desktopMode) {
	if (desktopMode) {
		SDL_SetWindowFullscreen((SDL_Window*)currentWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else {
		SDL_SetWindowFullscreen((SDL_Window*)currentWindow, SDL_WINDOW_FULLSCREEN);
	}
}

void IOManager::setWindowVSync(bool vSyncEnabled) {
	SDL_GL_SetSwapInterval(vSyncEnabled);
}

void IOManager::setWindowResizeable(bool isResizeable) {
	SDL_SetWindowResizable((SDL_Window*)currentWindow, (SDL_bool)isResizeable);
}

void IOManager::deleteWindow(unsigned int win) {
	size_t sz = windows.size();
	for (unsigned int i = 0; i < sz; i++) {
		if (windows[i].window == win) {
			SDL_GL_DeleteContext(windows[i].context);
			windows.erase(windows.begin() + i);
			break;
		}
	}

	SDL_DestroyWindow(SDL_GetWindowFromID(win));
}

void IOManager::delay(unsigned int t){
	SDL_Delay(t);
}

void IOManager::displayMessageBox(const char* title, const char* message, unsigned int flags){
	SDL_ShowSimpleMessageBox(flags, title, message, (SDL_Window*)currentWindow);
}

bool IOManager::isWindowVSyncEnabled() {
	return (bool)SDL_GL_GetSwapInterval();
}

unsigned int IOManager::createWindow(const char * title, int locX, int locY, int width, int height) {
	SDL_Window* window = SDL_CreateWindow(title, locX, locY, width, height, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	WindowTag wt = {
		SDL_GetWindowID(window),
		context
	};

	windows.push_back(wt);

	if (windows.size() == 1) {
		currentWindow = (SDL_Window*)window;
	}

	return SDL_GetWindowID(window);
}

int IOManager::getWindowPositionX() {
	int x, y;
	SDL_GetWindowPosition((SDL_Window*)currentWindow, &x, &y);
	return x;
}

int IOManager::getWindowPositionY() {
	int x, y;
	SDL_GetWindowPosition((SDL_Window*)currentWindow, &x, &y);
	return y;
}

int IOManager::getWindowWidth() {
	int w, h;
	SDL_GetWindowSize((SDL_Window*)currentWindow, &w, &h);
	return w;
}

int IOManager::getWindowHeight() {
	int w, h;
	SDL_GetWindowSize((SDL_Window*)currentWindow, &w, &h);
	return h;
}

int IOManager::getMonitorWidth(int monitor){
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(monitor, 0, &mode);
	return mode.w;
}

int IOManager::getMonitorHeight(int monitor){
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(monitor, 0, &mode);
	return mode.h;
}

long IOManager::getTime() {
	return SDL_GetTicks();
}
