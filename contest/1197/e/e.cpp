#pragma gcc optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb              push_back
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
#define MOD 1000000007
#define in first
#define x first
#define out second
#define y second

typedef long long       ll;
typedef pair<int, int>  ii;
typedef pair<ll, ll> pll;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

using namespace std;

int add(int a, int b) {
    int c = a + b;
    if(c >= MOD) return c - MOD;
    else return c;
}

template<typename T>
struct seg_tree {
    vector<T> t;
    size_t n;
    T init_value = {1e9, 0};
    T op(T v1, T v2) {
        if(v1.x == v2.x) return {v1.x, add(v1.y, v2.y)};
        else return v1.x < v2.x ? v1 : v2;
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

    sci(n);
    vll m_out(n), m_in(n);
    vector<ii> mat(n);
    rep(i, 0, n) {
        scii(out_, in_);
        mat[i] = {in_, out_};
    }
    sort(all(mat));
    int max_in = mat[n-1].in;
    vector<ii> v(n, {1e9, 0});
    seg_tree<ii> dp(v); // dp[i] = (x, y)    ------ minimum space is x and there are y subsequences that i-th doll is minimal.
    for(int i = n - 1; i >= 0; i--) {
        if(mat[i].out > max_in) {
            dp.modify(i, {mat[i].in, 1});
        } else {
            auto g = lower_bound(mat.begin(), mat.end(), make_pair(mat[i].out, 0)) - mat.begin();
            auto f = dp.query(g, n);
            f.first = f.first - mat[i].out + mat[i].in;
            dp.modify(i, f);
        }
    }

   /*  rep(i, 0, n) {
        cout << mat[i].in << ' ' << mat[i].out << '\n';
    } cout << '\n';

    rep(i, 0, n) {
        auto f = dp.query(i, i+1);
        cout << f.x << ' ' << f.y << '\n';
    } cout << '\n'; */

    cout << dp.query(0, n).y << '\n';

    return 0;
}