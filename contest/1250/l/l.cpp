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

long long a,b,c;
long long g[3];

long long sol1()
{
    g[0] = a;
    g[1] = c/2;
    g[2] = c - g[1];
    long long bb = b;
    while (bb)
    {
        int pos = 0;
        for (int i=1; i<3; i++)
            if (g[i] < g[pos])
                pos = i;

        g[pos]++;
        bb--;
    }
    return max({g[0], g[1], g[2]});
}
long long sol2()
{
    g[0] = c;
    g[1] = a/2;
    g[2] = a - g[1];
    long long bb = b;
    while (bb)
    {
        int pos = 0;
        for (int i=1; i<3; i++)
            if (g[i] < g[pos])
                pos = i;

        g[pos]++;
        bb--;
    }
    return max({g[0], g[1], g[2]});
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    TC(t)
    {
        cin >> a >> b >> c;
        cout << min(sol1(), sol2()) << "\n";
    }

    return 0;
}