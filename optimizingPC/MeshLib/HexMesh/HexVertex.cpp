#include "HexVertex.h"


HexVertex::HexVertex() :
m_id(-1), m_index(-1), m_point(Point(0, 0, 0)), m_property(""), m_boundary(false), m_isCorner(false)
 {

}

HexVertex::HexVertex(int id, int index, Point& pos, std::string& property) :
m_id(id), m_index(index), m_point(pos), m_property(property), m_boundary(false), m_isCorner(false)
{

}

HexVertex::~HexVertex() {

}