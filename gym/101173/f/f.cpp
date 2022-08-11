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
    sci(n);
    scvi(p, n);
    scvi(q, n);
    rep(i, 0, n) { p[i]--; q[i]--; }
    vector<bool> p_bottom(n, true), q_bottom(n, true);
    vi p_height(n, 0), q_height(n, 0);
    for(int i = n - 1; i >= 0; --i) {
        if(p[i] != -1) {
            p_bottom[p[i]] = false;
            p_height[i] = p_height[p[i]] + 1;
        }
        if(q[i] != -1) {
            q_bottom[q[i]] = false;
            q_height[i] = q_height[q[i]] + 1;
        }
    }
    int save = 0, destroy = 0, build = 0;
    rep(i, 0, n) {
        if(p_bottom[i] and q_bottom[i]) {
            int v = i;
            while(p[v] != -1 and q[v] != -1 and p[v] == q[v]) {
                v = p[v];
                save += 2;
            }
        }
        if(p_bottom[i]) destroy += p_height[i];
        if(q_bottom[i]) build += q_height[i];
    }
    cout << build + destroy - save << '\n';
    return 0;
}