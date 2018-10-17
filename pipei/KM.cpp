/************************************************************/
/* KM 算法 求最大权匹配问题
 * 复杂度 O(nx*nx*ny)
 * 若求最小权匹配,可将权值取相反数,结果取相反数
 * 首先将图读入到邻接矩阵g[][]中，然后设置两边的点数nx, ny
 * 接着调用KM()，返回最大权
 * 注意点的编号从 0 开始
 */

const int N = 310;
int nx,ny;					//两边的点数
int g[N][N];				//二分图描述
int linker[N],lx[N],ly[N];	//y 中各点匹配状态,x,y 中的点标号
int slack[N];
bool visx[N],visy[N];
bool DFS(int x){
	visx[x] = true;
	for(int y = 0; y < ny; y++){
		if(visy[y])continue;
		int tmp = lx[x] + ly[y] - g[x][y];
		if(tmp == 0){
			visy[y] = true;
			if(linker[y] == - 1 || DFS(linker[y])){
				linker[y] = x;
				return true;
			}
		}
		else if(slack[y] > tmp)
			slack[y] = tmp;
	}
	return false;
}
int KM(){
	memset(linker, - 1,sizeof(linker));
	memset(ly,0,sizeof(ly));
	for(int i = 0;i < nx;i++){
		lx[i] = - INF;
		for(int j = 0;j < ny;j++)
			if(g[i][j] > lx[i])
				lx[i] = g[i][j];
	}
	for(int x = 0;x < nx;x++){
		for(int i = 0;i < ny;i++)
			slack[i] = INF;
		while(true){
			memset(visx,false,sizeof(visx));
			memset(visy,false,sizeof(visy));
			if(DFS(x))break;
			int d = INF;
			for(int i = 0;i < ny;i++)
				if(!visy[i] && d > slack[i])
					d = slack[i];
			for(int i = 0;i < nx;i++)
				if(visx[i])
					lx[i] -= d;
			for(int i = 0;i < ny;i++){
				if(visy[i])ly[i] += d;
				else slack[i] -= d;
			}
		}
	}
	int res = 0;
	for(int i = 0;i < ny;i++)
		if(linker[i] != -1)
			res += g[linker[i]][i];
	return res;
}
//HDU 2255
//int main(){
//	if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
//	int n;
//	while(scanf("%d",&n) == 1){
//		for(int i = 0;i < n;i++)
//			for(int j = 0;j < n;j++)
//				scanf("%d",&g[i][j]);
//		nx = ny = n;
//		printf("%d\n",KM());
//	}
//	return 0;
//}

/************************************************************/

