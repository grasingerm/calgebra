#ifndef __TOKEN_HH
#define __TOKEN_HH

#include<stack>
#include<queue>
#include<memory>
#include<iostream>
#include<string>

namespace scalc {

class AbstractToken;
using TokenHandler = std::shared_ptr<const AbstractToken>;
using TokenStack = std::stack<TokenHandler>;
using TokenQueue = std::queue<TokenHandler>;

class AbstractToken {
private:
  virtual void _parse(TokenQueue&, TokenStack&) const=0;
  virtual void _eval(TokenQueue&, TokenStack&) const=0;
public:
  inline void parse(TokenQueue& oq, TokenStack& os) const { _parse(oq, os); }
  inline void eval(TokenQueue& oq, TokenStack& os) const { _eval(oq, os); }
  virtual void simplify(TokenQueue& oq, TokenStack& os) const { _eval(oq, os); }
  virtual ~AbstractToken() {}
  virtual std::string toString() const=0;
};

std::ostream& operator<<(std::ostream&, const TokenQueue&);
std::ostream& operator<<(std::ostream&, const TokenStack&);

} // namespace scalc

#endif // __TOKEN_HH
