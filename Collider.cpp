#include "stdafx.h"
#include "Collider.h"
#include <cmath>
#include <SFML\Graphics.hpp>

using namespace sf;

bool Collider::CheckCollision(Collider  other)

{

	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x + 14.5;
	float deltaY = otherPosition.y - thisPosition.y + 14.5; 

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);





	if (intersectX < 0.0f && intersectY < 0.0f)// If statement checking if two objects are colliding 
	{

		



		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f) move(intersectX, 0.0f);
			else move(-intersectX, 0.0f);

		}

		else

		{
			if (deltaY > 0.0f) move(0.0f, intersectY);
			else move(0.0f, -intersectY);
		}

		

		return true;

	}

	return false;

}



bool Collider::CheckCollisionGoal(CircleShape Laser) // collisions with the goal

{

	Vector2f LaserPosition = Laser.getPosition();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();





	float deltaX = LaserPosition.x - thisPosition.x;
	float deltaY = LaserPosition.y - thisPosition.y;
	float radius = Laser.getRadius();


	float intersectX = abs(deltaX) - (radius + thisHalfSize.x);
	float intersectY = abs(deltaY) - (radius + thisHalfSize.y);

	if (intersectX <= 0.0f && intersectY <= 0.0f)// If statement checking if two objects are colliding 

	{

		Laser.setPosition(LaserPosition.x, LaserPosition.y);
		return true;

	}

	return false;

}
