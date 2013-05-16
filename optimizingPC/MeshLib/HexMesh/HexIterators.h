#ifndef HexIterators_h__
#define HexIterators_h__

#include <set>
#include <vector>

class HexEdge;
class Hex;
class HexVertex;
class Quad;

class HexEdgeHexIterator {
public:
	HexEdgeHexIterator(HexEdge *hedge);
	~HexEdgeHexIterator();

	void operator ++() {
		++m_it;
	}	

	Hex* operator* () {
		return *m_it;
	}

	bool end() {
		return m_it == m_hexes.end();	
	}

private:
	std::set<Hex*> m_hexes;
	std::set<Hex*>::iterator m_it;
};

class HexMeshHexIterator {
public:
	HexMeshHexIterator(HexMesh *hexmesh);

	~HexMeshHexIterator();

	void operator ++() {
		++m_it;
	}	

	Hex* operator* () {
		return *m_it;
	}

	bool end() {
		return m_it == m_hexes.end();	
	}
private:
	std::vector<Hex*> m_hexes;
	std::vector<Hex*>::iterator m_it;
};

class HexMeshVertexIterator {
public:
	HexMeshVertexIterator(HexMesh *hexmesh);
	~HexMeshVertexIterator();

	void operator ++() {
		++m_it;
	}	

	HexVertex* operator* () {
		return *m_it;
	}

	bool end() {
		return m_it == m_vers.end();	
	}
private:
	std::vector<HexVertex*> m_vers;
	std::vector<HexVertex*>::iterator m_it;
};


class HexMeshQuadIterator {
public:
	HexMeshQuadIterator(HexMesh *hexmesh);
	~HexMeshQuadIterator();

	void operator ++() {
		++m_it;
	}	

	Quad* operator* () {
		return *m_it;
	}

	bool end() {
		return m_it == m_end;
	}

private:
	std::vector<Quad*>::iterator m_it, m_end;		
	
};


#endif // HexIterators_h__