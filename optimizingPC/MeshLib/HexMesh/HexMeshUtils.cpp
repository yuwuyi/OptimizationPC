#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include "HexMeshUtils.h"
#include "Hex.h"
#include "HexVertex.h"

void save_hexes(std::vector<Hex*>& hexes, const char *fname) {
	std::map<HexVertex*, int> veridmap;

	std::set<HexVertex*> verset;
	for(size_t i = 0; i < hexes.size(); ++i) {
		Hex *hex = hexes[i];
		for (int j = 0; j < 8; ++j) {
			verset.insert(hex->vertex(j));
		}
	}

	int vind = 0;
	for (std::set<HexVertex*>::iterator b = verset.begin(), 
		e = verset.end(); b != e; ++b, ++vind) {
		HexVertex *hv = *b;
		veridmap[hv] = hv->id();
		hv->id() = vind;
	}

	std::ofstream output(fname);
	for (std::set<HexVertex*>::iterator b = verset.begin(), 
		e = verset.end(); b != e; ++b, ++vind) {
			HexVertex *hv = *b;

			output << "Vertex " << hv->id() << " " 
				<< hv->point()[0] << " "
				<< hv->point()[1] << " "
				<< hv->point()[2] << " {" << hv->property() << "}\n";
	}

	for (size_t i = 0; i < hexes.size(); ++i) {
		Hex *hex = hexes[i];
		output << "Hex " << i << " " ;
		for (int j = 0; j < 8; ++j){
			output 	<< hex->vertex(j)->id() << " ";
		}
		output << "{" << hex->property() << "}\n";
	}
	

	for (std::set<HexVertex*>::iterator b = verset.begin(), 
		e = verset.end(); b != e; ++b, ++vind) {
		HexVertex *hv = *b;
		hv->id() = veridmap[hv] ;
	}

	output.close();
	return;
}


