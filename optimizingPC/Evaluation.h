#pragma once

#include <vector>

class Hex;

class Evaluation
{
public:
	Evaluation();
	~Evaluation();

	static double geometry(std::vector<Hex*>& hexes);
	static int corner(std::vector<Hex*>& hexes);
};
