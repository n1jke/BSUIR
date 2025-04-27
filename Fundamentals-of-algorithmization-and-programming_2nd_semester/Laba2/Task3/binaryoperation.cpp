#include "binaryoperation.h"

BinaryOperation::BinaryOperation(Expression* left, Expression* right,
                                 char oper) {
  left_ = left;
  right_ = right;
  operation_ = oper;
}

BinaryOperation::~BinaryOperation() {
  delete left_;
  delete right_;
}

double BinaryOperation::evaluate() {
  double a = left_->evaluate();
  double b = right_->evaluate();
  switch (operation_) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return (b != 0) ? a / b : 0;
    default:
      return 0;
  }
}
