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

string s, t;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> s >> t;
    vi l(((int)t.size())), r(((int)t.size()));
    int q = 0;
    for(int i = 0; i < s.size() and q < t.size(); i++) {
        if(s[i] == t[q]) {
            l[q++] = i;
        }
    }
    q = t.size() - 1;
    for(int i = s.size() - 1; i >= 0 and q >= 0; i--) {
        if(s[i] == t[q]) {
            r[q--] = i;
        }
    }
    int n = t.size();
    int k = max(r[0], ((int)s.size()) - 1 - l[n - 1]);
    for(int i = 0; i < n - 1; i++) {
        k = max(k, r[i + 1] - l[i] - 1);
    }
    cout << k << '\n';
    return 0;
}