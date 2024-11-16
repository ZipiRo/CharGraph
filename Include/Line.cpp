#include "Scene.h"
#include "Vector2D.h"
#include "Point.h"
#include "Line.h"

Line::Line(){
	this->cchar = ' ';
}

Line::Line(Vector2D origin, Vector2D range, char cchar){
    this->origin = origin;
    this->range = range;
    this->cchar = cchar;
}

void Line::draw(Scene& scene) {
    if (origin.x == range.x) {
        if (origin.y > range.y) {
            int aux = origin.y;
            origin.y = range.y;
            range.y = aux;
        }

        Point* point;
        for (int y = this->origin.y; y <= this->range.y; y++) {
            point = new Point(Vector2D(origin.x, y), cchar);
            point->draw(scene);
            delete point;
        }

        return;
    }

    int dx = range.x - origin.x;
    int dy = range.y - origin.y;

    Point* point;
    if (origin.x < range.x) {
        for (int x = this->origin.x; x <= this->range.x; x++) {
            int y = this->origin.y + dy * (x - this->origin.x) / dx;
            point = new Point(Vector2D(x, y), cchar);
            point->draw(scene);
            delete point;
        }
    } else {
        for (int x = this->range.x; x <= this->origin.x; x++) {
            int y = this->origin.y + dy * (x - this->origin.x) / dx;
            point = new Point(Vector2D(x, y), cchar);
            point->draw(scene);
            delete point;
        }
    }
}