#include "HexEdge.h"

HexEdge::HexEdge(HexVertex *v0, HexVertex *v1) {
	m_vers[0] = v0;
	m_vers[1] = v1;

}

HexEdge::~HexEdge() {

}
