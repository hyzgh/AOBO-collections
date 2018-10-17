/************************************************************************************/
/* 白书版dinic算法：解决最大流问题(Tested 2 times)
 * 时间复杂度为O(|E| * |V| * |V|)，不过，该算法在实际应用中速度非常快。
 */

const int MAX_V = 209;	//最大点数

struct edge{int to, cap, rev;};

vector<edge> G[MAX_V];
int level[MAX_V];
int iter[MAX_V];

void add_edge(int from, int to, int cap) {
	G[from].push_back((edge){to, cap, static_cast<int>(G[to].size())});
	G[to].push_back((edge){from, 0, static_cast<int>(G[from].size()-1)});
}

void bfs(int s) {
	memset(level, -1, sizeof level);
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while(!que.empty()) {
		int v = que.front(); que.pop();
		for(int i = 0; i < G[v].size(); i++) {
			edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0) {
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}

int dfs(int v, int t, int f) {
	if(v==t) return f;
	for(int &i = iter[v]; i < G[v].size(); i++) {
		edge &e = G[v][i];
		if(e.cap > 0 && level[v] < level[e.to]) {
			int d=dfs(e.to, t, min(f, e.cap));
			if(d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int s, int t) {
	int flow = 0;
	while(1) {
		bfs(s);
		if(level[t] < 0) return flow;
		memset(iter, 0, sizeof iter);
		int f;
		while((f = dfs(s, t, INF)) > 0)
			flow += f;
	}
}

/************************************************************************************/
