#include "TetVertex.h"
#include "TetHalfFace.h"
#include "TetFace.h"
#include "TetEdge.h"
#include "TetMesh.h"
#include "Tetra.h"
#include "../Point.h"
#include "Triple.h"
#include "TetMeshUtility.h"
#include <iostream>
#include <fstream>
#include <map>

TetMesh::TetMesh()
: m_next_vid(0), m_next_tid(0), first_boudnary_face(0)
{
}

TetMesh::~TetMesh() {
}



bool TetMesh::read(const char *filename) {
	std::ifstream input(filename);
	
	m_next_vid = -1;
	m_next_tid = -1;

	while(input.good()) {
		std::string line;
		getline(input, line);
		if (line.empty()) {
			continue;
		}

		std::stringstream ss(line);

		std::string title, remain;
		ss >> title;

		if (title == "Vertex") {
			TetVertex *tv = createTetVertex(ss);
			id2Ver[tv->id()] = tv;
			if (tv->id() >= m_next_vid) {
				m_next_vid = tv->id() + 1;
			}
		} else if (title == "Tetrahedron") {
			Tetra *tet = createTetra(ss);
			id2Tetra[tet->id()] = tet;
			if (tet->id() >= m_next_tid) {
				m_next_tid = tet->id() + 1;
			}
		}
	}

	input.close();

	id2Ver.rehash(id2Ver.size());
	id2Tetra.rehash(id2Tetra.size());
	
	
	//link vertex to tetra
	for (stdext::hash_map<int, Tetra*>::iterator b = id2Tetra.begin(), e = id2Tetra.end(); b != e; ++b) {
		Tetra *tet = (*b).second;
		for (int i = 0; i < 4; ++i) {
			TetVertex *tv = tet->vertex(i);
			tv->add(tet);
		}
	}

	std::vector<TetHalfFace*> halffaces;
	for (stdext::hash_map<int, Tetra*>::iterator b = id2Tetra.begin(), e = id2Tetra.end(); b != e; ++b) {
		Tetra *tet = (*b).second;
		for (int i = 0; i < 4; ++i) {
			TetHalfFace *hf = tet->halfface(i);
			halffaces.push_back(hf);
		}
	}

	std::vector<TetFace*> faces;
	TetMeshUtility::buildFaces(halffaces, faces);
	
	first_boudnary_face = TetMeshUtility::buildBoundaryFaces(faces);

	std::vector<TetEdge*> edges;
	TetMeshUtility::buildEdges(faces, edges);

	return true;
}

void TetMesh::save(const char *filename) {
	std::ofstream output(filename);

	for (int vid = 0; vid < m_next_vid; ++vid) {
		TetVertex *v = id2Ver[vid];
		if (!v) {
			continue;
		}
		output << "Vertex " << vid << " " 
			<< v->point()[0] << " " 
			<< v->point()[1] << " " 
			<< v->point()[2] << " {" << v->property() << "}\n";
	}

	for (int tid = 0; tid < m_next_tid; ++tid) {
		Tetra *t = id2Tetra[tid];
		if (!t || !t->isValid())  {
			continue;
		}
		output << "Tetrahedron " << tid << " "
			<< t->vertex(0)->id() << " "
			<< t->vertex(1)->id() << " "
			<< t->vertex(2)->id() << " "
			<< t->vertex(3)->id() << " {" << t->property()<< "}\n";
	}

	output.close();	
}

TetVertex * TetMesh::createTetVertex(std::stringstream &ss) {
	int id;
	Point pos;
	std::string property;
	ss >> id >> pos.v[0] >> pos.v[1] >> pos.v[2];
	getline(ss, property);
	TetVertex *v = new TetVertex(id, pos, property);
	v->index() = id2Ver.size();
	return v;
}


TetFace * TetMesh::createTetFace(TetHalfFace *halfface) {
	return new TetFace(halfface);
}

Tetra * TetMesh::createTetra(std::stringstream &ss) {
	int id;
	int vids[4];
	std::string property;
	ss >> id >> vids[0] >> vids[1] >> vids[2] >> vids[3];
	TetVertex *vers[4];
	for (int i = 0; i < 4; ++i) {
		vers[i] = id2Ver[vids[i]];
	}
	getline(ss, property);
	Tetra *tet = new Tetra(id, id2Tetra.size(), vers, property);
	return tet;
}
