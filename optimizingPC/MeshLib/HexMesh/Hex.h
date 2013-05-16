#ifndef Hex_h__
#define Hex_h__

#include <string>
#include <vector>
#include "../Point.h"
#include "Common.h"

class HexVertex;
class HalfQuad;
class HexEdge;
class Quad;

class Hex {
public:
	Hex(int id, int index, HexVertex *vers[8], std::string& property = std::string(""));
	~Hex();
	int id() { return m_id; }
	int& index() { return m_index; }
	HexVertex *&vertex(int i) { return m_vers[i]; }
	
	
	std::string& property() { return m_property; }
	HalfQuad *&halfquad(int i) { return m_halfquads[i]; }
	Point center() const { return m_center; }
	bool& isBoundary() { return m_boundary; }
	std::vector<HalfQuad*> boundaryHalfQuads;
	std::vector<HexEdge*>& edges() { return m_edges; }
	HexEdge *opposite(Quad *q1, Quad *q2);

	double dihedral_angle(ORIENTATION o1, ORIENTATION o2);

private:
	bool m_boundary;
	int m_id;
	int m_index;
	HexVertex *m_vers[8];		
	HalfQuad *m_halfquads[6];
	std::string m_property;
	Point m_center;	
	std::vector<HexEdge*> m_edges;
	Point m_quadNorm[6];
};
#endif // Hex_h__