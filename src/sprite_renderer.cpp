#include "sprite_renderer.h"

#include <GL/glew.h>

#include "shader_compiler.h"

SpriteRenderer* SpriteRenderer::instance = nullptr;

SpriteRenderer::SpriteRenderer(){
	initialize();
}

SpriteRenderer::~SpriteRenderer(){
	if(instance){
		shutdown();
	}
}

void SpriteRenderer::initialize(){
	const char vertexShader[] = "#version 410 core\n"
															"in vec4 position;"
															"out vec2 textureCoordinates;"
															"uniform mat4 mvpMatrix;"
															"void main(){"
															"	textureCoordinates = position.zw;"
															"	gl_Position = mvpMatrix * vec4(position.xy, 0, 1);"
															"}";

	const char fragmentShader[] = "#version 410 core\n"
															"out vec4 finalColor;"
															"in vec2 textureCoordinates;"
															"uniform sampler2D texImg;"
															"void main(){"
															"	finalColor = texture(texImg, textureCoordinates);"
															"}";

	shader = compileShaderVF(vertexShader, fragmentShader);
	positionID = glGetAttribLocation(shader, "position");
	mvpID = glGetUniformLocation(shader, "mvpMatrix");

	float verts[] = {
		-0.5, -0.5, 0.0, 1.0,
		-0.5,  0.5, 0.0, 0.0,
		 0.5,  0.5, 1.0, 0.0,
		 0.5, -0.5, 1.0, 1.0

	};
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(positionID, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(positionID);

	unsigned char tex[] = {
		255, 0, 255, 255, 0, 255, 0, 255,
		0, 255, 0, 255, 255, 0, 255, 255
	};

	glGenTextures(1, &spriteTexture);
	glBindTexture(GL_TEXTURE_2D, spriteTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void SpriteRenderer::render(Camera2D cam){
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &cam.projectionMatrix.v[0][0]);
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 1);
}

void SpriteRenderer::prepare(){
	glUseProgram(shader);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, spriteTexture);
}

void SpriteRenderer::shutdown(){
	if(instance){
		delete instance;
		instance = nullptr;
	}
}

SpriteRenderer* SpriteRenderer::getInstance(){
	if(!instance){
		instance = new SpriteRenderer();
	}
	return instance;
}
