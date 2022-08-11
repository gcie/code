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
    string s;
    cin >> s;
    int n = ((int)s.length()) / 2;
    sort(s.begin(), s.end());
    map<char, int> occ;
    for(char c : s) occ[c]+=1;
    char mostocc = '.';
    for(pair<char, int> e : occ) {
        if(e.nd > n) mostocc = e.st;
    }
    if(mostocc == '.') {
        cout << "YES\n";
        cout << s << '\n';
    } else if(occ[mostocc] > 2 * n - 2) {
        cout << "NO\n";
    } else if(occ[mostocc] == 2 * n - 2) {
        string other = "";
        rep(i, 0, 2 * n) if(s[i] != mostocc) other += s[i];
        if(other[0] != other[1]) {
            cout << "YES\n";
            rep(i, 0, n - 1) cout << mostocc;
            cout << other[0];
            rep(i, 0, n - 1) cout << mostocc;
            cout << other[1];
            cout << '\n';
        } else {
            cout << "NO\n";
        }
    } else if(occ[mostocc] > n) {
        cout << "YES\n";
        int k = 2 * n - occ[mostocc];
        string other = "";
        rep(i, 0, 2 * n) {
            if(s[i] != mostocc) other += s[i];
        }
        rep(i, 0, n - 1) cout << mostocc;
        cout << other[0];
        rep(i, 0, n - k + 1) cout << mostocc;
        rep(i, 1, k) cout << other[i];
        cout << '\n';
    }

    return 0;
}