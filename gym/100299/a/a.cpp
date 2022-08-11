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
#define flip(h, i)      (h - i - 1)
#define dest(i, j)      (i * w + j)
using namespace std;

typedef long long       ll;
typedef pair<int, int>  ii;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;


inline string istr(int i) {
    return "R" + to_string(i+1);
}

inline string jstr(int j) {
    return "C" + to_string(j+1);
}


void solve_4pos(vector<vi> &rubik, vector<string> &moves, int h, int w, int i, int j) {
    vector<int> rturn = {dest(i, j), dest(flip(h, i), j), dest(flip(h, i), flip(w, j)), dest(i, flip(w, j))};
    vector<int> lturn = {dest(i, j), dest(i, flip(w, j)), dest(flip(h, i), flip(w, j)), dest(flip(h, i), j)};
    vector<int> rti = {i, flip(h, i), flip(h, i), i, i, flip(h, i), flip(h, i), i};
    vector<int> rtj = {j, j, flip(w, j), flip(w, j), j, j, flip(w, j), flip(w, j)};
    vector<int> lti = {i, i, flip(h, i), flip(h, i), i, i, flip(h, i), flip(h, i)};
    vector<int> ltj = {j, flip(w, j), flip(w, j), j, j, flip(w, j), flip(w, j), j};
    int cnt, d;
    for(int k = 0; k < 8; k++) {
        if(rubik[rti[k]][rtj[k]] == rturn[cnt]) cnt++; else cnt = 0;
        if(cnt == 4) {
            d = k - 3;
            break;
        }
    }
    if(cnt == 4) { // right turn by d

    }
    for(int k = 0; k < 8; k++) {
        if(rubik[rti[k]][rtj[k]] == rturn[cnt]) cnt++; else cnt = 0;
        if(cnt == 4) {
            d = k - 3;
            break;
        }
    }
}


bool is_ok(vector<vi> &rubik, int h, int w, int i, int j) {
    int fi = flip(h, i), fj = flip(w, j);
    set<int> d = {dest(i, j), dest(fi, j), dest(i, fj), dest(fi, fj)};
    for(int k : {i, fi}) {
        for(int l : {j ,fj}) {
            if(d.find(rubik[k][l]) == d.end()) return false;
        }
    }
    return true;
}

int mutual_flip(vector<vi> &rubik, int h, int w, int i, int j) {
    int fi = flip(h, i), fj = flip(w, j);
    if(rubik[i][j] == dest(fi, fj) and dest(i, j) == rubik[fi][fj]) {
        return (rubik[i][fj] == dest(fi, j) and dest(i, fj) == rubik[fi][j] ? 3 : 0); // 3 - cross
    }
    if(rubik[i][j] == dest(fi, j) and rubik[fi][j] == dest(i, j)) {
        return (rubik[i][fj] == dest(fi, fj) and rubik[fi][fj] == dest(i, fj) ? 4 : 0); // parallel, fix j
    }
    if(rubik[i][j] == dest(i, fj) and rubik[i][fj] == dest(i, j)) {
        return (rubik[fi][fj] == dest(fi, j) and rubik[fi][j] == dest(fi, fj) ? 5 : 0); // parallel, fix i
    }
    return 0;
}

int solve_1(vector<vi> &rubik, vector<string> &moves, int h, int w, int i, int j) {
    int fi = flip(h, i), fj = flip(w, j);
    int ki, kj;
    for(auto k : {i, fi}) for(auto l : {j, fj}) {
        if(rubik[k][l] == dest(k, l)) {
            ki = k; kj = l;
        }
    }
    int fki = flip(h, ki), fkj = flip(w, kj);
    if(rubik[fki][fkj] == dest(ki, fkj)) {
        moves.push_back(istr(fki));
        moves.push_back(jstr(fkj));
        moves.push_back(istr(fki));
        moves.push_back(jstr(fkj));
    } else {
        moves.push_back(istr(fki));
        moves.push_back(jstr(fkj));
        moves.push_back(istr(fki));
        moves.push_back(jstr(fkj));
    }
}

int which_case(vector<vi> &rubik, int h, int w, int i, int j) {
    int ok = 0;
    int fi = flip(h, i), fj = flip(w, j);
    for(int k : {i, fi}) {
        for(int l : {j, fj}) {
            if(rubik[k][l] == k * w + l) ok++;
        }
    }
    switch(ok) {
        case 1:
            return 1;
        case 2:
            return 0;
        case 4:
            return 2;
        default:
            return mutual_flip(rubik, h, w, i, j);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    TC(T) {
        scii(w, h);

        // na polu [i][j] powinno być i * w + j
        vector<vi> rubik(h, vi(w, 0));
        vector<bool> flip_row(h, false);
        vector<bool> flip_col(w, false);

        rep(i, 0, h) rep(j, 0, w) {
            cin >> rubik[i][j];
            rubik[i][j]--;
        }


        int h2 = h / 2, w2 = w / 2;
        int h_cent = h % 2, w_cent = w % 2;

        vector<string> moves;

        vector<vector<bool>> req_flip(h2, vector<bool>(w2, false));
        rep(i, 0, h2) { rep(j, 0, w2) {
            if(!is_ok(rubik, h, w, i, j)) {
                goto fail;
            }
            req_flip[i][j] = (0 == which_case(rubik, h, w, i, j));
        }}

        if(w2 > 0 and h2 > 0) {
            rep(i, 0, h2) {
                if(req_flip[i][0]) {
                    flip_row[i] = true;
                    moves.push_back("R" + to_string(i + 1));
                }
            }
            rep(j, 0, w2) {
                if(req_flip[0][j] ^ flip_row[0]) {
                    flip_col[j] = true;
                    moves.push_back("C" + to_string(j + 1));
                }
            }
            rep(i, 0, h2) rep(j, 0, w2) {
                if(flip_row[i] ^ flip_col[j] != req_flip[i][j]) {
                    goto fail;
                }
            }
        }

        if(h_cent && w_cent) {
            if(rubik[h2][w2] != dest(h2, w2)) goto fail;
        }

        if(h_cent) {
            bool forward = true, backward = true;

            rep(j, 0, w) {
                if(rubik[h2][j] != dest(h2, j)) forward = false;
                if(rubik[h2][w-j-1] != dest(h2, j)) backward = false;
            }

            if(forward == false and backward == false) goto fail;

            if(backward) {
                moves.push_back("R" + to_string(h2+1));
                flip_row[h2] = true;
            }
        }

        if(w_cent) {
            bool forward = true, backward = true;

            rep(i, 0, h) {
                if(rubik[i][w2] != dest(i, w2)) forward = false;
                if(rubik[h-i-1][w2] != dest(i, w2)) backward = false;
            }

            if(forward == false and backward == false) goto fail;

            if(backward) {
                moves.push_back("C" + to_string(w2+1));
                flip_col[w2] = true;
            }
        }

        rep(i, 0, h2) rep(j, 0, w2) {
            int fi = flip(h, i), fj = flip(w, j);
            if(flip_row[i]) swap(rubik[i][j], rubik[i][fj]);
            if(flip_col[j]) swap(rubik[i][j], rubik[fi][j]);
            switch(which_case(rubik, h, w, i, j)){
            case 0:
                goto fail;
            case 1:
                solve_1(rubik, moves, h, w, i, j);
                break;
            case 2: // solved
                break;
            case 3: // cross
                moves.push_back(istr(i));
                moves.push_back(jstr(j));
                moves.push_back(istr(fi));
                moves.push_back(istr(i));
                moves.push_back(jstr(j));
                moves.push_back(istr(fi));
                break;
            case 4: // parallel, fix j
                moves.push_back(jstr(j));
                moves.push_back(istr(i));
                moves.push_back(istr(fi));
                moves.push_back(jstr(j));
                moves.push_back(istr(i));
                moves.push_back(istr(fi));
                break;
            case 5:
                moves.push_back(istr(i));
                moves.push_back(jstr(j));
                moves.push_back(jstr(fj));
                moves.push_back(istr(i));
                moves.push_back(jstr(j));
                moves.push_back(jstr(fj));
                break;
            }
        }


        cout << "POSSIBLE " << moves.size() << ' ';
        // prvv(rubik);
        prv(moves);
        goto success;


        fail:
        cout << "IMPOSSIBLE\n";
        success: {}
    }

    return 0;
}

/**
1

10

10
00

IMPOSSIBLE
*/