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

const ld pi = 3.141592653589793;
const ld sq3 = sqrt(3.0);

char shp[25];

inline ld sqr(ld x) {
    return x * x;
}

inline ld pita(ld x, ld y) {
    return sqrt(sqr(x) + sqr(y));
}

inline ld revpita(ld x, ld y) {
    return sqrt(sqr(x) - sqr(y));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, l = -1, r = -1;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> shp[i];
        if(l == -1 && shp[i] != 'T') l = i;
    }
    for(int i = n; i >= 1; --i) {
        if(r == -1 && shp[i] != 'T') r = i;
    }

    if(r == -1) {
        cout << setprecision(15) << fixed << (ld)(2 * n + 1);
        return 0;
    }

    ld sum = n + r - l - 1;
    if(shp[1] == 'T' || shp[1] == 'S') sum += 0.5;
    if(shp[n] == 'T' || shp[n] == 'S') sum += 0.5;
    if(shp[l] == 'S') {
        sum += 1.5;
        if(l > 1)
            sum += pita((ld)l - 1.5, 1.0 - sq3 / 2.0);
    }
    else {
        if(l == 1) sum += pi / 2.0;
        else {
            ld k = l - 1;
            sum += 1.0;
            ld pom0 = (sq3 - 1.0) / 2.0;
            ld pom1 = pita(k, pom0);
            sum += revpita(pom1, 0.5);
            ld alpha = asin(0.5 / pom1);
            ld beta = atan(pom0 / k);
            sum += (alpha - beta) / 2.0;
        }
    }

    if(shp[r] == 'S') {
        sum += 1.5;
        if(r < n)
            sum += pita((ld)(n - r) - 0.5, 1.0 - sq3 / 2.0);
    }
    else {
        if(r == n) sum += pi / 2.0;
        else {
            ld k = n - r;
            sum += 1.0;
            ld pom0 = (sq3 - 1.0) / 2.0;
            ld pom1 = pita(k, pom0);
            sum += revpita(pom1, 0.5);
            ld alpha = asin(0.5 / pom1);
            ld beta = atan(pom0 / k);
            sum += (alpha - beta) / 2.0;
        }
    }


    cout << setprecision(15) << fixed << sum;
    return 0;
}