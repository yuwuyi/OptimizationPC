//#pragma warning (disable: 4267)

#ifndef _XMESHLIB_CURVE_H_
#define _XMESHLIB_CURVE_H_

#include "../Meshlib_Core/Mesh.h"
class Halfedge;

namespace XMeshLib
{

	class Curve
	{
	public:
		Curve():valid(false){;}		
		//The following constructors are used for input that is sorted halfedge lists. assuming the validity
		Curve(int length, Halfedge * hes[]);
		Curve(std::vector<Halfedge *> & inhelist);
		~Curve();
		void Clear();

	protected:
		bool valid;
		std::vector<Halfedge *> helist;

	public:
		Vertex * HeadV() const	{return (valid)?(helist[0]->source()):NULL;}
		Vertex * TailV() const  {return (valid)?(helist[helist.size()-1]->target()):NULL;}
		Vertex * V(int const ind);		
		int SizeV() {return (valid)?(helist.size()+1):(-1);}

		Halfedge * operator[] (int const ind) const	{
			if (!valid || ind < 0 || (ind >= static_cast<int>(helist.size())))
				return NULL;
			else 
				return helist[ind];
		}

		void AppendHE(Halfedge * he){helist.push_back(he);}
		int SizeHE() const{return (valid)?(helist.size()):(-1);}

		//I/O Operations
		bool WriteToFile(const char file[]);
		bool WriteToCMesh(const char file[]);
		bool ReadFromFile(Mesh * mesh, const char file[]);
		void MarkOnMesh() const;
	};

	class Loop: public Curve
	{
	public:
		Loop():isLoop(false){;}
		bool checkIsLoop();
		int TraceMeshBoundary(Halfedge * startHE);
		bool isLoop;
	private:
	};

}

#endif
