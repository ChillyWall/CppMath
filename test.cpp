#include "Real.h"
#include "Integer.h"
#include "Matrix.h"
#include<iostream>

using namespace std;

void test1() {
    default_random_engine e;
    e.seed(time(0));
    uniform_real_distribution<long double> s(-1000, 1000);
    for (int i = 100; i > 0; i--) {
        Real a(s(e) * 10000);
        Real b(s(e));
        cout << "a: " << a << ",   b: " << b << endl
            << "a + b = " << a + b << endl
            << "a - b = " << a - b << endl
            << "a * b = " << a * b << endl
            << "a / b = " << a / b << endl;
    }
}

void test2() {
    Matrix<Real> A(3, 3, {Real(2), Real(4), Real(1), Real(5), Real(3), Real(4), Real(1), Real(9), Real(2)});
    cout << A << endl;
    auto B = inverse(A);
    cout << B << endl;
    auto C = A * B;
    cout << C << endl;
}

void test5() {
    Matrix<double> A(3, 3, {2, 4, 1, 5, 3, 4, 1, 9, 2});
    cout << A << endl;
    auto B = inverse(A);
    cout << B << endl;
    auto C = A * B;
    cout << C << endl;
}

void test3() {
    Real a("3.141592653589793238462643383279502", 0);
    Real b("2.7182818284590452353602874713527", 0);
    cout << a << endl << b << endl;
    cout << a + b << endl;
    b += a;
    cout << b << endl;
}

void test4() {
    Real a("-0.3333333333");
    cout << a << endl;
    Real b("1.2");
    cout << b << endl;
    Real c = a * b;
    cout << c << endl;
}

int main() {
    test2();
    return 0;
}