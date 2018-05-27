#pragma once
#include "stdafx.h"
#include <SFML\Graphics.hpp>


class Mirror
{
	
public:
	Mirror() {};
	Mirror(int, int);
	~Mirror() {};
	int CoordinatesX, CoordinatesY;
	

	sf::RectangleShape MirrorShape;
	


};