/************************************************************/
/* 拓扑排序
 * cp from zyb.
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<TYPE>g[MAX_N];                  //TYPE可以根据需要进行修改
int degree[MAX_N];

int topo(int n)
{
	queue<TYPE>q;
	memset(degree,0,sizeof(degree));   //注意初始化
	for(int i=0;i<n;i++)               //注意数据的给法是从0开始还是1开始
	{
		for(int j=0;j<g[i].size();j++)
		{
			degree[g[i][j]]++;
		}
	}
	for(int i=0;i<n;i++)               //注意数据的给法是从0开始还是1开始
	{
		if(degree[i]==0)
		{
			q.push(i);
		}
	}
	int tot=0;
	while(q.size())
	{
		int qq=q.front();                  //根据类型修改qq的类型
		q.pop();
		tot++;
		for(int i=0;i<g[qq].size();i++)
		{
			degree[g[qq][i]]--;
			if(degree[g[qq][i]]==0)
				q.push(g[qq][i]);
		}
	}
	if(tot==n)                           //判断自环
		return 1;
	else
		return 0;
}
int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(g,0,sizeof(g));
		int a,b;
		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&a,&b);
			g[a].push_back(b);                 //根据TYPE的类型和出度入度的不同，这里会有所不同
		}
		if(topo(n))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
/************************************************************/
