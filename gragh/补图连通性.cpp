/*
����һ��ͼ�������ͼ�Ĳ�ͼ����ͨ������Լ�ÿ����ͨ��Ĵ�С

��1������һ�����нڵ������ 1->2->3->����.���˴�������set���桪����1-n�����ַ���set�У�������һ��log�ĸ��Ӷȣ����Ҳ�������������
��2����������ȡ��һ���㣬����������ڵ����е���ϱ�ǣ���ô��û�б����ϱ�ǵĵ�͸�������Ϊһ����ͨ��
��3�����������ҳ�û�б����ϱ�ǵĵ㣬�������н���ɾ������������У�ֱ������Ϊ�գ������ҵ���һ����ͨ�飻�ص���2����ֱ������Ϊ��
��4���㷨ʱ�临�Ӷ�O��n+m��
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000010;//�˴�������Ŀ�����޸�
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
bool vis1[maxn], vis2[maxn]; //vis1������ڵ㣬vis2����ڶ��еĴ���״̬
int scc[maxn], scccnt;
void bfs(){
    queue <int> q;
    memset(vis1, 0, sizeof(vis1));
    memset(vis2, 0, sizeof(vis2));
    while(L[0].nxt){//�����ڽڵ�
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
            for(int i = head[u]; ~i; i = E[i].nxt) vis1[E[i].v] = 0; //һ��ȡ�����ڽڵ�ı��
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
