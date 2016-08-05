#ifndef __PARSER_HH
#define __PARSER_HH

#include "token.hh"
#include <string>

namespace scalc {

enum class ParserMode { NORMAL, LINEAR_EQ_SOLVER };

class Parser {
private:
  ParserMode mode;
public:
  Parser() : mode(ParserMode::NORMAL) {} 
  TokenQueue exprToInfix(const char*);
  TokenQueue infixToPostfix(TokenQueue&);
  double evaluatePostfix(TokenQueue&);

  double valueEvaluateExpr(const char*);
  std::string formatEvaluateExpr(const char*);
};

}

#endif
