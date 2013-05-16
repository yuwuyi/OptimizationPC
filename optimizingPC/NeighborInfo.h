#pragma once
#include <vector>

class HexMesh;
class Hex;
class NeighborInfo
{
public:
	NeighborInfo(HexMesh* hexmesh);
	~NeighborInfo(void);
	void build();
	std::vector<Hex*>& getNeighbor(Hex* hex); 
private:
	HexMesh *m_hexmesh;
	std::vector< std::vector<Hex*> > m_neighors;
};
