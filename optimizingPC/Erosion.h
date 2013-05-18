#pragma once
#include <map>
#include <vector>

class Hex;
class Quad;
class HexEdge;
class HexVertex;
class Window;


	typedef std::map<Quad*, std::vector<Hex*> > QuadElementMap;
	typedef std::map<HexEdge*, std::vector<Quad*> > EdgeElementMap;
	typedef std::map<HexVertex*, std::vector<HexEdge*> > VertexElementMap;
	typedef std::map<Hex*, bool> HexSelectedMap;

class Erosion
{
public:
	Erosion(Window *win);
	~Erosion(void);
	void perform();

	bool ero();
	void recon();
	void initialize();
	void saveSelected(const char *filename);
protected:

protected:
	void update_quadmap(Hex *hex);
	void update_edgemap(Quad *quad);
	void update_vertmap(HexEdge* edge);

private:
	QuadElementMap quadmap;
	EdgeElementMap edgemap;
	VertexElementMap vertmap;
	HexSelectedMap hexselmap;
	Window *m_win;
};
