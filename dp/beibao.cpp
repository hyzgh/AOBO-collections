/************************************************************/
/* 01背包, 完全背包, 多重背包(Tested 1 times)
 * 实际应用直接调用multiPack即可, 其中w表示当前物品的代价, v表示价值, number表示数量
 * V表示背包最大容量
 */
void zeroPack(int *dp, int w, int v) {
	for(int i = V; i >= w; i--)
		dp[i] = max(dp[i], dp[i-w] + v);
}

void completePack(int *dp, int w, int v) {
	for(int i = w; i <= V; i++)
		dp[i] = max(dp[i], dp[i-w] + v);
}

void multiPack(int *dp, int w, int v, int num) {
	if(num*w >= V) {
		completePack(dp, w, v);
		return;
	}
	int k = 1;
	while(k < num) {
		zeroPack(dp, w*k, v*k);
		num -= k;
		k *= 2;
	}
	zeroPack(dp, w*num, v*num);
}
/************************************************************/
