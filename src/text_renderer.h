#pragma once

class TextRenderer{
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


private:
	static TextRenderer* instance;

	TextRenderer();
	void initialize();
};
