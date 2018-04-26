#pragma once

#include "game_camera.h"
#include "game_math.h"

class SpriteRenderer{
private:
	static SpriteRenderer* instance;

	unsigned int vao;
	unsigned int vbo;
	unsigned int shader;
	unsigned int positionID;
	unsigned int mvpID;
	unsigned int spriteTexture;

	SpriteRenderer();
	void initialize();
public:
	static SpriteRenderer* getInstance();

	~SpriteRenderer();
	void prepare();
	void shutdown();
	void render(Camera2D cam);
};
