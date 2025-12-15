/*
Advent of Code 2025: Day 2
By: Dan Shan
2025, Dec 2
*/

#include <bits/stdc++.h>
using namespace std;
/*
// Part 1
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long res = 0;
    string s;

    while (cin >> s) {
        stringstream ss(s);
        string token;
        while (getline(ss, token, ',')) { // split by commas
            stringstream range(token);
            string L, R;
            getline(range, L, '-');
            getline(range, R, '-');

            long long l = stoll(L), r = stoll(R);
            for(long long x = l; x <= r; ++x){
                string num = to_string(x);
                if(num.size() % 2 == 0){
                    string first = num.substr(0, num.size()/2);
                    string second = num.substr(num.size()/2);
                    if(first == second) res += x;
                }
            }
        }
    }
    cout << res;
}

*/

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long res = 0;
    string s;

    while (cin >> s) {
        stringstream ss(s);
        string token;
        while (getline(ss, token, ',')) { // split by commas
            stringstream range(token);
            string L, R;
            getline(range, L, '-');
            getline(range, R, '-');

            long long l = stoll(L), r = stoll(R);
            for(long long x = l; x <= r; ++x){
                string num = to_string(x);
                bool val = 0;
                int n = (int)num.size();
                for(int i = 1; i <= n/2; ++i){
                    if(n % i != 0) continue;
                    string seg = num.substr(0, i);
                    bool vi = 1;
                    for(int j = i; j < n; j += i){
                        if(seg != num.substr(j, i)){
                            vi = 0; break; // this interval works
                        }
                    }
                    if(vi){
                        val = 1; break;
                    }
                }
                if(val) res += x;
            }
        }
    }
    cout << res;
}
