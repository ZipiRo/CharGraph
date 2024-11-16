#include "Vector2D.h"
#include "Transform.h"

Transform::Transform(){
    this->position = Zero;
    this->scale = Zero;
    this->pivot = Zero;
}

void Transform::setPosition(Vector2D position){
    this->position = position;
}

void Transform::setScale(Vector2D scale){
    this->scale = scale;
}

void Transform::setPivot(Vector2D pivot){
    this->pivot = pivot;
    this->position = this->position - floorf(multiply(this->scale - Vector2D(1, 1), this->pivot));
}

Vector2D Transform::getPosition(){
    return this->position;
}

Vector2D Transform::getScale(){
    return this->scale;
}

Vector2D Transform::getPivot(){
    return this->pivot;
}

