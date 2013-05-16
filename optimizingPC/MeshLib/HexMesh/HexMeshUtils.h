#ifndef HexMeshUtils_h__
#define HexMeshUtils_h__

#include "HalfQuad.h"
#include "Quad.h"
#include "HexVertex.h"
#include "HexEdge.h"
#include <algorithm>
#include <map>


typedef std::pair<int, int> pairint;

inline pairint construct_pairint(HexVertex *v0, HexVertex *v1) {
	int vid0 = v0->id();
	int vid1 = v1->id();
	
	return vid0 < vid1 ? std::make_pair(vid0, vid1) : std::make_pair(vid1, vid0);
}

typedef std::pair<int, std::pair<int, std::pair<int, int> > > quadlet;

inline quadlet construct_quad(HalfQuad *halfquad) {
	int vids[4] = {halfquad->vertex(0)->id(), halfquad->vertex(1)->id(), halfquad->vertex(2)->id(), halfquad->vertex(3)->id()};
	/*int mn = std::min(vids[0], std::min(vids[1], vids[2]));
	int mx = std::max(vids[0], std::max(vids[1], vids[2]));
	int mid = vids[0] + vids[1] + vids[2] - mn -mx;*/
	
	std::sort(vids, vids + 4);
	return make_pair(vids[0], std::make_pair(vids[1], std::make_pair(vids[2], vids[3])));
}


inline void growing(std::vector<HalfQuad *> & halfquads, ORIENTATION o) {
	std::map<HalfQuad *, bool> visitMap;

	for (size_t i = 0; i < halfquads.size(); ++i) {
		HalfQuad *halfquad = halfquads[i];
		visitMap[halfquad] = true;
	}
		std::vector<HalfQuad *> front = halfquads;

	do {
		std::vector<HalfQuad*> newfront;
		for (size_t i = 0; i < front.size(); ++i) {
			HalfQuad *halfquad = halfquads[i];
			for (int j = 0; j < 4; ++j) {
				HexEdge *hedge = halfquad->quad()->hexedge(j);
				std::vector<Quad*>& nquads = hedge->quads();
				for (size_t k = 0; k < nquads.size(); ++k) {
					Quad *quad = nquads[k];
					for (int l = 0; l < 2; ++l) {
						HalfQuad *nextquad = quad->halfquad(l);
						if (!nextquad) {
							continue;
						}
						if (nextquad->orientation() != o) {
							continue;
						}
						if (visitMap[nextquad]) {
							continue;		
						}
						newfront.push_back(nextquad);
						halfquads.push_back(nextquad);
						visitMap[nextquad] = true;
					}
				}
			}
		}
		front = newfront;
	} while(!front.empty());
}

void save_hexes(std::vector<Hex*>& hexes, const char *fname);
#endif // HexMeshUtils_h__