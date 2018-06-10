#pragma once
#pragma once
#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Sat.h"


class Booster
{
public:
	Booster() {};
	Booster(int Length, int Height);
	int BoostRate;
	~Booster() {};
	int CoordinatesX, CoordinatesY;
	void Boost(int* Power);

	sf::RectangleShape BoosterShape;

};