#include "sprite_renderer.h"

#include "shader_compiler.h"

SpriteRenderer* SpriteRenderer::instance = nullptr;

SpriteRenderer::SpriteRenderer(){
	initialize();
}

SpriteRenderer::~SpriteRenderer(){
	
}

SpriteRenderer* SpriteRenderer::getInstance(){
	if(!instance){
		instance = new SpriteRenderer();
	}
	return instance;
}

void SpriteRenderer::shutdown(){
	if(instance){
		glDeleteVertexArrays(1, &spriteVao);
		glDeleteBuffers(1, &spriteVbo);
		glDeleteBuffers(1, &spriteEbo);
		glDeleteProgram(spriteShader);
		glDeleteTextures(1, &textureArray);
		
		textureIds.clear();
		freeTextures.clear();
		freeSprites.clear();
		textureWidths.clear();
		textureHeights.clear();
		spriteColors.clear();
		modelMatrices.clear();
		sprites.clear();
		
		delete instance;
		instance = nullptr;
	}
}

void SpriteRenderer::render(Camera2D cam){
	glUseProgram(spriteShader);
	glBindVertexArray(spriteVao);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	for(int i = 0; i < totalSpriteCount; i++){
		mat4 mvp = cam.projectionMatrix * inverse(cam.viewMatrix) * modelMatrices[i];
		glUniform3f(textureDataId, textureWidths[i], textureHeights[i], textureIds[i]);
		glUniform4f(spriteColorId, spriteColors[i].x, spriteColors[i].y, spriteColors[i].z, spriteColors[i].w);
		glUniformMatrix4fv(mvpMatId, 1, GL_FALSE, value_ptr(mvp));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
	}
}

void SpriteRenderer::loadTextureData(SpriteTextureData* texDat,  unsigned char* data, int width, int height){
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
	if(freeTextures.size() > 0){
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, freeTextures.back(), width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
		freeTextures.pop_back();
	}else{
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, totalTextures, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	texDat->textureId = totalTextures++;
	texDat->width = (float)width / (float)MAX_TEXTURE_SIZE;
	texDat->height = (float)height / (float)MAX_TEXTURE_SIZE;
}

void SpriteRenderer::assignTextureToSprite(SpriteTextureData& texDat, Sprite* sprite){
	int i = sprite->indexId;
	textureIds[i] = texDat.textureId;
	textureWidths[i] = texDat.width;
	textureHeights[i] = texDat.height;
}

void SpriteRenderer::deleteTextureData(SpriteTextureData& texDat){
	freeTextures.push_back(texDat.textureId);
	int tid = texDat.textureId;
	for(int i = 0; i < totalSpriteCount; i++){
		if(textureIds[i] == tid){
			textureIds[i] = defaultTextureData.textureId;
			textureWidths[i] = defaultTextureData.width;
			textureHeights[i] = defaultTextureData.height;
		}
	}
}

void SpriteRenderer::deleteSprite(Sprite* sprite){
	int ind = sprite->indexId;
	sprite->indexId = -1;
	totalSpriteCount--;
	int sz = sprites.size();
	
	for(int i = 0; i < sz; i++){
		if(sprites[i].indexId == totalSpriteCount){
			sprites[i].indexId = ind;
		}else if(sprite == &sprites[i]){
			freeSprites.push_back(i);
		}
	}
	sprite = nullptr;
	
	textureIds[ind] = textureIds[totalSpriteCount];
	textureWidths[ind] = textureWidths[totalSpriteCount];
	textureHeights[ind] = textureHeights[totalSpriteCount];
	modelMatrices[ind] = modelMatrices[totalSpriteCount];
	textureIds.pop_back();
	textureWidths.pop_back();
	textureHeights.pop_back();
	modelMatrices.pop_back();
}

void SpriteRenderer::updateSprite(Sprite* sprite){
	int i = sprite->indexId;
	mat4 m = mat4(1);
	m = translate(m, vec3(sprite->position, 0));
	m = rotate(m, sprite->rotation, vec3(0, 0, 1));
	m = scale(m, vec3(sprite->scale, 0));
	modelMatrices[i] = m;
}

void SpriteRenderer::setSpriteColor(Sprite* spt, vec4 rgba){
	int i = spt->indexId;
	spriteColors[i] = rgba;
}

void SpriteRenderer::initialize(){
	totalSpriteCount = 0;
	totalTextures = 0;

	float vertexData[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,  
        -0.5f,  0.5f, 0.0f, 1.0f, 
		 0.5f,  0.5f, 1.0f, 1.0f, 
		 0.5f, -0.5f, 1.0f, 0.0f  
	};
	
	unsigned char elementData[] = {
		0, 1, 2, 2, 3, 0
	};
	
	glGenVertexArrays(1, &spriteVao);
	glBindVertexArray(spriteVao);
	
	glGenBuffers(1, &spriteVbo);
	glBindBuffer(GL_ARRAY_BUFFER, spriteVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	glGenBuffers(1, &spriteEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);
	
	const GLchar* vertexShaderSource = "#version 310 es\n"
    "layout (location = 0) in vec2 position;"
    "layout (location = 1) in vec2 texcoord;"
    "uniform mat4 mvpMatrix;"
    "out vec2 Texcoord;"
    "void main()"
    "{"   
    "    Texcoord = vec2(texcoord.x,  1.0 - texcoord.y);"
    "    gl_Position = mvpMatrix * vec4(position, 0.0, 1.0);"
    "}";
	const GLchar* fragmentShaderSource = "#version 310 es\n"
	"precision mediump float;"
	"precision mediump sampler2DArray;"
    "in vec2 Texcoord;"
    "out vec4 outColor;"
    "uniform vec4 spriteColor;"
    "uniform vec3 texData;"
    "uniform sampler2DArray tex;"
    "void main()"
    "{"
    "    outColor = spriteColor * texture(tex, vec3(Texcoord * texData.xy, texData.z));\n"
    "}";
	
	spriteShader = compileShaderVF(vertexShaderSource, fragmentShaderSource);
	mvpMatId = glGetUniformLocation(spriteShader, "mvpMatrix");
	spriteColorId = glGetUniformLocation(spriteShader, "spriteColor");
	textureDataId = glGetUniformLocation(spriteShader, "texData");
	
	textureIds.reserve(MAX_SPRITES);
	freeTextures.reserve(MAX_TEXTURES);
	freeSprites.reserve(MAX_SPRITES);
	textureWidths.reserve(MAX_SPRITES);
	textureHeights.reserve(MAX_SPRITES);
	spriteColors.reserve(MAX_SPRITES);
	modelMatrices.reserve(MAX_SPRITES);
	sprites.reserve(MAX_SPRITES);
	
	glGenTextures(1, &textureArray);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, MAX_TEXTURE_SIZE, MAX_TEXTURE_SIZE, MAX_TEXTURE_DEPTH);

	GLubyte data[] = {
		255, 255, 255, 255
	};
	loadTextureData(&defaultTextureData, data, 1, 1);		
}

void SpriteRenderer::updateAnimatedSprite(AnimatedSprite* aspt, float delta){ 
	int curfrm = aspt->currentFrame;
	int prvfrm = aspt->previousFrame;
	float curtm = aspt->frameElapsedTime + delta;
	int totfrms = aspt->totalFrames;
	float curfrmtm = aspt->durations[curfrm];
	
	if(curtm > curfrmtm){
		prvfrm = curfrm;
		curfrm++;
		if(curfrm > totfrms - 1){
			curfrm -= totfrms;
		}	
		assignTextureToSprite(aspt->images[curfrm], aspt->sprite);
		curtm = 0;
	}
	
	aspt->currentFrame = curfrm;
	aspt->previousFrame = prvfrm;
	aspt->frameElapsedTime = curtm;
	
	updateSprite(aspt->sprite);
}

void SpriteRenderer::initializeAnimatedSprite(AnimatedSprite* anispt){
	anispt->sprite = createSprite();
	
	if(!anispt->images.empty()){
		assignTextureToSprite(anispt->images[0], anispt->sprite);
	}
}

Sprite* SpriteRenderer::createSprite(){
	//THIS IS TEMPORARY
	if(totalSpriteCount > MAX_SPRITES){
		std::cerr << "MAX SPRITES IN SCENE HAS BEEN EXCEEDED.\n\n\n";
		return NULL;
	}
	
	textureIds.push_back(defaultTextureData.textureId);
	textureWidths.push_back(defaultTextureData.width);
	textureHeights.push_back(defaultTextureData.height);
	spriteColors.push_back(vec4(1));
	modelMatrices.push_back(mat4(1));
	
	Sprite sprite;
	sprite.indexId = totalSpriteCount;
	
	if(freeSprites.size() > 0){
		sprites[freeSprites.back()] = sprite;
		freeSprites.pop_back();
	}else{
		sprites.push_back(sprite);
	}
	
	return &sprites[totalSpriteCount++];
}

Sprite* SpriteRenderer::createSprite(SpriteTextureData& texDat){
	Sprite* sprite = createSprite();
	int i = sprite->indexId;
	textureIds[i] = texDat.textureId;
	textureWidths[i] = texDat.width;
	textureHeights[i] = texDat.height;
	
	return sprite;
}

Sprite* SpriteRenderer::createSprite(vec4 rgba){
	Sprite* sprite = createSprite();
	int i = sprite->indexId;
	spriteColors[i] = rgba;
	
	return sprite;
}

Sprite* SpriteRenderer::createSprite(SpriteTextureData& texDat, vec4 rgba){
	Sprite* sprite = createSprite();
	int i = sprite->indexId;
	textureIds[i] = texDat.textureId;
	textureWidths[i] = texDat.width;
	textureHeights[i] = texDat.height;
	spriteColors[i] = rgba;
	
	return sprite;
}
