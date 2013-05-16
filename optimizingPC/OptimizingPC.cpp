#include "OptimizingPC.h"
#include "HexIterators.h"
#include "TraitParser.h"
#include "HexMesh.h"
#include "Hex.h"

bool isSelect(Hex *hex) {
	int isSel = -1;
	TraitParser::ReadIntTrait(hex->property(), "select", 1, &isSel);
	return isSel == 1;
}

OptimizingPC::OptimizingPC(HexMesh *hexmesh)
: m_hexmesh(hexmesh)
{
}

OptimizingPC::~OptimizingPC(void)
{
}



void OptimizingPC::extract_boundary_layer() {
	m_selectBitMap.resize(m_hexmesh->hexSize());	
	for (HexMeshHexIterator hhit(m_hexmesh); !hhit.end(); ++hhit) {
		Hex *hex = *hhit;
		m_selectBitMap[hex->id()] =  isSelect(hex);
	}
}