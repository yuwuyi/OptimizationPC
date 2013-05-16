#pragma warning (disable : 4018)
#include "Curve.h"
#include "../Meshlib_Core/Halfedge.h"
#include "../Meshlib_Core/Iterators.h"
#include <iostream>
#include <fstream>


using namespace XMeshLib;

Curve::Curve(int length, Halfedge * hes[]){
	for (int i=0; i<length; ++i)
		helist.push_back(hes[i]);
	valid = true;
}

Curve::Curve(std::vector<Halfedge *> & inhelist){
	for (int i=0; i<inhelist.size(); ++i)
		helist.push_back(inhelist[i]);
	valid = true;
}

Curve::~Curve(){Clear();}

void Curve::Clear()
{
	helist.clear();
	valid = false;
}

Vertex * Curve::V(int const ind)
{
	if (!valid || ind < 0 || ind > helist.size())
		return NULL;
	else if (!ind)
		return helist[0]->source();
	else
		return helist[ind-1]->target();
}





bool Curve::WriteToFile(const char file[])
{
	if (!valid)
	{
		std::cerr << "Error: The curve is invalid" << std::endl;
		return false;
	}

	std::ofstream fp;
	fp.open(file);
	if (!fp.good())
	{
		std::cerr << "I/O Error: Cannot write into file " << file << " !" << std::endl;
		return false;
	}
	fp << helist.size() << std::endl;
	for (int i=0;i<helist.size(); ++i)
	{
		Halfedge * he = helist[i];
		fp << he->source()->id() << " " << he->target()->id() << std::endl;
	}
	fp.close();
	return true;
}

bool Curve::WriteToCMesh(const char file[])
{
	if (!valid)
	{
		std::cerr << "Error: The curve is invalid" << std::endl;
		return false;
	}

	std::ofstream fp;
	fp.open(file);
	if (!fp.good())
	{
		std::cerr << "I/O Error: Cannot write into file " << file << " !" << std::endl;
		return false;
	}
	//fp << helist.size() << std::endl;
	for (int i=0;i<helist.size(); ++i)
	{
		Halfedge * he = helist[i];
		Vertex * v=he->source();
		fp << "Vertex  " << v->id() << " " << v->point()[0] << " "<< v->point()[1] << " "<< v->point()[2] << "\n";
	}

	for (int i=0;i<helist.size(); ++i)
	{
		Halfedge * he = helist[i];
		fp << "Edge  " << he->source()->id() << " " << he->target()->id() << std::endl;
	}
	fp.close();
	return true;
}

bool Curve::ReadFromFile(Mesh *mesh, const char file[])
{
	helist.clear();
	std::ifstream fp;
	fp.open(file);
	if (!fp.good())
	{
		std::cerr << "I/O Error: Cannot read from file " << file << " !" << std::endl;
		return false;
	}
	int hesize;
	fp >> hesize;	
	for (int i=0;i<hesize; ++i)
	{
		int id1, id2;
		fp >> id1;
		fp >> id2;
		Vertex * v1 = mesh->idVertex(id1);
		Vertex * v2 = mesh->idVertex(id2);
		if (!v1 || !v2)
		{
			std::cerr << "Error: input data donot fit the mesh" << std::endl;
			return false;
		}
		Halfedge * he = mesh->vertexHalfedge(v1, v2);
		if (!he) {
			std::cerr << "Error: the input curve is not on this mesh!" << std::endl;
			return false;
		}
		else
			helist.push_back(he);
	}
	fp.close();
	return true;
}

bool Loop::checkIsLoop()
{
	for (int i=1;i<=helist.size();++i)
		if (helist[i-1]->target()!=helist[i]->source())
			return false;
	if (helist[0]->source()==helist[helist.size()-1]->target())
		return true;
	else
		return false;
}

int Loop::TraceMeshBoundary(Halfedge * startHE){
	Clear();
	if (!startHE->edge()->boundary()){
		std::cerr << "Error: the input halfedge is not on the boundary!" << std::endl;
		return -1;
	}
	helist.push_back(startHE);
	Halfedge * he = startHE->target()->most_clw_out_halfedge();
	while (he && he!=startHE){
		helist.push_back(he);
		he = he->target()->most_clw_out_halfedge();
	}
	valid = true;
	isLoop = true;	
	return helist.size();

}




