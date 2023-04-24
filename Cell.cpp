#include "Cell.h"

Cell::Cell(int x, int y, vector<GLfloat> color, Food *food ) : x(x), y(y), color(color), food(food)
{
	isSnakeHere = false;
	isFoodHere = false;
}

void Cell::update()
{
	if (isSnakeHere)
		isSnakeHere = --length > 0;
}
