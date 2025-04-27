#include <iostream>
#include "binaryoperation.h"
#include "number.h"


bool check_equals(Expression const* left, Expression const* right) {
    //cast to void** to get virtualtable
    void** vptr_left = reinterpret_cast<void**>(const_cast<Expression*>(left));
    void** vptr_right =
        reinterpret_cast<void**>(const_cast<Expression*>(right));
    //std::cout << vptr_right << " " << *vptr_right << '\n';
    //std::cout << vptr_left << " " << *vptr_left << '\n';

    return *vptr_left == *vptr_right;
}

const double kFourAndHalf = 4.5;
const double kFive = 5;
const double kTen = 10;


int main() {
    Expression* sub_expr =
        new BinaryOperation(new Number(kFourAndHalf), new Number(kFive), '*');
    Expression* expr = new BinaryOperation(new Number(3), sub_expr, '+');

    std::cout << expr->evaluate() << '\n';

    auto* num = new Number(kTen);
    std::cout << check_equals(sub_expr, num) << '\n';
    std::cout << check_equals(sub_expr, expr) << '\n';

    delete expr;
    return 0;
}
