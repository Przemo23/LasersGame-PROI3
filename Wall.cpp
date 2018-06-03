
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Sat.h"
#include "Wall.h"

using namespace sf;
Wall::Wall(int Length, int Height)
{
	WallShape.setSize(Vector2f(30.0, 30.0));
	WallShape.setPosition(Length*30.0 + 1.0, Height*30.0 + 1.0);

	WallShape.setOrigin(Vector2f(15.0, 15.0));
	WallShape.setFillColor(Color::Yellow);

}


