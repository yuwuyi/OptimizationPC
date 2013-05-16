#ifndef TetIterators_h__
#define TetIterators_h__

#include <set>
#include <hash_map>

class TetMesh;
class TetEdge;
class TetFace;
class TetVertex;
class Tetra;

class TetEdgeTetraIterator {
public:
	TetEdgeTetraIterator(TetEdge* tedge);
	~TetEdgeTetraIterator();
	
	void operator++() {
		++m_it;
	}

	Tetra* operator*() {
		return *m_it;
	}

	bool end() {
		return m_it == m_tetra.end();
	}

private:
	std::set<Tetra*> m_tetra;
	std::set<Tetra*>::iterator m_it;
	
};



class TetMeshTetraIterator {
public:
	TetMeshTetraIterator(TetMesh *tetmesh);
	~TetMeshTetraIterator();

	void operator++() {
		++m_it;
	}

	Tetra* operator*() {
		return (*m_it).second;
	}

	bool end() {
		return m_it == m_end;
	}

private:
	stdext::hash_map<int, Tetra *>::iterator m_it, m_end;
};

class TetMeshVertexIterator {
public:
	TetMeshVertexIterator(TetMesh *tetmesh);
	~TetMeshVertexIterator();


	void operator++() {
		++m_it;
	}

	TetVertex* operator*() {
		return (*m_it).second;
	}

	bool end() {
		return m_it == m_end;
	}

private:
	stdext::hash_map<int, TetVertex *>::iterator m_it, m_end;
};

class TetMeshBoundaryFaceIterator {
public:
	TetMeshBoundaryFaceIterator(TetMesh *tetmesh);
	~TetMeshBoundaryFaceIterator();
	
	void operator++();
	TetFace* operator*(); 
	bool end();

private:
	TetFace *pf;	
};
#endif // TetIterators_h__