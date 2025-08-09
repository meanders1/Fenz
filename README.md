# Fenz

A set of single-header c++ libraries made for maximum safety while still being performant.

## Array (fenz/array.hpp)

This library provides a set of C++ classes for working with fixed-size arrays and non-owning views over array data. It is header-only and designed for performance and safety.

### Features

- Element access with **compile-time bounds checking**.
- Range-based for loop support.
- Efficient subarray views without copying data.

### Class overview:

- **Array**: Owns its data, fixed size, supports initialization with default values.
- **Iterable**: Non-owning view, allows mutable access and iteration.
- **ConstIterable**: Non-owning view, allows read-only access and iteration.

### Usage

Include the header:

```cpp
#include "fenz/array.hpp"
```

Create an array:

```cpp
fenz::Array<int, 5> arr(0); // Array of 5 ints, initialized to 0
```

Iterate and modify:

```cpp
for(int& value : arr) {
    value = 1;
}

arr.enumerate([](int &value, int index) {
    value += index * 2;
});
```

Create a view:

```cpp
auto view = arr.view<1, 4>(); // View of elements 1 to 3
```

Iterate over the view:

```cpp
int sum = 0;

for(int& value : view) {
    sum += value;
}
```

### API Reference

See [fenz/array.hpp](fenz/array.hpp) for full documentation of:

- [`fenz::Array`](fenz/array.hpp)
- [`fenz::Iterable`](fenz/array.hpp)
- [`fenz::ConstIterable`](fenz/array.hpp)

## Time (fenz/time.hpp)

This header-only library provides types and utilities for safe, efficient time handling in C++. It is designed for performance and clarity, with strong type safety and Doxygen-style documentation.

### Overview

- **fenzTimeSource**: A user-defined function returning the current time in milliseconds since an arbitrary start. **Must be defined by the user for the library to work.**
- **fenz::Duration**: Represents a time duration in milliseconds. Supports conversion to seconds, arithmetic, and comparison.
- **fenz::Moment**: Represents a point in time (in milliseconds, as defined by `fenzTimeSource`). Supports arithmetic and comparison with `Duration` and other `Moment` objects.

### Usage

Include the header:

```cpp
#include "fenz/time.hpp"
```

Define the time source (example using `<chrono>`):

```cpp
#include <chrono>

long long fenzTimeSource() {
        auto now = std::chrono::system_clock::now();
        auto duration_since_epoch = now.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch).count();
        return milliseconds;
}
```

Create and use durations:

```cpp
fenz::Duration d1 = fenz::Duration::fromMillis(500);
fenz::Duration d2 = fenz::Duration::fromSeconds(2.5);
auto total = d1 + d2;
double seconds = total.seconds();
```

Work with moments:

```cpp
fenz::Moment start = fenz::Moment::now();
// ... do work ...
fenz::Moment end = fenz::Moment::now();
fenz::Duration elapsed = end - start;
if (elapsed > fenz::Duration::fromSeconds(1.0)) {
        // More than 1 second has passed
}
```

### API Reference

See [fenz/time.hpp](fenz/time.hpp) for full documentation of:

- [`fenzTimeSource`](fenz/time.hpp): User-defined function returning the current time in milliseconds.
- [`fenz::Duration`](fenz/time.hpp):
  - `fromMillis(long long ms)`: Create from milliseconds.
  - `fromSeconds(double sec)`: Create from seconds.
  - `millis()`: Get milliseconds.
  - `seconds()`: Get seconds as double.
  - Arithmetic and comparison operators.
- [`fenz::Moment`](fenz/time.hpp):
  - `now()`: Get the current moment.
  - Arithmetic and comparison with `Duration` and other `Moment` objects.

All operators and methods are documented in the header file.

## License

Distributed under the terms of the GNU General Public License v3. See [LICENSE](LICENSE)
