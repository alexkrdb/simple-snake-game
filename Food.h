#pragma once
#include <vector>
#include<GLFW/glfw3.h>

using namespace std;

class Food
{
public:
	vector<GLfloat> color;
	virtual void printFood() = 0;

};

