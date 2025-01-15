#include "Caching.hpp"

void testCache(Cache<std::string, int>* cache) {
    cache->put("a", 1);
    std::cout << cache->get("a") << std::endl;
    cache->put("b", 2);
    try {
        cache->get("c"); // Throws an exception
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}