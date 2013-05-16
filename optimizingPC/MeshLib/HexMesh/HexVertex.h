#ifndef HexVertex_h__
#define HexVertex_h__

#include "../Point.h"
#include <string>
#include <vector>

class Hex;

class HexVertex {
public:
	HexVertex();
		HexVertex(int id, int index, Point& pos, std::string& property = std::string(""));
	~HexVertex();
	int& id() { return m_id; }
	int& index() { return m_index; }
	void add(Hex* hex) { m_hexes.push_back(hex); }
	std::vector<Hex*> & hexes() { return m_hexes; }
	Point& point() { return m_point; }
	std::string& property() { return m_property; }
	bool& isBoundary() { return m_boundary; }	
	bool& isCorner() { return m_isCorner; }

private:
	int m_id;
	bool m_boundary;
	int m_index;
	Point m_point;
	std::string m_property;
	std::vector<Hex*> m_hexes;
	bool m_isCorner;
};

#endif // HexVertex_h__