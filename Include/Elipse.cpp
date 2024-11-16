#include <cmath>
#include "Scene.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Shape.h"
#include "Point.h"
#include "Elipse.h"

Elipse::Elipse(){
	this->ochar = ' ';
}

Elipse::Elipse(Vector2D position, Vector2D scale) {
	this->transform.setPosition(position);
	this->transform.setScale(scale); 
	this->ochar = ' ';
}

Elipse::Elipse(Vector2D position, Vector2D scale, char ochar){
	this->transform.setPosition(position);
	this->transform.setScale(scale); 
	this->ochar = ochar;
}

void Elipse::draw(Scene& scene) {
	Point point;
	for (float angle = 0.03f; angle <= (2.00f * 3.14159); angle+=0.01f){
		int dx = transform.getScale().x * sin(angle);
		int dy = transform.getScale().y * cos(angle);

		point = Point(transform.getPosition() + Vector2D(dx, dy), ochar);
		point.draw(scene);
	}
}