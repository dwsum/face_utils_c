#include "test.h"

extern "C" {
    void print_foo_c(int x) {
        print_foo(x);
    }
}