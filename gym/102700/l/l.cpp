#pragma gcc optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb              push_back
#define _dist(x)        get<0>(x)
#define _dir(x)         get<1>(x)
#define _pos(x)         get<2>(x)
#define st              first 
#define nd              second 
#define all(x)          (x).begin(), (x).end()
#define sci(x)          int x;       cin >> x;
#define scii(x, y)      int x, y;    cin >> x >> y;
#define sciii(x, y, z)  int x, y, z; cin >> x >> y >> z;
#define TC(x)           sci(x); while(x --)
#define rep(i, x, y)    for (__typeof(x) i = x; i < y; i ++)
#define repi(i, x, y)   for(__typeof(y) i = y - 1; i >= x; i --)
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
    ios_base::sync_with_stdio(false); cin.tie(0);
    scii(n, m);
    vector<vi> board(n, vi(m, 0));
    vector<vi> shortest_path(n, vi(m, 1000000000));
    vector<vector<char>> last_dir(n, vector<char>(m, 'X'));

    map<char, vector<vi>> dton;
    dton['D'] = new vector<vi>(n, vi(m, -1));
    dton['L'] = new vector<vi>(n, vi(m, -1));
    dton['R'] = new vector<vi>(n, vi(m, -1));
    dton['U'] = new vector<vi>(n, vi(m, -1));

    rep(i, 0, n) {
        int q = -1;
        rep(j, 0, m) {
            dton['L'][i][j] = q;
            if(!board[i][j]) q = j;
        }
        q = -1;
        repi(j, 0, m) {
            dton['R'][i][j] = q;
            if(!board[i][j]) q = j;
        }
    }

    rep(j, 0, m) {
        int q = -1;
        rep(i, 0, n) {
            dton['D'][i][j] = q;
            if(!board[i][j]) q = i;
        }
        q = -1;
        repi(i, 0, n) {
            dton['U'][i][j] = q;
            if(!board[i][j]) q = i;
        }
    }

    ii start, finish;
    priority_queue<tuple<int, char, ii>> pq;

    rep(i, 0, n) {
        string s;
        cin >> s;
        rep(j, 0, m) {
            if(s[j] == 'X') board[i][j] = 1;
            else if(s[j] == 'S') start = {i, j};
            else if(s[j] == 'E') finish = {i, j};
        }
    }

    pq.push({0, 'S', first});
    while(!pq.empty()) {
        auto el = pq.top();
        int x = _pos(x).st, y = _pos(x).nd, dist = _dist(x);

        for(char dir : {'D', 'L', 'R', 'U'}) {
            int next = dton[dir][x][y];
            if(next != -1) {
                if(shortest_path[x][y] == dist + 1) {
                    if(last_dir[x][y] > dir) {
                        last_dir[x][y] = dir;

                    }
                }

            }
        }



    }


    return 0;
}