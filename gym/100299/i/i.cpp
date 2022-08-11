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

int p[10042];
int pos[10042];
vector<ii> ans;
int nn;

void swp(int l, int r)
{
    int v1 = p[l];
    int v2 = p[r];
    pos[v1] = r;
    pos[v2] = l;
    p[l] = v2;
    p[r] = v1;
}

void change(int l, int r)
{
    int d = (r-l+1)/2;
    for (int i=0; i<d; i++)
        swp(l+i, l+i+d);
    ans.pb({l,r});
    //cout << "swp(" << l << "," << r << "): ";
    // for (int i=1; i<=nn; i++)
    //     cout << p[i] << " ";
    // cout << "\n";
}

void srt(int n)
{
    for (int a=1; a<=n; a++)
    {
        while (pos[a] != a)
        {
            int r = pos[a];
            int l = a;
            if ((r-l)%2 == 0)
                l++;
            change(l,r);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    TC(x)
    {
        int n;
        cin >> n;
        nn = n;
        for (int i=1; i<=n; i++)
        {
            cin >> p[i];
            pos[p[i]] = i;
        }
        ans.clear();
        srt(n);
        cout << ans.size() << "\n";
        for (auto a : ans)
            cout << a.st << " " << a.nd << "\n";
    }

    return 0;
}