#include "stdafx.h" //OSX in OSX useless
#include <SFML/Graphics.hpp> //OSX "/" UNIX vs "\" Windows
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
#include "Board.h"
#include "Keyboard1.h"

using namespace sf;

SourceLaser initializeSource(int K, int L)
{
    SourceLaser Created = SourceLaser(K, L);
    
    return Created;
}

Board::Board(int a)
{
    std::vector<Mirror> Mirrors;
    std::vector<SourceLaser> Sources;
    std::vector<Prism> Prisms;
    std::vector<Laser> Lasers;
    std::vector<Wall> Walls;
    std::vector<Booster> Boosters;
    std::vector<RoughObject> RObjects;
    
    int size = a;
    //main matrix of data
    enum object { nth, source, mirror, goal,prism,rough,wall,booster };
    enum object matrix[size][size];
    //matrix2[size][size];
    int i, j;
    int k = 0, l = 0; //edited ones / coursor
    int isEdit = 0;
    bool GoalCheck = false;
    Clock clock;
    int win = 0;
    double MirrorRotation;
    
    Time ElapsedTime;
    Vector2f TempDirection;
    
    for (i = 0; i<size; i++)
        for (j = 0; j<size; j++)
            matrix[i][j] = nth;
    
    Goal LaserGoal;
    
    RenderWindow window(VideoMode((size * 30 + 2) * 1, size * 30 + 2, 32), "The Game", Style::Close | Style::Titlebar);
    window.clear();
    
    Texture sourceTexture;
    sourceTexture.loadFromFile(resourcePath() + "Source.png"); //OSX if(windows) erease "resourcePath() + "
    //Texture mirrorTexture;
    //mirrorTexture.loadFromFile( "resourcePath() + Mirror.png"); //OSX if(windows) erease "resourcePath() + "
    Texture goalTexture;
    goalTexture.loadFromFile(resourcePath() + "Goal.png");
    Texture BackgroundTexture;
    BackgroundTexture.loadFromFile(resourcePath() + "Background.png");
    Texture PrismTexture;
    PrismTexture.loadFromFile(resourcePath() + "Prism.png");
    Texture WallTexture;
    WallTexture.loadFromFile(resourcePath() + "Wall.png");
    Texture BoosterTexture;
    BoosterTexture.loadFromFile(resourcePath() + "Booster.png");
    Texture RoughTexture;
    RoughTexture.loadFromFile(resourcePath() +  "Rough.png");
    
    window.clear();
    
    while (window.isOpen())
    {
        
        Event e;
        
        while (window.pollEvent(e))
        {
            {
                if (e.type == Event::Closed)
                    window.close();
                
                //switching between modes
                if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::E))
                {
                    isEdit = ((isEdit + 1) % 2);
                    win = 0;
                    for (int i = 0; i < Lasers.size(); i++)
                    {
                        Lasers[i].LaserShape.setPosition(Lasers[i].baseLaser);
                        Lasers[i].dirLaser = Lasers[i].baseDirLaser;
                    }
                }
                
                //coursor moving
                if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Right))
                    if (k<size - 1)
                        k++;
                if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Left))
                    if (k>0)
                        k--;
                if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Down))
                    if (l<size - 1)
                        l++;
                if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Up))
                    if (l>0)
                        l--;
                
                //edit mode
                if (isEdit == 1)
                {
                    //source insertion
                    if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::S))
                        if (((k == 0 || (k == size - 1)) && (l != 0 && l != size - 1)) || ((l == 0 || (l == size - 1)) && (k != 0 && k != size - 1)))
                        {
                            if (matrix[k][l] != source)
                            {
                                Sources.push_back(initializeSource(k, l));
                                matrix[k][l] = source;
                                Lasers.push_back(Laser(k, l));
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
                    //Prism insertion
                    if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::U))
                    {
                        if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
                        {
                            
                            
                            matrix[k][l] = prism;
                            Prisms.push_back(Prism(k, l));
                            Prisms.back().PrismShape.setTexture(&PrismTexture);
                        }
                        
                    }
                    //Booster insertion
                    if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::B))
                    {
                        if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
                        {
                            
                            matrix[k][l] = booster;
                            Boosters.push_back(Booster(k, l));
                            
                            Boosters.back().BoosterShape.setTexture(&BoosterTexture);
                        }
                        
                    }
                    //RoughObject insertion
                    if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::R))
                    {
                        if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
                        {
                            
                            matrix[k][l] = rough;
                            RObjects.push_back(RoughObject(k, l));
                            
                            RObjects.back().RoughObjectShape.setTexture(&RoughTexture);
                        }
                        
                    }
                    //Wall insertion
                    if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::W))
                    {
                        if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
                        {
                            
                            matrix[k][l] = wall;
                            Walls.push_back(Wall(k, l));
                            
                            Walls.back().WallShape.setTexture(&WallTexture);
                        }
                        
                    }
                    //goal or source deletion
                    if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::L))
                    {
                        //Booster deletion
                        if (matrix[k][l] == booster)
                        {
                            for (int i = 0; i < Boosters.size(); i++)
                            {
                                if (k == Boosters[i].CoordinatesX && l == Boosters[i].CoordinatesY)
                                {
                                    Boosters.erase(Boosters.begin() + i);
                                    matrix[k][l] = nth;
                                }
                            }
                        }
                        
                        //Wall deletion
                        if (matrix[k][l] == wall)
                        {
                            for (int i = 0; i < Walls.size(); i++)
                            {
                                if (k == Walls[i].CoordinatesX && l == Walls[i].CoordinatesY)
                                {
                                    Walls.erase(Walls.begin() + i);
                                    matrix[k][l] = nth;
                                }
                            }
                        }
                        
                        
                        //Prism deletion
                        if (matrix[k][l] == prism)
                        {
                            for (int i = 0; i < Prisms.size(); i++)
                            {
                                if (k == Prisms[i].CoordinatesX && l == Prisms[i].CoordinatesY)
                                {
                                    Prisms.erase(Prisms.begin() + i);
                                    matrix[k][l] = nth;
                                }
                            }
                        }
                        
                        
                        //RoughObject deletion
                        if (matrix[k][l] == rough)
                        {
                            for (int i = 0; i < RObjects.size(); i++)
                            {
                                if (k == RObjects[i].CoordinatesX && l == RObjects[i].CoordinatesY)
                                {
                                    RObjects.erase(RObjects.begin() + i);
                                    matrix[k][l] = nth;
                                }
                            }
                        }
                        
                        
                        
                        
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
                                
                                matrix[k][l] = nth;
                                Mirrors.erase(Mirrors.begin() + i);
                            }
                        }
                    }
                }
            }

        }
        
        
        
        //background0 rendering
        sf::RectangleShape rectangle(sf::Vector2f((size * 30 + 2) * 1, size * 30 + 2));
        rectangle.setFillColor(Color::Black);
        window.draw(rectangle);
        
        //background1 rendering
        for (i = 0; i<size; i++)
            for (j = 0; j<size; j++)
            {
                sf::RectangleShape rectangle(sf::Vector2f(30.0f, 30.0f));
                rectangle.setPosition(i*30.0 + 1.0, j*30.0 + 1.0);
                rectangle.setTexture(&BackgroundTexture);
                window.draw(rectangle);
            }
        
        
        
        
        
        
        for (int i = 0; i <Lasers.size(); i++)
        {
            if (GoalCheck == true)
            {
                if (Lasers[i].getCollider().CheckCollision(LaserGoal.getCollider()) == true)
                {
                    Lasers[i].MoveCheck = false;
                    win++;
                    //Sources[i].Laser.setFillColor(sf::Color::Blue);
                }
            }
        }
        
        for (int i = 0; i < Lasers.size(); i++) // Mirror collisions
        {
            for (int k = 0; k < Mirrors.size(); k++)
            {
                Time Interval = Lasers[i].getTime();
                if (true == Lasers[i].CheckMirrorCollision().CheckSatCollision(Mirrors[k].MirrorShape)&& Interval > Lasers[i].collisionTimestamp)
                {
                    
                    Lasers[i].restartTime();
                    
                    
                    MirrorRotation = Mirrors[k].MirrorShape.getRotation();
                    /*Now I'm checking with which side of the mirror the laser collides.
                     Depending on the result there will be different algorythms used
                     to determine the direction of the laser.
                     */
                    
                    if (Lasers[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape) == 1 || Lasers[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape) == 3) // Initial top or bottom side of the mirror
                    {
                        Lasers[i].CheckMirrorCollision().MirrorCollision13(&Lasers[i].dirLaser,MirrorRotation);
                        
                    }
                    if (Lasers[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape) == 2 || Lasers[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape) == 4)// Initial right or left side of the mirror
                    {
                        Lasers[i].CheckMirrorCollision().MirrorCollision24(&Lasers[i].dirLaser,MirrorRotation);
                    }
                    
                    
                    
                    
                    
                    
                }
            }
        }
        for (int i = 0; i < Lasers.size(); i++) // Załamywanie światła
        {
            
            for (int k = 0; k < Prisms.size(); k++)
            {
                Time Interval = Lasers[i].getTime();
                if (true == Lasers[i].CheckMirrorCollision().CheckSatCollision(Prisms[k].PrismShape) && Interval>Lasers[i].collisionTimestamp )
                {
                    Lasers[i].restartTime();
                    if (Lasers[i].CheckMirrorCollision().CheckWhichAxis(Prisms[k].PrismShape) == 2 || Lasers[i].CheckMirrorCollision().CheckWhichAxis(Prisms[k].PrismShape) == 4)// Initial right or left side of the mirror
                    {
                        
                        Prisms[k].Refraction42Sides( &Lasers[i].dirLaser);
                        if (Lasers[i].LaserShape.getFillColor() == sf::Color::White)
                        {
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Red, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size()-1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Yellow, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Green, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Blue, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Cyan, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Magenta, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.erase(Lasers.begin() + i);
                        }
                    }
                    if (Lasers[i].CheckMirrorCollision().CheckWhichAxis(Prisms[k].PrismShape) == 1 || Lasers[i].CheckMirrorCollision().CheckWhichAxis(Prisms[k].PrismShape) == 3)
                    {
                        Prisms[k].Refraction31Sides( &Lasers[i].dirLaser);
                        if (Lasers[i].LaserShape.getFillColor() == sf::Color::White)
                        {
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Red, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Yellow, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Green, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Blue, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Cyan, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Magenta, Lasers[i].dirLaser,1));
                            Lasers[Lasers.size() - 1].LaserIncurvating();
                            Lasers.erase(Lasers.begin() + i);
                            
                        }
                        
                    }
                }
            }
        }
        for (int i = 0; i < Lasers.size(); i++) // Dispersion on the RoughObject
        {
            
            for (int k = 0; k < RObjects.size(); k++)
            {
                Time Interval = Lasers[i].getTime();
                if (true == Lasers[i].CheckMirrorCollision().CheckSatCollision(RObjects[k].RoughObjectShape) && Interval>Lasers[i].collisionTimestamp)
                {
                    Lasers[i].restartTime();
                    if (Lasers[i].CheckMirrorCollision().CheckWhichAxis(RObjects[k].RoughObjectShape) == 2 || Lasers[i].CheckMirrorCollision().CheckWhichAxis(RObjects[k].RoughObjectShape) == 4)// Initial right or left side of the Object
                    {
                        
                        Lasers[i].CheckMirrorCollision().MirrorCollision24(&Lasers[i].dirLaser, RObjects[k].RoughObjectShape.getRotation());
                        if (Lasers[i].LaserShape.getFillColor() == sf::Color::White) Lasers[i].LaserShape.setFillColor(RObjects[k].FillingColor);
                        int n = 5;// Number of lasers that you want to create
                        for ( int a = 0; a < n; a++) Lasers.push_back(Laser(Lasers[i].LaserShape.getPosition(), Lasers[i].LaserShape.getFillColor(), RObjects[k].Dispersion(Lasers[i].dirLaser) , n));
                        Lasers.erase(Lasers.begin() + i);
                    }
                    if (Lasers[i].CheckMirrorCollision().CheckWhichAxis(RObjects[k].RoughObjectShape) == 1 || Lasers[i].CheckMirrorCollision().CheckWhichAxis(RObjects[k].RoughObjectShape) ==3)// Initial right or left side of the object
                    {
                        Lasers[i].CheckMirrorCollision().MirrorCollision13(&Lasers[i].dirLaser, RObjects[k].RoughObjectShape.getRotation());
                        if (Lasers[i].LaserShape.getFillColor() == sf::Color::White) Lasers[i].LaserShape.setFillColor(RObjects[k].FillingColor);
                        int n = 5;// Number of lasers that you want to create
                        for ( int a = 0; a < n; a++) Lasers.push_back(Laser(Lasers[i].LaserShape.getPosition(), Lasers[i].LaserShape.getFillColor(), RObjects[k].Dispersion(Lasers[i].dirLaser), n));
                        
                        Lasers.erase(Lasers.begin() + i);
                        
                        
                    }
                }
            }
        }
        for (int i = 0; i < Lasers.size(); i++) // Wall collisions
        {
            
            for (int k = 0; k < Walls.size(); k++)
            {
                if (true == Lasers[i].CheckMirrorCollision().CheckSatCollision(Walls[k].WallShape))
                    Lasers.erase(Lasers.begin() + i);
            }
        }
        for (int i = 0; i < Lasers.size(); i++) // Booster collisions
        {
            
            for (int k = 0; k < Boosters.size(); k++)
            {
                Time Interval = Lasers[i].getTime();
                if (true == Lasers[i].CheckMirrorCollision().CheckSatCollision(Boosters[k].BoosterShape) && Interval > Lasers[i].collisionTimestamp)
                {
                    Lasers[i].restartTime();
                    Boosters[k].Boost(&Lasers[i].Power);
                    std::cout << "Love";
                }
            }
        }
        //movement of laser beams
        for (int i = 0; i < Lasers.size(); i++)
        {
            
            
            if (Lasers[i].MoveCheck == true) Lasers[i].LaserShape.move(Lasers[i].dirLaser.x, Lasers[i].dirLaser.y );
            
        }
        for (int i = 0; i < Sources.size(); i++)
        {
            Sources[i].Source.setTexture(&sourceTexture);
            window.draw(Sources[i].Source);
            
            
        }
        
        
        
        for (int i = 0; i < Prisms.size(); i++)
        {
            
            window.draw(Prisms[i].PrismShape);
            
        }
        for (int i = 0; i < Lasers.size(); i++)
        {
            window.draw(Lasers[i].LaserShape);
            
        }
        for (int i = 0; i < RObjects.size(); i++)
        {
            window.draw(RObjects[i].RoughObjectShape);
            
        }
        for (int i = 0; i < Walls.size(); i++)
        {
            window.draw(Walls[i].WallShape);
            
        }
        for (int i = 0; i < Boosters.size(); i++)
        {
            window.draw(Boosters[i].BoosterShape);
            
        }
        for (int i = 0; i < Mirrors.size(); i++)
        {
            
            window.draw(Mirrors[i].MirrorShape);
            
        }
        
        
        if (GoalCheck == true)
        {
            LaserGoal.GoalShape.setTexture(&goalTexture);
            window.draw(LaserGoal.GoalShape);
        }
        
        
        //refreshing coursor
        if ((time(0) % 2 == 0))
        {
            sf::RectangleShape rectangle(sf::Vector2f(30.0f, 30.0f));
            rectangle.setPosition(k*30.0 + 1.0, l*30.0 + 1.0);
            if (isEdit == 1)
                rectangle.setFillColor(Color::Red);
            else
                rectangle.setFillColor(Color::White);
            window.draw(rectangle);
        }
        if (win == Lasers.size() && Lasers.size() != 0 && isEdit == 0)
        {
            std::cout << "DUUUUUUUUUUUUUPAAAAAAA XD";
            window.close();
        }
        //refreshing the position of laser beams
        
        
        for (int i = 0; i < Lasers.size(); i++)
        {
            Lasers[i].LaserShape.setPosition(Lasers[i].LaserShape.getPosition());
            //Lasers[i].dirLaser = Lasers[i].baseDirLaser;
            
            Lasers[i].MoveCheck = true;
        }
        
        //std::cout << " " << win;
        
        window.display();
    }
}

