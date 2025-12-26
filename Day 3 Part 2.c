// Advent of Code: Day 3. Part 2
// Same Logic as C++ counterpart, implemented in C
// Dan Shan
// 12-25-2025
#include <string.h>
#pragma GCC optimize("Ofast")

// Part 2
// Montonic stack

int main() {
    long long res = 0, t = 200; // **SET LINE COUNT MANUALLY
    char s[1000];
    int k = 12;  // exactly 12 digits
    while (t--) {
        scanf("%s",s);
        long long n = strlen(s), r = n - k, val = 0, bk = 0;
        char st[100000];
        for (char c : s) { // prune until k remain
            while (bk && r && st[bk-1] < c) {
                --r; --bk;
            }
            st[bk++] = c;
        }
        for (int i = 0; i < k; ++i) {
            val = val * 10 + (st[i] - '0');
        }
        res += val;
    }
    printf("%lld\n",res);
}
