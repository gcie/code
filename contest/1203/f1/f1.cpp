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
#define TC(x)           sci(x); while(x --)
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

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    scii(n, r);
    set<ii> ps;
    vector<ii> ns;
    int a, b;
    rep(i, 0, n) {
        cin >> a >> b;
        if(b >= 0) ps.insert({a, b});
        else ns.pb({-a, -b});
    }

    int cnt = 0;
    for(auto &p : ps) {
        if(p.st <= r) {
            r += p.nd; cnt++;
        }
    }
    sort(ns.begin(), ns.end(), [&ns](ii a, ii b){ return a.st + a.nd < b.st + b.nd; });
    vector<vi> rs(((int)ns.size()) + 1, vi(r + 1, 1));
    int j = 0;
    for(auto &x : ns) {
        j++;
        for(int i = r; i >= 0; i--) {
            if(i + x.nd <= r and i + x.nd >= - x.st) {
                rs[j][i] = max(rs[j-1][i], rs[j-1][i+x.nd] + 1);
                if(i < r) rs[j][i] = max(rs[j][i], rs[j][i+1]);
            } else {
                rs[j][i] = rs[j-1][i];
                if(i < r) rs[j][i] = max(rs[j][i], rs[j][i+1]);
            }
        }
    }
    int m = -1; rep(i, 0, r + 1) m = max(m, rs[j][i]);
    cout << (cnt + m - 1 == n ? "YES\n" : "NO\n");
    return 0;
}