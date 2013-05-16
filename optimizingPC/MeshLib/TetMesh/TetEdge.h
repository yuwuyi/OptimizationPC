#ifndef TetEdge_h__
#define TetEdge_h__

#include <vector> 

class TetVertex;
class TetFace;

class TetEdge {
public:
	TetEdge(TetVertex *v0, TetVertex *v1);
	~TetEdge();
	bool& isValid() { return m_isvalid; }
	TetVertex *vertex(int i) { return m_vers[i]; }
	void add(TetFace *face) { 
		m_faces.push_back(face); 
	}

private:
	TetVertex *m_vers[2];
	std::vector<TetFace *> m_faces;
	bool m_isvalid;

	friend class TetEdgeTetraIterator;
};

#endif // TetEdge_h__