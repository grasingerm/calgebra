#ifndef __OPERAND_HH
#define __OPERAND_HH

#include "token.hh"
#include "monomial.hh"
#include <cstring>
#include <iostream>
#include <sstream>

namespace scalc {

class Operand : public AbstractToken {
private:
  monomial value;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  Operand(const monomial& value) : value(value) {}
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

monomial popOperandValue(TokenStack& token_stack, const char* what_for="operator");

inline bool isTokenOperand(const AbstractToken* ptoken) {
  return (dynamic_cast<const Operand*>(ptoken) != nullptr);
}

} // namespace scalc

#endif // __OPERAND_HH
