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

template<typename T = int>
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
    vector<vector<int>> img(n, vector<int>(n));
    rep(i, 0, n) {
        string s; cin >> s;
        rep(j, 0, n) img[i][j] = (s[j] == 'B' ? 1 : 0); 
    }

    vector<vi> row_pre(n), row_suf(n), col_pre(n), col_suf(n);
    rep(i, 0, n) {
        int rpi = 0, rsi = 0, cpi = 0, csi = 0;
        rep(j, 0, n) {
            row_pre[i].pb(rpi);
            row_suf[i].pb(rsi);
            col_pre[i].pb(cpi);
            col_suf[i].pb(csi);
            rpi += img[i][j];
            rsi += img[i][n - j - 1];
            cpi += img[j][i];
            csi += img[n - j - 1][i];
        }
        row_pre[i].pb(rpi);
        row_suf[i].pb(rsi);
        col_pre[i].pb(cpi);
        col_suf[i].pb(csi);
    }
    // prvv(row_pre); cout << '\n';
    // prvv(row_suf); cout << '\n';
    // prvv(col_pre); cout << '\n';
    // prvv(col_suf); cout << '\n';

    vector<vi> row_tr(n - k + 1, vi(n)), col_tr(n - k + 1, vi(n));
    rep(i, 0, n) {
        rep(j, 0, n - k + 1) row_tr[j][i] = (0 == row_pre[i][j] and row_suf[i][n - k - j] == 0 ? 1 : 0);
        rep(j, 0, n - k + 1) col_tr[j][i] = (0 == col_pre[i][j] and col_suf[i][n - k - j] == 0 ? 1 : 0);
    }
    
    vector<seg_tree<>> rows, cols;
    rep(i, 0, n - k + 1) {
        seg_tree<> row(row_tr[i]), col(col_tr[i]);
        rows.pb(row);
        cols.pb(col);
    }

    vi row_emp_tr(n), col_emp_tr(n);
    rep(i, 0, n) row_emp_tr[i] = (0 == row_pre[i][n] ? 1 : 0);
    rep(i, 0, n) col_emp_tr[i] = (0 == col_pre[i][n] ? 1 : 0);
    seg_tree<> row_emp(row_emp_tr), col_emp(col_emp_tr);

    int m = 0;
    rep(i, 0, n - k + 1) rep(j, 0, n - k + 1) {
        m = max(m, row_emp.query(0, i) + rows[j].query(i, i + k) + row_emp.query(i + k, n) + 
        col_emp.query(0, j) + cols[i].query(j, j + k) + col_emp.query(j + k, n));
    }

    // prv(row_emp_tr); cout << '\n';
    // prv(col_emp_tr); cout << '\n';
    cout << m << '\n';

    // prvv(row_tr); cout << '\n';
    // prvv(col_tr);
    // vector<seg_tree<>> rows, cols;
    // rep(i, 0, n) {
    //     seg_tree<> row(img[i]);
    //     rows.pb(row);
    // }
    // rep(i, 0, n) {
    //     vector<int> v_col(n);
    //     rep(j, 0, n) v_col[j] = img[j][i];
    //     seg_tree<> col(v_col);
    //     cols.pb(col);
    // }
    


    return 0;
}