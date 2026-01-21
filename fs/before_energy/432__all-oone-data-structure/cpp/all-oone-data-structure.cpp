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