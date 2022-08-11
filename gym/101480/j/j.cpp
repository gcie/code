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
const ll mod = 100000001467LL;

vector<ii> nbh[3042];
vector<ii> edges;

int p[4542][3042];
int s[4542][3042];
int n,m;
int phase = 1;
set<int> bridges;
int currentDel = 1e6;
ll has[3042];

int ff(int ph, int i)
{
    if (p[ph][i] == i)
        return i;
    return p[ph][i] = ff(ph, p[ph][i]);
}

void uu(int v, int u)
{
    u = ff(phase, u);
    v = ff(phase, v);
    if (u == v)
        return;
    if (s[phase][u] > s[phase][v])
    {
        s[phase][u] += s[phase][v];
        p[phase][v] = u;
    }
    else
    {
        s[phase][v] += s[phase][u];
        p[phase][u] = v;
    }
}

void unionFind()
{
    //cout << "UF phase " << phase << "\n";
    for (int i=0; i<n; i++)
    {
        p[phase][i] = i;
        s[phase][i] = 1;
    }
    for (int i=0; i<m; i++)
    {
        if (bridges.find(i) == bridges.end())// && ff(phase-1, edges[i].st) == ff(phase-1, edges[i].nd))
        {
            uu(edges[i].st, edges[i].nd);
            //cout << "uu(" << edges[i].st+1 << "," << edges[i].nd+1 << ")\n";
        }
    }
    phase++;
}

vector<bool> visited;
vector<int> tin, low;
int timer;

void IS_BRIDGE(int v, int u, int i)
{
    bridges.insert(i);
}

void dfs(int v, int p = -1) 
{
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (auto to : nbh[v]) 
    {
        if (to.st == p) 
            continue;
        if (to.nd == currentDel)
            continue;

        if (visited[to.st])
        {
            low[v] = min(low[v], tin[to.st]);
        }
        else 
        {
            dfs(to.st, v);
            low[v] = min(low[v], low[to.st]);
            if (low[to.st] > tin[v])
                IS_BRIDGE(v, to.st, to.nd);
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

void cntHash()
{
    for (int i=0; i<n; i++)
    {
        for (int j=1; j<phase; j++)
        {
            has[i] = (has[i]*37 + ff(j, i)*17)%mod;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> n >> m;
    for (int i=0; i<m; i++)
    {
        int u,v;
        cin >> u >> v;
        u--; v--;

        edges.pb({u,v});
        nbh[u].pb({v,i});
        nbh[v].pb({u,i});
    }

    for (int i=0; i<n; i++)
    {
        p[0][i] = 0;
    }

    unionFind();
    find_bridges();
    unionFind();

    for (int e = 0; e < m; e++)
    {
        currentDel = e;
        bridges.clear();
        bridges.insert(e);
        find_bridges();
        // cout << "Phase: " << phase << "\n";
        // cout << "With del (" << edges[e].st+1 << "," << edges[e].nd+1 << ") bridges: ";
        // for (int i : bridges)
        //     cout << "(" << edges[i].st+1 << "," << edges[i].nd+1 << ") ";
        // cout << "\n";
        unionFind();
    }


    cntHash();
    int ans = 0;
    for (int i=0; i<n; i++)
        for (int j=i+1; j<n; j++)
        {
            bool ok = has[i] == has[j];
            // cout << "ff(" << i+1 << "," << j+1 << "): ";
            // for (int ph = 0; ph < phase; ph++)
            //     if (ff(ph, i) == ff(ph, j))
            //         cout << ph << " ";
                
            // cout << "\n";

            if (ok)
                ans += 3; //, cout << "(" << i+1 << "," << j+1 << "): " << 3 << "\n";
            else if (ff(2, i) == ff(2, j))
                ans += 2; //, cout << "(" << i+1 << "," << j+1 << "): " << 2 << "\n";
            else if (ff(1, i) == ff(1, j))
                ans += 1; //, cout << "(" << i+1 << "," << j+1 << "): " << 1 << "\n";;
        }

    cout << ans << "\n";


    return 0;
}