/*
高斯消元法解方程组(Gauss-Jordan elimination).(-2表示有浮点数解，但无整数解，-1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
有equ个方程，var个变元。增广矩阵行数为equ,分别为0到equ-1,列数为var+1,分别为0到var.
*/
#include<cstdio>
#include<iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstring>
using namespace std;

const int maxn =50;
int equ,var;         //有equ个方程，var个变元
int a[maxn][maxn] ;  //增广矩阵
int x[maxn];         //解集
bool free_x[maxn];   //标记是否是不确定的变元，初始化为true,确定为0

inline int gcd(int a,int b){
	return b == 0 ? a : gcd(b, a%b);
}

inline int lcm(int a,int b){
	return a/gcd(a,b)*b;
}

int Gauss(int equ,int var)
{
	int i,j,k;
	int max_r;     // 当前这列绝对值最大的行.
	int col;       //当前处理的列
	int ta,tb;
	int LCM, temp;
	int free_x_num;
	int free_index;

	for(int i=0; i<=var; i++) {
		x[i]=0;           //初始化解集
		free_x[i]=true;
	}
    //转换为阶梯阵.
	col=0;        // 当前处理的列
	for(k=0; k<equ&&col<var; k++,col++) {
		max_r=k;
		for(i=k+1; i<equ; i++) {//行变幻
			if(abs(a[i][col])>abs(a[max_r][col])) max_r=i;
		}
		if(max_r!=k) {
			for(j=k; j<var+1; j++) swap(a[k][j],a[max_r][j]);
		}
		if(a[k][col]==0) {
			k--;
			continue;
		}
		for(i=k+1; i<equ; i++) {
			if(a[i][col]!=0) {
				LCM=lcm(abs(a[i][col]),abs(a[k][col]));
				ta=LCM/abs(a[i][col]);
				tb=LCM/abs(a[k][col]);
				if(a[i][col]*a[k][col]<0)  tb=-tb;
				for(j=col; j<var+1; j++) {
					a[i][j]=a[i][j]*ta-a[k][j]*tb;
				}
			}
		}
	}

	for(i=k; i<equ; i++) {
		if(a[i][col]!=0) return -1;
		// 无解
	}

	if(k<var) {
		// 自由变元有var - k个， 无穷解
		for(i=k-1; i>=0; i--) {
			free_x_num=0;
			for(j=0; j<var; j++) {
				if(a[i][j]!=0&&free_x[j])
					free_x_num++,free_index=j;
			}
			if(free_x_num>1) continue;    // 无法求解出确定的变元.
			temp=a[i][var];
			for(j=0; j<var; j++)
			{
				if(a[i][j]!=0&&j!=free_index) temp-=a[i][j]*x[j];
			}
			x[free_index]=temp/a[i][free_index];    // 求出该变元.
			free_x[free_index]=0;      // 该变元是确定的.
		}
		return var-k;        // 自由变元有var - k个.
	}

	for(i=var-1; i>=0; i--) {
		temp=a[i][var];
		for(j=i+1; j<var; j++) {
			if(a[i][j]!=0) temp-=a[i][j]*x[j];
		}
		if(temp%a[i][i]!=0) return -2;       // 说明有浮点数解，但无整数解.
		x[i]=temp/a[i][i];
	}
	return 0; // 唯一整数解
}

int main() {//Input :  增广矩阵
	int i,j;
	while(scanf("%d%d",&equ,&var)!=EOF) {
		memset(a,0,sizeof(a));
		for(i=0; i<equ; i++) {
			for(j=0; j<var+1; j++) {
				scanf("%d",&a[i][j]);
			}
		}
		int free_num=Gauss(equ,var);
	}
	return 0;
}
