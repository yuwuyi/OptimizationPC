#include "Window.h"
#include "TraitParser.h"
#include "Evaluation.h"
#include "HexVertex.h"
#include "Hex.h"
#include <iostream>
#include <set>


double Evaluation::geometry(Window *win) {
	double geoSimilarity = 0;
	std::set<HexVertex*> &hvers = win->getBoundaryVertices();
	for (std::set<HexVertex*>::iterator b = hvers.begin(), e = hvers.end(); b != e; ++b) {
		HexVertex *hver = *b;
		double df = 0;
		TraitParser::ReadTrait(hver->property(), "df", 1, &df);
		if ( df != 0) {
			//std::cout << ".";
		}
		geoSimilarity += fabs(df);
	}
	return geoSimilarity;
}

int Evaluation::corner(Window *win) {
	std::vector<Hex*> &hexes = win->hexes();
	std::map<HexVertex*, int> v2hexMap;
	for (size_t i = 0; i < hexes.size(); ++i) {
		Hex *hex = hexes[i];
		if (hex->isSelected()) {
			for (int j = 0; j < 8; ++j) {
				HexVertex *v = hex->vertex(j);
				++v2hexMap[v];
			}
		}
	}
	int count = 0;
	for (std::map<HexVertex*, int>::iterator b = v2hexMap.begin(),
		e = v2hexMap.end(); b != e; ++b) {
			int corner = (*b).second;
			if ( corner == 1 || corner == 3 || corner == 5) {
				++count;
			}
	}
	return count;
}

double Evaluation::eva(Window *win, double alpha) {
	double geo = geometry(win);
	double cor = corner(win);
	return geo * alpha + cor;
}