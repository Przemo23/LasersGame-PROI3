#include "stdafx.h" //OSX in OSX useless
/*#include <SFML/Graphics.hpp> //OSX "/" UNIX vs "\" Windows
					 //#include <SFML/Color.hpp>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include "SourceLaser.h"
#include "Goal.h"
#include "Mirror.h"
#include "Sat.h"
#include <chrono>
#include "Prism.h"
#include "Laser.h"
#include "Booster.h"
#include "RoughObject.h"
#include "Wall.h"*/
#include "Board.h"
#define PI 3.14159265
					 //#include "ResourcePath.hpp" //OSX in Win useless

	using namespace sf;

	
/*bool IfWon(std::vector<Goal> Goals)
{
	for (int i = 0; i < Goals.size(); i++)
	{
		if (Goals[i].GoalSaturation != Goals[i].PowerCap) return false;

	}
	return true;
}*/




int main()
{
	Board sth=Board();
	sth.Board1();
	return 0;
}
