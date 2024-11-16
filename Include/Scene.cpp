#include <iostream>
#include <cstring>
#include "Scene.h"

#define RESET_CURSOR_POSITION std::cout << "\033[H";
#define CLEAR_CONSOLE std::cout << "\033[2J";

Scene::Scene(int width, int height) {
	this->width = width;
	this->height = height;
	this->cchar = cchar;

	memset(canvasBuffer, ' ', width * height);
}

void Scene::fill(char cchar) {
	memset(canvasBuffer, cchar, width * height);
}

void Scene::paint() {
	RESET_CURSOR_POSITION
	for(int i = 0; i < width * height; i++)
		putchar((i + 1) % width ? canvasBuffer[i] : 10);
}

void Scene::clear() {
	memset(canvasBuffer, cchar, width * height);
}