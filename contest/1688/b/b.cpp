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

int to_odd(int n) {
    if(n & 1) return 0;
    else return 1 + to_odd(n / 2);
}

void solve() {
	sci(n);
    scvi(a, n);
    int odd =0;
    rep(i, 0, n) odd += (a[i] & 1);
    if(odd == 0) {
        int min_dist = 1e9;
        rep(i, 0, n) {
            int dist = to_odd(a[i]);
            if(dist < min_dist) min_dist = dist;
        }
        cout << min_dist + (n - 1) << endl;
    } else {
        cout << n - odd << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	TC solve();
    return 0;
}