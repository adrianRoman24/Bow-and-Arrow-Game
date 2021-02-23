#include "PowerBar.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

PowerBar::PowerBar(std::string name, float limit, float factor,
	float speed, float length, float x, float y) {
	PowerBar::name = name;
	PowerBar::limit = limit;
	PowerBar::factor = factor;
	PowerBar::speed = speed;
	PowerBar::length = length;
	PowerBar::x = x;
	PowerBar::y = y;
}

PowerBar::~PowerBar() {

}