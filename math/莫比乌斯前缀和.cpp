/*
莫比乌斯前缀和，HDU4746
i~[1,n], j~[1,m], facp[(i,j)] <= p, 求<i,j>对数
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
const int M = 20;

int prime[N], cnt, facp[N], mo[N], sum[M][N];
// 素数 ，素数个数，素因子个数，莫比乌斯函数，莫比乌斯前缀和
bool vis[N];

void init() {
    mo[1] = 1;
    facp[1] = 0;
    for (long long i = 2; i < N; i++) {
		if (!vis[i]) {
			prime[cnt ++] = i;
			mo[i] = -1;
			facp[i] = 1;
		}
		for (long long j = 0, k; j < cnt && (k = i * prime[j]) < N; j++) {
			vis[k] = 1;
			facp[k] = facp[i] + 1;
			if (i % prime[j]) {
				mo[k] = -mo[i];
			} else {
				mo[k] = 0;
				break;
			}
		}
    }
}

void sum_mo() {
	// 对于每一个数字，先把他的因子累加
	for (int i = 1; i < N; i++) {
		for (int j = i; j < N; j += i) {
			sum[facp[i]][j] += mo[j / i]; // 倍数型
			//                 mo[i]       约数型
		}
	}
	// sum对于facp从小到大累加的
	for (int i = 1; i < M; i++) {
		for (int j = 1; j < N; j++) {
			sum[i][j] += sum[i - 1][j];
		}
	}
	// sum[][j] 前缀和
	for (int i = 0; i < M; i++) {
		for (int j = 1; j < N; j++) {
			sum[i][j] += sum[i][j - 1];
		}
	}
}

int main() {
	init();	sum_mo();
	int T;	scanf("%d", &T);
	while (T--) {
		int n, m, p;
		scanf ("%d%d%d", &n, &m, &p);
		p = min(p, 19);
		long long ans = 0;
		for (int i = 1; i <= min(n, m);) {
			long long a = n / i, b = m / i;
			int now = min(n / a, m / b);
			ans += a * b * (sum[p][now] - sum[p][i - 1]); // [i, now]中，n/a, m/b 不变
			i = now + 1;
		}
		cout << ans << endl;
	}
	return 0;
}
