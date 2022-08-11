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
    vector<int> lengths;
    string s; getline(cin, s);
    int i = 0;
    int c = 0;
    while(i < s.size()) {
        if(s[i] == ' ') {
            lengths.push_back(c);
            c = 0;
        } else c++;
        i++;
    }
    if(!s.empty()) lengths.push_back(c);
    ll ls = -1; for(auto &x : lengths) ls += x + 1;
    scii(a, b);

    vector<int> beg(ls, -1);
    vector<int> l(ls, -1);
    int prs = 0;
    for(auto &x : lengths) {
        l[prs] = x;
        for(int i = 0; i < x; i++) {
            beg[i+prs] = prs;
        }
        prs += x + 1;
    }
    // prv(beg);
    // prv(l);

    for(int i = a; i <= b; i++) {
        int q = 0;
        int pos = 0;
        while(true) {
            // cout << "(" << pos << ", " << l[pos] << ", " << beg[pos] <<  ") ";
            if(l[pos] != -1) q += l[pos] + 1;
            pos += i;
            // cout << "(" << pos << ", " << l[pos] << ", " << beg[pos] <<  ") ";
            if(pos >= ls) break;
            else if (beg[pos] == -1) {
                pos++;
            } else pos = beg[pos];
        }
        cout << q - 1 << '\n';
    }


    return 0;
}