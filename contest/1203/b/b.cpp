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

bool check(vi a, int n, int ar) {
    int l = 0, r = 4 * n - 1;
    while(l < r) {
        if(a[l] != a[l+1] or a[r] != a[r-1] or a[l] * a[r] != ar) return false;
        l += 2; r -= 2;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    TC(q) {
        sci(n);
        scvi(a, 4 * n);
        sort(all(a));
        int l = 0, r = 4 * n - 1;
        int ar = a[l] * a[r];
        cout << (check(a, n, ar) ? "YES\n" : "NO\n");
    }

    return 0;
}