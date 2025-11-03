#include <vector>
#include "alloc_common.h"

int main() {
    constexpr size_t KB = 1024;
    constexpr size_t ITER = 100000;

    std::vector<size_t> sizes = {
        1*KB, 2*KB, 4*KB, 8*KB, 12*KB, 16*KB, 20*KB, 24*KB,
        32*KB, 48*KB, 64*KB, 80*KB, 96*KB, 112*KB, 128*KB,
        160*KB, 192*KB, 224*KB, 256*KB, 320*KB, 384*KB,
        448*KB, 512*KB, 640*KB, 768*KB, 896*KB, 1024*KB
    };

    print_table_header();
    for (auto s : sizes) {
        auto r = run_allocation_test(s, ITER);
        print_result(r);
    }
    return 0;
}