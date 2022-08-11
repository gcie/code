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
#define prv(v)          for(auto& x: v) //cout << x << ' '; //cout << '\n';
#define prvv(v)         for(auto& w: v) { for(auto& x: w) //cout << x << ' '; //cout << '\n'; }
using namespace std;

typedef long long       ll;
typedef pair<int, int>  ii;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

using namespace std;

struct kw
{
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    int zmin;
    int zmax;
};

vector<kw> xkw, ykw, zkw;
kw x, y, z;

kw rzutx(vector<kw>& v)
{
    kw r;
    r.xmin = 1000000000;
    r.xmax = -1000000000;
    r.ymin = -1000000000;
    r.ymax = 1000000000;
    r.zmin = -1000000000;
    r.zmax = 1000000000;

    for (auto k : v)
    {
        r.xmin = min(r.xmin, k.xmin);
        r.xmax = max(r.xmax, k.xmax);
        
        r.ymin = max(r.ymin, k.ymin);
        r.ymax = min(r.ymax, k.ymax);
        
        r.zmin = max(r.zmin, k.zmin);
        r.zmax = min(r.zmax, k.zmax);
    }

    return r;
}
kw rzuty(vector<kw>& v)
{
    kw r;
    r.xmin = -1000000000;
    r.xmax = 1000000000;
    r.ymin = 1000000000;
    r.ymax = -1000000000;
    r.zmin = -1000000000;
    r.zmax = 1000000000;

    for (auto k : v)
    {
        r.xmin = max(r.xmin, k.xmin);
        r.xmax = min(r.xmax, k.xmax);
        
        r.ymin = min(r.ymin, k.ymin);
        r.ymax = max(r.ymax, k.ymax);
        
        r.zmin = max(r.zmin, k.zmin);
        r.zmax = min(r.zmax, k.zmax);
    }

    return r;
}
kw rzutz(vector<kw>& v)
{
    kw r;
    r.xmin = -1000000000;
    r.xmax = 1000000000;
    r.ymin = -1000000000;
    r.ymax = 1000000000;
    r.zmin = 1000000000;
    r.zmax = -1000000000;

    for (auto k : v)
    {
        r.xmin = max(r.xmin, k.xmin);
        r.xmax = min(r.xmax, k.xmax);
        
        r.ymin = max(r.ymin, k.ymin);
        r.ymax = min(r.ymax, k.ymax);
        
        r.zmin = min(r.zmin, k.zmin);
        r.zmax = max(r.zmax, k.zmax);
    }

    return r;
}

bool checkyz(kw y, kw z)
{
    if (y.ymin < z.ymin || y.ymax > z.ymax)
    {
        //cout << "F1\n";
        return false;
    }
    if (z.zmin < y.zmin || z.zmax > y.zmax)
    {
        //cout << "F2\n";
        return false;
    }

    int in1 = y.xmin < z.xmin && z.xmin < y.xmax;
    int in2 = y.xmin < z.xmax && z.xmax < y.xmax;
    
    //cout << "F3\n";
    return (in1 + in2 >= 1);
}
bool checkxy(kw x, kw y)
{
    if (x.xmin < y.xmin || x.xmax > y.xmax)
    {
        //cout << "F1\n";
        return false;
    }
    if (y.ymin < x.ymin || y.ymax > x.ymax)
    {
        //cout << "F2\n";
        return false;
    }

    int in1 = x.zmin < y.zmin && y.zmin < x.zmax;
    int in2 = x.zmin < y.zmax && y.zmax < x.zmax;
    
    //cout << "F3 " << in1 + in2 << "\n";
    return (in1 + in2 >= 1);
}
bool checkxz(kw x, kw z)
{
    if (x.xmin < z.xmin || x.xmax > z.xmax)
    {
        //cout << "F1\n";
        return false;
    }
    if (z.zmin < x.zmin || z.zmax > x.zmax)
    {
        //cout << "F2\n";
        return false;
    }

    int in1 = x.ymin < z.ymin && z.ymin < x.ymax;
    int in2 = x.ymin < z.ymax && z.ymax < x.ymax;
    
    //cout << "F3\n";
    return (in1 + in2 >= 1);
}

bool ch(kw x)
{
    if (x.xmin > x.xmax)
        return false;
    if (x.ymin > x.ymax)
        return false;
    if (x.zmin > x.zmax)
        return false;
}

bool solve()
{
    int ile_pustych = xkw.empty() + ykw.empty() + zkw.empty();
    if (ile_pustych > 1)
        return false;

    if (!xkw.empty())
    {
        if (ch(x) && all_of(ykw.begin(), ykw.end(), [&](auto ky){ return checkxy(x, ky);}) && all_of(zkw.begin(), zkw.end(), [&](auto kz){ return checkxz(x, kz);}))
            return true;
    }
    if (!ykw.empty())
    {
        if (ch(y) && all_of(xkw.begin(), xkw.end(), [&](auto kx){ return checkxy(kx, y);}) && all_of(zkw.begin(), zkw.end(), [&](auto kz){ return checkyz(y, kz);}))
            return true;
    }
    if (!zkw.empty())
    {
        if (ch(z) && all_of(xkw.begin(), xkw.end(), [&](auto kx){ return checkxz(kx, z);}) && all_of(ykw.begin(), ykw.end(), [&](auto ky){ return checkyz(ky, z);}))
            return true;
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    TC(ttt)
    {
        xkw.clear(), ykw.clear(), zkw.clear();
        int n;
        cin >> n;
        for (int i=0; i<n; i++)
        {
            kw k;
            cin >> k.xmin >> k.ymin >> k.zmin >> k.xmax >> k.ymax >> k.zmax;
            if (k.xmin > k.xmax)
                swap(k.xmin, k.xmax);
            if (k.ymin > k.ymax)
                swap(k.ymin, k.ymax);
            if (k.zmin > k.zmax)
                swap(k.zmin, k.zmax);

            if (k.xmin == k.xmax)
                xkw.pb(k);
            else if (k.ymin == k.ymax)
                ykw.pb(k);
            else zkw.pb(k);
        }

        x = rzutx(xkw);
        y = rzuty(ykw);
        z = rzutz(zkw);
        //cout << "x: " << x.xmin << " " << x.xmax << " " << x.ymin << " " << x.ymax << " " << x.zmin << " " << x.zmax << "\n";
        //cout << "y: " << y.xmin << " " << y.xmax << " " << y.ymin << " " << y.ymax << " " << y.zmin << " " << y.zmax << "\n";
        //cout << "z: " << z.xmin << " " << z.xmax << " " << z.ymin << " " << z.ymax << " " << z.zmin << " " << z.zmax << "\n";

        //cout << checkxy(x,y) << "\n";
        //cout << checkxz(x,z) << "\n";
        //cout << checkyz(y,z) << "\n";

        cout << (solve() ? "YES\n" : "NO\n");
    }

    return 0;
}