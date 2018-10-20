/************************************************************************
    > File Name: 平面内最近点对距离.cpp
    > Author: zhangab
    > Mail: 2411035458@163.com 
    > Created Time: 2018年10月20日 星期六 15时59分03秒
    > 平面内最近点对的距离
************************************************************************/

#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

const int N = 1e4+5;
const int inf = 0x3f3f3f3f;
struct node
{
	double x, y;
}a[N];

bool cmpx(node a, node b)
{
	return a.x<b.x;
}

double dist(node a, node b)
{
	return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}

double solve(int l, int r)
{
	if(l==r)	return inf;
	if(l+1==r)	return dist(a[l], a[r]);

	//划分解决
	int mid = (l+r)>>1;
	double st = a[mid].x;//划分依据
	double d = min(solve(l, mid), solve(mid+1, r));

	//在矩形空间内，左边的点跟右边的点一一匹配，合并
	for(int i = mid; i >= l && st-a[i].x < d; i --)
		for(int j = mid+1; j <= r && a[j].x-st < d; j ++)
			d = min(d, dist(a[i], a[j]));

	return d;
}

int main()
{
	int n;
	while(scanf("%d", &n), n)
	{
		for(int i = 0; i < n; i ++)
			scanf("%lf%lf", &a[i].x, &a[i].y);
		sort(a, a+n, cmpx);
		double ans = solve(0, n-1);
		if(ans<10000.0)	printf("%.4f\n", ans);
		else puts("INFINITY");
	}
    return 0;
}
