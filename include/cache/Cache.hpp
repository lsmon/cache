#ifndef __CACHE_HPP__
#define __CACHE_HPP__

#include <unordered_map>
#include <mutex>
#include <memory>
#include <stdexcept>

template<typename Key, typename Value>
class Cache {
protected:
    size_t capacity;
    std::unordered_map<Key, Value> data;
    mutable std::mutex mtx;

    Cache(size_t capacity) : capacity(capacity) {}

public:
    virtual ~Cache() = default;

    virtual bool exists(const Key& key) const {
        std::lock_guard<std::mutex> lock(mtx);
        return data.find(key) != data.end();
    }

    virtual size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data.size();
    }

    virtual void put(const Key& key, const Value& value) = 0;
    virtual Value get(const Key& key) = 0;
    virtual void erase(const Key& key) {
        std::lock_guard<std::mutex> lock(mtx);
        data.erase(key);
    }

    size_t getCapacity() const {
        return capacity;
    }
};

#endif // __CACHE_HPP__
