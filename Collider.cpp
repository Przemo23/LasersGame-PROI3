#include "stdafx.h"
#include "Collider.h"
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;

/*bool Collider::CheckCollision(RectangleShape Goal,RectangleShape Laser)

{

	Vector2f otherPosition = Laser.getPosition();
	Vector2f otherHalfSize = Laser.GetHalfSize();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x + 14.5;
	float deltaY = otherPosition.y - thisPosition.y + 14.5; 

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);







	return false;

}*/



bool Collider::CheckCollision(sf::RectangleShape Laser,sf::RectangleShape Goal)
{
	Vector2f LaserPosition = Laser.getPosition();
	Vector2f LaserHalfSize = GetHalfSize(Laser);
	Vector2f GoalPosition = Goal.getPosition(); 
	Vector2f GoalHalfSize = GetHalfSize(Goal);
	LaserPosition.x += 2.5;
	LaserPosition.y += 2.5;

	float deltaX = LaserPosition.x - GoalPosition.x;
	float deltaY = LaserPosition.y - GoalPosition.y;

	float intersectX = abs(deltaX) - (LaserHalfSize.x + GoalHalfSize.x);
	float intersectY = abs(deltaY) - (LaserHalfSize.y + GoalHalfSize.y);

	if (intersectX <= 0 && intersectY <= 0) return true;

	return false;
}

/*bool Collider::CheckCollisionGoal(CircleShape Laser) // collisions with the goal

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

}*/
