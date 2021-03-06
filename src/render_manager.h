#pragma once

#include "game_camera.h"
#include "game_math.h"
#include "sprite_renderer.h"
#include "text_renderer.h"

class RenderManager{
private:
	static RenderManager* instance;

	TextRenderer* txtrdr;
	vec4 viewport = vec4(0, 0, 0, 0);
	vec4 clearColor = vec4(0, 0, 0, 1);

	RenderManager();
	void initialize();

public:

	static const unsigned int COLOR_BUFFER;
	static const unsigned int TRIANGLES;
	static RenderManager* getInstance();

	~RenderManager();
	void shutdown();
	void setViewport(int x, int y, int w, int h);
	void setClearColor(float r, float g, float b, float a);
	void clear(int field);
	void enable(int field);

	TextRenderer* getTextRendererInstance();
};
