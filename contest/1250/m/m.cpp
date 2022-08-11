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

pair<vi, vi> ins_co_k(int r, int c, int k, int n) {
    vi rs, cs; r = r % k; c = c % k;
    while(r < n) {
        rs.push_back(r);
        r += k;
    }
    while(c < n) {
        cs.push_back(c);
        c += k;
    }
    return {rs, cs};
}

void apply(vector<vi> &q, pair<vi, vi> cmd, int op = 1) {
    for(auto &r : cmd.st){
        for(auto &c : cmd.nd) {
            q[r][c] = op;
        }
    }
}

void show(vector<vi> &q) {
    for(auto &v : q) {
        for(auto &x : v) {
            cout << (x == 0 ? '.' : (x == 2 ? '#' : '*'));
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    sci(n);
    vector<vi> q(n, vi(n, 0));
    for(int i = 0; i < n; i++) {
        q[i][i] = 2;
        if(i > 0) q[i][i-1] = 2;
    }
    // rep(i, 0, 3) {
    //     auto k = ins_co_k(i, 1+i, 3, n);
    //     apply(q, k);
    // }
    rep(i, 0, 4) {
        auto k = ins_co_k(i, 1+i, 4, n);
        apply(q, k);
        k = ins_co_k(i, 2+i, 4, n);
        apply(q, k);
    }
    // rep(i, 0, 5) {
    //     auto k = ins_co_k(i, 3+i, 5, n);
    //     apply(q, k);
    // }
    // rep(i, 0, 7) {
    //     auto k = ins_co_k(i, 3+i, 7, n);
    //     apply(q, k);
    // }
    // rep(i, 0, 11) {
    //     auto k = ins_co_k(i, 12+i, 11, n);
    //     apply(q, k);
    // }
    // rep(i, 0, 13) {
    //     auto k = ins_co_k(i, 5+i, 13, n);
    //     apply(q, k);
    // }
    show(q);


    return 0;
}