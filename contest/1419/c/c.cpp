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
#define TC              sci(__test_case); while(__test_case --)
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

void res(int x) {
    cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    TC {
        scii(n, x);

        scvi(a, n);

        bool all_eq = 1;
        ll m = 0;
        ll x_eq = 0;
        rep(i, 0, n) {
            if(a[i] == x) x_eq++;
            else m += a[i];

        }

        if(x_eq == n) {
            res(0);
            continue;
        }

        if(x_eq > 0) {
            res(1);
            continue;
        } 

        if(m == x * n) { // m / n = x
            res(1);
            continue;
        }
        res(2);


        // bool can_infect_all = false;
        // for(int i = 1; i <= x_eq; i++) {
        //     if((m + i * x) % (k + i) == 0) {
        //         can_infect_all = true;
        //     }
        // }

        // if(can_infect_all) {
        //     res(1);
        //     continue;
        // }

        // if(x_eq > 0) {
        //     res(2);
        //     continue;
        // }


               

    }

    return 0;
}