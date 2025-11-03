#include "alloc_common.h"
#include <thread>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>

struct ThreadStats {
    double totalTime = 0;
    size_t iterations = 0;
};

// Simple argument parser for --threads or -t
static size_t parse_threads_arg(int argc, char** argv, size_t def = 8) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "--threads" || arg == "-t") && i + 1 < argc) {
            return std::stoul(argv[i + 1]);
        }
    }
    return def;
}

int main(int argc, char** argv) {
    constexpr size_t KB = 1024;
    constexpr size_t MIN_SIZE = 150 * KB;
    constexpr size_t MAX_SIZE = 300 * KB;
    constexpr size_t STEP = 10 * KB;
    constexpr size_t ITER_PER_THREAD = 2000000;

    const size_t THREADS = parse_threads_arg(argc, argv, 8);

    std::cout << "Running deterministic multi-threaded test with "
              << THREADS << " threads\n"
              << "Allocation sizes: " << MIN_SIZE / KB << "-" << MAX_SIZE / KB
              << " KB (step " << STEP / KB << " KB)\n";

    std::vector<size_t> sizes;
    for (size_t s = MIN_SIZE; s <= MAX_SIZE; s += STEP)
        sizes.push_back(s);
    const size_t NUM_SIZES = sizes.size();

    std::vector<std::thread> workers;
    std::vector<ThreadStats> stats(THREADS);

    Timer totalTimer;
    totalTimer.reset();

    for (size_t t = 0; t < THREADS; ++t) {
        workers.emplace_back([&, t]() {
            Timer threadTimer;
            threadTimer.reset();

            for (size_t i = 0; i < ITER_PER_THREAD; ++i) {
                size_t allocSize = sizes[i % NUM_SIZES];
                void* p = std::malloc(allocSize);
                std::memset(p, 0, allocSize);
                std::free(p);
            }

            stats[t].totalTime = threadTimer.elapsed();
            stats[t].iterations = ITER_PER_THREAD;
        });
    }

    for (auto& w : workers) w.join();

    double totalWall = totalTimer.elapsed();
    double totalThreadTime = 0;
    size_t totalIter = 0;
    for (auto& s : stats) {
        totalThreadTime += s.totalTime;
        totalIter += s.iterations;
    }

    double avgUs = totalThreadTime / totalIter * 1e6;

    std::cout << "\n=== Summary ===\n";
    std::cout << "Threads: " << THREADS << "\n";
    std::cout << "Total allocations: " << totalIter * THREADS << "\n";
    std::cout << "Average per alloc (us): " << std::fixed << std::setprecision(3)
              << avgUs << "\n";
    std::cout << "Wall-clock time (s): " << std::fixed << std::setprecision(3)
              << totalWall << "\n";

    return 0;
}