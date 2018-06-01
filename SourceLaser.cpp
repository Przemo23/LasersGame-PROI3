#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "SourceLaser.h"
//#include "ResourcePath.hpp" //OSX in Win useless

#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace sf;
SourceLaser::SourceLaser(int Length, int Height)
{
	//Texture SourceTexture;
	//SourceTexture.loadFromFile(resourcePath() + "Source.png");
	Source.setSize(Vector2f(30.0, 30.0));
	Source.setPosition(Length*30.0 + 15.0, Height*30.0 + 15.0);
	Source.setOrigin(Vector2f(15.0, 15.0));
	collisionTimestamp = 0;
	bool MoveCheck = true;
	CoordinatesX = Length;
	CoordinatesY = Height;
	collisionTimestamp = 100;
	//Source.setTexture(&SourceTexture);//must be STATIC, never worked
	Laser.setSize(Vector2f(5.0, 5.0));
	Laser.setFillColor(Color::Red);
	ElapsedTime = clock.getElapsedTime();
	
	LaserMove = true;
	if (Length == 0)
	{
		Source.setRotation(90);
		Laser.setPosition(30.0, Height*30.0 + 15.0);
		dirLaser = Vector2f(5.0f, 0.0f);
	}
	if (Height == 0)
	{
		Source.setRotation(180);
		Laser.setPosition(Length*30.0 + 15.0, 31.0);
		dirLaser = Vector2f(0.0f, 5.0f);
	}
	if (Length>Height&&Height != 0)
	{
		Source.setRotation(270);
		Laser.setPosition(Length*30.0 + 1.0, Height*30.0 + 16.0);
		dirLaser = Vector2f(-5.0f, 0.0f);
	}
	if (Length<Height&&Length != 0)
	{
		Source.setRotation(0);
		Laser.setPosition(Length*30.0 + 15.0, Height*30.0 - 1.0);
		dirLaser = Vector2f(0.0f, -5.0f);
	}
	baseLaser = Laser.getPosition();
	baseDirLaser = dirLaser;
}
