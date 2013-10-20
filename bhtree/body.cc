#include "body.h"
#include "force.h"

#include <stdio.h>

void Body::Dump() const {
  printf("body (%.3lf, %.3lf), m=%.3lf, f = (%lf, %lf)\n", px_, py_, mass_, fx_,
         fy_);
}

void Body::Combine(const Body& other) {
	double new_mass = mass_ + other.mass_;
	double new_px = (px_ * mass_ + other.px_ * other.mass_) / new_mass;
	double new_py = (py_ * mass_ + other.py_ * other.mass_) / new_mass;
	px_ = new_px;
	py_ = new_py;
	mass_ = new_mass;
}



void Body::Update(double dt) {
	double dpx = vx_ * dt + oldfx_ * dt * dt / mass_ / 2;
	double dpy = vy_ * dt + oldfy_ * dt * dt / mass_ / 2;
	vx_ = vx_ + (fx_ + oldfx_) * dt / mass_ / 2;
	vy_ = vy_ + (fy_ + oldfy_) * dt / mass_ / 2;
	// Bounce
	//printf("dp = %lf, %lf\n", dpx, dpy);
	if (px_ + dpx < 1.0 && px_ + dpx > 0) {
		px_ += dpx;
	} else {
		px_ -= dpx;
		vx_ = -vx_;
	}

	if (py_ + dpy < 1.0 && py_ + dpy > 0) {
		py_ += dpy;
	} else {
		py_ -= dpy;
		vy_ = -vy_;
	}
	vx_ *= 0.4;
	vy_ *= 0.4;
}

void Body::AddForce(const Body& other, const Force& force) {
	pair<double, double> F = force(*this, other);
	fx_ += F.first;
	fy_ += F.second;
}

