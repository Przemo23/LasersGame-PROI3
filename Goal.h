#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Collider.h"


class Goal
{
public:
	Goal() {};
	Goal(int Lenght, int Height);
	~Goal() {};

	Collider getCollider() { return Collider(GoalShape); }

	sf::RectangleShape GoalShape;

};
