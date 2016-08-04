#ifndef __MFUNCTION_HH
#define __MFUNCTION_HH

#include "token.hh"
#include <string>

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
  virtual ~MFunction() {}
};

inline bool isTokenFunction(const AbstractToken* ptoken) {
  return (dynamic_cast<const MFunction*>(ptoken) != nullptr);
}

} // namespace scalc

#endif // __MFUNCTION_HH
