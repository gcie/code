#include <bits/stdc++.h>
using namespace std;
typedef vector<int>     vi;

string s, t;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> s >> t;
    vi l(((int)t.size())), r(((int)t.size()));
    int q = 0;
    for(int i = 0; i < s.size() and q < t.size(); i++) {
        if(s[i] == t[q]) {
            l[q++] = i;
        }
    }
    q = t.size() - 1;
    for(int i = s.size() - 1; i >= 0 and q >= 0; i--) {
        if(s[i] == t[q]) {
            r[q--] = i;
        }
    }
    int n = t.size();
    int k = max(r[0], ((int)s.size()) - 1 - l[n - 1]);
    for(int i = 0; i < n - 1; i++) {
        k = max(k, r[i + 1] - l[i] - 1);
    }
    cout << k << '\n';
    return 0;
}