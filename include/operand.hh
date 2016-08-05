#ifndef __OPERAND_HH
#define __OPERAND_HH

#include "token.hh"
#include <cstring>
#include <iostream>

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

  friend std::ostream& operator<<(std::ostream& os, const Operand& op) {
    os << op.value;
    return os;
  }
};

double popOperandValue(TokenStack& token_stack, const char* what_for="operator");

inline bool isTokenOperand(const AbstractToken* ptoken) {
  return (dynamic_cast<const Operand*>(ptoken) != nullptr);
}

} // namespace scalc

#endif // __OPERAND_HH
