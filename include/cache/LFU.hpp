#ifndef __LFU_HPP__
#define __LFU_HPP__

#include "Cache.hpp"
#include <map>
#include <unordered_map>
#include <list>

template<typename Key, typename Value>
class LFUCache : public Cache<Key, Value> {
private:
    std::map<int, std::list<Key>> freqList; // frequency to list of keys
    std::unordered_map<Key, std::pair<Value, typename std::list<Key>::iterator>> itemInfo; // item data and iterator in freqList
    std::unordered_map<Key, int> freq; // frequency counter for each key

    void updateFreq(const Key& key) {
        auto it = itemInfo.find(key);
        if (it == itemInfo.end()) return;

        int currentFreq = freq[key];
        freqList[currentFreq].erase(it->second);
        if (freqList[currentFreq].empty()) {
            freqList.erase(currentFreq);
        }

        ++freq[key];
        freqList[freq[key]].push_front(key);
        it->second = freqList[freq[key]].begin();
    }

public:
    LFUCache(size_t capacity) : Cache<Key, Value>(capacity) {}

    void put(const Key& key, const Value& value) override {
        std::lock_guard<std::mutex> lock(this->mtx);
        
        if (this->data.size() >= this->capacity) {
            auto leastFreq = freqList.begin()->first;
            auto& leastFreqKeys = freqList.begin()->second;
            auto keyToRemove = leastFreqKeys.back();
            this->data.erase(keyToRemove);
            itemInfo.erase(keyToRemove);
            freq.erase(keyToRemove);
            leastFreqKeys.pop_back();
            if (leastFreqKeys.empty()) {
                freqList.erase(leastFreq);
            }
        }

        this->data[key] = value;
        freq[key] = 1;
        freqList[1].push_front(key);
        itemInfo[key] = { value, freqList[1].begin() };
    }

    Value get(const Key& key) override {
        std::lock_guard<std::mutex> lock(this->mtx);
        auto it = this->data.find(key);
        if (it == this->data.end()) {
            throw std::out_of_range("Key not found in cache");
        }
        updateFreq(key);
        return it->second;
    }
};

#endif // __LFU_HPP__