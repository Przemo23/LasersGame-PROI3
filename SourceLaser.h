#pragma once
#include "stdafx.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "Sat.h"

class SourceLaser
{

public:
	SourceLaser(int Length, int Height);
	~SourceLaser() {};


	sf::RectangleShape Source;
	sf::RectangleShape Laser;
	sf::Vector2f dirLaser;
	sf::Vector2f baseLaser;
	sf::Vector2f baseDirLaser;
	int collisionTimestamp;
	bool MoveCheck ;
	int CoordinatesX, CoordinatesY;
	bool LaserMove;
	Sat CheckMirrorCollision() { return Sat(Laser); }
	Collider getCollider() { return Collider(Laser); }
};