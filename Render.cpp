#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Render.h"
#include <iostream>
#include "ResourcePath.hpp"

using namespace sf;


int size;
int isEdit;
int syst;

Texture sourceTexture;
Texture goalTexture;
Texture BackgroundTexture;
Texture PrismTexture;
Texture WallTexture;
Texture BoosterTexture;
Texture RoughTexture;



void show::renderAll()
{
    RenderWindow window(VideoMode((size * 30 + 2) * 1, size * 30 + 2, 32), "The Game2", Style::Close | Style::Titlebar);
    while(window.isOpen())
    {
        Event ev;
        while (window.pollEvent( ev ))
        {
            if( ev.type == Event::Closed )
                window.close();
        }
        window.clear();
        
        loadTxtr(syst);
        
        ////
        window.display();
    }
    return;
}

void show::loadTxtr(int a)
{
    if (a==0)
    {
        sourceTexture.loadFromFile("Source.png");
        goalTexture.loadFromFile("Goal.png");
        BackgroundTexture.loadFromFile("Background.png");
        PrismTexture.loadFromFile("Prism.png");
        WallTexture.loadFromFile("Wall.png");
        BoosterTexture.loadFromFile("Booster.png");
        RoughTexture.loadFromFile("Rough.png");
    }
    else
    {
        sourceTexture.loadFromFile(resourcePath() + "Source.png");
        goalTexture.loadFromFile(resourcePath() + "Goal.png");
        BackgroundTexture.loadFromFile(resourcePath() + "Background.png");
        PrismTexture.loadFromFile(resourcePath() + "Prism.png");
        WallTexture.loadFromFile(resourcePath() + "Wall.png");
        BoosterTexture.loadFromFile(resourcePath() + "Booster.png");
        RoughTexture.loadFromFile(resourcePath() + "Rough.png");
    }
}

/*void show::showGame()
{
    
}

void show::controlEvent()
{
    
}
*/
