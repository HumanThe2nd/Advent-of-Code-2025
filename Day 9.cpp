
/*
Advent of Code 2025: Day 9
By: Dan Shan
2025, Dec 9
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/*
// Part 1
// Brute force max area of grid
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<ll, ll>> pts;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        ll x, y;
        char comma;
        stringstream ss(line);
        ss >> x >> comma >> y;
        pts.emplace_back(x, y);
    }

    ll res = 0, n = pts.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll dx = abs(pts[i].first  - pts[j].first)  + 1;
            ll dy = abs(pts[i].second - pts[j].second) + 1;
            ll area = dx * dy;
            res = max(res, area);
        }
    }

    cout << res << "\n";
    return 0;
}
*/
/*
Assisted by GPT 
Approach:
1. Input red tiles and treat them as a polygon
2. Compress x-coordinates into blocks
3. Find valid blocks (within polygon)
4. Test all valid red rectangle pairs
5. Return max area of valid pairs
*/
struct V{ int x, ylo, yhi; }; // points
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<int,int>> pts;
    string s;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        int x,y; char c; stringstream ss(s); ss >> x >> c >> y;
        pts.emplace_back(x,y);
    }

    // collect vertical edges and y-bounds
    vector<V> vedges;
    int n = pts.size(), minY = 2e9, maxY = -2e9, minX = 2e9, maxX = -2e9;
    for(int i=0;i<n;i++){
        auto a=pts[i], b=pts[(i+1)%n];
        minY = min(minY, min(a.second,b.second));
        maxY = max(maxY, max(a.second,b.second));
        minX = min(minX, min(a.first,b.first));
        maxX = max(maxX, max(a.first,b.first));
        if (a.first == b.first) vedges.push_back({a.first, min(a.second,b.second), max(a.second,b.second)});
    }

    // coord compression over x axis
    vector<int> xs;
    for(auto e: vedges) xs.push_back(e.x);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    int X = (int)xs.size()-1; // number of x coords

    vector<vector<pair<int,int>>> blocks(X); // valid y-interval per block
    vector<int> active(X, INT_MIN); // active starts per block 

    // scan rows y from minY to maxY
    for(int y = minY; y <= maxY; ++y){
        vector<int> inter; inter.reserve(vedges.size());
        for(auto &e: vedges) if (y >= e.ylo && y < e.yhi) inter.push_back(e.x);

        sort(inter.begin(), inter.end());
        if(inter.size() & 1) inter.pop_back();

        // mark covered blocks
        vector<char> covered(X, 0);
        for(size_t k=0; k+1 < inter.size(); k+=2){
            int L = inter[k], R = inter[k+1]; // covers x in [L, R)

            // binary search interval
            int li = int(lower_bound(xs.begin(), xs.end(), L) - xs.begin());
            int ri = int(lower_bound(xs.begin(), xs.end(), R) - xs.begin());
            for(int b = li; b < ri; ++b) covered[b] = 1;
        }
        // update active intervals 
        for(int b = 0; b < X; ++b){
            if (covered[b]){
                if (active[b] == INT_MIN) active[b] = y; // new run
            } 
            else if (active[b] != INT_MIN){ blocks[b].emplace_back(active[b], y); active[b] = INT_MIN; }
        }
    }

    auto validate = [&](int b, int ly, int ry) -> int{
        auto v = blocks[b];
        if (v.empty()) return 0;
        int l = 0, r = v.size()-1;
        while(l <= r){ // binary search
            int m = (l+r) >> 1;
            if (v[m].first <= ly) l = m + 1;
            else r = m - 1;
        }
        if (v[r].first <= ly && v[r].second >= ry) return true;
        return 0;
    };

    // test all red pairs 
    ll res = 0;
    for(int i = 0; i < n; ++i) for(int j = i+1; j < n; ++j){
        int x1 = pts[i].first, y1 = pts[i].second, x2 = pts[j].first, y2 = pts[j].second;
        ll lx = min(x1,x2), rx = max(x1,x2), ly = min(y1,y2), ry = max(y1,y2);
        int bl = int(upper_bound(xs.begin(), xs.end(), lx) - xs.begin()) - 1;
        int br = int(upper_bound(xs.begin(), xs.end(), rx) - xs.begin()) - 1;
        if ( bl >= X || br >= X) continue;
        bool ok = 1; // validate interval
        for(int b = bl; b <= br; ++b){
            if (!validate(b, ly, ry)){ ok = 0; break; }
        }
        if(!ok) continue;
        ll area = (ll)(rx - lx + 1) * (ll)(ry - ly + 1); // inclusive tiles
        res = max(res, area);
    }

    cout << res << "\n";
}
// 1644094530
