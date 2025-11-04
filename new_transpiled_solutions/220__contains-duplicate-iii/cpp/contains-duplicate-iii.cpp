#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <cstdint>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k < 0 || t < 0) {
            return false;
        }
        
        // Ordered dictionary semantics: maintain insertion order and allow pop from front.
        list<long long> order;  // keeps bucket keys in insertion order
        unordered_map<long long, pair<long long, list<long long>::iterator>> window; // bucket -> (value, iterator in order)
        
        for (const int x : nums) {
            long long n = static_cast<long long>(x);
            
            // Ensure window size
            if (window.size() > static_cast<size_t>(k)) {
                long long oldestKey = order.front();
                order.pop_front();
                window.erase(oldestKey);
            }
            
            // Compute bucket id: bucket = n if t == 0 else floor_div(n, t)
            long long bucket;
            if (t == 0) {
                bucket = n;
            } else {
                long long b = static_cast<long long>(t);
                long long q = n / b;
                long long r = n % b;
                if (r != 0 && n < 0) {
                    --q; // adjust for floor division with negative numbers
                }
                bucket = q;
            }
            
            // Check neighbors: bucket-1, bucket, bucket+1
            for (long long nb : {bucket - 1, bucket, bucket + 1}) {
                auto it = window.find(nb);
                if (it != window.end()) {
                    long long m = it->second.first;
                    long long diff = (n >= m) ? (n - m) : (m - n);
                    if (diff <= static_cast<long long>(t)) {
                        return true;
                    }
                }
            }
            
            // Insert/update current bucket
            auto it2 = window.find(bucket);
            if (it2 != window.end()) {
                // Update value, keep order position (Python 2 OrderedDict behavior)
                it2->second.first = n;
            } else {
                order.push_back(bucket);
                auto iter = prev(order.end());
                window.emplace(bucket, make_pair(n, iter));
            }
        }
        
        return false;
    }
};