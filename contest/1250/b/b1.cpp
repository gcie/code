#pragma gcc optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb              push_back
#define st              first
#define nd              second 
#define mp make_pair
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
typedef pair<ll, ll>  ii;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    scii(n, k);
    scvi(t, n);
    vector<ll> a(k, 0);
    rep(i, 0, n) {
        a[t[i]-1]++;
    }
    sort(all(a));
    vector<vector<ii>> dp(k, vector<ii>(k, {0, 0}));
    rep(i, 0, k) {
        dp[i][i] = {1ll, a[i]};
    }
    rep(i, 0, k - 1) {
        dp[i][i+1] = {1ll, a[i] + a[i+1]};
    }
    for(int d = 2; d < k; d++) {
        rep(i, 0, k - d) {

            ll r1 = dp[i][i+d-1].st;
            ll s1 = dp[i][i+d-1].nd;
            ll R1 = r1 + 1;
            ll S1 = max(s1, a[i+d]);

            ll r2 = dp[i+1][i+d-1].st;
            ll s2 = dp[i+1][i+d-1].nd;
            ll R2 = r2 + 1;
            ll S2 = max(s2, a[i] + a[i+d]);

            dp[i][i+d] = ((R1 * S1 < R2 * S2) ? mp(R1, S1) : mp(R2, S2));
        }
    }
    cout << dp[0][k-1].st * dp[0][k-1].nd << '\n';

    return 0;
}