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

typedef pair<bool, int> lit;

typedef struct impl{
    lit l1, l2;
    impl(lit _l1, lit _l2): l1(_l1), l2(_l2) {}
} impl;

lit neg(lit a) {
    lit b(!a.st, a.nd);
    return b;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    sci(n);
    scvi(w1, n);
    scvi(w2, n);
    scvi(w3, n);
    set<lit> g1, g2, g3;
    set<lit> g;
    rep(i, 0, n) {
        if(w1[i] and 0 == w2[i] and 0 == w3[i]) {
            lit a(true, i);
            g1.insert(a);
        } else if(0 == w1[i] and w2[i] and 0 == w3[i]) {
            lit a(true, i);
            g2.insert(a);
        } else if(0 == w1[i] and 0 == w2[i] and w3[i]) {
            lit a(true, i);
            g3.insert(a);
        } else if(0 == w1[i] and w2[i] and w3[i]) {
            lit a(false, i);
            g1.insert(a);
        } else if(w1[i] and 0 == w2[i] and w3[i]) {
            lit a(false, i);
            g2.insert(a);
        } else if(w1[i] and w2[i] and 0 == w3[i]) {
            lit a(false, i);
            g3.insert(a);
        } else if(w1[i] and w2[i] and w3[i]) {
            lit a(true, i);
            g.insert(a);
        } else {
            lit a(false, i);
            g.insert(a);
        }
    }

    vector<impl> sat;
    if(g1.empty()) {
        g1.insert(g3.begin(), g3.end());
        g3.clear();
    } else if(g2.empty()) {
        g2.insert(g3.begin(), g3.end());
        g3.clear();
    }


    if(!g3.empty()) {
        cout << -1 << '\n';
        return 0;
    }

    {
        auto it1 = g1.begin();
        auto it2 = g1.begin();
        it2++;
        while(it2 != g1.end()) {
            impl i1(*it1, *it2);
            impl i2(*it2, *it1);
            sat.push_back(i1);
            sat.push_back(i2);
            it1++;
            it2++;
        }
        impl i1(*g1.begin(), *g1.rbegin());
        impl i2(*g1.rbegin(), *g1.begin());
        sat.push_back(i1);
        sat.push_back(i2);
    }
    {
        auto it1 = g2.begin();   
        auto it2 = g2.begin();
        it2++;
        while(it2 != g2.end()) {
            impl i1(*it1, *it2);
            impl i2(*it2, *it1);
            sat.push_back(i1);
            sat.push_back(i2);
            it1++;
            it2++;
        }
        impl i1(*g2.begin(), *g2.rbegin());
        impl i2(*g2.rbegin(), *g2.begin());
        sat.push_back(i1);
        sat.push_back(i2);
    }
    for(lit a: g) {
        impl im(neg(a), a);
        sat.push_back(im);
    }
    impl im(*g1.begin(), neg(*g2.begin()));
    sat.push_back(im);

    cout << sat.size() << '\n';
    for(auto i : sat) {
        cout << (i.l1.st ? "x" : "!x") << i.l1.nd + 1 << " -> " << (i.l2.st ? "x" : "!x") << i.l2.nd + 1 << '\n';
    }

    return 0;
}