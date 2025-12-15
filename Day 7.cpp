
/*
Advent of Code 2025: Day 7
By: Dan Shan
2025, Dec 7
*/
#include <bits/stdc++.h>
using namespace std;

/*
// Part 1
int main() {
	vector<string> g;
    string s;
    while(cin >> s) g.emplace_back(s);
    long long res = 0, sx = 0, sy = 0, n = g.size(), m = g[0].size();

    // find S
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (g[r][c] == 'S') {
                sx = r; sy = c; break;
            }
        }

    }
    long long dp[n][m] = {};
    dp[sx][sy] = 1;
    for(int xi = 0; xi < n; ++xi){
        for(int yi = 0; yi < m; ++yi){
            if(!dp[xi][yi]) continue; // unreached
            if(xi+1 >= n) { // end reached
                continue;
            }
            if(g[xi+1][yi] == '^'){ // wall reached
                if(yi > 0){
                    dp[xi+1][yi-1] += dp[xi][yi];
                }
                if(yi < m-1){
                    dp[xi+1][yi+1] += dp[xi][yi];
                }
            }
            else dp[xi+1][yi] += dp[xi][yi]; // push dp
        }
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(dp[i][j] && ((i > 0 && g[i-1][j] =='^')||(i < m-1 && g[i+1][j] == '^'))) ++res;
        }
    }
    cout << res;
}
*/ 
// Part 2
int main() {
	vector<string> g;
    string s;
    while(cin >> s) g.emplace_back(s);
    long long res = 0, sx = 0, sy = 0, n = g.size(), m = g[0].size();

    // find S
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (g[r][c] == 'S') {
                sx = r; sy = c; break;
            }
        }

    }
    long long dp[n][m] = {};
    dp[sx][sy] = 1;
    for(int xi = 0; xi < n; ++xi){
        for(int yi = 0; yi < m; ++yi){
            if(!dp[xi][yi]) continue; // unreached
            if(xi+1 >= n) { // end reached
                res += dp[xi][yi];
                continue;
            }
            if(g[xi+1][yi] == '^'){ // wall reached
                if(yi > 0){
                    dp[xi+1][yi-1] += dp[xi][yi];
                }
                if(yi < m-1){
                    dp[xi+1][yi+1] += dp[xi][yi];
                }
            }
            else dp[xi+1][yi] += dp[xi][yi]; // push dp
        }
    }
    cout << res;
}
