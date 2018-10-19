/************************************************************/
/* dijkstra算法：解决最短路问题(Tested 0 times)
 * 前向心存图
 */
const int MAX_V=1e5+9;
int d[MAX_V];

void dijkstra(int s) {
	priority_queue<pii, vector<pii>, greater<pii> > que;
	memset(d, INF, sizeof d);
	d[s] = 0;
	que.push(pii(0, s));
	while(!que.empty()) {
		pii p = que.top(); que.pop();
		int u = p.second;
		if(d[u] < p.first) continue;
		for(int i = head[u]; ~i; i = edge[i].next) {
			Edge e = edge[i];
			if(d[e.to] > d[u] + e.cost) {
				d[e.to] = d[u] + e.cost;
				que.push(pii(d[e.to], e.to));
			}
		}
	}
}
/************************************************************/
