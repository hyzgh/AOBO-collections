/************************************************************/
/* 后缀自动机(Tested 8 times)
 * 数组实现，效率较高
 * 开点时才初始化，在多组样例的情况下会比直接memset整个数组快很多，比如HDU4416
 * 时间复杂度：O(n * CHARSET_SIZE)
 * used variables: N, 
 */
const int CHARSET_SIZE = 26;
const int MAXN = N << 1;  // 注意在SAM里面开的数组大小应为MAXN，因为长度为n的字符串最多会有2*n个结点

struct SuffixAutomaton {
	int ch[MAXN][CHARSET_SIZE], len[MAXN], fail[MAXN], sz, last, cntPos[MAXN];
	int tong[MAXN], topo[MAXN];
	void init() {
		len[0] = 0;
		sz = 1;
		last = newnode(0);
	}
	int newnode(int le) {
		len[sz] = le;
		fail[sz] = 0;
		for(int i = 0; i < CHARSET_SIZE; i++)
			ch[sz][i] = 0;
		return sz++;
	}
	void insert(int c) {
		c -= 'a';
		int v = last, u = newnode(len[v] + 1);
		last = u;
		cntPos[u] = 1;
		for(; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if(!v){fail[u] = 1; return;}
		int o = ch[v][c];
		if(len[v] + 1 == len[o]) fail[u] = o;
		else {
			int n = newnode(len[v] + 1);
			cntPos[n] = 0;
			memcpy(ch[n], ch[o], sizeof(ch[0]));
			fail[n] = fail[o];
			fail[u] = fail[o] = n;
			for(; ch[v][c] == o; v = fail[v]) ch[v][c] = n;
		}
	}
	void topoSort() {
		memset(tong, 0, sizeof tong);
		tong[0] = 1;
		for(int i = 1; i < sz; i++)
			tong[len[i]]++;
		for(int i = 1; i < sz; i++)
			tong[i] += tong[i - 1];
		for(int i = sz - 1; i >= 1; i--)
			topo[--tong[len[i]]] = i;
	}
}sam;
/************************************************************/
