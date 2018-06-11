#pragma once
#pragma once
#include "stdafx.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Sat.h"

class Laser
{

	public:
		Laser() {};

		Laser(int Length, int Height);
		Laser(sf::Vector2f, sf::Color, sf::Vector2f,int);
		~Laser() {};


		
		sf::RectangleShape LaserShape;
		sf::Vector2f dirLaser;
		sf::Vector2f baseLaser;
		sf::Vector2f baseDirLaser;
		sf::Time collisionTimestamp;
		bool MoveCheck;
			int CoordinatesX, CoordinatesY;
		
		sf::Time getTime();
		void restartTime();
		int Power;
		sf::Clock clock;
		sf::Time ElapsedTime;
		void LaserIncurvating();
		bool DistanceToObject(sf::RectangleShape);
		Sat CheckMirrorCollision() { return Sat(LaserShape); }
		Collider getCollider() { return Collider(LaserShape); }
};
