#include "Shuriken.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

Shuriken::Shuriken(std::string name, float cathetus, float x, float y, float distructionFactor, float speedOy) {
	Shuriken::name = name;
	Shuriken::cathetus = cathetus;
	Shuriken::x = x;
	Shuriken::y = y;
	Shuriken::distructionFactor = distructionFactor;
	Shuriken::speedOy = speedOy;

}

Shuriken::~Shuriken() {

}

bool Shuriken::Collision(Arrow *arrow) {
	float totalLength = arrow->length + arrow->peak * (float)sqrt(3) / 2;
	float xA = arrow->x + totalLength * cos(arrow->angle);
	float yA = arrow->y + totalLength * sin(arrow->angle);
	float arrow_baloon_angle = abs(atan((y - yA) / (x - xA)));
	float distance = sqrt((x - xA) * (x - xA) + (y - yA) * (y - yA));
	float radius = cathetus * (float)sqrt(2);
	float minimumDistance = radius * cos(arrow_baloon_angle) + radius * sin(arrow_baloon_angle);
	return minimumDistance >= distance;
}