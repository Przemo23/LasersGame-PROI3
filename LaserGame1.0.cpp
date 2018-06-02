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
#define PI 3.14159265
					 //#include "ResourcePath.hpp" //OSX in Win useless

	using namespace sf;

SourceLaser initializeSource(int K, int L)
{
	SourceLaser Created = SourceLaser(K, L);

	return Created;
}



int main()
{
	std::vector<Mirror> Mirrors;
	std::vector<SourceLaser> Sources;
	std::vector<Prism> Prisms;
	
	const int size = 30;
	//main matrix of data
	enum object { nth, source, mirror, goal,prism };
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
	Prism Prism1;
	Goal LaserGoal;

	RenderWindow window(VideoMode((size * 30 + 2) * 1, size * 30 + 2, 32), "The Game", Style::Close | Style::Titlebar);
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
	window.clear();

	while (window.isOpen())
	{
		
		Event e;
		
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			//switching between modes
			if ((e.type == e.KeyPressed) && (e.key.code == sf::Keyboard::E))
			{
				isEdit = ((isEdit + 1) % 2);
				win = 0;
				for (int i = 0; i < Sources.size(); i++)
				{
					Sources[i].Laser.setPosition(Sources[i].baseLaser);
					Sources[i].dirLaser = Sources[i].baseDirLaser;
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
						Prism1 = Prism(k, l);
						Prism1.PrismShape.setTexture(&PrismTexture);
						matrix[k][l] = prism;
						Prisms.push_back(Prism1);
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

		//movement of laser beams
		for (int i = 0; i < Sources.size(); i++)
		{
			if (Sources[i].MoveCheck == true) Sources[i].Laser.move(Sources[i].dirLaser);
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

		/*
		//rendering
		for (i = 0; i<size; i++)
		for (j = 0; j<size; j++)
		{
		if (((i != k || j != l) || isEdit == 0) || ((time(0) % 2 == 1)))
		{
		sf::RectangleShape rectangle(sf::Vector2f(30.0f, 30.0f));
		rectangle.setPosition(i*30.0 + 1.0, j*30.0 + 1.0);

		if (matrix[i][j] == source)
		{
		rectangle.setTexture(&sourceTexture);
		}
		if (matrix[i][j] == mirror)
		{
		//rectangle.setTexture(&mirrorTexture);
		}
		if (matrix[i][j]==goal)
		{

		}
		if(matrix[i][j] == nth)
		{
		rectangle.setFillColor(Color::Blue);
		window.draw(rectangle);
		}


		}
		else
		{
		if (isEdit == 1)
		if ((time(0) % 2 == 0))
		{
		sf::RectangleShape rectangle(sf::Vector2f(30.0f, 30.0f));
		rectangle.setPosition(i*30.0 + 1.0, j*30.0 + 1.0);
		rectangle.setFillColor(Color::Red);
		window.draw(rectangle);
		}
		}
		}
		*/

		for (int i = 0; i < Sources.size(); i++)
		{
			Sources[i].ElapsedTime = Sources[i].clock.getElapsedTime();

		}


		for (int i = 0; i < Sources.size(); i++)
		{
			if (GoalCheck == true)
			{
				if (Sources[i].getCollider().CheckCollision(LaserGoal.getCollider()) == true)
				{
					Sources[i].MoveCheck = false;
					win++;
					//Sources[i].Laser.setFillColor(sf::Color::Blue);
				}
			}
		}

		for (int i = 0; i < Sources.size(); i++)
		{
			for (int k = 0; k < Mirrors.size(); k++)
			{
				if (true == Sources[i].CheckMirrorCollision().CheckSatCollision(Mirrors[k].MirrorShape) && Sources[i].ElapsedTime.asMilliseconds() > Sources[i].collisionTimestamp)
				{
					int Side;
					Sources[i].clock.restart();
					Side = Sources[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape);
					Vector2f TempCordinates;
					TempCordinates = Mirrors[k].MirrorShape.getSize();
					MirrorRotation = Mirrors[k].MirrorShape.getRotation();
					/*Now I'm checking with which side of the mirror the laser collides.
					Depending on the result there will be different algorythms used
					to determine the direction of the laser.
					*/
					if (Sources[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape) == 1 || Sources[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape) == 3) // Initial top or bottom side of the mirror
					{
						TempDirection.x = -(Sources[i].dirLaser.x * cos(1.5 * PI - MirrorRotation * PI / 180) - Sources[i].dirLaser.y * sin(1.5 * PI - MirrorRotation * PI / 180));
						TempDirection.y = Sources[i].dirLaser.x * sin(1.5 * PI - MirrorRotation * PI / 180) + Sources[i].dirLaser.y * cos(1.5 * PI - MirrorRotation * PI / 180);
						Sources[i].dirLaser.x = (TempDirection.x * cos(0.5*PI + MirrorRotation * PI / 180) - TempDirection.y * sin(0.5*PI + MirrorRotation * PI / 180));
						Sources[i].dirLaser.y = TempDirection.x * sin(0.5*PI +MirrorRotation * PI / 180) + TempDirection.y * cos(0.5*PI +MirrorRotation * PI / 180);
					}
					if (Sources[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape) == 2 || Sources[i].CheckMirrorCollision().CheckWhichAxis(Mirrors[k].MirrorShape) == 4)// Initial right or left side of the mirror
					{
						TempDirection.x = -(Sources[i].dirLaser.x * cos(2 * PI - MirrorRotation * PI / 180) - Sources[i].dirLaser.y * sin(2 * PI - MirrorRotation * PI / 180));
						TempDirection.y = Sources[i].dirLaser.x * sin(2 * PI - MirrorRotation * PI / 180) + Sources[i].dirLaser.y * cos(2 * PI - MirrorRotation * PI / 180);
						Sources[i].dirLaser.x = (TempDirection.x * cos(MirrorRotation * PI / 180) - TempDirection.y * sin(MirrorRotation * PI / 180));
						Sources[i].dirLaser.y = TempDirection.x * sin(MirrorRotation * PI / 180) + TempDirection.y * cos(MirrorRotation * PI / 180);
					}
					
					
						
					
					
					
				}
			}
		}
		for (int i = 0; i < Sources.size(); i++) // Załamywanie światła
		{
			
			for (int k = 0; k < Prisms.size(); k++)
			{
				if (true == Sources[i].CheckMirrorCollision().CheckSatCollision(Prism1.PrismShape))
				{
					if (Sources[i].CheckMirrorCollision().CheckWhichAxis(Prisms[k].PrismShape) == 2 || Sources[i].CheckMirrorCollision().CheckWhichAxis(Prisms[k].PrismShape) == 4)// Initial right or left side of the mirror
						Prism1.Refraction42Sides(Sources[i].Laser, &Sources[i].dirLaser);
					if (Sources[i].CheckMirrorCollision().CheckWhichAxis(Prisms[k].PrismShape) == 1 || Sources[i].CheckMirrorCollision().CheckWhichAxis(Prisms[k].PrismShape) == 3)
						Prism1.Refraction31Sides(Sources[i].Laser, &Sources[i].dirLaser);
				}
			}
		}
		for (int i = 0; i < Sources.size(); i++)
		{
			Sources[i].Source.setTexture(&sourceTexture);
			window.draw(Sources[i].Source);
			window.draw(Sources[i].Laser);
			
		}
		for (int i = 0; i < Sources.size(); i++)
		{
			Sources[i].Source.setTexture(&sourceTexture);
			window.draw(Sources[i].Source);
			window.draw(Sources[i].Laser);

		}
		
		for (int i = 0; i < Prisms.size(); i++)
		{

			window.draw(Prisms[i].PrismShape);

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
		if (win == Sources.size() && Sources.size() != 0 && isEdit == 0)
		{
			std::cout << "DUUUUUUUUUUUUUPAAAAAAA XD";
			window.close();
		}
		//refreshing the position of laser beams
		if ((time(0) % 6 == 0)/*&&isEdit==0*/)
		{
			win = 0;
			for (int i = 0; i < Sources.size(); i++)
			{
				Sources[i].Laser.setPosition(Sources[i].baseLaser);
				Sources[i].dirLaser = Sources[i].baseDirLaser;
				Sources[i].Laser.setFillColor(sf::Color::Red);
				Sources[i].MoveCheck = true;
			}
		}
		//std::cout << " " << win;
		
		window.display();
	}
	return 0;
}