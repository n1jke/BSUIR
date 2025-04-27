#ifndef BINARYOPERATION_H
#define BINARYOPERATION_H
#include <expression.h>

class BinaryOperation : public Expression {
 private:
  Expression* left_;
  Expression* right_;
  char operation_;

 public:
  BinaryOperation(Expression* left, Expression* right, char oper);

  ~BinaryOperation() override;

  double evaluate() override;
};

#endif  // BINARYOPERATION_H
