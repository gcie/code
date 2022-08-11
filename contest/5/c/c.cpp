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

ii add_sol(ii prev, int n) {
    if(n > prev.first) {
        return {n, 1};
    } else if(n == prev.first) {
        return {n, prev.second + 1};
    } else return prev;
}


void solve() {
	string s;
    cin >> s;
    int n = s.length();
    int d = 0;
    map<int, int> last;
    ii sol = {0, 1};
    rep(i, 0, n) {
        if(last.find(d) != last.end() && last[d] != -1) {
            sol = add_sol(sol, i - last[d]);
        }
        if(s[i] == '(') {
            if(last.find(d) == last.end() || last[d] == -1) {
                last[d] = i;
            }
            d += 1;
        } else {
            last[d] = -1;
            d -= 1;
        }
    }
    if(last.find(d) != last.end() && last[d] != -1) {
        sol = add_sol(sol, n - last[d]);
    }
    cout << sol.first << ' ' << sol.second << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	solve();
    return 0;
}