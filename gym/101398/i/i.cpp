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
typedef vector<vi> vvi;

using namespace std;

vi solpass;

bool resolve(int x, vi &pass, vector<bool> &resolved, set<int> &not_resolved, vvi &onpassmustpass, vvi &onpassmustfail, vvi &onfailmustpass, vvi &onfailmustfail) {
    set<int> topass, tofail;
    if(pass[x] > 0) {
        for(int &y : onpassmustfail[x]) {
            if(pass[y] < 0) continue;
            if(pass[y] > 0) return false;
            else tofail.insert(y);
        }
        for(int &y : onpassmustpass[x]) {
            if(pass[y] < 0) return false;
            if(pass[y] > 0) continue;
            else topass.insert(y);
        }
    } else {
        for(int &y : onfailmustfail[x]) {
            if(pass[y] < 0) continue;
            if(pass[y] > 0) return false;
            else tofail.insert(y);
        }
        for(int &y : onfailmustpass[x]) {
            if(pass[y] < 0) return false;
            if(pass[y] > 0) continue;
            else topass.insert(y);
        }
    }
    set<int> intersect;
    set_intersection(topass.begin(),topass.end(),tofail.begin(),tofail.end(),std::inserter(intersect,intersect.begin()));
    if(!intersect.empty()) return false;
    for(auto &y: topass) {
        pass[y] = 1;
    }
    for(auto &y : tofail) {
        pass[y] = -1;
    }
    resolved[x] = true;
    not_resolved.erase(x);
    for(auto &y: topass) {
        if(!resolved[y] and !resolve(y, pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail)) return false;
    }
    for(auto &y : tofail) {
        if(!resolved[y] and !resolve(y, pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail)) return false;
    }
    return true;
}
bool solve(vi &pass, vector<bool> &resolved, set<int> &not_resolved, vvi &onpassmustpass, vvi &onpassmustfail, vvi &onfailmustpass, vvi &onfailmustfail);

bool trytrue(vi pass, vector<bool> resolved, set<int> not_resolved, vvi onpassmustpass, vvi onpassmustfail, vvi onfailmustpass, vvi onfailmustfail) {
    // cout << "trytrue pass: "; prv(pass);
    // cout << "trytrue nr: "; prv(not_resolved);
    int x = *(not_resolved.begin());
    pass[x] = 1;
    if(!resolve(x, pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail)) return false;
    // cout << "WOLOLO\n";
    // cout << "trytrue nr2: "; prv(not_resolved);
    return solve(pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail);
}
bool tryfalse(vi pass, vector<bool> resolved, set<int> not_resolved, vvi onpassmustpass, vvi onpassmustfail, vvi onfailmustpass, vvi onfailmustfail) {
    // cout << "trfalse pass: "; prv(pass);
    // cout << "trfalse nr: "; prv(not_resolved);
    int x = *(not_resolved.begin());
    pass[x] = -1;
    if(!resolve(x, pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail)) return false;
    return solve(pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail);
}

bool solve(vi &pass, vector<bool> &resolved, set<int> &not_resolved, vvi &onpassmustpass, vvi &onpassmustfail, vvi &onfailmustpass, vvi &onfailmustfail) {
    // prv(not_resolved);
    if(not_resolved.empty()) { solpass = pass; return true; }
    bool tr = trytrue(pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail);
    if(tr) return true;
    return tryfalse(pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail);
}

bool check(vi &pass, vvi &onpassmustpass, vvi &onpassmustfail, vvi &onfailmustpass, vvi &onfailmustfail) {
    for(int i = 0; i < ((int)pass.size()); i++) {
        if(pass[i] == 0) return false;
        if(pass[i] > 0) {
            for(int &y : onpassmustpass[i]) if(pass[y] < 0) return false;
            for(int &y : onpassmustfail[i]) if(pass[y] > 0) return false;
        } else {
            for(int &y : onfailmustpass[i]) if(pass[y] < 0) return false;
            for(int &y : onfailmustfail[i]) if(pass[y] > 0) return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n;
    while(cin >> n) {
        int m; cin >> m;
        vector<int> pass;
        solpass = {};
        vvi onfailmustpass;
        vvi onfailmustfail;
        vvi onpassmustfail;
        vvi onpassmustpass;
        vector<bool> resolved;
        set<int> not_resolved;
        onfailmustfail.assign(n, {});
        onfailmustpass.assign(n, {});
        onpassmustfail.assign(n, {});
        onpassmustpass.assign(n, {});
        pass.assign(n, 0);
        resolved.assign(n, false);
        not_resolved = {}; rep(i, 0, n) not_resolved.insert(i);
        rep(i, 0, m) {
            scii(a, b);
            if(a < 0 and b < 0) {
                a = -a; b = -b;
                onpassmustfail[--a].pb(--b);
                onpassmustfail[b].pb(a);
            } else if(a < 0 and b > 0) {
                a = -a;
                onpassmustpass[--a].pb(--b);
                onfailmustfail[b].pb(a);
            } else if (a > 0 and b < 0) {
                b = -b;
                onfailmustfail[--a].pb(--b);
                onpassmustpass[b].pb(a);
            } else {
                onfailmustpass[--a].pb(--b);
                onfailmustpass[b].pb(a);
            }
        }
        pass[0] = 1;
        
        if(!resolve(0, pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail)) {
            cout << "no\n";
            continue;
        }
        if(!solve(pass, resolved, not_resolved, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail)) {
            cout << "no\n";
            continue;
        }
        if(check(solpass, onpassmustpass, onpassmustfail, onfailmustpass, onfailmustfail)) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }


    return 0;
}