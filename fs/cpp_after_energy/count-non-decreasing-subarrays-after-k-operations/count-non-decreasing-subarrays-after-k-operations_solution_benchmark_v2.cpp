#include <vector>
#include <deque>

template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
private:
    long long solve(std::vector<int>& nums, long long k) {
        long long result = 0;
        long long cnt = 0;
        std::deque<int> dq;
        int n = static_cast<int>(nums.size());
        int right = n - 1;
        for (int left = n - 1; left >= 0; --left) {
            while (!dq.empty() && nums[dq.back()] < nums[left]) {
                int l = dq.back();
                dq.pop_back();
                int r = !dq.empty() ? dq.back() - 1 : right;
                cnt += 1LL * (r - l + 1) * (nums[left] - nums[l]);
            }
            dq.push_back(left);
            while (cnt > k) {
                cnt -= static_cast<long long>(nums[dq.front()]) - nums[right];
                if (dq.front() == right) {
                    dq.pop_front();
                }
                --right;
            }
            result += (right - left + 1);
        }
        return result;
    }
public:
    long long countNonDecreasingSubarrays(std::vector<int>& nums, long long k) {
        return solve(nums, k);
    }
    long long countNonDecreasingSubarrays(std::vector<int>& nums, int k) {
        return solve(nums, static_cast<long long>(k));
    }
};

struct Test {
    std::vector<int> nums;
    long long k;
};

volatile int sink = 0;

int main() {
    std::vector<Test> tests = {
        {{5}, 0},
        {{1, 2, 3, 4}, 0},
        {{4, 3, 2, 1}, 0},
        {{3, 1, 2, 1, 2}, 2},
        {{2, 2, 2, 2, 2}, 0},
        {{0, 0, 1, 0, 0}, 3},
        {{1, 5, 2, 6, 3, 7, 4, 8, 5, 9}, 20},
        {{1000000000, 1, 1000000000, 1}, 3000000000LL},
        {{5, 1}, 3},
        {{1, 3, 2, 2, 5, 1, 7, 2, 3}, 5}
    };

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        Solution sol;
        for (auto t : tests) {
            long long r = sol.countNonDecreasingSubarrays(t.nums, t.k);
            DoNotOptimize(r); 
            //checksum += static_cast<int>(r);
        }
        //sink = checksum;
    }

    return 0;
}