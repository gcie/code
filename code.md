# Hungarian algorithm
```cpp
struct Hungarian
{
	long long *C[maxN], pot[maxN * 2], mluz[maxN * 2];
	int *part, n, ctr, qtop, qback, vis[maxN * 2], vluz[maxN * 2], Q[maxN];
	#define LUZ(a, b)	(C[a][(b) - n] - pot[a] - pot[b])
	inline void aug(int x, int y)
	{
		while (x != 0)
			part[y] = x, swap(part[x], y), x = vluz[x];
	}
	inline void ins(int v, int prev)
	{
		FOR(j, n+1, n*2+1)
		{
			long long luz = LUZ(v, j);
			if (mluz[j] > luz)
				mluz[j] = luz, vluz[j] = v;
		}
		vis[v] = vis[part[v]] = ctr;
		Q[qback++] = v;	vluz[v] = prev;
	}
	long long f(int nn, long long Cin[maxN][maxN], int* partOut)
	{
		n = nn; part = partOut;
		FOR(i, 0, n*2+1) vis[i] = part[i] = pot[i] = 0;
		FOR(i, 0, n+1)	 C[i] = Cin[i];
		for (ctr=1; ctr<=n; ctr++)
		{
			fill(mluz + n+1, mluz + n*2+1, INF);
			ins(ctr, qback = qtop = 0);
			while (true)
			{
				for (int i = Q[qtop]; qtop != qback; qtop++)
				{
					FOR(j, n+1, n*2+1)
					if (vis[j] != ctr and LUZ(i, j) == 0)
					{
						if (part[j] == 0) {aug(i, j); goto Break;}
						ins(part[j], i);
					}
				}
				long long mn = INF;
				FOR(j, n+1, n*2+1)
					if (vis[j] != ctr)
						remin(mn, mluz[j]);
				FOR(i, 1, n+1)
					if (vis[i] == ctr)
						pot[i] += mn;
				FOR(j, n+1, n*2+1)
					vis[j] == ctr	?	pot[j] -= mn : mluz[j] -= mn;
				FOR(j, n+1, n*2+1)
				if (vis[j] != ctr and mluz[j] == 0)
				{
					if (part[j] == 0)
					{	aug(vluz[j], j); goto Break;	}
					ins(part[j], vluz[j]);
				}
			} Break: ;
		}
		long long cost = 0;
		FOR(i, 1, n+1)	cost += C[i][part[i] - n];
		return cost;
	}
};
```

# Tree isomorphism
```cpp
struct Tree_isomorphism
{
    vector <int> bucket[maxN], presLetters[maxN], seqsOfLen[maxN], emptys;
    int temp[maxN][2];
    void posSort(vector <int>* T, int n, vector <int>& res)
    {
        int maxLen = 0, tempSize = 0, M = n;
        FOR(i, 0, n)
        {
            FOR(j, 0, T[i].size())
            {
                temp[tempSize][0] = j;
                temp[tempSize++][1] = T[i][j];
                M = max(M, T[i][j]);
            }
            int len = T[i].size() - 1;
            maxLen = max(len, maxLen);
            len == -1 ? emptys.pb(i) : seqsOfLen[len].pb(i);
        }
        remax(M, maxLen);
        for (int s=1; s>=0; s--)
        {
            FOR(i, 0, tempSize)
            {
                int key = temp[i][s], val = temp[i][s ^ 1];
                bucket[key].pb(val);
            }
            for (int i=0, k=0; i<=M; i++)
            {
                for (int a : bucket[i])
                {
                    temp[k][s] = i;
                    temp[k++][s ^ 1] = a;
                }
                bucket[i].resize(0);
            }
        }
        FOR(i, 0, tempSize)
        if (i == 0 or temp[i][0] != temp[i - 1][0] or temp[i][1] != temp[i - 1][1])
                presLetters[temp[i][0]].pb(temp[i][1]);
        res.resize(0);
        for (int len=maxLen; len>=0; len--)
        {
            for (int id : seqsOfLen[len])	bucket[T[id][len]].pb(id);  
            for (int id : res)				bucket[T[id][len]].pb(id);
            res.resize(0);
            for (int letter : presLetters[len])
            {
                res.insert(res.end(), ALL(bucket[letter]));
                bucket[letter].resize(0);
            } 
            presLetters[len].resize(0);
            seqsOfLen[len].resize(0);
        }
        res.insert(res.begin(), ALL(emptys));
        emptys.resize(0);
    }
    int id[2][maxN], sz[maxN];
    vector <int> L[2][maxN], vsOnDist[2][maxN], tempSeq[maxN], order0, order1, *G; 
    void clear(int n)
    {
        FOR(i, 0, n+1) FOR(s, 0, 2)
            L[s][i].resize(0), vsOnDist[s][i].resize(0);
        order0.resize(0); order1.resize(0);
    }
    void newCentroid(int a, int u, int v, vector <int>* g, bool ins)
    {
        int tab[2]; tab[0] = u, tab[1] = v;
        FOR(s, 0, 2)
        {
            for (int& w : g[v])
                if (w == u or w == a)
                {	w = ins ? a : u; break;	}
            swap(u, v);
        }
        ins ? g[a].pb(u), g[a].pb(v) : g[a].resize(0);
    }
    int dfsCents(int v, int fath)
    {
        sz[v] = 1;
        for (int u : G[v])	if (u != fath)	sz[v] += dfsCents(u, v);
        return sz[v];
    }
    void getCentroids(vector <int>* g, int n, vector <int>& res)
    {
        G = g;	dfsCents(1, 0);
        for (int v=1; v<=n and res.size()<2; v++)
        {
            bool isCentroid = sz[v] >= n / 2;
            for (int u : g[v])
                if (n / 2 < sz[u] and sz[u] < sz[v])
					isCentroid = false;         
            if (isCentroid)	res.pb(v);
        }
    }
    vector <int>* tab;
    void dfsVsOnDist(int v, int father, int d)
    {
        tab[d].pb(v);
        for (int u : G[v])
            if (u != father)  dfsVsOnDist(u, v, d + 1);
    }
    void toDigits(int a, vector <int>& t)
    {
        if (a == 0) t.pb(0);
        for (; a != 0; a /= 10)	t.pb(a % 10);
    }
    int fold(vector <int>& t)
    {
        int res = 0;
        for (int i=t.size()-1; i>=0; i--) res = res * 10 + t[i];
        return res;
    }
    bool checkIsomorphism(vector <int>* g0, vector <int>* g1, int n)
    {
        if (n < 3)  return true;
        bool res = false;
        vector <int> cents[2];
        getCentroids(g0, n, cents[0]);
        getCentroids(g1, n, cents[1]);
        if (cents[0].size() != cents[1].size())	return false;
        int roots[2] = {cents[0][0], cents[1][0]};
        bool newVertex = false;
        if (cents[0].size() != 1)
        {
            roots[0] = roots[1] = ++n;
            newCentroid(n, cents[0][0], cents[0][1], g0, true);
            newCentroid(n, cents[1][0], cents[1][1], g1, true);
            newVertex = true;
        }
        G = g0, tab = vsOnDist[0];
        dfsVsOnDist(roots[0], 0, 0);
        G = g1, tab = vsOnDist[1];
        dfsVsOnDist(roots[1], 0, 0);       
        int maxD = 0;
        FOR(i, 1, n+1)
            if (!vsOnDist[0][i].empty() or !vsOnDist[1][i].empty())
                maxD = i;
            else break;
        FOR(s, 0, 2) fill(id[s] + 1, id[s] + n + 1, -1);
        for (int d=maxD; d>=0; d--)
        {
            int levelSize = vsOnDist[0][d].size();
            if (levelSize != vsOnDist[1][d].size())	goto End;
            FOR(s, 0, 2)
            {
                G = (s == 0 ? g0 : g1);
                vector <int>& level = vsOnDist[s][d];
                vector <int>* currL = L[s];
                int* currId = id[s];
                FOR(i, 0, levelSize)
                {
                    int v = level[i], tempSize = 0;
                    for (int u : G[v])
                        if (currId[u] != -1)
                          toDigits(currId[u], tempSeq[tempSize++]);
                    posSort(tempSeq, tempSize, order0);
                    for (int ind : order0)
                    {
                        currL[i].pb(fold(tempSeq[ind]));
                        tempSeq[ind].resize(0);
                    }
                    order0.resize(0);
                }
            }
            posSort(L[0], levelSize, order0);
            posSort(L[1], levelSize, order1);
            int newIdsCtr = 0;
            vector <int> &lev0 = vsOnDist[0][d], &lev1 = vsOnDist[1][d];
            FOR(i, 0, levelSize)
            {
                int ind0 = order0[i], ind1 = order1[i];
                if (L[0][ind0] != L[1][ind1])	goto End;
                int prevInd = i == 0 ? -1 : order0[i - 1];
                if (i > 0 and L[0][prevInd] != L[0][ind0])
                    newIdsCtr++;
                int v0 = lev0[ind0], v1 = lev1[ind1];
                id[0][v0] = id[1][v1] = newIdsCtr;
            }
            FOR(i, 0, levelSize) FOR(s, 0, 2)	L[s][i].resize(0);   
            order0.resize(0); order1.resize(0);
        }
        res = true;	End:
        if (newVertex)
        {
            newCentroid(n, cents[0][0], cents[0][1], g0, false);
            newCentroid(n, cents[1][0], cents[1][1], g1, false);
        }
        clear(n);	return res;
    }
};
```
# Suffix array
```cpp
struct SuffixArray
{
	int temp[maxN], inds[maxN], cnt[maxN], Tglobal[maxN * 4];
	int *R, *cmpPtr, brutConst = 6;

	bool cmpSort(int i, int j)
	{
		int k = 0;
		while (cmpPtr[i+k] == cmpPtr[j+k])	k++;
		return cmpPtr[i+k] < cmpPtr[j+k];
	}
	void brut(int n, int* T, int* res)
	{
		FOR(i, 0, n)	res[i] = i;
		cmpPtr = T;	sort(res, res + n, cmpSort);
	}
	int cntSort(int n, int* T, int k)
	{
		int m = 0;
		if (k == 0)
		{
			for (int i=0; i<n; i+=3)	temp[m++] = i;
			for (int i=1; i<n; i+=3)	temp[m++] = i;
		}
		else for (int i=2; i<n; i+=3)	temp[m++] = i;
		for (int j=2-k; j>=0; j--)
		{
			FOR(i, 0, m)
			{
				int ind = temp[i];
				int v = j & k ? R[ind + 1] : T[ind + j];
				cnt[v]++;
			}
			for (int i=1; cnt[i-1]!=m; i++)	cnt[i] += cnt[i-1];
			for (int i=m-1; i>=0; i--)
			{
				int ind = temp[i];
				int v = j & k ? R[ind + 1] : T[ind + j];
				inds[--cnt[v]] = ind;
			}
			fill(cnt, cnt + n + 1, 0);
			if (j != 0)	FOR(i, 0, m)
				temp[i] = inds[i];
		}
		return m;
	}
	inline bool differ(int* T, int i, int j)
	{	return T[i+2]^T[j+2] | T[i+1]^T[j+1] | T[i]^T[j];	}
	
	inline int newInd(int i, int p)
	{	return i / 3 + i % 3 * p;	}
	
	void calcRanks(int* sa, int n, int d=0)
	{	FOR(i, 0, n)	R[sa[i]] = i+d;	}
	
	bool cmpMerge(int i, int j)
	{
		for (; true; i++, j++)
		{
			if (cmpPtr[i] != cmpPtr[j])	return cmpPtr[i] < cmpPtr[j];
			if (i % 3 != 2 and j % 3 != 2)	return R[i] < R[j];
		}
	}
	
	void ks(int n, int* T, int* res)
	{
		if (n < brutConst)
		{	brut(n, T, res);	return;	}
		int m = cntSort(n, T, 0), p = (n+2)/3+1;
		int *newT = T + n+2, *newRes = res + n/3;
		newT[p-1] = 1, newT[m+1] = newT[m+2] = 0;
		for (int i=0, ctr=2; i<m; i++)
		{
			if (i != 0 and differ(T, inds[i-1], inds[i]))	ctr++;
			newT[newInd(inds[i], p)] = ctr;
		}
		ks(m + 1, newT, newRes - 1);
		FOR(i, 0, m)
			newRes[i] = newRes[i] < p ? newRes[i] * 3 : (newRes[i] - p)*3 + 1;
		calcRanks(newRes, m, 1); R[n] = 0;
		int k = cntSort(n, T, 1);
		cmpPtr = T;
		merge(newRes, newRes+m, inds, inds+k, res, cmpMerge);
	}
	void suffixArray(char* T, int n, int* sa, int* lcp, int* ranks)
	{
		R = ranks;
		FOR(i, 0, n)	Tglobal[i] = (int)T[i] + 1;
		Tglobal[n] = Tglobal[n+1] = 0;
		n < 256 ? brut(n, Tglobal, sa) : ks(n, Tglobal, sa);
		calcRanks(sa, n);
		for (int i=0, q=0; i<n; i++)
		{
			if (R[i] == n - 1)	continue;
			int j = sa[R[i] + 1];
			while (Tglobal[i + q] == Tglobal[j + q])	q++;
			lcp[R[i]] = q;
			if (q != 0)	q--;
		}
	}
};
```
# Congruence solver
```cpp
struct Congruence_solver
{
    long long extGcd(long long a, long long b, long long& x, long long& y)
	{
		if (b == 0)
		{   x = 1; y = 0; return a;	}
		long long gcd = extGcd(b, a % b, y, x);
		y -= a / b * x;
		return gcd;
	}
	//assert(nww(mod)) miesci sie w long long
    pair <long long, long long> congruence_solver(long long* r, long long* mod, int n)
    {
        long long restGlobal = 0, modGlobal = 1;
        FOR(i, 0, n)
        {
            long long x, y, gcd = extGcd(modGlobal, mod[i], x, y);
            if ((restGlobal - r[i]) % gcd != 0)	return {0, 0};

            long long m1 = modGlobal / gcd, m2 = mod[i] / gcd;
            modGlobal = m1 * m2 * gcd;
			restGlobal = restGlobal * m2 * y + r[i] * m1 * x;// overflow?
			restGlobal = myMod(restGlobal, modGlobal);
        }
        return {restGlobal, modGlobal};
    }
};
```
# UnionSepOffline
```cpp
struct UnionSepOffline // qlogqlogn
{
	int F[maxN], sz[maxN], t, offset, qbegin, qend;
	bool* res;
	map <PII, int> birth;	
	pair <PII, int> Q[maxT];
	vector <PII> tree[maxTs]; // pot2 >= t*2
	#define UNFOLD(p, a, b)	int a = find(p.first), b = find(p.second)
	int find(int a)
	{	while (F[a] != a)	a = F[a];	return a;	}
	void onion(PII& p)
	{
		UNFOLD(p, a, b);
		if (sz[a] < sz[b])	swap(a, b);
		if (a != b)			F[b] = a, sz[a] += sz[b];
		p = {a, b};
	}
	void add(int v, int left, int right)
	{
		if (left >= qend or right <= qbegin) return;
		if (left >= qbegin and right <= qend)
		{
			tree[v].pb(Q[qbegin - offset].first);
			return;
		}
		add(v * 2, left, (left + right) / 2);
		add(v*2+1, (left + right) / 2, right);
	}
	void dfs(int v)
	{
		for (auto& p : tree[v])	onion(p);
		if (v < offset) dfs(v * 2), dfs(v*2+1);
		else
		{
			int i = v - offset;
			if (Q[i].second == 0)
			{
				UNFOLD(Q[i].first, a, b);
				res[i] = a == b;
			}
		}
		for (int i=tree[v].size()-1; i>=0; i--)
		{
			int a,b; tie(a,b) = tree[v][i];
			if (a != b)		F[b] = b, sz[a] -= sz[b];
		}
	}
	// wierzch. ind od 1, czas od 0| event: <<para wierzch.>, smierc kraw./0-query>
	void symulate(int n, bool* Rout)
	{
		res = Rout;
		for (offset = 1; offset < t; offset *= 2);
		FOR(i, 1, n+1)	F[i] = i, sz[i] = 1;
		FOR(i, 0, t)	if (Q[i].second != 0)
		{
			qbegin = i + offset;
			qend = Q[i].second + offset;
			add(1, offset, offset*2);
		}
		dfs(1);
	}
	bool dodaj(int a, int b)
	{
		if (b < a)	swap(a, b);
		auto it = birth.find({a, b});
		if (it != birth.end() and it->second != -1)	return false;
		Q[t].first = {a, b};
		birth[{a, b}] = t++;
		return true;			// musi zostac zabita
	}
	void zabij(int a, int b)	// nie bedzie jej od momentu t wlacznie
	{
		if (b < a)	swap(a, b);
		int start = birth[{a, b}];		// kiedys byla >=1 raz dodana
		if (start == -1)	return;
		Q[start].second = t;
		birth[{a, b}] = -1;
	}
	void query(int a, int b)
	{	Q[t++].first = {a, b};	}
	void clean()
	{
		FOR(i, 1, offset*2)	tree[i].clear();
		FOR(i, 0, t)		Q[i].second = 0;
		t = 0;	birth.clear();
	}
};
```
# Dio
```
struct Dio
{	//zachowuja znak
	long long chopy(long long a, long long b, long long m)
	{
		if (b < 0)	a *= -1, b *= -1;
		long long res = 0;
		for (; b; b>>=1)
		{
			if (b & 1)	res = (res + a) % m;
			a = a * 2 % m;
		}
		return res;
	}
	//assert a,b>=0, |a|,|b|,|c|<=3*10^18
	//gdy a,b!=0, to rozwiazania to x-k*b/g, y+k*a/g,
	//zwracane x, y ma najmniejszy modul roznicy
	bool diophEq(long long a, long long b, long long c, long long& x, long long& y)
	{
		if (a == 0 and b == 0)
		{	x = y = 0;	return c == 0;	}
		if (a == 0 or b == 0)
		{
			x = y = c / max(a, b);
			return c % max(a, b) == 0;
		}
		long long g = extEuc(a, b, x, y);
		if (c % g != 0)	return false;
		long long dx = c / a;
		c -= dx * a;
		long long dy = c / b;
		c -= dy * b;
		x = dx + chopy(x, c / g, b);
		y = dy + chopy(y, c / g, a);
		long long p = y - x, q = (a + b) / g;
		long long k = (p < 0 and p % q != 0) ? p / q - 1 : p / q;	
		x += b / g * k;  y -= a / g * k;
		if (llabs(x - y + (a + b) / g) < llabs(x - y))
			x += b / g, y -= a / g;
		return true;	
	}
};
```
# SuffixAut
```cpp
struct SuffixAut
{
	int link[maxN], len[maxN], trans[maxN][Alph], num, last;
	void init()	// init za kazdym razem, clear przy bonusie
	{
		FOR(i, 0, Alph) trans[0][i] = trans[maxN-1][i] = -1;
		link[maxN-1] = last = 0;
		link[0] = -1;
		num = 1;
	}
	void cp(int a, int b)
	{
		copy(trans[b], trans[b] + Alph, trans[a]);	link[a] = link[b];
	}
	void add(char cc)
	{
		int p = last, c = cc-'a';
		cp(num, maxN-1);
		len[num] = len[last] + 1;
		last = num++;
		while (p != -1 and trans[p][c] == -1)
			trans[p][c] = last, p = link[p];
		if (p == -1)
			return;
		int q = trans[p][c];
		if (len[q] == len[p] + 1)
		{
			link[last] = q;
			return;
		}
		int clone = num++;
		cp(clone, q);
		len[clone] = len[p] + 1;
		link[q] = link[last] = clone;
		while (p != -1 and trans[p][c] == q)
			trans[p][c] = clone, p = link[p];
	}
	int jp[maxL][maxN], card[maxN], sufState[maxN];
	vector <int> G[maxN];
	bool terminal[maxN];
	void clear()
	{
		FOR(i, 0, num)
		{
			card[i] = sufState[i] = terminal[i] = 0;
			G[i].resize(0);
		}	
	}
	void dfs(int v)
	{
		for (int u : G[v])
			dfs(u),	card[v] += card[u];
	}
	void bonus()	// liczy link-tree, sufState, card, terminal, jp
	{
		FOR(i, 1, num)
		{
			G[link[i]].pb(i);
			jp[0][i] = link[i];
		}
		jp[0][0] = 0;
		FOR(lg, 1, maxL) FOR(i, 0, num)
			jp[lg][i] = jp[lg-1][jp[lg-1][i]];
		int v = 0;
		FOR(i, 0, n)
		{
			v = trans[v][S[i] - 'a'];	//	S - tekst 0-ind
			sufState[i] = v;
			card[v] = 1;
		}
		dfs(0);
		card[0] = 0;
		for (; v != -1; v = link[v])
			terminal[v] = true;
	}
	int getState(int a, int b)	//0-ind, [a,b]
	{
		int c = b - a + 1;
		int v = sufState[b];
		for (int i=maxL-1; i>=0; i--)
			if (len[jp[i][v]] >= c)
				v = jp[i][v];
		return v;
	}
};
```
# LCA
```cpp
struct LCA
{
    pair <int, int> res, INF, T[maxTS];	//mTS >= maxN*4, pot2
    int offset, qbegin, qend, ctr, in[maxN], out[maxN];
    vector <int>* G;
    void min_priv(int v, int a, int b)
    {
        if (a >= qend or b <= qbegin)
            return;
        if (a >= qbegin and b <= qend)
        {	res = min(res, T[v]);	return;		}
        min_priv(v * 2, a, (a+b) / 2);
        min_priv(v*2+1, (a+b) / 2, b);
    }
    void dfs(int v, int h, int father)
    {
        in[v] = ctr;
        T[ctr++] = {h, v};
        for (int u : G[v]) if (u != father)
			dfs(u, h+1, v), T[ctr++] = {h, v};
        out[v] = ctr;
    }
    void init(vector <int>* g, int n, int root)
    {
        for (offset = 1; offset < n*2 - 1; offset *= 2); //;!
        G = g; ctr = offset; INF = {n, n};
        dfs(root, 0, -1);
        FOR(i, ctr, offset*2)			T[i] = INF;
        for (int i=offset-1; i>0; i--)  T[i] = min(T[i * 2], T[i*2+1]);
    }
    int lca(int u, int v)
    {
        res = INF;
        qbegin = min(in[u], in[v]);
        qend = max(out[u], out[v]);
        min_priv(1, offset, offset * 2);
        return res.second;
    }
    int ver_heigth(int v)
    {   return T[in[v]].first;  }
    bool is_anc(int anc, int v)
    {	return in[anc] <= in[v] and out[v] <= out[anc];	}
};
```
# Geometry
```cpp
struct 'Point'
{
	Tp x, y;	int ind;
	Point (Tp a = 0, Tp b = 0, int i = 0)
		: x(a), y(b), ind(i) {}
	Tp operator% (const Point& he) 	const
	{	return x * he.y - he.x * y;	}
	Point operator- (const Point& he)	const
	{	return Point(x - he.x, y - he.y, ind);	}
	Tp len2()	const
	{	return x*x + y*y;	}
	bool operator< (const Point& he)	const
	{
		Tp ilo = (*this) % he;
		if (ilo != 0)			return ilo > 0;
		if (y != 0 or he.y != 0)return y < he.y;
		return x < he.x;	//	!abs
	}
};
int bottomLeftInd(vector <Point>& T)
{	int j = 0;
	FOR(i, 1, T.size())
		if (T[i].y < T[j].y or (T[i].y == T[j].y and T[i].x < T[j].x))
			j = i;		return j;
}		
vector <Point> convex(vector <Point>& P)
{
	Point mv = P[bottomLeftInd(P)];
	FOR(i, 0, P.size())	P[i] = P[i] - mv;
	sort(ALL(P));
	vector <Point> res(1, P[0]);
	FOR(i, 1, P.size())
	{	
		#define LAST(i) res[res.size() - (i)]
		while (res.size() > 1 and (LAST(1) - LAST(2)) % (P[i] - LAST(2)) <= 0)
			res.pop_back();
		res.pb(P[i]);
	}
	return res;
}
pair <int, int> perimeter(vector <Point>& C) // C - convex, |C|>1
{
	pair <int, int> res = {0, 1};
	if (C.size() == 2)	return res;
	int j = 1;	C.pb(C[0]);
	Tp dst2 = 0;
	FOR(i, 1, C.size())
	{
		T a = C[i].y - C[i-1].y, b = C[i-1].x - C[i].x, c = -a*C[i].x - b*C[i].y;
		#define DIST(k)	abs(a * C[k].x + b * C[k].y + c)	//uwaga na abs
		#define NX(k)	((k+1) % C.size())
		while (DIST(NX(j)) >= DIST(j))	j = NX(j);
		Tp cand = (C[i] - C[j]).len2();
		if (dst2 < cand)
			dst2 = cand, res = {i, j};
	}
	C.pop_back();
	res.first %= C.size();
	return res;
}
vector <Point> minkowskiSum(vector <Point>& A, vector <Point>& B)	// clockwise
{
	vector <Point> res;
	int i0 = bottomLeftInd(A), j0 = bottomLeftInd(B), i = i0, j = j0;
	do
	{	res.pb(A[i] + B[j]);
		int ni = (i + 1) % A.size(), nj = (j + 1) % B.size();
		long long ilo = (A[ni] - A[i]) % (B[nj] - B[j]);
		if (ilo >= 0)	j = nj;
		if (ilo <= 0)	i = ni;
	}
	while (i != i0 or j != j0);		return res;
}
bool intersect(const Segment& A, const Segment& B)
{
	Point P[2][2] = {{A.first, A.second}, {B.first, B.second}};
	FOR(i, 0, 2) FOR(j, 0, 2)
		if (P[i][j].inside(P[i^1][0], P[i^1][1]))
			return true;
	long long dir[2][2];
	FOR(i, 0, 2) FOR(j, 0, 2)
		dir[i][j] = (P[i][1] - P[i][0]) % (P[i^1][j] - P[i][0]);
	return sgn(dir[0][0]) * sgn(dir[0][1]) + sgn(dir[1][0]) * sgn(dir[1][1]) == -2;
}
pair <Point, Point> crcLineInter(const Crc& C, Point a, Point b)
{
	a -= C.pt, b -= C.pt;
	double dx = b.x - a.x, dy = b.y - a.y;
	double d2 = kw(dx) + kw(dy), ilo = a % b;
	double w = d2 * kw(C.r) - kw(ilo);	// rzut punktu (C) na prostą (ab) -> w=0
	if (w < -E)
		return {{INF, INF}, {INF, INF}};
	w = sqrt(max(w, 0.0));
	a.x = ilo * dy + w * dx;
	b.x = ilo * dy - w * dx;
	if (dy < 0)		swap(a.x, b.x);
	
	a.y = -ilo * dx + w * fabs(dy);
	b.y = -ilo * dx - w * fabs(dy);
	a *= 1.0/d2;	a += C.pt;
	b *= 1.0/d2;	b += C.pt;
	return {a, b};
}
vector <Point> crcInter(const Crc& Ci, const Crc& Cj)	//assert inter nonEmpty
{
	long long dx = Ci.x - Cj.x, dy = Ci.y - Cj.y, d2 = kw(dx) + kw(dy);
	double D = sqrt(d2);
	double X = (d2 + kw(Cj.r) - kw(Ci.r)) / (2.0 * D);
	double Y = sqrt(kw(Cj.r) - kw(X));
	vector <Point> res({Point(X, Y), Point(X, -Y)});
	double c = dx / D, s = dy / D;
	FOR(k, 0, 2)
		res[k] = Point(res[k] % Point(s,c), res[k] % Point(-c,s)) + Cj.pt;
	return res;
}
void cntZ(char* T, int n, int* Z)
{
	int a = 0, b = 0;
	FOR(i, 1, n)
	{
		if (i <= b)
			Z[i] = min(Z[i - a], b - i + 1);
		while (i + Z[i]<n and T[i + Z[i]] == T[Z[i]])
			Z[i]++;
		if (i + Z[i] - 1 > b)
			a = i, b = i + Z[i] - 1;
	}
}
```
# Dominator tree
```cpp
struct Dominator_tree
{
    vector <int>* G;
    vector <int> Ginv[maxN], bucket[maxN]; 
    int inctr, in[maxN], ininv[maxN], sdom[maxN],
		idom[maxN], parent[maxN], anc[maxN], F[maxN];

    int find(int v, bool flag = true)
    {
        if (anc[v] == v)
			return flag ? v : 0;
        int u = find(anc[v], false);
        if (u == 0) return F[v];
        if (sdom[u] < sdom[F[v]])
			F[v] = u;
        anc[v] = anc[anc[v]];
        return F[v];
    }
    void dfs(int v)
    {
        in[v] = ++inctr, ininv[inctr] = v;
        for (int u : G[v])
        {
            if (in[u] == 0)
				dfs(u), parent[in[u]] = in[v];
            Ginv[in[u]].pb(in[v]);
        }
    }
    void clear(int n)	//	mozna olac jesli uzywamy tylko raz
    {
        FOR(i, 1, inctr+1)
            Ginv[i].resize(0), bucket[i].resize(0);
        fill(idom, idom + inctr + 1, 0);
        fill(F, F + inctr + 1, 0);
        fill(in, in + n + 1, 0);	inctr = 0;
    }
    void genDomTree(vector <int>* g, int n, int s, vector <int>* res)
    {
        G = g;  dfs(s);
        FOR(i, 1, inctr+1)	anc[i] = sdom[i] = i;
        for (int i=inctr; i>1; i--)
        {
            for (int v : Ginv[i])
				remin(sdom[i], sdom[find(v)]);
            bucket[sdom[i]].pb(i);
            int fath = parent[i];
            anc[i] = fath, F[i] = i;
            for (int v : bucket[fath])
            {
                int u = find(v);
                idom[v] = (sdom[u] == sdom[v] ? fath : u);
            }
            bucket[fath].resize(0);
        }
        FOR(i, 2, inctr+1)
        {
            int& id = idom[i];
            if (id != sdom[i])
				id = idom[id];
            res[ininv[id]].pb(ininv[i]);
        }
        clear(n);
    }
};
```
# Aho
```cpp
struct Aho
{	/*usage: clean(),add(),calcF(),query(). query() zwraca pary postaci
	<KONIEC wystapienia, ind. klucza>. Teksty i klucze ind. od zera*/
	int n, T[maxN][Alph], F[maxN], N[maxN], o[maxN];
	queue <int> Q;
	void add(char* t, int m, int ind)
	{
		int v = 1;
		FOR(i, 0, m)
		{
			int& u = T[v][t[i] - 'a'];
			if (u == 0)	u = ++n;
			v = u;
		}
		o[v] = ind + 1;	
	}
	void calcF()
	{
		F[1] = 1;
		FOR(c, 0, Alph)
		{
			int& u = T[1][c];
			if (u == 0)	u = 1;
			else 		F[u] = 1, Q.push(u);
		}
		
		while (!Q.empty())
		{
			int v = Q.front();	Q.pop();
			FOR(c, 0, Alph)
			{
				int &u = T[v][c], w = F[v];
				if (u == 0)
				{
					u = T[w][c];
					continue;
				}
				F[u] = T[w][c];
				N[u] = o[F[u]] == 0 ? N[F[u]] : F[u];
				Q.push(u);
			}
		}
	}
	void query(char* t, int m, vector <pair <int, int> >* res)
	{
		int v = 1;
		FOR(i, 0, m)
		{
			v = T[v][t[i] - 'a'];
			int u = o[v] == 0 ? N[v] : v;
			for (; u != 0; u = N[u])
				res.pb({i, o[u]-1});
		}
	}
	void clean(int v = 1)
	{
		FOR(c, 0, Alph)
		{
			if (T[v][c] > 1)	clean(T[v][c]);
			T[v][c] = 0;
		}
		F[v] = N[v] = o[v] = 0;	n = 1;		
	}
};
```
# FFT
```cpp
struct FFT //maxN - potega2
{
	#define CMPX complex <double>	//long double - mozliwe tle
    CMPX A[maxN], B[maxN], C[maxN], omega[maxN + 1];
    unsigned int bitrev[maxN];
    unsigned int builtin_bitrev(unsigned int M)
    {
        static unsigned int m[5] =
        {0xFFFF0000, 0xFF00FF00, 0xF0F0F0F0, 0xCCCCCCCC, 0xAAAAAAAA};
        for (int i=0, d=16; i<5; i++, d>>=1)
            M = ((M & m[i]) >> d) | ((M & ~m[i]) << d);
        return M;
    }
    void init()
    {
    	FOR(i, 0, maxN)	bitrev[i] = builtin_bitrev(i);
    	for (int d=1; d<maxN; d*=2)
    	{
    		double ang = M_PI / (maxN / (d*2));
    		for (int i=1; d*i<maxN; i+=2)
    			omega[d*i] = CMPX(cos(ang*i), sin(ang*i));
    	}
    	omega[0] = omega[maxN] = CMPX(1, 0);
    }
    void fft_iter(CMPX* a, CMPX* res, int n, int dir)
    {
        int w = __builtin_clz(n) + 1;
        FOR(i, 0, n)	res[bitrev[i] >> w] = a[i];
        for (int len=2, lg=1; len<=n; len*=2, lg++)
        {
            int d = (maxN >> lg) * dir;
            for (CMPX* t = res; t != res + n; t += len)
            {
                int j = dir == 1 ? 0 : maxN;
                FOR(i, 0, len/2)
                {
                    CMPX x = t[len/2 + i] * omega[j];
                    t[len/2 + i] = t[i] - x;
                    t[i] += x;	j += d;
                }
            }
        }
    }
    void mult_polys_fft(vector <int>& a, vector <int>& b, vector <int>& c)
    {
        int g = 1, n = a.size(), m = b.size(); c.resize(n + m);
        while (g < c.size())   g *= 2;
        FOR(i, 0, n)    A[i] = CMPX(a[i], 0);
        FOR(i, n, g)    A[i] = CMPX(0, 0);
        fft_iter(A, B, g, 1);
        FOR(i, 0, m)    A[i] = CMPX(b[i], 0);
        FOR(i, m, g)    A[i] = CMPX(0, 0);
        fft_iter(A, C, g, 1);
        FOR(i, 0, g)    C[i] *= B[i];
        fft_iter(C, A, g, -1);
        FOR(i, 0, c.size())	c[i] = A[i].real() / g + 0.5;
    }
};
```
# SOS
```cpp
void SOS(int* S, int n) // uwzglednia zbior pusty, S - in/out
{	
	FOR(i, 0, n) FOR(m, 0, 1<<n)
		if (ithBit(m, i))
			S[m] += S[m ^ 1<<i];
}
```
# S_2SAT
```cpp
struct S_2SAT
{    //   T -> tablica klauzul indeksowana od zera, gdzie:
     //     -literal x<0 -> negacja -x, x>0 -> x
     //     -zmienne indeksowane od 1
     //   m -> #klauzul, n -> #zmiennych
    int inCtr, sccCtr, low[maxN], in[maxN], scc[maxN], S[maxN], tp;
    vector <int> G[maxN];
    int dfs(int v)
    {
        low[v] = in[v] = ++inCtr;  S[tp++] = v;
        for (int u : G[v])	if (in[u] >= 0)
        	low[v] = min(low[v], in[u] == 0 ? dfs(u) : in[u]);
        if (in[v] != low[v])    return low[v];
        for (int u=-1; u!=v;)
        {
            u = S[--tp];
            scc[u] = sccCtr;
            in[u] *= -1;
        }
        sccCtr++;	return low[v];
    }
    int trans(int a)
    {	return a < 0 ? -2*a - 1 : 2*a - 2;	}
    void clear(int n)
    {
        FOR(i, 0, n)
            G[i].resize(0), low[i] = in[i] = scc[i] = 0;
        inCtr = sccCtr = 0;
    }
    bool f_2SAT(pair <int, int>* T, int m, int n, bool* res)
    {
        n *= 2;
        FOR(i, 0, m)
        {
        	int u = trans(T[i].first), v = trans(T[i].second);
        	G[u^1].pb(v); G[v^1].pb(u);
        }
        FOR(i, 0, n)	if (in[i] == 0)   dfs(i);
        int *neg = low, *sccState = in;
        for (int i=0; i<n; i+=2)
        {
            int a = scc[i], b = scc[i+1];
            neg[a] = b, neg[b] = a;
            if (a == b) {	clear(n); return false;	}
        }
        FOR(i, 0, sccCtr)
            if (sccState[i] < 0)
                sccState[i] = 1, sccState[neg[i]] = 0;
        for (int i=0; i<n; i+=2)
            res[i/2+1] = sccState[scc[i]] == 1;
        clear(n); return true;
    }
};
```
# Fenwick
```cpp
struct Fenwick
{
	void updt(int i, long long val)
	{	for (i++; i<=ran; i+=(-i)&i)	T[i] += val;	}
	long long sum(int i)	// [0,i)
	{
		long long ret = 0;
		for (; i!=0; i&=i-1)	ret+=T[i];
		return ret;
	}
};
```
# Matching
```cpp
struct Matching
{
    int *part, n, m, visctr, ser, dist[maxN], vis[maxN];
    int qb, Q[maxN];
    vector <int>* G;
	void ins(int v, int d)
	{
		dist[v] = d; vis[v] = visctr;
		if (d <= ser)	Q[qb++] = v;
	}	
    bool bfs()
    {
        visctr++;
        ser = n + m; qb = 0;
        FOR(i, 1, n+1)
			if (part[i] == 0) ins(i, 0);
        for (int qf = 0; qf != qb; qf++)
        {
            int v = Q[qf];
            for (int w : G[v])
            {
                int u = part[w];
                if (vis[u] == visctr)	continue;
                if (u == 0)
                {	remin(ser, dist[v]+1);	continue;	}
				ins(u, dist[v] + 2);
            }
        }
        visctr++;	return ser != n + m;
    }
    bool dfs(int v)
    {
        vis[v] = visctr;
        if (dist[v] > ser)	return false;
        for (int w : G[v])
        {
            int u = part[w];
            if (u == 0 or
				(vis[u] != visctr and dist[u] == dist[v] + 2 and dfs(u)))
            {	match(w, v); return true;	}
        }
        return false;
    }
    int matching(vector <int>* Gin, int nn, int mm, int* partout)
    {
        G = Gin; n = nn; m = mm; part = partout;
        while (bfs())  FOR(i, 1, n+1)
			if (part[i] == 0) dfs(i);
        int res = 0;
        FOR(i, 1, n+1)	res += part[i] != 0;
        return res;
    }
};
```
# Gray codes
```cpp
// n - rozmiar zbioru, którego podzbiory będą przeglądane
// T - ind. od 0. Który bit zmienić by przejść do kolejnej maski
void GrayCodes(int n, int* T)
{
	int q = 1, b = -1;
	FOR(i, 0, 1<<n)
	{
		if (i+1 == q)	q *= 2, T[i] = ++b;
		else 			T[i] = T[i - q/2];
	}
};
```
# MaxFlowRelabelToFront
```cpp
struct Max_flow_relabel_to_front
{
    // uwaga: funkcja modyfikuje tablicę cap
    // uwaga2: G nie może zawierać krawędzi wielokrotnych ani cykli długości 2
    long long excess[maxN];
    int H[maxN], nbr[maxN];
    list <int> L;
    long long maxflow (VI* G, LL cap[][maxN], int n, int source, int target)
    {
    	FOR(i, 1, n+1)	excess[i] = H[i] = nbr[i] = 0;
        L.clear();
        H[source] = n;
        for (int u : G[source])
        {
            excess[u] = cap[u][source] = cap[source][u];
            excess[source] -= cap[source][u];
            cap[source][u] = 0;
        }
        FOR(v, 1, n+1)	if (v != source and v != target)	L.pb(v);
        for (auto it = L.begin(); it != L.end(); it++)
        {
            int v = *it, oldH = H[v];
            while (excess[v] > 0)
            {
                if (nbr[v] == G[v].size())
                {
                    H[v] = n * 2;
                    for (int w : G[v])	if (cap[v][w] > 0)
						H[v] = min(H[v], H[w]);
                    H[v]++;	nbr[v] = 0;	continue;
                }
                int u = G[v][nbr[v]];
                if (cap[v][u] > 0 and H[u] < H[v])
                {
                    long long d = min(excess[v], cap[v][u]);
                    excess[v] -= d; cap[v][u] -= d;
                    excess[u] += d; cap[u][v] += d;
                }
                else nbr[v]++;
            }
            if (oldH < H[v])
                L.erase(it), L.push_front(v), it = L.begin();
        }
        long long res = 0;
        for (int u : G[source])	res += cap[u][source];
        return res;
    }
};
```
# Hash
```cpp
struct Hash
{
    long long H[maxN], pows[maxN], mod, p;
    void initialize (char* T, int n)
    {
        mod = 100000000000000099LL; //10^17+99
        p = 29, base = 8;
        pows[0] = 1; H[n] = 0;
        FOR(i, 1, n+1)
            pows[i] = pows[i - 1] * p % mod;
        for (int i=n-1; i>=0; i--)
            H[i] = (H[i + 1] * p + (T[i]-'a') + 1) % mod;
    }
    long long hash(int a, int b)	// hash podsłowa T[a...b]
	{	b++; return myMod(H[a] - H[b] * pows[b-a]);	}
};
```
# MinDist
```cpp
struct MinDist
{	
	Punkt temp1[maxN], temp2[maxN];
	int bins(int n, Punkt* T, int bord) // ind. 1. punktu o x > border
	{
		int begin = -1, end = n;
		while (end - begin > 1)
		{
			int mid = (begin + end) / 2;
			bord < T[mid].x ? end = mid : begin = mid;
		}
		return end;
	}
	bool cmp1(const Punkt& A, const Punkt& B)
	{	return A.x == B.x ? A.y > B.y : A.x < B.x;	}
	bool cmp2(const Punkt& A, const Punkt& B)
	{	return A.y == B.y ? A.x < B.x : A.y > B.y;	}
	
	long long go(int n, Punkt* T) //przed wywolaniem posortuj wg cmp1
	{
		long long res = INF;
		if (n < 6)
		{
			FOR(i, 0, n) FOR(j, i+1, n)	remin(res, T[i].dist(T[j]));
			return res;
		}
		int n1 = n / 2, n2 = n - n1;
		Punkt* T1 = T, *T2 = T + n1;
		res = min(go(n1, T1), go(n2, T2));
		long long d = sqrt(res);
		long long x1 = T1[n1 - 1].x, x2 = T2[0].x;

		int begin = bins(n1, T1, (x1 + x2) / 2 - d);
		FOR(i, begin, n1)	temp1[i - begin] = T1[i];
		n1 -= begin;
		sort(temp1, temp1 + n1, cmp2);

		int end = bins(n2, T2, (x1 + x2 - 1) / 2 + d), k = 0;
		FOR(i, 0, end)	temp2[i] = T2[i];
		n2 = end;
		sort(temp2, temp2 + n2, cmp2);
		FOR(i, 0, n1)
		{
			while (k < n2 and temp2[k].y - temp1[i].y > d)	k++;
			FOR(j, 0, min(5, n2-k))
				remin(res, temp1[i].dist(temp2[finger + j]));
		}
		return res;
	}
};
```
# STL++
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree <T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;		//find_by_order() / order_of_key()
	
template <class Key, class Value, class Hash = hash <Key> >
using __fast_unordered_map = gp_hash_table<Key, Value, Hash>;
```
# MaxFlow
```cpp
struct Max_flow
{
	vector <int> *G;
	int source, target, bfsctr, parent[maxN], vis[maxN], Q[maxN];
    long long* cap[maxN];
	bool bfs()
	{
		vis[source] = ++bfsctr;	Q[0] = source;
		for (int qF=0, qB=1; qF != qB; qF++)
		{
			int v = Q[qF];
			for (int u : G[v])
			{
				if (vis[u] == bfsctr or cap[v][u] <= 0)	continue;
				vis[u] = bfsctr; parent[u] = v;
				Q[qB++] = u;
				if (u == target)
				{	qF = qB - 1;	break;	}
			}
		}
		return vis[target] == bfsctr;		
	}
	long long maxflow(vector <int>* Gin, long long Cin[maxN][maxN],
				int n, int src, int trg)	//Cin bedzie modyfikowana
	{
		G = Gin; source = src; target = trg;
        FOR(i, 0, n+1)    cap[i] = Cin[i];
		long long res = 0;
		while (bfs())
		{
			long long mc = INF;
			for (int v = target; v != source; v = parent[v])
				mc = min(mc, cap[parent[v]][v]);
			for (int v = target; v != source; v = parent[v])
				cap[parent[v]][v] -= mc, cap[v][parent[v]] += mc;
			res += mc;
		}
		return res;
	}
};
```
# Miller-Rabin
```cpp
struct Miller_rabin_test
{	
	long long mod;
    bool witness(long long w)
    {
    	long long x = mod - 1, prev = x, k = __builtin_ctzll(x);
        __int128_t a = qpow(w, x>>k);
        while (a != 1 and k--)
        	prev = a, a = a * a % mod;
       	return prev != x or a != 1;
    }
    bool prime(long long n)
    {
        if (n < 2)  return false;	if (n < 4)  return true;
        mod = n;	int s = 15;
        while (s--)
        {
            long long a = 1;
            while (a == 1 or a % 2 == 0)	a = 1ll*rand()*rand()%n;
            if (witness(a))	return false;
        }
        return true;
    }
};
```
# Rho-Pollard
```cpp
struct Rho_Pollard
{
    long long mod, c;
    vector <long long> res;
    Miller_rabin_test alg;
    long long f(__int128_t x)
    {  
    	return ((x * x - c) % mod + mod) % mod;
    }
    void go(long long n)
    {
        for (; n%2 == 0; n /= 2) res.pb(2);
        if (n <= 1000000)	return;
        if (n > 1000000000000LL and alg.prime(n))    // 10^12
        {	res.pb(n);	return;	}
        
        mod = n;
        for (c=1; c<=5; c+=2)
        {
            long long x = 2, y = 2, d = 1;
            while (d == 1)
            {
                x = f(x); y = f(f(y));
                d = __gcd(llabs(x - y), n);
            }           
            if (d < n)
            {
				go(d); go(n / d); 
				return;
			}
        }
        res.pb(n);
    }//	czynniki <= 10^6 nie musza byc pierwsze
    vector <long long> rhopollard(long long n)	
    {
        res.clear();
        if (n < 2)  return res;
        go(n); sort(ALL(res));
        return res;
    }
};
```
# VerCover
```cpp
struct VerCover
{
    vector <int>* g;
    int* part;
    bool* res;
    void dfs(int v)
    {
        for (int u : g[v])
            if (part[u] != 0 and !res[u])
            {	res[u] = true;	dfs(part[u]);	}
    }
    //n - # wierzchołków w 1. zbiorze.
    void cover(vector <int>* g, int n, int* Pin, bool* Rout)
    {
        g = g, part = Pin, res = Rout;
        FOR(i, 1, n+1)
			if (part[i] == 0)
				dfs(i);
        FOR(i, 1, n+1)
            if (part[i] != 0 and !res[i] and !res[part[i]])
                res[i] = true;
    }
};
```
# Convolution xor
```cpp
struct Convolution_xor
{
    void tf(int* a, int* res, int n)
    {
        copy(a, a + n, res);
        for (int len=1; len<n; len*=2)
            for (int* t=res; t!=res+n; t+=len*2)
                FOR(i, 0, len)
                {
                    int u = t[i];
                    subMod(t[i], t[len + i]);
                    addMod(t[len + i], u);
                }
    }
    void utf(int* a, int n)
    {
        for (int len=n/2; len>0; len/=2)
            for (int* t=a; t!=a+n; t+=len*2)
                FOR(i, 0, len)
                {
                    int u = t[len + i];
                    subMod (t[len + i], t[i]);
                    multMod(t[len + i], (mod+1)/2);
                    addMod (t[i], u);
                    multMod(t[i], (mod+1)/2);
                }
    }
    int temp[maxN];
    void convolution(int*a, int* b, int* c, int n)
    {
        tf(a, temp, n);
        tf(b, c, n);
        FOR(i, 0, n)
			multMod(c[i], temp[i]);
        utf(c, n);
    }
};
```
# Machenar
```cpp
struct Machenar
{
	void countR(char* T, int* r, int n, int parity)
    {
        int p = 0;
        FOR(i, 1, n+1)
        {
            if (p + r[p] < i)
				p = i;
            r[i] = min(r[p*2 - i], p + r[p] - i);
            while (T[i - r[i] - parity] == T[i + r[i] + 1])
				r[i]++;
            if (p + r[p] < i + r[i])
				p = i;
        }
    }
    // r0 - parzyste, srodek miedzy T[i] a T[i+1]
    
    void machenar(char* T, int* r0, int* r1, int n)	
    {
        char a = T[0], b = T[n + 1];
        T[0] = '@', T[n + 1] = '#';	//! znaki spoza alfabetu
        countR(T, r0, n, 0);
        countR(T, r1, n, 1);
        T[0] = a, T[n + 1] = b;
    }
};
```
# BugNum
```cpp
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
		FOR(i, 0, a.size())
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
		FOR(i, 0, a.size())
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
	BigNum operator* (BigNum& other)
	{
		BigNum res(0);
		vector <int> &b = other.a, &c = res.a;
		c.resize(a.size() + b.size());
		FOR(i, 0, a.size()) FOR(j, 0, b.size())
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
		FOR(i, 0, a.size())
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
```
# Centroid decomposition
```cpp
struct Centroid_Dec
{
	vector <int> *G, *C;
	bool taken[maxN];
	int *d, sz[maxN];
	int dfs(int v, int fat)
	{
		sz[v] = 1;
		for (int u : G[v])
			if (u != fat and !taken[u])
				sz[v] += dfs(u, v);
		return sz[v];
	}	
	int f(int v, int depth)
	{
		int n = dfs(v, -1);
		bool moved = true;
		while (moved)
		{
			moved = false;
			for (int u : G[v])
				if (!taken[u] and n/2 < sz[u] and sz[u] < sz[v])
				{	v = u; moved = true; break;		}
		}
		d[v] = depth;
		taken[v] = true;
		for (int u : G[v])
			if (!taken[u])	C[v].pb(f(u, depth + 1));
		return v;
	}
	int centDec(vector <int>* Gin, vector <int>* Cout, int* dout)
	{
		G = Gin, C = Cout, d = dout;	return f(1, 0);
	}
	void clear() {	fill(taken, taken + maxN, false);	}
};
```
# Gauss
```cpp
struct Gauss
{
    int gauss(long double T[maxN][maxN], int n)
    {
        bool resUnique = true;
        FOR(d, 0, n)
        {
            long double val = T[d][d];
            int rtc = d;
            FOR(i, d+1, n)
                if (ABS(val) < ABS(T[i][d]))
                    val = T[i][d], rtc = i;
            if (ABS(val) < E)   continue;
            if (rtc != d)
                FOR(j, d, n+1)
                    swap(T[d][j], T[rtc][j]);
            FOR(i, 0, n)
            {
                if (i == d) continue;
                val = T[i][d] / T[d][d];
                FOR(j, d, n+1)	T[i][j] -= T[d][j] * val;
            }
            val = T[d][d];
            FOR(j, d, n+1)	T[d][j] /= val;  
        }
        for (int d=n-1; d>=0; d--) if (T[d][d] == 0)
        {
            if (T[d][n] != 0)   return 0;	//brak rozw
            resUnique = false;
        }
        return resUnique ? 1 : 2; // jedyne rozw/wiele, zm. wolne - 0 na przek
    }
};
```
# Discrete logarithm
```cpp
struct Discrete_Logarithm
{
    pair <long long, int> t[maxD];
    int discrete(long long a, long long b)
    {
        int d = sqrt(mod) + 42;
        t[0] = {1, 0};
		FOR(i, 1, d+1)	t[i] = {t[i - 1].first * a % mod, i};
        t[d].first = qpow(t[d].first, mod-2);
        sort(t, t + d);
        FOR(i, 0, d)
        {
            auto find = lower_bound(t, t + d, make_pair(b, 0));
            if (find != t + d and find->first == b)
                return d * i + find->second;
			b = b * t[d].first % mod;
        }
        return -1;
    }
};
```
# HL decomposition
```cpp
struct HL_dec
{
	int *in, *out, *R, *F, inCtr, son[maxN];
	vector <int>* G;
	int dfs0(int v)
	{
		int sz = 1, maxsz = 0, x;
		son[v] = -1;
		for (int u : G[v]) if (u != F[v])
		{
			F[u] = v;
			sz += x = dfs0(u);
			if (maxsz < x)	maxsz = x, son[v] = u;
		}
		return sz;
	}
	void dfs(int v, int myroot)
	{
		in[v] = inCtr++;
		R[v] = myroot;
		if (son[v] != -1)
			dfs(son[v], myroot);
		for (int u : G[v])
			if (u != F[v] and u != son[v])
				dfs(u, u);
		out[v] = inCtr;
	}
	void f(vector<int>* Gin, int* Iout, int* Oout, int* Rout, int* Fout, int rt=1)
	{
		G = Gin, in = inout, R = Rout, F = Fout;
		F[rt] = inCtr = 0;
		in[0] = -1;		dfs0(rt);	dfs(rt, rt);
	}
	void query(int a, int b) // a ^ b
	{
		#define RT R[a]
		for (; in[a] >= in[b]; a = F[RT]) tree.operation(max(in[b], in[RT]), in[a]);
	}
};
```
# HPI
```cpp
namespace HPI
{
	pair <Point, Point>* P;
	Point v[maxN];
	long long A[maxN], B[maxN], C[maxN];
	int inds[maxN];
	#define Ihalf(w) (w.x < 0 or (w.x == 0 and w.y > 0))
	
	bool inHp(int i, const Point& a)
	{		return v[i] % (a - P[i].first) > 0;	}
	
	bool cmp(int i, int j)
	{
		if (Ihalf(v[i]) xor Ihalf(v[j]))
			return Ihalf(v[i]);
		long long ilo = v[i] % v[j];
		return ilo == 0 ? inHp(j, P[i].first) : ilo > 0;
	}	
	void cross(int i, int j, long long& x, long long& y, long long& z)
	{
		x = B[i] * C[j] - B[j] * C[i];
		y = C[i] * A[j] - C[j] * A[i];
		z = A[i] * B[j] - A[j] * B[i];
	}
	bool crossInHp(int i, int j, int k, bool border = false)
	{
		long long x, y, z;
		cross(j, k, x, y, z);
		if (z < 0)	x = -x, y = -y, z = -z;
		long long a = z * (P[i].first % v[i]);
		long long b = Point(x, y) % v[i];
		return border ? a >= b : a > b;
	}
	int jazda(pair <Point, Point>* Pin, int n, vector <int>& res)
	{
		P = Pin;
		FOR(i, 0, n)
		{
			inds[i] = i;
			v[i] = P[i].second - P[i].first;
			A[i] = v[i].y;	B[i] = -v[i].x;
			C[i] = v[i] % P[i].first;
		}
		sort(inds, inds + n, cmp);
		res.pb(inds[0]);
		int s = 0;
		FOR(j, 1, n)
		{
			#define ASparl(a, b)	{	if (!inHp(a, P[b].first))	return 2;	}
			#define ASempty			{	if (!crossInHp(i, L, LL))	return 2;	}
			#define GET(a)			{	res.pb(a);	continue;	}	
			#define ASerase(d)		{	if (crossInHp(L, LL, i, true)) \
							{	d ? res.pop_back(),0 : s++; j--; continue;	}	}
			int i = inds[j], L = res.back();
			long long ilo = v[i] % v[L];
	
			if (ilo > 0)	return 1;
			if (ilo == 0)
			{
				if (Ihalf(v[i]) xor Ihalf(v[L]))
					return inHp(i, P[L].first) ? 1 : 2; //unBD : EP
				else continue;
			}	
			if (res.size() - s == 1)	GET(i);	
			int LL = res[res.size() - 2];	
			ilo = v[i] % v[LL];
			
			if (ilo > 0)	ASempty;
			if (ilo == 0)	ASparl(i, LL);
			if (ilo < 0)	ASerase(1);
			
			L = res[s], LL = res[s+1];
			ilo = v[i] % v[L];
			
			if (ilo == 0)	ASparl(i, L);
			if (ilo <= 0)	GET(i);
			
			ilo = v[i] % v[LL];
			
			if (ilo < 0)	ASempty;
			if (ilo == 0)	ASparl(i, LL);
			if (ilo > 0)	ASerase(0);

			LL = res.back();			
			if (v[LL] % v[L] <= 0 or !crossInHp(i, LL, L, true))
				res.pb(i);
		}
		if (res.size()-s < 3 or v[res.back()] % v[res[s]] <= 0)
			return 1;
		res.erase(res.begin(), res.begin() + s);
		return 0;
	}
	vector <PointR> getPoints(vector <int>& is)
	{
		int n = is.size();
		vector <PointR> res(n);
		FOR(i, 0, n)
		{
			long long x, y, z;
			cross(is[i], is[(i+1)%n], x, y, z);
			res[i] = PointR(1.0*x/z, 1.0*y/z);
		}
		return res;
	}
}
```
# Steiner tree
```cpp
namespace SteinerTree	//	n * 3^t
{
	int dp[maxN][1 << maxT]; // G - ind od 0, brak kraw=INF, Gii = 0.
	int compute(int G[maxN][maxN], int n, int* terms, int t)
	{
		FOR(k, 0, n) FOR(i, 0, n) FOR(j, 0, n)
			remin(G[i][j], G[i][k] + G[k][j]);
		FOR(m, 1, 1<<t)
		{
			FOR(v, 0, n)
			{
				dp[v][m] = INF;
				for (int m2 = m-1 & m; m2 != 0; m2 = m2-1 & m)
					remin(dp[v][m], dp[v][m^m2] + dp[v][m2] - 1);
			}
			if (PPC(m) == 1)	dp[terms[CTZ(m)]][m] = 1;
			
			FOR(v, 0, n) FOR(u, 0, n)
				remin(dp[v][m], G[v][u] + dp[u][m]);			
		}
		return dp[terms[0]][(1<<t) - 1];
	}
}
