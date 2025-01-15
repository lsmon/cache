#ifndef __FIFO_HPP__
#define __FIFO_HPP__

#include "Cache.hpp"
#include <list>

template<typename Key, typename Value>
class FIFOCache : public Cache<Key, Value> {
private:
    std::list<Key> order;

public:
    FIFOCache(size_t capacity) : Cache<Key, Value>(capacity) {}

    void put(const Key& key, const Value& value) override {
        std::lock_guard<std::mutex> lock(this->mtx);
        
        if (this->data.size() >= this->capacity) {
            auto& back = order.back();
            this->data.erase(back);
            order.pop_back();
        }
        order.push_front(key);
        this->data[key] = value;
    }

    Value get(const Key& key) override {
        std::lock_guard<std::mutex> lock(this->mtx);
        auto it = this->data.find(key);
        if (it == this->data.end()) {
            throw std::out_of_range("Key not found in cache");
        }
        return it->second;
    }
};


#endif // __FIFO_HPP__