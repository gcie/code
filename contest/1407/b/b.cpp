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

template <typename T>
vector<size_t> index_sort(const vector<T> &v) {
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
    return idx;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    TC(_t) {
        sci(n);
        scvi(a, n);
        sort(a.begin(), a.end());
        reverse(all(a));
        // prv(a);
        int q = a[0];
        vi used(n, 0);
        used[0] = 1;
        vi gcd(n, 0);
        cout << q << ' ';
        rep(i, 1, n) {
            fill(all(gcd), 0);
            rep(i, 0, n) {
                if(!used[i]) {
                    gcd[i] = __gcd(q, a[i]);
                }
            }
            int largest_gcd_idx = index_sort(gcd)[n-1];
            cout << a[largest_gcd_idx] << ' ';
            q = gcd[largest_gcd_idx];
            used[largest_gcd_idx] = 1;
        }
        cout << '\n';



    }

    return 0;
}