#include "Caching.hpp"

int main() {
    std::vector<std::thread> threads;
    std::unique_ptr<Cache<std::string, int>> cache;

    // Example with LRU cache:
    cache = std::make_unique<LRUCache<std::string, int>>(2);
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(testCache, cache.get());
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
