#include <iostream>
#include <vectors.h>

int main() {
    Vector3 test = Vector3 {1.0, 2.0, 3.0};
    Vector3 test2 = Vector3 {4.0, 5.0, 6.0};
    test.print();
    test2.print();
    test.change_origin(test2).print();
    //std::cout << test.angle(test2);
    return 0;
}