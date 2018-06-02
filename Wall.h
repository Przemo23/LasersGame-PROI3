#pragma once
#pragma once
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "Sat.h"


class Wall
{
public:
	Wall() {};
	Wall(int Length, int Height);
	~Wall() {};

	void StopMovement(sf::Vector2f*);

	sf::RectangleShape WallShape;

};
