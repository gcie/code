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

const int duzo = 200007;
const ll mod = 1000003;
ll a, b, c;
int n;
ll sil[duzo], odw[duzo];
ll l[duzo], t[duzo];

ll pot(ll p, ll w) {
    if(w == 0) return 1ll;
    ll pom = pot(p, w / 2ll);
    pom *= pom;
    pom %= mod;
    if(w % 2ll == 0ll) {
        pom *= p;
        pom %= mod;
    }
    return pom;
}

void licz_sil() {
    sil[0] = odw[0] = 1ll;
    for(int i = 1; i <= 2 * n; ++i) {
        sil[i] = (ll(i)) * sil[i - 1];
        odw[i] = pot(sil[i], mod - 2);
    }
}

ll npok(ll nn, ll kk) {
    ll wyn = sil[nn] * odw[nn - kk];
    wyn %= mod;
    wyn *= odw[kk];
    wyn %= mod;
    return wyn;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> a >> b >> c;
    licz_sil();
    for(int i = 1; i <= n; ++i)
        cin >> l[i];
    for(int i = 1; i <= n; ++i)
        cin >> t[i];

    ll wyn = 0ll;
    for(int i = 2; i <= n; ++i) {
        ll nnn = npok(2 * n - i - 1, n - i + 1);
        wyn += a * nnn * t[i];
        wyn += b * nnn * l[i];
        wyn %= mod;
    }

    for(int i = 0; i <= n - 2; ++i) {
        wyn += pot(a + b, i) * c;
    }
    wyn %= mod;

    cout << wyn;

    return 0;
}