#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class Solution {
public:
    int strongPasswordChecker(string s) {
        int n = static_cast<int>(s.size());
        int missing_type_cnt = 3;
        bool has_lower = false, has_upper = false, has_digit = false;
        for (char c : s) {
            if ('a' <= c && c <= 'z') has_lower = true;
            else if ('A' <= c && c <= 'Z') has_upper = true;
            else if (isdigit(static_cast<unsigned char>(c))) has_digit = true;
        }
        if (has_lower) missing_type_cnt -= 1;
        if (has_upper) missing_type_cnt -= 1;
        if (has_digit) missing_type_cnt -= 1;

        int total_change_cnt = 0;
        int one_change_cnt = 0, two_change_cnt = 0, three_change_cnt = 0;

        int i = 2;
        while (i < n) {
            if (s[i] == s[i - 1] && s[i - 1] == s[i - 2]) {
                int length = 2;
                while (i < n && s[i] == s[i - 1]) {
                    length += 1;
                    i += 1;
                }
                total_change_cnt += length / 3;
                if (length % 3 == 0) {
                    one_change_cnt += 1;
                } else if (length % 3 == 1) {
                    two_change_cnt += 1;
                } else {
                    three_change_cnt += 1;
                }
            } else {
                i += 1;
            }
        }

        if (n < 6) {
            return max(missing_type_cnt, 6 - n);
        } else if (n <= 20) {
            return max(missing_type_cnt, total_change_cnt);
        } else {
            int delete_cnt = n - 20;

            total_change_cnt -= (min(delete_cnt, one_change_cnt * 1)) / 1;
            total_change_cnt -= (min(max(delete_cnt - one_change_cnt, 0), two_change_cnt * 2)) / 2;
            total_change_cnt -= (min(max(delete_cnt - one_change_cnt - 2 * two_change_cnt, 0), three_change_cnt * 3)) / 3;

            return delete_cnt + max(missing_type_cnt, total_change_cnt);
        }
    }
};