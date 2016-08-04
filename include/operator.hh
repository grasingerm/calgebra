#ifndef __OPERATOR_HH
#define __OPERATOR_HH

#include "token.hh"
#include <stdexcept>

namespace scalc {

enum class Associativity { LEFT, RIGHT };

class AbstractOperator : public AbstractToken {
private:
  int precedence;
  Associativity associativity;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  AbstractOperator(const int precedence, const Associativity associativity) :
    precedence(precedence), associativity(associativity) {}
  virtual ~AbstractOperator() {}
  inline auto getPrecedence() const noexcept { return precedence; }
  inline auto getAssociativity() const noexcept { return associativity; }
};

inline bool isTokenOperator(const AbstractToken* ptoken) {
  return (dynamic_cast<const AbstractOperator*>(ptoken) != nullptr);
}

int getTokenPrecedence(const AbstractToken* ptoken);

class Carrot : public AbstractOperator {
public:
  Carrot() : AbstractOperator(5, Associativity::RIGHT) {}
  virtual ~Carrot() {}
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
};

class Negation : public AbstractOperator {
public:
  Negation() : AbstractOperator(4, Associativity::RIGHT) {}
  virtual ~Negation() {}
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
};

class Multiplication : public AbstractOperator {
public:
  Multiplication() : AbstractOperator(3, Associativity::LEFT) {}
  virtual ~Multiplication() {}
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
};

class Division : public AbstractOperator {
public:
  Division() : AbstractOperator(3, Associativity::LEFT) {}
  virtual ~Division() {}
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
};

class Addition : public AbstractOperator {
public:
  Addition() : AbstractOperator(2, Associativity::LEFT) {}
  virtual ~Addition() {}
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
};

class Subtraction : public AbstractOperator {
public:
  Subtraction() : AbstractOperator(2, Associativity::LEFT) {}
  virtual ~Subtraction() {}
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
};

} // namespace scalc

#endif // __OPERATOR_HH
