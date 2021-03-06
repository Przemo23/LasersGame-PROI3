#pragma once
#include "stdafx.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Sat.h"


class RoughObject
{
public:
	RoughObject() {};
	RoughObject(int Length, int Height);
	~RoughObject() {};
	sf::Color FillingColor;
	std::vector <float> DispersionValues;
	int CoordinatesX, CoordinatesY;
	sf::Vector2f Dispersion(sf::Vector2f,float);
	
	sf::Color ChangingColor(sf::Color);

	sf::RectangleShape RoughObjectShape;

};