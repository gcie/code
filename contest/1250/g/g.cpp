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
typedef pair<ll,ll> pll;

using namespace std;

int n; ll k;
ll a[100042];
ll b[100042];
ll m[100042];
ll dp[100042];
vi restets;

void cntdp()
{
    if (a[0] >= k)
    {
        dp[0] = -1;
    }
    else
    {
        dp[0] = 0;
    }
    
    ll sum = a[0];
    for (int i=1; i<n; i++)
    {
        if (a[i]-a[i-1] >= k || dp[i-1] == -1)
        {
            dp[i] = -1;
        }
        else
        {
            dp[i] = dp[i-1];
            sum += a[i]-a[i-1];
            if (sum >= k)
            {
                dp[i]++;
                sum = a[i]-a[i-1];
                restets.pb(i-1);
            }
        }
    }
}

// const int N = 262144;  // limit for array size
// ll t[2 * N];

// void build() {  // build the tree
//   for (int i=0; i<N; i++)
//     t[i+N] = dp[i];
//   for (int i = N - 1; i > 0; --i)
//     t[i] = min(t[i<<1], t[i<<1|1]);
// }

// void modify(int p, int value) {  // set value at position p
//   for (t[p += N] = value; p > 1; p >>= 1) 
//     t[p>>1] = min(t[p] , t[p^1]);
// }

// ll query(int l, int r) {  // sum on interval [l, r)
//   ll res = 0;
//   for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
//     if (l&1) res = min(res, t[l++]);
//     if (r&1) res = min(t[--r], res);
//   }
//   return res;
// }

ll win[100042];
int pp[100042];

void solve()
{
    // build();
    for (int i=0; i<n; i++)
    {
        //cout << i << " " << dp[i] << "\n";

        if (a[i] >= b[i] || b[i] < k)
        {
            win[i] = -1;
            continue;
        }
        ll m1 = a[i] - k + 1;
        ll m2 = b[i] - k;
        auto pIt = lower_bound(m, m+i, m1);
        auto qIt = upper_bound(m, m+i, m2);
        int p = distance(m, pIt);
        int q = distance(m, qIt);
        if (p < q)
        {
            // win[i] = query(p, q) + 1;
            win[i] = dp[p] + 1;
            pp[i] = p;
            // cout << "ab: " << a[i] << " " << b[i] << "\n";
            // cout << "win: " << p << " " << q << " " << m1 << " " << m2 << "\n";
        }
        else
        {
            win[i] = -1;
        }
    }
}

void write()
{
    ll ans = 2e18;
    ll best = -1;
    for (int i=0; i<n; i++)
        if (win[i] != -1)
        {
            ans = min(ans, win[i]);
            best = i;
        }
    if (best == -1)
    {
        cout << -1 << "\n";
        return;
    }
    cout << ans << "\n";
    for (int r : restets)
    {
        if (r >= best)
            break;
        cout << r << " ";
    }
    cout << pp[best] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    TC(t)
    {
        //cout << "TEST\n";
        cin >> n >> k;
        for (int i=0; i<n; i++)
            cin >> a[i];
        for (int i=0; i<n; i++)
            cin >> b[i];
        for (int i=1; i<n; i++)
            a[i] += a[i-1];
        for (int i=1; i<n; i++)
            b[i] += b[i-1];
        
        if (a[n-1] < k && b[n-1] >= k)
        {
            cout << 0 << "\n";
            continue;
        }

        // cout << "as: ";   
        // for (int i=0; i<n; i++)
        // {
        //     cout << a[i] << " ";
        // }
        // cout << "\n";
        // cout << "bs: ";   
        // for (int i=0; i<n; i++)
        // {
        //     cout << b[i] << " ";
        // }
        // cout << "\n";
        // cout << "mins: ";   
        for (int i=0; i<n; i++)
        {
            m[i] = min(a[i], b[i]);
            //cout << m[i] << " ";
        }
        //cout << "\n";

        cntdp();
        solve();
        write();
    }

    return 0;
}