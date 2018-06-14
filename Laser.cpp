//#include "ResourcePath.hpp" //OSX in Win useless
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include "Laser.h"
#include "Sat.h"

#define PI 3.14159265
using namespace sf;
/*Laser& Laser::operator=(const Laser & Another)
{
	//this->dirLaser = Another.dirLaser;

	return *this;
	// TODO: tu wstawiæ instrukcjê return
}*/
Laser::Laser(int Length, int Height)
{
	//Texture SourceTexture;
	//SourceTexture.loadFromFile(resourcePath() + "Source.png");
	
	
	
	CoordinatesX = Length;
	CoordinatesY = Height;
	collisionTimestamp = microseconds(500000);
	//Source.setTexture(&SourceTexture);//must be STATIC, never worked
	LaserShape.setSize(Vector2f(5.0, 5.0));
	Power = 100.0;
	LaserShape.setFillColor(Color::White);
	ElapsedTime = clock.getElapsedTime();

	
	if (Length == 0)
	{
		
		LaserShape.setPosition(30.0, Height*30.0 + 15.0);
		dirLaser = Vector2f(10.0f, 0.0f);
	}
	if (Height == 0)
	{
		
		LaserShape.setPosition(Length*30.0 + 15.0, 31.0);
		dirLaser = Vector2f(0.0f, 10.0f);
	}
	if (Length>Height&&Height != 0)
	{
		
		LaserShape.setPosition(Length*30.0 + 1.0, Height*30.0 + 16.0);
		dirLaser = Vector2f(-10.0f, 0.0f);
	}
	if (Length<Height&&Length != 0)
	{
		
		LaserShape.setPosition(Length*30.0 + 15.0, Height*30.0 - 1.0);
		dirLaser = Vector2f(0.0f, -10.0f);
	}
	
}

Laser::Laser(sf::Vector2f Position, sf::Color FillingColor, sf::Vector2f Movement, int number)
{
	
	
	Power = 100/number;
	collisionTimestamp = microseconds(500000);
	//Source.setTexture(&SourceTexture);//must be STATIC, never worked
	LaserShape.setPosition(Position.x, Position.y);
	LaserShape.setSize(Vector2f(5.0, 5.0));
	LaserShape.setFillColor(FillingColor);
	ElapsedTime = clock.getElapsedTime();

	
	dirLaser.x = Movement.x;
	dirLaser.y = Movement.y;
	//dirLaser = LaserIncurvating(Movement, FillingColor);
	
	clock.restart();

	
}
sf::Time Laser::getTime()
{
	ElapsedTime = clock.getElapsedTime();
	return ElapsedTime;
}
void Laser::restartTime()
{
	clock.restart();
}
void Laser::LaserIncurvating()
{
	double AngleR; //Angle which will defy how much the new laser incurvates
	sf::Vector2f TempDirection;
	sf::Color FillingColor = LaserShape.getFillColor();
	if (FillingColor == sf::Color::Red) AngleR = -10.0;
	if (FillingColor == sf::Color::Yellow) AngleR = -6.0;
	if (FillingColor == sf::Color::Green)AngleR = -2.0;
	if (FillingColor == sf::Color::Blue)AngleR =2.0;
	if (FillingColor == sf::Color::Cyan)AngleR = 6.0;
	if (FillingColor == sf::Color::Magenta)AngleR = 10.0;
	double Rotation = atan(tan(dirLaser.y / dirLaser.x)) + 90;
	if (Rotation >= 360) Rotation -= 360;
	AngleR *= PI / 180;
	TempDirection.x = dirLaser.x;
	TempDirection.y = dirLaser.y;
	dirLaser.x = TempDirection.x*cos(AngleR) - TempDirection.y*sin(AngleR);
	dirLaser.y = TempDirection.x*sin(AngleR) + TempDirection.y*cos(AngleR);
	
}

bool Laser::DistanceToObject(sf::RectangleShape Object)
{
	Vector2f LaserPosition, ObjectPosition;
	float Distance,MaxDistance;
	ObjectPosition = Object.getPosition();
	LaserPosition = LaserShape.getPosition();
	LaserPosition.x += 2.5;
	LaserPosition.y += 2.5;
	Distance = sqrt((LaserPosition.x  - ObjectPosition.x)*(LaserPosition.x - ObjectPosition.x) + (LaserPosition.y - ObjectPosition.y)*(LaserPosition.y - ObjectPosition.y));
	MaxDistance = sqrt(LaserPosition.x*LaserPosition.x + LaserPosition.y*LaserPosition.y) / 2 + sqrt(ObjectPosition.x*ObjectPosition.x + ObjectPosition.y*ObjectPosition.y) / 2;
	if (MaxDistance < Distance) return false;
	else return true;
}
