#include <cassert>
#include <iostream>
#include "monomial.hh"
#include <cstdlib>

using namespace std;
using namespace scalc;

int main() {
  double x[] = {0.0, 0.0, 0.0, 0.0}; 
  double c[4];
  monomial m[4];

  for (int k = 0; k < 10000; ++k) {
    for (int i = 0; i < 2; ++i) {
      x[i] = rand();
      c[i] = rand();
      m[i].x = x[i];
      m[i].c = c[i];
    }
    for (int i = 2; i < 4; ++i) {
      c[i] = rand();
      m[i].x = x[i];
      m[i].c = c[i];
    }

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        monomial res;

        assert(ae(m[i] + m[j], m[j] + m[i]));

        res.x = x[i] + x[j];
        res.c = c[i] + c[j];
        assert(ae(m[i] + m[j], res));
        
        res.x = x[i] - x[j];
        res.c = c[i] - c[j];
        assert(ae(m[i] - m[j], res));
      }
    }
    for (int k = 0; k < 2; ++k) {
      monomial res;
      
      res.x = x[k] * c[k+2];
      res.c = c[k] * c[k+2];
      assert(ae(m[k] * m[k+2], res));

      res.x = x[k] / c[k+2];
      res.c = c[k] / c[k+2];
      assert(ae(m[k] / m[k+2], res));

      try {
        m[k] * m[k];
        assert(false);
      }
      catch (const std::exception& e) {
        assert(true);
      }

      try {
        m[k] / m[k];
        assert(false);
      }
      catch (const std::exception& e) {
        assert(true);
      }
    }
  }

  cout << "Tests passed.\n";

  return 0;
}
