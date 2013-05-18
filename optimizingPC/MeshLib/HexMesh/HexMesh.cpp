#include "Hex.h"
#include "Quad.h"
#include "HexEdge.h"
#include "HexMesh.h"
#include "HalfQuad.h"
#include "../Utils/TraitParser.h"
#include "HexVertex.h"
#include "HexMeshUtils.h"
#include <iostream>
#include <fstream>
#include <map>

HexMesh::HexMesh() {

}

HexMesh::~HexMesh() {
	for (size_t i = 0; i < m_hexedges.size(); ++i) {
		delete m_hexedges[i];
	}
}


void HexMesh::read(const char *filename) {
	
	std::ifstream input(filename);
	
	m_next_vid = -1;
	m_next_hid = -1;

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
			HexVertex *tv = createHexVertex(ss);
			if (id2Ver[tv->id()]) {
				std::cout << "tvid: " << tv->id() << " dup!\n";
				exit(-1);
			} else {
				id2Ver[tv->id()] = tv;
			}
			if (tv->id() >= m_next_vid) {
				m_next_vid = tv->id() + 1;
			}
			HexVertex *hv0 = id2Ver[0];	
		} else if (title == "Hex") {
			Hex *hex = createHex(ss);
			id2Hex[hex->id()] = hex;
			if (hex->id() >= m_next_hid) {
				m_next_hid = hex->id() + 1;
			}
		}
	}


	input.close();

	id2Ver.rehash(id2Ver.size());
	id2Hex.rehash(id2Hex.size());
	
	
	
	//link vertex to tetra
	for (stdext::hash_map<int, Hex*>::iterator b = id2Hex.begin(), e = id2Hex.end(); b != e; ++b) {
		Hex *hex = (*b).second;
		hex->isSelected() = isSelect(hex);
		for (int i = 0; i < 8; ++i) {
			HexVertex *hv = hex->vertex(i);
			hv->add(hex);
		}
	}


//	std::vector<TetFace*> faces;
//	TetMeshUtility::buildFaces(halffaces, faces);

//	std::vector<TetEdge*> edges;
	//TetMeshUtility::buildEdges(faces, edges);


	//build quads
	std::map<quadlet, Quad*> quadmap;

	for (stdext::hash_map<int, Hex*>::iterator b = id2Hex.begin(), e = id2Hex.end(); b != e; ++b) {
		Hex *hex = (*b).second;
		for (int i = 0; i < 6; ++i) {
			HalfQuad *halfquad = hex->halfquad(i);	
			quadlet qlet = construct_quad(halfquad);
				
			Quad *quad = quadmap[qlet];

			if (!quad) {
				quad = new Quad(halfquad);				
				quad->index() = m_quads.size();
				m_quads.push_back(quad);
				quadmap[qlet] = quad;
			} else {
				if (quad->halfquad(1)) {
					std::cout << "non-manifold!\n";
					exit(-1);
				}
				quad->halfquad(1) = halfquad;
				halfquad->quad() = quad;
			}
		}
	}

	for(std::map<quadlet, Quad*>::iterator b = quadmap.begin(), e = quadmap.end(); b != e; ++b) {
		Quad *quad = (*b).second;
		if (!quad->halfquad(1)) {
			m_boundary_halfquads.push_back(quad->halfquad(0));
			quad->halfquad(0)->hex()->isBoundary() = true;
			quad->halfquad(0)->hex()->boundaryHalfQuads.push_back(quad->halfquad(0));
			for (int i = 0; i < 4; ++i) {
				quad->halfquad(0)->vertex(i)->isBoundary() = true;
			}
		}
	}


	//build edges;
	std::map<pairint, HexEdge*> edgemap;
	for (std::map<quadlet, Quad*>::iterator b = quadmap.begin(), e = quadmap.end(); b != e; ++b) {
		Quad *quad = (*b).second;
		HalfQuad *halfquad = quad->halfquad(0);
		if (halfquad->hex()->id() == 75) {
			std::cout <<".";
		}
		for (int i = 0; i < 4; ++i) {
			HexVertex *v0 = halfquad->vertex(i);
			HexVertex *v1 = halfquad->vertex((i+1) % 4);

			pairint p = construct_pairint(v0, v1);
			HexEdge *hedge = edgemap[p];

			if (!hedge) {
				hedge = new HexEdge(v0, v1);
				edgemap[p] = hedge;
				m_hexedges.push_back(hedge);
			} 
			
			halfquad->hex()->edges().push_back(hedge);
			quad->hexedge(i) = hedge;
			hedge->add(quad);
		}
	}

	

}


void HexMesh::write(const char *filename) {
	std::ofstream output(filename);
	for (int i = 0; i < m_next_vid; ++i) {
		if (id2Ver.find(i) == id2Ver.end()) {
			continue;
		}
		
		HexVertex *v = id2Ver[i];
		Point pt = v->point();
		output << "Vertex " << i  << " " << pt[0] << " " << pt[1] << " " << pt[2] << " {" << v->property() << "}\n";
	}	

	for (int i = 0; i < m_next_hid; ++i) {
		if (id2Hex.find(i) == id2Hex.end()) {
			continue;
		}
		
		Hex *h = id2Hex[i];
		output << "Hex " << i  << " ";
		for (int j = 0; j < 8; ++j) {
			output  << h->vertex(j)->id() << " ";
		}
		output << "{" << h->property() << "}\n";
	}	

	output.close();
}


HexVertex * HexMesh::createHexVertex(std::stringstream &ss) {
	int id;
	Point pos;
	ss >> id >> pos.v[0] >> pos.v[1] >> pos.v[2];

	std::string line, property;
	getline(ss, line);

	std::string s(line);
	int sp = s.find("{");
	int ep = s.find("}");

	if( sp >= 0 && ep >= 0 )
	{
		property = s.substr( sp+1, ep-sp-1 );
	}

	HexVertex *v = new HexVertex(id, id2Ver.size(), pos, property);
	return v;
}

Hex*  HexMesh::createHex(std::stringstream &ss) {
	if (id2Hex.empty()) {
		//normalize();
	}
	int id;
	int vids[8];

	ss >> id >> vids[0] >> vids[1] >> vids[2] >> vids[3] >> vids[4] >> vids[5] >> vids[6] >> vids[7];

	HexVertex *vers[8];
	for (int i = 0; i < 8; ++i) {
		vers[i] = id2Ver[vids[i]];
	}


	std::string line, property;
	getline(ss, line);

	std::string s(line);
	int sp = s.find("{");
	int ep = s.find("}");

	if( sp >= 0 && ep >= 0 )
	{
		property = s.substr( sp+1, ep-sp-1 );
	}

	Hex *hex = new Hex(id, id2Hex.size(), vers, property);
	return hex;
}



void HexMesh::write2(const char *filename) {
	std::ofstream output(filename);
	for (int i = 0; i < m_next_vid; ++i) {
		if (id2Ver.find(i) == id2Ver.end()) {
			continue;
		}
		
		HexVertex *v = id2Ver[i];
		Point pt = v->point();
		output << "Vertex " << i  << " " << pt[0] << " " << pt[1] << " " << pt[2] << " " << v->property() << "\n";
	}	

	for (int i = 0; i < m_next_hid; ++i) {
		if (id2Hex.find(i) == id2Hex.end()) {
			continue;
		}
		
		Hex *h = id2Hex[i];
		output << "Hex " << i  << " ";
		output  << h->vertex(0)->id() << " " 
			<< h->vertex(1)->id() << " " 
			<< h->vertex(4)->id() << " " 
			<< h->vertex(5)->id() << " " 
			<< h->vertex(3)->id() << " " 
			<< h->vertex(2)->id() << " " 
			<< h->vertex(7)->id() << " " 
			<< h->vertex(6)->id() << " "; 

		output << h->property() << "\n";
	}	

	output.close();
}


void HexMesh::normalize() {
	//normalize
	Point center;
	int count = 0;
	for (stdext::hash_map<int, HexVertex *>::iterator b = id2Ver.begin(), e = id2Ver.end(); b != e; ++b) {
		HexVertex *v = (*b).second;
		center += v->point();	
		++count;
	}
	center /= count;
		
	double max_len = -1e10;
	for (stdext::hash_map<int, HexVertex *>::iterator b = id2Ver.begin(), e = id2Ver.end(); b != e; ++b) {
		HexVertex *v = (*b).second;
		double len = (v->point() - center).norm();
	
		if (len > max_len) {
			max_len = len;
		}
	}
	
	for (stdext::hash_map<int, HexVertex *>::iterator b = id2Ver.begin(), e = id2Ver.end(); b != e; ++b) {
		HexVertex *v = (*b).second;
		v->point() -= center;
		v->point() /= max_len;
	}
}


HexVertex *HexMesh::addVertex(Point pt) {
	HexVertex *v = new HexVertex;
	v->point() = pt;
	v->id() = m_next_vid;
	++m_next_vid;
	id2Ver[v->id()] = v;
	return v;
}

bool sort_hv(HexVertex *v1, HexVertex *v2) {
	if (v1->point()[0] < v2->point()[0]) {
		return true;
	} 
	if (v1->point()[0] > v2->point()[0]) {
		return false;
	} 
	if (v1->point()[1] < v2->point()[1]) {
		return true;
	} 
	if (v1->point()[1] > v2->point()[1]) {
		return false;
	} 
	return v1->point()[2] < v2->point()[2];
}

Hex *HexMesh::addHex(HexVertex *vers[8]) {
	HexVertex *hver[8];
	for (int i = 0; i < 8; ++i) {
		hver[i] = vers[i];
	}

//	std::sort(hver, hver + 8, sort_hv);
	Hex *hex = new Hex(m_next_hid, id2Hex.size(), hver);
	id2Hex[hex->id()] = hex;
	++m_next_hid;
	return hex;
}