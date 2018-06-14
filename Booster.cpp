#include "stdafx.h"
#include "Booster.h"


Booster::Booster(int x, int y)
{
	BoosterShape.setSize(sf::Vector2f(20.0f, 20.0f));
	BoosterShape.setPosition(x*30.0 + 16.0, y*30.0 + 16.0);
	BoosterShape.setOrigin(sf::Vector2f(10.0f, 10.0f));
	BoostRate = 2.0;
	CoordinatesX = x;
	CoordinatesY = y;
}

void Booster::Boost(float * Power)
{
	*Power *= BoostRate;
}
