// Advent of Code: Day 3. Part 1
// Same Logic as C++ counterpart, implemented in C
// Dan Shan
// 12-25-2025

#include <stdio.h>
#include <string.h>
#pragma GCC optimize("Ofast")

// Part 1
int main() {
    long long res = 0, t = 200; // **SET LINE COUNT MANUALLY
    char s[1000];
    while (t--) {
        scanf("%s", s);
        int n = strlen(s), mx = 0;
        for(int i = 0; i < n; ++i){
            int d = 10*(s[i]-'0');
            for(int j = i+1; j < n; ++j){
                int d2 = d + s[j]-'0';
                if(d2 > mx) mx = d2;
            }
        }
        res += mx;
    }
    printf("%lld\n",res);
}
