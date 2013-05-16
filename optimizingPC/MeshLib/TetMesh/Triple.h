#ifndef Triple_h__
#define Triple_h__

typedef std::pair<int, std::pair<int, int> > triple;
typedef std::pair<int, int> pairint;

inline pairint construct_pairint(TetVertex *v0, TetVertex *v1) {
	int vid0 = v0->id();
	int vid1 = v1->id();
	
	return vid0 < vid1 ? std::make_pair(vid0, vid1) : std::make_pair(vid1, vid0);
}

inline triple construct_triple(TetHalfFace *halfface) {
	int vids[3] = {halfface->vertex(0)->id(), halfface->vertex(1)->id(), halfface->vertex(2)->id()};
	int mn = std::min(vids[0], std::min(vids[1], vids[2]));
	int mx = std::max(vids[0], std::max(vids[1], vids[2]));
	int mid = vids[0] + vids[1] + vids[2] - mn -mx;
	return make_pair(mn, std::make_pair(mid, mx));
}

#endif // Triple_h__