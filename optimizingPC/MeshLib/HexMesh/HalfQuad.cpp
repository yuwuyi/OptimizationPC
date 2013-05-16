#include "HalfQuad.h"
#include "HexVertex.h"

HalfQuad::HalfQuad(HexVertex *vers[4], ORIENTATION o)
: m_orientation(o) 
{
	for (int i = 0; i < 4; ++i) {
		m_vers[i] = vers[i];
	}
	m_norm = (m_vers[1]->point() - m_vers[0]->point()) ^ (m_vers[2]->point() - m_vers[1]->point());
	m_norm /= m_norm.norm();
}

HalfQuad::~HalfQuad() {
	
}
