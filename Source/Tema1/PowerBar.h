#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class PowerBar
{
public:
	PowerBar(std::string name, float limit, float factor,
		float speed, float length, float x, float y);
	~PowerBar();
	std::string name;
	float limit, factor, speed, length, x, y;
};