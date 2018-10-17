/************************************************************/
/* 普通莫队：解决一类区间问题
 * 时间复杂度O(n*sqrt(n))
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

struct Node {
	int l, r, block, id;
	bool operator < (const Node &rhs) const {
		if(block == rhs.block) return r < rhs.r;
		return block < rhs.block;
	}
}q[N];

int n, m, a[N], len, cnt[N], an[N];

int main(void) {
	if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
	while(~scanf("%d", &n)) {
		len = sqrt(n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", a + i);
		}
		scanf("%d", &m);
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &q[i].l, &q[i].r);
			q[i].block = q[i].l / len;
			q[i].id = i;
		}
		sort(q, q + m);
		int l = 1, r = 0, ans = 0;
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < m; i++) {
			Node t = q[i];
			while(r < t.r) {
				ans += (++cnt[a[++r]] == 1);
			}
			while(l > t.l) {
				ans += (++cnt[a[--l]] == 1);
			}
			while(r > t.r) {
				ans -= (--cnt[a[r--]] == 0);
			}
			while(l < t.l) {
				ans -= (--cnt[a[l++]] == 0);
			}
			an[t.id] = ans;
		}
		for(int i = 0; i < m; i++) {
			printf("%d%c", an[i], " \n"[i == m - 1]);
		}
	}

	return 0;
}
/************************************************************/
