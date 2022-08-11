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

ll internal(ll size) {
    if(size >= 4) {
        return size * (size - 1) * (size - 2) * (size - 3) / 24;
    } else return 0ll;
}

void solve() {
	sci(n);
    scvi(a, n); rep(i, 0, n) a[i]--;
    vector<vi> lt(n, vi(n));
    vector<vi> gt(n, vi(n));
    vector<vi> idx(n, vi());
    rep(i, 0, n) {
        idx[a[i]].push_back(i);
    }
    rep(i, 0, n) {
        int total = 0;
        rep(j, 0, n) {
            lt[i][j] = total;
            total += a[j] == i;
        }
    }
    rep(i, 0, n) {
        int total = 0;
        for(int j = n - 1; j >= 0; --j) {
            gt[i][j] = total;
            total += a[j] == i;
        }
    }
    
    ll zigzags = 0;
    rep(i, 0, n) zigzags += internal((ll)idx[i].size());

    rep(i, 0, n-1) rep(j, i+1, n) {
        int I = idx[i].size();
        int J = idx[j].size();
        rep(_i, 0, I) rep(_j, 0, J) {
            if(idx[i][_i] < idx[j][_j]) {
                zigzags += (ll)lt[j][idx[i][_i]] * (ll)gt[i][idx[j][_j]];
            } else {
                zigzags += (ll)lt[i][idx[j][_j]] * (ll)gt[j][idx[i][_i]];
            }
        }
    }

    // prvv(idx);
    cout << zigzags << endl;

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	TC solve();
    return 0;
}