#include<cstdio>
#include<iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=10005;
const double eps=1e-12;
double a[maxn][maxn];  // �������
int equ,var;     //equ������,var������
double x[maxn];   //�⼯
bool free_x[maxn];
int n;

//�жϸ������Ƿ�����Χ�ڿ�������0
int sgn(double x) {
	return (x>eps)-(x<-eps);
}
// ��˹��Ԫ���ⷽ����(Gauss-Jordan elimination).(-1��ʾ�޽⣬0��ʾΨһ�⣬����0��ʾ����⣬���������ɱ�Ԫ�ĸ���)
int Gauss(int equ,int var) {
	int i,j,k;
	int max_r;   // ��ǰ���о���ֵ������.
	int col;     // ��ǰ�������.
	double temp;
	int free_x_num;
	int free_index;
	// ת��Ϊ������.
	col=0;    // ��ǰ�������.
	memset(free_x,true,sizeof(free_x));
	for (k=0;k<equ&&col<var;k++,col++) {
		max_r=k;
		for(i=k+1;i<equ;i++) {
			if(sgn(fabs(a[i][col])-fabs(a[max_r][col]))>0)
		         max_r=i;
 		}
 		if(max_r!=k) {
 			// ���k�н���.
 			for(j=k;j<var+1;j++)
 			   swap(a[k][j],a[max_r][j]);
		}
		if(sgn(a[k][col])==0) {
			// ˵����col�е�k������ȫ��0�ˣ�����ǰ�е���һ��.
			k--;continue;
		}
		for(i=k+1;i<equ;i++) {
			// ö��Ҫɾȥ����.
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
		return -1; // �޽�
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
		return var-k; // �����⣬���ɱ�Ԫ����
	}
	for(i=var-1;i>=0;i--) {
		temp=a[i][var];
		for(j=i+1;j<var;j++) {
			if(sgn(a[i][j])!=0)
			  temp-=a[i][j]*x[j];
		}
		x[i]=temp/a[i][i];
	}
	return 0; // Ψһ��
}
int main() {
	int i,j;
	while(scanf("%d%d",&equ,&var)!=EOF) {
		memset(a,0,sizeof(a));
		for(i=0; i<equ; i++) {
			for(j=0; j<var+1; j++) {
				scanf("%lf",&a[i][j]); // �����������
			}
		}
		int free_num=Gauss(equ,var);
	}
	return 0;
}
