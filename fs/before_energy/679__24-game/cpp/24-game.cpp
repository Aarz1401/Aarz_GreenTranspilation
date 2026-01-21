#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <functional>
#include <cmath>
#include <numeric>
#include <algorithm>

using namespace std;

// Time:  O(n^3 * 4^n) = O(1), n = 4
// Space: O(n^2) = O(1)
class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<double> a(nums.begin(), nums.end());
        return dfs(a);
    }

private:
    static constexpr double EPS = 1e-6;

    bool dfs(vector<double>& nums) {
        if (nums.size() == 1) {
            return fabs(nums[0] - 24.0) < EPS;
        }
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                vector<double> next;
                next.reserve(n - 1);
                for (int k = 0; k < n; ++k) {
                    if (k != i && k != j) next.push_back(nums[k]);
                }
                for (int op = 0; op < 4; ++op) {
                    // Skip duplicate computations for commutative ops (+, *)
                    if ((op == 0 || op == 2) && j > i) continue;
                    // Avoid division by zero
                    if (op == 3 && fabs(nums[j]) < EPS) continue;

                    double val = 0.0;
                    switch (op) {
                        case 0: val = nums[i] + nums[j]; break; // add
                        case 1: val = nums[i] - nums[j]; break; // sub
                        case 2: val = nums[i] * nums[j]; break; // mul
                        case 3: val = nums[i] / nums[j]; break; // truediv
                    }
                    next.push_back(val);
                    if (dfs(next)) return true;
                    next.pop_back();
                }
            }
        }
        return false;
    }
};

// Time:  O(n^3 * 4^n) = O(1), n = 4
// Space: O(n^2) = O(1)
class Solution2 {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<Fraction> a;
        a.reserve(nums.size());
        for (int x : nums) a.emplace_back(x, 1);
        return dfs(a);
    }

private:
    struct Fraction {
        long long num;
        long long den; // always > 0

        Fraction(long long n = 0, long long d = 1) : num(n), den(d) {
            normalize();
        }

        void normalize() {
            if (den < 0) {
                den = -den;
                num = -num;
            }
            if (num == 0) {
                den = 1;
                return;
            }
            long long g = std::gcd(std::llabs(num), std::llabs(den));
            num /= g;
            den /= g;
        }

        bool isZero() const { return num == 0; }
        bool isTwentyFour() const { return num == 24 && den == 1; }
    };

    Fraction add(const Fraction& a, const Fraction& b) {
        Fraction r(a.num * b.den + b.num * a.den, a.den * b.den);
        r.normalize();
        return r;
    }

    Fraction sub(const Fraction& a, const Fraction& b) {
        Fraction r(a.num * b.den - b.num * a.den, a.den * b.den);
        r.normalize();
        return r;
    }

    Fraction mul(const Fraction& a, const Fraction& b) {
        Fraction r(a.num * b.num, a.den * b.den);
        r.normalize();
        return r;
    }

    bool div(const Fraction& a, const Fraction& b, Fraction& out) {
        if (b.isZero()) return false;
        out = Fraction(a.num * b.den, a.den * b.num);
        out.normalize();
        return true;
    }

    bool dfs(vector<Fraction>& nums) {
        if (nums.size() == 1) {
            return nums[0].isTwentyFour();
        }
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                vector<Fraction> next;
                next.reserve(n - 1);
                for (int k = 0; k < n; ++k) {
                    if (k != i && k != j) next.emplace_back(nums[k]);
                }
                for (int op = 0; op < 4; ++op) {
                    if ((op == 0 || op == 2) && j > i) continue; // +, * commutative
                    Fraction val;
                    bool ok = true;
                    switch (op) {
                        case 0: val = add(nums[i], nums[j]); break;
                        case 1: val = sub(nums[i], nums[j]); break;
                        case 2: val = mul(nums[i], nums[j]); break;
                        case 3: ok = div(nums[i], nums[j], val); break;
                    }
                    if (!ok) continue;
                    next.push_back(val);
                    if (dfs(next)) return true;
                    next.pop_back();
                }
            }
        }
        return false;
    }
};