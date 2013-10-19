#ifndef _BHTREE_BODY_H_
#define _BHTREE_BODY_H_

class Body {
 public:
  Body(double px, double py, double vx, double vy, double mass)
      : px_(px), py_(py), vx_(vx), vy_(vy), mass_(mass) {}
	Body()
      : px_(0), py_(0), vx_(0), vy_(0), mass_(0) {}

  double DistanceTo(const Body& other);
  void Update(double dt);
  void AddForce(const Body& other);
	void Combine(const Body& other);
	void Dump() const;

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
  double mass_;     // mass
};

#endif
