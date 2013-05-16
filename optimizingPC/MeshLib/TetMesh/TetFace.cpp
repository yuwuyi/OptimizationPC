#include "TetFace.h"
#include "TetEdge.h"
#include "TetHalfFace.h"

TetFace::TetFace(TetHalfFace *halfface) : m_next_boundary_face(0) {
	m_halfface[0] = halfface;
	m_halfface[1] = 0;

	for (int i = 0; i < 3; ++i) {
		m_edges[i] = 0;
	}
}

TetFace::~TetFace() {

}