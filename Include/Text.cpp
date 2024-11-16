#include "Scene.h"
#include "Vector2D.h"
#include "Text.h"

int strlen(char* text) {
	int i = 0;
	for (i; text[i]; i++);
	return i;
}
char* toString(int number, char text[200]) {
	int i = 0, p = 1, n = number;
	while (n) { p *= 10; n /= 10; }
	p /= 10;

	while (p) {
		text[i] = char(number / p + 48);
		number %= p;
		p /= 10;
		i++;
	} text[i] = '\0';

	return text;
}

Text::Text(){}

Text::Text(int x, int y, int number) {
	this->position = Vector2D(x, y);

	char string[200];
	this->text = toString(number, string);
	this->length = strlen(text) + x;
}

Text::Text(Vector2D position, int number) {
	this->position = position;

	char string[200];
	this->text = toString(number, string);
	this->length = strlen(text) + position.x;
}

Text::Text(int x, int y, char* text) {
	this->position = Vector2D(x, y);
	this->text = text;

	length = strlen(text) + x;
}

Text::Text(Vector2D position, char* text) {
	this->position = position;
	this->text = text;

	length = strlen(text) + position.x;
}


void Text::draw(Scene& scene) {
	int j = 0;
	for (int i = position.x; i < length; i++)
		scene.canvasBuffer[int(position.y) * scene.width + i] = text[j++];
}

void Text::set(char* text) {
	this->text = text;

	length = strlen(text) + position.x;
}

void Text::set(int number) {
	char string[200];
	text = toString(number, string);

	length = strlen(text) + position.x;
}


