#include "Baloon.h"

#include <string>
#include <vector>
#include <iostream>

#include <Core/Engine.h>

Baloon::Baloon(std::string name, std::string color,  float radius, float scaleFactor,
	float x, float y, float distructionFactor) {
	Baloon::color = color;
	Baloon::name = name;
	Baloon::radius = radius;
	Baloon::scaleFactor = scaleFactor;
	Baloon::x = x;
	Baloon::y = y;
	Baloon::distructionFactor = distructionFactor;
}

Baloon::~Baloon() {

}

bool Baloon::Collision(Arrow *arrow) {
	float totalLength = arrow->length + arrow->peak * (float)sqrt(3) / 2;
	float xA = arrow->x + totalLength * cos(arrow->angle);
	float yA = arrow->y + totalLength * sin(arrow->angle);
	float arrow_baloon_angle = abs(atan((y - yA) / (x - xA)));
	float distance = sqrt((x - xA) * (x - xA) + (y - yA) * (y - yA));
	float minimumDistance = (float)(radius * cos(arrow_baloon_angle) + radius * sin(arrow_baloon_angle) * scaleFactor);
	return minimumDistance >= distance;
}
