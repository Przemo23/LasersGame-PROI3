#pragma once
#include "stdafx.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Sat.h"
#include "SourceLaser.h"

class Prism
{

public:
	Prism() {};
	Prism(int, int);
	
	
	~Prism() {};
	int CoordinatesX, CoordinatesY;
	
	void Refraction42Sides( sf::Vector2f*); // It will get the Laser and its movement vector as parametrs
	//Sat CheckPrismCollision() { return Sat(Laser); }
	void Refraction31Sides( sf::Vector2f * Movement);
	
	float RefractionRate;

	sf::RectangleShape PrismShape;
	//sf::LineStrip PrismOutline;


};