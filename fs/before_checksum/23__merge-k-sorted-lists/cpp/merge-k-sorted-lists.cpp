#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <cstddef>

using namespace std;

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