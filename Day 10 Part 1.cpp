/*
Advent of Code 2025: Day 10
2025, Dec 10
Brute force with optimizations (bitmasking)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Part 1
// Brute force all combinations
int min_presses(int t, vector<int> buttons){
    int m = buttons.size();
    int min_press = 2e9;
    for (int mask = 0; mask < (1 << m); ++mask) { // bitmask optimization by GPT
        int state = 0;
        int presses = 0;
        for (int i = 0; i < m; ++i) {
            if (mask & (1 << i)) {
                state ^= buttons[i];
                ++presses;
            }
        }
        if (state == t) {
            min_press = min(min_press, presses);
        }
    }
    return min_press;
}
int main() {
    string line;
    int res = 0;
    while (getline(cin, line)) {
        // Diagram
        size_t start = line.find('['), end = line.find(']');
        string diagram = line.substr(start + 1, end - start - 1);
        int target = 0;
        for (int i = 0; i < diagram.size(); ++i)
            if (diagram[i] == '#') target |= (1 << i);
        // Buttons
        vector<int> buttons;
        stringstream ss(line);
        string token;
        while (ss >> token) {
            if (token.front() == '(' && token.back() == ')') {
                token = token.substr(1, token.size() - 2);
                stringstream nums(token);
                string num;
                int mask = 0;
                while (getline(nums, num, ',')) {
                    if (!num.empty()) {
                        int bit = stoi(num);
                        mask |= (1 << bit);
                    }
                }
                buttons.push_back(mask);
            }
        }
        res += min_presses(target, buttons);
    }
    cout << res << endl;
}
// Part 2: I gave up in C++ and used a python library with GPT assistance
// Approach: use a premade linear programming library (I used PuLP 3.3.0)
