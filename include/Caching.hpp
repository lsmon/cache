#include "cache/LFU.hpp"
#include "cache/LRU.hpp"
#include "cache/Fifo.hpp"
#include <iostream>
#include <thread>
#include <vector>

void testCache(Cache<std::string, int>* cache);