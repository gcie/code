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


void solve() {
	scii(n, m);
    vi a(n);
    rep(i, 0, n) {
        sci(x); a[i] = x % m;
    }
    sort(all(a));
    vi rem(m, 0);
    rep(i, 0, n) rem[a[i]] = min(rem[a[i]] + 1, m);


    if(rem[0] > 0) {
        cout << "YES\n";
        return;
    }

    vector<vector<bool>> dp;
    int t = -1;
    rep(i, 1, m) {
        while(rem[i]-->0) {
            dp.push_back(vector<bool>(m, false));
            dp[t+1][i] = 1;
            rep(k, 0, m) {
                if(t >= 0 && dp[t][k]) {
                    dp[t+1][k] = 1;
                    dp[t+1][(k+i)%m] = 1;
                }
            }
            t += 1;
        }
    }
    if(dp[t][0]) cout << "YES\n"; else cout << "NO\n";

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	solve();
    return 0;
}