# vl_vector Project

This repository contains an implementation of a custom dynamic array data structure in C++, called `vl_vector`,
designed to optimize both memory usage and runtime performance through a hybrid allocation strategy.
 Additionally, it includes a `vl_string` class, which inherits from `vl_vector<char>` and provides string-specific operations.


The project is written in modern C++20 and uses template-based programming to allow generic usage with
different data types. The implementation includes full iterator support, dynamic/static memory handling, and basic STL-like functionality.

---

## Project Overview

### vl_vector

`vl_vector<T, StaticCapacity>` is a generic vector-like container that supports:

- Static memory allocation for small sequences (up to `StaticCapacity` elements)
- Heap allocation for larger sequences beyond the static threshold
- Efficient memory growth using the formula: `(3*(n + k))/2`
- Random-access iterator support (`begin`, `end`, `rbegin`, `cbegin`, etc.)
- Custom implementations of common operations: `push_back`, `insert`, `erase`, `clear`, `pop_back`
- Equality and inequality operators
- Bounds-safe element access via `at()` and `[]`
- Move/copy constructors and initializations using iterators or initializer lists

The internal storage switches between static buffer (`T st_data[StaticCapacity]`) and dynamically allocated heap memory (`T* heap_data`), depending on the size.

### vl_string

`vl_string<StaticCapacity>` is a specialized string class based on `vl_vector<char, StaticCapacity>`. It supports:

- Construction from `const char*`
- Appending with `+=` for both characters and C-strings
- Concatenation with `+` operators (both left and right sided)
- Implicit conversion to `std::string`
- Manual memory management for internal storage to reduce allocations

`vl_string` provides more efficient string manipulation than `std::string` in certain use cases where small strings are common and heap allocations are expensive.

---

## File Structure

- `vl_vector.hpp`: The main implementation of the templated `vl_vector` class
- `vl_string.hpp`: Implementation of `vl_string`, inheriting from `vl_vector<char>`
- `helpers.h`: General utility code (if applicable)
- `CMakeLists.txt`: CMake configuration file for building the project

---

## Build Instructions

This project uses CMake for building.

```bash
# Clone the repository
git clone https://github.com/aviel12-coll/vl_vector.git
cd vl_vector

# Build the project with CMake
cmake -S . -B build
cmake --build build