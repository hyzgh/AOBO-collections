/************************************************************/
/* 区间不同元素个数，第k大
 * 主席树变种
 */
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
const int N = 2e5+9;

#define mid ((l + r) >> 1)

int ans, n, T, m, a[N], vis[N], l, r, kase;
int tot, rt[N], lson[N * 40], rson[N * 40], sum[N * 40];

void build(int &rt, int l, int r) {
	rt = ++tot;
	sum[rt] = 0;
	if(l == r)
		return;
	build(lson[rt], l, mid);
	build(rson[rt], mid + 1, r);
}

void decode(int &l, int &r) {
	(l += ans) %= n;
	(r += ans) %= n;
	l++, r++;
	if(l > r)
		swap(l, r);
}

void update(int &rt, int last, int l, int r, int pos, int x) {
	rt = ++tot;
	lson[rt] = lson[last];
	rson[rt] = rson[last];
	sum[rt] = sum[last] + x;
	if(l == r) {
		return;
	}
	if(pos <= mid)
		update(lson[rt], lson[last], l, mid, pos, x);
	else
		update(rson[rt], rson[last], mid + 1, r, pos, x);
}

int queryNum(int rt, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		return sum[rt];
	}
	int ans = 0;
	if(L <= mid)
		ans += queryNum(lson[rt], l, mid, L, R);
	if(mid < R)
		ans += queryNum(rson[rt], mid + 1, r, L, R);
	return ans;
}

int queryId(int rt, int l, int r, int k) {
	if(l == r)
		return l;
	if(sum[lson[rt]] >= k)
		return queryId(lson[rt], l, mid, k);
	return queryId(rson[rt], mid + 1, r, k - sum[lson[rt]]);
}

int main(void) {
	if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) {
			scanf("%d", a + i);
		}
		tot = 0;
		memset(vis, 0, sizeof vis);
		build(rt[n+1], 1, n);
		for(int i = n; i >= 1; i--) {
			int last = rt[i + 1];
			if(vis[a[i]])
				update(last, last, 1, n, vis[a[i]], -1);
			update(rt[i], last, 1, n, i, 1);
			vis[a[i]] = i;
		}
		ans = 0;
		// cout << queryNum(rt[1], 1, n, 1, 1) << endl;
		printf("Case #%d:", ++kase);
		while(m--) {
			scanf("%d%d", &l, &r);
			decode(l, r);
			// cout << l << " " << r << endl;
			int k = queryNum(rt[l], 1, n, l, r);
			k = (k + 1) >> 1;
			// cout << "k: " << k << endl;
			ans = queryId(rt[l], 1, n, k);
			printf(" %d", ans);
		}
		printf("\n");
	}

	return 0;
}
/************************************************************/
