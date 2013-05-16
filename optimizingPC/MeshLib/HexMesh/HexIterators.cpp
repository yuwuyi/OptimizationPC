#include "HexMesh.h"
#include "HexIterators.h"
#include "HexVertex.h"
#include "HalfQuad.h"
#include "HexEdge.h"
#include "Quad.h"

HexEdgeHexIterator::HexEdgeHexIterator(HexEdge *hedge) {
	for (size_t i = 0; i < hedge->m_quads.size(); ++i) {
		Quad *quad = hedge->m_quads[i];
		for (int j = 0; j < 2; ++j) {
			HalfQuad *halfquad = quad->halfquad(j);
			if (halfquad) {
				Hex *hex = halfquad->hex();
				m_hexes.insert(hex);
			}
		}
	}
	m_it = m_hexes.begin();
}


HexEdgeHexIterator::~HexEdgeHexIterator() {}


HexMeshHexIterator::HexMeshHexIterator(HexMesh *hexmesh) {
	for(stdext::hash_map<int, Hex *>::iterator b = hexmesh->id2Hex.begin(), e = hexmesh->id2Hex.end(); b != e; ++b) {
		Hex *hex = (*b).second;
		m_hexes.push_back(hex);
	}
	m_it = m_hexes.begin();
}


HexMeshHexIterator::~HexMeshHexIterator() {
}


HexMeshVertexIterator::HexMeshVertexIterator(HexMesh *hexmesh) {
	for(stdext::hash_map<int, HexVertex *>::iterator b = hexmesh->id2Ver.begin(), e = hexmesh->id2Ver.end(); b != e; ++b) {
		HexVertex *ver = (*b).second;
		m_vers.push_back(ver);
	}
	m_it = m_vers.begin();

}

HexMeshVertexIterator::~HexMeshVertexIterator() {

}


HexMeshQuadIterator::HexMeshQuadIterator(HexMesh *hexmesh) 
{
	m_end = hexmesh->m_quads.end();
	m_it = hexmesh->m_quads.begin();
}

