#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

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

static inline int shash(const string& s) {
    unsigned int h = 0;
    for (unsigned char c : s) h = h * 131u + c;
    return (int)h;
}

int main() {
    vector<vector<pair<char, string>>> tests;

    // Test 1
    tests.push_back({
        {'I',"a"}, {'I',"b"}, {'I',"a"}, {'I',"c"}, {'I',"b"}, {'I',"a"}
    });

    // Test 2
    tests.push_back({
        {'I',"apple"}, {'I',"apple"}, {'I',"apple"}, {'I',"apple"}, {'I',"apple"},
        {'I',"banana"}, {'I',"banana"}, {'I',"banana"},
        {'I',"cherry"},
        {'I',"date"}, {'I',"date"}
    });

    // Test 3
    tests.push_back({
        {'I',"x"}, {'I',"x"}, {'I',"x"}, {'I',"x"},
        {'I',"y"},
        {'I',"z"}, {'I',"z"}, {'I',"z"}
    });

    // Test 4
    tests.push_back({
        {'I',"m"}, {'I',"m"},
        {'I',"n"}, {'I',"n"},
        {'D',"n"}, {'D',"n"},
        {'I',"n"},
        {'I',"o"}, {'D',"o"}
    });

    // Test 5
    tests.push_back({
        {'I',"k1"}, {'I',"k1"}, {'I',"k1"}, {'I',"k1"}, {'I',"k1"},
        {'I',"k1"}, {'I',"k1"}, {'I',"k1"}, {'I',"k1"}, {'I',"k1"},
        {'I',"k2"}, {'I',"k2"}, {'I',"k2"}, {'I',"k2"}, {'I',"k2"},
        {'I',"k2"}, {'I',"k2"}, {'I',"k2"}, {'I',"k2"},
        {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"},
        {'I',"k3"}, {'I',"k3"}, {'I',"k3"},
        {'I',"k4"}, {'I',"k4"}, {'I',"k4"}, {'I',"k4"}, {'I',"k4"},
        {'I',"k4"}, {'I',"k4"},
        {'I',"k5"}, {'I',"k5"}, {'I',"k5"}, {'I',"k5"}, {'I',"k5"}, {'I',"k5"}
    });

    // Test 6
    tests.push_back({
        {'I',"alpha"}, {'I',"alpha"},
        {'I',"beta"}, {'I',"beta"}, {'I',"beta"},
        {'D',"alpha"},
        {'D',"beta"},
        {'I',"gamma"}, {'I',"gamma"}, {'I',"gamma"}, {'I',"gamma"},
        {'D',"gamma"}, {'D',"gamma"},
        {'I',"beta"}
    });

    // Test 7
    tests.push_back({
        {'I',"aa"},
        {'I',"bb"}, {'I',"bb"}, {'I',"bb"}, {'I',"bb"},
        {'I',"cc"}, {'I',"cc"},
        {'I',"dd"}, {'I',"dd"}, {'I',"dd"}
    });

    // Test 8
    tests.push_back({
        {'I',"t1"}, {'I',"t1"}, {'I',"t1"},
        {'I',"t2"}, {'I',"t2"},
        {'I',"t3"}, {'I',"t3"}, {'I',"t3"}, {'I',"t3"}, {'I',"t3"}, {'I',"t3"},
        {'I',"t4"}, {'I',"t4"}, {'I',"t4"},
        {'D',"t3"}, {'D',"t3"},
        {'I',"t1"}, {'I',"t1"},
        {'I',"t3"}, {'I',"t3"}, {'I',"t3"},
        {'D',"t4"},
        {'D',"t2"}
    });

    // Test 9
    tests.push_back({
        {'I',"k0"}, {'I',"k0"}, {'I',"k0"}, {'I',"k0"}, {'I',"k0"},
        {'I',"k0"}, {'I',"k0"}, {'I',"k0"}, {'I',"k0"},
        {'I',"k1"},
        {'I',"k2"}, {'I',"k2"}, {'I',"k2"}, {'I',"k2"},
        {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"}, {'I',"k3"}
    });

    // Test 10
    tests.push_back({
        {'I',"w1"}, {'I',"w1"}, {'I',"w1"},
        {'I',"w2"}, {'I',"w2"}, {'D',"w2"},
        {'I',"w3"}, {'I',"w3"},
        {'I',"w4"}, {'I',"w4"}, {'I',"w4"}, {'I',"w4"}, {'I',"w4"},
        {'I',"w5"}, {'I',"w5"}, {'I',"w5"}, {'I',"w5"}
    });

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code
        int checksum = 0;
        for (const auto& ops : tests) {
            AllOne ds;
            for (const auto& op : ops) {
                if (op.first == 'I') ds.inc(op.second);
                else if (op.first == 'D') ds.dec(op.second);
            }
            string mx = ds.getMaxKey();
            string mn = ds.getMinKey();
            checksum += shash(mx) + shash(mn);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}