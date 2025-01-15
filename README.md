# Caching System

This project implements a generic caching system in C++17 with support for three different eviction policies: **FIFO (First In, First Out)**, **LRU (Least Recently Used)**, and **LFU (Least Frequently Used)**. The implementation is designed to be thread-safe, ensuring robustness in multi-threaded environments.

## Features

- **Generic Cache Interface**: Use any of the three caching strategies through a common interface.
- **Thread Safety**: Utilizes mutexes to ensure safe concurrent access to the cache.
- **Flexible Key-Value Types**: Use any type for keys and values that supports hashing for keys.
- **Capacity Management**: Automatically manages items based on the set capacity, evicting items according to the selected policy.

## Installation

### Prerequisites

- CMake (version 3.5.0 or later)
- A modern C++ compiler with C++17 support

### Building the Project

1. **Clone the repository:**
    ```bash
    git clone [your-repo-url]
    cd caching-system
    ```

2. **Generate the build files**
    ```bash
    cmake -S . -B build
    ```
3. **Build the project:**
    ```bash
    cmake --build build
    ```
    * On Windows, you might want to specify the configuration:
    ```bash
    cmake --build build --config Release
    ```

## Usage
### Example
Here's how you might use the LRU cache:

```cpp
#include "LRU.hpp"
#include <iostream>

int main() {
    LRUCache<std::string, int> cache(2); // Capacity of 2

    cache.put("key1", 1);
    cache.put("key2", 2);
    std::cout << cache.get("key1") << std::endl; // Prints: 1

    cache.put("key3", 3); // key2 will be evicted as it's least recently used
    try {
        cache.get("key2"); // Throws an exception
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
```

### Choosing a Cache Type
* FIFO Cache: Use FIFOCache from FIFO.hpp.
* LRU Cache: Use LRUCache from LRU.hpp.
* LFU Cache: Use LFUCache from LFU.hpp.

Each type inherits from the Cache class in Cache.hpp, allowing you to switch policies easily.

### Testing
This project includes a simple testing mechanism. To enable testing:

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
cd build
ctest
```

### Contributing
Contributions are welcome! Please:

* Fork the repository
* Create a new branch for your feature or fix
* Commit your changes
* Create a pull request

### License
MIT License

<!-- ### Acknowledgements -->


### Contact
* https://www.x.com/@lsmon714
* https://linkedin.com/in/salomon-lee
* https://www.salomonlee.com
