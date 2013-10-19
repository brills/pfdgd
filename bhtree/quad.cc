#include "quad.h"
#include "bhtree.h"

#include <vector>

using namespace std;

void Quad::Split(vector<Quad>* new_quad) const {
	assert(new_quad->size() == BHTree::kNumChild);
	double xmid = (xmin_ + xmax_) / 2;
	double ymid = (ymin_ + ymax_) / 2;
	vector<Quad>& mynewquad = *new_quad;
	mynewquad[BHTree::NW] = Quad(xmin_, xmid, ymid, ymax_);
	mynewquad[BHTree::NE] = Quad(xmid, xmax_, ymid, ymax_);
	mynewquad[BHTree::SW] = Quad(xmin_, xmid, ymin_, ymid);
	mynewquad[BHTree::SE] = Quad(xmid, xmax_, ymin_, ymid);
}

void Quad::Dump() const {
	printf("(%.3lf, %.3lf, %.3lf, %.3lf)\n",
			xmin_, xmax_, ymin_, ymax_);
}
