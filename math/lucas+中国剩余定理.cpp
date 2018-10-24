/************************************************************/
/* Lucas定理
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//求C_n^k%p  其中p不是素数
long long exgcd(long long a,long long b,long long &x,long long &y)
{
    long long d=a;
    if(b!=0)
    {
        d=exgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }else{
        x=1;
        y=0;
    }
    return d;
}
long long pow_mod(long long a,long long b,long long p)
{
    long long res=1;
    while(b)
    {
        if(b&1) res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
long long mod_inverser(long long a,long long m)
{
    long long x,y;
    exgcd(a,m,x,y);
    return (m+x%m)%m;
}
long long cal(long long n,long long pi,long long pk)
{
    if(n==0) return 1;
    long long ans=1;
    if(n/pk)
    {
         for(long long i=2;i<=pk;i++)
         {
             if(i%pi)
                ans=ans*i%pk;
         }
         ans=pow_mod(ans,n/pk,pk);
    }
    for(long long i=2;i<=n%pk;i++)
    {
        if(i%pi)
            ans=ans*i%pk;
    }
    return ans*cal(n/pi,pi,pk)%pk;
}
long long C(long long n,long long k,long long p,long long pi,long long pk)
{
    if(k>n) return 0;
    long long a=cal(n,pi,pk),b=cal(k,pi,pk),c=cal(n-k,pi,pk);
    long long x=0,ans;
    for(long long i=n;i;i/=pi) x+=i/pi;
    for(long long i=k;i;i/=pi) x-=i/pi;
    for(long long i=n-k;i;i/=pi) x-=i/pi;
    ans=a*mod_inverser(b,pk)%pk*mod_inverser(c,pk)*pow_mod(pi,x,pk)%pk;
    return ans*(p/pk)%p*mod_inverser(p/pk,pk)%p;
}

int main()
{
    long long n,k,p;
    cin>>n>>k>>p;
    long long ans=0;
    for(long long x=p,i=2;i<=p;i++)
    {
        if(x%i==0)
        {
            long long pk=1;
            while(x%i==0)
            {
                pk*=i;
                x/=i;
            }
            ans=(ans+C(n,k,p,i,pk))%p;
        }
    }
    cout<<ans<<endl;
    return 0;
}
/************************************************************/
