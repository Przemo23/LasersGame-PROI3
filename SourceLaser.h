#pragma once
#include "stdafx.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Sat.h"

class SourceLaser
{

public:
	SourceLaser() {};
	
	SourceLaser(int Length, int Height);
	
	~SourceLaser() {};


	sf::RectangleShape Source;

	int CoordinatesX, CoordinatesY;

};