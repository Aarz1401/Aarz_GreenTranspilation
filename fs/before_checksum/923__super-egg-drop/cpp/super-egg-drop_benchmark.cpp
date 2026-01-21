#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <chrono>

class Solution {
public:
    // Time:  O(K * log N)
    // Space: O(1)
    int superEggDrop(int K, int N) {
        auto check = [&](long long n, int K, long long N) -> bool {
            // let f(n, K) be the max number of floors could be solved by n moves and K eggs,
            // we want to do binary search to find min of n, s.t. f(n, K) >= N,
            // if we use one move to drop egg with X floors
            // 1. if it breaks, we can search new X in the range [X-f(n-1, K-1), X-1]
            // 2. if it doesn't break, we can search new X in the range [X+1, X+f(n-1, K)]
            // => f(n, K) = (X+f(n-1, K))-(X-f(n-1, K-1))+1 = f(n-1, K)+f(n-1, K-1)+1
            // => (1) f(n, K)   = f(n-1, K)  +1+f(n-1, K-1)
            //    (2) f(n, K-1) = f(n-1, K-1)+1+f(n-1, K-2)
            // let g(n, K) = f(n, K)-f(n, K-1), and we subtract (1) by (2)
            // => g(n, K) = g(n-1, K)+g(n-1, K-1), obviously, it is binomial coefficient
            // => C(n, K) = g(n, K) = f(n, K)-f(n, K-1),
            //    which also implies if we have one more egg with n moves and x-1 eggs, we can have more C(n, x) floors solvable
            // => f(n, K) = C(n, K)+f(n, K-1) = C(n, K) + C(n, K-1) + ... + C(n, 1) + f(n, 0) = sum(C(n, k) for k in [1, K])
            // => all we have to do is to check sum(C(n, k) for k in [1, K]) >= N,
            //    if true, there must exist a 1-to-1 mapping from each F in [1, N] to each success and failure sequence of every C(n, k) combinations for k in [1, K]
            long long total = 0;
            __int128 c = 1;  // C(n, 0)
            for (int k = 1; k <= K; ++k) {
                // c = c * (n - k + 1) / k
                c = c * (n - k + 1) / k;
                if (c <= 0) {  // when k > n, combinations become 0 thereafter
                    break;
                }
                if (c > N) c = N + 1;  // clamp to prevent overflow in subsequent steps
                total += static_cast<long long>(c);
                if (total >= N) {
                    return true;
                }
            }
            return false;
        };

        long long left = 1, right = N;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (check(mid, K, N)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return static_cast<int>(left);
    }
};

int main() {
    std::vector<std::pair<int, int>> tests = {
        {1, 1},
        {1, 1000},
        {2, 100},
        {2, 10000},
        {3, 1000},
        {10, 10000},
        {15, 1000000},
        {50, 1000000},
        {100, 10000000},
        {3, 2000000000}
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int K = tests[i].first;
            int N = tests[i].second;
            int res = sol.superEggDrop(K, N);
            checksum += (res ^ (static_cast<int>(i) + 31) ^ (iter << 1)) + K + (N & 0xFFFF);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}