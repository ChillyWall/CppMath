#include "Real.h"
#include <iostream>

using namespace std;

void test() {
    Real pi("3.141592653589793238462643383279502");
    Real e("-2.71828");
    Real a("1232110940");
    Real b("0.000133423");
    Real sum = pi + e;
    Real dif = pi - e;
    Real prod = pi * e;
    Real div = pi / e;
    cout << pi << endl
        << e << endl
        << a << endl
        << b << endl;

    cout << sum << endl
        << pi - e << endl
        << pi * e << endl
        << pi / e << endl;
}

int main() {
    test();
    return 0;
}