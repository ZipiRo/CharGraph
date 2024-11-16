#include "cmath"
#include "Vector2D.h"

Vector2D::Vector2D(){
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator= (Vector2D b){
    this->x = b.x; this->y = b.y;
    return *this;
}

Vector2D Vector2D::operator+ (Vector2D b) const{
    return Vector2D(this->x + b.x, this->y + b.y);
}

Vector2D Vector2D::operator+= (Vector2D b){
    this->x += b.x; this->y += b.y;
    return *this;
}

Vector2D Vector2D::operator- (Vector2D b) const{
    return Vector2D(this->x - b.x, this->y - b.y);
}

Vector2D Vector2D::operator-= (Vector2D b){
    this->x -= b.x; this->y -= b.y;
    return *this;
}

Vector2D Vector2D::operator* (float scalar) const{
    return Vector2D(this->x * scalar, this->y * scalar);
}

Vector2D Vector2D::operator/ (float scalar) const{
    return Vector2D(this->x / scalar, this->y / scalar);
}

bool Vector2D::operator== (Vector2D b) const{
    return (this->x == b.x && this->y == b.y);
}

Vector2D multiply(Vector2D a, Vector2D b){
    return Vector2D(a.x * b.x, a.y * b.y);
}

Vector2D divide(Vector2D a, Vector2D b){
    return Vector2D(a.x / b.x, a.y / b.y);
}

Vector2D floorf(Vector2D a){
    return Vector2D(floorf(a.x), floorf(a.y));
}

Vector2D fabsf(Vector2D a){
    return Vector2D(fabsf(a.x), fabsf(a.y));
}