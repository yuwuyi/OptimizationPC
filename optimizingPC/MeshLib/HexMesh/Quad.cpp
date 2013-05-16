#include "Quad.h"
#include "HalfQuad.h"
#include "HexVertex.h"

Quad::Quad(HalfQuad *halfquad) {
	m_halfquads[0] = halfquad;
	halfquad->quad() = this;

	m_halfquads[1] = 0;
	for(int i = 0; i < 4; ++i) {
		m_center += halfquad->vertex(i)->point();
	}
	m_center /= 4.0;
}

Quad::~Quad() {

}