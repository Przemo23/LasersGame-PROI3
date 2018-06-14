#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Collider.h"


class Goal
{
public:
	Goal() {};
	Goal(int Lenght, int Height, sf::Color,int);
	~Goal() {};
	float PowerCap;
	sf::Color Color;
	int CoordinatesX, CoordinatesY;

	float GoalSaturation;
	sf::RectangleShape PowerBar;
	sf::RectangleShape PowerBackground;
	//Collider getCollider() { return Collider(GoalShape); }
	void UpdateBar();
	sf::RectangleShape GoalShape;

};