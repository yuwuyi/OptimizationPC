#ifndef TetFace_h__
#define TetFace_h__


class TetHalfFace;
class TetEdge;

class TetFace {
public:
	TetFace(TetHalfFace *halfface);
	~TetFace();
	TetHalfFace *&halfface(int i) { return m_halfface[i]; }
	TetEdge *&edge(int i) { return m_edges[i]; }

	TetFace*& next_boundary_face() { return m_next_boundary_face; }
	bool boundary() { return m_next_boundary_face != 0; }
	TetHalfFace *other(TetHalfFace *thf) { 
		if (m_halfface[0] == thf)	 {
			return m_halfface[1];
		} else if (m_halfface[1] == thf) {
			return m_halfface[0];
		}
		return 0;
	}
private:
	TetHalfFace *m_halfface[2];
	TetEdge *m_edges[3];

	TetFace * m_next_boundary_face;
};

#endif // TetFace_h__