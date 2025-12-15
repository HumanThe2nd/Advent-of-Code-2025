/*
Advent of Cod2 2025: Day 1
By: Dan Shan
2025, Dec 1
*/

#include <bits/stdc++.h>
using namespace std;
/*
// Part 1
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int p = 50, ans = 0;
    string s;
    while (cin >> s) {
        char dir = s[0];
        long long dist = stoi(s.substr(1));
        int d = dist % 100;
        if(dir == 'L')
            p = (p - d + 100) % 100;
        else
            p = (p + d) % 100;
        if (p == 0) ans++;
    }
    cout << ans;
}
*/

// Part 2

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long ans = 0;
    int pos = 50;
    string s;

    while (cin >> s) {
        char dir = s[0];
        long long d = stoi(s.substr(1));
        
        ans += d / 100;
        long long rem = d % 100;

        if (dir == 'R') {
            int firstHit = (100 - pos) % 100;
            ans += (firstHit > 0 && firstHit <= rem);
            pos = (pos + rem) % 100;
        } else {
            int firstHit = pos % 100; 
            ans += (firstHit > 0 && firstHit <= rem);
            pos = (pos - rem + 100) % 100;
        }
    }
    cout << ans;
}
