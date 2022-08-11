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
typedef unsigned long long ull;

using namespace std;

vector<int> get_pos(string s, int a, int b, char c) {
    vi res = {};
    rep(i, a, b) if(s[i] == c) res.push_back(i - a);
    return res;
}

pair<int, vi> check(vector<vi> &p, int a, int k, int n) {
    vector<int> bs;
    rep(i, 0, k) {
        if(p[a][i] == n) {
            bs.push_back(i);
        }
    }
    // cout << "bs: "; prv(bs);
    if(bs.empty()) return {0, {}};
    int b0 = bs[0];
    vi as = {};
    rep(i, 0, k) {
        if(p[i][b0] == n) as.push_back(i);
    }
    // cout << "as: "; prv(as);
    rep(i, 1, ((int)bs.size())) {
        int b = bs[i];
        vi as2 = {};
        rep(j, 0, k) if(p[j][b] == n) as2.push_back(j);
        if(as2 != as) return {0, {}};
    }
    if(as.size() != bs.size()) return {0, {}};
    for(int i = 0; i < ((int)as.size()); i++) {
        int a = as[i];
        vi bs2 = {};
        rep(j, 0, k) if(p[a][j] == n) bs2.push_back(j);
        if(bs2 != bs) return {0, {}};
    }
    // cout << "COOL RETURN\n";
    return {((int)as.size()), as};
}

ull fact(int n) {
    if(n == 1) return 1;
    else return ((ull)n) * fact(n - 1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int k;
    while(cin >> k) {
        string A, B; cin >> A >> B;
        int n = ((int)A.size());
        vector<vi> perm(k, vi(k));
        for(int j = 0; j < n; j += k) {
            for(int i = 0; i < k; i++) {
                auto bpos = get_pos(B, j, j+k, A[j+i]);
                for(int &x : bpos) {
                    perm[i][x] += 1;
                }
            }
        }

        // prvv(perm);

        vector<bool> checked(k);
        unsigned long long res = 1;
        for(int i = 0; i < k; i++) {
            if(checked[i]) continue;
            auto q = check(perm, i, k, n/k);
            if(q.first == 0) {
                res = 0;
                break;
            }
            res *= fact(q.first);
            for(auto &x : q.second) {
                checked[x] = true;
            }
        }
        cout << res << '\n';
    }

    return 0;
}