#include "parser.hh"
#include "operand.hh"
#include "operator.hh"
#include "mfunction.hh"
#include "parenthesis.hh"
#include <cmath>
#include <memory>
#include <cstring>
#include <string>
#include <stdexcept>

using namespace scalc;
using namespace std;

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
        infix_queue.emplace(new LeftParen());
        ++expr;
        break;
      }
      case ')':
      {
        infix_queue.emplace(new RightParen());
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
        const double value = strtod(expr, &pend);
        infix_queue.emplace(new Operand(value));
        expr = pend;
        break;
      }
      default:
      {
        const char* pend = expr;
        size_t n = 1;
        // TODO: should we allow alpha numerics? e.g. log10
        while (isalpha(*(++pend))) ++n;
        string name(expr, n);

        if (name == "log") infix_queue.emplace(new MFunction(log, name));
        else if (name == "exp") infix_queue.emplace(new MFunction(exp, name));
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
