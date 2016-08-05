#ifndef __TOKEN_HH
#define __TOKEN_HH

#include<stack>
#include<queue>
#include<memory>

namespace scalc {

class AbstractToken;
using TokenStack = std::stack<std::shared_ptr<const AbstractToken>>;
using TokenQueue = std::queue<std::shared_ptr<const AbstractToken>>;

class AbstractToken {
private:
  virtual void _parse(TokenQueue&, TokenStack&) const=0;
  virtual void _eval(TokenQueue&, TokenStack&) const=0; 
public:
  inline void parse(TokenQueue& oq, TokenStack& os) const { _parse(oq, os); }
  inline void eval(TokenQueue& oq, TokenStack& os) const { _eval(oq, os); }
  virtual ~AbstractToken() {}
};

} // namespace scalc

#endif // __TOKEN_HH
