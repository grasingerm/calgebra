#ifndef __PARENTHESIS_HH
#define __PARENTHESIS_HH

#include "token.hh"
#include "mfunction.hh"

namespace scalc {

class LeftParen : public AbstractToken {
private:
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  virtual ~LeftParen() {}
};

class RightParen : public AbstractToken {
private:
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  virtual ~RightParen() {}
};

inline bool isTokenRightParen(const AbstractToken* ptoken) {
  return (dynamic_cast<const RightParen*>(ptoken) != nullptr);
}

inline bool isTokenLeftParen(const AbstractToken* ptoken) {
  return (dynamic_cast<const LeftParen*>(ptoken) != nullptr);
}

} // namespace scalc

#endif // __PARENTHESIS_HH
