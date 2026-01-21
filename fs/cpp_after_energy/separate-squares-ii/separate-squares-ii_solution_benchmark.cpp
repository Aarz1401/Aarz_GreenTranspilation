#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        struct Event {
            int y;
            int v;
            int x1;
            int x2;
        };

        vector<Event> events;
        events.reserve(squares.size() * 2);
        vector<int> xs;
        xs.reserve(squares.size() * 2);

        for (const auto& s : squares) {
            int x = s[0], y = s[1], len = s[2];
            events.push_back({y, 1, x, x + len});
            events.push_back({y + len, -1, x, x + len});
            xs.push_back(x);
            xs.push_back(x + len);
        }

        sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
            return a.y < b.y;
        });

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        unordered_map<int, int> x_to_idx;
        x_to_idx.reserve(xs.size() * 2);
        for (int i = 0; i < (int)xs.size(); ++i) {
            x_to_idx[xs[i]] = i;
        }

        struct SegmentTree {
            const vector<int>& xs;
            vector<double> tree;
            vector<int> cnt;
            int n; // number of segments = xs.size() - 1

            SegmentTree(const vector<int>& sorted_x) : xs(sorted_x) {
                n = max(0, (int)xs.size() - 1);
                int sz = 4 * max(1, n) + 5;
                tree.assign(sz, 0.0);
                cnt.assign(sz, 0);
            }

            void update(int ql, int qr, int v, int l, int r, int i) {
                if (ql >= r || qr <= l) return;
                if (ql <= l && r <= qr) {
                    cnt[i] += v;
                } else {
                    int m = l + (r - l) / 2;
                    update(ql, qr, v, l, m, i * 2);
                    update(ql, qr, v, m, r, i * 2 + 1);
                }
                if (cnt[i] > 0) {
                    tree[i] = xs[r] - xs[l];
                } else {
                    if (r - l == 1) {
                        tree[i] = 0.0;
                    } else {
                        tree[i] = tree[i * 2] + tree[i * 2 + 1];
                    }
                }
            }

            double totalCovered() const {
                return tree[1];
            }
        };

        SegmentTree st(xs);

        int prev = events[0].y;
        struct Interval { double y1, y2, curr; };
        vector<Interval> intervals;
        intervals.reserve(events.size());

        for (const auto& e : events) {
            if (e.y != prev) {
                intervals.push_back(Interval{(double)prev, (double)e.y, st.totalCovered()});
                prev = e.y;
            }
            int l = x_to_idx[e.x1];
            int r = x_to_idx[e.x2];
            st.update(l, r, e.v, 0, (int)xs.size() - 1, 1);
        }

        double expect = 0.0;
        for (const auto& iv : intervals) {
            expect += (iv.y2 - iv.y1) * iv.curr;
        }
        expect /= 2.0;

        double total = 0.0;
        double y1_break = 0.0, curr_break = 1.0;
        for (const auto& iv : intervals) {
            double area = (iv.y2 - iv.y1) * iv.curr;
            if (total + area >= expect) {
                y1_break = iv.y1;
                curr_break = iv.curr;
                break;
            }
            total += area;
        }

        return y1_break + (expect - total) / curr_break;
    }
};

int main() {
    // Prepare 10 diverse test inputs
    vector<vector<vector<int>>> tests;

    // 1. Single small square
    tests.push_back({{0, 0, 2}});

    // 2. Two non-overlapping squares
    tests.push_back({{0, 0, 3}, {5, 1, 2}});

    // 3. Two partially overlapping squares
    tests.push_back({{0, 0, 4}, {2, 1, 3}});

    // 4. Nested squares
    tests.push_back({{0, 0, 10}, {2, 2, 6}, {4, 4, 2}});

    // 5. Grid of small unit squares (5x5)
    {
        vector<vector<int>> t;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                t.push_back({i * 2, j * 2, 1});
            }
        }
        tests.push_back(std::move(t));
    }

    // 6. Very large coordinates
    tests.push_back({{-1000000000, -1000000000, 1500000000}});

    // 7. Many overlapping horizontal squares
    {
        vector<vector<int>> t;
        for (int i = 0; i < 50; ++i) {
            t.push_back({i, 0, 10});
        }
        tests.push_back(std::move(t));
    }

    // 8. Edge-touching squares
    tests.push_back({{0, 0, 10}, {10, 0, 10}, {20, 0, 10}, {30, 0, 10}, {0, 10, 10}, {10, 10, 10}});

    // 9. Negative coordinates with overlaps
    tests.push_back({{-5, -5, 3}, {-2, -1, 4}, {-10, 0, 5}});

    // 10. Pattern-generated diverse squares
    {
        vector<vector<int>> t;
        for (int i = 0; i < 100; ++i) {
            int x = (i % 11) * 3 - 15;
            int y = (i % 13) * 2 - 12;
            int len = (i % 9) + 1;
            t.push_back({x, y, len});
        }
        tests.push_back(std::move(t));
    }

    Solution sol;
    double checksum = 0.0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            auto& squares = tests[t];
            double res = sol.separateSquares(squares);
            checksum += res * (static_cast<int>(t) + 1);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    cout << fixed << setprecision(6);
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}