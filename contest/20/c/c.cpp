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

#define INF 4e18

struct dijkstra
{
    vector<vector<pair<int, int>>> G;
    vector<int> parent;
    vector<long long> dist;

    dijkstra(vector<vector<pair<int, int>>> _G, int source): G(_G) {
        int n = G.size();
        dist.assign(n, INF);
        parent.assign(n, -1);
        dist[source] = 0;
        parent[source] = source;
        set<pair<int, int>> q;
        q.insert({0, source});
        while (!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());
            for (auto edge : G[v]) {
                int to = edge.first;
                int len = edge.second;
                if (dist[v] + len < dist[to]) {
                    q.erase({dist[to], to});
                    dist[to] = dist[v] + len;
                    parent[to] = v;
                    q.insert({dist[to], to});
                }
            }
        }
    }

    vector<int> get_path(int v) {
        int x = v;
        vector<int> p;
        p.push_back(x);
        while(p[x] != x) {
            x = p[x];
            p.push_back(x);
        }
        reverse(p.begin(), p.end());
        return p;
    }
};

void solve() {
	scii(n, m);
    vector<vector<ii>> G(n, vector<ii>());
    rep(i, 0, m) {
        sciii(x, y, w);
        --x; --y;
        G[x].push_back({y, w});
        G[y].push_back({x, w});
    }
    // dijkstra d(n, G);
    vi parent(n);
    vll dist(n);
    dijkstra dj(G, 0);

    if(dj.dist[n-1] == INF) {
        cout << -1 << endl;
        return;
    }

    for(auto x : dj.get_path(n-1)) {
        cout << x + 1 << ' ';
    }
    cout << endl;

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    solve();
    return 0;
}