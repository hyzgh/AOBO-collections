/************************************************************/
/* bellman算法：解决有负边的最短路问题
 */
const int MAX_E=1e5+9;
const int MAX_V=1e5+9;
struct edge { int from, to, cost; };

edge es[MAX_E];
int d[MAX_V], V, E;
//d[i]表示到达顶点i的最短距离, V表示图的实际顶点数, E表示图的实际边数, 下标从0开始

void bellman(int s){
	for(int i=0; i<V; i++) d[i]=INF;
	d[s]=0;
	while(true){
		bool update=false;
		for(int i=0; i<E; i++) {
			edge e = es[i];
			if (d[e.from]!=INF && d[e.to] > d[e.from] + e.cost) {
				d[e.to]=d[e.from]+e.cost;
				update=true;
			}
		}
		if(!update) break;
	}
}

bool find_nagative_loop() {
	memset(d, 0, sizeof d);
	for(int i=0; i<V; i++){
		for(int j=0; j<E; j++){
			edge e=es[j];
			if(d[e.to]>d[e.from]+e.cost){
				d[e.to]=d[e.from]+e.cost;
				if(i==V-1) return true;
			}
		}
	}
	return false;
}
/************************************************************/
