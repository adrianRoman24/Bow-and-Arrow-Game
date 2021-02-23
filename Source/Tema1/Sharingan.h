#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "Arrow.h"

class Sharingan
{
public:
	Sharingan(std::string name, float radius, float x,
		float y, float distructionFactor, float speedOy);
	~Sharingan();
	bool Collision(Arrow *arrow);

	std::string name;
	std::string color;
	float radius, x, y;
	bool hit = false, bowCollision = false;
	float distructionFactor;
	float speedOy;
};