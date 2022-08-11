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

bool s1[101][101];
bool s2[101][101];

bool solMin[101][101][101];
bool solMax[101][101][101];

int sizeMin, sizeMax;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n,m,h;
    cin >> n >> m >> h;
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
        {
            char c;
            cin >> c;
            s1[i][j] = (c == '1');
        }
    // for (int i=0; i<n; i++)
    // {
    //     for (int j=0; j<m; j++)
    //     {
    //         cout << s1[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    for (int i=0; i<n; i++)
        for (int j=0; j<h; j++)
        {
            char c;
            cin >> c;
            s2[i][j] = (c == '1');
        }

    // for (int i=0; i<n; i++)
    // {
    //     for (int j=0; j<h; j++)
    //     {
    //         cout << s2[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // return 0;

    for (int i=0; i<n; i++)
    {
        vector<int> pos1;
        vector<int> pos2;
        for (int j=0; j<m; j++)
            if (s1[i][j])
                pos1.pb(j);

        for (int j=0; j<h; j++)
            if (s2[i][j])
                pos2.pb(j);

        if (((int)pos1.empty() + (int)pos2.empty()) == 1)
        {
            cout << -1 << "\n";
            return 0;
        }
        if (pos1.empty() && pos2.empty())
            continue;
            
        for (int j : pos1)
            for (int k : pos2)
                solMax[i][j][k] = 1;
        sizeMax += pos1.size()*pos2.size();

        
        int dif = abs((int)pos1.size() - (int)pos2.size());
        if (pos1.size() >= pos2.size())
        {
            for (int p = 0; p <= dif; p++)
            {
                solMin[i][pos1[p]][pos2[0]] = 1;
            }
            for (int p = 1; p < pos2.size(); p++)
            {
                solMin[i][pos1[p+dif]][pos2[p]] = 1;
            }
        }
        else
        {
            //cout << "ELSE! DIFF: " << dif << "\n";;
            for (int p = 0; p <= dif; p++)
            {
                solMin[i][pos1[0]][pos2[p]] = 1;
                //cout << "assigned" << pos1[0] << " " << pos2[p] << "\n"; 
            }
            for (int p = 1; p < pos1.size(); p++)
            {
                solMin[i][pos1[p]][pos2[p+dif]] = 1;
            }
        }
        sizeMin += max(pos1.size(), pos2.size());
    }
    
    cout << sizeMax << "\n";
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            for (int k=0; k<h; k++)
            {
                if (solMax[i][j][k])
                    cout << i << " " << j << " " << k << "\n";
            }
        }
    }
    cout << sizeMin << "\n";
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            for (int k=0; k<h; k++)
            {
                if (solMin[i][j][k])
                    cout << i << " " << j << " " << k << "\n";
            }
        }
    }

    return 0;
}