#include "stdafx.h"
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
#include <SFML\Graphics.hpp>
#include "GameMode.h"

using namespace sf;



/*SourceLaser initializeSource(int K, int L)
{
	SourceLaser Created = SourceLaser(K, L);

	return Created;
}*/

void Game::GameMode(Event e)
{
	if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Right))
		if (k < size - 1)	 k++;
	if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Left))
		if (k > 0)	 k--;
	if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Down))
		if (l < size - 1)		l++;
	if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Up))
		if (l > 0)	l--;



	//game mode
	if (isEdit == 0)
	{
		//mirror insertion
		if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::M))
			if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
			{
				if (matrix[k][l] == nth)
				{
					Mirrors.push_back(Mirror(k, l));
					matrix[k][l] = mirror;
				}
			}
		//mirror rotation to the right
		if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::P) && matrix[k][l] == mirror)
		{
			for (int i = 0; i < Mirrors.size(); i++)
			{
				if (k == Mirrors[i].CoordinatesX && l == Mirrors[i].CoordinatesY)
				{
					Mirrors[i].MirrorShape.setRotation(Mirrors[i].MirrorShape.getRotation() + 3);
				}
			}
		}
		//mirror rotation to the left

		if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::O) && matrix[k][l] == mirror)
		{
			for (int i = 0; i < Mirrors.size(); i++)
			{
				if (k == Mirrors[i].CoordinatesX && l == Mirrors[i].CoordinatesY)
				{
					Mirrors[i].MirrorShape.setRotation(Mirrors[i].MirrorShape.getRotation() - 3);
				}
			}

		}

		//mirror deletion
		if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::L) && matrix[k][l] == mirror)
		{
			for (int i = 0; i < Mirrors.size(); i++)
			{
				if (k == Mirrors[i].CoordinatesX && l == Mirrors[i].CoordinatesY)
				{
					Mirrors.erase(Mirrors.begin() + i);
					matrix[k][l] = nth;
				}
			}
		}



		//movement of laser beams
		for (int i = 0; i < Sources.size(); i++)
		{
			if (Sources[i].MoveCheck == true) Sources[i].Laser.move(Sources[i].dirLaser);
		}
	}
}
void Game::EditMode(Event e)
{

	//source insertion
	if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::S))
		if (((k == 0 || (k == size - 1)) && (l != 0 && l != size - 1)) || ((l == 0 || (l == size - 1)) && (k != 0 && k != size - 1)))
		{
			if (matrix[k][l] != source)
			{
				//Sources.push_back(initializeSource(k, l));
				matrix[k][l] = source;
			}
		}

	//goal insertion
	if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::G) && (GoalCheck == false))
	{
		if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
		{
			LaserGoal = Goal(k, l);
			GoalCheck = true;
			matrix[k][l] = goal;
		}

	}

	//goal or source deletion
	if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::L))
	{
		//source deletion
		if (matrix[k][l] == source)
		{
			for (int i = 0; i < Sources.size(); i++)
			{
				if (k == Sources[i].CoordinatesX && l == Sources[i].CoordinatesY)
				{
					Sources.erase(Sources.begin() + i);
					matrix[k][l] = nth;
				}
			}
		}
		//goal deletion
		if (matrix[k][l] == goal)
		{
			matrix[k][l] = nth;
			GoalCheck = false;
		}
	}




}

