#include <iostream>
#include <vectors.h>

int main() {
    Vector3 test = Vector3 {-4.35219416541761e12, -1.20435305698913e12, -3.84635726778866e11};
    Vector3 test2;
    test.print();
    test2.print();
    std::cout << test.mag();
    return 0;
}