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
string b[10];
vector<pair<ii,int>> poles;
set<int> white;
set<int> black;
vector<int> nbh[142];

void isEdge(int i, int j)
{
    if (abs(poles[i].st.st - poles[j].st.st) != 2 || abs(poles[i].st.nd - poles[j].st.nd) != 2)
        return;

    ii mid = {(poles[i].st.st + poles[j].st.st) / 2, (poles[i].st.nd + poles[j].st.nd) / 2};
    if (b[mid.st][mid.nd] != 'B')
        return;
    if (b[poles[i].st.st][poles[i].st.nd] != 'B')
        nbh[j].pb(i);
    if (b[poles[j].st.st][poles[j].st.nd] != 'B')
        nbh[i].pb(j);
}

int ans = 0;
bool was[142][142];

void dfs(int v, int pocz, int cnt = 0)
{
    ans = max(ans, cnt);

    for (int w : nbh[v])
    {
        if (black.find(w) != black.end())
            continue;
        if (w != pocz && white.find(w) != white.end())
            continue;
        if (was[min(v,w)][max(v,w)])
            continue;
        was[min(v,w)][max(v,w)] = 1;
        dfs(w, pocz, cnt+1);
        was[min(v,w)][max(v,w)] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int id = 0;
    for (int i=0; i<10; i++)
        for (int j=0; j<10; j++)
            if ((i+j)%2 == 1)
                poles.pb({{i,j},id}), id++; //, cout << id-1 << " = (" << i << "," << j << ")\n";

    TC(x)
    {
        for (int i=0; i<10; i++)
            cin >> b[i];

        white.clear();
        black.clear();
        for (auto p : poles)
        {
            if (b[p.st.st][p.st.nd] == 'W')
                white.insert(p.nd);
            else if (b[p.st.st][p.st.nd] == 'B')
                black.insert(p.nd);
        }

        for (int i=0; i<id; i++)
            nbh[i].clear();
        for (int i=0; i<id; i++)
            for (int j=i+1; j<id; j++)
                 isEdge(i,j);

        ans = 0;
        for (auto p : white)
        {
            for (int i=0; i<id; i++)
                for (int j=i+1; j<id; j++)
                {
                    was[i][j] = was[j][i] = 0;
                }
            dfs(p,p);
        }
        cout << ans << "\n";

        // for (int i=0; i<id; i++)
        // {
        //     if (nbh[i].empty())
        //         continue;
        //     cout << "nbh[" << i << "]: ";
        //     for (auto j : nbh[i])
        //         cout << j << " ";
        //     cout << "\n";
        // }
        // cout << "\n\n";
    }

    return 0;
}