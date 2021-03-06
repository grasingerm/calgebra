#ifndef __PARSER_HH
#define __PARSER_HH

#include "token.hh"
#include "monomial.hh"
#include <string>

namespace scalc {

enum class ParserMode { NORMAL, LINEAR_EQ_SOLVER };

class Parser {
private:
  ParserMode mode;
  char x;
public:
  Parser() : mode(ParserMode::NORMAL), x('x') {} 
  void setMode(ParserMode newmode) { mode = newmode; }
  TokenQueue exprToInfix(const char*);
  TokenQueue infixToPostfix(TokenQueue&);
  monomial evaluatePostfix(TokenQueue&);

  monomial valueEvaluateExpr(const char*);
  std::string formatEvaluateExpr(const char*);
};

}

#endif
