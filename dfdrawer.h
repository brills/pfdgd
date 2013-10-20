#ifndef _DFDRAWER_H_
#define _DFDRAWER_H_

#include "bhtree/bhtree.h"
#include "bhtree/body.h"
#include "bhtree/quad.h"

#include <vector>
#include <set>
#include <memory>

using namespace std;

class DFDrawer {
 public:
  DFDrawer(vector<Body>* node, vector<set<int>>* adj);
  void Iterate();

 private:
  double kDT = 0.03;
  Quad root_quad_;
	Body center_dummy_body_;
  unique_ptr<Force> attractive_force_;
  unique_ptr<Force> repulsive_force_;
	unique_ptr<Force> gravity_;
	unique_ptr<Force> friction_;
  vector<Body>* node_;
  vector<set<int>>* adj_;

  double CalculateEnergy();
};
#endif
