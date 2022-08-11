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
typedef pair<ll, int>  pll;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

using namespace std;

struct seg_tree {
    vector<pll> t;
    vector<ll> d;
    size_t n;
    size_t h;
    seg_tree(size_t _n) {
        n = _n;
        h = 18;
        t.resize(2 * n);
        d.resize(n);
        for(int i = 0; i < n; i++) t[i] = {-2e18, 0};
        for(int i = 0; i < n; i++) t[i + n] = {0, i};
        fill(d.begin(), d.end(), 0);
    }
    void apply(size_t p, ll value) {
        t[p] = {t[p].st + value, t[p].nd};
        if(p < n) d[p] += value;
    }
    void build(size_t p) {
        while (p > 1) {
            p >>= 1;
            auto x = max(t[p<<1], t[p<<1|1]); 
            t[p] = {x.st + d[p], x.nd};
        }
    }
    void push(size_t p) {
        for (int s = h; s > 0; --s) {
            int i = p >> s;
            if (d[i] != 0) {
                apply(i<<1, d[i]);
                apply(i<<1|1, d[i]);
                d[i] = 0;
            }
        }
    }
    void inc(size_t l, size_t r, ll value) {
        l += n, r += n;
        size_t l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) apply(l++, value);
            if (r&1) apply(--r, value);
        }
        build(l0);
        build(r0 - 1);
    }
    pll query(size_t l, size_t r) {
        l += n, r += n;
        push(l);
        push(r - 1);
        pll res = {-2e18, -1};
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = max(res, t[l++]);
            if (r&1) res = max(t[--r], res);
        }
        return res;
    }
};

struct project{
    int l, r, i;
    ll c;
    project(int _l, int _r, int _c, int _i): l(_l), r(_r), c(_c), i(_i) {};
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    sci(n); ll k; cin >> k;
    vector<project> ps;
    rep(i, 0, n) {
        scii(l, r); ll c; cin >> c;
        project p(l, r, c, i+1);
        ps.push_back(p);
    }
    sort(all(ps), [](project &p1, project &p2){ return p1.r < p2.r; });
    seg_tree t(262144);
    rep(i, 2, 262144) t.inc(i, 262144, k);
    ll sum = 0ll;
    ll best = 0ll;
    int bestl, bestr;
    rep(i, 0, n) {
        sum += ps[i].c;
        t.inc(ps[i].l+1, 262144, -ps[i].c);
        pll x = t.query(1, ps[i].r + 1);
        if(x.st + sum - k * ps[i].r > best) {
            best = x.st + sum - k * ps[i].r;
            bestl = x.nd;
            bestr = ps[i].r;
        }
        // cout << t.query(0, ps[i].r + 1) + sum - k * ps[i].r << " = " << t.query(0, ps[i].r + 1) << " + " << sum << " - " << k * ps[i].r << "\n";
        // for (int a=0; a<10; a++)
        //     cout << t.query(a, a+1) << " ";
        // cout << "\n";
    }
    cout << best;
    if(best > 0){
        cout << ' ' << bestl << ' ' << bestr << ' ';
        vi trg;
        for(project &p : ps)
            if(p.l >= bestl and p.r <= bestr)
                trg.push_back(p.i);
        
        cout << trg.size() << '\n';
        prv(trg);
    }

    return 0;
}