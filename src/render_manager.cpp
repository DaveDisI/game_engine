#include "render_manager.h"

#include <GL/glew.h>

RenderManager* RenderManager::instance = nullptr;
const unsigned int RenderManager::COLOR_BUFFER = GL_COLOR_BUFFER_BIT;
const unsigned int RenderManager::TRIANGLES = GL_TRIANGLES;

RenderManager::~RenderManager(){

}

RenderManager::RenderManager(){
	initialize();
}

void RenderManager::shutdown(){
	if(instance){
		txtrdr->shutdown();

		delete instance;
		instance = nullptr;
	}
}

void RenderManager::initialize(){
	glewInit();
}

void RenderManager::setViewport(int x, int y, int w, int h){
	viewport = vec4(x, y, w, h);
	glViewport(x, y, w, h);
}

void RenderManager::setClearColor(float r, float g, float b, float a){
	clearColor = vec4(r, g, b, a);
	glClearColor(r, g, b, a);
}

void RenderManager::clear(int field){
	glClear((GLbitfield)field);
}

void RenderManager::enable(int field){
	glEnable((GLbitfield)field);
}
RenderManager* RenderManager::getInstance(){
	if(!instance){
		instance = new RenderManager();
	}

	return instance;
}

TextRenderer* RenderManager::getTextRendererInstance(){
	txtrdr = TextRenderer::getInstance();
	txtrdr->setProjection((float)viewport.v[0], (float)viewport.v[2], (float)viewport.v[1], (float)viewport.v[3]);
	return txtrdr;
}
