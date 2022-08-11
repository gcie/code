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

int win_r = 1, win_c = 1, wr, wc, r, c;

string parse_window(vector<string> &img, int x, int y) {
    string window = "";
    rep(i, 1 + y * (win_r + 1), 1 + win_r + y * (win_r + 1)) {
        window += img[i].substr(1 + x * (win_c + 1), win_c);
    }
    return window;
}

string rot90(string window) {
    string rot = "";
    for(int j = win_c - 1; j >= 0; j--) {
        for(int i = 0; i < win_r; i++) {
            rot += window[i * win_c + j];
        }
    }
    return rot;
}

string rot180(string window) {
    string rot = "";
    for(int j = win_r - 1; j >= 0; j--) {
        for(int i = win_c - 1; i >= 0; i--) {
            rot += window[j * win_c + i];
        }
    }
    return rot;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> r >> c;
    vector<string> img(r);
    rep(i, 0, r) {
        cin >> img[i];
    }
    while(img[win_r+1][1] != '#') win_r++;
    while(img[1][win_c+1] != '#') win_c++;
    // cout << win_r << ' ' << win_c << '\n';

    int wr = r / (win_r + 1), wc = c / (win_c + 1);
    set<string> occ;
    rep(x, 0, wc) {
        rep(y, 0, wr) {
            if(win_r == win_c) {

                string w1 = parse_window(img, x, y);
                string w2 = rot90(w1);
                string w3 = rot90(w2);
                string w4 = rot90(w3);
                if(occ.find(w1) == occ.end() and 
                    occ.find(w2) == occ.end() and
                    occ.find(w3) == occ.end() and
                    occ.find(w4) == occ.end()) {
                    occ.insert(w1);
                }
            } else {
                
                string w1 = parse_window(img, x, y);
                string w2 = rot180(w1);
                if(occ.find(w1) == occ.end() and 
                    occ.find(w2) == occ.end()) {
                    occ.insert(w1);
                }
            }
        }
    }
    cout << occ.size() << '\n';


    return 0;
}