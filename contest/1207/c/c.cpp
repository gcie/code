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
#define INF 1000000000000000ll
using namespace std;

typedef long long       ll;
typedef pair<int, int>  ii;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    TC(t) {
        sci(n)
        ll a, b; cin >> a >> b;
        string s; cin >> s;
        vll dp1(n), dp2(n);
        dp1[0] = 2 * b + a;
        dp2[0] = 3 * b + 2 * a;
        rep(i, 1, n) {
            if(s[i] == '1') {
                dp2[i] = dp2[i-1] + 2 * b + a;
                dp1[i] = INF;
            } else {
                dp1[i] = min(dp1[i - 1] + b + a, dp2[i - 1] + b + 2 * a);
                dp2[i] = min(dp2[i-1] + 2 * b + a, dp1[i - 1] + 2 * b + 2 * a);
            }
        }
        cout << dp1[n-1] << '\n';
    }

    return 0;
}