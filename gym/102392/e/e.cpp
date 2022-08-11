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

ll n,k;
ll lc, pc, lm, pm;
ll t, d;
ll a[100042];
ll dp[100042];
ll dpc[100042];
ll dpm[100042];
ll leqc[100042];
ll leqm[100042];

ll sum(int p, int q) // sum of intr [p,q) index form 0
{
    return dp[q] - dp[p];
}

ll solve(ll dr)
{
    ll pas = (k-1)*dr;
    ll mot = n - pas - dr;

    ll neededAge = leqc[dr] + (mot > 0 ? leqm[dr + mot] - leqm[dr] : 0LL);
    ll ageToSpare = dpc[dr] + (mot > 0 ? dpm[dr + mot] - dpm[dr] : 0LL) + dp[n] - dp[max(dr,dr + mot)];

    //cout << "Dr: " << dr << ", mot: " << mot << ", pas: " << pas << ", neededAge: " << neededAge << ", ageToSpare: " << ageToSpare << "\n";

    if (dr > 0 && a[dr-1] + d < lc)
        return -1;
    if (pas + dr < n && a[dr + mot - 1] + d < lm)
        return -1;

    // ll neededAge = leqc[dr] + leqm[dr + mot] - leqm[dr];
    // ll ageToSpare = dpc[dr] + dpm[dr + mot] - dpm[dr] + dp[n] - dp[dr + mot];
    if (neededAge > ageToSpare)
        return -1;

    ll cost = dr*pc + (mot > 0 ? mot*pm : 0LL) + t*neededAge;
    //cout << "Cost: " << cost << "\n";
    return cost;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> n >> k;
    cin >> lc >> pc >> lm >> pm;
    cin >> t >> d;
    for (int i=0; i<n; i++)
        cin >> a[i];

    sort(a, a+n);
    reverse(a, a+n);

    dp[0] = dpc[0] = dpm[0] = leqc[0] = leqm[0] = 0;
    for (int i=1; i<=n; i++)
    {
        dp[i] = dp[i-1] + max(0LL, min(a[i-1]-1, d));
        dpc[i] = dpc[i-1] + max(0LL, min(a[i-1]-lc, d));
        dpm[i] = dpm[i-1] + max(0LL, min(a[i-1]-lm, d));
        leqc[i] = leqc[i-1] + max(0LL, lc - a[i-1]);
        leqm[i] = leqm[i-1] + max(0LL, lm - a[i-1]);
    }

    ll ans = -1;
    for (int dr=0; dr<=n; dr++)
    {
        ll ans2 = solve(dr);
        if (ans2 != -1 && (ans == -1 || ans2 < ans))
            ans = ans2;
    }
    cout << ans << "\n";

    return 0;
}