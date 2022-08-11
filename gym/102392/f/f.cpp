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

vi par;
vector<vi> succ;
vector<vi> nbh;
set<int> leaves;

void build_tree(int v = 0) {
    if(nbh[v].size() == 1 && v != 0) leaves.insert(v);
    for(int w : nbh[v]) {
        if(w != par[v]) {
            par[w] = v;
            succ[v].push_back(w);
            build_tree(w);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    sci(n);
    int root = 0;
    par.resize(n);
    par[root] = -1;
    nbh.resize(n);
    succ.resize(n);
    rep(i, 0, n - 1) {
        scii(a, b);
        nbh[--a].push_back(--b);
        nbh[b].push_back(a);
    }
    build_tree();

    vector<bool> result_down(n, false);
    vector<int> who_failed_down(n, 0);
    vector<int> fail_cnt_down(n, 0);
    vector<int> resolved(n, 0);
    set<int> vs = leaves;

    while(!vs.empty()) {
        set<int> nvs;
        for(int v : vs) {
            if(par[v] != -1) resolved[par[v]]++;
            result_down[v] = succ[v].size() > 0;
            for(int &w : succ[v]) {
                result_down[v] &= result_down[w];
                fail_cnt_down[v] += fail_cnt_down[w];
            }
            if(!result_down[v]) fail_cnt_down[v]++;
            if(par[v] != -1) {
                if(resolved[par[v]] == succ[par[v]].size()) nvs.insert(par[v]);
            }
        }
        vs = nvs;
    }

    vector<bool> result_up(n, false);
    
    vs.insert(all(succ[root]));
    
    while(!vs.empty()) {
        set<int> nvs;
        for(int v : vs) {
            if(!result_down[par[v]] and !result_up[par[v]]) {
                result_up[v] = true;
            } else if(!result_up[par[v]] and who_failed_down[par[v]] == v and fail_cnt_down[par[v]] == 1) {
                result_up[v] = true;
            }
            nvs.insert(all(succ[v]));
        }
        vs = nvs;
    }

    rep(i, 0, n) {
        if(!result_up[i] and !result_down[i]) {
            cout << "Alice\n"; return 0;
        }
    }
    cout << "Bob\n";
    return 0;
}