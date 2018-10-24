/************************************************************************
    > File Name: 数列分治.cpp
    > Author: zhangab
    > Mail: 2411035458@qq.com 
    > Created Time: 2018年10月20日 星期六 16时28分46秒
    > 逆序对
************************************************************************/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5+5;

int a[N], ans[N];

ll solve(int l, int r)
{
	//划分并解决子问题
	int mid = (l+r)>>1;
	if(l==r)	return 0;
	ll num = 0;//逆序对的个数

	num += solve(l, mid);
	num += solve(mid+1, r);

	//合并子问题
	
	//每一次的处理结果，升序保存在ans数组
	//将属于不同子序列的逆序对个数累加
	for(int i = l, j = mid+1, k = 0; i<=mid||j<=r; k ++)
	{
		if(i>mid)	ans[k] = a[j++];
		else if(j>r)	ans[k] = a[i++];
		else if(a[i]<=a[j])	ans[k] = a[i++];
		else
		{
			//出现逆序对
			ans[k] = a[j++];
			num += mid-i+1;//B序列中大于a[j]的个数
		}
	}
	for(int i = 0; i <= (r-l); i ++)
		a[l+i] = ans[i];
	return num;
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", a+i);
	printf("%lld\n",solve(0, n-1));
	return 0;
}

