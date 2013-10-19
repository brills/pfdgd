#include "bhtree/bhtree.h"
#include "bhtree/quad.h"
#include "bhtree/body.h"

#include <stdlib.h>
#include <stdio.h>

#define N 10
int main() {
  Body mybodies[N];
  srand(0);
	double total_mass = 0, cx = 0, cy = 0;
  for (int i = 0; i < N; ++i) {
    mybodies[i].set_px(rand() / (double)RAND_MAX);
    mybodies[i].set_py(rand() / (double)RAND_MAX);
    mybodies[i].set_mass(rand() / (double)RAND_MAX);
		mybodies[i].Dump();
		total_mass += mybodies[i].get_mass();
		cx += mybodies[i].get_px() * mybodies[i].get_mass();
		cy += mybodies[i].get_py() * mybodies[i].get_mass();
  }
	cx /= total_mass;
	cy /= total_mass;
	printf("*** total_mass=%lf, c-o-m=(%.3lf, %.3lf)\n", total_mass, cx, cy);

  Quad main_quad(0, 1, 0, 1);
  BHTree mytree(main_quad, NULL);
  for (int i = 0; i < N; ++i) {
    mytree.Insert(mybodies[i]);
//		printf("After insert body %d\n", i);
//		mytree.Dump();
  }
	mytree.Dump();
}
