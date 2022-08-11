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

string s;
vi ans;

void check(int i)
{
    int score = (i > 0 ? s[i] != s[i-1] : 1) + (s[i+1] != s[i]) + (s[i+2] != s[i+1]);
    string cc = "";
    if (i > 0)
        cc += s[i-1];
    else
    {
        cc += 'a';
    }
    cc += s[i];
    cc += s[i+1];
    cc += s[i+2];
    //cout << "For i = " << i << "\n";
    //cout << "org: " << cc << " : " << score << "\n";
    
    cc[1] = '1' - (cc[1] == '1');
    cc[2] = '1' - (cc[2] == '1');
    int score0 = (cc[0] != cc[1]) + (cc[1] != cc[2]) + (cc[2] != cc[3]);
    //cout << "0: " << cc << " : " << score0 << "\n";
    
    cc[1] = '1' - (cc[1] == '1');
    cc[3] = '1' - (cc[3] == '1');
    int score1 = (cc[0] != cc[1]) + (cc[1] != cc[2]) + (cc[2] != cc[3]);
    //cout << "1: " << cc << " : " << score1 << "\n";


    if (score >= max(score0, score1))
        return;
    if (score0 >= score1)
    {
        s[i] = '1' - (s[i] == '1');
        s[i+1] = '1' - (s[i+1] == '1');
        ans.pb(i);
    }
    else
    {
        s[i+1] = '1' - (s[i+1] == '1');
        s[i+2] = '1' - (s[i+2] == '1');
        ans.pb(i+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> s;

    for (int i=0; i<s.size(); i += 3)
    {
        check(i);
    }
    //cout << "new s: " << s << "\n";

    cout << ans.size() << "\n";
    if (ans.empty())
        return 0;

    for (int a : ans)
        cout << a+1 << " ";
    cout << "\n";


    return 0;
}