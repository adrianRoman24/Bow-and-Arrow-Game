#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "Shuriken.h"
#include "Sharingan.h"

class Bow
{
public:
	Bow(std::string name, float angle, float radius, float scaleFactor, float x, float y);
	~Bow();
	bool Collision(Shuriken *shuriken);
	bool Collision(Sharingan *sharingan);
	std::string name;
	float angle, radius, scaleFactor, x, y;
};