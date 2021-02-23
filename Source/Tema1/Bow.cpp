#include "Bow.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

Bow::Bow(std::string name, float angle, float radius, float scaleFactor, float x, float y) {
	Bow::name = name;
	Bow::angle = angle;
	Bow::radius = radius;
	Bow::scaleFactor = scaleFactor;
	Bow::x = x;
	Bow::y = y;
}

Bow::~Bow() {

}

bool Bow::Collision(Shuriken *shuriken) {
	float xDistance = shuriken->x - x;
	float yDistance = shuriken->y - y;
	float distance = sqrt(xDistance * xDistance + yDistance * yDistance);
	float minimumDistance = shuriken->cathetus * (float)sqrt(2); // shuriken radius
	minimumDistance += radius;
	return minimumDistance >= distance;
}

bool Bow::Collision(Sharingan *sharingan) {
	float xDistance = sharingan->x - x;
	float yDistance = sharingan->y - y;
	float distance = (float)sqrt(xDistance * xDistance + yDistance * yDistance);
	float minimumDistance = sharingan->radius;
	minimumDistance += radius;
	return minimumDistance >= distance;
}
