#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "Mirror.h"

using namespace sf;

Mirror::Mirror(int K, int L)
{
	MirrorShape.setSize(Vector2f(10.0f, 30.0f));
	MirrorShape.setPosition(K*30.0 + 16.0, L*30.0 + 16.0);
	MirrorShape.setOrigin(Vector2f(5.0f, 15.0f));
	MirrorShape.setFillColor(Color::Red);
	CoordinatesX = K;
	CoordinatesY = L;
	
}

