#include "TetEdge.h"

TetEdge::TetEdge(TetVertex *v0, TetVertex *v1)
: m_isvalid(true) {
	m_vers[0] = v0;
	m_vers[1] = v1;
}

TetEdge::~TetEdge() {

}