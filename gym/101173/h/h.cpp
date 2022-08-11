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

const int malo = 1007, duzo = 300007;
bool t[malo][malo];
int n, q;
int ile[malo][malo];

inline bool bounds(int x, int y) {
    if(x < 1 || x > n) return false;
    if(y < 1 || y > n) return false;
    return true;
}

inline int kwad(int r, int c, int rad) {
    rad /= 2;
    if(!bounds(r - rad, c - rad)) return 1;
    if(!bounds(r + rad, c + rad)) return 1;
    return ile[r + rad][c + rad] - ile[r + rad][c - rad - 1] - ile[r - rad - 1][c + rad] + ile[r - rad - 1][c - rad - 1];
}

inline int nrw(int i, int j) {
    return (i - 1) * n + j;
}

inline ii wsp(int nn) {
    return {(nn - 1) / n + 1, (nn - 1) % n + 1};
}

vector<ii> wir;
ii qst[duzo];
int ans[duzo];

int f[malo * malo], rr[malo * malo];
int fajnd(int x) {
    if(f[x] == x) return x;
    f[x] = fajnd(f[x]);
    return f[x];
}

int junion(int x, int y) {
    x = fajnd(x);
    y = fajnd(y);
    if(rr[x] < rr[y]) swap(x, y);
    f[y] = x;
    if(rr[x] == rr[y]) ++rr[x];
}

inline void init_jf() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int nn = nrw(i, j);
            f[nn] = nn;
            rr[nn] = 1;
        }
    }
}

bool som[malo * malo];
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            char c;
            cin >> c;
            if(c == '.') t[i][j] = true;
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            ile[i][j] = ile[i - 1][j] + ile[i][j - 1] - ile[i - 1][j - 1];
            if(!t[i][j]) ++ile[i][j];
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(t[i][j]) {
                int a = 1, b = 2 * n + 1;
                while(a + 1 < b) {
                    int sr = (a + b) / 2;
                    if(kwad(i, j, sr) == 0) a = sr;
                    else b = sr;
                }
                wir.pb({a, nrw(i, j)});
            }
        }
    }
    
    cin >> q;
    for(int i = 1; i <= q; ++i) {
        int ra, ca, rb, cb;
        cin >> ra >> ca >> rb >> cb;
        qst[i] = {nrw(ra, ca), nrw(rb, cb)};
    }
    init_jf();

    sort(wir.rbegin(), wir.rend());
    wir.pb({-1, 0});
    for(int i = 0, sss = SZ(wir); i < sss; ++i) {
        int ziom = wir[i].nd;
        auto ww = wsp(ziom);
        int rg = wir[i].st;
        som[ziom] = true;
        for(int l = 0; l < 4; ++l) {
            int nx = ww.st + dx[l];
            int ny = ww.nd + dy[l];
            if(!bounds(nx, ny)) continue;
            if(!som[nrw(nx, ny)]) continue;
            junion(ziom, nrw(nx, ny));
        }
        if(i < sss - 1 && wir[i + 1].st != wir[i].st) {
            for(int j = 1; j <= q; ++j) {
                if(ans[j] == 0) {
                    if(fajnd(qst[j].st) == fajnd(qst[j].nd)) ans[j] = rg;
                }
            }
        }
    }

    for(int i = 1; i <= q; ++i) cout << ans[i] << "\n";

    return 0;
}