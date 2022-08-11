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
typedef pair<ld, ld>    pkt;

using namespace std;

pkt p[5];
int oczka[] = {3, 6, 4, 1};
const ld pol = 0.5;
const ld dp = 25.0;

inline void znajdz_pkt(vector<int>& res) {
    for(int i = 1; i <= 4; ++i) {
        if(p[i].st > pol) res.pb(i);
    }
}

inline void obroc() {
    ld pom;
    for(int i = 1; i <= 4; ++i) {
        pom = p[i].st;
        p[i].st = p[i].nd;
        p[i].nd = -pom;
    }
}

inline int excl(vi& v) {
    int sum = 0;
    for(auto x: v) sum += x;
    return 10 - sum;
}

inline ld przec(int p1, int p2) {
    ld x1 = p[p1].st;
    ld x2 = p[p2].st;
    ld y1 = p[p1].nd;
    ld y2 = p[p2].nd;
    return (abs(x1 - pol) * y2 + abs(x2 - pol) * y1) / abs(x1 - x2);
}

inline ld pole(int wie, ld y1, ld y2) {
    return 0.5 * abs(p[wie].st - pol) * abs(y1 - y2);
}

inline ld sqr(const ld& x) {
    return x * x;
}

inline ld dlug(pkt& p1, pkt& p2) {
    return sqrt(sqr(p1.st - p2.st) + sqr(p1.nd - p2.nd));
}

inline ld trap(pkt p1, pkt p2, pkt som1, pkt som2) {
    return 2.5 * (dlug(p1, som1) + dlug(p2, som2));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    for(int i = 1; i <= 4; ++i) {
        cin >> p[i].st >> p[i].nd;
    }

    ld sum = 0.0;

    for(int i = 0; i < 4; ++i) {
        /*for(int i = 1; i <= 4; ++i) {
            cerr << p[i].st << " " << p[i].nd << endl;
        }*/
        vector<int> v;
        znajdz_pkt(v);
        int siz = v.size();
        if(siz == 2) {
            if(v[0] == 1 && v[1] == 4) swap(v[0], v[1]);
            int som[2];
            som[0] = v[0] - 1;
            som[1] = v[1] + 1;
            for(int i = 0; i <= 1; ++i) {
                if(som[i] == 5) som[i] = 1;
                if(som[i] == 0) som[i] = 4;
            }

            ld y1 = przec(v[0], som[0]);
            ld y2 = przec(v[1], som[1]);
            ld area = trap(p[v[0]], p[v[1]], {pol, y1}, {pol, y2});
            
            //cerr << i << " " << area << endl;

            sum += ld(oczka[i]) * (5.0 * area / 124.0);

        }
        else {
            int put = v[0];
            if(siz == 3) put = excl(v);
            int som[2];
            som[0] = put + 1;
            som[1] = put - 1;
            for(int i = 0; i <= 1; ++i) {
                if(som[i] == 5) som[i] = 1;
                if(som[i] == 0) som[i] = 4;
            }

            ld y1 = przec(put, som[0]);
            ld y2 = przec(put, som[1]);
            ld area = pole(put, y1, y2);

            //cerr << i << " " << area << endl;

            if(siz == 3) sum += ld(oczka[i]) * (5.0 * (dp - area) / 124.0);
            else sum += ld(oczka[i]) * (5.0 * area / 124.0);
        }
        obroc();
    }

    sum += 125.0 / 31.0;

    cout << setprecision(10) << fixed << sum;

    return 0;
}