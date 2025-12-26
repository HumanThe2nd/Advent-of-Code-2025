// Advent of Code: Day 1. Part 1
// Same Logic as C++ counterpart, implemented in C
// Dan Shan
// 12-25-2025
#include <stdio.h>
#include <string.h>
#pragma GCC optimize("Ofast")

// Part 1
int main() {
    int p = 50, ans = 0;
    char s[5];
    for(int i = 0; i < 4446; ++i) {
        scanf("%s", s);
        char dir = s[0];
        int dist = 0, l = strlen(s);
        for(int i = 1; i < l; ++i){
            dist = dist * 10 + s[i] - '0';
        }
        int d = dist % 100;
        if(dir == 'L')
            p = (p - d + 100) % 100;
        else
            p = (p + d) % 100;
        if (p == 0) ans++;
    }
   printf("%d\n", ans);
}
