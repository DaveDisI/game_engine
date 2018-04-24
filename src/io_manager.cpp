#include "io_manager.h"

IOManager* IOManager::instance;

SDL_Window* currentWindow;

bool IOManager::QUIT = false;

struct WindowTag {
	unsigned int window;
	SDL_GLContext context;
};

std::vector<WindowTag> windows;

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

SDL_GameController* IOManager::controller1;
SDL_GameController* IOManager::controller2;


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
				controller1 = SDL_GameControllerOpen(i);
			}
			else if (controller2 == NULL) {
				controller2 = SDL_GameControllerOpen(i);
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
	SDL_GL_SwapWindow(currentWindow);
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
			currentWindow = SDL_GetWindowFromID(win);
			SDL_GL_MakeCurrent(currentWindow, windows[i].context);
			break;
		}
	}

}

void IOManager::setWindowDimensions(int w, int h) {
	SDL_SetWindowSize(currentWindow, w, h);
}

void IOManager::setWindowPosition(int x, int y) {
	SDL_SetWindowPosition(currentWindow, x, y);
}

void IOManager::setWindowFullScreen(bool desktopMode) {
	if (desktopMode) {
		SDL_SetWindowFullscreen(currentWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else {
		SDL_SetWindowFullscreen(currentWindow, SDL_WINDOW_FULLSCREEN);
	}
}

void IOManager::setWindowVSync(bool vSyncEnabled) {
	SDL_GL_SetSwapInterval(vSyncEnabled);
}

void IOManager::setWindowResizeable(bool isResizeable) {
	SDL_SetWindowResizable(currentWindow, (SDL_bool)isResizeable);
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
	SDL_ShowSimpleMessageBox(flags, title, message, currentWindow);
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
		currentWindow = window;
	}

	return SDL_GetWindowID(window);
}

int IOManager::getWindowPositionX() {
	int x, y;
	SDL_GetWindowPosition(currentWindow, &x, &y);
	return x;
}

int IOManager::getWindowPositionY() {
	int x, y;
	SDL_GetWindowPosition(currentWindow, &x, &y);
	return y;
}

int IOManager::getWindowWidth() {
	int w, h;
	SDL_GetWindowSize(currentWindow, &w, &h);
	return w;
}

int IOManager::getWindowHeight() {
	int w, h;
	SDL_GetWindowSize(currentWindow, &w, &h);
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
