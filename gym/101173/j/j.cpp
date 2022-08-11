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

int a[300042];
map<ii, vector<char>> dirs; // {u < v} --> dir == u -> v 
map<ii, vector<ll>> costs; // 

ll cnt(vector<char>& dirs, char d)
{
    ll res = 0;
    ll ds = 0;

    for (auto c : dirs)
    {
        if (c == d)
            ds++;
        else
        {
            if (ds > 0)
            {
                res++;
                ds--;
            }
        }
    }

    return res;
}

vector<char> clr(vector<char>& dirs, char d)
{
    // cout << "clr(" << d << "):\n";
    // cout << "\tBefore: ";
    // for (auto c : dirs) cout << c;
    // cout << "\n";

    vector<char> res;
    for (auto c : dirs)
    {
        if (c != d && (!res.empty() && res.back() == d))
        {
            res.pop_back();
            continue;
        }
        res.pb(c);
    }

    
    // cout << "\tAfter: ";
    // for (auto c : res) cout << c;
    // cout << "\n";
    return res;
}

ll solve(ii dest, vector<char>& dirs)
{
    ll cost = 0;

    ll c0, c1, c2, c3;
    c0 = costs[dest][0];
    c1 = costs[dest][1];
    c2 = costs[dest][2];
    c3 = costs[dest][3];

    ll cntUp = cnt(dirs, '0');
    ll cntDown = cnt(dirs, '1');

    bool debug = false;
    if (debug)
    {
        cout << "solve(" << dest.st << "," << dest.nd << "):";
        cout << "\tcosts(" << c0 << "," << c1 << "," << c2 << "," << c3 << ")\n";
        cout << "\tdirs: ";
        for (auto c : dirs)
            cout << c;
        cout << "\n"; 
        cout << "\tcnts(" << cntUp << "," << cntDown << ")\n";
    }

    if ((c0 != -1 && c1 != -1 && c2 >= c0 + c1) || cntUp == 0)
        c2 = -1;
    if ((c0 != -1 && c1 != -1 && c3 >= c0 + c1) || cntDown == 0)
        c3 = -1;
    
    if (c2 != -1 && c3 != -1)
    {
        if (c2 <= c3)
        {
            cost += cntUp*c2;
            dirs = clr(dirs, '0');
        }
        else
        {
            cost += cntDown*c3;
            dirs = clr(dirs, '1');
        }

        cntUp = cnt(dirs, '0');
        cntDown = cnt(dirs, '1');
    }


    if ((c0 != -1 && c1 != -1 && c2 >= c0 + c1) || cntUp == 0)
        c2 = -1;
    if ((c0 != -1 && c1 != -1 && c3 >= c0 + c1) || cntDown == 0)
        c3 = -1;

    if (c2 != -1)
    {
        cost += cntUp*c2;
        dirs = clr(dirs, '0');
    }
    if (c3 != -1)
    {
        cost += cntDown*c3;
        dirs = clr(dirs, '1');
    }

    for (auto c : dirs)
    {
        c == '0' ? cost += c0 : cost += c1;
    }

    if (debug)
    {
        cout << "\tcost: " << cost << "\n";
        cout << "-----------------\n";
    }

    return cost;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n,d;
    cin >> n >> d;
    for (int i=0; i<d; ++i)
    {
        cin >> a[i];
        if (i > 0)
        {
            int u = a[i-1];
            int v = a[i];
            bool swaped = (u > v);
            if (swaped)
                swap(u,v);
            dirs[{u,v}].pb(swaped ? '1' : '0');
        }
    }

    for (auto& dir : dirs)
    {
        costs[dir.st] = {-1,-1,-1,-1};
    }

    int m;
    cin >> m;
    for (int i=0; i<m; ++i)
    {
        int u, v;
        char d;
        ll c;
        cin >> u >> v >> d >> c;
        bool swaped = (u > v);
        if (swaped)
            swap(u,v);
        if (d == 'O')
        {
            if (!swaped)
            {
                if (costs[{u,v}][0] == -1 || costs[{u,v}][0] > c)
                    costs[{u,v}][0] = c;
            }
            else
            {
                if (costs[{u,v}][1] == -1 || costs[{u,v}][1] > c)
                    costs[{u,v}][1] = c;
            }
        }
        else
        {
            if (!swaped)
            {
                if (costs[{u,v}][0] == -1 || costs[{u,v}][0] > c)
                    costs[{u,v}][0] = c;
                if (costs[{u,v}][2] == -1 || costs[{u,v}][2] > c)
                    costs[{u,v}][2] = c;

            }
            else
            {
                if (costs[{u,v}][1] == -1 || costs[{u,v}][1] > c)
                    costs[{u,v}][1] = c;
                if (costs[{u,v}][3] == -1 || costs[{u,v}][3] > c)
                    costs[{u,v}][3] = c;
            }
        }
    }

    cout << std::accumulate(dirs.begin(), dirs.end(), 0LL, [](ll sum, auto& dir){ return sum + solve(dir.st, dir.nd); }) << "\n";

    return 0;
}