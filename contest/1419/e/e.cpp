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
#define TC              sci(__test_case); while(__test_case --)
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


int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0);
    TC {

    ll n;
    cin >> n;

    int d = 2;
    set<int> prime_divisors;
    
    ll m = n;
    while(m > 1) {
        while (m % d == 0) {
            prime_divisors.insert(d);
            m /= d;
        }
        d++;
    }

    d = 2;
    set<int> divisors;
    divisors.insert(n);
    while(d * d <= n) {
        if(n % d == 0) {
            divisors.insert(d);
            divisors.insert(n / d);
        }
        d += 1;
    }

    map<int, vi> divs;

    for(int div : divisors) {
        if (prime_divisors.find(div) != prime_divisors.end()) continue;
        else {
            for(int p : prime_divisors) {
                if (div % p == 0) {
                    auto it = prime_divisors.find(p);
                    auto jt = prime_divisors.find(div / p);

                    if(jt == prime_divisors.end() || (it != next(jt) && next(it) != jt && !((next(jt) == prime_divisors.end() && it == prime_divisors.begin()) || (next(it) == prime_divisors.end() && jt == prime_divisors.begin())))) {
                       divs[p].push_back(div);
                    }
                    break;
                }
            }
        }
    }


    if(prime_divisors.size() == 1) {
        prv(divisors);
        cout << 0 << '\n';
    } else if (prime_divisors.size() == 2) {
        int p1 = *(prime_divisors.begin());
        int p2 = *(prime_divisors.rbegin());
        

        if(p1 * p2 == n) {
            cout << p1 << ' ' << p2 << ' ' << n << '\n' << 1 << '\n';
        } else {
            set<int> common_divs;
            for(int div : divisors) {
                if (div % p1 == 0 && div % p2 == 0) {
                    common_divs.insert(div);
                }
            }
            cout << p1 << ' ';
            for(auto div : divs[p1]) {
                if(common_divs.find(div) != common_divs.end()) continue;
                cout << div << ' ';
            }
            auto it = common_divs.begin();
            cout << *it << ' ';
            it++;
            cout << p2 << ' ';
            for(auto div : divs[p2]) {
                if(common_divs.find(div) != common_divs.end()) continue;
                cout << div << ' ';
            }
            while(it != common_divs.end()) {
                cout << *it << ' ';
                it++;
            }
            cout << '\n' << 0 << '\n';
        }
    } else {

        for(auto it = prime_divisors.begin(); it != prime_divisors.end(); it++) {
            int p = *it;
            auto jt = next(it);
            int q = 0;
            if (jt == prime_divisors.end()) q = *(prime_divisors.begin());
            else q = *jt;

            cout << p << ' ';
            for(int div : divs[p]) {
                cout << div << ' ';
            }
            cout << p * q << ' ';
        }
        cout << '\n' << 0 << '\n';
    }
    }

    return 0;
}