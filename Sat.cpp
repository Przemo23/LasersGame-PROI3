#include "stdafx.h"
#include "Sat.h"
#include <SFML\Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>


using namespace sf;

const float M_PI = 3.14159265;


void Sat::getMirrorVectors(RectangleShape Object)
{
	Vector2f Vertex1, Vertex2, Vertex3, Vertex4;
	float Rotation = Object.getRotation();
	Vector2f Position = Object.getPosition();
	Vector2f Size = Object.getSize();
	float Diagonal = sqrt((Size.x*Size.x)/4 + (Size.y*Size.y)/4);
	float Angle = Rotation * (M_PI / 180);
	Vertex1.x = Position.x + Diagonal *sin(asin(Size.y/(2*Diagonal)) + Angle);
	Vertex1.y = Position.y + Diagonal *cos(asin(Size.y / (2*Diagonal)) + Angle);
	Vertex2.x = Position.x + Diagonal *sin(M_PI - asin(Size.y / (2 * Diagonal)) +Angle);
	Vertex2.y = Position.y + Diagonal *cos(M_PI - asin(Size.y / (2 * Diagonal)) + Angle);
	Vertex3.x = Position.x + Diagonal *sin(M_PI + asin(Size.y / (2 * Diagonal)) + Angle);
	Vertex3.y = Position.y + Diagonal *cos(M_PI + asin(Size.y / (2 * Diagonal)) + Angle);
	Vertex4.x = Position.x + Diagonal *sin(- asin(Size.y / (2 * Diagonal)) + Angle);
	Vertex4.y = Position.y + Diagonal *cos(- asin(Size.y / (2 * Diagonal)) + Angle);
	
	MirrorVectors.push_back(Vertex1);
	MirrorVectors.push_back(Vertex2);
	MirrorVectors.push_back(Vertex3);
	MirrorVectors.push_back(Vertex4);
}

void Sat::getLaserVectors()
{
	Vector2f Vertex1, Vertex2, Vertex3, Vertex4;
	Vector2f Position = GetPosition();

	Vertex1.x = Position.x ;
	Vertex1.y = Position.y ;
	Vertex2.x = Position.x + 5.0;
	Vertex2.y = Position.y;
	Vertex3.x = Position.x + 5.0;
	Vertex3.y = Position.y + 5.0;
	Vertex4.x = Position.x ;
	Vertex4.y = Position.y + 5.0;

	LaserVectors.push_back(Vertex1);
	LaserVectors.push_back(Vertex2);
	LaserVectors.push_back(Vertex3);
	LaserVectors.push_back(Vertex4);

}

void Sat::getAxis(RectangleShape Object)
{
	
	float Rotation = Object.getRotation();
	float Angle = Rotation * (M_PI / 180);
	Vector2f ObjectSize = Object.getSize();
	Vector2f Axis1, Axis2, Axis3, Axis4;
	Axis1.x = MirrorVectors[0].x - MirrorVectors[1].x;
	Axis1.y = MirrorVectors[0].y - MirrorVectors[1].y;
	
	Axis2.x = (MirrorVectors[0].x - MirrorVectors[3].x);
	Axis2.y = MirrorVectors[0].y - MirrorVectors[3].y;
	Axis3.x = 1.0;
	Axis3.y = 0.0;
	Axis4.x = 0.0;
	Axis4.y = 1.0;
	Axises.push_back(Axis1); 
	Axises.push_back(Axis2);
	Axises.push_back(Axis3);
	Axises.push_back(Axis4);
	
}

void Sat::getNormalised(Vector2f* Axis)
{
	
	float AxisLength = sqrt(Axis->x*Axis->x + Axis->y*Axis->y);
	Axis->x = Axis->x / AxisLength;
	Axis->y = Axis->y / AxisLength;

}


void Sat::Project(int i,float* min1,float* max1 )
{
	float d,mint,maxt;
	mint=maxt = DotProduct(0, i);
	
	for (int k = 1; k < MirrorVectors.size(); k++)
	{
		d = DotProduct(k, i);
		maxt = std::max(maxt, d);
		mint = std::min(mint, d);
	}
	*min1 = mint;
	*max1 = maxt;
}

void Sat::ProjectLaser(int i, float* min1, float* max1)
{
	float d, mint, maxt;
	mint = maxt = DotProductLaser(0, i);

	for (int k = 1; k < LaserVectors.size(); k++)
	{
		d = DotProductLaser(k, i);
		maxt = std::max(maxt, d);
		mint = std::min(mint, d);
	}
	*min1 = mint;
	*max1 = maxt;
}

float Sat::DotProduct(int i,int k)
{
	return (Axises[k].x*(MirrorVectors[i].x ) + Axises[k].y*(MirrorVectors[i].y));
}
float Sat::DotProductLaser(int i, int k)
{
	return (Axises[k].x*(LaserVectors[i].x) + Axises[k].y*(LaserVectors[i].y));
}

float Sat::GetIntervalDistance(float minA, float maxA, float minB, float maxB)
{
	float intervalDistance;
	if (minA < minB)
	{
		intervalDistance = minB - maxA;
	}
	else
	{
		intervalDistance = minA - maxB;
	}
	return intervalDistance; //A positive value indicates this axis can be separated.
}


bool Sat::CheckSatCollision(RectangleShape Mirror)
{
	Vector2f MirrorPosition = Mirror.getPosition();
	Vector2f thisPosition = GetPosition();
	
	
	getMirrorVectors(Mirror);
	getLaserVectors();
	getAxis(Mirror);
	getNormalised(&Axises[0]);
	getNormalised(&Axises[1]);
	std::cout << Axises[0].x << Axises[0].y << std::endl;
	std::cout << Axises[1].x << Axises[1].y << std::endl;
	std::cout << Axises[2].x << Axises[2].y << std::endl;
	std::cout << Axises[3].x << Axises[3].y << std::endl;
	std::cout << LaserVectors[0].x <<LaserVectors[0].y << std::endl;
	


	for (int i = 0; i < Axises.size(); i++)
	{
		float minA=0.0, minB=0.0, maxA=0.0, maxB=0.0;
		Project(i, &minB, &maxB);
		ProjectLaser(i, &minA, &maxA);

		float intervalDistance = GetIntervalDistance(minA, maxA, minB, maxB);
		
		if (intervalDistance > 0) return false; //Collision not occurring
	}




	
	
	
	return true;
}

int Sat::CheckWhichAxis(RectangleShape Mirror) // Method currently not used. It was supposed to check with which part of the mirror the laser collides
{
	if (CheckSatCollision(Mirror) != true) std::cout << "? ? ? ";
	float LineDirection, LineConstant, LineDirection2, LineConstant2;
	float Distance1, Distance2;
	Vector2f Intersection1,Intersection2,LaserCenter;
	LaserCenter.x = (MirrorVectors[0].x + MirrorVectors[2].x) / 2;
	LaserCenter.y = (MirrorVectors[0].y + MirrorVectors[2].y) / 2;
	
	
		// Calculating the distance from one Axis
	if ((MirrorVectors[0].x - MirrorVectors[1].x) == 0) LineDirection = 3.402823E+38; //Avoiding division by zero
		else LineDirection = (MirrorVectors[0].y - MirrorVectors[1].y+2.5) / (MirrorVectors[0].x - MirrorVectors[1].x + 2.5);
		LineConstant = MirrorVectors[0].y - LineDirection * MirrorVectors[0].x;
		if (LineDirection == 0) LineDirection2 = 3.402823E+38; //Avoiding division by zero
		else LineDirection2 = -1 / LineDirection;
		LineConstant2 = LaserVectors[0].y - LineDirection2 * LaserVectors[0].x;
		Intersection1.x = (LineConstant2 - LineConstant) / (LineDirection - LineDirection2);
		Intersection1.y = LineConstant + Intersection1.x*LineDirection;
		Distance1 = sqrt((LaserCenter.x - Intersection1.x)*(LaserCenter.x - Intersection1.x) + (LaserCenter.y - Intersection1.y)*(LaserCenter.y - Intersection1.y));


		// Calculating the distance from another Axis
		if((MirrorVectors[0].x - MirrorVectors[3].x + 2.5) == 0) LineDirection = 3.402823E+38; //Avoiding division by zero
			else LineDirection = (MirrorVectors[0].y - MirrorVectors[3].y) / (MirrorVectors[0].x - MirrorVectors[3].x);
		LineConstant = MirrorVectors[0].y - LineDirection * MirrorVectors[0].x;
		if (LineDirection == 0) LineDirection2 = 3.402823E+38; //Avoiding division by zero
		else LineDirection2 = -1.0 / LineDirection;
		LineConstant2 = LaserVectors[0].y - LineDirection2 * LaserVectors[0].x;
		Intersection2.x = (LineConstant2 - LineConstant) / (LineDirection - LineDirection2);
		Intersection2.y = LineConstant + Intersection2.x*LineDirection;
		Distance2 = sqrt((LaserCenter.x - Intersection2.x)*(LaserCenter.x - Intersection2.x) + (LaserCenter.y - Intersection2.y)*(LaserCenter.y - Intersection2.y));

		if (Distance1 >= Distance2) return 0; // This means that the distance from Axis[1] is smaller which means that the object is collideng with Axis[1]
		else return 1; // Colliding with the other axis

	
	return 0;
}
