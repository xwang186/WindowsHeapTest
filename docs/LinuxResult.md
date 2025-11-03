# Windows Results

## Env
**Compiler**: g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0 
**Compile Mode**: RelWithDebInfo  
**CPU**: 12th Gen Intel(R) Core(TM) i9-12900K (3.20 GHz)  
**RAM**: Samsung SSD 980 PRO 2TB  
**OS/Kernel version**: Ubuntu 24.04.3 LTS (6.14.7-061407-generic)
**glibc version**: ldd (Ubuntu GLIBC 2.39-0ubuntu8.6) 2.39

## Perf Data (Single Thread)
| Size (KB) | Total Time (s) | Avg per alloc (us) |
|-----------|----------------|--------------------|
|        1 |   0.004572 |      0.046 |
|        2 |   0.001619 |      0.016 |
|        4 |   0.009272 |      0.093 |
|        8 |   0.009584 |      0.096 |
|       12 |   0.006842 |      0.068 |
|       16 |   0.013243 |      0.132 |
|       20 |   0.011255 |      0.113 |
|       24 |   0.009162 |      0.092 |
|       32 |   0.012043 |      0.120 |
|       48 |   0.024036 |      0.240 |
|       64 |   0.080464 |      0.805 |
|       80 |   0.098626 |      0.986 |
|       96 |   0.117726 |      1.177 |
|      112 |   0.136893 |      1.369 |
|      128 |   0.156529 |      1.565 |
|      160 |   0.194025 |      1.940 |
|      192 |   0.232239 |      2.322 |
|      224 |   0.272593 |      2.726 |
|      256 |   0.312549 |      3.125 |
|      320 |   0.387003 |      3.870 |
|      384 |   0.464608 |      4.646 |
|      448 |   0.538526 |      5.385 |
|      512 |   0.627070 |      6.271 |
|      640 |   0.775634 |      7.756 |
|      768 |   0.928954 |      9.290 |
|      896 |   1.090843 |     10.908 |
|     1024 |   1.255235 |     12.552 |

## Perf Data (Multiple Thread)
Running deterministic multi-threaded test with 8 threads
Allocation sizes: 150–300 KB (step 10 KB)

=== Summary ===
Threads: 8
Total allocations: 128000000
Average per alloc (us): 2.920
Wall-clock time (s): 5.900
