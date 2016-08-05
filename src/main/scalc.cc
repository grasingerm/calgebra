#include "scalc.hh"
#include <iostream>
#include <string>

using namespace std;
using namespace scalc;

static const char* prompt = 
  "Enter an expression to evaluate (empty line to quit): ";

int main() {
  string ans, expr;
  Parser parser; 

  cout << '\n' << prompt << '\n';
  getline(cin, expr);

  while (!expr.empty()) {
    try {
      ans = parser.formatEvaluateExpr(expr.c_str());
      cout << ans << "\n\n";
    }
    catch (const std::exception& e) {
      cerr << "ERROR: " << e.what() << '\n';
    }

    cout << prompt << '\n';
    getline(cin, expr);
  }

  return 0;
}
