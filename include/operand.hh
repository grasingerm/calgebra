#ifndef __OPERAND_HH
#define __OPERAND_HH

#include "token.hh"
#include <cstring>
#include <iostream>
#include <sstream>

namespace scalc {

template <class T> 
class Operand<T> : public AbstractToken {
private:
  T value;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  Operand<T>(const T value) : value(value) {}
  Operand<T>(const Operand<T>& op) : value(op.value) {}
  virtual ~Operand() {}
  inline auto getValue() const noexcept { return value; }
  virtual std::string toString() const {
    std::stringstream ss;
    ss << value;
    return ss.str();
  }

  template <class T>
  friend std::ostream& operator<<(std::ostream& os, const Operand<T>& op) {
    os << op.value;
    return os;
  }
};

double popOperandValue(TokenStack& token_stack, const char* what_for="operator");

template <class T>
inline bool isTokenOperand(const AbstractToken* ptoken) {
  return (dynamic_cast<const Operand<T>*>(ptoken) != nullptr);
}

} // namespace scalc

#endif // __OPERAND_HH
