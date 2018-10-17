/************************************************************/
/* EK算法：解决最大流问题，使用邻接矩阵，可打印路径(Tested 1 times)
 * 初始化：g[][], start, end, nn
 * 时间复杂度：O(|V| * |E| * |E|)
 */
const int MAXN = 110;//注意修改，有点小
const int INF = 0x3fffffff;
int g[MAXN][MAXN];//存边的容量，没有边的初始化为0
int path[MAXN], flow[MAXN], start, en;
int nn;//点的个数，编号0-nn.nn包括了源点和汇点

queue<int>q;
int bfs() {
	int i,t;
	while(!q.empty()) q.pop();//把清空队列
	memset(path, -1, sizeof path);//每次搜索前都把路径初始化成-1
	path[start] = 0;
	//memset(flow, 0, sizeof flow);//加上这一句，可在最终的残余网络求割边
	flow[start] = INF;//源点可以有无穷的流流进
	q.push(start);
	while(!q.empty()) {
		t = q.front();
		q.pop();
		if(t == en) break;
		//枚举所有的点，如果点的编号起始点有变化可以改这里
		for(i = 0;i <= nn; i++) {
			if(i != start && path[i] == -1 && g[t][i]) {
				flow[i] = min(flow[t], g[t][i]);
				q.push(i);
				path[i] = t;
			}
		}
	}
	if(path[en] == -1) return -1;//找不到增广路径了
	return flow[en];
}
int max_flow() {
	int max_flow = 0;
	int step, now, pre;
	while((step = bfs()) != -1) {
		max_flow += step;
		now = en;
		while(now != start) {
			pre = path[now];
			g[pre][now] -= step;
			g[now][pre] += step;
			now = pre;
		}
	}
	return max_flow;
}
/************************************************************/
