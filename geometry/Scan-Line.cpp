#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Line{
    double x,y1,y2;
    int val;
    Line(){}
    Line(double x,double y1,double y2,int val):x(x),y1(y1),y2(y2),val(val){};
}s[2005];
int cov[2005<<2];
double x[2005<<2],sum[2005<<2];

bool cmp(const Line &a,const Line &b)
{
    return a.x<b.x;
}
void push_up(int root,int l,int r)
{
    if(cov[root]) sum[root]=x[r+1]-x[l];
    else if(l==r) sum[root]=0;
    else sum[root]=sum[root<<1]+sum[root<<1|1];
}
void update(int L,int R,int val,int root,int l,int r)
{
    if(L<=l&&r<=R)
    {
        cov[root]+=val;
        push_up(root,l,r);
        return ;
    }
    int mid=(l+r)>>1;
    if(L<=mid) update(L,R,val,root<<1,l,mid);
    if(mid<R) update(L,R,val,root<<1|1,mid+1,r);
    push_up(root,l,r);
}
int binary_find(double xx,int tot)
{
    int ll=-1,rr=tot-1;
    while(rr-ll>1)
    {
        int mid=(ll+rr)>>1;
        if(x[mid]>=xx) rr=mid;
        else ll=mid;
    }
    return rr;
}
int main()
{
    int cas=1;
    int n;
    while(~scanf("%d",&n)&&n){
        for(int i=0;i<n;i++){
            double a,b,c,d;
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            s[i*2]=Line(a,b,d,1);
            s[i*2+1]=Line(c,b,d,-1);
            x[i*2]=b;
            x[i*2+1]=d;
        }
        int tot=0;
        sort(s,s+n*2,cmp);
        sort(x,x+n*2);
        tot++; //?
        for(int i=1;i<n*2;i++){
            if(x[i]!=x[i-1]) x[tot++]=x[i];
        }
        double ans=0;
        memset(sum,0,sizeof sum);
        memset(cov,0,sizeof cov);
        for(int i=0;i<n*2-1;i++)
        {
            int l=binary_find(s[i].y1,tot);
            int r=binary_find(s[i].y2,tot)-1;
            update(l,r,s[i].val,1,0,tot-1);
            ans+=sum[1]*(s[i+1].x-s[i].x);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",cas++ , ans);
    }
    return 0;
}
