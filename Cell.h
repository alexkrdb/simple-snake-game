#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include "Food.h"

using namespace std;

class Cell
{
public:
	vector<GLfloat> color;
	int x, y;
	bool isSnakeHere;
	Food *food;
	bool isFoodHere;
	int length=0;
	Cell(int x, int y, vector<GLfloat> color, Food* food = nullptr);
	void update();
};

