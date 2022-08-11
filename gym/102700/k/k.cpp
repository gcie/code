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


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    string s1, s2;
    cin >> s1 >> s2;

    int s1i = 0, s2i = 0;
    while(s1[s1i] > '9' || s1[s1i] < '0') s1i++;
    while(s1[s2i] > '9' || s1[s2i] < '0') s2i++;

    string l1 = s1.substr(0, s1i);
    string l2 = s2.substr(0, s2i);

    string n1 = s1.substr(s1i, s1.length() - s1i);
    string n2 = s2.substr(s2i, s2.length() - s2i);

    int c1 = l1.compare(l2);

    if(c1 > 0) {
        cout << '>';
    } else if(c1 < 0) {
        cout << '<';
    } else if(n1.length() > n2.length()) {
        cout << '>';
    } else if(n1.length() < n2.length()) {
        cout << '<';
    } else {
        int c2 = n1.compare(n2);
        if(c2 > 0) {
            cout << '>';
        } else if(c2 < 0) {
            cout << '<';
        }   else {
            cout << '=';
        }
    }

    cout << '\n';

    return 0;
}