#pragma gcc optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb              push_back
#define st              first
#define nd              second.first
#define rd second.second
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
typedef pair<ll, ll> pll;

struct BigNum
{
	static const int B = 1000000000;
	vector <int> a;		int sign;
	void normalise()
	{
		while (a.size() != 1 and a.back() == 0)	a.pop_back();
		if (a.back() == 0)	sign = 1;
	}
	int operator[] (int i)	const	{	return a[i];	}	
	bool lowerMod(const BigNum& other)	const
	{
		if (a.size() != other.a.size())
			return a.size() < other.a.size();
		for (int i=a.size()-1; i>=0; i--)
			if (a[i] != other[i])
				return a[i] < other[i];
		return false;
	}		
	void operator+= (BigNum& other)
	{
		if (other.sign != sign)
		{
			other.sign *= -1;	(*this) -= other;
			other.sign *= -1;	return;
		}
		a.resize(max(a.size(), other.a.size()));
		int carry = 0;
		rep(i, 0, a.size())
		{
			int b = a[i] + carry + (i < other.a.size() ? other[i] : 0);
			a[i] = b % B;
			carry = b >= B;
		}
		if (carry == 1)	a.pb(1);
	}
	void operator-= (BigNum& other)
	{
		if (sign != other.sign)
		{
			other.sign *= -1;	(*this) -= other;
			other.sign *= -1;	return;
		}
		bool inv = lowerMod(other);
		vector <int>& x = inv ? other.a : a;
		vector <int>& y = inv ? a : other.a;
		a.resize(x.size());
		int carry = 0;
		rep(i, 0, a.size())
		{
			a[i] = x[i] - carry - (i < y.size() ? y[i] : 0);
			if (carry = (a[i] < 0))		a[i] += B;
		}
		if (inv) sign = -sign;
		normalise();
	}
	void operator/= (int m)	//|m|<B
	{
		if (m < 0)	m = -m, sign = -sign;
		long long mod = 0;
		for (int i=a.size()-1; i>=0; i--)
		{
			mod = mod * B + a[i];
			a[i] = mod / m;
			mod %= m;
		}
		normalise();
		if (sign == -1 and mod != 0)
		{
			BigNum mOne(-1ll);
			(*this) += mOne;
		}
	}
	BigNum operator* (BigNum other)
	{
		BigNum res(0);
		vector <int> &b = other.a, &c = res.a;
		c.resize(a.size() + b.size());
		rep(i, 0, a.size()) rep(j, 0, b.size())
		{
			long long x = 1ll * a[i] * b[j] + c[i+j];
			c[i+j] = x % B;
			c[i+j+1] += x / B;
		}
		res.sign = sign * other.sign;
		res.normalise();
		return res;
	}
	int operator% (int m)	// m duze -> int128
	{
		long long b = 1;
		int res = 0;
		rep(i, 0, a.size())
			res = (b * a[i] + res) % m, b = b * B % m;
		if (sign == -1 and res != 0)	res = m - res;
		return res;
	}
	bool operator< (const BigNum& other)
	{
		if (sign != other.sign)	return sign < other.sign;
		return sign == 1 ? lowerMod(other) : other.lowerMod(*this);
	}
	void operator= (char* s)
	{
		sign = 1; a.resize(0);
		if (s[0] == '-')	sign = -1, s++;
		int m = strlen(s);
		for (int i=m; i>0; i-=9)
		{
			int j=max(0, i-9);	swap(s[i], s[m]);
			a.pb(atoi(s+j));	swap(s[i], s[m]);
		}
		normalise();
	}
	void operator= (long long n)
	{
		sign = 1;
		if (n < 0)	sign = -1, n *= -1;
		a.resize(0);
		if (n == 0)	a.pb(0);
		for (; n != 0; n /= B)	a.pb(n % B);
	}
	void operator= (const BigNum& other)
	{	sign = other.sign; a = other.a;	}
	BigNum(long long n)		{	(*this) = n;	}	//char* s, BigNum&
	BigNum operator+ (BigNum& other)	//-, /, %
	{	BigNum res(*this);	res += other; return res;	}
};

typedef pair<BigNum, pair<BigNum, BigNum>> tll;

ll solve(int k, ll b, ll c) {
    ll delta = k * k * (b + c) * (b + c) - 4 * (b * b + c * c - k * b * c - 1);
    return (k * (b + c) + sqrt(delta)) / 2;
}

bool check(ll a, ll b, ll c, int k) {
    return a * a + b * b + c * c == k * (a * b + b * c + c * a) + 1;
}

int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0);
    scii(k, n);
    set<BigNum> used;
    int done = 0;
    queue<tll> q;
    q.push({0, {1, k}});
    while(done < n) {
        tll t = q.front();
        q.pop();
        if(BigNum(0) < t.st and BigNum(0) < t.nd and BigNum(0) < t.rd and used.find(t.st) == used.end() and used.find(t.nd) == used.end() and used.find(t.rd) == used.end()) {
            cout << t.st << ' ' << t.nd << ' ' << t.rd << '\n';
            used.insert(t.st);
            used.insert(t.nd);
            used.insert(t.rd);
            done++;
        }
        if(BigNum(-1) < t.st and BigNum(-1) < t.rd and BigNum(-1) < t.nd) {
            q.push({t.st, make_pair(t.nd, BigNum(k) * (t.st + t.nd) - t.rd)});
            q.push({t.st, make_pair(BigNum(k) * (t.st + t.rd) - t.nd, t.rd)});
            q.push({BigNum(k) * (t.nd + t.rd) - t.st, make_pair(t.nd, t.rd)});
        }
    }
    return 0;
}