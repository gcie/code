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
typedef set<ll, greater<ll>> setig;

using namespace std;

ll gcd(ll a, ll b)
{
	if(b==0) return a;
	a%=b;
		return gcd(b,a);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    TC(T) {
        sci(n);
        scvll(as, n);
        map<ll, int> gtl;
        setig keys;
        ll m = 0;
        for(ll &a : as) {
            map<ll, int> new_gtl;
            setig new_keys;
            new_gtl[a] = 1;
            m = max(m, a);
            new_keys.insert(a);
            for(auto &k : keys) {
                ll g = gcd(k, a);
                new_gtl[g] = gtl[k] + 1;
                new_keys.insert(g);
                m = max(m, g * new_gtl[g]);
            }
            gtl = new_gtl;
            keys = new_keys;
        }
        cout << m << '\n';
    }

    return 0;
}