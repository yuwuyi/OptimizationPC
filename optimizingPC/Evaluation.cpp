#include "Evaluation.h"
#include "HexVertex.h"
#include "Hex.h"
#include <set>

Evaluation::Evaluation(void)
{
}

Evaluation::~Evaluation(void)
{
}


double Evaluation::geometry(std::vector<Hex*>& hexes) {
	std::set<HexVertex*> nvers;
	for (size_t i = 0; i < hexes.size(); ++i) {
		Hex *hex = hexes[i];
		for(int j = 0; j < 8; ++j) {
			nvers.insert(hex->vertex(j));
		}
	}
	return 0;
}

int Evaluation::corner(std::vector<Hex*>& hexes) {
	return 0;
}
