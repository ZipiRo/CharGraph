#include "Scene.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Line.h"
#include "Shape.h"
#include "Poligon.h"

Poligon::Poligon(){
    this->ochar = ' ';
}

Poligon::Poligon(Vector2D points[], int sides){
    for(int i = 0; i < sides; i++)
        this->points[i] = points[i];

	this->sides = sides;
	this->ochar = ' ';
}

Poligon::Poligon(Vector2D points[], int sides, char ochar){
    for(int i = 0; i < sides; i++)
        this->points[i] = points[i];

	this->sides = sides;
	this->ochar = ochar;
}

void Poligon::draw(Scene &scene){
    Line l[100];
    
    int i = 0;
    for (i; i < sides - 1; i++) {
        l[i] = Line(points[i], points[i + 1], ochar);
        l[i].draw(scene);
    }

    l[i + 1] = Line(points[i], points[0], ochar);
    l[i + 1].draw(scene);
}