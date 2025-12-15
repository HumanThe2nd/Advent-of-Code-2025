
/*
Advent of Code 2025: Day 4
By: Dan Shan
2025, Dec 4
*/
#include <bits/stdc++.h>
using namespace std;
/*
// Part 1
int main() {
    vector<string> g;
    string s;
    while (cin >> s) g.push_back(s);

    int n = g.size();
    int m = g[0].size();

    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};

    long long res = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] != '@') continue;  // must be a roll

            int adj = 0;
            for (int k = 0; k < 8; ++k) {
                int ni = i + dx[k], nj = j + dy[k];  // FIXED: dy, not dx
                if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
                if (g[ni][nj] == '@') adj++;
            }
            if (adj < 4) res++;
        }
    }

    cout << res;
}*/

int main() {
    vector<string> g;
    string s;
    while (cin >> s) g.push_back(s);

    int n = g.size();
    int m = g[0].size();

    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};

    long long res = 0;
    while(1){
        int r = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (g[i][j] != '@') continue;  // must be a roll

                int adj = 0;
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k], nj = j + dy[k];  // FIXED: dy, not dx
                    if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
                    if (g[ni][nj] == '@') ++adj;
                }
                if (adj < 4) {
                    res++; ++r;
                    g[i][j] = '.'; 
                }
            }
        }
        if(!r) break;
    }

    cout << res;
}
