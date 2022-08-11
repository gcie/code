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

string s1 = "....x....x....x....x....x....x....x";
string s2 = "xxxxx....x....xxxxxxx....x....xxxxx";
string s3 = "xxxxx....x....xxxxxx....x....xxxxxx";
string s4 = "x...xx...xx...xxxxxx....x....x....x";
string s5 = "xxxxxx....x....xxxxx....x....xxxxxx";
string s6 = "xxxxxx....x....xxxxxx...xx...xxxxxx";
string s7 = "xxxxx....x....x....x....x....x....x";
string s8 = "xxxxxx...xx...xxxxxxx...xx...xxxxxx";
string s9 = "xxxxxx...xx...xxxxxx....x....xxxxxx";
string s0 = "xxxxxx...xx...xx...xx...xx...xxxxxx";
string sp = ".......x....x..xxxxx..x....x.......";

map<string, int> smtoi;
map<int, string> itosm;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s[7];
    smtoi[s0] = 0;
    smtoi[s1] = 1;
    smtoi[s2] = 2;
    smtoi[s3] = 3;
    smtoi[s4] = 4;
    smtoi[s5] = 5;
    smtoi[s6] = 6;
    smtoi[s7] = 7;
    smtoi[s8] = 8;
    smtoi[s9] = 9;
    smtoi[sp] = -1;
    itosm[0] = s0;
    itosm[1] = s1;
    itosm[2] = s2;
    itosm[3] = s3;
    itosm[4] = s4;
    itosm[5] = s5;
    itosm[6] = s6;
    itosm[7] = s7;
    itosm[8] = s8;
    itosm[9] = s9;

    rep(i, 0, 7) cin >> s[i];
    int n = (s[0].length() + 1) / 6;
    ll i1 = 0, i2 = 0;
    bool fdone = false;
    rep(i, 0, n) {
        int off = i * 6;
        string p = "";
        rep(j, 0, 7) {
            p += s[j].substr(off, 5);
        }
        if(smtoi[p] == -1) {
            fdone = true;
        } else if(!fdone) {
            i1 *= 10;
            i1 += smtoi[p];
        } else {
            i2 *= 10;
            i2 += smtoi[p];
        }
    }
    ll res = i1 + i2;
    vector<int> r;
    if(res == 0) {
        cout << "xxxxx\nx...x\nx...x\nx...x\nx...x\nx...x\nxxxxx";
    } else {
        while(res > 0) {
            r.push_back(res % 10);
            res /= 10;
        }
        reverse(all(r));
        rep(i, 0, 7) {
            for(int j = 0; j < r.size(); j++) {
                cout << itosm[r[j]].substr(i*5, 5);
                if(j + 1 != r.size()) cout << '.';
                else cout << '\n';
            }
        }
    }
    return 0;
}