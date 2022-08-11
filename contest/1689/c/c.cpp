#pragma gcc optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb              push_back
#define st              first
#define nd              second 
#define all(x)          (x).begin(), (x).end()
#define sci(x)          int x;       cin >> x;
#define scii(x, y)      int x, y;    cin >> x >> y;
#define sciii(x, y, z)  int x, y, z; cin >> x >> y >> z;
#define TC              sci(__test_case); while(__test_case --)
#define rep(i, x, y)    for (__typeof(x) i = x; i < y; i ++)
#define scvi(v, n)      vector<int> v(n); rep(i, 0, n) cin >> v[i];
#define scvll(v, n)     vector<long long> v(n); rep(i, 0, n) cin >> v[i];
#define SZ(x)           ((int)(x).size())
#define er_dup(x)       sort(all(x)); (x).resize(distance((x).begin(), unique(all(x))));
#define prv(v)          for(auto& x: v) cout << x << ' '; cout << '\n';
#define prvv(v)         for(auto& w: v) { for(auto& x: w) cout << x << ' '; cout << '\n'; }

using namespace std;

typedef long long       ll;
typedef pair<int, int>  ii;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

void parse(int vertex, vector<vi> &nbh, vi &parent, vi &child1, vi &child2) {
    for(auto x: nbh[vertex]) {
        if(x != parent[vertex]) {
            parent[x] = vertex;
            if(child1[vertex] == -1) {
                child1[vertex] = x;
            } else {
                child2[vertex] = x;
            }
            parse(x, nbh, parent, child1, child2);
        }
    }
}

int parse2(int v,  vi &child1, vi &child2, vi& vertices, vi& max_saved) {
    int saved = -1e9;
    if(child2[v] != -1) {
        parse2(child1[v], child1, child2, vertices, max_saved);
        parse2(child2[v], child1, child2, vertices, max_saved);
        max_saved[v] = max(
            max_saved[child1[v]] + vertices[child2[v]] - 1,
            max_saved[child2[v]] + vertices[child1[v]] - 1
        );
        vertices[v] = vertices[child1[v]] + vertices[child2[v]] + 1;
    } else if(child1[v] != -1) {
        parse2(child1[v], child1, child2, vertices, max_saved);
        max_saved[v] = vertices[child1[v]] - 1;
        vertices[v] = vertices[child1[v]] + 1;
    } else {
        max_saved[v] = 0;
        vertices[v] = 1;
    }
}

void solve() {
    sci(n);
    vector<vi> nbh(n, vi());
    vi parent(n, -1);
    vi child1(n, -1), child2(n, -1);

    rep(i, 0, n-1) {
        scii(x, y);
        nbh[x-1].push_back(y-1);
        nbh[y-1].push_back(x-1);
    }

    parse(0, nbh, parent, child1, child2);

    vi vertices(n), max_saved(n);
    
    parse2(0, child1, child2, vertices, max_saved);

    cout << max_saved[0] << endl;



}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    TC solve();

    return 0;
}