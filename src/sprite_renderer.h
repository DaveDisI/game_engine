#pragma once

#include <vector>

#include <GL/glew.h>

#include "math_util.h"
#include "render_camera.h"

using namespace std;

struct SpriteTextureData {
	unsigned short textureId = 0;
	float width = 0;
	float height = 0;
};

struct Sprite {
	int indexId = -1;
	unsigned int* textureId = nullptr;
	float rotation = 0;
	vec2 position = vec2(0, 0);
	vec2 scale = vec2(1, 1);
};

struct AnimatedSprite {
	unsigned int currentFrame = 0;
	unsigned int previousFrame = 0;
	unsigned int totalFrames = 0;
	float frameElapsedTime = 0;
	Sprite* sprite = nullptr;
	vector<SpriteTextureData> images;
	vector<float> durations;
	
	unsigned int addKeyframe(SpriteTextureData image, float duration){
		images.push_back(image);
		durations.push_back(duration);
		totalFrames++;
	}
};

class SpriteRenderer{
public:
	static SpriteRenderer* getInstance(); 
	~SpriteRenderer();
	
	void shutdown();
	void render(Camera2D cam);
	void loadTextureData(SpriteTextureData* texDat, unsigned char* data, int w, int h);
	void assignTextureToSprite(SpriteTextureData& texDat, Sprite* spt);
	void deleteTextureData(SpriteTextureData& texDat);
	void deleteSprite(Sprite* spt);
	void updateSprite(Sprite* spt);
	void updateAnimatedSprite(AnimatedSprite* aspt, float delta);
	void setSpriteColor(Sprite* spt, vec4 rgba);
	void initializeAnimatedSprite(AnimatedSprite* anispt);
	Sprite* createSprite();
	Sprite* createSprite(SpriteTextureData& texDat);
	Sprite* createSprite(vec4 rgba);
	Sprite* createSprite(SpriteTextureData& texDat, vec4 rgba);
	
private:
	static SpriteRenderer* instance;

	static const unsigned int MAX_SPRITES = 1024;
	static const unsigned int MAX_TEXTURES = 256;
	static const unsigned int MAX_TEXTURE_SIZE = 1024;
	static const unsigned int MAX_TEXTURE_DEPTH = 256;

	unsigned int totalSpriteCount;
	unsigned int totalTextures;

	GLuint spriteShader;
	GLuint mvpMatId, spriteColorId, textureDataId;
	GLuint spriteVao, spriteVbo, spriteEbo;
	GLuint textureArray;
	
	SpriteTextureData defaultTextureData;

	vector<unsigned short> textureIds;
	vector<unsigned short> freeTextures;
	vector<unsigned short> freeSprites;
	vector<float> textureWidths;
	vector<float> textureHeights;
	vector<vec4> spriteColors;
	vector<mat4> modelMatrices;
	vector<Sprite> sprites;	
	
	void initialize();
	SpriteRenderer();
};


