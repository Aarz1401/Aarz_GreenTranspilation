#include <iostream>
#include <unordered_map>
#include <list>
#include <climits>
#include <utility>
#include <algorithm>
#include <chrono>

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

// 10 diverse test scenarios

long long scenario1() {
    LFUCache c(2);
    long long s = 0;
    c.put(1, 1);
    c.put(2, 2);
    s += c.get(1);      // 1
    c.put(3, 3);        // evict 2
    s += c.get(2);      // -1
    s += c.get(3);      // 3
    c.put(4, 4);        // evict 1
    s += c.get(1);      // -1
    s += c.get(3);      // 3
    s += c.get(4);      // 4
    return s;
}

long long scenario2() {
    LFUCache c(3);
    long long s = 0;
    c.put(2, 2);
    c.put(3, 3);
    c.put(4, 4);
    s += c.get(4);
    s += c.get(4);
    s += c.get(4);
    c.put(5, 5);        // evict 2
    s += c.get(2);      // -1
    s += c.get(3);      // 3
    s += c.get(4);      // 4
    s += c.get(5);      // 5
    return s;
}

long long scenario3() {
    LFUCache c(0);
    long long s = 0;
    c.put(1, 1);
    s += c.get(1);      // -1
    c.put(2, 2);
    s += c.get(2);      // -1
    return s;
}

long long scenario4() {
    LFUCache c(2);
    long long s = 0;
    c.put(1, 1);
    c.put(2, 2);
    c.put(2, 20);       // update value, increase freq
    s += c.get(2);      // 20
    c.put(3, 3);        // evict 1
    s += c.get(1);      // -1
    s += c.get(3);      // 3
    s += c.get(2);      // 20
    return s;
}

long long scenario5() {
    LFUCache c(2);
    long long s = 0;
    c.put(1, 1);
    c.put(2, 2);
    s += c.get(1);      // 1
    s += c.get(2);      // 2
    c.put(3, 3);        // evict 1 due to order in freq 2
    s += c.get(1);      // -1
    s += c.get(2);      // 2
    s += c.get(3);      // 3
    return s;
}

long long scenario6() {
    LFUCache c(5);
    long long s = 0;
    c.put(-1, 100);
    c.put(10, 200);
    c.put(20, 300);
    s += c.get(-1);     // 100 (increase freq)
    s += c.get(10);     // 200 (increase freq)
    c.put(30, 400);
    c.put(40, 500);
    s += c.get(999);    // -1
    c.put(50, 600);     // evict 20 (LFU among freq 1)
    s += c.get(20);     // -1
    s += c.get(50);     // 600
    s += c.get(-1);     // 100
    s += c.get(40);     // 500
    return s;
}

long long scenario7() {
    LFUCache c(3);
    long long s = 0;
    c.put(1, 1);
    c.put(2, 2);
    c.put(3, 3);
    for (int i = 0; i < 5; ++i) s += c.get(2); // bump 2
    for (int i = 0; i < 3; ++i) s += c.get(1); // bump 1
    c.put(4, 4);        // evict 3
    s += c.get(3);      // -1
    s += c.get(1);      // 1
    s += c.get(2);      // 2
    s += c.get(4);      // 4
    return s;
}

long long scenario8() {
    LFUCache c(2);
    long long s = 0;
    c.put(1, 1);
    c.put(2, 2);
    c.put(1, 10);       // update value and increase freq
    s += c.get(1);      // 10
    c.put(3, 3);        // evict 2 (LFU)
    s += c.get(2);      // -1
    s += c.get(3);      // 3
    s += c.get(1);      // 10
    return s;
}

long long scenario9() {
    LFUCache c(3);
    long long s = 0;
    c.put(INT_MAX, INT_MIN);
    c.put(INT_MIN, INT_MAX);
    s += c.get(INT_MAX); // INT_MIN, bump its freq
    c.put(0, 0);
    c.put(1, 1);         // evict INT_MIN
    s += c.get(INT_MIN); // -1
    s += c.get(0);       // 0
    s += c.get(1);       // 1
    s += c.get(INT_MAX); // INT_MIN
    return s;
}

long long scenario10() {
    LFUCache c(1);
    long long s = 0;
    s += c.get(42);      // -1
    c.put(5, 5);
    s += c.get(5);       // 5
    s += c.get(6);       // -1
    c.put(6, 6);         // evict 5
    s += c.get(5);       // -1
    s += c.get(6);       // 6
    return s;
}

long long run_all_scenarios() {
    long long total = 0;
    total += scenario1();
    total += scenario2();
    total += scenario3();
    total += scenario4();
    total += scenario5();
    total += scenario6();
    total += scenario7();
    total += scenario8();
    total += scenario9();
    total += scenario10();
    return total;
}

int main() {
    using std::chrono::high_resolution_clock;

    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        checksum += run_all_scenarios();
    }
    auto end = high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}