#include <iostream>
#include <chrono>
#include <vector>

constexpr size_t KB = 1024;
constexpr size_t TEST_ITER = 100000;

void test_allocation(size_t allocSize) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < TEST_ITER; ++i) {
        void* p = malloc(allocSize);
        if (p) memset(p, 0, allocSize);
        free(p);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<double>(end - start).count();

    std::cout << allocSize / KB << " KB allocation: "
              << elapsed << " s total ("
              << (elapsed / TEST_ITER * 1e6) << " us per alloc)" << std::endl;
}

int main() {
    std::vector<size_t> sizes = {
        1 * KB, 2 * KB, 4 * KB, 8 * KB, 12 * KB, 16 * KB, 20 * KB, 24 * KB,
        32 * KB, 48 * KB, 64 * KB, 80 * KB, 96 * KB, 112 * KB, 128 * KB, 160 * KB,
        192 * KB, 224 * KB, 256 * KB, 320 * KB, 384 * KB, 448 * KB, 512 * KB,
        640 * KB, 768 * KB, 896 * KB, 1024 * KB
    };

    for (auto s : sizes) {
        test_allocation(s);
    }

    return 0;
}