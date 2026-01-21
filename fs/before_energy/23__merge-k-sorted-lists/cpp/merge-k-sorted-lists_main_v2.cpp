int main() {
    vector<vector<vector<int>>> tests = {
        { {1,2,3,4,5} },
        { {1,4,7}, {2,3,6,8} },
        { {1,1,1}, {1,1}, {1} },
        { {-5,-3,0,2}, {-4,-1,3}, {-2,2,5}, {-6,-6,7} },
        { {0,10000}, {5,10,15}, {1,2,3,4}, {9999,10000}, {6} },
        { {3}, {1}, {2}, {5}, {4}, {0} },
        { {1,3,5,7,9}, {2,4,6,8,10}, {0,11,12} },
        { {2,2,2,2}, {2,2,2} },
        { {-10,-9,-9,-8}, {-8,-8}, {-7}, {-10,-5}, {-6,-6,-6}, {-4,-3,-3,-3}, {-2,-1,0} },
        { {1,5,9}, {2,6,10}, {3,7,11}, {4,8,12} }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;

        for (const auto& test : tests) {
            vector<ListNode*> lists;
            lists.reserve(test.size());
            for (const auto& seq : test) {
                ListNode* head = new ListNode(seq[0]);
                ListNode* tail = head;
                for (size_t i = 1; i < seq.size(); ++i) {
                    tail->next = new ListNode(seq[i]);
                    tail = tail->next;
                }
                lists.push_back(head);
            }

            ListNode* merged = sol.mergeKLists(lists);
            while (merged) {
                checksum += merged->val;
                ListNode* tmp = merged;
                merged = merged->next;
                delete tmp;
            }
        }

        sink = checksum;
    }

    return 0;
}