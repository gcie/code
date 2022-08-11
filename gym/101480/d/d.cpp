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
#define mod 1000000007

using namespace std;

typedef long long       ll;
typedef pair<int, int>  ii;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

ll k(ll x) {
    return (x * x) % mod;
}

ll mpow(ll a, ll b) {
    return b == 0 ? 1 : (b & 1 ? (a * k(mpow(a, b>>1))) % mod : k(mpow(a, b>>1)));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    sci(n);
    ll m; cin >> m;
    string s;
    cin >> s;
    ll d = 0;
    int c = 0;
    for(int i = 0; i < s.size(); i++) {
        d = (d * 10) % m;
        d = (d + (s[i] - '0')) % m;
        if(d == 0) c++;
    }
    if(d == 0) {
        cout << mpow(2, c - 1) << '\n';
    } else {
        cout << 0 << '\n';
    }


    return 0;
}