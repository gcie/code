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

struct kraw {
    int a, b, p;
};

inline bool mn(kraw& a, kraw& b) {
    return a.p < b.p;
}

const int duzo = 300007;
int n, m;

vector<kraw> kr;
vector<ii> pyt;
ii odp[duzo];

int st[duzo], vst[duzo];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int a, b, p;
        cin >> a >> b >> p;
        kraw pom;
        pom.a = min(a, b);
        pom.b = max(a, b);
        pom.p = p;
        kr.pb(pom);
        ++st[a]; ++st[b];
    }
    kr.pb({0, 0, duzo});
    sort(all(kr), mn);

    int q; cin >> q;
    for(int i = 1; i <= q; ++i) {
        int th;
        cin >> th;
        pyt.pb({th, i});
    }
    pyt.pb({duzo, 0});
    sort(all(pyt));

    int ilew = n, ilek = m;
    for(int i = 1; i <= n; ++i) {
        if(st[i] == 2) {
            --ilek;
            --ilew;
        }
    }

    int wskp = 0;
    for(int i = 0; i < m; ++i) {
        cerr << "usuwam " << i << endl;
        int a = kr[i].a;
        int b = kr[i].b;
        --st[a];
        --st[b];
        if(st[a] == 1 && st[b] == 1) {
            ++ilek;
        }
        else {
            if(st[a] >= 2 && st[b] >= 2) --ilek;
            if(st[a] == 2) {
                --ilek;
                --ilew;
            }
            else if(st[a] == 1) ++ilew;
            else if(st[a] == 0) --ilew;
            if(st[b] == 2) {
                --ilek;
                --ilew;
            }
            else if(st[b] == 1) ++ilew;
            else if(st[a] == 0) --ilew;
        }
        if(kr[i + 1].p > kr[i].p) {
            while(pyt[wskp].st <= kr[i + 1].p) {
                cerr << "odpowiadam " << wskp << endl;
                odp[pyt[wskp].nd] = {ilew, ilek};
                ++wskp;
            }
        }
    }


    for(int i = 1; i <= q; ++i) cout << odp[i].st << " " << odp[i].nd << "\n";

    return 0;
}