/*
��˹��Ԫ���ⷽ����(Gauss-Jordan elimination).(-2��ʾ�и������⣬���������⣬-1��ʾ�޽⣬0��ʾΨһ�⣬����0��ʾ����⣬���������ɱ�Ԫ�ĸ���)
��equ�����̣�var����Ԫ�������������Ϊequ,�ֱ�Ϊ0��equ-1,����Ϊvar+1,�ֱ�Ϊ0��var.
*/
#include<cstdio>
#include<iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstring>
using namespace std;

const int maxn =50;
int equ,var;         //��equ�����̣�var����Ԫ
int a[maxn][maxn] ;  //�������
int x[maxn];         //�⼯
bool free_x[maxn];   //����Ƿ��ǲ�ȷ���ı�Ԫ����ʼ��Ϊtrue,ȷ��Ϊ0

inline int gcd(int a,int b){
	return b == 0 ? a : gcd(b, a%b);
}

inline int lcm(int a,int b){
	return a/gcd(a,b)*b;
}

int Gauss(int equ,int var)
{
	int i,j,k;
	int max_r;     // ��ǰ���о���ֵ������.
	int col;       //��ǰ�������
	int ta,tb;
	int LCM, temp;
	int free_x_num;
	int free_index;

	for(int i=0; i<=var; i++) {
		x[i]=0;           //��ʼ���⼯
		free_x[i]=true;
	}
    //ת��Ϊ������.
	col=0;        // ��ǰ�������
	for(k=0; k<equ&&col<var; k++,col++) {
		max_r=k;
		for(i=k+1; i<equ; i++) {//�б��
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
		// �޽�
	}

	if(k<var) {
		// ���ɱ�Ԫ��var - k���� �����
		for(i=k-1; i>=0; i--) {
			free_x_num=0;
			for(j=0; j<var; j++) {
				if(a[i][j]!=0&&free_x[j])
					free_x_num++,free_index=j;
			}
			if(free_x_num>1) continue;    // �޷�����ȷ���ı�Ԫ.
			temp=a[i][var];
			for(j=0; j<var; j++)
			{
				if(a[i][j]!=0&&j!=free_index) temp-=a[i][j]*x[j];
			}
			x[free_index]=temp/a[i][free_index];    // ����ñ�Ԫ.
			free_x[free_index]=0;      // �ñ�Ԫ��ȷ����.
		}
		return var-k;        // ���ɱ�Ԫ��var - k��.
	}

	for(i=var-1; i>=0; i--) {
		temp=a[i][var];
		for(j=i+1; j<var; j++) {
			if(a[i][j]!=0) temp-=a[i][j]*x[j];
		}
		if(temp%a[i][i]!=0) return -2;       // ˵���и������⣬����������.
		x[i]=temp/a[i][i];
	}
	return 0; // Ψһ������
}

int main() {//Input :  �������
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
