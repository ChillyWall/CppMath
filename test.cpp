#include "Matrix.h"
#include "Real.h"
#include <iostream>

using namespace std;

void test() {
    auto a = rand_real_matrix<Real>(5, 5);
    cout << a << endl;
}

int main() {
    test();
    return 0;
}