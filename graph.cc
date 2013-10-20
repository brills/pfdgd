#include "graph.h"
#include "bhtree/body.h"

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

Graph::Graph(const string& filename) {
  srand(0);
  ifstream fin;
  fin.open(filename);
  string line;
  assert(fin.is_open());
  getline(fin, line);
  int num_node;
  sscanf(line.c_str(), "%d", &num_node);
  node_.reset(new vector<Body>(num_node));
  adj_.reset(new vector<set<int> >(num_node));

  while (getline(fin, line)) {
    int n1, n2;
    sscanf(line.c_str(), "%d %d", &n1, &n2);
    (*adj_)[n1].insert(n2);
    (*adj_)[n2].insert(n1);
  }

  for (auto& node : *node_) {
    node.set_px(rand() / (double)RAND_MAX);
    node.set_py(rand() / (double)RAND_MAX);
    node.set_mass(0.5);
  }
	
	for (const auto& s: *adj_) {
		for (auto i: s) {
			printf("%d ", i);
		}
		printf("\n");
	}
}
