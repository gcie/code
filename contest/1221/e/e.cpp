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

void bob() {
    cout << "NO\n";
}
void alice() {
    cout << "YES\n";
}

bool solve(int s, int a, int b) { // s >= a
    if(s <= a + 2 * b - 2) {
        return true;
    } else if(s >= a + 4 * b - 1) {
        return false;
    } else if(s >= 3 * a) {
        return (s - a + 1) / 2 < 2 * b;
    } else {
        return false;
    }
}

bool antisolve(int s, int a, int b) { // s >= a
    if(s < 2 * b) return true;
    else if(s < 2 * a) return false;
    else if(s <= a + b - 1 + 2 * b - 1) return 2 * b - 1 >= a;
    else return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    TC(T) {
        scii(a, b);
        string s; cin >> s;
        int dcnt = 0;
        vector<int> seg;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '.') {
                dcnt++;
            } else if(dcnt > 0) {
                if(dcnt >= b) seg.push_back(dcnt);
                dcnt = 0;
            }
        }
        if(dcnt >= b) seg.push_back(dcnt);
        sort(all(seg));
        // prv(seg);
        int n = ((int)seg.size());
        if(n == 0) {
            bob();
        } else if(seg[0] < a) {
            bob();
        } else if(n == 1) {
            if(solve(seg[0], a, b)) {
                alice();
            } else {
                bob();
            }
        } else if(seg[n - 2] >= 2 * b) {
            bob();
        } else {
            if(n % 2) {
                if(solve(seg[n-1], a, b)) {
                    alice();
                } else {
                    bob();
                }
            } else {
                if(antisolve(seg[n-1], a, b)) {
                    alice();
                } else {
                    bob();
                }
            }

        }


    }

    return 0;
}