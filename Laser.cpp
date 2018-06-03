//#include "ResourcePath.hpp" //OSX in Win useless
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include "Laser.h"
#define PI 3.14159265
using namespace sf;
Laser::Laser(int Length, int Height)
{
	//Texture SourceTexture;
	//SourceTexture.loadFromFile(resourcePath() + "Source.png");
	
	
	bool MoveCheck = true;
	CoordinatesX = Length;
	CoordinatesY = Height;
	collisionTimestamp = microseconds(500000);
	//Source.setTexture(&SourceTexture);//must be STATIC, never worked
	LaserShape.setSize(Vector2f(5.0, 5.0));
	
	LaserShape.setFillColor(Color::White);
	ElapsedTime = clock.getElapsedTime();

	
	if (Length == 0)
	{
		
		LaserShape.setPosition(30.0, Height*30.0 + 15.0);
		dirLaser = Vector2f(5.0f, 0.0f);
	}
	if (Height == 0)
	{
		
		LaserShape.setPosition(Length*30.0 + 15.0, 31.0);
		dirLaser = Vector2f(0.0f, 5.0f);
	}
	if (Length>Height&&Height != 0)
	{
		
		LaserShape.setPosition(Length*30.0 + 1.0, Height*30.0 + 16.0);
		dirLaser = Vector2f(-5.0f, 0.0f);
	}
	if (Length<Height&&Length != 0)
	{
		
		LaserShape.setPosition(Length*30.0 + 15.0, Height*30.0 - 1.0);
		dirLaser = Vector2f(0.0f, -5.0f);
	}
	baseLaser = LaserShape.getPosition();
	baseDirLaser = dirLaser;
}

Laser::Laser(sf::Vector2f Position, sf::Color FillingColor, sf::Vector2f Movement)
{
	
	bool MoveCheck = true;
	
	collisionTimestamp = microseconds(500000);
	//Source.setTexture(&SourceTexture);//must be STATIC, never worked
	LaserShape.setPosition(Position.x, Position.y);
	LaserShape.setSize(Vector2f(5.0, 5.0));
	LaserShape.setFillColor(FillingColor);
	ElapsedTime = clock.getElapsedTime();

	
	
	dirLaser = LaserIncurvating(Movement, FillingColor);
	baseDirLaser = dirLaser;
	baseLaser = Vector2f(500.0, 500.0);
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
sf::Vector2f Laser::LaserIncurvating(sf::Vector2f Movement, sf::Color FillingColor)
{
	double AngleR; //Angle which will defy how much the new laser incurvates
	
	if (FillingColor == sf::Color::Red) AngleR = -5.0;
	if (FillingColor == sf::Color::Yellow) AngleR = -3.0;
	if (FillingColor == sf::Color::Green)AngleR = -1.0;
	if (FillingColor == sf::Color::Blue)AngleR = 1.0;
	if (FillingColor == sf::Color::Cyan)AngleR = 3.0;
	if (FillingColor == sf::Color::Magenta)AngleR = 5.0;
	double Rotation = atan(tan(Movement.y / Movement.x)) + 90;
	if (Rotation >= 360) Rotation -= 360;
	AngleR *= PI / 180;
	
	Movement.x = Movement.x*cos(AngleR) - Movement.y*sin(AngleR);
	Movement.y = Movement.y*sin(AngleR) + Movement.x*cos(AngleR);
	return Movement;
}
