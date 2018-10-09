#include<cstdio>
#include<iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=10005;
const double eps=1e-12;
double a[maxn][maxn];  // 增广矩阵
int equ,var;     //equ个方程,var个变量
double x[maxn];   //解集
bool free_x[maxn];
int n;

//判断浮点数是否在误差范围内看作等于0
int sgn(double x) {
	return (x>eps)-(x<-eps);
}
// 高斯消元法解方程组(Gauss-Jordan elimination).(-1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
int Gauss(int equ,int var) {
	int i,j,k;
	int max_r;   // 当前这列绝对值最大的行.
	int col;     // 当前处理的列.
	double temp;
	int free_x_num;
	int free_index;
	// 转换为阶梯阵.
	col=0;    // 当前处理的列.
	memset(free_x,true,sizeof(free_x));
	for (k=0;k<equ&&col<var;k++,col++) {
		max_r=k;
		for(i=k+1;i<equ;i++) {
			if(sgn(fabs(a[i][col])-fabs(a[max_r][col]))>0)
		         max_r=i;
 		}
 		if(max_r!=k) {
 			// 与第k行交换.
 			for(j=k;j<var+1;j++)
 			   swap(a[k][j],a[max_r][j]);
		}
		if(sgn(a[k][col])==0) {
			// 说明该col列第k行以下全是0了，则处理当前行的下一列.
			k--;continue;
		}
		for(i=k+1;i<equ;i++) {
			// 枚举要删去的行.
			if(sgn(a[i][col])!=0) {
				temp=a[i][col]/a[k][col];
				for(j=col;j<var+1;j++) {
					a[i][j]=a[i][j]-a[k][j]*temp;
				}
			}
		}
	}
	for(i=k;i<equ;i++) {
		if(sgn(a[i][col])!=0)
		return -1; // 无解
	}
	if(k<var) {
		for(i=k-1;i>=0;i--) {
			free_x_num=0;
			for(j=0;j<var;j++) {
				if(sgn(a[i][j])!=0&&free_x[j])
				   free_x_num++,free_index=j;
			}
			if(free_x_num>1) continue;
			temp=a[i][var];
			for(j=0;j<var;j++) {
				if(sgn(a[i][j])!=0&&j!=free_index)
				    temp-=a[i][j]*x[j];
			}
			x[free_index]=temp/a[i][free_index];
			free_x[free_index]=0;
		}
		return var-k; // 无穷多解，自由变元个数
	}
	for(i=var-1;i>=0;i--) {
		temp=a[i][var];
		for(j=i+1;j<var;j++) {
			if(sgn(a[i][j])!=0)
			  temp-=a[i][j]*x[j];
		}
		x[i]=temp/a[i][i];
	}
	return 0; // 唯一解
}
int main() {
	int i,j;
	while(scanf("%d%d",&equ,&var)!=EOF) {
		memset(a,0,sizeof(a));
		for(i=0; i<equ; i++) {
			for(j=0; j<var+1; j++) {
				scanf("%lf",&a[i][j]); // 读入增广矩阵
			}
		}
		int free_num=Gauss(equ,var);
	}
	return 0;
}
