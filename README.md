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

## License

Distributed under the terms of the GNU General Public License v3. See [LICENSE](LICENSE)
