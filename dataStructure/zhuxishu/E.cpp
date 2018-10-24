// BIT + 主席树

#include<bits/stdc++.h>
#define x first
#define y second
#define ok cout << "ok" << endl;
#define okd(d) cout << "ok " << d << endl;
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

const int N = 5e4 + 9;
const int M = 1e4 + 9;

#define mid ((l + r) >> 1)

struct Node {
	int data, left, right;
}tree[N * 50];

vi p, q;
char op[9], O[M];
int cnt, tot, a[N], b[2 * N], L[M], R[M], sz, K[M], rt[2 * N], n, m, T;

void build(int &rt, int x, int l, int r) {
	tree[++tot] = tree[rt];
	rt = tot;
	tree[rt].data++;
	if(l == r)
		return;
	if(x <= mid)
		build(tree[rt].left, x, l, mid);
	else
		build(tree[rt].right, x, mid + 1, r);
}

void insert(int &rt, int x, int y, int l, int r) {
	tree[++tot] = tree[rt];
	rt = tot;
	tree[rt].data += y;
	if(l == r)
		return;
	if(x <= mid)
		insert(tree[rt].left, x, y, l, mid);
	else
		insert(tree[rt].right, x, y, mid + 1, r);
}

void bitInsert(int i, int x, int y) {
	while(i <= n) {
		insert(rt[i], x, y, 1, sz);
		i += i & -i;
	}
}

int query(int k, int l, int r) {
	if(l == r)
		return l;
	int cnt1 = 0, cnt2 = 0;
	for(int i = 0; i < p.size(); i++)
		cnt1 += tree[tree[p[i]].left].data;
	for(int i = 0; i < q.size(); i++)
		cnt2 += tree[tree[q[i]].left].data;
	if(cnt2 - cnt1 >= k) {
		for(int i = 0; i < p.size(); i++)
			p[i] = tree[p[i]].left;
		for(int i = 0; i < q.size(); i++)
			q[i] = tree[q[i]].left;
		return query(k, l, mid);
	}
	else {
		for(int i = 0; i < p.size(); i++)
			p[i] = tree[p[i]].right;
		for(int i = 0; i < q.size(); i++)
			q[i] = tree[q[i]].right;
		return query(k - (cnt2 - cnt1), mid + 1, r);
	}
}

int solve(int l, int r, int k) {
	p.clear(); q.clear();
	if(l > 0)
		p.push_back(rt[l + n]);
	q.push_back(rt[r + n]);
	while(l) {
		p.push_back(rt[l]);
		l -= l & -l;
	}
	while(r) {
		q.push_back(rt[r]);
		r -= r & -r;
	}
	return query(k, 1, sz);
}


int main(void) {
	if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
	scanf("%d", &T);
	while(T--) {
		memset(rt, 0, sizeof rt);
		memset(tree, 0, sizeof tree);
		scanf("%d%d", &n, &m);
		cnt = tot = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", a + i);
			b[++cnt] = a[i];
		}
		for(int i = 1; i <= m; i++) {
			scanf("%s%d%d", op, &L[i], &R[i]);
			O[i] = op[0];
			if(op[0] == 'Q')
				scanf("%d", &K[i]);
			else
				b[++cnt] = R[i];
		}
		sort(b + 1, b + cnt + 1);
		sz = unique(b + 1, b + cnt + 1) - (b + 1);
		for(int i = 1; i <= n; i++) {
			a[i] = lower_bound(b + 1, b + sz + 1, a[i]) - b;
		}
		for(int i = 1; i <= n; i++) {
			rt[i + n] = rt[i + n - 1];
			build(rt[i + n], a[i], 1, sz);
		}
		for(int i = 1; i <= m; i++) {
			if(O[i] == 'C') {
				bitInsert(L[i], a[L[i]], -1);
				a[L[i]] = lower_bound(b + 1, b + sz + 1, R[i]) - b;
				bitInsert(L[i], a[L[i]], 1);
			}
			else {
				int ans = solve(L[i] - 1, R[i], K[i]);
				printf("%d\n", b[ans]);
			}
		}
	}

	return 0;
}
