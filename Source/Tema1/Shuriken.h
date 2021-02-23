#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "Arrow.h"

class Shuriken
{
public:
	Shuriken(std::string name, float cathetus, float x, float y, float distructionFactor, float speedOy);
	~Shuriken();
	bool Collision(Arrow *arrow);

	std::string name;
	float cathetus, x, y;
	bool hit = false, bowCollision = false;
	float distructionFactor;
	float speedOy;
};