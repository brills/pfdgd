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

  BHTree(const Quad& quad, BHTree* parent);

  void Insert(const Body& body);
  void UpdateForce(Body* body);

	void Dump() const;

 private:
  inline bool IsLeaf() const {
		for (int i = 0; i < kNumChild; ++i) {
			if (child_[i] != NULL) return false;
		}
		return true;
  }

	void Split();
	void UpdatePath();
	// Deprecated
	void CalculateCenterOfMass();

	unique_ptr<Body> body_;
  Quad quad_;
	BHTree* child_[kNumChild];
  BHTree* parent_;
};

#endif
