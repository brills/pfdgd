#include "dfdrawer.h"

#include "bhtree/bhtree.h"
#include "bhtree/body.h"
#include "bhtree/force.h"

#include <set>
#include <vector>
#include <memory>

DFDrawer::DFDrawer(vector<Body>* node, vector<set<int>>* adj)
    : root_quad_(0, 1, 0, 1),  node_(node), adj_(adj) {
	center_dummy_body_.set_px(0.5);
	center_dummy_body_.set_py(0.5);
	center_dummy_body_.set_mass(1e3);
  attractive_force_.reset(new AttractiveForce());
  repulsive_force_.reset(new RepulsiveForce());
	gravity_.reset(new Gravity());
	friction_.reset(new Friction());
}

void DFDrawer::Iterate() {
  vector<Body>& node = *node_;
  vector<set<int>>& adj = *adj_;
  // repulsive force calculation
  unique_ptr<BHTree> bh_tree;
  bh_tree.reset(new BHTree(root_quad_, NULL, repulsive_force_.get()));
  for (const auto& v : node) {
    bh_tree->Insert(v);
  }
  for (auto& v : node) {
    v.SwitchForce();
    bh_tree->UpdateForce(&v);
  }

  // attractive force calculation
  for (int i = 0; i < node.size(); ++i) {
    for (const auto& other_id : adj[i]) {
      node[i].AddForce(node[other_id], *attractive_force_);
    }
  }

	// central gravity
	for (auto& v : node) {
		v.AddForce(center_dummy_body_, *gravity_);
		v.AddForce(center_dummy_body_, *friction_);
	}

  // update position
  for (auto& v : node) {
    v.Update(kDT);
  }
}
