#include "Scene.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Line.h"
#include "Shape.h"
#include "Rectangle.h"

Rectangle::Rectangle(){
	this->ochar = ' ';
}

Rectangle::Rectangle(Vector2D position, Vector2D scale){
	this->transform.setPosition(position);
	this->transform.setScale(scale);
	this->ochar = ' ';
}

Rectangle::Rectangle(Vector2D position, Vector2D scale, char ochar){
	this->transform.setPosition(position);
	this->transform.setScale(scale);
	this->ochar = ochar;
}

void Rectangle::draw(Scene& scene){
	Line side[5];

	Vector2D top_left_corner = transform.getPosition();
	Vector2D top_right_corner = transform.getPosition() + Vector2D(transform.getScale().x - 1, 0);
	Vector2D bottom_right_corner = transform.getPosition() + Vector2D(transform.getScale().x - 1, transform.getScale().y - 1);
	Vector2D bottom_left_corner = transform.getPosition() + Vector2D(0, transform.getScale().y - 1);

	side[0] = Line(top_left_corner, top_right_corner, ochar);
	side[1] = Line(top_right_corner, bottom_right_corner, ochar);
	side[2] = Line(bottom_right_corner, bottom_left_corner, ochar);
	side[3] = Line(bottom_left_corner, top_left_corner, ochar);

	for (int i = 0; i < 4; i++)
		side[i].draw(scene);
}