#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <cstddef>
#include <chrono>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* n) : val(x), next(n) {}
};

// Time:  O(nlogk)
// Space: O(1)
// Merge two by two solution.
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto mergeTwoLists = [](ListNode* l1, ListNode* l2) -> ListNode* {
            ListNode dummy(0);
            ListNode* curr = &dummy;
            while (l1 && l2) {
                if (l1->val < l2->val) {
                    curr->next = l1;
                    l1 = l1->next;
                } else {
                    curr->next = l2;
                    l2 = l2->next;
                }
                curr = curr->next;
            }
            curr->next = l1 ? l1 : l2;
            return dummy.next;
        };

        if (lists.empty()) {
            return nullptr;
        }
        int left = 0, right = static_cast<int>(lists.size()) - 1;
        while (right > 0) {
            lists[left] = mergeTwoLists(lists[left], lists[right]);
            ++left;
            --right;
            if (left >= right) {
                left = 0;
            }
        }
        return lists[0];
    }
};

// Time:  O(nlogk)
// Space: O(logk)
// Divide and Conquer solution.
class Solution2 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return mergeKListsHelper(lists, 0, static_cast<int>(lists.size()) - 1);
    }
private:
    static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        curr->next = l1 ? l1 : l2;
        return dummy.next;
    }

    static ListNode* mergeKListsHelper(vector<ListNode*>& lists, int begin, int end) {
        if (begin > end) {
            return nullptr;
        }
        if (begin == end) {
            return lists[begin];
        }
        int mid = (begin + end) / 2;
        return mergeTwoLists(mergeKListsHelper(lists, begin, mid),
                             mergeKListsHelper(lists, mid + 1, end));
    }
};

// Time:  O(nlogk)
// Space: O(k)
// Heap solution.
class Solution3 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy(0);
        ListNode* current = &dummy;

        using NodePair = pair<int, ListNode*>;
        priority_queue<NodePair, vector<NodePair>, greater<NodePair>> min_heap;

        for (ListNode* node : lists) {
            if (node) {
                min_heap.emplace(node->val, node);
            }
        }

        while (!min_heap.empty()) {
            auto [val, node] = min_heap.top();
            min_heap.pop();
            current->next = node;
            current = current->next;
            if (node->next) {
                min_heap.emplace(node->next->val, node->next);
            }
        }

        return dummy.next;
    }
};

static ListNode* buildList(const vector<int>& vals) {
    ListNode* head = nullptr;
    ListNode** cur = &head;
    for (int v : vals) {
        *cur = new ListNode(v);
        cur = &((*cur)->next);
    }
    return head;
}

static vector<ListNode*> buildLists(const vector<vector<int>>& listsData) {
    vector<ListNode*> lists;
    lists.reserve(listsData.size());
    for (const auto& v : listsData) {
        lists.push_back(buildList(v));
    }
    return lists;
}

static void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    // Prepare 10 diverse test inputs (as vectors of sorted integer lists)
    vector<vector<vector<int>>> tests;
    tests.reserve(10);

    // 1. No lists
    tests.emplace_back(vector<vector<int>>{});
    // 2. Single empty list
    tests.emplace_back(vector<vector<int>>{{}});
    // 3. Multiple empty lists
    tests.emplace_back(vector<vector<int>>{{}, {}, {}});
    // 4. Single sorted list
    tests.emplace_back(vector<vector<int>>{{1, 2, 3, 4}});
    // 5. Mixed positive lists (classic sample)
    tests.emplace_back(vector<vector<int>>{{1, 4, 5}, {1, 3, 4}, {2, 6}});
    // 6. Negative and positive numbers
    tests.emplace_back(vector<vector<int>>{{-10, -5, 0}, {-6, -3, 2, 9}, {-7, -3, 0, 1}});
    // 7. Varying lengths and empties
    tests.emplace_back(vector<vector<int>>{{5}, {}, {1,2,3,4,5,6,7,8,9,10}, {2,2,2,2,2}, {1000}});
    // 8. Heavy duplicates
    tests.emplace_back(vector<vector<int>>{{1,1,1,1}, {1,1,1}, {1,1}, {1}});
    // 9. Many small single-node lists
    tests.emplace_back(vector<vector<int>>{{0},{-1},{-2},{-3},{-4},{-5},{-6},{-7},{-8},{-9}});
    // 10. Larger case: 5 lists of 100 elements each
    {
        vector<vector<int>> big(5);
        for (int j = 0; j < 5; ++j) {
            big[j].reserve(100);
            for (int i = 0; i < 100; ++i) {
                big[j].push_back(j * 1000 + i * 3 - j); // strictly increasing within each list
            }
        }
        tests.emplace_back(move(big));
    }

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            vector<ListNode*> lists = buildLists(tests[t]);
            ListNode* merged = sol.mergeKLists(lists);

            long long sum = 0;
            long long count = 0;
            for (ListNode* p = merged; p != nullptr; p = p->next) {
                sum += p->val;
                ++count;
            }
            // Mix in iteration and test index to avoid trivial optimization
            checksum += (sum ^ (count * 1315423911LL)) + static_cast<long long>(t * 17 + iter);

            freeList(merged);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}