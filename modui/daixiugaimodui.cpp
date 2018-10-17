/************************************************************/
/* 待修改莫队：解决一类区间问题
 * 时间复杂度O(n^(5/3))
 */

#include<bits/stdc++.h>
#define x first
#define y second
#define ok cout << "ok" << endl;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const long double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const ll LINF = 9223372036854775807;
const double Eps = 1e-7;
const int N = 1e6+9;

char c;
int len, n, m, a[N], cnt[N], l, r, ans, an[N], timer, tot, last[N], flag[N];

inline void sub(int pos) {
	ans -= (--cnt[a[pos]] == 0);
	flag[pos] = 0;
}

inline void add(int pos) {
	ans += (++cnt[a[pos]] == 1);
	flag[pos] = 1;
}

inline void modify(int pos, int val) {
	if(!flag[pos])
		a[pos] = val;
	else {
		sub(pos);
		a[pos] = val;
		add(pos);
	}
}

struct Node {
	int l, r, id, lblock, rblock, timer;
	Node () {}
	Node (int l, int r, int id, int timer): l(l), r(r), id(id), timer(timer) {
		lblock = l / len;
		rblock = r / len;
	}
	bool operator < (const Node &rhs) const {
		if(lblock != rhs.lblock) return lblock < rhs.lblock;
		else if(rblock != rhs.rblock) return rblock < rhs.rblock;
		return timer < rhs.timer;
	}
}q[N];

struct Node1 {
	int pos, val, last;
	Node1 () {}
	Node1 (int pos, int val, int last): pos(pos), val(val), last(last) {}
}chg[N];

int main(void) {
	if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
	while(~scanf("%d%d", &n, &m)) {
		len = pow(n, 2.0 / 3);
		timer = tot = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", a + i);
			last[i] = a[i];
		}
		for(int i = 0; i < m; i++) {
			scanf(" %c%d%d", &c, &l, &r);
			if(c == 'Q') {
				q[tot] = Node{l, r, tot, timer};
				tot++;
			}
			else {
				chg[++timer] = Node1{l, r, last[l]};
				last[l] = r;
			}
		}
		sort(q, q + tot);
		l = 1, r = ans = timer = 0;
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < tot; i++) {
			Node t = q[i];
			while(timer < t.timer) {
				timer++;
				modify(chg[timer].pos, chg[timer].val);
			}
			while(timer > t.timer) {
				modify(chg[timer].pos, chg[timer].last);
				timer--;
			}
			while(r < t.r) add(++r);
			while(l > t.l) add(--l);
			while(r > t.r) sub(r--);
			while(l < t.l) sub(l++);
			an[t.id] = ans;
		}
		for(int i = 0; i < tot; i++) {
			printf("%d\n", an[i]);
		}
	}

	return 0;
}
/************************************************************/
