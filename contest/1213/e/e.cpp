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

int n;


bool sub(string r, string s) {
    rep(i, 0, ((int)r.size()) - 1) {
        if(r[i] == s[0] and r[i + 1] == s[1]) return true;
    }
    return false;
}

void solve(string s, string t) {
    vector<string> q = {"abca", "acba", "bcab", "bacb", "cbac", "cabc"};
    rep(i, 0, 6) {
        if(sub(q[i], s) or sub(q[i], t)) {
            continue;
        }
        rep(j, 0, n) cout << q[i][0] << q[i][1] << q[i][2];
        cout << '\n';
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s, t;
    cin >> n >> s >> t;
    cout << "YES\n";
    if(s[0] != s[1] and s[0] == t[1] and s[1] == t[0]) {
        char c = 'a'; while(c == s[0] or c == s[1]) c = (char)((int)c + 1);
        rep(i, 0, n) cout << s[0];
        rep(i, 0, n) cout << c;
        rep(i, 0, n) cout << s[1];
        cout << '\n';
    } else if(s[1] == t[1] and s[0] != t[0] and s[0] != s[1] and t[0] != t[1]) {
        rep(i, 0, n) cout << s[1];
        char c = 'a';
        if(c == s[1]) c++;
        rep(i, 0, n) cout << c;
        c++;
        if(c == s[1]) c++;
        rep(i, 0, n) cout << c;
        cout << '\n';
    } else if(s[0] == t[0] and s[1] != t[1] and s[0] != s[1] and t[0] != t[1]) {
        char c = 'a';
        if(c == s[0]) c++;
        rep(i, 0, n) cout << c;
        c++;
        if(c == s[0]) c++;
        rep(i, 0, n) cout << c;
        rep(i, 0, n) cout << s[0];
        cout << '\n';
    } else solve(s, t);
    return 0;
}