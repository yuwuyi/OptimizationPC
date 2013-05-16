#include "TetVertex.h"

TetVertex::TetVertex(int id, Point& pos, const std::string& property)
: m_id(id), m_pos(pos), m_property(property) 
{
	size_t sp = m_property.find('{');
	size_t ep = m_property.find('}');
	if (sp != std::string::npos && ep != std::string::npos) {
		m_property = m_property.substr(sp + 1, ep - sp - 1);
	}
}

TetVertex::~TetVertex() {

}
