#pragma once
#include "stdafx.h" //OSX in OSX useless
#include <SFML/Graphics.hpp> //OSX "/" UNIX vs "\" Windows
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
#include "Wall.h"
#define PI 3.14159265
#include "ResourcePath.hpp" //OSX in Win useless


class Board
{
public:
	Board() {};
	Board(int a);
	~Board() {};
    
    sf::Window window;
    int isEdit;
    int win;
    


};
