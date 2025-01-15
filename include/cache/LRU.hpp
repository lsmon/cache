#ifndef __LRU_HPP__
#define __LRU_HPP__

#include "Cache.hpp"
#include <list>

template<typename Key, typename Value>
class LRUCache : public Cache<Key, Value> {
private:
    std::list<Key> order;

    void touch(const Key& key) {
        auto it = std::find(order.begin(), order.end(), key);
        if (it != order.end()) {
            order.erase(it);
        }
        order.push_front(key);
    }

public:
    LRUCache(size_t capacity) : Cache<Key, Value>(capacity) {}

    void put(const Key& key, const Value& value) override {
        std::lock_guard<std::mutex> lock(this->mtx);
        
        touch(key);
        if (this->data.size() >= this->capacity) {
            auto& back = order.back();
            this->data.erase(back);
            order.pop_back();
        }
        this->data[key] = value;
    }

    Value get(const Key& key) override {
        std::lock_guard<std::mutex> lock(this->mtx);
        touch(key);
        auto it = this->data.find(key);
        if (it == this->data.end()) {
            throw std::out_of_range("Key not found in cache");
        }
        return it->second;
    }
};


#endif 