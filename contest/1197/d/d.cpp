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

int n, m, k;
ll dp[10][300005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> n >> m >> k;
    scvi(a, n);

    for(int j = 0; j < m; j++) dp[j][0] = 0; dp[1][0] = a[0];
    for(int i = 0; i < n; i++) {
        dp[0][i] = max(0ll, dp[m-1][i-1] + a[i] - k);
        for(int j = 1; j < m; j++) {
            if(j <= i + 1) dp[j][i] = dp[j-1][i-1] + a[i];
        }
    }
    ll mmax = 0;
    rep(i, 0, n) mmax = max(mmax, dp[0][i]);
    for(int j = 1; j < m; j++) {
        for(int i = 0; i < n; i++) {
            mmax = max(mmax, dp[j][i] - k);
        }
    }

    cout << mmax << '\n';

    return 0;
}