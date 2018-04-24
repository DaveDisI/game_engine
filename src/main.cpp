#include "stdio.h"

#include "io_manager.h"
#include "render_manager.h"

int main(int argc, char** argv){
	IOManager* iomgr = IOManager::getInstance();
	iomgr->createWindow("GAME ENGINE", 100, 100, 800, 500);
	iomgr->setWindowVSync(false);

	RenderManager* rdrmgr = RenderManager::getInstance();
	rdrmgr->setViewport(0, 0, iomgr->getWindowWidth(), iomgr->getWindowHeight());
	rdrmgr->setClearColor(0.2, 0.4, 0.6, 1);

	TextRenderer* txtrdr = rdrmgr->getTextRendererInstance();

	long startTime = 0, endTime = 0;
	float deltaTime = 0;
	int fps = 0;
	int frameRate = 0;
	long totalFrames = 0;
	double elapsedTime = 0;
	long frameStartTime = 0;
	char fpsStr[4];

	while(!iomgr->keys[IOManager::ESC_KEY] && !iomgr->QUIT){
		startTime = iomgr->getTime();
		iomgr->processEvents();
		rdrmgr->clear(GL_COLOR_BUFFER_BIT);

		txtrdr->prepare();
		sprintf(fpsStr, "%d", frameRate);
		txtrdr->renderText("FPS:", 10, 225, 0.4);
		txtrdr->renderText(fpsStr, 50, 225, 0.4);

		iomgr->swapWindowBuffer();

		endTime = iomgr->getTime();
		deltaTime = (float)((double)endTime - (double)startTime) / 1000.0;
		totalFrames++;
		fps++;
		elapsedTime += deltaTime;

		if(endTime - frameStartTime >= 1000){
			frameRate = fps;
			fps = 0;
			frameStartTime = endTime;
		}
	}

	rdrmgr->shutdown();
	iomgr->shutdown();

	return 0;
}
