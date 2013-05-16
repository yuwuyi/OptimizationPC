#include "TetIterators.h"
#include "TetEdge.h"
#include "TetFace.h"
#include "TetMesh.h"
#include "TetFace.h"
#include "TetHalfFace.h"

TetEdgeTetraIterator::TetEdgeTetraIterator(TetEdge* tedge) {
//TODO: can speed up. shall we need to add every two half faces,
//      or just halfface(0)? 
	
	for (size_t i = 0; i < tedge->m_faces.size(); ++i) {
		TetFace *face = tedge->m_faces[i];
		m_tetra.insert(face->halfface(0)->tetra());

		if (face->halfface(1)) {
			m_tetra.insert(face->halfface(1)->tetra());
		}
	}

	m_it = m_tetra.begin();
}




TetEdgeTetraIterator::~TetEdgeTetraIterator() {
	

}


TetMeshTetraIterator::TetMeshTetraIterator(TetMesh *tetmesh) {
	m_it = tetmesh->id2Tetra.begin();
	m_end = tetmesh->id2Tetra.end();
}

TetMeshTetraIterator::~TetMeshTetraIterator() {

}


TetMeshVertexIterator::TetMeshVertexIterator(TetMesh *tetmesh ) {
	m_it = tetmesh->id2Ver.begin();
	m_end = tetmesh->id2Ver.end();
}

TetMeshVertexIterator::~TetMeshVertexIterator() {

}


TetMeshBoundaryFaceIterator::TetMeshBoundaryFaceIterator(TetMesh *tetmesh) {
	pf = tetmesh->first_boudnary_face;		
}

TetMeshBoundaryFaceIterator::~TetMeshBoundaryFaceIterator() {

}


void TetMeshBoundaryFaceIterator::operator++() {
	pf = pf->next_boundary_face();
}

TetFace* TetMeshBoundaryFaceIterator::operator*() {
	return pf;
}

bool TetMeshBoundaryFaceIterator::end() {
	return (pf == NULL);
}
