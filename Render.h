#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"



class show
{
public:
    show(){};
    int isEdit;
    int size;
    int syst;
    /*
    int size;
    void showBasic(int size);
    ~show(){};
    int isEdit;*/
    void renderAll();
private:
    void showGame();
    void showSet();
    void loadTxtr(int system);
    //sf::Window window;

    
    

};
