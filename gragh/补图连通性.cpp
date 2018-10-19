/*
给定一个图，求这个图的补图的连通块个数以及每个联通块的大小

（1）构造一条所有节点的链表： 1->2->3->…….（此处可以用set代替——将1-n的数字放入set中，会增加一个log的复杂度，而且操作不如链表灵活）
（2）从链表中取出一个点，将这个点相邻的所有点打上标记，那么，没有被打上标记的点就跟这个点成为一个联通块
（3）遍历链表找出没有被打上标记的点，从链表中将其删除并放入队列中，直到队列为空，于是找到了一个联通块；回到（2），直到链表为空
（4）算法时间复杂度O（n+m）
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000010;//此处根据题目做了修改
const int maxm = 2000010;
int n, m, edgecnt, head[maxn];
struct edge{int v, nxt; } E[maxm*2];
struct link{int pre, nxt; }L[maxn];
void del(int x){
    L[L[x].pre].nxt = L[x].nxt;
    L[L[x].nxt].pre = L[x].pre;
}
void init(){
    memset(head, -1, sizeof(head));
    edgecnt = 0;
}
void addedge(int u, int v){
    E[edgecnt].v = v, E[edgecnt].nxt = head[u], head[u] = edgecnt++;
}
bool vis1[maxn], vis2[maxn]; //vis1标记相邻点，vis2标记在队列的存在状态
int scc[maxn], scccnt;
void bfs(){
    queue <int> q;
    memset(vis1, 0, sizeof(vis1));
    memset(vis2, 0, sizeof(vis2));
    while(L[0].nxt){//还存在节点
        int now = L[0].nxt, curscc = 1;
        del(now);
        q.push(now);
        vis2[now] = 1;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int i = head[u]; ~i; i = E[i].nxt) vis1[E[i].v] = 1;
            for(int i = L[0].nxt; i; i = L[i].nxt){
                if(!vis1[i] && !vis2[i]){
                    vis2[i] = 1;
                    q.push(i);
                    curscc++;
                    del(i);
                }
            }
            for(int i = head[u]; ~i; i = E[i].nxt) vis1[E[i].v] = 0; //一定取消相邻节点的标记
        }
        scc[++scccnt] = curscc;
    }
}
int main(){
    init();
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    for(int i = 1; i <= n; i++){
        L[i-1].nxt = i; L[i].pre = i - 1;
    } L[n].nxt = 0;
    bfs();
    sort(scc + 1, scc + scccnt + 1);
    printf("%d\n", scccnt);
    for(int i = 1; i < scccnt; i++) printf("%d ", scc[i]); printf("%d", scc[scccnt]);
    return 0;
}
