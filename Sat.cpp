#include "stdafx.h"
#include "Sat.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#define PI 3.14159265

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
	
	Vertex1.x = Position.x + Diagonal * cos(M_PI + asin(Size.y / (2 * Diagonal)) + Angle);
	Vertex1.y = Position.y + Diagonal * sin(M_PI + asin(Size.y / (2 * Diagonal)) + Angle);
	Vertex2.x = Position.x + Diagonal * cos(-asin(Size.y / (2 * Diagonal)) + Angle);
	Vertex2.y = Position.y + Diagonal * sin(-asin(Size.y / (2 * Diagonal)) + Angle);
	Vertex3.x = Position.x + Diagonal *cos(asin(Size.y/(2*Diagonal)) + Angle);
	Vertex3.y = Position.y + Diagonal *sin(asin(Size.y / (2*Diagonal)) + Angle);
	Vertex4.x = Position.x + Diagonal *cos(M_PI - asin(Size.y / (2 * Diagonal)) +Angle);
	Vertex4.y = Position.y + Diagonal *sin(M_PI - asin(Size.y / (2 * Diagonal)) + Angle);
	
	
	
	MirrorVectors.push_back(Vertex1);
	MirrorVectors.push_back(Vertex2);
	MirrorVectors.push_back(Vertex3);
	MirrorVectors.push_back(Vertex4);
}

void Sat::getLaserVectors(RectangleShape Laser)
{
	Vector2f Vertex1, Vertex2, Vertex3, Vertex4;
	Vector2f Position = Laser.getPosition();

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


bool Sat::CheckSatCollision(RectangleShape Mirror,RectangleShape Laser)
{
	Vector2f MirrorPosition = Mirror.getPosition();
	Vector2f thisPosition = Laser.getPosition();
		
	getMirrorVectors(Mirror);
	getLaserVectors(Laser);
	getAxis(Mirror);
	getNormalised(&Axises[0]);
	getNormalised(&Axises[1]);
	

	for (int i = 0; i < Axises.size(); i++)
	{
		float minA = 0.0, minB = 0.0, maxA = 0.0, maxB = 0.0;
		Project(i, &minB, &maxB);
		ProjectLaser(i, &minA, &maxA);

		float intervalDistance = GetIntervalDistance(minA, maxA, minB, maxB);

		if (intervalDistance > 0)
		{
			LaserVectors.clear();
			MirrorVectors.clear();
			Axises.clear();
			return false; //Collision not occurring

		}
	}
	return true;
	
}

float Sat::CalculatingDistance(int A, int B)
{
	Vector2f Intersection1, LaserCenter;
	float LineDirection,  LineConstant;
	float Distance1;
	
	LaserCenter.x = (LaserVectors[0].x + LaserVectors[2].x) / 2;
	LaserCenter.y = (LaserVectors[0].y + LaserVectors[2].y) / 2;

	if ((MirrorVectors[A].x - MirrorVectors[B].x) == 0)  //Avoiding division by zero
	{
		Distance1 = std::fabs(MirrorVectors[A].x - LaserCenter.x);
	}
	else
	{
		LineDirection = (MirrorVectors[A].y - MirrorVectors[B].y) / (MirrorVectors[A].x - MirrorVectors[B].x);
		LineConstant = MirrorVectors[A].y - LineDirection * MirrorVectors[A].x;
		Distance1 = (std::fabs(LineDirection*LaserCenter.x - LaserCenter.y + LineConstant)) / sqrt(LineDirection*LineDirection + 1);
	}
	return Distance1;
}
void Sat::MirrorCollision13(sf::Vector2f *Movement, float MirrorRotation)
{
	Vector2f TempDirection;
	TempDirection.x = -(Movement->x * cos(1.5 * PI - MirrorRotation * PI / 180) - Movement->y * sin(1.5 * PI - MirrorRotation * PI / 180));
	TempDirection.y = Movement->x * sin(1.5 * PI - MirrorRotation * PI / 180) + Movement->y * cos(1.5 * PI - MirrorRotation * PI / 180);
	Movement->x = TempDirection.x * cos(0.5*PI + MirrorRotation * PI / 180) - TempDirection.y* sin(0.5*PI + MirrorRotation * PI / 180);
	Movement->y = TempDirection.x* sin(0.5*PI + MirrorRotation * PI / 180) + TempDirection.y * cos(0.5*PI + MirrorRotation * PI / 180);

}
void Sat::MirrorCollision24(sf::Vector2f *Movement, float MirrorRotation)
{
	Vector2f TempDirection;
	TempDirection.x = -(Movement->x * cos(2 * PI - MirrorRotation * PI / 180) - Movement->y * sin(2 * PI - MirrorRotation * PI / 180));
	TempDirection.y = Movement->x * sin(2 * PI - MirrorRotation * PI / 180) + Movement->y * cos(2 * PI - MirrorRotation * PI / 180);
	Movement->x = TempDirection.x * cos(MirrorRotation * PI / 180) - TempDirection.y * sin( MirrorRotation * PI / 180);
	Movement->y = TempDirection.x * sin( MirrorRotation * PI / 180) + TempDirection.y * cos(MirrorRotation * PI / 180);

}
float CalculatingFmin(float Distance1, float Distance2, float Distance3, float Distance4)
{
	float Minimum1, Minimum2;
	Minimum1 = std::fmin(Distance1, Distance2);
	Minimum2 = std::fmin(Distance3, Distance4);
	Minimum1 = std::fmin(Minimum1, Minimum2);
	return Minimum1;
}

int Sat::CheckWhichAxis(RectangleShape Mirror) //  It is supposed to check with which part of the mirror the laser collides
{
	
	float Distance1, Distance2, Distance3,Distance4,MinimalDistance;
	Distance1 = CalculatingDistance(0, 1);
	Distance2 = CalculatingDistance(1, 2);
	Distance3 = CalculatingDistance(2, 3);
	Distance4 = CalculatingDistance(0, 3);

	MinimalDistance = CalculatingFmin(Distance1, Distance2, Distance3, Distance4);

	LaserVectors.clear();
	MirrorVectors.clear();
	Axises.clear();

	if (MinimalDistance == Distance1) return 1;
	if (MinimalDistance == Distance2) return 2;
	if (MinimalDistance == Distance3) return 3;
	if (MinimalDistance == Distance4) return 4;
	
	


		
}


