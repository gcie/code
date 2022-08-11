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
#define prv(v)          for(auto& x: v) //cout << x << ' '; //cout << '\n';
#define prvv(v)         for(auto& w: v) { for(auto& x: w) //cout << x << ' '; //cout << '\n'; }
using namespace std;

typedef long long       ll;
typedef pair<int, int>  ii;
typedef vector<int>     vi;
typedef long double     ld;
typedef vector<ll>      vll;

using namespace std;

map<string, int> stationId;
map<string, int> lineId;
vi line[300042]; // lineId -> {stations}
vi station[300042]; // stationId -> {lines}

int minutes[300042];
int changes[300042];
bool wasLine[300042];

string jhn;
string mich;
int jhId = 0;
int miId = 0;

void clr()
{
    for (int i=0; i<lineId.size(); i++)
    {
        wasLine[i] = 0;
        line[i].clear();
    }
    for (int i=0; i<stationId.size(); i++)
    {
        changes[i] = 0;
        minutes[i] = 0;
        station[i].clear();
    }
    stationId.clear();
    lineId.clear();
}

void read()
{
    int stId = 0;
    string trash;cin >> trash;string stp;cin >> stp;
    while (stp != "Lines:")
    {
        if (stp.back() == ',')
            stp.pop_back();
        stationId[stp] = stId++;
        cin >> stp;
    }

    int lnId = 0;
    string ln;cin >> ln;
    while (ln.back() == ',')
    {
        ln.pop_back();
        lineId[ln] = lnId++;
        cin >> ln;
    }
    lineId[ln] = lnId++;

    cin >> ln;
    while (ln != "Johny")
    {
        //cout << "READ: " << ln << ": ";
        int lnId = lineId[ln];
        cin >> trash;
        string stp;cin >> stp;
        while (stp.back() == ',')
        {
            //cout << stp << " ";
            stp.pop_back();
            int stId = stationId[stp];
            line[lnId].pb(stId);
            station[stId].pb(lnId);
            cin >> stp;
        }
        int stId = stationId[stp];
        line[lnId].pb(stId);
        station[stId].pb(lnId);
        //cout << stp << "\n";

        cin >> ln;
    }

    // Johny
    cin >> trash;cin >> trash; cin >> jhn;
    jhId = stationId[jhn];
    // Michelle
    cin >> trash;cin >> trash;cin >> trash; cin >> mich;
    miId = stationId[mich];
    
}

void solve()
{
    minutes[miId] = 0;
    changes[miId] = 1;
    int prev = 1;
    vector<int> slice = station[miId];
    while (!slice.empty())
    {
        //cout << "Slice nr " << prev+1 << "\n";
        set<int> newSlice;

        for (int lnId : slice)
        {
            //cout << "Line nr " << lnId << "\n";
            wasLine[lnId] = 1;

            bool was = 0;
            int actmax = -1;
            //cout << "Sts : ";
            for (int i=0; i<line[lnId].size(); i++)
            {
                if (actmax != -1)
                    actmax++;
                int st = line[lnId][i];
                //cout << st << " ";
                if (changes[st] == prev)
                {
                    was = 1;
                    actmax = max(actmax, minutes[st]);
                    continue;
                }
                changes[st] = prev+1;
                for (int ln : station[st])
                    if (!wasLine[ln])
                        newSlice.insert(ln);
                        
                if (!was || i == 0)
                    continue;
                minutes[st] = max(minutes[st], actmax);
            }
            //cout << "\nSts reversed : ";

            was = 0;
            actmax = -1;
            for (int i=line[lnId].size()-1; i>=0; i--)
            {
                if (actmax != -1)
                    actmax++;
                int st = line[lnId][i];
                //cout << st << " ";
                if (changes[st] == prev)
                {
                    was = 1;
                    actmax = max(actmax, minutes[st]);
                    continue;
                }
                if (!was || i == line[lnId].size()-1)
                    continue;
                minutes[st] = max(minutes[st], actmax);
            }
            //cout << "\n";
        }

        slice.clear();
        for (int l : newSlice)
        {
            if (!wasLine[l])
                slice.pb(l);
        }
        prev++;
    }
}

void answser()
{
    //cout << "JhId : " << jhId << ", miId : " << miId << "\n";
    int usedLines = changes[jhId]-1;
    string ls = " line";
    ls += (usedLines > 1 ? "s" : "");
    ls += ", ";
    int usedMinutes = minutes[jhId];
    string ms = " minute";
    ms += (usedMinutes > 1 ? "s" : "");
    cout << "optimal travel from " << jhn << " to " << mich << ": " << usedLines << ls << usedMinutes << ms << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    TC(x)
    {
        clr();
        read();
        solve();
        answser();
    }

    return 0;
}