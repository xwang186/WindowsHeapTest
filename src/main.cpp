#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <cstring>
#include <cstdlib>

constexpr size_t KB = 1024;
constexpr size_t TEST_ITER = 100000;

void test_allocation(size_t allocSize) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < TEST_ITER; ++i) {
        void* p = std::malloc(allocSize);
        if (p) std::memset(p, 0, allocSize);
        std::free(p);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<double>(end - start).count();

    double perAllocUs = elapsed / TEST_ITER * 1e6;
    std::cout << "| " << std::setw(8) << allocSize / KB << " | "
              << std::setw(10) << std::fixed << std::setprecision(6) << elapsed
              << " | " << std::setw(10) << std::fixed << std::setprecision(3) << perAllocUs
              << " |" << std::endl;
}

int main() {
    std::vector<size_t> sizes = {
        1 * KB, 2 * KB, 4 * KB, 8 * KB, 12 * KB, 16 * KB, 20 * KB, 24 * KB,
        32 * KB, 48 * KB, 64 * KB, 80 * KB, 96 * KB, 112 * KB, 128 * KB, 160 * KB,
        192 * KB, 224 * KB, 256 * KB, 320 * KB, 384 * KB, 448 * KB, 512 * KB,
        640 * KB, 768 * KB, 896 * KB, 1024 * KB
    };

    std::cout << "| Size (KB) | Total Time (s) | Avg per alloc (us) |\n";
    std::cout << "|-----------|----------------|--------------------|\n";

    for (auto s : sizes) {
        test_allocation(s);
    }

    return 0;
}