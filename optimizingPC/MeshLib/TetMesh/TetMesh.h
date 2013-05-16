#ifndef TetMesh_h__
#define TetMesh_h__

#include "../Point.h"
#include <hash_map>
#include <sstream>

class TetVertex;
class TetHalfFace;
class TetFace;
class Tetra;

class TetMesh {
public:
	TetMesh();
	~TetMesh();

	bool read(const char *filename);
	void save(const char *filename);

	TetVertex *vertex(int id) { return id2Ver[id];}
	Tetra *tetra(int id) { return id2Tetra[id]; }

	size_t numVertices() { return id2Ver.size(); }
	size_t numTetras() { return id2Tetra.size(); }

protected:
	TetVertex *createTetVertex(std::stringstream &ss);
	TetVertex *createTetVertex(Point& pos);
	TetFace *createTetFace(TetHalfFace *halfface);	
	Tetra *createTetra(std::stringstream &ss);
		
	//some helper functions
	int m_next_tid;
	int m_next_vid;
	TetFace *first_boudnary_face;
protected:
	stdext::hash_map<int, TetVertex *>		id2Ver;			// given a vertex id, get the corresponding vertex pointer in the container
	stdext::hash_map<int, Tetra *>		id2Tetra;		// given a face id, get the corresponding face pointer in the container
	
	friend class TetMeshUtility;
	friend class TetMeshTetraIterator;
	friend class TetMeshVertexIterator;
	friend class TetMeshBoundaryFaceIterator;

};

#endif // TetMesh_h__