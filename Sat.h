#pragma once
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <vector>


class Sat
{
public:
	
	Sat(sf::RectangleShape& body) : body(body) {};
	~Sat() {};
	std::vector<sf::Vector2f> Axises;
	std::vector<sf::Vector2f> MirrorVectors;
	std::vector<sf::Vector2f> LaserVectors;
	void getMirrorVectors(sf::RectangleShape Mirror);

	void getLaserVectors();

	void getAxis(sf::RectangleShape);
	void getNormalised(sf::Vector2f* Axis);
	
	void Project(int i, float* min1, float* max1);
	void ProjectLaser(int i, float* min1, float* max1);
	float DotProduct(int,int);
	float DotProductLaser(int i, int k);
	float GetIntervalDistance(float minA, float maxA, float minB, float maxB);
	bool CheckSatCollision(sf::RectangleShape);
	int CheckWhichAxis(sf::RectangleShape);
	float CalculatingDistance(int, int);
	


	sf::Vector2f GetPosition() { return body.getPosition(); }
private:
	sf::RectangleShape& body;
};