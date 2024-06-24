#include "Real.h"
#include "Integer.h"
#include "LinearAlgebra.h"
#include <iostream>

using namespace std;

void test1()
{
    default_random_engine e;
    e.seed(time(0));
    uniform_real_distribution<long double> s(-1000, 1000);
    Real a;
    Real b;
    double ad;
    double bd;
    for (int i = 100; i > 0; i--)
    {
        ad = s(e);
        bd = s(e);
        a = ad;
        b = bd;
        cout << "Real:\na: " << a << ",   b: " << b << endl
             << "a + b = " << a + b << endl
             << "a - b = " << a - b << endl
             << "a * b = " << a * b << endl
             << "a / b = " << a / b << endl
             << "\ndouble:\na: " << ad << ",   b: " << bd << endl
             << "a + b = " << ad + bd << endl
             << "a - b = " << ad - bd << endl
             << "a * b = " << ad * bd << endl
             << "a / b = " << ad / bd << endl;
    }
}

void test2()
{
    Matrix<Real> A(5, 5, {
        Real(0.473433), Real(0.120688), Real(-0.728248), Real(0.997545), Real(0.02901), Real(0.524752), Real(0.773064), Real(-0.633016), Real(0.211179), Real(-0.349263), Real(-0.843103), Real(0.690887), Real(-0.77325), Real(-0.428949), Real(0.455823), Real(-0.644143), Real(-0.587645), Real(0.372893), Real(0.766187), Real(0.909021), Real(0.503164), Real(0.759169), Real(0.035798), Real(0.732717), Real(-0.864868)});
    cout << A << endl;
    auto B = inverse(A);
    cout << B << endl;
    auto C = A * B;
    cout << C << endl;
}

void test5()
{
    Matrix<double> A(5, 5, {
        0.473433, 0.120688, -0.728248, 0.997545, 0.02901, 
        0.524752, 0.773064, -0.633016, 0.211179, -0.349263, 
        -0.843103, 0.690887, -0.77325, -0.428949, 0.455823, 
        -0.644143, -0.587645, 0.372893, 0.766187, 0.909021, 
        0.503164, 0.759169, 0.035798, 0.732717, -0.864868});
    cout << A << endl;
    auto B = inverse(A);
    cout << B << endl;
    auto C = A * B;
    cout << C << endl;
}

void test3()
{
    Real a("3.141592653589793238462643383279502", 0);
    Real b("2.7182818284590452353602874713527", 0);
    cout << a << endl
         << b << endl;
    cout << a + b << endl;
    b += a;
    cout << b << endl;
}

void test4()
{
    Real a("-1.1154927538");
    Real b("1.2030759143");
    Real l = a / b;
    Real c("-0.0655562276");
    Real d("0.5607655737");
    cout << "l = " << l << endl;
    Real e = c * l;
    cout << "e = " << e << endl;
    d -= e;
    cout << "d = " << d << endl;
    cout << -1.1154927538 / 1.2030759143 << endl;
}

int main()
{
    test1();
    return 0;
}