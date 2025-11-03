# Memory Allocation Threshold Benchmark

This project demonstrates and verifies **Windows heap allocation thresholds** — specifically how allocation performance changes when the requested memory size exceeds internal thresholds (such as **16 KB**, **128 KB**, and **512 KB**).  

The goal is to **measure and visualize performance degradation** that occurs when the system transitions between:
- **Low Fragmentation Heap (LFH)** — fastest, small allocations.
- **Standard Heap Segments** — medium-size allocations.
- **VirtualAlloc-backed large blocks** — slow, kernel-mode allocations.

Although the thresholds are Windows-specific, this benchmark can also be built and executed on Linux to observe how `malloc()` and `mmap()` behaviors differ.

---

## 🧠 Problem Statement

Memory allocation on modern systems is not uniform — large allocations may bypass user-mode heaps and fall back to OS-level page allocations.  
This behavior is **not obvious to developers**, yet it can have a huge impact on performance when memory blocks exceed certain thresholds.

This demo helps:
- Quantify the performance difference across allocation sizes.
- Identify threshold boundaries (e.g., ~16 KB, ~128 KB, ~512 KB on Windows).
- Compare allocation behavior between Windows and Linux.

## **Results Summary**

| Scenario | Linux behavior | Windows behavior |
|-----------|----------------|------------------|
| **Single-thread** | Smooth, near-linear latency across all sizes; no performance cliff even above 1 MB | Clear slowdown near ~1 MB when allocator switches from heap to `VirtualAlloc()` |
| **Multi-thread (8 threads)** | Scales well due to per-thread arenas; minimal locking overhead | ~3–4× slower; heap lock contention and `VirtualAlloc` commit overhead dominate |
| **Memory commit policy** | Lazy page commit (`mmap` / `brk`) | Immediate zero-fill on `VirtualAlloc` commit |
| **Recommended mitigation** | Optional pooling for very large blocks | Strongly prefer pooling or reserved sub-allocation to avoid repeated `VirtualAlloc()` |

## Results

 [Windows Results](./docs/WinResult.md)  
 [Linux Results](./docs/LinuxResult.md)  
