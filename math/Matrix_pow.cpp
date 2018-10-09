#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N = 2;
ll k, n, b, mod ;

struct matrix
{
    ll m[N][N];
    void init0()
    {//零矩阵
        memset(m, 0, sizeof m);
    }
    void init1()
    {//单位阵
        init0();
        for(int i = 0; i < N; i ++)
        {
            m[i][i] = 1;
        }
    }
    void init()
    {
        init0();
        m[0][0] = m[0][1] = m[1][0] = 1;
    }
};

matrix operator +(const matrix&a, const matrix&b)
{//重载矩阵加法
    matrix c;
    for(int i = 0; i < N; i ++)
        for(int j = 0; j < N; j ++)
    {
        c.m[i][j] = a.m[i][j]+b.m[i][j];
        c.m[i][j] %= mod;
    }
    return c;
}

matrix operator -(const matrix&a, const matrix&b)
{//重载矩阵减法
    matrix c;
    for(int i = 0; i < N; i ++)
        for(int j = 0; j < N; j ++)
    {
        c.m[i][j] = a.m[i][j]-b.m[i][j] + mod;
        c.m[i][j] %= mod;
    }
    return c;
}

matrix operator *(const matrix&a, const matrix&b)
{//重载矩阵乘法
    matrix c;
    for(int i = 0; i < N; i ++)
        for(int j = 0; j < N ; j ++)
    {
        c.m[i][j] = 0;
        for(int k = 0; k < N; k ++)
        {
            c.m[i][j] += a.m[i][k]*b.m[k][j];
            c.m[i][j] %= mod;
        }
    }
    return c;
}

matrix power(matrix x, ll n)
{//矩阵快速幂
    matrix a;
    a.init1();
    while(n)
    {
        if(n&1) a = a * x;
        x = x * x;
        n >>= 1;
    }
    return a;
}

matrix S(matrix a, ll k)
{//A^1+A^2+ ... + A^n
    matrix b;   b.init1();
    if(k==1)    return a;
    if(k==0)    return b;
    matrix x = power(a, (k+1)>>1);
    matrix y = S(a, k>>1);
    if(k&1)
        return a+(a+x)*y;
    return (b+x)*y;
}

int main()
{
    matrix f;   f.init0();
    return 0;
}
