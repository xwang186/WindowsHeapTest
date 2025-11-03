#include "alloc_common.h"
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <chrono>


// ---- Timer implementation ----
Timer::Timer() { reset(); }

void Timer::reset() {
    start_ = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() const {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start_).count();
}


Result run_allocation_test(size_t allocSize, size_t iterations) {
    Timer t;
    t.reset();

    for (size_t i = 0; i < iterations; ++i) {
        void* p = std::malloc(allocSize);
        if (p) std::memset(p, 0, allocSize);
        std::free(p);
    }

    double total = t.elapsed();
    double avg = total / iterations * 1e6;
    return {allocSize / 1024, total, avg};
}

void print_table_header() {
    std::cout << "| Size (KB) | Total Time (s) | Avg per alloc (us) |\n";
    std::cout << "|-----------|----------------|--------------------|\n";
}

void print_result(const Result& r) {
    std::cout << "| " << std::setw(9) << r.sizeKB
              << " | " << std::setw(14) << std::fixed << std::setprecision(6) << r.totalSec
              << " | " << std::setw(18) << std::fixed << std::setprecision(3) << r.avgUs
              << " |\n";
}
