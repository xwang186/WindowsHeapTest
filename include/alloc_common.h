#pragma once
#include <cstddef>
#include <chrono>
struct Result {
    size_t sizeKB;
    double totalSec;
    double avgUs;
};

class Timer {
public:
    Timer();
    void reset();
    double elapsed() const;
private:
    std::chrono::high_resolution_clock::time_point start_;
};

// Core test and printing helpers
Result run_allocation_test(size_t allocSize, size_t iterations);
void print_table_header();
void print_result(const Result& r);