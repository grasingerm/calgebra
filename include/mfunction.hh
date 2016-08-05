#ifndef __MFUNCTION_HH
#define __MFUNCTION_HH

#include "token.hh"
#include <string>
#include <iostream>

namespace scalc {

class MFunction : public AbstractToken {
private:
  double (*f)(double);
  std::string functionName;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  MFunction(double (*f)(double), const std::string functionName) 
    : f(f), functionName(functionName) {}
  MFunction(double (*f)(double), const char* functionName) 
    : f(f), functionName(std::string(functionName)) {}
  MFunction(const MFunction& mf) : f(mf.f), functionName(mf.functionName) {}
  virtual ~MFunction() {}

  friend std::ostream& operator<<(std::ostream& os, const MFunction& mf) {
    os << mf.functionName << "(real x)";
    return os;
  }
};

inline bool isTokenFunction(const AbstractToken* ptoken) {
  return (dynamic_cast<const MFunction*>(ptoken) != nullptr);
}

} // namespace scalc

#endif // __MFUNCTION_HH
