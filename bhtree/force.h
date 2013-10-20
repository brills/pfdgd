#ifndef _DHTREE_FORCE_H_
#define _DHTREE_FORCE_H_

#include "body.h"
#include <utility>

using namespace std;
class Body;

class Force {
 public:
  virtual pair<double, double> operator()(const Body& self,
                                          const Body& other) const = 0;
};

class GForce: public Force {
 public:
  GForce(double G = 6.67e-6) : G_(G) {}
  virtual pair<double, double> operator()(const Body& self,
                                          const Body& other) const;

 private:
		double G_;
};


class RepulsiveForce : public Force {
 public:
  virtual pair<double, double> operator()(const Body& self,
                                          const Body& other) const;
};


class AttractiveForce : public Force {
 public:
  virtual pair<double, double> operator()(const Body& self,
                                          const Body& other) const;
};


class Gravity : public Force {
 public:
  Gravity() : gf_(6.67e-7) {};
  virtual pair<double, double> operator()(const Body& self,
                                          const Body& other) const;

 private:
  GForce gf_;
};

class Friction : public Force {
 public:
  virtual pair<double, double> operator()(const Body& self,
                                          const Body& other) const;
};


#endif
