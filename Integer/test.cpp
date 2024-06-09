#include "Integer.h"

using namespace std;

void test_constr() {
    Integer n1;
    Integer n2(123456789);
    Integer n3("-3141592653589793238462643383279502");
    Integer n4(n3);
    cout << n1 << endl << n2 << endl << n3 << endl << n4 << endl;
    n2 = "271828";
    n3 = n2;
    cout << n2 << endl << n3 << endl;
}

void test_operation() {
    Integer n2(123456789);
    Integer n3("-3141592");

    cout << n2 + n3 << endl;
    cout << n2 - n3 << endl;
    cout << n2 * n3 << endl;
    cout << n2 / n3 << endl;
}

int main() {
    test_operation();
    return 0;
}