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
    scii(n, m);
    vector<vi> A(n, vi(m, 0));
    vector<vi> B(n, vi(m, 0));
    vector<ii> q;
    rep(i, 0, n) rep(j, 0, m) cin >> A[i][j];
    rep(i, 0, n - 1) rep(j, 0, m - 1) {
        if(A[i][j] & A[i+1][j] & A[i][j+1] & A[i+1][j+1]) {
            B[i][j] = 1;
            B[i+1][j] = 1;
            B[i][j+1] = 1;
            B[i+1][j+1] = 1;
            q.pb({i + 1, j + 1});
        }
    }

    rep(i, 0, n) rep(j, 0, m) {
        if(A[i][j] != B[i][j]) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << q.size() << '\n';
    for(ii x : q) {
        cout << x.st << ' ' << x.nd << '\n';
    }

    return 0;
}