#pragma once
#include <iostream>
#include "Cell.h"
#include "Snake.h"
#include "Apple.h"
#include "Lemon.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <ctime>

using namespace std;
static Snake* statSnake;


class Game
{
private:
	double delta;
	double lastTime;
	bool stop = false;
	double frames = 0;
	double timer;
	int UPS = 5;
	int totalFoodNumber = 1;
	int foodNumber = 0;
	vector<GLfloat> snakeColor = { 110.0/255, 170.0/255, 234.0/255 };
public:
	int width, height;
	float squareA;
	int cells = 16;

	Snake snake;
	GLFWwindow* window;
	vector<Cell> field;
	Game(int width, int height, string name);
	~Game();
	bool gameShouldClose();
	void run();
	void render();
	void update();
	void goToCords(int x, int y);
	void setKeyCallBack();
	void drawSnake(int x, int y, vector<GLfloat>& color, float gradient=0);
	void drawSquare(int x, int y, float a, vector<GLfloat>& color, float gradient=0);
	void drawBall(int x, int y, float ballRadius, vector<GLfloat>& color);
};

