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

vector<int> arr = {8, 9, 1, 13, 3, 12, 7, 5, 0, 2, 4, 11, 6, 10, 15, 14};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    sci(n);
    /* int q = 0;
    int m = n / 4;
    vector<vector<int>> grid(n, vector<int>(n));
    rep(i, 0, m) {
        rep(j, 0, m) {
            rep(k, 0, 4) rep(l, 0, 4)  grid[i * 4  +k][j * 4 + l] = arr[k * 4 + l] + q;
            q += 16;
        }
    } */
    rep(i, 0, n) {
        rep(j, 0, n) cout << i * n + j << ' ';
        cout << '\n';
    }
    return 0;
}