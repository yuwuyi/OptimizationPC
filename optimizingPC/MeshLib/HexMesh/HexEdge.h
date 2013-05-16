#ifndef HexEdge_h__
#define HexEdge_h__

#include <vector>

class Quad;
class HexVertex; 

class HexEdge {
public:
	HexEdge(HexVertex *v0, HexVertex *v1);
	~HexEdge();

	void add(Quad* quad) {
		m_quads.push_back(quad);
	}
	std::vector<Quad*>& quads() { return m_quads; }
	
	HexVertex *vertex(int i) { return m_vers[i]; }
private:
	std::vector<Quad*> m_quads;
	HexVertex *m_vers[2];

	friend class HexEdgeHexIterator;
};
#endif // HexEdge_h__