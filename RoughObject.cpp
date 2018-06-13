#include "stdafx.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Sat.h"
#include "RoughObject.h"
#include <time.h>
#include <stdio.h>
#define PI 3.14159265
using namespace sf;
RoughObject::RoughObject(int x, int y)
{
	DispersionValues.push_back ((rand() % 20 - 10 )* PI / 180);
	DispersionValues.push_back((rand() % 20 - 10)* PI / 180);
	DispersionValues.push_back((rand() % 20 - 10)* PI / 180);
	DispersionValues.push_back((rand() % 20 - 10)* PI / 180);
	RoughObjectShape.setSize(Vector2f(20.0f, 20.0f));
	RoughObjectShape.setPosition(x*30.0 + 16.0, y*30.0 + 16.0);
	RoughObjectShape.setOrigin(Vector2f(10.0f, 10.0f));
	CoordinatesX = x;
	CoordinatesY = y;
	FillingColor = sf::Color::Red;
}
Vector2f RoughObject::Dispersion( Vector2f  Movement,float RandomAngle)
{
	Vector2f TempDirection;
	
	TempDirection.x = Movement.x;
	TempDirection.y = Movement.y;


	
	
	
	Movement.x = TempDirection.x * cos(RandomAngle) - TempDirection.y * sin(RandomAngle);
	Movement.y = TempDirection.x * sin(RandomAngle) + TempDirection.y * cos(RandomAngle);
	return Movement;
}



Color RoughObject::ChangingColor(Color LaserColor)
{
	
	if (LaserColor !=FillingColor)
	{
		LaserColor = FillingColor;
		
	}
	
		return LaserColor;
	
}
