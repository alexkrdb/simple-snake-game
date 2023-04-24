#include "Snake.h"

Snake::Snake(int x, int y, int max, int length) : x(x), y(y), max(max), length(length)
{
	lastDir = dir = Top;
	std::cout << "snake";
}

Snake::Snake()
{
	max = 16;
	lastDir = dir = Top;
	x = 0;
	y = 0;
	length = 1;
}

void Snake::incX()
{
	if (x < max)
		x++;
}


void Snake::incY()
{
	if (y < max)
		y++;
}

void Snake::decX()
{
	if (x >= 0)
		x--;
}

void Snake::decY()
{
	if (y >= 0)
		y--;
}

void Snake::update()
{
	if (abs(dir) != abs(lastDir)) {
		lastDir = dir;
	}
	else {
		dir = lastDir;
	}
	 
	switch (dir)
	{
	case Top:
		incY();
		break;
	case Bottom:
		decY();
		break;
	case West:
		decX();
		break;
	case East:
		incX();
		break;
	default:
		break;
	}
	lastDir = dir;
}



