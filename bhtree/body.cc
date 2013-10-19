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
}

// Fixme for fdgd
void Body::AddForce(const Body& other, bool edge) {
	const double G = 6.67e-6;
	const double EPS = 3e-2;
	double dx = other.px_ - px_;
	double dy = other.py_ - py_;
	double dist = sqrt(dx*dx + dy*dy);
	if (dist == 0) return;
	double F = (G * mass_ * other.mass_) / (dist * dist + EPS * EPS);
	fx_ += F * dx / dist;
	fy_ += F * dy / dist;
}
