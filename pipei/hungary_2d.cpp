/************************************************************/
/* 匈牙利算法：解决多重匹配问题
 * 先确定左边点数uN和右边点数vN，然后确定右边各点的最大匹配数num[]
 * 接着调用hungary()即可，返回最大匹配数
 */
const int MAXN = 1009;
const int MAXM = 509;
int uN,vN;
int g[MAXN][MAXM];		//下标从0开始
int linker[MAXM][MAXN];
bool used[MAXM];
int num[MAXM];//右边最大的匹配数
bool dfs(int u){
	for(int v = 0; v < vN;v++)
		if(g[u][v] && !used[v]){
			used[v] = true;
			if(linker[v][0] < num[v]){
				linker[v][++linker[v][0]] = u;
				return true;
			}
			for(int i = 1;i <= num[v];i++)
				if(dfs(linker[v][i])){
					linker[v][i] = u;
					return true;
				}
		}
	return false;
}
int hungary(){
	int res = 0;
	for(int i = 0;i < vN;i++)
		linker[i][0] = 0;		//初始化右边第i点的已匹配点数为0
	for(int u = 0; u < uN; u++){
		memset(used,false,sizeof(used));
		if(dfs(u))res++;
	}
	return res;
}
/************************************************************/
