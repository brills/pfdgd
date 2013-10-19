#include "body.h"

#include <stdio.h>

void Body::Dump() const {
	printf("body (%.3lf, %.3lf), m=%.3lf\n", px_, py_, mass_);
}

void Body::Combine(const Body& other) {
	double new_mass = mass_ + other.mass_;
	double new_px = (px_ * mass_ + other.px_ * other.mass_) / new_mass;
	double new_py = (py_ * mass_ + other.py_ * other.mass_) / new_mass;
	px_ = new_px;
	py_ = new_py;
	mass_ = new_mass;
}
