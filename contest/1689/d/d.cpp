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


void solve() {
    scii(n, m);
    int summin = 1e9, summax = -1e9, difmin = 1e9, difmax = -1e9;
    ii a, b, c, d;
    rep(i, 0, n) {
        string s;
        cin >> s;
        rep(j, 0, m) {
            if(s[j] == 'B') {
                if(i + j < summin) {
                    a = {i, j};
                    summin = i + j;
                }
                if(i + j > summax) {
                    b = {i, j};
                    summax = i + j;
                }
                if(i - j < difmin) {
                    c = {i, j};
                    difmin = i - j;
                }
                if(i - j > difmax) {
                    d = {i, j};
                    difmax = i - j;
                }
            }
        }
    }

    // cout << "a: " << a.st << ", " << a.nd << " b: " << b.st << ", " << b.nd << " c: " << c.st << ", " << c.nd << " d: " << d.st << ", " << d.nd << endl;
    // cout << "difmin: " << difmin << " - " << difmax << " sum: " << summin << " - " << summax << endl;

    ii q;
    int best_dist = 1e9;

    rep(i, 0, n) rep(j, 0, m) {
        // if(summin <= i + j && i + j <= summax && difmin <= i - j && i - j <= difmax) {
            int dist = max(max(abs(i - a.st) + abs(j - a.nd),
                    abs(i - b.st) + abs(j - b.nd)),
                    max(abs(i - c.st) + abs(j - c.nd),
                    abs(i - d.st) + abs(j - d.nd)));
            if(dist < best_dist) {
                best_dist = dist;
                q = {i, j};
            }
        // }
    }

    cout << q.st + 1 << ' ' << q.nd + 1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    TC solve();
    return 0;
}
