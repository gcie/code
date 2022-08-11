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


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> int_dis;
uniform_real_distribution<double> double_dis;

inline int rand_int() {
    return int_dis(rng);
}

inline double rand_double() {
    return double_dis(rng);
}

struct treap {
    int value, size, priority;
    treap* left;
    treap* right;
    treap(int _value, int _priority, int _size, treap* _left, treap* _right): value(_value), priority(_priority), size(_size), left(_left), right(_right) {}
    treap(int _value, int _priority, int _size): value(_value), priority(_priority), size(_size), left(nullptr), right(nullptr) {}
    treap(int _value, int _priority): value(_value), priority(_priority), size(1), left(nullptr), right(nullptr) {}

    treap* insert(int _value) {
        return insert(_value, rand_int());
    }

    treap* insert(int _value, int _priority) {
        if(_priority > priority) {
            treap* t = new treap(_value, _priority, size+1);
            if(value < _value) {
                t->left = this;
            } else {
                t->right = this;
            }
            return t;
        } else if(_value < value) {
            if(left == nullptr) {
                left = new treap(_value, _priority);
            } else left->insert(_value, _priority);
            return this;
        } else {
            if(right == nullptr) {
                right = new treap(_value, _priority);
            } else right->insert(_value, _priority);
            return this;
        }
    }

    void print() {
        if(left != nullptr && right != nullptr) {
            cout << "(";
            left->print();
            cout << ") <- " << value << " -> (";
            right->print();
            cout << ")";
        } else if (left != nullptr) {
            cout << "(";
            left->print();
            cout << ") <- " << value;
        } else if (right != nullptr) {
            cout << value << " -> (";
            right->print();
            cout << ")";
        } else cout << value;
    }
};


void solve() {
	scii(n, q);


}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	// solve();
    sci(n);

    treap* t = new treap(0, 0);
    rep(i, 1, n+1) {
        t = t->insert(i);
    }
    t->print();



    return 0;
}