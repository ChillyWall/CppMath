#include "Real.h"
#include "Integer.h"
#include "LinearAlgebra.h"
#include <iostream>

using namespace std;

void test1() {
    Real::default_precision = 30;
    Real e(2);
    Real term(1);
    for (int i = 2; i < 20; i++) {
        term /= Real(i);
        e += term;
    }
    cout << e << endl;
}

void test2() {
    auto A = rand_real_matrix<Real>(5, 5);
    auto B = A.inv();
    auto C = A * B;
    cout << A << endl << B << endl << C << endl;
}

int main() {
    test2();
    return 0;
}