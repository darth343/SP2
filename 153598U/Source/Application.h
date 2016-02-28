
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include <iostream>
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SP2.h"
using std::cout;
using std::endl;

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static double mouseX;
	static double mouseY;
	static double scrollX;
	static double scrollY;
	static void pass(double xpos, double ypos);
	static GLFWwindow* m_window;
private:

	//Declare a window object
	StopWatch m_timer;
};

#endif