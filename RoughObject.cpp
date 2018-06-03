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
	RoughObjectShape.setSize(Vector2f(20.0f, 20.0f));
	RoughObjectShape.setPosition(x*30.0 + 16.0, y*30.0 + 16.0);
	RoughObjectShape.setOrigin(Vector2f(10.0f, 10.0f));
	CoordinatesX = x;
	CoordinatesY = y;
}
void RoughObject::Dispersion31( sf::Vector2f * Movement)
{
	Vector2f TempDirection, TempDirection2;
	float IncidenceAngle, RandomAngle;
	float TemporaryValue;
	float Rotation = RoughObjectShape.getRotation();

	
	srand(time(NULL));

	TempDirection.x = - (Movement->x * cos(1.5 * PI - Rotation * PI / 180) - Movement->y * sin(1.5 * PI - Rotation * PI / 180));
	TempDirection.y = Movement->x * sin(1.5 * PI - Rotation * PI / 180) + Movement->y * cos(1.5* PI - Rotation * PI / 180);
	TemporaryValue = sqrt(TempDirection.x*TempDirection.x + TempDirection.y*TempDirection.y);
	IncidenceAngle = abs(asin(sin(TempDirection.y / TemporaryValue)));
	RandomAngle = rand() % 40 - 20;
	TempDirection2.x = TempDirection.x * cos(IncidenceAngle - RandomAngle) - TempDirection.y * sin(IncidenceAngle - RandomAngle);
	TempDirection2.y = TempDirection.x * sin(IncidenceAngle - RandomAngle) + TempDirection.y * cos(IncidenceAngle - RandomAngle);
	Movement->x = TempDirection2.x * cos(0.5*PI + Rotation * PI / 180) - TempDirection2.y * sin(0.5*PI + Rotation * PI / 180);
	Movement->y = TempDirection2.x * sin(0.5*PI + Rotation * PI / 180) + TempDirection2.y * cos(0.5*PI + Rotation * PI / 180);

}

void RoughObject::Dispersion42(sf::Vector2f * Movement)
{
	Vector2f TempDirection, TempDirection2;
	float IncidenceAngle, RandomAngle;
	float TemporaryValue;
	float Rotation = RoughObjectShape.getRotation();
	srand(time(NULL));

	TempDirection.x = - (Movement->x * cos(2 * PI - Rotation * PI / 180) - Movement->y * sin(2 * PI - Rotation * PI / 180));
	TempDirection.y = Movement->x * sin(2 * PI - Rotation * PI / 180) + Movement->y * cos(2 * PI - Rotation * PI / 180);
	TemporaryValue = sqrt(TempDirection.x*TempDirection.x + TempDirection.y*TempDirection.y);
	IncidenceAngle = abs(asin(sin(TempDirection.y / TemporaryValue)));
	RandomAngle = (rand() % 40 - 20)*PI / 180;
	TempDirection2.x = TempDirection.x * cos(IncidenceAngle - RandomAngle) - TempDirection.y * sin(IncidenceAngle - RandomAngle);
	TempDirection2.y = TempDirection.x * sin(IncidenceAngle - RandomAngle) + TempDirection.y * cos(IncidenceAngle - RandomAngle);
	Movement->x = TempDirection2.x * cos(Rotation * PI / 180) - TempDirection2.y * sin(Rotation * PI / 180);
	Movement->y = TempDirection2.x * sin(Rotation * PI / 180) + TempDirection2.y * cos(Rotation * PI / 180);
}

Color RoughObject::ChangingColor(Color LaserColor)
{
	
	if (LaserColor !=FillingColor)
	{
		LaserColor = FillingColor;
		
	}
	
		return LaserColor;
	
}
