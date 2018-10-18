//#include<cstdio>
//#include<iostream>
//#include<cstring>
//#include<cmath>
//using namespace std;
//
//const int VN = 105;
//const int INF = 0x7fffffff;
//
//template<typename Type>
//class Directed_MST{
//public:
//    void init(int _n){
//        n=_n;
//        ans = 0;
//        memset(vis, 0, sizeof(vis));
//        memset(inc, 0, sizeof(inc));
//        for(int i=0; i<=n; ++i){
//            w[i][i] = INF;
//            for(int j=i+1; j<=n; ++j)
//                w[i][j]=w[j][i]=INF;
//        }
//    }
//    void insert(int u, int v, Type _w){
//        if(w[u][v]>_w) w[u][v] = _w;
//    }
//    Type directed_mst(int u){
//        //==  步骤1： 判断能否形成最小树形图，直接dfs遍历
//        dfs(u);
//        for(int i=1; i<=n; ++i)
//            if(!vis[i]) { return -1; }
//
//        //== 如果可以形成最小树形图，继续
//        memset(vis, 0, sizeof(vis));
//        while(true){
//            //== 1. 找最小前驱边
//            for(int i=1; i<=n; ++i)if(i!=u&&!inc[i]){          //不是root而且该点没有被收缩
//                w[i][i]=INF, pre[i] = i;
//                for(int j=1; j<=n; ++j)if(!inc[j] && w[j][i]<w[pre[i]][i]){
//                    pre[i] = j;
//                }
//            }
//            //== 2.判断是否有环
//            int i;
//            for(i=1; i<=n; ++i){
//                if(i!=u&&!inc[i]){
//                    int j=i, cnt=0;
//                    while(j!=u && pre[j]!=i && cnt<=n)
//                        j=pre[j], ++cnt;     //O(n);
//                    if(j==u || cnt>n) continue; //没找到
//                    break;
//                }
//            }
//
//            //== 没有找到环,得到答案
//            if(i>n){
//                for(int i=1; i<=n; ++i)if(i!=u && !inc[i]) ans+=w[pre[i]][i];
//                return ans;
//            }
//            //==  有环，进行收缩
//            int j=i;
//            memset(vis, 0, sizeof(vis));
//            do{
//                ans += w[pre[j]][j], j=pre[j], vis[j]=inc[j]=true;
//            }while(j!=i);
//            inc[i] = false; // 环缩成了点i，点i仍然存在
//
//            //==  收缩
//            for(int k=1; k<=n; ++k)if(vis[k]){ // 在环中点点
//                for(int j=1; j<=n; ++j)if(!vis[j]){  // 不在环中的点
//                    if(w[i][j] > w[k][j]) w[i][j] = w[k][j];
//                    if(w[j][k]<INF && w[j][k]-w[pre[k]][k] < w[j][i])
//                        w[j][i] = w[j][k] - w[pre[k]][k];
//                }
//            }
//        }
//        return ans;
//    }
//
//private:
//    // 从根结点遍历一遍，判断是否存在最小树形图
//    void dfs(int u){
//        vis[u] = true;
//        for(int i=1; i<=n; ++i)if(!vis[i]&&w[u][i]<INF){
//            dfs(i);
//        }
//    }
//
//private:
//    Type ans;         // 所求答案
//    int n;            // 结点个数
//    int pre[VN];      // 权值最小的前驱边
//    bool vis[VN];     // 是在环中还是在环外
//    bool inc[VN];     // 该点是否被删除了（收缩）
//    Type w[VN][VN];   // 图
//};
//
//
//Directed_MST<double>G;
//double x[VN],y[VN];
//inline double getDist(double x1,double y1,double x2,double y2){
//    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
//}
//
//int main(){
//    int n,m;
//    while(~scanf("%d%d",&n,&m)){
//        G.init(n);
//        for(int i=1; i<=n; ++i)
//            scanf("%lf%lf",&x[i],&y[i]);
//        for(int i=0; i<m; ++i){
//            int a,b;
//            scanf("%d%d",&a,&b);
//            if(a==b)continue;
//            G.insert(a,b,getDist(x[a],y[a],x[b],y[b]));
//        }
//        double ans = G.directed_mst(1);
//        if(ans < 0) puts("poor snoopy");
//        else printf("%.2f\n", ans);
//    }
//    return 0;
//}

