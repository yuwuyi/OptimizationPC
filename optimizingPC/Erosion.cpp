#include "Erosion.h"
#include "HexMeshUtils.h"
#include "HexIterators.h"
#include "Window.h"
#include "Hex.h"
#include "Quad.h"
#include "HalfQuad.h"
#include "HexEdge.h"
#include "HexVertex.h"
#include <algorithm>

Erosion::Erosion(Window *win)
: m_win(win)
{
}

Erosion::~Erosion(void)
{
}

void Erosion::perform() {
	while(ero()); 
	//recon;
	recon();
}

void Erosion::saveSelected(const char *filename) {
	std::vector<Hex*> selHexes;
	for (size_t i = 0; i < m_win->hexes().size(); ++i) {
		Hex *hex = m_win->hexes()[i];
		if (hex->isSelected()) {
			selHexes.push_back(hex);
		}
	}
	save_hexes(selHexes, filename);
}
void Erosion::recon() {
	std::set<Hex*> reconHexes;
	for (VertexElementMap::iterator b = vertmap.begin(), e = vertmap.end(); b != e; ++b) {
		HexVertex *vert = (*b).first;
		std::copy(vert->hexes().begin(), vert->hexes().end(), std::inserter(reconHexes, reconHexes.end()));
	}

	for (EdgeElementMap::iterator b = edgemap.begin(), e = edgemap.end(); b != e; ++b) {
		HexEdge *edge = (*b).first;
		for (HexEdgeHexIterator hehit(edge); !hehit.end(); ++hehit) {
			Hex *hex = *hehit;
			reconHexes.insert(hex);
		}
	}

	for (std::set<Hex*>::iterator b = reconHexes.begin(), e = reconHexes.end(); b != e; ++b) {
		Hex *hex = *b;
		hex->isSelected() = hexselmap[hex];
	}
}

void Erosion::update_vertmap(HexEdge* edge) {
	for (int i = 0; i < 2; ++i) {
		HexVertex *vert = edge->vertex(i);

		if ( vertmap.find(vert) == vertmap.end() ) {
			continue;
		}

		std::vector<HexEdge*> &vec = vertmap[vert];
		vec.erase(std::remove(vec.begin(), vec.end(), edge), vec.end());
	}
}

void Erosion::update_edgemap(Quad *quad) {
	for (int i = 0; i < 4; ++i) {
		HexEdge *hedge = quad->hexedge(i);
		if ( edgemap.find(hedge) == edgemap.end() ) {
			continue;
		}
		std::vector<Quad*> &vec = edgemap[hedge];
		vec.erase(std::remove(vec.begin(), vec.end(), quad), vec.end());

	}
}

void Erosion::update_quadmap(Hex *hex) {
	for (int i = 0; i < 6; ++i) {
		Quad *quad = hex->halfquad(i)->quad();
		if ( quadmap.find(quad) == quadmap.end() ) {
			continue;
		}
		std::vector<Hex*> &vec = quadmap[quad];
		vec.erase(std::remove(vec.begin(), vec.end(), hex), vec.end());
//		if (vec.empty()) {
//			update_edgemap(quad);
//			quadmap.erase(quad);
//		}
	}

}


bool Erosion::ero() {
	bool isEro = false;

	{
		QuadElementMap::iterator b = quadmap.begin();
		while (b != quadmap.end()) {
			Quad *quad = (*b).first;
			std::vector<Hex*> hexes = (*b).second;

			if (hexes.size() == 1) {
				isEro =true;
				update_quadmap(hexes[0]);
				hexes[0]->isSelected() = false;
				update_edgemap(quad);
				quadmap.erase(b++);
			} else {
				++b;
			}

		}
	}


	std::set<Quad*> eroQuads;
	{
		EdgeElementMap::iterator b = edgemap.begin();
		while (b != edgemap.end()) {
			HexEdge *edge = (*b).first;
			std::vector<Quad*> quads = (*b).second;

			if (quads.size() == 1) {
				isEro =true;
				//eroQuads.insert(quads[0]);
				update_edgemap(quads[0]);
				quadmap.erase(quads[0]);
				update_vertmap(edge);
				edgemap.erase(b++);				
			} else {
				++b;
			}

		}
	}

	std::set<HexEdge*> eroEdges;

	{
		VertexElementMap::iterator b = vertmap.begin();
		while (b != vertmap.end()) {
			HexVertex *vert = (*b).first;
			std::vector<HexEdge*> edges = (*b).second;

			if (edges.size() == 1) {
				isEro =true;
				update_vertmap(edges[0]);
				edgemap.erase(edges[0]);	
				vertmap.erase(b++);
			} else {
				++b;
			}
		}
	}
	
	//for (size_t i = 0; i < eroEdges.size(); ++i) {
/*	for (std::set<HexEdge*>::iterator b = eroEdges.begin(), e = eroEdges.end(); b != e; ++b) {
		HexEdge *edge = *b;
		update_vertmap(edge);
	}*/

	return isEro;
}

void Erosion::initialize() {

	std::vector<Hex*> hexes = m_win->hexes();

	for (size_t i = 0; i < hexes.size(); ++i) {
		Hex *hex = hexes[i];
		hexselmap[hex] = hex->isSelected();
		if (!hex->isSelected()) {
			continue;
		}
		for (int j = 0; j < 6; ++j) {
			Quad *quad = hex->halfquad(j)->quad();
			quadmap[quad].push_back(hex);
		}
	}

	for (QuadElementMap::iterator b = quadmap.begin(), e = quadmap.end(); b != e; ++b) {
		Quad *quad = (*b).first;
		for (int i = 0; i < 4; ++i) {
			HexEdge *hedge = quad->hexedge(i);
			edgemap[hedge].push_back(quad);
		}
	}

	for (EdgeElementMap::iterator b = edgemap.begin(), e = edgemap.end(); b != e; ++b) {
		HexEdge *hedge = (*b).first;
		vertmap[hedge->vertex(0)].push_back(hedge);
		vertmap[hedge->vertex(1)].push_back(hedge);
	}

}