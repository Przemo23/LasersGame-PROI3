#include "stdafx.h"
#include <SFML/Graphics.hpp>
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
	
	CoordinatesX = Length;
	CoordinatesY = Height;
	
	//Source.setTexture(&SourceTexture);//must be STATIC, never worked
	
	
	
	if (Length == 0)
	{
		Source.setRotation(90);
		
	}
	if (Height == 0)
	{
		Source.setRotation(180);
		
	}
	if (Length>Height&&Height != 0)
	{
		Source.setRotation(270);
		
	}
	if (Length<Height&&Length != 0)
	{
		Source.setRotation(0);
		
	}
	
}
