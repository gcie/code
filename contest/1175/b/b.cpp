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

ll x = 0;
vector<pair<string, int>> fun;

void overflow() {
    cout << "OVERFLOW!!!\n"; exit(0);
}

pair<ll, int> get_for(int pos) {
    ll mult = fun[pos].second;
    ll vals = 0;
    int i = pos + 1;
    while(fun[i].first != "end") {
        if(fun[i].first == "for") {
            auto r = get_for(i);
            i = r.second;
            vals += r.first;
        } else if(fun[i].first == "add") {
            vals += 1;
        }
        i++;
    }
    if(mult * vals >= (1ll<<32)) overflow();
    return {mult * vals, i};
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    sci(l);
    rep(i, 0, l) {
        string cmd; cin >> cmd;
        if(cmd == "add") {
            fun.push_back({cmd, 1});
        } else if(cmd == "for") {
            int x; cin >> x;
            fun.push_back({cmd, x});
        } else {
            fun.push_back({cmd, 0});
        }
    }

    ll val = 0;
    int i = 0;
    while(i < l) {
        if(fun[i].first == "add") {
            val += 1;
            if(val >= (1ll<<32)) overflow();
        } else if(fun[i].first == "for") {
            auto x = get_for(i);
            i = x.second;
            val += x.first;
            if(val >= (1ll<<32)) overflow();
        }
        i++;
    }
    cout << val << '\n';
    
    
    return 0;
}