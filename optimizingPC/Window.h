#pragma once
#include <set>
#include <vector>
#include <map>

class Hex;
class HexVertex;

class Window
{
public:
	Window(Hex *hex, int size);
	~Window(void);
	void generate();

	std::vector<Hex*>& hexes() { return m_hexesvec; }
	bool isSimple(Hex* hex) { return m_simpleBitMap[hex]; }
	std::set<HexVertex*>& getBoundaryVertices() { return m_boundaryVertices; }
	void updateBoundary();
	void save();
	void restore();

protected:
	void buildSimpleMap();
private:
	Hex *m_hex;
	int m_size;
	std::vector<Hex*> m_hexesvec;
	std::map<Hex*, bool> m_simpleBitMap, m_backSimpleBitMap;
	std::map<Hex*, bool> m_selectedMap, m_backSelectedMap;
	std::set<HexVertex*> m_boundaryVertices, m_backBoundaryVertices;
};
