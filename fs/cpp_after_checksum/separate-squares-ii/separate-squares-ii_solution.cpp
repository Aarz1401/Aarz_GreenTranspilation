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

using namespace std;

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
