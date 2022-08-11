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

int from_vector(vi &v) {
    string q = "? ";
    rep(i, 0, v.size()) {
        q += v[i] == 1 ? '1' : '0';
    }
    cout << q << endl;
    sci(ans);
    return ans;
}

template <typename T>
vector<size_t> index_sort(const vector<T> &v) {
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
    return idx;
}

void solve() {
    scii(n, m);
    // query all edges
    vi weight(m);
    rep(i, 0, m) {
        string q = "? ";
        rep(j, 0, i) q += '0';
        q += '1';
        rep(j, i+1, m) q += '0';
        cout << q << endl;
        cin >> weight[i];
    }
    auto I = index_sort(weight);

    vi necessary(m, 1);

    string q = "? ";
    rep(i, 0, m) q += '1';
    cout << q << endl;
    int last_weight;
    cin >> last_weight;
    for(int i = m - 1; i > 0; --i) {
        necessary[I[i]] = 0;
        int new_weight = from_vector(necessary);
        if(new_weight + weight[I[i]] == last_weight) {
            necessary[I[i]] = 1;
        } else {
            last_weight = new_weight;
        }
    }
    cout << "! " << last_weight << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	solve();
    return 0;
}