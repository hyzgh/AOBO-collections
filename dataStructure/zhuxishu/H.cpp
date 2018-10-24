
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
const int N = 1e5+9;

#define mid ((l + r) >> 1)
#define lson (rt << 1)
#define rson (rt << 1 | 1)

int sum[N * 20], tot, rt[N * 20], ls[N * 20], rs[N * 20];
int T, n, a[N], b[N], sz, l, r, k, q;

void build(int &rt, int l, int r) {
	rt = ++tot;
	sum[rt] = 0;
	if(l == r)
		return;
	build(ls[rt], l, mid);
	build(rs[rt], mid + 1, r);
}

void pushup(int rt) {
	sum[rt] = sum[ls[rt]] + sum[rs[rt]];
}

void update(int &rt, int last, int l, int r, int val) {
	rt = ++tot;
	if(l == r) {
		sum[rt] = sum[last] + 1;
		return;
	}

	ls[rt] = ls[last];
	rs[rt] = rs[last];

	if(val <= mid)
		update(ls[rt], ls[last], l, mid, val);
	else
		update(rs[rt], rs[last], mid + 1, r, val);
	pushup(rt);
}

int query(int rt1, int rt2, int l, int r, int k) {
	if(l == r)
		return l;
	int cnt = sum[ls[rt2]] - sum[ls[rt1]];
	if(k <= cnt) {
		return query(ls[rt1], ls[rt2], l, mid, k);
	}
	else {
		return query(rs[rt1], rs[rt2], mid + 1, r, k - cnt);
	}
}


void work() {
	scanf("%d%d%d", &l, &r, &k);
	int ans = query(rt[l - 1], rt[r], 1, sz, k);
	printf("%d\n", b[ans]);
}

int main(void) {
	if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &q);
		for(int i = 1; i <= n; i++) {
			scanf("%d", a + i);
			b[i] = a[i];
		}
		sort(b + 1, b + n + 1);
		sz = unique(b + 1, b + n + 1) - (b + 1);
		tot = 0;
		build(rt[0], 1, sz);
		for(int i = 1; i <= n; i++) {
			a[i] = lower_bound(b + 1, b + sz + 1, a[i]) - b;
			update(rt[i], rt[i - 1], 1, sz, a[i]);
		}
		while(q--) {
			work();
		}
	}

	return 0;
}
