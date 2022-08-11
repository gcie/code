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
	sci(n);
    ll x; cin >> x;
    scvi(d, n);
    ll i1 = 0, i2 = 0, j1 = 0, j2 = x;

    ll dsum = 0; rep(i, 0, n) dsum += (ll)d[i];

    if(x == dsum) {
        ll hugs = 0;
        rep(i, 0, n) hugs += (ll)d[i] * ((ll)d[i] + 1) / 2ll;
        cout << hugs << endl;
        return;
    }

    while(j2 - d[j1] >= 0) {
        j2 -= d[j1];
        j1++;
    }
    ll hugs = j2 * (j2 + 1) / 2;
    rep(i, i1, j1) hugs += (ll)d[i] * ((ll)d[i] + 1) / 2ll;
    // cout << hugs << endl;
    ll max_hugs = hugs;
    while(i1 < n) {
        if(d[j1] - j2 < d[i1] - i2) {
            int q = d[j1] - j2;
            ll neg = (ll)(i2 * 2 + q + 1) * (ll)q / 2ll;
            ll pos = (ll)(j2 * 2 + q + 1) * (ll)q / 2ll;
            hugs += pos - neg;
            max_hugs = max(max_hugs, hugs);
            i2 += q;
            j1 = (j1 + 1) % n;
            j2 = 0;
        } else if (d[j1] - j2 > d[i1] - i2) {
            int q = d[i1] - i2;
            ll neg = (ll)(i2 * 2 + q + 1) * (ll)q / 2ll;
            ll pos = (ll)(j2 * 2 + q + 1) * (ll)q / 2ll;
            hugs += pos - neg;
            max_hugs = max(max_hugs, hugs);
            j2 += q;
            i1++;
            i2 = 0;
        } else {
            int q = d[i1] - i2;
            ll neg = (ll)(i2 * 2 + q + 1) * (ll)q / 2ll;
            ll pos = (ll)(j2 * 2 + q + 1) * (ll)q / 2ll;
            hugs += pos - neg;
            max_hugs = max(max_hugs, hugs);
            i1++;
            j1 = (j1 + 1) % n;
            i2 = 0;
            j2 = 0;
        }
    }

    cout << max_hugs << endl;

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	solve();
    return 0;
}