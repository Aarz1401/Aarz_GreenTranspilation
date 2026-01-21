#include <iostream>
#include <vector>

using namespace std;

// Time:  O((logn)^2)
// Space: O(1)

class Solution {
public:
    int preimageSizeFZF(int K) {
        auto count_of_factorial_primes = [](long long n, long long p) -> long long {
            long long cnt = 0;
            while (n > 0) {
                n /= p;
                cnt += n;
            }
            return cnt;
        };

        const long long p = 5;
        long long left = 0, right = p * static_cast<long long>(K);
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (count_of_factorial_primes(mid, p) >= K) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return (count_of_factorial_primes(left, p) == K) ? 5 : 0;
    }
};

int main() {
    vector<int> tests = {
        0,
        1,
        4,
        5,
        10,
        25,
        29,
        30,
        123456789,
        1000000000
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int k : tests) {
            checksum += s.preimageSizeFZF(k);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}