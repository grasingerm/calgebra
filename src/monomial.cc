#include <iostream>
#include "monomial.hh"

namespace scalc {

std::ostream& operator<<(std::ostream& os, const monomial& m) {
  if (m.x != 0) {
    if (m.c > 0) 
      os << m.x << "x + " << m.c;
    else if (m.c < 0)
      os << m.x << "x - " << -m.c;
    else
      os << m.x << "x";
  }
  else
    os << m.c;

  return os;
}

monomial operator+(const monomial& m1, const monomial& m2) {
  monomial retval;
  retval.x = m1.x + m2.x;
  retval.c = m1.c + m2.c;

  return retval;
}

monomial operator-(const monomial& m1, const monomial& m2) {
  monomial retval;
  retval.x = m1.x - m2.x;
  retval.c = m1.c - m2.c;

  return retval;
}

monomial operator-(const monomial& m) {
  monomial retval;
  retval.x = -m.x;
  retval.c = -m.c;

  return retval;
}

monomial operator*(const monomial& m1, const monomial& m2) {
  monomial retval;
  if (m2.x == 0) {
    retval.x = m1.x * m2.c;
    retval.c = m1.c * m2.c;
  }
  else if (m1.x == 0) {
    retval.x = m2.x * m1.c;
    retval.c = m1.c * m2.c;
  }
  else throw std::runtime_error("Cannot multiply two monomials with nonzero x "
                                "coefficients");

  return retval;
}

monomial operator/(const monomial& m1, const monomial& m2) {
  monomial retval;
  if (m2.x == 0) {
    retval.x = m1.x / m2.c;
    retval.c = m1.c / m2.c;
  }
  else throw std::runtime_error("Cannot divide by a monomial");

  return retval;
}

}
