#pragma once

#include <vector>
class Hex;
class HexMesh;

class OptimizingPC
{
public:
	OptimizingPC(HexMesh *hexmesh);
	~OptimizingPC(void);

protected:
	void extract_boundary_layer();
private:
	std::vector<bool> m_selectBitMap;
	HexMesh *m_hexmesh;
	std::vector<Hex*> m_boundary_layer;
};
