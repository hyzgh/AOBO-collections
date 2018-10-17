/************************************************************/
/* O(nlogn) 求解上升子序列问题(Tested 0 times)
 */
int n, a[N], s[N], dp[N];
// 下标从1开始
// dp[i] 表示以a[i]结尾的LIS长度
// s[i] 表示LIS序列的第i个元素

void init() {
    for(int i = 1; i <= n; i++) s[i] = INF; //上升为INF,下降为-INF
    memset(dp, 0, sizeof dp);
}

int BinSearch(int x, int y, ll v) {
    while(x <= y) {
        int mid = x + (y - x) / 2;
        if(s[mid] < v) x = mid + 1;		//严格为<或> 非严格为<=或>=
        else y = mid - 1;
    }
    return x;
}

int LIS() {
    init();
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int pos = BinSearch(1, i, a[i]);
        dp[i] = pos;
        s[pos] = min(s[pos], a[i]);    //上升为min,下降为max
        ans = max(ans, dp[i]);
    }
	return ans;
}
/************************************************************/
