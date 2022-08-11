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

map<int, map<int,int>> nbh;
map<int,int> s;
map<int,int> p;
ll n;
vector<tuple<int,int,int>> ans;
vector<tuple<int,int,int>> not_used;
map<int,vector<tuple<int,int,int>>> to_use;
priority_queue<ii> comps;
map<int, vector<int>> leaves;

void clr()
{
    while (!comps.empty())
        comps.pop();
    leaves.clear();
    ans.clear();
    not_used.clear();
    to_use.clear();
    nbh.clear();
    s.clear();
    p.clear();
}

int ff(int a)
{
    if (p[a] == a)
        return a;
    return p[a] = ff(p[a]);
}

void uu(int a, int b, int i)
{
    int pa = ff(a);
    int pb = ff(b);
    if (pa != pb)
    {
        nbh[a][b] = i;
        nbh[b][a] = i;
        if (s[pa] > s[pb])
        {
            s[pa] += s[pb];
            p[pb] = pa;
        }
        else
        {
            s[pb] += s[pa];
            p[pa] = pb;
        }
    }
    else
    {
        not_used.emplace_back(i, a, b);
    }
}

void uu2(int a, int b)
{
    p[b] = a;
    for (auto e : to_use[b])
        to_use[a].pb(e);
}

void uu3(int a, int b)
{
    for (int l : leaves[b])
        leaves[a].pb(l);
    if (nbh[b].size() == 1)
        leaves[a].pb(b);
}

void rd(int i)
{
    int a,b;
    cin >> a >> b;
    if (s.find(a) == s.end())
        s[a] = 1;
    if (s.find(b) == s.end())
        s[b] = 1;
    if (p.find(a) == p.end())
        p[a] = a;
    if (p.find(b) == p.end())
        p[b] = b;

    uu(a,b, i);
}

void solve()
{
    // build comps
    // for (auto e : not_used)
    //     to_use[ff(get<1>(e))].push_back(e);

    // for (auto aa : p)
    //     if (aa.first == aa.second)
    //         comps.push({to_use[aa.first].size(), aa.first});


    // while (comps.size() > 1 && comps.top().first > 0)
    // {
    //     auto pa = comps.top();
    //     comps.pop();
    //     auto pb = comps.top();
    //     comps.pop();

    //     int w, a, b;
    //     tie(w,a,b) = to_use[pa.second].back();
    //     to_use[pa.second].pop_back();

    //     ans.emplace_back(w, a, pb.second);
    //     nbh[a][pb.second] = w;
    //     nbh[pb.second][a] = w;

    //     uu2(pa.second,pb.second);
    //     pa.first = to_use[pa.second].size();
    //     comps.push(pa);
    // }

    for (auto aa : p)
    {
        if (aa.first != aa.second && nbh[aa.first].size() == 1)
            leaves[ff(aa.first)].pb(aa.first);
    }

    // while (!comps.empty())
    //     comps.pop();

    // for (auto aa : p)
    //     if (aa.first == aa.second)
    //         comps.push({leaves[aa.first].size(), aa.first});

    // for (auto aa : p)
    // {
    //     int i = aa.first;
    //     cout << i << ": p[i]: " << p[i] << ", ff(i): " << ff(i) << ", nbh[i]:";
    //     for (auto e : nbh[i])
    //         cout << "(" << e.first << "," << e.second << ") ";
    //     cout << "\n";
    // }

    int par = ff(p.begin()->first);
    for (auto aa : p)
    {
        int p2 = ff(aa.first);
        if (p2 != par)
        {
            int a = leaves[p2].back();
            int w = nbh[a].begin()->second;
            ans.emplace_back(w, a, par);
            p[p2] = par;
        }
    }

    // while (comps.size() > 1)
    // {
    //     auto pa = comps.top();
    //     comps.pop();
    //     auto pb = comps.top();
    //     comps.pop();

    //     int a;
    //     if (leaves[pa.second].empty())
    //     {
    //         while (1);
    //     }
    //     a = leaves[pa.second].back();
    //     leaves[pa.second].pop_back();
    //     int b, w;
    //     tie(b, w) = *nbh[a].begin();
    //     nbh[a].clear();
    //     nbh[b].erase(a);

    //     ans.emplace_back(w, a, pb.second);
    //     nbh[b][pb.second] = w;
    //     nbh[pb.second][b] = w;

    //     uu3(pa.second,pb.second);
    //     pa.first = leaves[pa.second].size();
    //     comps.push(pa);
    // }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    TC(t)
    {
        clr();
        cin >> n;
        for (int i=1; i<=n; i++)
        {
            rd(i);
        }
        solve();
        cout << ans.size() << "\n";
        for (auto e : ans)
            cout << get<0>(e) << " " << get<1>(e) << " " << get<2>(e) << "\n";
    }


    return 0;
}