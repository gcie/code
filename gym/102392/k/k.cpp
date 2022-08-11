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

using namespace std;

const int duzo = 501;
vector<vector<vector<char> > > t;
int skr[3][duzo][duzo][2];

inline int sg(const int& k) {
    return k == 0 ? (-1) : 1;
}

inline int dod(const int& w, const int& l, const int& k) {
    return -sg(k) * (w == l ? 1 : 0);
}

inline int wsp(const int& i, const int& j, const int& k, const int& l) {
    if(l == 0) return i;
    if(l == 1) return j;
    if(l == 2) return k;
}

int n, m, p;

struct wierzch {
    int i, j, k;

    wierzch() {}
    wierzch(int i, int j, int k) : i(i), j(j), k(k) {};
};

inline bool boundary(const int& w, const int& wart) {
    if(wart < 1) return false;
    if(w == 0) return wart <= n;
    if(w == 1) return wart <= m;
    return wart <= p;
}

vector<vector<vector<bool> > > odw;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> p;

    odw.resize(n + 1);
    t.resize(n + 1);
    for(int i = 1; i <= n; ++i) {
        odw[i].resize(m + 1);
        t[i].resize(m + 1);
        for(int j = 1; j <= m; ++j) {
            odw[i][j].resize(p + 1, false);
            t[i][j].resize(p + 1, false);
        }
    }

    int si = 0, sj = 0, sk = 0;
    int fi = 0, fj = 0, fk = 0;

    for(int k = 1; k <= p; ++k) {
        for(int j = 1; j <= m; ++j) {
            for(int i = 1; i <= n; ++i) {
                char c;
                cin >> c;
                if(c == '*') {
                    t[i][j][k] = true;
                }
                else if(c == 'R') {
                    si = i; sj = j; sk = k;
                }
                else if(c == 'T') {
                    fi = i; fj = j; fk = k;
                }
            }
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            for(int k = 1; k <= p; ++k) {
                if(t[i][j][k]) {
                    if(skr[0][j][k][0] == 0)
                        skr[0][j][k][0] = i;
                    skr[0][j][k][1] = i;

                    if(skr[1][i][k][0] == 0)
                        skr[1][i][k][0] = j;
                    skr[1][i][k][1] = j;

                    if(skr[2][i][j][0] == 0)
                        skr[2][i][j][0] = k;
                    skr[2][i][j][1] = k;
                }
            }
        }
    }

    queue<pair<wierzch, int> > q;
    q.push({wierzch(si, sj, sk), 0});
    odw[si][sj][sk] = true;

    while(!q.empty()) {
        auto zz = q.front();
        q.pop();

        auto ziom = zz.st;
        int i = ziom.i;
        int j = ziom.j;
        int k = ziom.k;
        int lev = zz.nd;
       // cerr << i << " " << j << " " << k << endl;

        for(int kier = 0; kier <= 2; ++kier) {
            for(int zw = 0; zw <= 1; ++zw) {
                bool ok = true;
                for(int spr = 0; spr <= 2; ++spr) {
                    if(!boundary(spr, wsp(i, j, k, spr) + dod(spr, kier, zw))) ok = false;
                }
                if(!ok) continue;
                int wi = i + dod(0, kier, zw);
                int wj = j + dod(1, kier, zw);
                int wk = k + dod(2, kier, zw);
                if(t[wi][wj][wk]) continue;
                //cerr << "proba" << wi << " " << wj << " " << wk << endl;
                for(int zw_sun = 0; zw_sun <= 1; ++zw_sun) {
                    if(kier != 0) {
                        int newi = 0, newj = 0, newk = 0;
                        if(skr[0][j][k][1 - zw_sun] != 0 && 
                            sg(zw_sun) * (skr[0][j][k][1 - zw_sun] - i) > 1) {
                            newi = skr[0][j][k][1 - zw_sun] - sg(zw_sun);
                            newj = j;
                            newk = k;
                        }
                        else if(skr[0][j][k][1 - zw_sun] != 0 &&
                            skr[0][wj][wk][1 - zw_sun] != 0 &&
                            sg(zw_sun) * (skr[0][j][k][1 - zw_sun] - i) == 1 &&
                            sg(zw_sun) * (skr[0][wj][wk][1 - zw_sun] - i) >= 1) {
                            
                            newi = skr[0][wj][wk][1 - zw_sun] - sg(zw_sun);
                            newj = wj;
                            newk = wk;
                        }


                        if(newi != 0) {
                            //cerr << 0 << " " << newi << " " << newj << " " << newk << endl;
                            if(!odw[newi][newj][newk]) {
                                if(newi == fi && newj == fj && newk == fk) {
                                    cout << lev + 1;
                                    return 0;
                                }
                                odw[newi][newj][newk] = true;
                                q.push({wierzch(newi, newj, newk), lev + 1});
                            }
                        }
                    }
                    if(kier != 1) {
                        int newi = 0, newj = 0, newk = 0;
                        
                        if(skr[1][i][k][1 - zw_sun] != 0 &&
                            sg(zw_sun) * (skr[1][i][k][1 - zw_sun] - j) > 1) {
                            newi = i;
                            newj = skr[1][i][k][1 - zw_sun] - sg(zw_sun);
                            newk = k;
                        }
                        else if(skr[1][i][k][1 - zw_sun] != 0 &&
                            skr[1][wi][wk][1 - zw_sun] != 0 &&
                            sg(zw_sun) * (skr[1][i][k][1 - zw_sun] - j) == 1 &&
                            sg(zw_sun) * (skr[1][wi][wk][1 - zw_sun] - j) >= 1) {
                            
                            newi = wi;
                            newj = skr[1][wi][wk][1 - zw_sun] - sg(zw_sun);
                            newk = wk;
                        }

                        if(newi != 0) {
                            //cerr << 1 << " " << newi << " " << newj << " " << newk << endl;
                            if(!odw[newi][newj][newk]) {
                                if(newi == fi && newj == fj && newk == fk) {
                                    cout << lev + 1;
                                    return 0;
                                }
                                odw[newi][newj][newk] = true;
                                q.push({wierzch(newi, newj, newk), lev + 1});
                            }
                        }
                    }
                    if(kier != 2) {
                        int newi = 0, newj = 0, newk = 0;
                        if(skr[2][i][j][1 - zw_sun] != 0 &&
                            sg(zw_sun) * (skr[2][i][j][1 - zw_sun] - k) > 1) {
                            newi = i;
                            newj = j;
                            newk = skr[2][i][j][1 - zw_sun] - sg(zw_sun);
                        }
                        else if(skr[2][i][j][1 - zw_sun] != 0 &&
                            skr[2][wi][wj][1 - zw_sun] != 0 &&
                            sg(zw_sun) * (skr[2][i][j][1 - zw_sun] - k) == 1 &&
                            sg(zw_sun) * (skr[2][wi][wj][1 - zw_sun] - k) >= 1) {
                            
                            newi = wi;
                            newj = wj;
                            newk = skr[2][wi][wj][1 - zw_sun] - sg(zw_sun);
                        }

                        if(newi != 0) {
                            //cerr << 2 << " " << newi << " " << newj << " " << newk << endl;
                            if(!odw[newi][newj][newk]) {
                                if(newi == fi && newj == fj && newk == fk) {
                                    cout << lev + 1;
                                    return 0;
                                }
                                odw[newi][newj][newk] = true;
                                q.push({wierzch(newi, newj, newk), lev + 1});
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "-1";
    return 0;
}