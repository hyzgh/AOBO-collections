/************************************************************/
/* 树链剖分
 */
#include <bits/stdc++.h>
#define pb push_back
#define lc (i << 1)
#define rc (i << 1 | 1)
#define mid (l + r >> 1)
using namespace std;
typedef unsigned long long ull;

const int N = 1e5 + 10;

vector<int> g[N];
int fa[N], sz[N], deep[N], son[N];
int p[N], top[N], dfsp;
ull sum[N << 2], add[N << 2], mul[N << 2];
int n, m;

void dfs1(int u, int dep)
{//fa, sz, deep, son
    sz[u] = 1;
    deep[u] = dep;
    son[u] = -1;
    for(auto i : g[u])
    {
        dfs1(i, dep + 1);
        sz[u] += sz[i];
        if(son[u] == -1 || sz[son[u]] < sz[i])
            son[u] = i;
    }
}

void dfs2(int u, int  Top)
{//p, top
    top[u] = Top;
    p[u] = ++ dfsp;
    if(son[u] + 1)
        dfs2(son[u], Top);
    for(auto i : g[u])
        if(i != son[u])
            dfs2(i, i);
}

void push_up(int i)
{
    sum[i] = sum[lc] + sum[rc];
}

void push_down(int l,  int r, int i)
{
    if(mul[i] - 1)
    {
        sum[lc] *= mul[i];
        mul[lc] *= mul[i];
        add[lc] *= mul[i];
        sum[rc] *= mul[i];
        mul[rc] *= mul[i];
        add[rc] *= mul[i];
        mul[i] =  1;
    }
    if(add[i])
    {
        sum[lc] += add[i] * (ull)(mid - l + 1);
        add[lc] += add[i];
        sum[rc] += add[i] * (ull)(r - mid);
        add[rc] += add[i];
        add[i] = 0;
    }
}

void build(int l, int r, int i = 1)
{
    add[i] = sum[i] = 0;
    mul[i] = 1;
    if(l == r)  return ;
    build(l, mid, lc);
    build(mid + 1, r, rc);
}

void update(int ll, int rr, int l, int r, bool flag, ull x, int i = 1)
{
    if(ll <= l && r <= rr)
    {
        if(flag)
        {// * 
            add[i] *= x;
            mul[i] *= x;
            sum[i] *= x;
        }
        else
        {// +
            sum[i] += x * (ull)(r - l + 1);
            add[i] += x;
        }
        return ;
    }
    push_down(l, r, i);
    if(ll <= mid)
        update(ll, rr, l, mid, flag, x, lc);
    if(rr > mid)
        update(ll, rr, mid + 1, r, flag, x, rc);
    push_up(i);
}

ull query(int ll, int rr, int l, int r, int i = 1)
{
    if(ll <= l && r <= rr)
    {
        return sum[i];
    }
    push_down(l, r, i);
    ull ans = 0;
    if(ll <= mid)
        ans += query(ll, rr, l, mid, lc);
    if(rr > mid)
        ans += query(ll, rr, mid + 1, r, rc);
    return ans;
}

void interval(int u, int v, bool flag, ull x)
{
    int a = top[u], b = top[v];
    while(a != b)
    {
        if(deep[a] < deep[b])
        {
            swap(a, b);
            swap(u, v);
        }
        update(p[a], p[u], 1, n, flag, x);
        u = fa[a];
        a = top[u];
    }
    if(deep[u] < deep[v])
        swap(u, v);
    update(p[v], p[u], 1, n, flag, x);
}

ull get_ans(int u, int v)
{
    int a = top[u], b = top[v];
    ull ans = 0;
    while(a != b)
    {
        if(deep[a] < deep[b])
        {
            swap(a, b);
            swap(u, v);
        }
        ans += query(p[a], p[u], 1, n);
        u = fa[a];
        a = top[u];
    }
    if(deep[u] < deep[v])
        swap(u, v);
    ans += query(p[v], p[u], 1, n);
    return ans;
}

int main()
{
    while(~scanf("%d", &n))
    {
        for(int i = 1; i <= n; i ++)
            g[i].clear();
        for(int i = 2; i <= n; i ++)
        {
            scanf("%d", fa + i);
            g[fa[i]].pb(i);
        }
        dfs1(1, 0);
        dfsp = 0;
        dfs2(1, 1);
        build(1, n);

        scanf("%d", &m);
        while(m --)
        {
            int op, u, v;
            ull x;
            scanf("%d%d%d",&op, &u, &v);

            if(op <= 2)
            {
                scanf("%llu", &x);
                interval(u, v, op & 1, x);
            }
            else if(op == 3)
            {
                interval(u, v, 1, (ull)-1);
                interval(u, v, 0, (ull)-1);
            }
            else
                printf("%llu\n", get_ans(u, v));
        }
    }
    return 0;
}
/************************************************************/
