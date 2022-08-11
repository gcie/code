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
    scii(n, k);
    scvi(t, n);
    vector<ll> a(k, 0);
    rep(i, 0, n) {
        a[t[i]-1]++;
    }
    sort(all(a));
    ll best = ((ll)k) * ((ll)a[k-1]);
    for(ll i = 1; i <= k; i++) {
        ll min_cap = a[k-1];
        rep(j, 0, i / 2) {
            min_cap = max(min_cap, a[j] + a[i-j-1]);
        }
        if(i % 2 == 1) {
            min_cap = max(min_cap, a[i/2]);
        }
        ll rides = i / 2 + (i % 2) + k - i;
        best = min(best, min_cap * rides);
    }
    cout << best << '\n';

    return 0;
}