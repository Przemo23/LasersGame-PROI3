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
	int CoordinatesX, CoordinatesY;
	void Dispersion31(sf::Vector2f*);
	void Dispersion42(sf::Vector2f*);

	sf::Color ChangingColor(sf::Color);

	sf::RectangleShape RoughObjectShape;

};