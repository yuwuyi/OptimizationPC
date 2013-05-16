#ifndef JacobianEva_h__
#define JacobianEva_h__

#include <map>
#include <vector>

class HexVertex;
class HexMesh;
class Hex;

class JacobianEva {
	
public:
	JacobianEva(HexMesh *hm);
	~JacobianEva();
	double evaluate(HexVertex *hv, HexVertex* nhv[3]);
	void evaluate(Hex *hex);
	void evaluate();
	double get(HexVertex*v) { return vertexJacobian[v]; }
private:
	HexMesh *m_hexmesh;
	
	std::map<HexVertex*, std::vector<double> >  vertexmap;
	std::map<HexVertex*, double> vertexJacobian;
};

#endif // JacobianEva_h__