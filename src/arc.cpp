#include <iostream>
#include <vectors.h>

int main() {
    Vector3 test = Vector3 {1.0, 2.0, 3.0};
    Vector3 test2 = Vector3 {4.0, 5.0, 6.0};
    test.print();
    test2.print();
    Vector6 test3 = Vector6 {test, test2};
    test3.print();
    auto test_arr = test3.split();
    for (int i=0; i < test_arr.size(); i++) {
        test_arr[i].print();
    }
    //std::cout << test.angle(test2);
    return 0;
}