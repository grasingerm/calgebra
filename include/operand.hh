#ifndef __OPERAND_HH
#define __OPERAND_HH

#include "token.hh"

namespace scalc {

class Operand : public AbstractToken {
private:
  double value;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  public Operand(const double value) : value(value) {}
  virtual ~Operand() {}
};

} // namespace scalc

#endif // __OPERAND_HH
