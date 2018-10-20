/************************************************************************
    > File Name: 树上分治.cpp
    > Author: zhangab
    > Mail: 2411035458@qq.com 
    > Created Time: 2018年10月20日 星期六 16时24分39秒
    > 树上距离小于等于k的点对数
************************************************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#define pb push_back

using namespace std;
const int maxn = 10005, inf = 0x3f3f3f3f;

struct Edge
{
	int to, next, dist;
}edge[maxn<<1];
int head[maxn], cnt;

void addedge(int u, int v, int w)
{
	edge[cnt].to = v;
	edge[cnt].dist = w;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

int n, k, ans;
int num[maxn];//num[i]表示以i为根的树 的节点数
int dp[maxn];//一维滚动。dp[i]将i删去后 当前树的最大联通块的大小

int Stack[maxn], top1;//栈
bool vis[maxn] ;//true表删除
int size;//当前树的节点数
int root;//根节点

void get_root(int u, int fa)//深搜遍历的同时找寻树的重心root
{
	dp[u] = 0;
	num[u] = 1;//初始化

	for(int i = head[u]; ~i; i  = edge[i].next)
	{
		int v = edge[i].to;
		if(v!=fa && !vis[v]	)
		{//保证不回溯
			get_root(v, u);
			num[u] += num[v];//加上儿子的节点数就是根的节点数
			dp[u] = max(num[v], dp[u]);//最大联通块大小可能是子树大小
		}
	}
	//最大联通块还有可能是当前树删除子树u之后的树大小
	dp[u] = max(dp[u] , size - num[u]);
	//最后跟目前的重心对比
	if(dp[u]<dp[root])	root = u;
}

int dist[maxn];//到根节点的距离
inline bool cmp(int i, int j)
{
	return dist[i] < dist[j];
}

void Find_dist(int u, int fa , int d)
{//计算当前树的所有节点到根的距离，并将点入栈
	Stack[++top1] = u;
	dist[u] = d;
	for(int i = head[u]; ~i ; i = edge[i].next)
	{
		int v = edge[i].to;
		if(vis[v] || v==fa)	continue ;
		Find_dist(v, u, d+edge[i].dist);
	}
}

int calc(int l, int r)//计算满足距离≤k的（i，j）个数
{
	int j = r, Ans = 0;//此时stack中l到r是按照dist升序排好的，ij一前一后往中间扫
	for(int i = l; i <= r; i ++)
	{
		while(dist[Stack[i]]+dist[Stack[j]]>k && j>i) j--;
		if(i==j)	break ;
		Ans += j-i;
		//Stack[i+1]~Stack[j]都是满足条件的
	}
	return Ans;
}

void solve(int u, int fa)
{
	dp[0] = maxn;
	size = num[u];
	root = 0;
	
	get_root(u, fa);//找到重心并将之转换为当前树的根

	top1 = 0;
	int top2 = 0;
	for(int i = head[root]; ~i; i = edge[i].next)
	{
		int v = edge[i].to;
		if(vis[v])	continue;
		top2 = top1;
		Find_dist(v, root, edge[i].dist);
		//top2+1 到top1+1为子树v的所有节点
		sort(Stack+top2+1, Stack+top1+1, cmp);
		ans -= calc(top2+1, top1);//减去在同一棵子树且经过根节点（即非最短距离）的答案数
	}
	
	Stack[++top1] = root;
	dist[root ] = 0;
	sort(Stack+1, Stack+top1+1, cmp);
	ans += calc(1, top1);

	vis[root] = 1;

	for(int i = head[root]; ~i; i = edge[i].next)
		if(!vis[edge[i].to])
			solve(edge[i].to, root);//分治解决
}

void init()
{
	memset(head, -1, sizeof head);
	memset(vis, 0, sizeof vis);
	ans = 0;
	cnt = 0;
}

int main()
{
	while(scanf("%d %d", &n, &k), n&&k)
	{
		init();
		for(int i = 1; i < n; i ++)
		{
			int u, v, d;
			scanf("%d %d %d", &u, &v, &d);
			addedge(u, v, d);
			addedge(v, u, d);
		}
		num[1] = n;
		solve(1, 0);
		printf("%d\n", ans);
	}
    return 0;
}
