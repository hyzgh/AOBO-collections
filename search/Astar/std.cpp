// 利用A*算法和dijkstra算法寻找k短路
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;  // INF表示无穷大

const int NODE_NUM = 1e5 + 9;  // 表示图的最大点数
const int EDGE_NUM = 1e5 + 9;  // 表示图的最大边数

int tot, head[NODE_NUM], headrev[NODE_NUM], h[NODE_NUM];

struct Edge {
	int to, cost, next;
	Edge() {}
	Edge(int to, int cost, int next): to(to), cost(cost), next(next) {}
}edge[EDGE_NUM << 1];

void init() {
	tot = 0;
	memset(head, -1, sizeof head);
	memset(headrev, -1, sizeof headrev);
}

void addedge(int u, int v, int cost) {
	edge[tot] = Edge{v, cost, head[u]};
	head[u] = tot++;
	edge[tot] = Edge{u, cost, headrev[v]};
	headrev[v] = tot++;
}

void dijkstra(int start) {
	priority_queue<pii, vector<pii>, greater<pii> > que;
	memset(h, INF, sizeof h);
	h[start] = 0;
	que.push(pii(0, start));
	while (!que.empty()) {
		pii p = que.top(); que.pop();
		int u = p.second;
		if (h[u] < p.first) continue;
		for (int i = headrev[u]; ~i; i = edge[i].next) {
			Edge e = edge[i];
			if(h[e.to] > h[u] + e.cost) {
				h[e.to] = h[u] + e.cost;
				que.push(pii(h[e.to], e.to));
			}
		}
	}
}

struct Status {
	int now, g;
	Status(int now, int g): now(now), g(g) {}
	bool operator < (const Status &rhs) const {
		return g + h[now] > rhs.g + h[rhs.now];
	}
};

int Astar(int start, int endd, int k) {
	if(h[start] == INF) {
		return -1;
	} else {
		int cnt[NODE_NUM];
		memset(cnt, 0, sizeof cnt);
		priority_queue<Status> que;
		que.push(Status(start, 0));
		while(!que.empty()) {
			Status sta = que.top();
			que.pop();
			int now = sta.now;
			int g = sta.g;
			cnt[now]++;
			if(cnt[endd] == k) return g;
			if(cnt[now] > k) continue;
			for(int i = head[now]; ~i; i = edge[i].next) {
				int to = edge[i].to;
				int cost = edge[i].cost;
				que.push(Status(to, g + cost));
			}
		}
	}
	return -1;
}

int main(void) {
	int nodeNum, edgeNum, u, v, cost, start, endd, k;
	while(~scanf("%d%d", &nodeNum, &edgeNum)) {
		init();
		for(int i = 0; i < edgeNum; i++) {
			// 表示u到v有一条权值为cost的有向边
			scanf("%d%d%d", &u, &v, &cost);
			addedge(u, v, cost);
		}
		scanf("%d%d%d", &start, &endd, &k);
		dijkstra(endd);
		if(start == endd) k++;
		printf("%d\n", Astar(start, endd, k));
	}
	return 0;
}
