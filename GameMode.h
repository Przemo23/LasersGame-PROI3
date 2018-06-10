#pragma once
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "Sat.h"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include "SourceLaser.h"
#include "Goal.h"
#include "Mirror.h"
#include <chrono>

using namespace sf;
class Game
{
	public:
	Game();
	~Game();
	
	void WindowDisplay();
	
	void GameMode(Event e);
	void EditMode(Event e);
	//SourceLaser initializeSource(int K, int L);
	
	std::vector<Mirror> Mirrors;
	std::vector<SourceLaser> Sources;
	int size = 30;
	//main matrix of data
	enum object { nth, source, mirror, goal };
	object matrix[30][30];
	//matrix2[size][size];
	int i, j;
	int k = 0, l = 0; //edited ones / coursor
	bool isEdit = 0;
	bool GoalCheck = false;
	Goal LaserGoal;
	int win = 0;
	double normalAngle;
	int now;
	Vector2f TempDirection;
	double CollisionAngle;



};
