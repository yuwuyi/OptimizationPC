#include "NeighborInfo.h"
#include "HexIterators.h"
#include "HexMesh.h"
#include "Hex.h"
#include <set>

NeighborInfo::NeighborInfo(HexMesh* hexmesh)
{
}

NeighborInfo::~NeighborInfo(void)
{
}

std::vector<Hex*>& NeighborInfo::getNeighbor(Hex* hex) { return m_neighors[hex->id()]; }

void NeighborInfo::build() {
	m_neighors.clear();
	m_neighors.resize(m_hexmesh->hexSize());


	for (HexMeshHexIterator hhit(m_hexmesh); !hhit.end(); ++hhit) {
		Hex *hex = *hhit;
		std::set<Hex*> nhexes;
		std::vector<HexEdge*> &edges = hex->edges();
		for (size_t i = 0; i < edges.size(); ++i) {
			HexEdge *hedge = edges[i];
			for (HexEdgeHexIterator hehit(hedge); !hehit.end(); ++hehit) {
				Hex *chex = *hehit;
				if (chex != hex) {
					nhexes.insert(chex);
				}
			}
		}
		for (std::set<Hex*>::iterator b = nhexes.begin(), e = nhexes.end(); b != e; ++b) {
			m_neighors[hex->id()].push_back(*b);
		}
	}
}