#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class Arrow
{
public:
	Arrow(std::string name, float speedX, float speedY, float angle, float length,
		float height, float peak, float x, float y);
	~Arrow();
	void Update(float deltaTimeSeconds);
	std::string name;
	float speedX, speedY, angle, length, height, peak, x, y;
};