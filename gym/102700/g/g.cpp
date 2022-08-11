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

const int MOD = 1000000007;
typedef pair<long long, long long> rational;

int mmul(int a, int b) { return ((ll)a * (ll)b) % MOD; }
int msq(int a) { return mmul(a, a); }
int mpow(int a, int b) { return b == 0 ? 1 : (b & 1 ? mmul(a, msq(mpow(a, b>>1))) : msq(mpow(a, b>>1))); }
int minv(int a, int b = MOD, int s0 = 1, int s1 = 0) { return b==0? s0: minv(b, a%b, s1, (s0 - mmul(s1, (a/b)) + MOD) % MOD); }
int mdiv(int a, int b) { return mmul(a, minv(b)); }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    scii(n, m);
    int f = 1;
    rep(i, 2, n + 1) f = mmul(f, i);
    cout << mdiv(f, pow(2, m)) << '\n';

    return 0;
}