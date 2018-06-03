#pragma once
#include <SFML/Graphics.hpp>


class Collider
{
	public:
		Collider(sf::RectangleShape &body) : body(body) {};
		
		~Collider() {};

		bool CheckCollision(Collider );
		bool CheckCollisionGoal(sf::CircleShape);
		sf::Vector2f GetPosition() { return body.getPosition(); }
		sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
		
		
		
		void move(float dx, float dy) { body.move(dx, dy); }
	private:
		sf::RectangleShape& body;



};