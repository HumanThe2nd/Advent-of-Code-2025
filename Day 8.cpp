/*
Advent of Code 2025: Day 8
By: Dan Shan
2025, Dec 8
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/*
// Part 1
// Kruskal's algroithm (only attach 1st 1000)
// Return product of sizes of all sets
struct DSU {
    int n;
    vector<int> p, sz;
    DSU(int n=0): n(n), p(n), sz(n,1) { iota(p.begin(), p.end(), 0); }
    int find(int a){ return p[a]==a ? a : p[a]=find(p[a]); }
    bool unite(int a, int b){
        a = find(a); b = find(b);
        if(a==b) return false;
        if(sz[a] < sz[b]) swap(a,b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
    int size(int a){ return sz[find(a)]; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<array<ll,3>> pts;
    string line;
    while(getline(cin, line)){
        if(line.size()==0) continue;
        // parse "x,y,z"
        for(char &c : line) if(c==',') c=' ';
        stringstream ss(line);
        ll x,y,z;
        if(!(ss >> x >> y >> z)) {
            cerr << "Failed to parse line: " << line << "\n";
            return 1;
        }
        pts.push_back({x,y,z});
    }

    int n = (int)pts.size();
    
    // create all pairs with squared distances
    struct Edge {ll d; int a,b; };
    vector<Edge> edges;
    edges.reserve((size_t)n*(n>0?(n-1):0)/2);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            ll dx = pts[i][0] - pts[j][0];
            ll dy = pts[i][1] - pts[j][1];
            ll dz = pts[i][2] - pts[j][2];
            ll dsq = (dx*dx) + (dy*dy) + (dz*dz);
            edges.push_back({dsq, i, j});
        }
    }

    // sort by non-descending distance
    sort(edges.begin(), edges.end(), [](const Edge &A, const Edge &B){
        if(A.d != B.d) return A.d < B.d;
        if(A.a != B.a) return A.a < B.a;
        return A.b < B.b;
    });

    int K = min(1000, (int)edges.size());

    DSU dsu(n);
    for(int i=0;i<K;i++){
        dsu.unite(edges[i].a, edges[i].b);
    }

    // compute component sizes
    unordered_map<int,ll> comp;
    comp.reserve(n*2);
    for(int i=0;i<n;i++){
        comp[dsu.find(i)]++;
    }
    vector<ll> sizes;
    sizes.reserve(comp.size());
    for(auto p : comp) sizes.push_back(p.second);
    sort(sizes.begin(), sizes.end(), greater<ll>());

    // multiply top three sizes (if fewer than 3 components, treat missing as 1)
    ll res = 1;
    for(int i = 0; i < 3; ++i){
        if(i < sizes.size()) res *= sizes[i];
    }
    cout << res << "\n";
    
}
*/
// Part 2:
// Kruskal's algorithm for MST
// multiply X cords of last 2 nodes that get connected
struct DSU {
    int n;
    vector<int> p;
    DSU(int n=0): n(n), p(n) {iota(p.begin(), p.end(), 0);}
    int find(int a){ return p[a]==a ? a : p[a]=find(p[a]); }
    bool unite(int a, int b){
        a = find(a); b = find(b);
        if(a==b) return 0;
        p[b] = a;
        return 1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<array<ll,3>> pts;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);
        ll x,y,z;
        ss >> x >> y >> z;
        pts.push_back({x,y,z});
    }
    int n = pts.size();
    struct Edge {ll d; int a,b; };
    vector<Edge> edges;
    edges.reserve(n*(n-1)/2);

    for (int i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
            ll dx = pts[i][0] - pts[j][0];
            ll dy = pts[i][1] - pts[j][1];
            ll dz = pts[i][2] - pts[j][2];
            ll dsq = dx*dx + dy*dy + dz*dz;
            edges.push_back({dsq, i, j});
        }
    }
    sort(edges.begin(), edges.end(),[&](auto A, auto B){ return A.d < B.d; });

    DSU dsu(n);
    ll res = 0, components = n;
    for (auto &e : edges) {
        if (dsu.unite(e.a, e.b)) {
            components--;
            res = pts[e.a][0] * pts[e.b][0];
            if (components == 1) break; // finished
        }
    }
    cout << res << "\n";
}
// 44543856
