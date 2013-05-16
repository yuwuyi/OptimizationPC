#ifndef TetHalfFace_h__
#define TetHalfFace_h__

#include <string>

class TetVertex;
class TetFace;
class Tetra;

class TetHalfFace {
public:
	TetHalfFace(TetVertex *vers[3]);
	~TetHalfFace();
	bool has(TetVertex *vertex) {
		for (int i = 0; i < 3; ++i) {
			if (m_vers[i] == vertex) {
				return true;
			}
		}
		return false;
	}
	int& index() { return m_index; }
	Tetra*& tetra() { return m_tetra; }	
	TetVertex *vertex(int i) { return m_vers[i]; }
	TetFace *&face() { return m_face; }

private:
	int m_index;
	TetVertex *m_vers[3];
	Tetra *m_tetra;
	TetFace *m_face;
};
#endif // TetHalfFace_h__