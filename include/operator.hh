#ifndef __OPERATOR_HH
#define __OPERATOR_HH

namespace scalc {

class AbstractOperator {
private:
  int precedence;
public:
  inline int getPrecedence() const { return precedence; }
  double operator()(const double result, )
  virtual ~AbstractOperator()=0;
};

} // namespace scalc

#endif // __OPERATOR_HH
