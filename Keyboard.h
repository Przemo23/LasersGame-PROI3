#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
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
#include "Board.h"

using namespace sf;

class Keyboard1 : public Board
{
public:
    Keyboard1 () {};
    Keyboard1 (Event e);
    ~Keyboard1 () {};
};
