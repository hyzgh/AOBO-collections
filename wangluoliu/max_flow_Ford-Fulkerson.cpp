/**********************************************************************/
/* 白书上的Ford-Fulkerson的算法，效率较低，不建议使用。
 * 时间复杂度为O(F * |E|)，F为最大流的流量，这是一个很松的上界，实际运用当中是较快的。
 */
struct edge{
	int to, cap, rev;
};

vector<edge> G[N];
bool used[N];

void add_edge(int from, int to, int cap){
	G[from].push_back( (edge){to, cap, static_cast<int>(G[to].size())});
	G[to].push_back( (edge){from, 0, static_cast<int>(G[from].size()-1)});
}

int dfs(int v, int t, int f){
	if(v==t) return f;
	used[v]=true;
	for(int i=0; i<G[v].size(); i++){
		edge &e=G[v][i];
		if(!used[e.to] && e.cap){
			int d=dfs(e.to, t, min(f, e.cap));
			if(d){
				e.cap-=d;
				G[e.to][e.rev].cap+=d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int s, int t){
	int flow=0;
	while(1){
		memset(used, 0, sizeof used);
		int f=dfs(s, t, INF);
		if (!f) return flow;
		flow+=f;
	}
}


/**********************************************************************/
