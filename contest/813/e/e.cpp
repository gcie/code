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

vi prev1;

int prev(int x, int k) {
    if(x == -1) return -1;
    if(k == 1) return prev1[x];
    else return prev(prev1[x], k - 1);
}

template<typename T>
struct seg_tree {
    vector<T> t;
    size_t n;
    T init_value = 0;
    T op(T v1, T v2) {
        return v1 + v2;
    }
    seg_tree(vector<T> v) {
        n = v.size();
        t.resize(2 * n);
        fill(t.begin(), t.end(), init_value);
        for(size_t i = 0; i < n; ++i) t[n + i] = v[i];
        for(size_t i = n - 1; i > 0; --i) t[i] = op(t[i<<1], t[i<<1|1]);
    }
    void modify(size_t p, T value) {  // set value at position p
        for(t[p += n] = value; p > 1; p >>= 1) t[p>>1] = op(t[p], t[p^1]);
    }
    T query(size_t l, size_t r) {  // sum on interval [l, r)
        T res = init_value;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = op(res, t[l++]);
            if (r&1) res = op(res, t[--r]);
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    scii(n, k);
    scvi(a, n);
    prev1.resize(n);
    map<int, int> last_pos;
    rep(i, 0, n) {
        prev1[i] = last_pos[a[i]] - 1;
        last_pos[a[i]] = i + 1;
    }
    vi b(n);
    rep(i, 0, n) b[i] = prev(i, k);
    TC(q) {
        scii(x, y);
    }

    return 0;
}