
/*
Advent of Code 2025: Day 12
By: Dan Shan
2025, Dec 12

Recursively brute force all possibilities
(I'm still perplexed by why this passes)
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vector<string> lines, cur, regions;
    while(getline(cin, s)) lines.push_back(s); 
    vector<vector<string>> raw;
    for(auto si: lines){ // Input formatting
        size_t x = si.find('x');
        if(x != string::npos) regions.push_back(si);
        else {
            if(si[0] >= '0' && si[0] <= '9') continue;
            if(si[0] == '\n' || si[0] == '\r') {raw.push_back(cur), cur.clear();}
            else cur.push_back(si);
        } 
    }
    if(cur.size()) raw.push_back(cur);
    int n = raw.size(), res = 0;
    vector<vector<pair<int, int>>> base(n);
    for(int i = 0; i < n; ++i){
        vector<string> g;
        for(int r = 0; r < raw[i].size(); ++r){
            string s = raw[i][r];
            g.push_back(s);
        }
        for(int r = 0; r < g.size(); ++r) // Organize input
            for(int c = 0; c < g[r].size(); ++c) 
                if(g[r][c] == '#') base[i].push_back({c, r});
        int mnx = 2e9, mny = 2e9;
        for(auto p: base[i]) mnx = min(mnx, p.first), mny = min(mny, p.second);
        for(auto &p: base[i]) p.first -= mnx, p.second -= mny;
    }
    auto gen_or = [&](auto cells){ // Generate all 8 orientations 
        set<vector<pair<int, int>>> S;
        auto normalize = [&](vector<pair<int,int>> v){
            int mnx = 2e9, mny = 2e9;
            for(auto p : v) mnx = min(mnx, p.first), mny = min(mny, p.second);
            for(auto &p : v) p.first -= mnx, p.second -= mny;
            sort(v.begin(), v.end());
            return v;
        };
        for(int flip = 0; flip < 2; ++flip)
            for(int rot = 0; rot < 4; ++rot){
                vector<pair<int,int>> w;
                for(auto &p : cells){
                    int x = p.first, y = p.second;
                    if(flip) x = -x; // flip 
                    for(int k = 0; k < rot; ++k){
                        int tx = x; x = -y; y = tx; // rotate
                    }
                    w.push_back({x, y});
                }
                S.insert(normalize(w));
            }
        return vector<vector<pair<int, int>>>(S.begin(), S.end());
    };
    vector<vector<vector<pair<int,int>>>> orients(n);
    for(int i = 0; i < n; ++i) orients[i] = gen_or(base[i]);
    for(auto rl: regions){
        size_t c = rl.find(':'); string L = rl.substr(0, c), Rr = rl.substr(c + 1);
        size_t x = L.find('x'); int W = stoi(L.substr(0, x)), H = stoi(L.substr(x + 1));
        stringstream ss(Rr); vector<int> need(n);
        for(int i = 0; i < n; ++i) ss >> need[i];
        long long total = 0;
        for(int i = 0; i < n ; ++i) total += need[i] * base[i].size();
        if(total > W * H) continue;
        // build list of pieces (shape indices) sorted by area desc
        vector<int> pieces;
        for(int i = 0; i < n; ++i) for(int k = 0; k < need[i]; ++k) pieces.push_back(i);
        vector<char> grid(W * H, 0);
        function<bool(int)> dfs = [&](int idx)->bool{ // Brute force all combinations
            if(idx == pieces.size()) return 1;
            int si = pieces[idx];
            for(auto ori: orients[si]){
                int mx = 0, my = 0;
                for(auto p: ori) mx = max(mx, p.first), my = max(my, p.second);
                for(int y = 0; y + my < H ; ++y) for(int x0 = 0; x0 + mx < W; ++x0){
                    bool ok = 1;
                    for(auto p: ori){
                        int x = x0 + p.first, y2 = y + p.second;
                        if(grid[y2 * W + x]) { ok = 0; break; }
                    }
                    if(!ok) continue;
                    for(auto p: ori) grid[(y + p.second) * W + (x0 + p.first)] = 1;
                    if(dfs(idx + 1)) return 1;
                    for(auto p: ori) grid[(y + p.second) * W + (x0 + p.first)] = 0;
                }
            }
            return 0;
        }; res += dfs(0);
    }
    cout << res << "\n";
}
// 544
