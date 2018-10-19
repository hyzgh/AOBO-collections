/************************************************************/
/* 回文自动机：解决一类回文字符串问题(Tested 6 times)
 * 时间复杂度：O(|S| * log(字符集个数))
 */
const int MAXN = 1e5 + 9;
const int NN = 26;	//字符集个数

struct Palindromic_Tree {
	int next[MAXN][NN];//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
	int fail[MAXN];//fail指针，失配后跳转到fail指针指向的节点
	int cnt[MAXN]; //cnt[i]表示i表示的回文字符串在整个字符串中出现了多少次
	int num[MAXN]; //num[i]表示i表示的回文字符串中有多少个本质不同的字符串（包括本身）
	int len[MAXN];//len[i]表示节点i表示的回文串的长度
	int S[MAXN];//存放添加的字符
	int last;//指向上一个字符所在的节点，方便下一次add
	int n;//字符数组指针
	int p;//节点指针

	int newnode(int l) {//新建节点
		for(int i = 0; i < NN; i++) next[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = l;
		return p++;
	}

	void init() {//初始化
		p = 0;
		newnode(0);
		newnode(-1);
		last = 0;
		n = 0;
		S[n] = -1;//开头放一个字符集中没有的字符，减少特判
		fail[0] = 1;
	}

	int get_fail(int x) {//和KMP一样，失配后找一个尽量最长的
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x ;
	}

	// 插入的是字符
	void add(int c) {
		c -= 'a';
		S[++ n] = c;
		int cur = get_fail(last);//通过上一个回文串找这个回文串的匹配位置
		if(!next[cur][c]) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
			int now = newnode(len[cur] + 2);//新建节点
			fail[now] = next[get_fail(fail[cur])][c];//和AC自动机一样建立fail指针，以便失配后跳转
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
	}

	void count () {
		for(int i = p - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
		//父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
	}
}pt;
/************************************************************/
