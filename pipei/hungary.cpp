/******************************************************************/
/* 匈牙利算法：解决二分匹配问题
 * 先确定点数V，然后使用init()进行初始化，再调用hungary()，返回最大匹配对数
 */

const int MAX_V = 1e5;	//点数的最大值

int V;					//点数，从0开始编号
vector<int> G[MAX_V];	//使用vector存邻接边
int match[MAX_V];
bool used[MAX_V];

void init() {
	for(int i = 0; i < V; i++)
		G[i].clear();
}

void add_edge(int u, int v) {
	G[u].push_back(v);
	G[v].push_back(u);
}

bool dfs(int v) {
	used[v]=true;
	for(int i = 0; i < G[v].size(); i++) {
		int u = G[v][i], w = match[u];
		if(w < 0 || (!used[w] && dfs(w))) {
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

int hungary() {
	int res=0;
	memset(match, -1, sizeof match);
	for(int v = 0; v < V; v++) {
		if(match[v] < 0) {
			memset(used, 0, sizeof used);
			if(dfs(v))
				res++;
		}
	}
	return res;
}

/******************************************************************/
