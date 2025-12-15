
/*
Advent of Code 2025: Day 3
By: Dan Shan
2025, Dec 3
*/

/*
// Part 1
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long res = 0;
    string s;

    while (cin >> s) {
        int n = s.size(),mx = 0;
        for(int i = 0; i < n; ++i){
            int d = 10*(s[i]-'0');
            for(int j = i+1; j < n; ++j){
                int d2 = d + s[j]-'0';
                if(d2 > mx) mx = d2;
            }
        }
        res += mx;
    }
    cout << res;
}
*/
// Montonic stack
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long res = 0;
    string s;
    int k = 12;  // exactly 12 digits
    while (cin >> s) {
        long long n = s.size(), r = n - k, val = 0;
        vector<char> st;
        for (char c : s) { // prune until k remain
            while (!st.empty() && r && st.back() < c) {
                st.pop_back();
                --r;
            }
            st.push_back(c);
        }
        for (int i = 0; i < k; ++i) {
            val = val * 10 + (st[i] - '0');
        }
        res += val;
    }
    cout << res;
}
