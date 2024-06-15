#include "include/Matrix.h"
#include <iostream>

using namespace std;

void test() {
    Matrix<double> A = rand_real_matrix<double>(5, 5);
    Matrix<double> B = inverse(A);
    Matrix<double> C = A * B;
    cout << A << endl << B << endl << C << endl;
}

int main() {
    test();
    return 0;
}