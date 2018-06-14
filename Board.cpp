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
#include "Board.h"
#define PI 3.14159265
//#include "ResourcePath.hpp" //OSX in Win useless

using namespace sf;


bool IfWon(std::vector<Goal> Goals)
{
	for (int i = 0; i < Goals.size(); i++)
	{
		if (Goals[i].GoalSaturation != Goals[i].PowerCap) return false;

	}
	return true;
}




void Board::Board1()
{
	std::vector<Mirror> Mirrors;
	std::vector<SourceLaser> Sources;
	std::vector<Prism> Prisms;
	std::vector<Laser> Lasers;
	std::vector<Wall> Walls;
	std::vector<Booster> Boosters;
	std::vector<RoughObject> RObjects;
	std::vector<Goal> Goals;



	const int size = 20;
	//main matrix of data
	enum object { nth, source, mirror, goal, prism, rough, wall, booster };
	enum object matrix[size][size];
	//matrix2[size][size];
	int k = 0, l = 0; //edited ones / coursor
	int isEdit = 0;



	double MirrorRotation;

	Time ElapsedTime;
	Vector2f TempDirection;

	for (int i = 0; i<size; i++)
		for (int j = 0; j<size; j++)
			matrix[i][j] = nth;

	Goal LaserGoal;

	RenderWindow window(VideoMode(size * 30 + 200, size * 30, 32), "The Game", Style::Close | Style::Titlebar);
	window.clear();

	Texture sourceTexture;
	sourceTexture.loadFromFile("Source.png"); //OSX if(windows) erease "resourcePath() + "
											  //Texture mirrorTexture;
											  //mirrorTexture.loadFromFile( "resourcePath() + Mirror.png"); //OSX if(windows) erease "resourcePath() + "
	Texture goalTexture;
	goalTexture.loadFromFile("Goal.png");
	Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("Background.png");
	Texture PrismTexture;
	PrismTexture.loadFromFile("Prism.png");
	Texture WallTexture;
	WallTexture.loadFromFile("Wall.png");
	Texture BoosterTexture;
	BoosterTexture.loadFromFile("Booster.png");
	Texture RoughTexture;
	RoughTexture.loadFromFile("Rough.png");
	Texture PanelTexture;
	PanelTexture.loadFromFile("Panel.png");

	RectangleShape Panel;
	Panel.setSize(Vector2f(200.0, 600.0));
	Panel.setPosition(Vector2f(601.0, 0.0));
	Panel.setTexture(&PanelTexture);

	Clock LaserClock;
	Time LaserTime = milliseconds(200);


	window.clear();
	window.setFramerateLimit(15);
	while (window.isOpen())
	{
		if (LaserClock.getElapsedTime() > LaserTime)
		{
			LaserClock.restart();
			for (int i = 0; i < Sources.size(); i++) // Creating new lasers every frame
			{
				Lasers.push_back(Laser(Sources[i].CoordinatesX, Sources[i].CoordinatesY));
			}
		}
		Event e;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			//switching between modes
			if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::E))
			{
				isEdit = ((isEdit + 1) % 2);



				Lasers.clear();


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
							Sources.push_back(SourceLaser(k, l));
							matrix[k][l] = source;
							Lasers.push_back(Laser(k, l));
						}
					}

				//goal insertion white
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Num0))
				{
					if (Goals.size() >= 10) std::cout << "Too many Goals" << std::endl;
					else
					{
						if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
						{
							Goals.push_back(Goal(k, l, sf::Color::White, Goals.size() + 1));
							Goals.back().GoalShape.setTexture(&goalTexture);
							matrix[k][l] = goal;
						}
					}
				}
				//goal insertion red
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Num1))
				{
					if (Goals.size() >= 10) std::cout << "Too many Goals" << std::endl;
					else
					{
						if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
						{
							Goals.push_back(Goal(k, l, sf::Color::Red, Goals.size() + 1));
							Goals.back().GoalShape.setTexture(&goalTexture);
							matrix[k][l] = goal;
						}
					}
				}
				//goal insertion yellow
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Num2))
				{
					if (Goals.size() >= 10) std::cout << "Too many Goals" << std::endl;
					else
					{
						if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
						{
							Goals.push_back(Goal(k, l, sf::Color::Yellow, Goals.size() + 1));
							Goals.back().GoalShape.setTexture(&goalTexture);
							matrix[k][l] = goal;
						}
					}
				}
				//goal insertion green
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Num3))
				{
					if (Goals.size() >= 10) std::cout << "Too many Goals" << std::endl;
					else
					{
						if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
						{
							Goals.push_back(Goal(k, l, sf::Color::Green, Goals.size() + 1));
							Goals.back().GoalShape.setTexture(&goalTexture);
							matrix[k][l] = goal;
						}
					}
				}
				//goal insertion cyan
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Num4))
				{
					if (Goals.size() >= 10) std::cout << "Too many Goals" << std::endl;
					else
					{
						if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
						{
							Goals.push_back(Goal(k, l, sf::Color::Cyan, Goals.size() + 1));
							Goals.back().GoalShape.setTexture(&goalTexture);
							matrix[k][l] = goal;
						}
					}
				}
				//goal insertion blue
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Num5))
				{
					if (Goals.size() >= 10) std::cout << "Too many Goals" << std::endl;
					else
					{
						if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
						{
							Goals.push_back(Goal(k, l, sf::Color::Blue, Goals.size() + 1));
							Goals.back().GoalShape.setTexture(&goalTexture);
							matrix[k][l] = goal;
						}
					}
				}
				//goal insertion magenta

				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::Num6))
				{
					if (Goals.size() >= 10) std::cout << "Too many Goals" << std::endl;
					else
					{
						if ((k != 0 && (k != size - 1)) && (l != 0) && (l != size - 1))
						{
							Goals.push_back(Goal(k, l, sf::Color::Magenta, Goals.size() + 1));
							Goals.back().GoalShape.setTexture(&goalTexture);
							matrix[k][l] = goal;
						}
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
						for (int i = 0; i < Goals.size(); i++)
						{
							if (k == Goals[i].CoordinatesX && l == Goals[i].CoordinatesY)
							{
								Goals.erase(Goals.begin() + i);
								matrix[k][l] = nth;
							}
						}
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
				//Prism rotation to the right
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::P) && matrix[k][l] == prism)
				{
					for (int i = 0; i < Prisms.size(); i++)
					{
						if (k == Prisms[i].CoordinatesX && l == Prisms[i].CoordinatesY)
						{
							Prisms[i].PrismShape.rotate(2);
						}
					}
				}
				//Prism rotation to the left
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::O) && matrix[k][l] == prism)
				{
					for (int i = 0; i < Prisms.size(); i++)
					{
						if (k == Prisms[i].CoordinatesX && l == Prisms[i].CoordinatesY)
						{
							Prisms[i].PrismShape.rotate(-2);
						}
					}
				}
				//Rough object rotation to the right
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::P) && matrix[k][l] == rough)
				{
					for (int i = 0; i < RObjects.size(); i++)
					{
						if (k == RObjects[i].CoordinatesX && l == RObjects[i].CoordinatesY)
						{
							RObjects[i].RoughObjectShape.rotate(2);
						}
					}
				}
				//Rough object rotation rotation to the left
				if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::O) && matrix[k][l] == rough)
				{
					for (int i = 0; i < RObjects.size(); i++)
					{
						if (k == RObjects[i].CoordinatesX && l == Prisms[i].CoordinatesY)
						{
							RObjects[i].RoughObjectShape.rotate(-2);
						}
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



		//background0 rendering
		sf::RectangleShape rectangle(sf::Vector2f((size * 30 + 2) * 1, size * 30 + 2));
		rectangle.setFillColor(Color::Black);
		window.draw(rectangle);

		//background1 rendering
		for (int i = 0; i<size; i++)
			for (int j = 0; j<size; j++)
			{
				sf::RectangleShape rectangle(sf::Vector2f(30.0f, 30.0f));
				rectangle.setPosition(i*30.0 + 1.0, j*30.0 + 1.0);
				rectangle.setTexture(&BackgroundTexture);
				window.draw(rectangle);
			}






		for (int k = 0; k < Goals.size(); k++) //Goals collisions
		{
			for (int i = 0; i < Lasers.size(); i++)
			{

				if (Lasers[i].DistanceToObject(Goals[k].GoalShape) == true)
				{
					if (Lasers[i].CheckCollision(Lasers[i].LaserShape, Goals[k].GoalShape) == true)
					{

						if (Lasers[i].LaserShape.getFillColor() == Goals[k].Color)
						{
							if (Goals[k].GoalSaturation < Goals[k].PowerCap)
							{
								Goals[k].GoalSaturation += Lasers[i].Power;

							}
							else
							{
								Goals[k].GoalSaturation = Goals[k].PowerCap;

							}
						}
						Lasers.erase(Lasers.begin() + i);

					}

				}
			}
			Goals[k].UpdateBar(k);
		}
		for (int k = 0; k < Mirrors.size(); k++) // Mirror collisions
		{
			for (int i = 0; i < Lasers.size(); i++)
			{
				if (Lasers[i].DistanceToObject(Mirrors[k].MirrorShape) == true)
				{
					Time Interval = Lasers[i].getTime();
					if (Interval > Lasers[i].collisionTimestamp)
					{
						if (true == Lasers[i].CheckSatCollision(Mirrors[k].MirrorShape, Lasers[i].LaserShape))
						{

							Lasers[i].restartTime();


							MirrorRotation = Mirrors[k].MirrorShape.getRotation();
							/*Now I'm checking with which side of the mirror the laser collides.
							Depending on the result there will be different algorythms used
							to determine the direction of the laser.
							*/

							unsigned int Axis = Lasers[i].CheckWhichAxis(Mirrors[k].MirrorShape);
							if (Axis == 1 || Axis == 3)// Initial right or left side of the Object // Initial top or bottom side of the mirror
							{
								Lasers[i].MirrorCollision13(&Lasers[i].dirLaser, MirrorRotation);

							}
							else
								//if (Lasers[i].CheckWhichAxis(Mirrors[k].MirrorShape) == 2 || Lasers[i].CheckWhichAxis(Mirrors[k].MirrorShape) == 4)// Initial right or left side of the mirror
							{
								Lasers[i].MirrorCollision24(&Lasers[i].dirLaser, MirrorRotation);
							}
							i = Lasers.size();

						}
					}
				}

			}
		}
		for (int k = 0; k < Prisms.size(); k++) // Za³amywanie œwiat³a
		{

			for (int i = 0; i < Lasers.size(); i++)
			{
				if (Lasers[i].DistanceToObject(Prisms[k].PrismShape) == true)
				{
					Time Interval = Lasers[i].getTime();
					if (Interval > Lasers[i].collisionTimestamp)
					{
						if (true == Lasers[i].CheckSatCollision(Prisms[k].PrismShape, Lasers[i].LaserShape))
						{
							Lasers[i].restartTime();
							unsigned int Axis = Lasers[i].CheckWhichAxis(Prisms[k].PrismShape);
							if (Axis == 2 || Axis == 4)//Initial right or left side of the prism
							{

								Prisms[k].Refraction42Sides(&Lasers[i].dirLaser);
								if (Lasers[i].LaserShape.getFillColor() == sf::Color::White)
								{
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Red, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Yellow, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Green, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Blue, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Cyan, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Magenta, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.erase(Lasers.begin() + i);
								}
							}
							//if (Lasers[i].CheckWhichAxis(Prisms[k].PrismShape) == 1 || Lasers[i].CheckWhichAxis(Prisms[k].PrismShape) == 3)
							else
							{
								Prisms[k].Refraction31Sides(&Lasers[i].dirLaser);
								if (Lasers[i].LaserShape.getFillColor() == sf::Color::White)
								{
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Red, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Yellow, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Green, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Blue, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Cyan, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.push_back(Laser(Prisms[k].PrismShape.getPosition(), sf::Color::Magenta, Lasers[i].dirLaser, 1));
									Lasers[Lasers.size() - 1].LaserIncurvating();
									Lasers.erase(Lasers.begin() + i);

								}

							}
							i = Lasers.size();
						}
					}
				}

			}
		}
		for (int k = 0; k < RObjects.size(); k++) // Dispersion on the RoughObject
		{

			for (int i = 0; i < Lasers.size(); i++)
			{
				if (Lasers[i].DistanceToObject(RObjects[k].RoughObjectShape) == true)
				{
					Time Interval = Lasers[i].getTime();
					if (Interval > Lasers[i].collisionTimestamp)
					{

						if (true == Lasers[i].CheckSatCollision(RObjects[k].RoughObjectShape, Lasers[i].LaserShape))
						{
							Lasers[i].restartTime();
							unsigned int Axis = Lasers[i].CheckWhichAxis(RObjects[k].RoughObjectShape);
							if (Axis == 2 || Axis == 4)// Initial right or left side of the Object
							{

								Lasers[i].MirrorCollision24(&Lasers[i].dirLaser, RObjects[k].RoughObjectShape.getRotation());
								if (Lasers[i].LaserShape.getFillColor() == sf::Color::White) Lasers[i].LaserShape.setFillColor(RObjects[k].FillingColor);
								int n = 4;// Number of lasers that you want to create
								for (int a = 0; a < n; a++) Lasers.push_back(Laser(Lasers[i].LaserShape.getPosition(), Lasers[i].LaserShape.getFillColor(), RObjects[k].Dispersion(Lasers[i].dirLaser, RObjects[k].DispersionValues[a]), n));
								Lasers.erase(Lasers.begin() + i);
							}
							//if (Lasers[i].CheckWhichAxis(RObjects[k].RoughObjectShape) == 1 || Lasers[i].CheckWhichAxis(RObjects[k].RoughObjectShape) == 3)// Initial right or left side of the object
							else
							{
								Lasers[i].MirrorCollision13(&Lasers[i].dirLaser, RObjects[k].RoughObjectShape.getRotation());
								if (Lasers[i].LaserShape.getFillColor() == sf::Color::White) Lasers[i].LaserShape.setFillColor(RObjects[k].FillingColor);
								int n = 4;// Number of lasers that you want to create
								for (int a = 0; a < n; a++) Lasers.push_back(Laser(Lasers[i].LaserShape.getPosition(), Lasers[i].LaserShape.getFillColor(), RObjects[k].Dispersion(Lasers[i].dirLaser, RObjects[k].DispersionValues[a]), n));

								Lasers.erase(Lasers.begin() + i);


							}
							i = Lasers.size(); // Ends the for loop if we found the collision
						}
					}
				}

			}
		}
		for (int k = 0; k < Walls.size(); k++) // Wall collisions
		{

			for (int i = 0; i < Lasers.size(); i++)
			{
				if (Lasers[i].DistanceToObject(Walls[k].WallShape) == true)
				{
					if (true == Lasers[i].CheckSatCollision(Walls[k].WallShape, Lasers[i].LaserShape))
						Lasers.erase(Lasers.begin() + i);
					i = Lasers.size();
				}
			}
		}
		for (int k = 0; k < Boosters.size(); k++) // Booster collisions
		{
			for (int i = 0; i < Lasers.size(); i++)

			{
				if (Lasers[i].DistanceToObject(Boosters[k].BoosterShape) == true)
				{
					Time Interval = Lasers[i].getTime();
					if (true == Lasers[i].CheckSatCollision(Boosters[k].BoosterShape, Lasers[i].LaserShape) && Interval > Lasers[i].collisionTimestamp)
					{
						Lasers[i].restartTime();
						Boosters[k].Boost(&Lasers[i].Power);
						std::cout << "Love";
					}
				}
			}
		}
		//movement of laser beams
		for (int i = 0; i < Lasers.size(); i++)
		{


			Lasers[i].LaserShape.move(Lasers[i].dirLaser.x, Lasers[i].dirLaser.y);

		}

		//Checking if the game is won

		if (Goals.size()>0 && IfWon(Goals) == true)
		{
			std::cout << "You won the game, press any button to exit the game." << std::endl;
			system("PAUSE");
			window.close();
		}

		window.draw(Panel);
		for (int i = 0; i < Lasers.size(); i++) // Checking if lasers are still in bounds
		{
			if (Lasers[i].LaserShape.getPosition().x<30.0 || Lasers[i].LaserShape.getPosition().x > 570.0 || Lasers[i].LaserShape.getPosition().y<30.0 || Lasers[i].LaserShape.getPosition().y>570.0)
				Lasers.erase(Lasers.begin() + i);


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


		for (int i = 0; i < Goals.size(); i++)
		{
			window.draw(Goals[i].GoalShape);
			window.draw(Goals[i].PowerBackground);
			window.draw(Goals[i].PowerBar);

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

		//refreshing the position of laser beams


		for (int i = 0; i < Lasers.size(); i++)
		{
			Lasers[i].LaserShape.setPosition(Lasers[i].LaserShape.getPosition());
			//Lasers[i].dirLaser = Lasers[i].baseDirLaser;

		}

		//std::cout << " " << win;

		window.display();
	}
	
}
