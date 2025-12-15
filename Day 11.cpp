/*
Advent of Code 2025: Day 11
By: Dan Shan
2025, Dec 11
Typical tree dynamic programming
I found this significantly easier than Days 9 and 10
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
// Part 1
// DFS directed graph, caching path counts
unordered_map<string, vector<string>> g;
unordered_map<string, ll> memo;
unordered_set<string> v;
ll dfs(string u) {
    if (u == "out") return 1;
    if (memo.count(u)) return memo[u];
    v.insert(u);
    ll res = 0;
    for (auto x: g[u]) res += dfs(x);
    v.erase(u);
    memo[u] = res;
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) { // Input formatted by GPT
        // format: name: a b c
        stringstream ss(line);
        string in;
        ss >> in;
        in.pop_back(); // remove ':'

        string out;
        while (ss >> out) {
            g[in].push_back(out);
        }
    }
    cout << dfs("you") << "\n";
}
*/

// Same as part 1, except: only count path if it passes through both checkpoints
unordered_map<string, vector<string>> g;
map<tuple<string, int, int>, ll> memo;
set<tuple<string, int, int>> v;

ll dfs(const string &u, bool DAC, bool FFT) {
    if (u == "out") return DAC && FFT; // count paths passing through both
    if (u == "dac") DAC = 1;
    else if (u == "fft") FFT = 1;
    auto key = make_tuple(u, DAC, FFT);
    if (memo.count(key)) return memo[key];
    v.insert(key);
    ll res = 0;
    for (const auto x : g[u]) {
        res += dfs(x, DAC, FFT);
    }
    v.erase(key);
    memo[key] = res;
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) { // Input formatted by GPT
        stringstream ss(line);
        string ai, bi;
        ss >> ai;
        ai.pop_back(); // remove colon
        while (ss >> bi) g[ai].push_back(bi);
    }
    cout << dfs("svr", 0, 0) << "\n";
}
// 383307150903216
