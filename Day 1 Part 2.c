// Advent of Code: Day 1. Part 2
// Same Logic as C++ counterpart, implemented in C
// Dan Shan
// 12-25-2025
#include <stdio.h>
#include <string.h>
#pragma GCC optimize("Ofast")

int main() {
    long long ans = 0;
    int pos = 50;
    char s[10];

    for(int i = 0; i < 4446; ++i){ // ** EDIT LINE COUNT MANUALLY
        scanf("%s", s);
        char dir = s[0];
        long long d = 0, l = strlen(s);
        for(int i = 1; i < l; ++i){
            d = d * 10 + s[i] - '0';
        }
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
    printf("%lld\n",ans);
}
