#include "Calculator.h"

void Calculator::push(double n) {
    values.push_back(n);
}

double Calculator::add() {
    double result = 0;
    for(std::list<double>::const_iterator i = values.begin(); i != values.end(); ++i) {
        result += *i;
    }
    return result;
}

double Calculator::divide() {
    double result = 0;
    for(std::list<double>::const_iterator i = values.begin(); i != values.end(); ++i) {
        result /= *i;
    }
    return result;
}

