#include "Hex.h"
#include "HexVertex.h"
#include "HalfQuad.h"
#include "Quad.h"
#include "HexEdge.h"
#include "HalfQuad.h"

#include <set>

Hex::Hex(int id, int index, HexVertex *vers[8], std::string& property)
: m_id(id), m_index(index), m_property(property),  m_boundary(false)
{
	
	for (int i = 0; i < 8; ++i) {
		m_vers[i] = vers[i];
		m_center += vers[i]->point();
	}

	m_center /= 8.0;

	static int fv_order[][4] = {
		1, 0, 4, 5, //FRONT
		3, 1, 5, 7, //UP
		3, 7, 6, 2, //BACK
		0, 2, 6, 4, //DOWN
		5, 4, 6, 7, //RIGHT
		1, 3, 2, 0, //LEFT
	};


	for (int i = 0; i < MAX_ORIENTATION; ++i) {
		HexVertex *vers[4];
		for (int j = 0; j < 4; ++j) {
			vers[j] = m_vers[fv_order[i][j]];
		}
			
		HalfQuad *halfquad = new HalfQuad(vers, ORIENTATION(i));
		m_halfquads[i] = halfquad;
		halfquad->hex() = this;
	}
}

Hex::~Hex() {

}


HexEdge * Hex::opposite(Quad *q1, Quad *q2) {
	std::set<HexVertex*> verset;

	for (int i = 0; i < 4; ++i) {
		verset.insert(q1->halfquad(0)->vertex(i));
	}

	for (int i = 0; i < 4; ++i) {
		verset.insert(q2->halfquad(0)->vertex(i));
	}

	for (int i = 0; i < m_edges.size(); ++i) {
		HexEdge *hedge = m_edges[i];
		if (verset.find(hedge->vertex(0)) == verset.end() && verset.find(hedge->vertex(1)) == verset.end() ) 
		{
			return hedge;
		}
	}

	return NULL;
}


double Hex::dihedral_angle(ORIENTATION o1, ORIENTATION o2) {
	HalfQuad *hq1 = m_halfquads[o1];	
	HalfQuad *hq2 = m_halfquads[o2];
	double angle = acos(hq1->normal() * hq2->normal());
	return angle;
}