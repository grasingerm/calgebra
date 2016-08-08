#include "parser.hh"
#include "operand.hh"
#include "operator.hh"
#include "mfunction.hh"
#include "parenthesis.hh"
#include "monomial.hh"
#include <cmath>
#include <memory>
#include <cstring>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

namespace scalc {

TokenQueue Parser::exprToInfix(const char* expr) {
  TokenQueue infix_queue;

  while (expr[0] != '\0') {
    switch(expr[0]) {
      case '^': 
      {
        infix_queue.emplace(new Carrot());
        ++expr;
        break;
      }
      case '-':
      {
        if (infix_queue.empty() || isTokenOperator(infix_queue.back().get())
            || isTokenLeftParen(infix_queue.back().get()))
          infix_queue.emplace(new Negation());
        else infix_queue.emplace(new Subtraction());
        ++expr;
        break;
      }
      case '*':
      {
        infix_queue.emplace(new Multiplication());
        ++expr;
        break;
      }
      case '/':
      {
        infix_queue.emplace(new Division());
        ++expr;
        break;
      }
      case '+':
      {
        infix_queue.emplace(new Addition());
        ++expr;
        break;
      }
      case '(':
      {
        if (!infix_queue.empty() && !isTokenOperator(infix_queue.back().get())
            && !isTokenFunction(infix_queue.back().get()))
          infix_queue.emplace(new Multiplication());

        infix_queue.emplace(new LeftParen());
        ++expr;
        break;
      }
      case ')':
      {
        infix_queue.emplace(new RightParen());
        while (*(expr+1) == ' ') ++expr;
        if (isalnum(*(expr+1)) || *(expr+1) == '(') 
          infix_queue.emplace(new Multiplication());
        ++expr;
        break;
      }
      case ' ':
      {
        ++expr;
        break;
      }
      case '.':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
      {
        char* pend;
        const monomial m {0.0, strtod(expr, &pend)};
        infix_queue.emplace(new Operand(m));
        expr = pend;
        break;
      }
      case '=':
      {
        if (mode == ParserMode::NORMAL)
          throw runtime_error("Equals sign '=' should not be used in 'normal' "
                              "mode");
        break;
      }
      default:
      {
        if (!infix_queue.empty() && isTokenOperand(infix_queue.back().get()))
          infix_queue.emplace(new Multiplication());

        if (*expr == this->x) {
          const monomial m {1.0, 0.0};
          infix_queue.emplace(new Operand(m));
          ++expr;
          break;
        }

        const char* pend = expr;
        size_t n = 1;
        // TODO: should we allow alpha numerics? e.g. log10
        while (isalpha(*(++pend))) ++n;
        string name(expr, n);

        if (name == "log") infix_queue.emplace(new MFunction(log, name));
        else if (name == "exp") infix_queue.emplace(new MFunction(exp, name));
        else if (name == "abs") infix_queue.emplace(new MFunction(std::abs, name));
        else if (name == "sin") infix_queue.emplace(new MFunction(sin, name));
        else if (name == "cos") infix_queue.emplace(new MFunction(cos, name));
        else if (name == "tan") infix_queue.emplace(new MFunction(tan, name));
        else if (name == "asin") infix_queue.emplace(new MFunction(asin, name));
        else if (name == "acos") infix_queue.emplace(new MFunction(acos, name));
        else if (name == "atan") infix_queue.emplace(new MFunction(atan, name));
        else if (name == "sinh") infix_queue.emplace(new MFunction(sinh, name));
        else if (name == "cosh") infix_queue.emplace(new MFunction(cosh, name));
        else if (name == "tanh") infix_queue.emplace(new MFunction(tanh, name));
        else if (name == "asinh") infix_queue.emplace(new MFunction(asinh, name));
        else if (name == "acosh") infix_queue.emplace(new MFunction(acosh, name));
        else if (name == "atanh") infix_queue.emplace(new MFunction(atanh, name));
        else 
          throw logic_error(string("Do not understand function name: ") + name);
        
        expr = pend;
        break;
      }
    }
  }

  return infix_queue;
}

TokenQueue Parser::infixToPostfix(TokenQueue& infix_queue) {
  TokenQueue postfix_queue;
  TokenStack opstack;

  while (!infix_queue.empty()) {
    const auto ptoken = infix_queue.front();
    ptoken->parse(postfix_queue, opstack);
    infix_queue.pop();
  }

  while (!opstack.empty()) {
    const auto ptoken = opstack.top();
    postfix_queue.emplace(ptoken);
    opstack.pop();
  }

  return postfix_queue;
}

monomial Parser::evaluatePostfix(TokenQueue& postfix_queue) {
  TokenStack token_stack;

  while (!postfix_queue.empty()) {
    const auto ptoken = postfix_queue.front();
    ptoken->eval(postfix_queue, token_stack);
    postfix_queue.pop();
  }

  const auto retval = popOperandValue(token_stack, "final value");
  if (!token_stack.empty()) throw logic_error("Tokens left on the stack");

  return retval;
}

monomial Parser::valueEvaluateExpr(const char* expr) {
  if (mode == ParserMode::NORMAL) {
    TokenQueue infix_queue = exprToInfix(expr);
    TokenQueue postfix_queue = infixToPostfix(infix_queue);
    if (postfix_queue.empty()) throw logic_error("Expression is empty of operands");
    return evaluatePostfix(postfix_queue);
  }
  else if (mode == ParserMode::LINEAR_EQ_SOLVER) {
    string sexpr(expr);
    auto eqpos = sexpr.find('=');
    if (eqpos != string::npos) {

      auto lhs_str = sexpr.substr(0, eqpos-1);
      auto rhs_str = sexpr.substr(eqpos+1);

      if (rhs_str.find('=') != string::npos)
        throw logic_error("More than one equals sign '=' in expression");

      // simplify left hand side
      auto lhs_inqueue  = exprToInfix(lhs_str.c_str());
      auto lhs_posqueue = infixToPostfix(lhs_inqueue);
      const auto lhs    = evaluatePostfix(lhs_posqueue);

      // simplify right hand side
      auto rhs_inqueue  = exprToInfix(rhs_str.c_str());
      auto rhs_posqueue = infixToPostfix(rhs_inqueue);
      const auto rhs    = evaluatePostfix(rhs_posqueue);

      // solve for x
      const auto denominator = rhs.x - lhs.x;
      if (denominator == 0) 
        throw logic_error("Equation is not solvable; x is eliminated.");
      const monomial x = (lhs.c - rhs.c) / denominator;

      return x;
    }
    else throw logic_error("No equals sign '=' in expression");
  }
  else throw logic_error("Parser mode is invalid");
}

string Parser::formatEvaluateExpr(const char* expr) {
  stringstream ss;
  if (mode == ParserMode::NORMAL) {
    ss << "ans = " << valueEvaluateExpr(expr);
    return ss.str();
  }
  else if (mode == ParserMode::LINEAR_EQ_SOLVER) {
    ss << "x = " << valueEvaluateExpr(expr);
    return ss.str();
  }
  else throw logic_error("Parser mode is invalid");
}

}
