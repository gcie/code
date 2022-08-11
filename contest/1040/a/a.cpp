#include <bits/stdc++.h>

#define forn(i, n) for(int i = 0; i < (n); ++i)
#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long LL;
typedef pair<int, int> pint;

int a, b, n;
int c[25];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> a >>b;
    forn(i, n) cin >> c[i];

    int cost = 0;
        for(int i = 0; i < n/2; i++) {
            if(c[i] == 2 && c[n - i - 1] == 2) {
                cost += 2 * min(a, b);
            } else if(c[i] == 2 && c[n - i - 1] != 2) {
                cost += c[n - i - 1] == 1 ? b : a;
            } else if(c[i] != 2 && c[n - i - 1] == 2) {
                cost += c[i] == 1 ? b : a;
            } else if(c[i] != c[n - i - 1]) {
                cout << -1;
                return 0;
            }
        }
    if(n & 1 && c[n/2] == 2) cost += min(a, b);
    cout << cost;
    return 0;
}