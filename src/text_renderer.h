#pragma once

#include <map>

#include "game_math.h"

class TextRenderer{
private:
	struct Character {
			unsigned int TextureID;   // ID handle of the glyph texture
			vec2 Size;    // Size of glyph
			vec2 Bearing;  // Offset from baseline to left/top of glyph
			long Advance;    // Horizontal offset to advance to next glyph
	};

	static TextRenderer* instance;

	unsigned int textTexture, textShader, textVao, textVbo, projMatID, colorID;
	vec4 textColor = vec4(0, 0, 0, 1);
	mat4 textProjMat = mat4(1);
	std::map<char, Character> Characters;

	TextRenderer();
	void initialize();

public:
	~TextRenderer();
	static TextRenderer* getInstance();
	void shutdown();
	void renderText(const char* text, float x, float y, float scale);
	void setFont(unsigned int font);
	void deleteFont(unsigned int font);
	void prepare();
	void setProjection(float left, float right, float bottom, float top);
	void setColor(float r, float g, float b, float a);
	unsigned int loadFont(unsigned char* fontFile);

};
