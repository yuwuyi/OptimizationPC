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

class Dilation

{
public:
	Dilation(Window *win);
	~Dilation(void);
	void perform();
	void saveSelected(const char *filename);
	void initialize();
protected:
	bool dil();
	void recon();

protected:
	void update_quadmap(Hex *hex);
	void update_edgemap(Quad *quad);
	void update_vertmap(HexEdge* edge);

private:
	Window *m_win;

	typedef std::map<Quad*, std::vector<Hex*> > QuadElementMap;
	typedef std::map<HexEdge*, std::vector<Quad*> > EdgeElementMap;
	typedef std::map<HexVertex*, std::vector<HexEdge*> > VertexElementMap;

	QuadElementMap quadmap;
	EdgeElementMap edgemap;
	VertexElementMap vertmap;
	HexSelectedMap hexselmap;
};
