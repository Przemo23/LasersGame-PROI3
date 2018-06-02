#include "stdafx.h"
#include <cmath>
#include <SFML\Graphics.hpp>
#include "Prism.h"
#include "Sat.h"
#include "SourceLaser.h"
#define PI 3.14159265


using namespace sf;

Prism::Prism(int x, int y)
{
	CoordinatesX = x;
	CoordinatesY = y;
	PrismShape.setSize(Vector2f(20.0f, 20.0f));
	PrismShape.setPosition(x*30.0 + 16.0, y*30.0 + 16.0);
	PrismShape.setOrigin(Vector2f(10.0f, 10.0f));
	
	
	
	RefractionRate = 1.5;
	

}

void Prism::Refraction42Sides(sf::RectangleShape Laser, sf::Vector2f* Movement)
{
	
	
		Vector2f TempDirection, PrismSize;
		float IncidenceAngle, ReflectionAngle;
		float TemporaryValue;
		PrismSize = PrismShape.getSize();
		
		
		TempDirection.x = (Movement->x * cos(2 * PI - Rotation * PI / 180) - Movement->y * sin(2 * PI - Rotation * PI / 180));
		TempDirection.y = Movement->x * sin(2 * PI - Rotation * PI / 180) + Movement->y * cos(2 * PI - Rotation * PI / 180);
		TemporaryValue = sqrt(TempDirection.x*TempDirection.x + TempDirection.y*TempDirection.y);
		IncidenceAngle = abs(asin(sin(TempDirection.y / TemporaryValue)));
		ReflectionAngle = asin(sin(IncidenceAngle) / RefractionRate);
		TempDirection.x = TempDirection.x * cos(IncidenceAngle - ReflectionAngle) - TempDirection.y * sin(IncidenceAngle - ReflectionAngle);
		TempDirection.y = TempDirection.x * sin(IncidenceAngle - ReflectionAngle) + TempDirection.y * cos(IncidenceAngle - ReflectionAngle);
		Movement->x = TempDirection.x * cos(Rotation * PI / 180) - TempDirection.y * sin(Rotation * PI / 180);
		Movement->y = TempDirection.x * sin(Rotation * PI / 180) + TempDirection.y * cos(Rotation * PI / 180);
	



}
void Prism::Refraction31Sides(sf::RectangleShape Laser, sf::Vector2f* Movement)
{
	Vector2f TempDirection, PrismSize;
	float IncidenceAngle, ReflectionAngle;
	float TemporaryValue;
	PrismSize = PrismShape.getSize();


	TempDirection.x = (Movement->x * cos(1.5 * PI - Rotation * PI / 180) - Movement->y * sin(1.5 * PI - Rotation * PI / 180));
	TempDirection.y = Movement->x * sin(1.5 * PI - Rotation * PI / 180) + Movement->y * cos(1.5* PI - Rotation * PI / 180);
	TemporaryValue = sqrt(TempDirection.x*TempDirection.x + TempDirection.y*TempDirection.y);
	IncidenceAngle = abs(asin(sin(TempDirection.y / TemporaryValue)));
	ReflectionAngle = asin(sin(IncidenceAngle) / RefractionRate);
	TempDirection.x = TempDirection.x * cos(IncidenceAngle - ReflectionAngle) - TempDirection.y * sin(IncidenceAngle - ReflectionAngle);
	TempDirection.y = TempDirection.x * sin(IncidenceAngle - ReflectionAngle) + TempDirection.y * cos(IncidenceAngle - ReflectionAngle);
	Movement->x = TempDirection.x * cos(0.5*PI + Rotation * PI / 180) - TempDirection.y * sin(0.5*PI + Rotation * PI / 180);
	Movement->y = TempDirection.x * sin(0.5*PI + Rotation * PI / 180) + TempDirection.y * cos(0.5*PI + Rotation * PI / 180);
	

}
