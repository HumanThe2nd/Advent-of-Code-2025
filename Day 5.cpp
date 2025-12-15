
/*
Advent of Code 2025: Day 5
By: Dan Shan
2025, Dec 5
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
/*
// Part 1

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> L, R, q;
    string s;

    // read ranges
    while (cin >> s) {
        int pos = s.find('-');
        if (pos == -1) break;  // first non-range line
        long long a = stoll(s.substr(0, pos));
        long long b = stoll(s.substr(pos + 1));
        L.push_back(a);
        R.push_back(b);
    }
    // already contains first ID
    q.push_back(stoll(s));

    // read remaining IDs
    long long x;
    while (cin >> x) q.push_back(x);
    long long res = 0;
    for (long long id : q) {
        for (int i = 0; i < (int)L.size(); i++) {
            if (id >= L[i] && id <= R[i]) {
                ++res;
                break;
            }
        }
    }
    cout << res;
}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<ll,ll>> ranges, merged;
    string s;
    while (cin >> s) {
        int pos = s.find('-');
        if (pos == -1) break; // end reached 
        ll a = stoll(s.substr(0, pos)),  b = stoll(s.substr(pos + 1));
        ranges.emplace_back(a, b);
    }

    // Sort and merge intervals
    sort(ranges.begin(), ranges.end());
    for (auto p : ranges) {
        if (merged.empty() || p.first > merged.back().second + 1) { // no overlap
            merged.push_back(p);
        } else { // combine
            merged.back().second = max(merged.back().second, p.second);
        }
    }
    long long res = 0;
    for (auto p : merged) {
        res += p.second - p.first + 1;
    }
    cout << res;
}
// ans: 347338785050515
