#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "bhtree/body.h"

#include <string>
#include <vector>
#include <set>
#include <memory>

using namespace std;

class Graph {
 public:
  Graph(const string& filename);
  inline vector<Body>& get_node() { return *node_; }
  inline vector<set<int> >& get_adj() { return *adj_; }

 private:
  unique_ptr<vector<Body> > node_;
  unique_ptr<vector<set<int> > > adj_;
};

#endif
