/************************************************************/
/* 带权并查集
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;

struct pre
{
	int p[N], dis[N];
	void init(int n)
	{
		memset(dis, 0, sizeof dis);
		for(int i = 0; i <= n; i ++)
			p[i] = i;
	}
	int Find(int x)
	{
		if(x == p[x])	return p[x];
		int fa = Find(p[x]);
		dis[x] += dis[p[x]];
		return p[x] = fa;
	}
	void Mix(int x, int y ,int dis_xy)
	{
		int fx = Find(x), fy = Find(y);
		if(fx==fy)	return ;
		p[fy] = fx;
		dis[fy] = dis[x] + dis_xy - dis[y];
	}
};
/************************************************************/
