#ifndef _BHTREE_BHTREE_H_
#define _BHTREE_BHTREE_H_

#include "body.h"
#include "quad.h"

#include <memory>

using namespace std;

#ifndef NULL
#define NULL 0
#endif


class BHTree {
 public:
	 enum Quadrant {
		 NW = 0,
		 NE,
		 SW,
		 SE,
		 kNumChild
	 };

  BHTree(const Quad& quad, BHTree* parent, Force* force);
  ~BHTree() {}

  void Insert(const Body& body);
  void UpdateForce(Body* body) const;

	void Dump() const;

 private:
	const double Theta = 0.05;

  inline bool IsLeaf() const {
		for (int i = 0; i < kNumChild; ++i) {
			if (child_[i].get() != NULL) return false;
		}
		return true;
  }

	void Split();
	void UpdatePath();
	// Deprecated
	void CalculateCenterOfMass();

	unique_ptr<Body> body_;
  Quad quad_;
	unique_ptr<BHTree> child_[kNumChild];
	// Owned by the creator!!
  BHTree* parent_;
	Force* force_;
};

#endif
