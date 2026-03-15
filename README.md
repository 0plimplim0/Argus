# Argus | High-Performance Text Analyzer

Argus is a text-analysis engine built in C++ (Zero-Dependency), designed for maximum throughput and minimal memory footprint.

**Current Performance:** Processes **1GB of raw text in 1.43s**.

### Key Technical Features
* **Zero-Copy Logic:** Using `std::string_view` to reference data directly in the buffer, avoiding heap allocations during the search phase.
* **Custom Argument Parser:** Built from scratch to avoid the overhead of heavy external libraries.
* **Memory Efficiency:** Uses `std::ios::ate` for precise buffer sizing and `reserve()` strategies to prevent vector reallocations.

## Benchmarks (1GB Plain text)

### **v0.1**

| Tool | Real Time | User Time | System Time | Notes |
| :--- | :--- | :--- | :--- | :--- |
| **grep -F** | 0.466s | 0.306s | 0.171s | Industry Standard (C/ASM) |
| **Argus** | 1.438s | 0.691s | 0.750s | Initial C++ Implementation |

## Requirements
* **Compiler:** `g++` (GCC 12+) with C++23 support.
* **Build System:** `make`.

## Roadmap
* [X] **v0.1:** Implementation of full RAM loading with zero-copy pointer logic for minimal latency.
* [ ] **v0.2:** Implementation of **Sliding Window Buffer (Chunks)** to process files larger than available RAM (1MB buffers).

## Building & Running
```bash
make
./build/argus --pattern="your_pattern" filename.txt
```
**For test speed:**
```bash
time ./build/argus --pattern="your_pattern" filename.txt
```

## License

[MIT](./LICENSE)
