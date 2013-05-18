#pragma once

#include <vector>

class Window;

class Evaluation
{
public:
	static double geometry(Window *win);
	static int corner(Window *win);
	static double eva(Window *win, double alpha);
};
