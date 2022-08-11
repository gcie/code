#pragma gcc optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb              push_back
#define ht              first
#define idx              second 
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
    scvi(h, n);

    vector<vi> G(n);
    set<ii> down;
    set<ii> up;

    rep(i, 0, n) {
        set<ii> up_rem;
        set<ii> up_add;
        for(auto &u : up) {
            if(h[i] > u.ht) {
                up_rem.insert(u);
                G[u.idx].push_back(i);
                if(h[i] < h[u.idx]) {
                    up_add.insert(make_pair(h[i], u.idx));
                }
            } else break;
        }
        for(auto& u: up_rem) up.erase(u);
        for(auto &u : up_add) up.insert(u);


        set<ii> down_rem;
        set<ii> down_add;
        for(auto &u : down) {
            if(h[i] < -u.ht) {
                down_rem.insert(u);
                G[u.idx].push_back(i);
                if(h[i] > h[u.idx]) {
                    down_add.insert(make_pair(-h[i], u.idx));
                }
            } else break;
        }
        for(auto& u: down_rem) down.erase(u);
        for(auto &u : down_add) down.insert(u);

        if(i < n - 1) {
            G[i].push_back(i+1);
            if(h[i] < h[i+1]) {
                down.insert(make_pair(-h[i+1], i));
            } else if(h[i] > h[i+1]) {
                up.insert(make_pair(h[i+1], i));
            }
        }
    }

    vi min_jumps(n, 2 * n);
    min_jumps[0] = 0;
    rep(i, 0, n - 1) {
        for(int &x : G[i]) {
            min_jumps[x] = min(min_jumps[x], min_jumps[i] + 1);
        }
    }

    cout << min_jumps[n-1] << '\n';



    // int pos = 0;
    // int jumps = 0;
    // while(pos < n - 1) {
    //     if(h[pos+1] == h[pos]) {
    //         jumps++;
    //         pos++;
    //     } else if(h[pos+1] > h[pos]) {
    //         int q = pos+1;
    //         int minh = h[q];
    //         int minpos = q;
    //         while(q < n && h[q] > h[pos]) {
    //             if(h[q] < minh) {                                                                                                                                                                                                                                                                                                                                                                                                
    //                 minh = h[q];
    //                 minpos = q;
    //             }
    //         }
    //     }
    // }



    return 0;
}