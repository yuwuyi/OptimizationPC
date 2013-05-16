#include "BoundingBox.h"


BoundingBox::BoundingBox(std::vector<Point>& points) 
{
	m_points = points;
	m_minpt = Point(1e4, 1e4, 1e4);
	m_maxpt = Point(-1e4, -1e4, -1e4);
}

BoundingBox::~BoundingBox() {

}
	
double BoundingBox::diag() {
	return (m_maxpt - m_minpt).norm();
}


void BoundingBox::compute() {
	for (size_t i = 0; i < m_points.size(); ++i) {
		Point pt = m_points[i];

		if (pt[0] < m_minpt[0]) {
			m_minpt[0] = pt[0];
		}

		if (pt[0] > m_maxpt[0]) {
			m_maxpt[0] = pt[0];
		}

		if (pt[1] < m_minpt[1]) {
			m_minpt[1] = pt[1];
		}

		if (pt[1] > m_maxpt[1]) {
			m_maxpt[1] = pt[1];
		}

		if (pt[2] < m_minpt[2]) {
			m_minpt[2] = pt[2];
		}

		if (pt[2] > m_maxpt[2]) {
			m_maxpt[2] = pt[2];
		}
	}
}