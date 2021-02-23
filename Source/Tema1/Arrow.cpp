#include "Arrow.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

Arrow::Arrow(std::string name, float speedX, float speedY, float angle,
	float length, float height, float peak, float x, float y) {
	Arrow::name = name;
	Arrow::speedX = speedX;
	Arrow::speedY = speedY;
	Arrow::angle = angle;
	Arrow::length = length;
	Arrow::height = height;
	Arrow::peak = peak;
	Arrow::x = x;
	Arrow::y = y;
}

Arrow::~Arrow() {

}

void Arrow::Update(float deltaTimeSeconds) {
	if (angle > 0) {
		if (speedX >= 0 && speedY >= 0) {
			// right up
			x += speedX * deltaTimeSeconds;
			y += speedY * deltaTimeSeconds;
		}
		else {
			// left down
			y += speedY * deltaTimeSeconds;
		}
	}
	else {
		if (speedX > 0) {
			// right down
			x += speedX * deltaTimeSeconds;
			y += speedY * deltaTimeSeconds;
		}
		else {
			// left down
			y += speedY * deltaTimeSeconds;
		}
	}
}
