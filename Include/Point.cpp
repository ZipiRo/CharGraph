#include "Scene.h"
#include "Vector2D.h"
#include "Point.h"

Point::Point(){
	this->cchar = cchar;
}

Point::Point(Vector2D position, char cchar) {
	this->position = position;
	this->cchar = cchar;
}

void Point::draw(Scene &scene) {
	scene.canvasBuffer[1 + int(position.x) + (int(position.y) * scene.width)] = cchar;
}