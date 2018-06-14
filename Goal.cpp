#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Goal.h"
//#include "ResourcePath.hpp" //OSX in Win useless


using namespace sf;
Goal::Goal(int Length, int Height,sf::Color color,int i)
{
	
	CoordinatesX = Length;
	CoordinatesY = Height;
	
	PowerCap = 10000.0;
	GoalSaturation = 0.0;
	
	GoalShape.setSize(Vector2f(30.0, 30.0));
	GoalShape.setPosition(Length*30.0 + 16.0, Height*30.0 + 16.0);
	GoalShape.setOrigin(Vector2f(15.0, 15.0));
	
	Color = color;
	
	PowerBar.setSize(Vector2f(0.0, 20.0));
	PowerBar.setFillColor(sf::Color::Magenta);
	PowerBar.setPosition(650.0, 40.0*i);
	
	PowerBackground.setSize(Vector2f(100.0, 20.0));
	PowerBackground.setPosition(650.0, 40.0*i);
	PowerBackground.setFillColor(sf::Color::Black);
	PowerBackground.setOutlineThickness(1.0);
	PowerBackground.setOutlineColor(sf::Color::Red);
	
}

void Goal::UpdateBar()
{
	
	PowerBar.setSize(Vector2f(100.0 * (GoalSaturation / PowerCap), 20.0));
}
