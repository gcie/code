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
#define FOR(i, a, b) for (int i=(a); i<(b); i++)

using namespace std;

const int n = 26;

bool M[n][n];
vector <int> G[n];
int state[n], dp[n], nt[n];
bool gotCyc;
int len, root;

void dfsCyc(int v)
{
    state[v] = 1;

    for (int u : G[v])
    {
        if (state[u] == 2)
            continue;
        if (state[u] == 1)
        {
            root = v;
            nt[v] = u;
            gotCyc = true;
            return;
        }

        dfsCyc(u);

        if (gotCyc)
        {
            nt[v] = u;
            return;
        }
    }

    state[v] = 2;
}

void dfsDp(int v)
{
    for (int u : G[v])
    {
        if (dp[u] == 0)
            dfsDp(u);
        if (dp[v] < dp[u])
            dp[v] = dp[u], nt[v] = u;
    }
    dp[v]++;
}

void test()
{
    FOR(i, 0, n) FOR(j, 0, n)
        M[i][j] = true;
    FOR(i, 0, n)
        nt[i] = state[i] = dp[i] = 0, G[i].resize(0);
    gotCyc = len = root = 0;

    int m;
    scanf ("%d", &m);
    while (m--)
    {
        char in[6];
        scanf ("%s", in);
        M[in[0] - 'a'][in[1] - 'a'] = false;
    }

    FOR(i, 0, n) FOR(j, 0, n)
        if (M[i][j])
            G[i].pb(j);

    FOR(i, 0, n) if (state[i] == 0)
    {
        dfsCyc(i);
        if (gotCyc)
        {
            len = 20;
            return;
        }
    }

    FOR(i, 0, n) if (dp[i] == 0)
    {
        dfsDp(i);
        if (dp[i] > len)
            len = dp[i], root = i;
    }

    len = (len + 1) / 2;
}

int main()
{
    int t;
    scanf ("%d", &t);
    while (t--)
    {
        test();
        int v = root;
        FOR(i, 0, len)
        {
            int u = v;
            FOR(j, 0, len)
            {
                printf("%c", 'a' + u);
                u = nt[u];
            }
            v = nt[v];
            printf("\n");
        }
    }

    return 0;
}