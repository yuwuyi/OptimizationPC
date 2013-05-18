#include <set>
#include <queue>
#include <algorithm>
#include "TraitParser.h"
#include "HexMeshUtils.h"
#include "Window.h"
#include "HexVertex.h"
#include "Hex.h"
#include "HalfQuad.h"
#include "Quad.h"

Window::Window(Hex *hex, int size)
: m_hex(hex), m_size(size)
{
}

Window::~Window(void)
{
}

int int_dist(HexVertex *v0, HexVertex *v1) {
	int loc0[3];
	int loc1[3];
	TraitParser::ReadIntTrait(v0->property(), "loc", 3, loc0);
	TraitParser::ReadIntTrait(v1->property(), "loc", 3, loc1);
	return std::max(std::max(abs(loc0[0] - loc1[0]), abs(loc0[1] - loc1[1])), abs(loc0[2] - loc1[2]));
}

void Window::generate() {
	std::queue<HalfQuad *> queue;
	//init
	for (int i = 0; i < 6; ++i) {
		queue.push(m_hex->halfquad(i));
	}

	std::set<Hex*> m_hexes;
	m_hexes.insert(m_hex);
	while(!queue.empty()) {
		HalfQuad *hquad = queue.front();
		queue.pop();
		HalfQuad *ohquad = hquad->quad()->other(hquad);
		if (ohquad) {
			Hex *nhex = ohquad->hex();
			bool should_add = true;
			for (int i = 0; i < 8; ++i) {
				if (int_dist(nhex->vertex(i), m_hex->vertex(0)) > m_size) {
					should_add = false;	
					break;
				}
			}

			if (!should_add) {
				continue;
			}

			std::pair< std::set<Hex*>::iterator, bool > it = m_hexes.insert(nhex);
			if (it.second) {
				for (int i = 0; i < 6; ++i) {
					HalfQuad *chquad = nhex->halfquad(i);
					if (chquad != ohquad) {
						queue.push(chquad);
					}
				}
			}
		}

	}
	
	m_hexesvec.clear();
	std::copy(m_hexes.begin(), m_hexes.end(), std::back_inserter(m_hexesvec));


	//build simple
	for (size_t i = 0; i < m_hexesvec.size(); ++i) {
		Hex *hex  = m_hexesvec[i];
		m_simpleBitMap[hex] = false;
		for (int j = 0; j < 6; ++j) {
			HalfQuad *hquad = hex->halfquad(j);
			HalfQuad *ohquad = hquad->quad()->other(hquad);
			if (!ohquad) {
				m_simpleBitMap[hex] = true;
				break;
			}

			Hex *ohex = ohquad->hex();
			if (ohex->isSelected() != hex->isSelected()) {
				m_simpleBitMap[hex] = true;
				break;
			}
		}
	}
}


void Window::updateBoundary() {
	m_boundaryVertices.clear();
	for (size_t i = 0; i < m_hexesvec.size(); ++i) {
		Hex *hex  = m_hexesvec[i];
		for (int j = 0; j < 6; ++j) {
			HalfQuad *hquad = hex->halfquad(j);
			HalfQuad *ohquad = hquad->quad()->other(hquad);
			if (!ohquad) {
				m_simpleBitMap[hex] = true;
				if (hex->isSelected()) {
					for (int k = 0; k < 4; ++k) {
						m_boundaryVertices.insert(hquad->vertex(k));
					}
				}
				break;
			}

			Hex *ohex = ohquad->hex();
			if (ohex->isSelected() != hex->isSelected()) {
				m_simpleBitMap[hex] = true;
				for (int k = 0; k < 4; ++k) {
					m_boundaryVertices.insert(hquad->vertex(k));
				}
				break;
			}
		}

	}

}



void Window::save() {
	for (size_t i = 0; i < m_hexesvec.size(); ++i) {
		Hex *hex = m_hexesvec[i];
		m_selectedMap[hex] = hex->isSelected();
	}

	m_backBoundaryVertices = m_boundaryVertices;
}

void Window::restore() {
	for (size_t i = 0; i < m_hexesvec.size(); ++i) {
		Hex *hex = m_hexesvec[i];
		hex->isSelected() = m_selectedMap[hex];
	}

	m_boundaryVertices = m_backBoundaryVertices;
}