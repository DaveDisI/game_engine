#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char* imageToByteArray(const char* file, int* width, int* height){
	int n;
	return stbi_load(file, width, height, &n, 0);
}

void deleteImageData(unsigned char* data){
	stbi_image_free(data);
}

