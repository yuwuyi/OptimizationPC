#ifndef BoundingBox_h__
#define BoundingBox_h__

#include <vector>
#include "../Point.h"

class BoundingBox {
public:
	BoundingBox(std::vector<Point>& points);
	~BoundingBox();
	void compute();	
	double diag();

private:
	std::vector<Point> m_points;
	Point m_minpt;
	Point m_maxpt;
};
#endif // BoundingBox_h__