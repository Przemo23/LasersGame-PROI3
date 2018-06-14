#pragma once
#include <SFML/Graphics.hpp>


class Collider
{
	public:
		Collider() {};
		~Collider() {};
		
		 bool CheckCollision(sf::RectangleShape,sf::RectangleShape );
		//bool CheckCollisionGoal(sf::CircleShape);
		//sf::Vector2f GetPosition(Rect) { return body.getPosition(); }
		sf::Vector2f GetHalfSize(sf::RectangleShape sth) { return sth.getSize() / 2.0f; }
		
		
		
		
	



};