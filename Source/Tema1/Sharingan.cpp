#include "Sharingan.h"

#include <string>
#include <vector>
#include <iostream>

#include <Core/Engine.h>

Sharingan::Sharingan(std::string name, float radius, float x,
	float y, float distructionFactor, float speedOy) {
	Sharingan::color = color;
	Sharingan::name = name;
	Sharingan::radius = radius;
	Sharingan::x = x;
	Sharingan::y = y;
	Sharingan::distructionFactor = distructionFactor;
	Sharingan::speedOy = speedOy;
}

Sharingan::~Sharingan() {
}

bool Sharingan :: Collision(Arrow *arrow) {
	float totalLength = arrow->length + arrow->peak * (float)sqrt(3) / 2;
	float xA = arrow->x + totalLength * cos(arrow->angle);
	float yA = arrow->y + totalLength * sin(arrow->angle);
	float arrow_baloon_angle = (float)abs(atan((y - yA) / (x - xA)));
	float distance = (float)sqrt((x - xA) * (x - xA) + (y - yA) * (y - yA));
	float minimumDistance = (float)(radius * cos(arrow_baloon_angle) + radius * sin(arrow_baloon_angle));
	return minimumDistance >= distance;
}