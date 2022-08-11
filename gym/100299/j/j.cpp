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

const int maxN = 1 << 12;

struct FFT
{
    #define CMPX complex <double>
    CMPX A[maxN], B[maxN], C[maxN], omega[maxN + 1];
    unsigned int bitrev[maxN];
    unsigned int builtin_bitrev(unsigned int M)
    {
        static unsigned int m[5] = 
        {0xFFFF0000, 0xFF00FF00, 0xF0F0F0F0, 0xCCCCCCCC, 0xAAAAAAAA};

        for (int i=0, d=16; i<5; i++, d>>=1)
            M = ((M & m[i]) >> d) | ((M & ~m[i]) << d);
        return M;
    }

    void init()
    {
        FOR(i, 0, maxN) bitrev[i] = builtin_bitrev(i);
        for (int d=1; d<maxN; d*=2)
        {
            double ang = 3.14159265358979323846 / (maxN / (d*2));
            for (int i=1; d*i<maxN; i+=2)
                omega[d*i] = CMPX(cos(ang*i), sin(ang*i));
        }
        omega[0] = omega[maxN] = CMPX(1, 0);
    }

    void fft_iter(CMPX* a, CMPX* res, int n, int dir)
    {
        int w = __builtin_clz(n) + 1;
        FOR(i, 0, n) res[bitrev[i] >> w] = a[i];
        for (int len = 2, lg=1; len<=n; len *= 2, lg++)
        {
            int d = (maxN >> lg) * dir;
            for (CMPX* t = res; t != res + n; t += len)
            {
                int j = dir == 1 ? 0 : maxN;
                FOR(i, 0, len/2)
                {
                    CMPX x = t[len/2 + i] * omega[j];
                    t[len/2 + i] = t[i] - x;
                    t[i] += x;  j += d;
                }
            }
        }
    }

    void mult_polys_fft(int* a, int n, int* b, int m, int* c)
    {
        n++, m++;
        int k = n + m, g = 1;
        while (g < k)   g *= 2;
        FOR(i, 0, n) A[i] = CMPX(a[i], 0);
        FOR(i, n, g) A[i] = CMPX(0, 0);
        fft_iter(A, B, g, 1);
        FOR(i, 0, m) A[i] = CMPX(b[i], 0);
        FOR(i, m, g) A[i] = CMPX(0, 0);
        fft_iter(A, C, g, 1);
        FOR(i, 0, g)    C[i] *= B[i];
        fft_iter(C, A, g, -1);
        FOR(i, 0, k)
            c[i] = A[i].real() / g + 0.5;
    }
}alg;

int mod, n;
int F[maxN], denom[maxN], pref[maxN][maxN], suf[maxN][maxN], avoid[maxN][maxN], p[maxN], a[maxN];

void clear()
{
    FOR(i, 0, n+1)
        a[i] = 0;

    FOR(i, 0, n+1) FOR(j, 0, n+1)
        avoid[i][j] = suf[i][j] = 0;
}

inline void addMod(int& a, long long b)
{    a = (b + a) % mod; }

inline void multMod(int& a, long long b)
{   a = b * a % mod;    }

long long qpow(int a, long long b)
{
    int res = 1;
    for (; b != 0; b /= 2)
    {
        if (b & 1ll)
            multMod(res, a);
        multMod(a, a);
    }
    return res;
}

inline void divMod(int& a, long long b)
{   a = qpow(b, mod-2) * a % mod;   }


long long W(int i, int j)
{
    int res = j == n ? 1 : avoid[i][n-j];
    divMod(res, denom[i]);
    if ((n-j) % 2 == 1)
        res = (mod - res) % mod;
    return res;
}

void test()
{
    scanf ("%d%d", &n, &mod);
    
    FOR(i, 1, n+1)
        scanf ("%d", p+i);
    
    FOR(i, 2, n+1)
        F[i] = (F[i-2] + F[i-1]) % mod;

    FOR(i, 1, n+1)
    {
        denom[i] = F[i];
        FOR(j, 1, n+1) if (j != i)
            multMod(denom[i], F[i] - F[j] + mod);
    }

    pref[0][0] = suf[n+1][0] = 1;

    FOR(i, 1, n+1)
    {
        pref[i][0] = 1;
        FOR(j, 1, i+1)
            pref[i][j] = (1ll * F[i] * pref[i-1][j-1] + pref[i-1][j]) % mod;
    }

    for (int i=n; i>0; i--)
    {
        suf[i][0] = 1;
        FOR(j, 1, n-i+2)
            suf[i][j] = (1ll * F[i] * suf[i+1][j-1] + suf[i+1][j]) % mod;
    }

    FOR(i, 1, n+1)
        alg.mult_polys_fft(pref[i-1], i-1, suf[i+1], n-i, avoid[i]);

    FOR(i, 1, n+1) FOR(j, 1, n+1)
        addMod(a[i], W(i, j) * p[j]);

    int res = 0;
    FOR(i, 1, n+1)
        addMod(res, qpow(F[i], n+1) * a[i]);
    printf("%d\n", res);
    clear();
}

int main()
{
    alg.init();
    F[0] = F[1] = 1ll;
    int t;
    scanf ("%d", &t);
    while (t--)
    {
        test();
    }

    return 0;
}