#include <iostream>
#include <vectors.h>

int main() {
    Vector3 test = Vector3 {1.0, 2.0, 3.0};
    Vector3 test2;
    test.print();
    test2.print();
    test.add(test2).print();
    return 0;
}