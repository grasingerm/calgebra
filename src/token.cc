#include "token.hh"

namespace scalc {

std::ostream& operator<<(std::ostream& os, const TokenQueue& tq) {
  TokenQueue temp(tq);
  os << "[ ";
  while (!temp.empty()) {
    os << temp.front()->toString() << ' ';
    temp.pop();
  }
  os << ']';
  return os;
}

std::ostream& operator<<(std::ostream& os, const TokenStack& ts) {
  TokenStack temp(ts);
  os << "[ ";
  while (!temp.empty()) {
    os << temp.top()->toString() << ' ';
    temp.pop();
  }
  os << ']';
  return os;
}

}
