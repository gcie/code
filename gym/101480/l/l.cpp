#pragma gcc optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb              push_back
#define st              first
#define nd              second 
#define all(x)          (x).begin(), (x).end()
#define sci(x)          ll x;       cin >> x;
#define scii(x, y)      ll x, y;    cin >> x >> y;
#define sciii(x, y, z)  ll x, y, z; cin >> x >> y >> z;
#define TC(x)           sci(x); while(x --)
#define rep(i, x, y)    for (__typeof(x) i = x; i < y; i ++)
#define scvi(v, n)      vector<ll> v(n); rep(i, 0, n) cin >> v[i];
#define scvll(v, n)     vector<long long> v(n); rep(i, 0, n) cin >> v[i];
#define SZ(x)           ((ll)(x).size())
#define er_dup(x)       sort(all(x)); (x).resize(distance((x).begin(), unique(all(x))));
#define prv(v)          for(auto& x: v) cout << x << ' '; cout << '\n';
#define prvv(v)         for(auto& w: v) { for(auto& x: w) cout << x << ' '; cout << '\n'; }
using namespace std;

typedef long long       ll;
typedef pair<ll, ll>  ii;
typedef vector<ll>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

using namespace std;

ll n, m;
ii start;
char tab[542][542];
bool ok[542][542];
vector<ii> difs = {{0,1}, {0,-1}, {-1,0}, {1,0}};

bool isField(ii f)
{
    return 0 <= f.st && f.st < 5*n && 0 <= f.nd && f.nd < 5*m;
}

void bfs()
{
    queue<ii> q;
    q.push(start);
    ok[start.st][start.nd] = 1;
    while (!q.empty())
    {
        auto act = q.front();
        q.pop();
        for (auto dif : difs)
        {
            ii bb = act;
            bb.st += dif.st;
            bb.nd += dif.nd;
            if (!isField(bb))
                continue;
            if (ok[bb.st][bb.nd])
                continue;
            if (tab[bb.st][bb.nd] == '#')
                continue;
            ok[bb.st][bb.nd] = true;
            q.push(bb);
        }
    }
}

ii change(ll x, ll y)
{
    if (isField({x,y}))
        return {x,y};
    ll xorg = x - 2*n;
    ll yorg = y - 2*m;
    ll xc = (x%n + n)%n;
    ll yc = (y%m + m)%m;
    ll mltx = (xorg - xc) / n;
    ll mlty = (yorg - yc) / m;

    if (abs(mltx) >= abs(mlty) && mltx != 0)
    {
        mltx = 2 * mltx / abs(mltx);
    }
    else if (mltx != 0)
    {
        mltx /= abs(mltx);
    }
    if (abs(mlty) >= abs(mltx) && mlty != 0)
    {
        mlty = 2 * mlty / abs(mlty);
    }
    else if (mlty != 0)
    {
        mlty /= abs(mlty);
    }

    //cout << "Cen: " << xc << " " << yc << "\n";

    return {n*(mltx+2) + xc, m*(mlty+2) + yc};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> n >> m;
    start = {2*n, 2*m};
    for (ll i=0; i<n; i++)
    {
        for (ll j=0; j<m; j++)
        {
            cin >> tab[i][j];
            for (ll i1=0; i1<5; i1++)
            {
                for (ll j1=0; j1<5; j1++)
                {
                    tab[i+i1*n][j+j1*m] = tab[i][j];
                }
            }
        }
    }

    bfs();
    ll q;
    cin >> q;
    while (q--)
    {
        ll x,y;
        cin >> x >> y;
        x += 2*n; y += 2*m;
        //cout << "Org: " << x << " " << y << "\n";
        tie(x,y) = change(x,y);
        //cout << "Changed: " << x << " " << y << "\n";
        cout << (ok[x][y] ? "yes" : "no") << "\n"; 
    }

    return 0;
}