#ifndef _MESH_H_
#define _MESH_H_

#include "Edge.h"
#include "Face.h"
#include "Halfedge.h"
#include "Vertex.h"
#include "../../Point.h"
#include <hash_map>
#include <list>

class Mesh
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////								Methods										//////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	//(1) Constructor and Destructor
	Mesh();
	Mesh(std::vector<Face*>& faces);
	~Mesh();

	//(2) I/O
	int numVertices()	{return m_verts.size();}							//number of vertices
	int numEdges()		{return m_edges.size();}							//number of edges
	int numFaces()		{return m_faces.size();}							//number of faces
	void copyTo( Mesh & targetMesh );								//copy current mesh to the target mesh 
	bool read( const char inFile[]);								//read a mesh from inFile
	bool write( const char outFile[]);								//write a mesh to outFile
	void clear();

	//(3) BASIC OPERATIONS
	//Check whether an element is on the boundary:
	bool isBoundary( Vertex *  v ) const {return v->boundary();}
	bool isBoundary( Edge *    e ) const {return e->boundary();}
	bool isBoundary( Halfedge *  he ) const {return !(he->twin());}
	
	//indexing elements
	Edge *				idEdge( int id0, int id1 );
	Face *				idFace(const int id );		
	Halfedge *			idHalfedge( int srcVid, int trgVid );
	Vertex *			idVertex( int id );
	Edge *				vertexEdge( Vertex * v0, Vertex * v1 );
	Halfedge *			vertexHalfedge(Vertex * srcV, Vertex * trgV);

	//(4) Mesh Modification Operators
	Vertex *	createVertex(int id);										
	Edge *		createEdge(Halfedge * he0, Halfedge * he1);
	Face *		createFace(int id);
	Face *		createFace(int v[], int id);
	Face *		createFace(Vertex * v[], int id);	
	void		LabelBoundaries();

	//(5) Indexing
	void SetVPropertyIndex();
	void SetFPropertyIndex();
	void SetEPropertyIndex();
	void SetHEPropertyIndex();

	////(6) Some Basic Mesh Processing Operations
	////	Flip the input edge, and return it.
	////	if the flip works, return the resultant edge, otherwise return NULL
	//Edge *				EdgeFlip(Edge * e);

	//// Split the given edge(input) into two. 
	////	  return :  newly created vertex or NULL(when the split fails);
	//Vertex *			EdgeSplit(Edge * e);
	//Vertex *			FaceSplit(Face * f, double bary[3]);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////								Variables										//////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

protected:
	std::list<Edge *>				m_edges;		// edge container
	std::list<Vertex *>				m_verts;		// vertex container
	std::list<Face *>				m_faces;		// face container

	int maxVid;											// the max vertex id in the mesh
	int maxFid;											// the max face id in the mesh
	stdext::hash_map<int, Vertex *>		id2Ver;			// given a vertex id, get the corresponding vertex pointer in the container
	stdext::hash_map<int, Face *>		id2Face;		// given a face id, get the corresponding face pointer in the container

	std::vector<std::vector<Halfedge *>> v_adjHeList;
	bool boundaryLabeled;
	bool hasVPropertyIndex;
	bool hasFPropertyIndex;
	bool hasEPropertyIndex;
	bool hasHEPropertyIndex;

protected:
	friend class MeshVertexIterator;
	friend class MeshEdgeIterator;
	friend class MeshFaceIterator;
	friend class MeshHalfedgeIterator;
};



#endif //_XMESHLIB_CORE_MESH_H_ defined
