#ifndef __PARENTHESIS_HH
#define __PARENTHESIS_HH

#include "token.hh"
#include "mfunction.hh"
#include <iostream>

namespace scalc {

class LeftParen : public AbstractToken {
private:
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  virtual ~LeftParen() {}
  virtual std::string toString() const { return std::string(1, '('); }
  
  friend std::ostream& operator<<(std::ostream& os, const LeftParen&) {
    os << '(';
    return os;
  }
};

class RightParen : public AbstractToken {
private:
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  virtual ~RightParen() {}
  virtual std::string toString() const { return std::string(1, ')'); }
  
  friend std::ostream& operator<<(std::ostream& os, const RightParen&) {
    os << ')';
    return os;
  }
};

inline bool isTokenRightParen(const AbstractToken* ptoken) {
  return (dynamic_cast<const RightParen*>(ptoken) != nullptr);
}

inline bool isTokenLeftParen(const AbstractToken* ptoken) {
  return (dynamic_cast<const LeftParen*>(ptoken) != nullptr);
}

} // namespace scalc

#endif // __PARENTHESIS_HH
