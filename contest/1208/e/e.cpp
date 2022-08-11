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

template<typename T>
struct alt_seg_tree {
    vector<T> t;
    size_t n;
    T init_value = 0;
    T op(T v1, T v2) {
        return v1 + v2;
    }
    alt_seg_tree(vector<T> v) { // build tree, comp = n
        n = v.size();
        t.resize(2 * n);
        fill(t.begin(), t.end(), init_value);
        for(size_t i = 0; i < n; ++i) t[n + i] = v[i];
    }
    
    void modify_segment(size_t l, size_t r, T value) { // add value on interval [l, r), comp = logn 
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) { t[l] = op(t[l], value); l++; }
            if (r&1) { --r; t[r] = op(t[r], value); }
        }
    }
    T query_point(size_t p) { // return value at point p, comp = logn
        T res = init_value;
        for (p += n; p > 0; p >>= 1) res = op(res, t[p]);
        return res;
    }
    void push() { // push changes to leaves, comp = n
        for (size_t i = 1; i < n; ++i) {
            t[i<<1] = op(t[i<<1], t[i]);
            t[i<<1|1] = op(t[i<<1|1], t[i]);
            t[i] = init_value;
        }
    }
    T leaf(size_t p) { // return value stored in leaf p, comp = 1
        return t[p + n];
    }
};

template<typename T>
struct seg_tree {
    vector<T> t;
    size_t n;
    T init_value = -2000000000;
    T op(T v1, T v2) {
        return max(v1, v2);
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
    scii(n, w);
    vector<vi> ar(n);
    rep(i, 0, n) {
        sci(l); scvi(a, l); ar[i] = a;
    }
    alt_seg_tree<ll> c(vector<ll>(w, 0));
    rep(i, 0, n) {
        if(2 * ar[i].size() <= w) {
            // cout << "SIMPLE\n";
            // simple case, pref/suf max
            int pmax = 0, smax = 0;
            for(int l = 0; l < ar[i].size(); l++) {
                pmax = max(pmax, ar[i][l]);
                c.modify_segment(l, l + 1, pmax);
            }
            for(int r = 0; r < ar[i].size(); r++) {
                smax = max(smax, ar[i][ar[i].size() - r - 1]);
                c.modify_segment(w - r - 1, w - r, smax);
            }
            c.modify_segment(ar[i].size(), w - ar[i].size(), pmax);
        } else {
            // cout << "COMPLEX\n";
            // complex case
            seg_tree<int> t(ar[i]);
            for(int j = 0; j < w; j++) {
                int mmax = -2000000000;
                if(j < w - ar[i].size() or j >= ar[i].size()) mmax = 0;
                mmax = max(mmax, t.query(max(0, j - (w - ((int)ar[i].size()))), min(((int)ar[i].size()), j + 1)));
                c.modify_segment(j, j + 1, mmax);
            }
        }
    }

    c.push();
    rep(i, 0, w) cout << c.leaf(i) << ' '; cout << '\n';

    return 0;
}