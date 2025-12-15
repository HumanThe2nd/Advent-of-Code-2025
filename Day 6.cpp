
/*
Advent of Code 2025: Day 6
By: Dan Shan
2025, Dec 6
Implementation hell
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/*
// Part 1
int main() {
   string s;
   vector<ll> nums, op;
   while(cin >> s){
    if(s[0] >= '0' && s[0] <= '9'){
        nums.emplace_back(stoi(s));
    }
    else op.emplace_back(s[0]);
   }
   ll lines = 4, res = 0, n = op.size(); // manually set, to save time 
   for(int i = 0; i < n; ++i){
    ll ri = op[i] == '*'?1:0;
    for(int j = 0; j < lines; ++j){
        if(op[i] == '*') ri *= nums[i + j * n];
        else ri += nums[i + j * n];
    }
    res += ri;
   }
   cout << res;
} // 6378679666679
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> grid;
    string line;
    while (getline(cin, line)) grid.push_back(line);
    int H = grid.size(), W = grid[0].size();
    auto is_empty_col = [&](int c) {
        for (int r = 0; r < H; r++) if (grid[r][c] != ' ') return 0;
        return 1;
    };
    ll res = 0, R = 0;
    while(R < W) {
        if (is_empty_col(R)) {
            R++;
            continue;
        }
        ll L = R; // Column range [L, R]
        while (R < W && !is_empty_col(R)) R++;
        char op = ' '; // Bottom-most non-space character
        for (int col = L; col < R; col++) {
            for (int row = H - 1; row >= 0; row--) {
                if (grid[row][col] == '+' || grid[row][col] == '*') {
                    op = grid[row][col]; break;
                }
            } if (op != ' ') break;
        }
        vector<long long> nums;
        for (int col = R - 1; col >= L; --col) {
            string digits;
            for (int row = 0; row < H; ++row)
                if (isdigit(grid[row][col])) digits.push_back(grid[row][col]);
            if (!digits.empty()) {
                ll val = 0;
                for (char d : digits) val = val * 10 + (d - '0');
                nums.push_back(val);
            }
        }
        if (op == '+') {
            ll ai = 0;
            for (auto v : nums) ai += v;
            res += ai;
        } 
        else { // '*'
            ll ai = 1;
            for (auto v : nums) ai *= v;
            res += ai;
        }
    }
    cout << res << "\n";
}
// 11494432585168
