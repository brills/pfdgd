#ifndef _BHTREE_BODY_H_
#define _BHTREE_BODY_H_

#include <math.h>

class Body {
 public:
  Body(double px, double py, double vx, double vy, double mass)
      : px_(px),
        py_(py),
        vx_(vx),
        vy_(vy),
        fx_(0),
        fy_(0),
        oldfx_(0),
        oldfy_(0),
        mass_(mass) {}
  Body()
      : px_(0),
        py_(0),
        vx_(0),
        vy_(0),
        fx_(0),
        fy_(0),
        oldfx_(0),
        oldfy_(0),
        mass_(0) {}

  inline double DistanceTo(const Body& other) {
		double dpx = px_ - other.px_,
					 dpy = py_ - other.py_;
		return sqrt(dpx*dpx + dpy*dpy);
	}
	//Leapfrog integrator
  void Update(double dt);
  void AddForce(const Body& other, bool edge);
	void Combine(const Body& other);
	void Dump() const;
	inline void SwitchForce() {
		oldfx_ = fx_;
		oldfy_ = fy_;
	}

	inline void set_px(double px) {px_ = px;}
	inline void set_py(double py) {py_ = py;}
	inline void set_mass(double mass) {mass_ = mass;};

	inline double get_px() const {return px_;}
	inline double get_py() const {return py_;}
	inline double get_mass() const {return mass_;}

 private:
  double px_, py_;  // position, or center-of-mass
  double vx_, vy_;  // velocity
  double fx_, fy_;  // force
	double oldfx_, oldfy_; // force, previous iterate, leapfrog
  double mass_;     // mass
};

#endif
