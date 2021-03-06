#ifndef __OPERATOR_HH
#define __OPERATOR_HH

#include "token.hh"
#include <stdexcept>
#include <iostream>
#include <memory>

namespace scalc {

enum class Associativity { LEFT, RIGHT };

class AbstractOperator : public AbstractToken {
private:
  int precedence;
  Associativity associativity;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const=0; 
  virtual void _pushToTokenStack(TokenStack&) const=0;
public:
  AbstractOperator(const int precedence, const Associativity associativity) :
    precedence(precedence), associativity(associativity) {}
  virtual ~AbstractOperator() {}
  virtual std::string toString() const=0;
  virtual TokenHandler getInverse() const=0;
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
  virtual TokenHandler getInverse() const { 
    throw std::logic_error("Cannot solve equations with '^' operator"); 
    return TokenHandler(nullptr);
  }
  virtual ~Carrot() {}
  virtual std::string toString() const { return std::string(1, '^'); }
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
  inline virtual void _pushToTokenStack(TokenStack& ts) const { 
    ts.emplace(new Carrot()); 
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Carrot&) {
    os << '^';
    return os;
  }
};

class Negation : public AbstractOperator {
public:
  Negation() : AbstractOperator(4, Associativity::RIGHT) {}
  virtual ~Negation() {}
  virtual TokenHandler getInverse() const 
    { return TokenHandler(new Negation()); }
  virtual std::string toString() const { return std::string(1, '-'); }
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
  inline virtual void _pushToTokenStack(TokenStack& ts) const { 
    ts.emplace(new Negation()); 
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Negation&) {
    os << '-';
    return os;
  }
};

class Multiplication : public AbstractOperator {
public:
  Multiplication() : AbstractOperator(3, Associativity::LEFT) {}
  virtual ~Multiplication() {}
  virtual TokenHandler getInverse() const;
  virtual std::string toString() const { return std::string(1, '*'); }
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
  inline virtual void _pushToTokenStack(TokenStack& ts) const { 
    ts.emplace(new Multiplication()); 
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Multiplication&) {
    os << '*';
    return os;
  }
};

class Division : public AbstractOperator {
public:
  Division() : AbstractOperator(3, Associativity::LEFT) {}
  virtual ~Division() {}
  virtual TokenHandler getInverse() const;
  virtual std::string toString() const { return std::string(1, '/'); }
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
  inline virtual void _pushToTokenStack(TokenStack& ts) const { 
    ts.emplace(new Division()); 
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Division&) {
    os << '/';
    return os;
  }
};

class Addition : public AbstractOperator {
public:
  Addition() : AbstractOperator(2, Associativity::LEFT) {}
  virtual ~Addition() {}
  virtual TokenHandler getInverse() const;
  virtual std::string toString() const { return std::string(1, '+'); }
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
  inline virtual void _pushToTokenStack(TokenStack& ts) const { 
    ts.emplace(new Addition()); 
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Addition&) {
    os << '+';
    return os;
  }
};

class Subtraction : public AbstractOperator {
public:
  Subtraction() : AbstractOperator(2, Associativity::LEFT) {}
  virtual ~Subtraction() {}
  virtual TokenHandler getInverse() const;
  virtual std::string toString() const { return std::string(1, '-'); }
private:
  virtual void _eval(TokenQueue&, TokenStack&) const;
  inline virtual void _pushToTokenStack(TokenStack& ts) const { 
    ts.emplace(new Subtraction()); 
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Subtraction&) {
    os << '-';
    return os;
  }
};

} // namespace scalc

#endif // __OPERATOR_HH
