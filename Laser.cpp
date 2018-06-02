//#include "ResourcePath.hpp" //OSX in Win useless
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include "Laser.h"

using namespace sf;
Laser::Laser(int Length, int Height)
{
	//Texture SourceTexture;
	//SourceTexture.loadFromFile(resourcePath() + "Source.png");
	
	collisionTimestamp = 0;
	bool MoveCheck = true;
	CoordinatesX = Length;
	CoordinatesY = Height;
	collisionTimestamp = 100;
	//Source.setTexture(&SourceTexture);//must be STATIC, never worked
	LaserShape.setSize(Vector2f(5.0, 5.0));
	LaserShape.setFillColor(Color::Red);
	ElapsedTime = clock.getElapsedTime();

	LaserMove = true;
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
