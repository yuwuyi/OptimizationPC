#ifndef Tetra_h__
#define Tetra_h__

#include <string>

class TetVertex;
class TetHalfFace;

class Tetra {
public:
	Tetra(int id, int index, TetVertex *vers[4], std::string& property = std::string(""));
	Tetra(int id, int index, TetHalfFace *halfface, TetVertex *vertex, std::string& property = std::string(""));
	~Tetra();
	
	int& index() { return m_index; }
	int id() const { return m_id; }
	std::string& property() { return m_property; }
	TetHalfFace *&halfface(int i) { return m_halffaces[i]; }
	TetVertex *vertex(int i) { return m_vers[i]; }
	bool& isValid() { return m_isvalid; }
	bool& boundary() { return m_boundary; }	

private:
	void createHalfFace(int start = 0);
	int m_id;
	int m_index;
	TetVertex *m_vers[4];
	TetHalfFace *m_halffaces[4];
	std::string m_property;
	bool m_isvalid;
	bool m_boundary;
};

#endif // Tetra_h__