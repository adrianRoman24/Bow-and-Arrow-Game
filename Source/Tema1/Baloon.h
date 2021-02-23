#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#include "Arrow.h"

class Baloon
{
public:
	Baloon(std::string name, std::string color, float radius, float scaleFactor,
		float x, float y, float distructionFactor);
	~Baloon();
	bool Collision(Arrow *arrow);

	std::string name;
	std::string color;
	float radius, scaleFactor, x, y;
	bool hit = false;
	float distructionFactor;
};