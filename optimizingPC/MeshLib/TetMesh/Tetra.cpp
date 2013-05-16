#include "Tetra.h"
#include "TetHalfFace.h"

Tetra::Tetra(int id, int index, TetVertex *vers[4], std::string& property) 
: m_id(id), m_index(index), m_property(property), m_isvalid(true), m_boundary(false)
{
	for (int i = 0; i < 4; ++i) {
		m_vers[i] = vers[i];
	}
	createHalfFace();

	size_t sp = m_property.find('{');
	size_t ep = m_property.find('}');
	if (sp != std::string::npos && ep != std::string::npos) {
		m_property = m_property.substr(sp + 1, ep - sp - 1);
	}

}

Tetra::Tetra(int id, int index, TetHalfFace *halfface, TetVertex *vertex, std::string& property) 
: m_id(id), m_index(index), m_property(property), m_isvalid(true){
	for (int i = 0; i < 3; ++i) {
		m_vers[i] = halfface->vertex(i);
	}
	m_vers[3] = vertex;
	m_halffaces[0] = halfface;
	halfface->tetra() = this;
	halfface->index() = 4 * m_index;
	createHalfFace(1);

}

Tetra::~Tetra() {

}

void Tetra::createHalfFace(int start) {
	TetVertex *face[3];
	for (int id = start; id < 4; ++id) {
		int j = 0;
		for (int i = 0; i < 4; ++i) {
			if (i == id) {
				continue;
			}
			face[j] = m_vers[i];
			++j;
		}

		if ((id % 2) == 0) {
			std::swap(face[0], face[1]);
		}

		TetHalfFace *hf = new TetHalfFace(face);
		hf->tetra() = this;
		m_halffaces[id] = hf;	
		hf->index() = m_index * 4 + id;
		
	}
}