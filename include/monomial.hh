#ifndef __MONOMIAL_HH
#define __MONOMIAL_HH

#include <iostream>
#include <cmath>

namespace scalc {

struct monomial
{
  double x;
  double c;

  monomial() : x(0.0), c(0.0) {}
  monomial(const double c) : x(0.0), c(c) {}
  monomial(const double x, const double c) : x(x), c(c) {}
};

std::ostream& operator<<(std::ostream&, const monomial&);
monomial operator+(const monomial&, const monomial&);
monomial operator-(const monomial&, const monomial&);
monomial operator-(const monomial&);
monomial operator*(const monomial&, const monomial&);
monomial operator/(const monomial&, const monomial&);

inline bool operator==(const monomial& m1, const monomial& m2) {
  return (m1.x == m2.x && m1.c == m2.c);
}

inline bool aeq(const monomial& m1, const monomial& m2, const double eps=1e-9) {
  return (std::abs(m1.x - m2.x) < eps && std::abs(m1.c - m2.c) < eps);
}

}

#endif
