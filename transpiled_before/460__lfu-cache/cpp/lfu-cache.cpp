#include <iostream>
#include <unordered_map>
#include <list>
#include <climits>
#include <utility>
#include <algorithm>

using namespace std;

// Time:  O(1), per operation
// Space: O(k), k is the capacity of cache

// using OrderedDict
class LFUCache {
public:
    LFUCache(int capacity) : capacity_(capacity), size_(0), min_freq_(INT_MAX) {}

    int get(int key) {
        if (key_to_freq_.find(key) == key_to_freq_.end()) {
            return -1;
        }
        int freq = key_to_freq_[key];
        int value = freq_to_nodes_[freq].get_value(key);
        update(key, value);
        return value;
    }

    void put(int key, int value) {
        if (capacity_ <= 0) {
            return;
        }
        if (key_to_freq_.find(key) == key_to_freq_.end() && size_ == capacity_) {
            auto& od = freq_to_nodes_[min_freq_];
            int evict_key = od.pop_front_key();
            key_to_freq_.erase(evict_key);
            if (od.empty()) {
                freq_to_nodes_.erase(min_freq_);
            }
            --size_;
        }
        update(key, value);
    }

private:
    struct OrderedDict {
        list<int> order;
        unordered_map<int, pair<list<int>::iterator, int>> m; // key -> (iterator in order, value)

        void set(int key, int value) {
            auto it = m.find(key);
            if (it != m.end()) {
                it->second.second = value;
            } else {
                order.push_back(key);
                auto iter = prev(order.end());
                m.emplace(key, make_pair(iter, value));
            }
        }

        void erase(int key) {
            auto it = m.find(key);
            if (it == m.end()) return;
            order.erase(it->second.first);
            m.erase(it);
        }

        bool empty() const {
            return m.empty();
        }

        int pop_front_key() {
            int k = order.front();
            order.pop_front();
            m.erase(k);
            return k;
        }

        int get_value(int key) const {
            auto it = m.find(key);
            return it->second.second;
        }
    };

    void update(int key, int value) {
        int freq = 0;
        auto it = key_to_freq_.find(key);
        if (it != key_to_freq_.end()) {
            freq = it->second;
            auto fit = freq_to_nodes_.find(freq);
            if (fit != freq_to_nodes_.end()) {
                fit->second.erase(key);
                if (fit->second.empty()) {
                    freq_to_nodes_.erase(fit);
                    if (min_freq_ == freq) {
                        ++min_freq_;
                    }
                }
            }
            --size_;
        }

        ++freq;
        min_freq_ = std::min(min_freq_, freq);
        key_to_freq_[key] = freq;
        freq_to_nodes_[freq].set(key, value);
        ++size_;
    }

    int capacity_;
    int size_;
    int min_freq_;
    unordered_map<int, OrderedDict> freq_to_nodes_;
    unordered_map<int, int> key_to_freq_;
};