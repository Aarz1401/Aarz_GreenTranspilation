#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <cstdint>

// Original solution (used without modification)
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AllOne {
private:
    struct Node {
        int value;
        unordered_set<string> keys;
        Node* prev;
        Node* next;
        explicit Node(int v) : value(v), prev(nullptr), next(nullptr) {}
    };

    struct LinkedList {
        Node* head;
        Node* tail;
        LinkedList() {
            head = new Node(0);
            tail = new Node(0);
            head->next = tail;
            tail->prev = head;
        }
        ~LinkedList() {
            Node* cur = head;
            while (cur) {
                Node* nxt = cur->next;
                delete cur;
                cur = nxt;
            }
        }
        Node* insert(Node* pos, Node* node) {
            Node* p = pos->prev;
            node->prev = p;
            node->next = pos;
            p->next = node;
            pos->prev = node;
            return node;
        }
        void erase(Node* node) {
            Node* p = node->prev;
            Node* n = node->next;
            p->next = n;
            n->prev = p;
            delete node;
        }
        bool empty() const {
            return head->next == tail;
        }
        Node* begin() const {
            return head->next;
        }
        Node* end() const {
            return tail;
        }
        Node* front() const {
            return head->next;
        }
        Node* back() const {
            return tail->prev;
        }
    };

    unordered_map<string, Node*> bucket_of_key;
    LinkedList buckets;

public:
    AllOne() {}

    void inc(string key) {
        if (!bucket_of_key.count(key)) {
            Node* zero = new Node(0);
            zero->keys.insert(key);
            bucket_of_key[key] = buckets.insert(buckets.begin(), zero);
        }
        Node* bucket = bucket_of_key[key];
        Node* next_bucket = bucket->next;
        if (next_bucket == buckets.end() || next_bucket->value > bucket->value + 1) {
            next_bucket = buckets.insert(next_bucket, new Node(bucket->value + 1));
        }
        next_bucket->keys.insert(key);
        bucket_of_key[key] = next_bucket;

        bucket->keys.erase(key);
        if (bucket->keys.empty()) {
            buckets.erase(bucket);
        }
    }

    void dec(string key) {
        if (!bucket_of_key.count(key)) {
            return;
        }
        Node* bucket = bucket_of_key[key];
        Node* prev_bucket = bucket->prev;
        bucket_of_key.erase(key);

        if (bucket->value > 1) {
            if (bucket == buckets.begin() || prev_bucket->value < bucket->value - 1) {
                prev_bucket = buckets.insert(bucket, new Node(bucket->value - 1));
            }
            prev_bucket->keys.insert(key);
            bucket_of_key[key] = prev_bucket;
        }

        bucket->keys.erase(key);
        if (bucket->keys.empty()) {
            buckets.erase(bucket);
        }
    }

    string getMaxKey() {
        if (buckets.empty()) return "";
        const auto& ks = buckets.back()->keys;
        if (ks.empty()) return "";  // Safety, though shouldn't happen
        return *(ks.begin());
    }

    string getMinKey() {
        if (buckets.empty()) return "";
        const auto& ks = buckets.front()->keys;
        if (ks.empty()) return "";  // Safety, though shouldn't happen
        return *(ks.begin());
    }
};

// Benchmark harness
struct Op {
    char type;     // 'I' = inc, 'D' = dec, 'X' = getMaxKey, 'N' = getMinKey
    std::string key;
};

struct TestCase {
    std::vector<Op> ops;
};

static inline uint64_t hashStr(const std::string& s) {
    uint64_t h = 1469598103934665603ull; // FNV-1a 64-bit offset
    for (unsigned char c : s) {
        h ^= c;
        h *= 1099511628211ull; // FNV prime
    }
    return h;
}

uint64_t runTest(const TestCase& tc) {
    AllOne ds;
    uint64_t local = 0;
    for (const auto& op : tc.ops) {
        switch (op.type) {
            case 'I':
                ds.inc(op.key);
                break;
            case 'D':
                ds.dec(op.key);
                break;
            case 'X': {
                std::string s = ds.getMaxKey();
                local ^= (hashStr(s) + 0x9e3779b97f4a7c15ull);
                local = (local << 7) | (local >> 57);
                break;
            }
            case 'N': {
                std::string s = ds.getMinKey();
                local ^= (hashStr(s) + 0xc2b2ae3d27d4eb4full);
                local = (local << 9) | (local >> 55);
                break;
            }
            default:
                break;
        }
    }
    // Mix in final state
    local ^= hashStr(ds.getMaxKey()) + 0x165667b19e3779f9ull;
    local ^= hashStr(ds.getMinKey()) + 0x85ebca6b27d4eb4full;
    return local;
}

std::vector<TestCase> buildTests() {
    std::vector<TestCase> tests;
    tests.reserve(10);

    // 1) Basic increments and queries
    tests.push_back(TestCase{
        {
            {'I',"a"}, {'I',"b"}, {'I',"a"},
            {'X',""}, {'N',""}
        }
    });

    // 2) Decrement to removal
    tests.push_back(TestCase{
        {
            {'I',"a"}, {'D',"a"},
            {'X',""}, {'N',""}
        }
    });

    // 3) Multiple keys with varied counts
    tests.push_back(TestCase{
        {
            {'I',"apple"}, {'I',"banana"}, {'I',"carrot"},
            {'I',"banana"}, {'I',"banana"}, {'I',"apple"},
            {'X',""}, {'N',""}, {'D',"banana"}, {'X',""}, {'N',""}
        }
    });

    // 4) Ties and min removal
    tests.push_back(TestCase{
        {
            {'I',"x"}, {'I',"y"}, {'I',"z"},
            {'I',"x"}, {'I',"y"},
            {'X',""}, {'N',""}, {'D',"z"}, {'N',""}
        }
    });

    // 5) Non-existent decrements and empty queries
    tests.push_back(TestCase{
        {
            {'D',"nope"}, {'X',""}, {'N',""},
            {'I',"a"}, {'D',"b"},
            {'X',""}, {'N',""}
        }
    });

    // 6) Bucket merging/splitting behavior
    tests.push_back(TestCase{
        {
            {'I',"k1"}, {'I',"k1"},
            {'I',"k2"},
            {'I',"k3"}, {'I',"k3"}, {'I',"k3"},
            {'D',"k3"}, {'D',"k2"},
            {'X',""}, {'N',""}
        }
    });

    // 7) Cross zero, repeated inc/dec
    tests.push_back(TestCase{
        {
            {'I',"t1"}, {'D',"t1"}, {'D',"t1"},
            {'X',""}, {'N',""},
            {'I',"t1"}, {'I',"t1"},
            {'N',""},
            {'D',"t1"}, {'D',"t1"},
            {'X',""}, {'N',""}
        }
    });

    // 8) Ten keys with increasing counts, then adjust
    {
        TestCase tc;
        for (int i = 0; i < 10; ++i) {
            std::string k = "k" + std::to_string(i);
            for (int j = 0; j <= i; ++j) tc.ops.push_back({'I', k});
        }
        for (int j = 0; j < 5; ++j) tc.ops.push_back({'D', "k9"});
        tc.ops.push_back({'X', ""});
        tc.ops.push_back({'N', ""});
        tc.ops.push_back({'D', "k0"});
        tc.ops.push_back({'N', ""});
        tests.push_back(std::move(tc));
    }

    // 9) Create contiguous buckets then modify
    tests.push_back(TestCase{
        {
            {'I',"a"}, {'I',"b"}, {'I',"c"}, {'I',"d"}, {'I',"e"},
            {'I',"a"},
            {'I',"b"}, {'I',"b"},
            {'I',"c"}, {'I',"c"}, {'I',"c"},
            {'I',"d"}, {'I',"d"}, {'I',"d"}, {'I',"d"},
            {'X',""}, {'N',""},
            {'D',"b"},
            {'D',"c"}, {'D',"c"}, {'D',"c"},
            {'X',""}, {'N',""}
        }
    });

    // 10) Interleaved queries and updates
    tests.push_back(TestCase{
        {
            {'I',"m"}, {'X',""}, {'N',""},
            {'I',"n"}, {'X',""}, {'N',""},
            {'D',"x"}, {'X',""}, {'N',""},
            {'I',"m"}, {'X',""}, {'N',""},
            {'D',"m"}, {'X',""}, {'N',""},
            {'D',"m"}, {'X',""}, {'N',""}
        }
    });

    return tests;
}

int main() {
    using namespace std::chrono;

    auto tests = buildTests();
    uint64_t checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            checksum += runTest(tc);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed << "\n";

    return 0;
}