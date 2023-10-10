#include "test.h"

extern "C" {
    void print_foo(int x) {
        std::cout << "Calling print_foo! " << x << "\n";
    }

}