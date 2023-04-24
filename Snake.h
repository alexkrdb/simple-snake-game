#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

enum Direction{Top = 1, Bottom = -1, West = 2, East = -2};

class Snake
{
public:
	int length;
	int x, y;
	int max;
	Direction dir;
	Direction lastDir;
	Snake(int x, int y, int max, int length);
	Snake();
	void incX();
	void incY();
	void decX();
	void decY();
	void update();
};