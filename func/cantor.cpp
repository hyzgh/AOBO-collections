/*************************************************************/
/* 康拓展开：用于压缩状态，可节省内存空间(Tested 1 times)
 */
static const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};   // 阶乘
int cantor(int *a, int n) {
	int x = 0;
	for (int i = 0; i < n; ++i) {
		int smaller = 0;  // 在当前位之后小于其的个数
		for (int j = i + 1; j < n; ++j) {
			if (a[j] < a[i])
				smaller++;
		}
		x += FAC[n - i - 1] * smaller; // 康托展开累加
	}
	return x;  // 康托展开值
}


//康托展开逆运算
void decantor(int x, int n)
{
    vector<int> v;  // 存放当前可选数
    vector<int> a;  // 所求排列组合
    for(int i=1;i<=n;i++)
        v.push_back(i);
    for(int i=m;i>=1;i--)
    {
        int r = x % FAC[i-1];
        int t = x / FAC[i-1];
        x = r;
        sort(v.begin(),v.end());// 从小到大排序
        a.push_back(v[t]);      // 剩余数里第t+1个数为当前位
        v.erase(v.begin()+t);   // 移除选做当前位的数
    }
}
/*************************************************************/
