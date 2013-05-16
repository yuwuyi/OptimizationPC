#include "JacobianEva.h"
#include "HexVertex.h"
#include "Hex.h"
#include "HexMesh.h"
#include "HexIterators.h"
#include "../Eigen/Eigen"
#include <numeric>
#include <iostream>

using namespace Eigen;

JacobianEva::JacobianEva(HexMesh *hm) : m_hexmesh (hm) {

}

JacobianEva::~JacobianEva() {

}

double JacobianEva::evaluate(HexVertex *hv, HexVertex* nhv[3]) {
	Matrix3d J = Matrix3d::Zero();
	for (int i = 0; i < 3; ++i) {
		Point pt = nhv[i]->point() - hv->point();
		pt /= pt.norm();
		for (int j = 0; j < 3; ++j) {
			J(j, i) = pt[j];
		}
	}
	
	return J.determinant();
}

void JacobianEva::evaluate(Hex *hex) {
	int corr[8][3] = {
		{4,2,1},
		{0,3,5},
		{0,6,3},
		{1,2,7},
		{6,0,5},
		{1,7,4},
		{2,4,7},
		{6,5,3},
	};

	double min_q = 1e10;

	for (int i = 0; i < 8; ++i) {
		HexVertex *hvs[3] = {NULL, NULL, NULL};
		for (int j = 0; j < 3; ++j) {
			hvs[j] = hex->vertex(corr[i][j]);
		}
		double q = evaluate(hex->vertex(i), hvs);
					
		if (q < min_q) {
			min_q = q;
		}
		vertexmap[hex->vertex(i)].push_back(q);
	}
	
	return;
}

void JacobianEva::evaluate() {
	vertexmap.clear();

	for (HexMeshHexIterator hmhit(m_hexmesh); !hmhit.end(); ++hmhit)  {
		Hex *hex = *hmhit;
		evaluate(hex);
	}
	
	for (std::map<HexVertex*, std::vector<double> >::iterator b = vertexmap.begin(), e = vertexmap.end(); b != e; ++b) {
		HexVertex *hv = (*b).first;
		std::vector<double> &vec = (*b).second;
		vertexJacobian[hv] = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
	}	

}
