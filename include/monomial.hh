#ifndef __MONOMIAL_HH
#define __MONOMIAL_HH

#include <iostream>
#include <cmath>

namespace scalc {

struct monomial
{
  double x;
  double c;
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

inline bool ae(const monomial& m1, const monomial& m2, const double eps=1e-9) {
  return (abs(m1.x - m2.x) < eps && abs(m1.c - m2.c) < eps);
}

}

#endif
