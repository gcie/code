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

int n, s1, s2;
ll dp[2][512][512];
ll x[512];
ll y[512];
ll r[512];
ll t[512];

void up1(int i, int j, int k)
{
    int j1 = j + x[i];
    int k1 = k;
    if (j1 > s1)
    {
        k1 += j1 - s1;
        j1 = s1;
    }
    if (k1 > s2)
    {
        k1 = s2;
    }
    int i0 = (i-1)%2;
    int i1 = i%2;

    if (dp[i0][j][k] == -1)
        return;

    ll tt = t[i] + dp[i0][j][k];
    if (dp[i1][j1][k1] == -1 || (tt < dp[i1][j1][k1]))
        dp[i1][j1][k1] = tt;
}

void up2(int i, int j, int k)
{
    int j2 = j;
    int k2 = k + y[i];
    if (k2 > s2)
    {
        k2 = s2;
    }
    int i0 = (i-1)%2;
    int i2 = i%2;

    if (dp[i0][j][k] == -1)
        return;

    ll tt = r[i] + dp[i0][j][k];
    if (dp[i2][j2][k2] == -1 || (tt < dp[i2][j2][k2]))
        dp[i2][j2][k2] = tt;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    vector<tuple<ll,ll,ll,ll>> vv;
    cin >> n >> s1 >> s2;
    for (int i=1; i<=n; i++)
    {
        ll xx, tt, yy, rr;
        cin >> xx >> tt >> yy >> rr;
        vv.emplace_back(xx,tt,yy,rr);
    }
    sort(all(vv));
    for (int i=1; i<=n; i++)
    {
        x[i] = get<0>(vv[i-1]);
        t[i] = get<1>(vv[i-1]);
        y[i] = get<2>(vv[i-1]);
        r[i] = get<3>(vv[i-1]);
    }

    for (int i = 0; i<512; i++)
        for (int j = 0; j<512; j++)
            dp[0][i][j] = dp[1][i][j] = -1;

    dp[0][0][0] = 0;
    dp[1][0][0] = 0;
    for (int i=1; i<=n; i++)
    {
        for (int j=0; j<=s1; j++)
        {
            for (int k=0; k<=s2; k++)
            {
                if (j < s1)
                    up1(i,j,k);
                up2(i,j,k);
            }
        }
        for (int j = 0; j<512; j++)
            for (int k = 0; k<512; k++)
                dp[(i-1)%2][j][k] = dp[i%2][j][k];
    }
    cout << dp[n%2][s1][s2] << "\n";

    return 0;
}