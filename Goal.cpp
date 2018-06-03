#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Goal.h"
//#include "ResourcePath.hpp" //OSX in Win useless


using namespace sf;
Goal::Goal(int Length, int Height)
{
	//Texture goalTexture;
	//goalTexture.loadFromFile(resourcePath() + "Source.png");
	GoalShape.setSize(Vector2f(30.0, 30.0));
	GoalShape.setPosition(Length*30.0 + 1.0, Height*30.0 + 1.0);
	//GoalShape.setFillColor(Color::Green);
	GoalShape.setOrigin(Vector2f(0.0, 0.0));
	//GoalShape.setTexture(&goalTexture);
}