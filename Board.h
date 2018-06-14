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


class Board
{
public:
	Board() {};
	void Board1();
	~Board() {};

};