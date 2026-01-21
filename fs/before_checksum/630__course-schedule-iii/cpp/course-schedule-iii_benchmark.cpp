#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

using namespace std;

// Time:  O(nlogn)
// Space: O(k), k is the number of courses you can take
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });
        priority_queue<int> max_heap;
        long long now = 0;
        for (const auto& c : courses) {
            int t = c[0], end = c[1];
            now += t;
            max_heap.push(t);
            if (now > end) {
                now -= max_heap.top();
                max_heap.pop();
            }
        }
        return static_cast<int>(max_heap.size());
    }
};

int main() {
    // Prepare 10 diverse test inputs
    vector<vector<vector<int>>> tests;

    // 1. Empty input
    tests.push_back({});

    // 2. Single feasible course
    tests.push_back({{1, 2}});

    // 3. Single infeasible course
    tests.push_back({{3, 2}});

    // 4. Typical sample set
    tests.push_back({{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}});

    // 5. Identical deadlines, varying durations
    tests.push_back({{5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}});

    // 6. Tight and overlapping deadlines
    tests.push_back({{2, 2}, {2, 2}, {3, 3}, {1, 2}, {2, 3}});

    // 7. All feasible: deadlines are prefix sums
    {
        vector<vector<int>> t;
        for (int i = 1; i <= 10; ++i) {
            t.push_back({i, i * (i + 1) / 2});
        }
        tests.push_back(move(t));
    }

    // 8. Larger mixed set (50 items) with varying durations and deadlines
    {
        vector<vector<int>> t;
        for (int i = 0; i < 50; ++i) {
            int dur = (i * 7) % 10 + 1;                 // 1..10
            int ddl = (i * 13) % 50 + dur + 5;          // ensure ddl > dur
            t.push_back({dur, ddl});
        }
        tests.push_back(move(t));
    }

    // 9. Heavy durations close to deadlines (30 items)
    {
        vector<vector<int>> t;
        for (int i = 0; i < 30; ++i) {
            int dur = 90 + (i % 21);                    // 90..110
            int ddl = 100 + ((i * 17) % 21);            // 100..120
            t.push_back({dur, ddl});
        }
        tests.push_back(move(t));
    }

    // 10. Decreasing deadlines (20 items)
    {
        vector<vector<int>> t;
        for (int i = 0; i < 20; ++i) {
            int dur = (i % 10) + 1;                     // 1..10
            int ddl = 100 - i * 3;                      // decreasing, stays positive
            t.push_back({dur, ddl});
        }
        tests.push_back(move(t));
    }

    Solution sol;
    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            auto courses = tests[i]; // copy, since scheduleCourse sorts in-place
            int result = sol.scheduleCourse(courses);
            checksum += result * static_cast<int>(i + 1);
        }
    }

    auto end = clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}