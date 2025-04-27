#ifndef NUMBER_H
#define NUMBER_H
#include "expression.h"

class Number : public Expression {
 private:
  double value_;

 public:
  Number(double val) { value_ = val; }

  double evaluate() override { return value_; }

  void setValue(double newVal) { value_ = newVal; }
};

#endif  // NUMBER_H
