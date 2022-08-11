#include <bits/stdc++.h>
#define st first
#define nd second
#define sci(x) int x; cin >> x;
#define scii(x, y) int x, y; cin >> x >> y;
#define sciii(x, y, z) int x, y, z; cin >> x >> y >> z;
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define scvi(v, n) vector<int> v(n); for(int i = 0; i < (n); ++i) cin >> v[i];
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;

using namespace std;

bool is_ok(vector<string> &image, int y, int x, int h) {
    for(int q = y + 1; q < y + h / 3; q++) if(image[y][x] != image[q][x]) return false;
    for(int q = y + h / 3 + 1; q < y + 2 * h / 3; q++) if(image[y + h / 3][x] != image[q][x]) return false;
    for(int q = y + 2 * h / 3 + 1; q < y + h; q++) if(image[y + 2 * h / 3][x] != image[q][x]) return false;
    return image[y][x] != image[y + h / 3][x] && image[y + h / 3][x] != image[y + 2 * h / 3][x];
}

bool _is_same(vector<string> &image, int y, int x, int h) {
    for(int q = y; q < y + h; ++q) if(image[q][x-1] != image[q][x]) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    scii(n, m);
    vector<string> image(n);
    rep(i, 0, n) cin >> image[i];
    long long res = 0;
    for(int h = 3; h <= n; h += 3) {
        for(int y = 0; y + h <= n; y++) {
            vector<int> c;
            bool new_flag = true;
            int cnt = 0;
            for(int x = 0; x < m; ++x) {
                if(!is_ok(image, y, x, h)) { if(cnt != 0) c.push_back(cnt); new_flag = true; cnt = 0; continue; }
                if(new_flag) {
                    new_flag = false;
                    cnt++;
                } else {
                    if(_is_same(image, y, x, h)) {
                        cnt++;
                    } else {
                        if(cnt != 0) c.push_back(cnt);
                        cnt = 1;
                    }
                }
            }
            if(cnt != 0) c.push_back(cnt);
            for(auto x : c) { /* cout << x << ' '; */ res += ((1 << x) - 1); }/*  cout << '\n'; */
        }
    }
    cout << res << '\n';

    return 0;
}