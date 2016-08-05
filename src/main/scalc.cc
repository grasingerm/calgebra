#include "scalc.hh"
#include <iostream>
#include <string>

using namespace std;
using namespace scalc;

static const char* prompt = 
  "Use command 'set mode normal' or 'set mode solve' to change calculator mode"
  "\nEnter an expression to evaluate (empty line or 'exit' to quit):\n";

int main() {
  string ans, expr;
  Parser parser; 

  cout << '\n' << prompt << '\n';
  getline(cin, expr);

  while (!expr.empty() && !(expr == "exit")) {
    if (expr == "set mode normal") {
      parser.setMode(ParserMode::NORMAL);
      cout << "Set calculator mode to 'normal'\n\n";
    }
    else if (expr == "set mode solve") {
      parser.setMode(ParserMode::LINEAR_EQ_SOLVER);
      cout << "Set calculator mode to 'solve'\n\n";
    }
    else {
      try {
        ans = parser.formatEvaluateExpr(expr.c_str());
        cout << ans << "\n\n";
      }
      catch (const std::exception& e) {
        cerr << "ERROR: " << e.what() << "\n\n";
      }
    }
    
    cout << prompt << '\n';
    getline(cin, expr);
  }

  return 0;
}
