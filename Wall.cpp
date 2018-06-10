
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Sat.h"
#include "Wall.h"

using namespace sf;
Wall::Wall(int x, int y)
{
	CoordinatesX = x;
	CoordinatesY = y;
	WallShape.setSize(Vector2f(20.0, 20.0));
	WallShape.setPosition(x*30.0 + 16.0, y*30.0 + 16.0);

	WallShape.setOrigin(Vector2f(10.0, 10.0));
	
	
}


