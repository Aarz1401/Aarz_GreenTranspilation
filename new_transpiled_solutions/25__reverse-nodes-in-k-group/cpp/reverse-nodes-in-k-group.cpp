#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(-1);
        dummy.next = head;

        ListNode* cur = head;
        ListNode* cur_dummy = &dummy;
        int length = 0;

        while (cur) {
            ListNode* next_cur = cur->next;
            length = (length + 1) % k;

            if (length == 0) {
                ListNode* next_dummy = cur_dummy->next;
                reverse(cur_dummy, cur->next);
                cur_dummy = next_dummy;
            }

            cur = next_cur;
        }

        return dummy.next;
    }

private:
    void reverse(ListNode* begin, ListNode* end) {
        ListNode* first = begin->next;
        ListNode* cur = first->next;

        while (cur != end) {
            first->next = cur->next;
            cur->next = begin->next;
            begin->next = cur;
            cur = first->next;
        }
    }
};