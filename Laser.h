#pragma once
#pragma once
#include "stdafx.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "Sat.h"

class Laser
{

	public:
		Laser() {};

		Laser(int Length, int Height);

		~Laser() {};


	
		sf::RectangleShape LaserShape;
		sf::Vector2f dirLaser;
		sf::Vector2f baseLaser;
		sf::Vector2f baseDirLaser;
		int collisionTimestamp;
		bool MoveCheck;
			int CoordinatesX, CoordinatesY;
		bool LaserMove;
		sf::Clock clock;
		sf::Time ElapsedTime;
		Sat CheckMirrorCollision() { return Sat(LaserShape); }
		Collider getCollider() { return Collider(LaserShape); }
};