#include <bits/stdc++.h>
#define st first
#define nd second
#define sci(x) int x; cin >> x;
#define scii(x, y) int x, y; cin >> x, y;
#define sciii(x, y, z) int x, y, z; cin >> x >> y >> z;
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define scvi(v, n) vector<int> v(n); for(int i = 0; i < (n); ++i) cin >> v[i];
#define all(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;


using namespace std;

void succ(int k) {
    cout << k << '\n';
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ll k; cin >> k; k--;

    ll starts = 1;
    ll length = 1;
    while(k >= 9 * starts * length) {
        k -= 9 * starts * length;
        length++; starts *= 10; 
    }
    starts += k / length;
    ll pos = length - k % length - 1;
    while(pos > 0) {
        starts /= 10;
        pos--;
    }
    succ(starts % 10);
    return 0;
}