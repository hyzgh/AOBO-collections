#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+100;
vector<int> prime;
int minp[maxn];//最小质因子
int minpc[maxn];//最小质因子指数
int d[maxn];//约数个数
int sumd[maxn];//约数和
int mu[maxn];//莫比乌斯函数
int phi[maxn];//欧拉函数
int t1[maxn],t2[maxn];//辅助数组
void init()
{
   for(int i=2;i<maxn;i++)
   {
      if(!minp[i])
      {
         minp[i]=i;minpc[i]=1;d[i]=2;sumd[i]=i+1;
         t1[i]=i+1;t2[i]=i;
         mu[i]=-1;phi[i]=i-1;prime.push_back(i);
      }
      for(int j=0,k;j<(int)prime.size()&&(k=i*prime[j])<maxn;j++)
      {
         minp[k]=prime[j];
         if(i%prime[j]==0)
         {
            minpc[k]=minpc[i]+1;d[k]=d[i]/(minpc[i]+1)*(minpc[k]+1);
            t2[k]=t2[i]*prime[j];t1[k]=t1[i]+t2[k];sumd[k]=sumd[i]/t1[i]*t1[k];
            mu[k]=0;phi[k]=phi[i]*prime[j];
            break;
         }
         else
         {
            minpc[k]=1;d[k]=d[i]*2;sumd[k]=sumd[i]*sumd[prime[j]];
            t1[k]=1+prime[j];t2[k]=prime[j];
            mu[k]=-mu[i];phi[k]=phi[i]*(prime[j]-1);
         }
      }
   }
}
 
int main()
{
   init();
   return 0;
}
