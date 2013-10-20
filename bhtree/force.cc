#include "force.h"
#include "body.h"
#include <utility>
#include <math.h>
#include <stdio.h>

pair<double, double> GForce::operator()(const Body& self,
                                        const Body& other) const {
  const double EPS = 3e-2;
  double dx = other.get_px() - self.get_px();
  double dy = other.get_py() - self.get_py();
  double dist = sqrt(dx * dx + dy * dy);
  if (dist == 0) return make_pair(0.0, 0.0);
  double F =
      (G_ * self.get_mass() * other.get_mass()) / (dist * dist + EPS * EPS);
  return make_pair(F * dx / dist, F * dy / dist);
}

pair<double, double> RepulsiveForce::operator()(const Body& self,
                                                const Body& other) const {
  const double G = 5e-3;
  const double EPS = 0.1;
  double dx = other.get_px() - self.get_px();
  double dy = other.get_py() - self.get_py();
  double dist = sqrt(dx * dx + dy * dy);
  if (dist == 0) return make_pair(0.0, 0.0);
  double F =
      -(G * self.get_mass() * other.get_mass()) / (dist * dist + EPS);
  return make_pair(F * dx / dist, F * dy / dist);
}

pair<double, double> AttractiveForce::operator()(const Body& self,
                                                 const Body& other) const {
	const double k = 9e-3;
	const double spring_length = 0.03;

  double dx = other.get_px() - self.get_px();
  double dy = other.get_py() - self.get_py();
	double dist = sqrt(dx * dx + dy * dy) + 0.01;

 return make_pair(-k * ((spring_length * dx / dist) - dx),
                  -k * ((spring_length * dy / dist) - dy));
}

pair<double, double> Gravity::operator()(const Body& self,
                                         const Body& other) const {

  double dx = other.get_px() - self.get_px();
  double dy = other.get_py() - self.get_py();
	int xdir = dx > 0 ? 1 : -1;
	int ydir = dy > 0 ? 1 : -1;
	double dist = sqrt(dx * dx + dy * dy);
	return make_pair(0.5 * dx * dx * dx / (dist + 0.001), 0.5 * dy * dy * dy / (dist + 0.001));
  return gf_(self, other);
}

pair<double, double> Friction::operator()(const Body& self,
                                         const Body& other) const {
	const double kFrictionEff = 0.03;//e-2;
	double vx = self.get_vx();
	double vy = self.get_vy();
	double mag = sqrt(vx * vx + vy * vy);
	if (mag == 0) return make_pair(0, 0);
	//vx /= mag;
	//vy /= mag;
	return make_pair(-kFrictionEff * vx, -kFrictionEff * vy);
}
