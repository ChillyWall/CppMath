#ifndef MATH_H_
#define MATH_H_ 1

#include "Real.h"

const static char* pi = "3.141592653589793238462643383279502";
const static char* e = "2.7182818284590452353602874713527";

template <typename Int>
Int factorial(const Int& n) {
    Int res(1);
    for (Int i(2); i <= n; i++) {
        res *= i;
    }
    return res;
}

#endif