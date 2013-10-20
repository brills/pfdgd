#include "body.h"
#include "quad.h"
#include "bhtree.h"

#include <stdio.h>
#include <assert.h>
#include <vector>
using namespace std;

BHTree::BHTree(const Quad& quad, BHTree* parent, Force* force)
    : quad_(quad), parent_(parent) , force_(force){
  for (int i = 0; i < kNumChild; ++i) {
    child_[i].reset(NULL);
  }
}

void BHTree::Insert(const Body& body) {
  // empty leaf
  if (IsLeaf()) {
    if (body_.get() == NULL) {
      body_.reset(new Body(body));
			UpdatePath();
      return;
    } else {
      // split
      Split();
      Insert(body);

      return;
    }
  }

  for (int i = 0; i < kNumChild; ++i) {
    if (child_[i]->quad_.Contains(body)) {
      child_[i]->Insert(body);
      return;
    }
  }
	printf("Body: %.3lf, %.3lf insert failed\n", body.get_px(), body.get_py());
	Dump();
  assert(false);
}

void BHTree::UpdateForce(Body* body) const {
	assert(body_.get() != NULL);
	Body& b = *body;
	double quot = quad_.Length() / b.DistanceTo(*body_);
	if (IsLeaf() || quot <= Theta) {
		b.AddForce(*body_, *force_);
		return;
	}

	for (int i = 0; i < kNumChild; ++i) {
		if (child_[i]->body_.get() != NULL) {
			child_[i]->UpdateForce(body);
		}
	}
}

void BHTree::Dump() const {
	printf("----- Node -----\n");
	quad_.Dump();
	if (IsLeaf()) {
		if (body_.get() != NULL) {
			printf("point: ");
			body_->Dump();
		} else {
			printf("empty leaf\n");
		}
	} else {
		printf("center-of-mass: ");
		body_->Dump();
	}
	for (int i = 0; i < kNumChild; ++i) {
		if (child_[i].get() != NULL) {
			child_[i]->Dump();
		}
	}

}

void BHTree::Split() {
	assert(IsLeaf());
	vector<Quad> new_quad(kNumChild);
	quad_.Split(&new_quad);
	for (int i = 0; i < kNumChild; ++i) {
		child_[i].reset(new BHTree(new_quad[i], this, force_));
	}
	
	for (int i = 0; i < kNumChild; ++i) {
		if (child_[i]->quad_.Contains(*body_)) {
			child_[i]->body_.reset(new Body(*body_));
			return;
		}
	}

	body_->Dump();
	for (int i = 0; i < kNumChild; ++i) {
		child_[i]->quad_.Dump();
	}
	assert(false);
}

void BHTree::UpdatePath() {
	const Body& new_body = *body_;
	BHTree* parent = parent_;
	while (parent) {
		parent->body_->Combine(new_body);
		parent = parent->parent_;
	}
}

// Deprecated
void BHTree::CalculateCenterOfMass() {
  assert(!IsLeaf());
  double total_mass = 0, cx = 0, cy = 0;
  for (int i = 0; i < kNumChild; ++i) {
    if (child_[i].get() != NULL && child_[i]->body_) {
      const Body& body = *child_[i]->body_;
      double mass = body.get_mass();
      double x = body.get_px();
      double y = body.get_py();
      cx += x * mass;
			cy += y * mass;
			total_mass += mass;
    }
  }
	body_->set_px(cx / total_mass);
	body_->set_py(cy / total_mass);
	body_->set_mass(total_mass);
}


