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

struct union_find {
    vector<int> par, sz;
    union_find(int n) {
        par.resize(n); sz.resize(n);
        iota(par.begin(), par.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    }
    const int &operator[] (int i) {
        return par[i] == i ? i : (par[i] = (*this)[par[i]]);
    }
    void un(int i, int j) {
        i = (*this)[i], j = (*this)[j];
        if(i == j) return;
        if(sz[i] < sz[j]) par[i] = j, sz[j] += sz[i];
        else par[j] = i, sz[i] += sz[j];
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    scii(n, m);
    union_find uf(n);
    rep(i, 0, m) {
        scii(u, v);
        uf.un(--u, --v); 
    }
    vector<int> occ;
    vector<int> pos(n, -1);
    int cnt = 0;
    rep(i, 0, n) {
        if(!occ.empty() && occ.back() == uf[i]) continue;
        else if(pos[uf[i]] == -1) {
            pos[uf[i]] = occ.size();
            occ.push_back(uf[i]);
        } else {
            while(occ.back() != uf[i]) {
                uf.un(uf[i], occ.back());
                occ.pop_back();
                cnt++;
            }
            pos[uf[i]] = occ.size() - 1;
        }
    }
    cout << cnt << '\n';
    return 0;
}