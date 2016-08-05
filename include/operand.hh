#ifndef __OPERAND_HH
#define __OPERAND_HH

#include "token.hh"
#include <cstring>
#include <iostream>
#include <sstream>

namespace scalc {

class Operand : public AbstractToken {
private:
  double value;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  Operand(const double value) : value(value) {}
  Operand(const Operand& op) : value(op.value) {}
  virtual ~Operand() {}
  inline auto getValue() const noexcept { return value; }
  virtual std::string toString() const {
    std::stringstream ss;
    ss << value;
    return ss.str();
  }

  friend std::ostream& operator<<(std::ostream& os, const Operand& op) {
    os << op.value;
    return os;
  }
};

double popOperandValue(TokenStack& token_stack, const char* what_for="operator");

inline bool isTokenOperand(const AbstractToken* ptoken) {
  return (dynamic_cast<const Operand*>(ptoken) != nullptr);
}

class X : public AbstractToken {
private:
  char x;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  X() : x('x') {}
  X(const char x) : x(x) {}
  X(const X& x) : x(x.x) {}
  virtual ~X() {}
  virtual std::string toString() const { return std::string(1, 'x'); }

  friend std::ostream& operator<<(std::ostream& os, const X& x) {
    os << x.x;
    return os;
  }
};

inline bool isTokenX(const AbstractToken* ptoken) {
  return (dynamic_cast<const X*>(ptoken) != nullptr);
}

} // namespace scalc

#endif // __OPERAND_HH
