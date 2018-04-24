#include "text_renderer.h"
#include <GL/glew.h>

#include <map>
#include <string>

#include "io_manager.h"
#include "game_math.h"
#include "shader_compiler.h"

#include "ft2build.h"
#include FT_FREETYPE_H

TextRenderer* TextRenderer::instance = nullptr;

const GLchar* textvs = "#version 330 core\n"
    "layout (location = 0) in vec4 position;"
    "uniform mat4 mvpMatrix;"
    "out vec2 Texcoord;"
    "void main()"
    "{"
    "    Texcoord = position.zw;"
    "    gl_Position = mvpMatrix * vec4(position.xy, 0.0, 1.0);"
    "}";
const GLchar* textfs = "#version 330 core\n"
    "in vec2 Texcoord;"
    "out vec4 outColor;"
    "uniform vec4 textColor;"
    "uniform sampler2D text;"
    "void main()"
    "{"
    "	 vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, Texcoord).r);"
    "    outColor = textColor * sampled;"
    "}";

FT_Library  library;
FT_Face face;

GLuint textTexture;

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    vec2 Size;    // Size of glyph
    vec2 Bearing;  // Offset from baseline to left/top of glyph
    long Advance;    // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
GLuint textShader, textVao, textVbo, projMatID, colorID;
vec4 textColor = vec4(0, 0, 0, 1);
mat4 textProjMat = mat4(1);

TextRenderer::~TextRenderer(){

}

TextRenderer* TextRenderer::getInstance(){
	if(!instance){
		instance = new TextRenderer();
	}

	return instance;
}
int ctr = 0;
void TextRenderer::shutdown(){
	if(instance){
		glDeleteVertexArrays(1, &textVao);
		glDeleteBuffers(1, &textVbo);
		glDeleteTextures(1, &textTexture);
		glDeleteProgram(textShader);
		Characters.clear();

		delete instance;
		instance = nullptr;
	}
}

TextRenderer::TextRenderer(){
	initialize();
}

void TextRenderer::initialize(){
	textShader = compileShaderVF(textvs, textfs);
	glUseProgram(textShader);
	projMatID = glGetUniformLocation(textShader, "mvpMatrix");
	colorID = glGetUniformLocation(textShader, "textColor");
	glUniform4fv(colorID, 1, &textColor.v[0]);

	if (FT_Init_FreeType( &library )){
		IOManager::getInstance()->displayMessageBox("FREE FONT ERROR", "Error initializing freetype", 0);
		std::cout << "ERROR INITIALIZING FREETYPE\n";
	}

	if(FT_New_Face(library, "./res/fonts/SFCompactDisplay-Medium.otf", 0, &face)){
		IOManager::getInstance()->displayMessageBox("FREE FONT ERROR", "Error loading free font face", 0);
		std::cout << "ERROR LOADING FONT FILE\n";
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture

        glGenTextures(1, &textTexture);
        glBindTexture(GL_TEXTURE_2D, textTexture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            textTexture,
            vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(library);


    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &textVao);
    glGenBuffers(1, &textVbo);
    glBindVertexArray(textVao);
    glBindBuffer(GL_ARRAY_BUFFER, textVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
}

void TextRenderer::renderText(const char* text, float x, float y, float scale)
{
    glActiveTexture(GL_TEXTURE0);

	std::string txt(text);
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = txt.begin(); c != txt.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.v[0] * scale;
        GLfloat ypos = y - (ch.Size.v[1] - ch.Bearing.v[1]) * scale;

        GLfloat w = ch.Size.v[0] * scale;
        GLfloat h = ch.Size.v[1] * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, textVbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
}

void TextRenderer::setFont(unsigned int font){

}

void TextRenderer::deleteFont(unsigned int font){

}

void TextRenderer::prepare(){
	glUseProgram(textShader);
	glBindVertexArray(textVao);
	glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TextRenderer::setProjection(float left, float right, float bottom, float top){
  setOrthographicProjection(textProjMat, left, right, bottom, top);
  glUseProgram(textShader);
  glUniformMatrix4fv(projMatID, 1, GL_FALSE, &textProjMat.v[0][0]);
}

void TextRenderer::setColor(float r, float g, float b, float a){
	textColor = vec4(r, g, b, a);
	glUseProgram(textShader);
	glUniform4f(colorID, r, g, b, a);
}

unsigned int TextRenderer::loadFont(unsigned char* fontFile){
	return 0;
}
