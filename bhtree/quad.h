#ifndef _BHTREE_QUAD_H_
#define _BHTREE_QUAD_H_

#include "body.h"

#include <math.h>
#include <assert.h>
#include <vector>

/*				^y
 *				|
 *		NW	|  NE
 *				|
 * --------------->x
 *  			|
 *    SW 	|  SE
 *  			|
 */

using namespace std;

class Quad {
 public:
	Quad(): xmin_(0), xmax_(0), ymin_(0), ymax_(0) {}
  Quad(double xmin, double xmax, double ymin, double ymax)
      : xmin_(xmin), xmax_(xmax), ymin_(ymin), ymax_(ymax) {}

  inline double Length() const { return fabs(xmax_ - xmin_); }

  inline bool Contains(double x, double y) const {
    return x <= xmax_ && x >= xmin_ && y <= ymax_ && y >= ymin_;
  }

  inline bool Contains(const Body& body) const {
    return Contains(body.get_px(), body.get_py());
  }

	void Split(vector<Quad>* new_quad) const;

	void Dump() const;

 private:
  double xmin_, xmax_;
  double ymin_, ymax_;
};

#endif
