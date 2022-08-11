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


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    scii(n, m);
    scvi(a, n);
    sort(all(a));
    reverse(all(a));
    vector<vi> ad(m, vi());
    rep(i, 0, n) {
        ad[i % m].push_back(a[i]);
    }
    vector<vll> pr(m, vll());
    for(int i = 0; i < m; i++) {
        ll s = 0;
        pr[i].push_back(0);
        for(auto &x : ad[i]) {
            s += x;
            pr[i].push_back(s);
        }
    }
    ll pen = 0;
    ll mult = 0;
    rep(i, 0, n) {
        if(i % m == 0) mult++;
        pen += a[i] * mult;
    }

    vector<ll> pens;
    rep(i, 0, n) {
        pens.push_back(pen);
        pen -= pr[i%m].back() - pr[i%m][i/m];
    }
    reverse(all(pens));
    prv(pens);

    return 0;
}