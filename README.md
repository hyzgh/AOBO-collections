# AOBO-collections

[TOC]
## vim 配置
```
syntax on
set nu
set tabstop=4
set shiftwidth=4
colo evening
set mouse=a
set cin

map <F2> :call Import() <CR>
map <F3> :only<CR>:60vsp in<CR>:sp out<CR><C-W><RIGHT>
nnoremap <F9>   <Esc>:w<CR> :! ctags %<CR> :!g++ -std=c++11 % -o /tmp/a.out && /tmp/a.out<CR>
map <F10> <Esc>:w<CR>gg"+1000Y

func Import()
    exec "r ~/code/z"
endfunc
```

## 起手式
```
#include<bits/stdc++.h>
#define x first
#define y second
#define ok cout << "ok" << endl;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const long double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const double Eps = 1e-7;
const int N = 1e5+9;

int main(void) {
    if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}

    return 0;
}
```

## Alpha-Beta 剪枝
```
/************************************************************/
/* Alpha-Beta 剪枝
 */
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;

#define ALLEDGES ((1 << 19) - 2)

typedef pair<int,int> pii;

map<pii, int> edgeID;
int triangle[9];

// 给边和三角形编码
void encode() {
    edgeID[pii(1, 2)] = 1 << 1; edgeID[pii(1, 3)] = 1 << 2; edgeID[pii(2, 3)] = 1 << 3;
    edgeID[pii(2, 4)] = 1 << 4; edgeID[pii(2, 5)] = 1 << 5; edgeID[pii(3, 5)] = 1 << 6;
    edgeID[pii(3, 6)] = 1 << 7; edgeID[pii(4, 5)] = 1 << 8; edgeID[pii(5, 6)] = 1 << 9;
    edgeID[pii(4, 7)] = 1 << 10; edgeID[pii(4, 8)] = 1 << 11; edgeID[pii(5, 8)] = 1 << 12;
    edgeID[pii(5, 9)] = 1 << 13; edgeID[pii(6, 9)] = 1 << 14; edgeID[pii(6, 10)] = 1 << 15;
    edgeID[pii(7, 8)] = 1 << 16; edgeID[pii(8, 9)] = 1 << 17; edgeID[pii(9, 10)] = 1 << 18;

    triangle[0] = (1 << 1) + (1 << 2) + (1 << 3);
    triangle[1] = (1 << 4) + (1 << 5) + (1 << 8);
    triangle[2] = (1 << 3) + (1 << 5) + (1 << 6);
    triangle[3] = (1 << 6) + (1 << 7) + (1 << 9);
    triangle[4] = (1 << 10) + (1 << 11) + (1 << 16);
    triangle[5] = (1 << 8) + (1 << 11) + (1 << 12);
    triangle[6] = (1 << 12) + (1 << 13) + (1 << 17);
    triangle[7] = (1 << 9) + (1 << 13) + (1 << 14);
    triangle[8] = (1 << 14) + (1 << 15) + (1 << 18);
}

// 计算新添加一条边可以获得的分数
int count(int status, int edgeID) {
    int ans = 0;
    for(int i = 0; i < 9; i++) {
        if((triangle[i] & edgeID) && (triangle[i] & status) == triangle[i])
            ans++;
    }
    return ans;
}

int findMax(int beta, int status, int score);

// 从当前状态status出发，搜索能取到的最低分
int findMin(int alpha, int status, int score) {
    // 所有的边都已经添加完，返回
    if(status == ALLEDGES)
        return score;
    int t = 1;
    // 枚举剩余可取的边
    int remain = ~status & ALLEDGES;
    while(remain) {
        int i = remain & -remain;
        int newStatus = status | i;
        int cnt = count(newStatus, i);
        // 假如添加一边有得分，则可以继续再走一步，否则轮到对方走
        t = cnt ? min(t, findMin(alpha, newStatus, score - cnt)) : min(t, findMax(t, newStatus, score));
        // alpha剪枝
        if(t <= alpha)
            return alpha;
        remain -= i;
    }
    return t;
}

// 从当前状态status出发，搜索能取到的最高分
int findMax(int beta, int status, int score) {
    // 所有的边都已经添加完，返回
    if(status == ALLEDGES)
        return score;
    int t = -1;
    // 枚举剩余可取的边
    int remain = ~status & ALLEDGES;
    while(remain) {
        int i = remain & -remain;
        int newStatus = status | i;
        int cnt = count(newStatus, i);
        // 假如添加一边有得分，则可以继续再走一步，否则轮到对方走
        t = cnt ? max(t, findMax(beta, newStatus, score + cnt)) : max(t, findMin(t, newStatus, score));
        // beta剪枝
        if(t >= beta)
            return beta;
        remain -= i;
    }
    return t;
}

int main(void) {
    encode();
    int allKase, edgeNum;
    scanf("%d", &allKase);
    for(int kase = 1; kase <= allKase; kase++) {
        printf("Game %d: ", kase);
        scanf("%d", &edgeNum);
        int score = 0, now = 0, status = 0;
        for(int i = 0, u, v; i < edgeNum; i++) {
            scanf("%d%d", &u, &v);
            if(u > v) {
                swap(u, v);
            }
            status |= edgeID[pii(u, v)];
            int cnt = count(status, edgeID[pii(u, v)]);
            // 假如添加一边有得分，则可以继续再走一步，否则轮到对方走
            if(cnt)
                score += now == 0 ? cnt : -cnt;
            else
                now ^= 1;
        }
        printf("%c wins.\n", (now == 0 ? findMax(1, status, score) : findMin(-1, status, score)) > 0 ? 'A' : 'B');
    }

    return 0;
}
/************************************************************/
```

## 数据结构
### AC自动机
```
/********************************************************************************/
/* AC自动机：解决多个模式串匹配问题(Tested 9+ times)
 */
struct AC {
    int next[N][26], fail[N], idx, root, end[N]; // 可以修改下数组大小，以防MLE
    void init() {
        idx = 0;
        root = newNode();
    }
    int newNode() {
        for(int i = 0; i < 26; i++)
            next[idx][i] = -1;
        end[idx] = 0;
        return idx++;
    }
    void insert(char s[]) {
        int len = strlen(s), now = root;
        for(int i = 0; i < len; i++) {
            if(next[now][s[i] - 'a'] == -1)
                next[now][s[i] - 'a'] = newNode();
            now = next[now][s[i] - 'a'];
        }
        end[now]++; //根据实际情况可能需要保存不同的信息
    }
    void build() {
        queue<int> que;
        fail[root] = root;
        for(int i = 0; i < 26; i++) {
            if(next[root][i] == -1) {
                next[root][i] = root;
            }
            else {
                fail[next[root][i]] = root;
                que.push(next[root][i]);
            }
        }
        while(que.size()) {
            int now = que.front();
            que.pop();
            for(int i = 0; i < 26; i++) {
                if(next[now][i] == -1) {
                    next[now][i] = next[fail[now]][i];
                }
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    que.push(next[now][i]);
                }
            }
        }
    }
    int query(char s[]) {
        int ans = 0, len = strlen(s), now = root;
        for(int i = 0; i < len; i++) {
            now = next[now][s[i] - 'a'];
            int temp = now;
            while(temp != root) {
                ans += end[temp];
                end[temp] = 0;      //为避免重复统计，清零。必要时可以设置个flag数组。
                temp = fail[temp];
            }
        }
        return ans;
    }
    void debug() {
        printf("%37c", ' ');
        for(int i = 0; i < 26; i++)
            printf("%2c", i + 'a');
        printf("\n");
        for(int i = 0;i < idx;i++) {
            printf("id = %3d,fail = %3d,end = %3d,chi = [",i,fail[i],end[i]);
            for(int j = 0;j < 26;j++)
                printf("%2d",next[i][j]);
            printf("]\n");
        }
    }
}ac;
/********************************************************************************/
```
### 回文自动机
```
/************************************************************/
/* 回文自动机：解决一类回文字符串问题(Tested 6 times)
 * 时间复杂度：O(|S| * log(字符集个数))
 */
const int MAXN = 1e5 + 9;
const int NN = 26;  //字符集个数

struct Palindromic_Tree {
    int next[MAXN][NN];//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[MAXN];//fail指针，失配后跳转到fail指针指向的节点
    int cnt[MAXN]; //cnt[i]表示i表示的回文字符串在整个字符串中出现了多少次
    int num[MAXN]; //num[i]表示i表示的回文字符串中有多少个本质不同的字符串（包括本身）
    int len[MAXN];//len[i]表示节点i表示的回文串的长度
    int S[MAXN];//存放添加的字符
    int last;//指向上一个字符所在的节点，方便下一次add
    int n;//字符数组指针
    int p;//节点指针

    int newnode(int l) {//新建节点
        for(int i = 0; i < NN; i++) next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }

    void init() {//初始化
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        S[n] = -1;//开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }

    int get_fail(int x) {//和KMP一样，失配后找一个尽量最长的
        while(S[n - len[x] - 1] != S[n]) x = fail[x];
        return x ;
    }

    // 插入的是字符
    void add(int c) {
        c -= 'a';
        S[++ n] = c;
        int cur = get_fail(last);//通过上一个回文串找这个回文串的匹配位置
        if(!next[cur][c]) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);//新建节点
            fail[now] = next[get_fail(fail[cur])][c];//和AC自动机一样建立fail指针，以便失配后跳转
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = next[cur][c];
        cnt[last]++;
    }

    void count () {
        for(int i = p - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
}pt;
/************************************************************/
```

### SAM
```
/************************************************************/
/* 后缀自动机(Tested 8 times)
 * 数组实现，效率较高
 * 开点时才初始化，在多组样例的情况下会比直接memset整个数组快很多，比如HDU4416
 * 时间复杂度：O(n * CHARSET_SIZE)
 * used variables: N, 
 */
const int CHARSET_SIZE = 26;
const int MAXN = N << 1;  // 注意在SAM里面开的数组大小应为MAXN，因为长度为n的字符串最多会有2*n个结点

struct SuffixAutomaton {
    int ch[MAXN][CHARSET_SIZE], len[MAXN], fail[MAXN], sz, last, cntPos[MAXN];
    int tong[MAXN], topo[MAXN];
    void init() {
        len[0] = 0;
        sz = 1;
        last = newnode(0);
    }
    int newnode(int le) {
        len[sz] = le;
        fail[sz] = 0;
        for(int i = 0; i < CHARSET_SIZE; i++)
            ch[sz][i] = 0;
        return sz++;
    }
    void insert(int c) {
        c -= 'a';
        int v = last, u = newnode(len[v] + 1);
        last = u;
        cntPos[u] = 1;
        for(; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
        if(!v){fail[u] = 1; return;}
        int o = ch[v][c];
        if(len[v] + 1 == len[o]) fail[u] = o;
        else {
            int n = newnode(len[v] + 1);
            cntPos[n] = 0;
            memcpy(ch[n], ch[o], sizeof(ch[0]));
            fail[n] = fail[o];
            fail[u] = fail[o] = n;
            for(; ch[v][c] == o; v = fail[v]) ch[v][c] = n;
        }
    }
    void topoSort() {
        memset(tong, 0, sizeof tong);
        tong[0] = 1;
        for(int i = 1; i < sz; i++)
            tong[len[i]]++;
        for(int i = 1; i < sz; i++)
            tong[i] += tong[i - 1];
        for(int i = sz - 1; i >= 1; i--)
            topo[--tong[len[i]]] = i;
    }
}sam;
/************************************************************/
```

### 树链剖分
```
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
```

### splay
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
const int N=200005, inf=0x3f3f3f3f;

typedef struct splaynode* node;
struct splaynode {
    node pre, ch[2];
    ll value, lazy, max, sum;
    int size, rev;
    void init(int _value) {
        pre=ch[0]=ch[1]=NULL;
        max=value=sum=_value;
        lazy=rev=0;
        size=1;
    }
}mem[N];
int memtop;

stack<node> S;
node root;

inline int getsize(node &x) {
    return x ? x->size : 0;
}

void pushdown(node &x) {
    if (!x) return;
    if (x->lazy) {
        ll w = x->lazy;
        x->value += w;
        if (x->ch[0]) {
            x->ch[0]->lazy += w;
            x->ch[0]->max += w;
            x->ch[0]->sum += w*getsize(x->ch[0]);
        }
        if (x->ch[1]) {
            x->ch[1]->lazy += w;
            x->ch[1]->max += w;
            x->ch[1]->sum += w*getsize(x->ch[1]);
        }
        x->lazy = 0;
    }
    if (x->rev) {
        node t = x->ch[0];
        x->ch[0] = x->ch[1];
        x->ch[1] = t;
        x->rev = 0;
        if (x->ch[0]) x->ch[0]->rev ^= 1;
        if (x->ch[1]) x->ch[1]->rev ^= 1;
    }
}

void update(node &x) {
    if (!x) return;
    x->size = 1;
    x->max = x->value;
    x->sum = x->value;
    if (x->ch[0]) {
        x->sum += x->ch[0]->sum;
        x->max = max(x->max, x->ch[0]->max);
        x->size += x->ch[0]->size;
    }
    if (x->ch[1]) {
        x->sum += x->ch[1]->sum;
        x->max = max(x->max, x->ch[1]->max);
        x->size += x->ch[1]->size;
    }
}

void rotate(node &x, int d) {
    node y = x->pre;
    pushdown(y);
    pushdown(x);
    pushdown(x->ch[d]);
    y->ch[!d] = x->ch[d];
    if (x->ch[d] != NULL) x->ch[d]->pre = y;
    x->pre = y->pre;
    if (y->pre != NULL)
        if (y->pre->ch[0] == y) y->pre->ch[0] = x; else y->pre->ch[1] = x;
    x->ch[d] = y;
    y->pre = x;
    update(y);
    if (y == root) root = x;
}

void splay(node &src, node &dst) {
    pushdown(src);
    while (src!=dst) {
        if (src->pre==dst) {
            if (dst->ch[0]==src) rotate(src, 1); else rotate(src, 0);
            break;
        }
        else {
            node y=src->pre, z=y->pre;
            if (z->ch[0]==y) {
                if (y->ch[0]==src) {
                    rotate(y, 1);
                    rotate(src, 1);
                }else {
                    rotate(src, 0);
                    rotate(src, 1);
                }
            }
            else {
                if (y->ch[1]==src) {
                    rotate(y, 0);
                    rotate(src, 0);
                }else {
                    rotate(src, 1);
                    rotate(src, 0);
                }
            }
            if (z==dst) break;
        }
        update(src);
    }
    update(src);
}

void select(int k, node &f) {  //
    int tmp;
    node t = root;
    while (1) {
        pushdown(t);
        tmp = getsize(t->ch[0]);
        if (k == tmp + 1) break;
        if (k <= tmp) t = t->ch[0];
        else {
            k -= tmp + 1;
            t = t->ch[1];
        }
    }
    pushdown(t);
    splay(t, f);
}

inline void selectsegment(int l,int r) { // 提取区间[l, r]
    select(l, root);
    select(r + 2, root->ch[1]);
}

void insert(int pos, int value) {  //在pos位置后面插入一个新值value
    selectsegment(pos + 1, pos);
    node t;
    node x = root->ch[1];
    pushdown(root);
    pushdown(x);
    if (!S.empty()) {
        t = S.top();
        S.pop();
    } else {
        t = &mem[memtop++];
    }
    t->init(value);
    t->ch[1] = x;
    x->pre = t;
    root->ch[1] = t;
    t->pre = root;
    splay(x, root);
}

void add(int a,int b, int value) {  //区间[a,b]中的数都加上value
    selectsegment(a, b);
    node x = root->ch[1]->ch[0];
    pushdown(x);
    update(x);
    x->max += value;
    x->lazy += value;
    splay(x, root);
}

void reverse(int a, int b) {   //区间[a,b]中的数翻转
    selectsegment(a, b);
    root->ch[1]->ch[0]->rev ^= 1;
    node x = root->ch[1]->ch[0];
    splay(x, root);
}

void revolve(int a, int b, int t) { //区间[a,b]中的数向后循环移t位
    node p1, p2;
    selectsegment(a, b);
    select(b + 1 - t, root->ch[1]->ch[0]);
    p1 = root->ch[1]->ch[0];
    pushdown(p1);
    p2 = p1->ch[1];
    p1->ch[1] = NULL;

    select(a + 1, root->ch[1]->ch[0]);
    p1 = root->ch[1]->ch[0];
    pushdown(p1);
    p1->ch[0] = p2;
    p2->pre = p1;

    splay(p2, root);
}

ll getmax(int a, int b) {   //取[a,b]中最小的值
    selectsegment(a, b);
    node x = root->ch[1];
    pushdown(x);
    x = x->ch[0];
    pushdown(x);
    update(x);
    return x->max;
}

ll getsum(int a, int b) { //
    selectsegment(a, b);
    node x = root->ch[1];
    pushdown(x);
    x = x->ch[0];
    pushdown(x);
    update(x);
    return x->sum;
}

void erase(int pos) {               //抹去第pos个元素
    selectsegment(pos, pos);
    pushdown(root->ch[1]);
    S.push(root->ch[1]->ch[0]);        //回收内存
    root->ch[1]->ch[0] = NULL;
    node x = root->ch[1];
    splay(x, root);
}


void cutandmove(int a,int b,int c)   // [a, b]移动到c后面
{
    selectsegment(a,b);
    node CutRoot=root->ch[1]->ch[0];
    CutRoot->pre=NULL;
    root->ch[1]->size-=CutRoot->size;
    root->ch[1]->ch[0]=NULL;

    selectsegment(c+1,c);

    CutRoot->pre=root->ch[1];
    root->ch[1]->ch[0]=CutRoot;
    root->ch[1]->size+=CutRoot->size;
}

void cut(int a,int b)  // 删除区间[l, r]
{
    selectsegment(a,b);
    node CutRoot=root->ch[1]->ch[0];
    CutRoot->pre=NULL;
    root->size-=CutRoot->size;
    root->ch[1]->size-=CutRoot->size;
    root->ch[1]->ch[0]=NULL;
}

vector<int> ans;
void inorder(node x) // 中序遍历结果
{
    if (!x) return;
    pushdown(x);
    inorder(x->ch[0]);
    if (x->value!=inf) ans.push_back(x->value);
    inorder(x->ch[1]);
}

void initsplaytree(ll *a, int n) { // 初始化
    memtop = 0;
    root = &mem[memtop++];
    root->init(inf);
    root->ch[1] = &mem[memtop++];
    root->ch[1]->init(inf);
    while (!S.empty()) S.pop();
    for (int i = 0; i < n; i++) insert(i, a[i]);
}
```

### 带权并查集
```
/************************************************************/
/* 带权并查集
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;

struct pre
{
    int p[N], dis[N];
    void init(int n)
    {
        memset(dis, 0, sizeof dis);
        for(int i = 0; i <= n; i ++)
            p[i] = i;
    }
    int Find(int x)
    {
        if(x == p[x])   return p[x];
        int fa = Find(p[x]);
        dis[x] += dis[p[x]];
        return p[x] = fa;
    }
    void Mix(int x, int y ,int dis_xy)
    {
        int fx = Find(x), fy = Find(y);
        if(fx==fy)  return ;
        p[fy] = fx;
        dis[fy] = dis[x] + dis_xy - dis[y];
    }
};
/************************************************************/
```

### 线段树
#### 扫描线
```
/************************************************************/
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
/************************************************************/
```
#### 二维线段树
```
/************************************************************/
/* segtree2D-sum (Tested 0 times)
 * 单点更新, 区间查询
 * 注意修改N的大小
 * 注意下标从0开始
 * 注意n, m表示n行, m列
 */
int t[4*N][4*N], a[N][N], n, m;

void build_y (int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry)
        if (lx == rx)
            t[vx][vy] = a[lx][ly];
        else
            t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
    else {
        int my = (ly + ry) / 2;
        build_y (vx, lx, rx, vy*2, ly, my);
        build_y (vx, lx, rx, vy*2+1, my+1, ry);
        t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
    }
}
 
void build_x (int vx, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        build_x (vx*2, lx, mx);
        build_x (vx*2+1, mx+1, rx);
    }
    build_y (vx, lx, rx, 1, 0, m-1);
}

void update_y (int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
    if (ly == ry) {
        if (lx == rx)
            t[vx][vy] = new_val;
        else
            t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
    }
    else {
        int my = (ly + ry) / 2;
        if (y <= my)
            update_y (vx, lx, rx, vy*2, ly, my, x, y, new_val);
        else
            update_y (vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
        t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
    }
}
 
void update_x (int vx, int lx, int rx, int x, int y, int new_val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx)
            update_x (vx*2, lx, mx, x, y, new_val);
        else
            update_x (vx*2+1, mx+1, rx, x, y, new_val);
    }
    update_y (vx, lx, rx, 1, 0, m-1, x, y, new_val);
}

int sum_y (int vx, int vy, int tly, int try_, int ly, int ry) {
    if (ly > ry)
        return 0;
    if (ly == tly && try_ == ry)
        return t[vx][vy];
    int tmy = (tly + try_) / 2;
    return sum_y (vx, vy*2, tly, tmy, ly, min(ry,tmy))
        + sum_y (vx, vy*2+1, tmy+1, try_, max(ly,tmy+1), ry);
}
 
int sum_x (int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx)
        return 0;
    if (lx == tlx && trx == rx)
        return sum_y (vx, 1, 0, m-1, ly, ry);
    int tmx = (tlx + trx) / 2;
    return sum_x (vx*2, tlx, tmx, lx, min(rx,tmx), ly, ry)
        + sum_x (vx*2+1, tmx+1, trx, max(lx,tmx+1), rx, ly, ry);
}
/************************************************************/
```
#### 非递归写法
##### 单点修改
```
/****************************************/
/* used variable: n, N, tree[2*N];
 */
int n, tree[2*N];

void build(){
    for(int i=n-1; i>0; i--)
        tree[i]=tree[i<<1]+tree[i<<1|1];
}

void modify(int p, int value){
    for(tree[p+=n]=value; p>1; p>>=1)
        tree[p>>1]=tree[p]+tree[p^1];
}

int query(int l, int r){
    int res=0;
    for(l+=n, r+=n; l<r; l>>=1, r>>=1){
        if(l&1) res+=tree[l++];
        if(r&1) res+=tree[--r];
    }
    return res;
}
/****************************************/
```
##### 区间修改
```
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
```

### 主席树
#### 静态第K大
```
/************************************************************/
/* 静态第k大（主席树）
 */
#include<bits/stdc++.h>
#define x first
#define y second
#define ok cout << "ok" << endl;
#define okd(d) cout << "ok " << d << endl;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const long double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const ll LINF = 9223372036854775807;
const double Eps = 1e-7;
const int N = 1e5+9;

#define mid ((l + r) >> 1)
#define lson (rt << 1)
#define rson (rt << 1 | 1)

int sum[N * 20], tot, rt[N * 20], ls[N * 20], rs[N * 20];
int T, n, a[N], b[N], sz, l, r, k, q;

void build(int &rt, int l, int r) {
    rt = ++tot;
    sum[rt] = 0;
    if(l == r)
        return;
    build(ls[rt], l, mid);
    build(rs[rt], mid + 1, r);
}

void pushup(int rt) {
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
}

void update(int &rt, int last, int l, int r, int val) {
    rt = ++tot;
    if(l == r) {
        sum[rt] = sum[last] + 1;
        return;
    }

    ls[rt] = ls[last];
    rs[rt] = rs[last];

    if(val <= mid)
        update(ls[rt], ls[last], l, mid, val);
    else
        update(rs[rt], rs[last], mid + 1, r, val);
    pushup(rt);
}

int query(int rt1, int rt2, int l, int r, int k) {
    if(l == r)
        return l;
    int cnt = sum[ls[rt2]] - sum[ls[rt1]];
    if(k <= cnt) {
        return query(ls[rt1], ls[rt2], l, mid, k);
    }
    else {
        return query(rs[rt1], rs[rt2], mid + 1, r, k - cnt);
    }
}


void work() {
    scanf("%d%d%d", &l, &r, &k);
    int ans = query(rt[l - 1], rt[r], 1, sz, k);
    printf("%d\n", b[ans]);
}

int main(void) {
    if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            b[i] = a[i];
        }
        sort(b + 1, b + n + 1);
        sz = unique(b + 1, b + n + 1) - (b + 1);
        tot = 0;
        build(rt[0], 1, sz);
        for(int i = 1; i <= n; i++) {
            a[i] = lower_bound(b + 1, b + sz + 1, a[i]) - b;
            update(rt[i], rt[i - 1], 1, sz, a[i]);
        }
        while(q--) {
            work();
        }
    }

    return 0;
}
/************************************************************/
```

#### 动态第K大
```
/************************************************************/
/* 动态求第k大：BIT + 主席树
 */

#include<bits/stdc++.h>
#define x first
#define y second
#define ok cout << "ok" << endl;
#define okd(d) cout << "ok " << d << endl;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const long double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const ll LINF = 9223372036854775807;
const double Eps = 1e-7;

const int N = 5e4 + 9;
const int M = 1e4 + 9;

#define mid ((l + r) >> 1)

struct Node {
    int data, left, right;
}tree[N * 50];

vi p, q;
char op[9], O[M];
int cnt, tot, a[N], b[2 * N], L[M], R[M], sz, K[M], rt[2 * N], n, m, T;

void build(int &rt, int x, int l, int r) {
    tree[++tot] = tree[rt];
    rt = tot;
    tree[rt].data++;
    if(l == r)
        return;
    if(x <= mid)
        build(tree[rt].left, x, l, mid);
    else
        build(tree[rt].right, x, mid + 1, r);
}

void insert(int &rt, int x, int y, int l, int r) {
    tree[++tot] = tree[rt];
    rt = tot;
    tree[rt].data += y;
    if(l == r)
        return;
    if(x <= mid)
        insert(tree[rt].left, x, y, l, mid);
    else
        insert(tree[rt].right, x, y, mid + 1, r);
}

void bitInsert(int i, int x, int y) {
    while(i <= n) {
        insert(rt[i], x, y, 1, sz);
        i += i & -i;
    }
}

int query(int k, int l, int r) {
    if(l == r)
        return l;
    int cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < p.size(); i++)
        cnt1 += tree[tree[p[i]].left].data;
    for(int i = 0; i < q.size(); i++)
        cnt2 += tree[tree[q[i]].left].data;
    if(cnt2 - cnt1 >= k) {
        for(int i = 0; i < p.size(); i++)
            p[i] = tree[p[i]].left;
        for(int i = 0; i < q.size(); i++)
            q[i] = tree[q[i]].left;
        return query(k, l, mid);
    }
    else {
        for(int i = 0; i < p.size(); i++)
            p[i] = tree[p[i]].right;
        for(int i = 0; i < q.size(); i++)
            q[i] = tree[q[i]].right;
        return query(k - (cnt2 - cnt1), mid + 1, r);
    }
}

int solve(int l, int r, int k) {
    p.clear(); q.clear();
    if(l > 0)
        p.push_back(rt[l + n]);
    q.push_back(rt[r + n]);
    while(l) {
        p.push_back(rt[l]);
        l -= l & -l;
    }
    while(r) {
        q.push_back(rt[r]);
        r -= r & -r;
    }
    return query(k, 1, sz);
}


int main(void) {
    if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
    scanf("%d", &T);
    while(T--) {
        memset(rt, 0, sizeof rt);
        memset(tree, 0, sizeof tree);
        scanf("%d%d", &n, &m);
        cnt = tot = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            b[++cnt] = a[i];
        }
        for(int i = 1; i <= m; i++) {
            scanf("%s%d%d", op, &L[i], &R[i]);
            O[i] = op[0];
            if(op[0] == 'Q')
                scanf("%d", &K[i]);
            else
                b[++cnt] = R[i];
        }
        sort(b + 1, b + cnt + 1);
        sz = unique(b + 1, b + cnt + 1) - (b + 1);
        for(int i = 1; i <= n; i++) {
            a[i] = lower_bound(b + 1, b + sz + 1, a[i]) - b;
        }
        for(int i = 1; i <= n; i++) {
            rt[i + n] = rt[i + n - 1];
            build(rt[i + n], a[i], 1, sz);
        }
        for(int i = 1; i <= m; i++) {
            if(O[i] == 'C') {
                bitInsert(L[i], a[L[i]], -1);
                a[L[i]] = lower_bound(b + 1, b + sz + 1, R[i]) - b;
                bitInsert(L[i], a[L[i]], 1);
            }
            else {
                int ans = solve(L[i] - 1, R[i], K[i]);
                printf("%d\n", b[ans]);
            }
        }
    }

    return 0;
}
/************************************************************/
```
#### 区间不同元素个数、第K大
```
/************************************************************/
/* 区间不同元素个数，第k大
 * 主席树变种
 */
#include<bits/stdc++.h>
#define x first
#define y second
#define ok cout << "ok" << endl;
#define okd(d) cout << "ok " << d << endl;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const long double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const ll LINF = 9223372036854775807;
const double Eps = 1e-7;
const int N = 2e5+9;

#define mid ((l + r) >> 1)

int ans, n, T, m, a[N], vis[N], l, r, kase;
int tot, rt[N], lson[N * 40], rson[N * 40], sum[N * 40];

void build(int &rt, int l, int r) {
    rt = ++tot;
    sum[rt] = 0;
    if(l == r)
        return;
    build(lson[rt], l, mid);
    build(rson[rt], mid + 1, r);
}

void decode(int &l, int &r) {
    (l += ans) %= n;
    (r += ans) %= n;
    l++, r++;
    if(l > r)
        swap(l, r);
}

void update(int &rt, int last, int l, int r, int pos, int x) {
    rt = ++tot;
    lson[rt] = lson[last];
    rson[rt] = rson[last];
    sum[rt] = sum[last] + x;
    if(l == r) {
        return;
    }
    if(pos <= mid)
        update(lson[rt], lson[last], l, mid, pos, x);
    else
        update(rson[rt], rson[last], mid + 1, r, pos, x);
}

int queryNum(int rt, int l, int r, int L, int R) {
    if(L <= l && r <= R) {
        return sum[rt];
    }
    int ans = 0;
    if(L <= mid)
        ans += queryNum(lson[rt], l, mid, L, R);
    if(mid < R)
        ans += queryNum(rson[rt], mid + 1, r, L, R);
    return ans;
}

int queryId(int rt, int l, int r, int k) {
    if(l == r)
        return l;
    if(sum[lson[rt]] >= k)
        return queryId(lson[rt], l, mid, k);
    return queryId(rson[rt], mid + 1, r, k - sum[lson[rt]]);
}

int main(void) {
    if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) {
            scanf("%d", a + i);
        }
        tot = 0;
        memset(vis, 0, sizeof vis);
        build(rt[n+1], 1, n);
        for(int i = n; i >= 1; i--) {
            int last = rt[i + 1];
            if(vis[a[i]])
                update(last, last, 1, n, vis[a[i]], -1);
            update(rt[i], last, 1, n, i, 1);
            vis[a[i]] = i;
        }
        ans = 0;
        // cout << queryNum(rt[1], 1, n, 1, 1) << endl;
        printf("Case #%d:", ++kase);
        while(m--) {
            scanf("%d%d", &l, &r);
            decode(l, r);
            // cout << l << " " << r << endl;
            int k = queryNum(rt[l], 1, n, l, r);
            k = (k + 1) >> 1;
            // cout << "k: " << k << endl;
            ans = queryId(rt[l], 1, n, k);
            printf(" %d", ans);
        }
        printf("\n");
    }

    return 0;
}
/************************************************************/
```

## 分治
### 数列分治
```
/************************************************************************
    > File Name: 数列分之.cpp
    > Author: zhangab
    > Mail: 2411035458@qq.com 
    > Created Time: 2018年10月20日 星期六 16时28分46秒
    > 逆序对
************************************************************************/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5+5;

int a[N], ans[N];

ll solve(int l, int r)
{
    //划分并解决子问题
    int mid = (l+r)>>1;
    if(l==r)    return 0;
    ll num = 0;//逆序对的个数

    num += solve(l, mid);
    num += solve(mid+1, r);

    //合并子问题
    
    //每一次的处理结果，升序保存在ans数组
    //将属于不同子序列的逆序对个数累加
    for(int i = l, j = mid+1, k = 0; i<=mid||j<=r; k ++)
    {
        if(i>mid)   ans[k] = a[j++];
        else if(j>r)    ans[k] = a[i++];
        else if(a[i]<=a[j]) ans[k] = a[i++];
        else
        {
            //出现逆序对
            ans[k] = a[j++];
            num += mid-i+1;//B序列中大于a[j]的个数
        }
    }
    for(int i = 0; i <= (r-l); i ++)
        a[l+i] = ans[i];
    return num;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", a+i);
    printf("%lld\n",solve(0, n-1));
    return 0;
}
```

### 平面分治
```
/************************************************************************
    > File Name: 平面内最近点对距离.cpp
    > Author: zhangab
    > Mail: 2411035458@163.com 
    > Created Time: 2018年10月20日 星期六 15时59分03秒
    > 平面内最近点对的距离
************************************************************************/

#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

const int N = 1e4+5;
const int inf = 0x3f3f3f3f;
struct node
{
    double x, y;
}a[N];

bool cmpx(node a, node b)
{
    return a.x<b.x;
}

double dist(node a, node b)
{
    return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}

double solve(int l, int r)
{
    if(l==r)    return inf;
    if(l+1==r)  return dist(a[l], a[r]);

    //划分解决
    int mid = (l+r)>>1;
    double st = a[mid].x;//划分依据
    double d = min(solve(l, mid), solve(mid+1, r));

    //在矩形空间内，左边的点跟右边的点一一匹配，合并
    for(int i = mid; i >= l && st-a[i].x < d; i --)
        for(int j = mid+1; j <= r && a[j].x-st < d; j ++)
            d = min(d, dist(a[i], a[j]));

    return d;
}

int main()
{
    int n;
    while(scanf("%d", &n), n)
    {
        for(int i = 0; i < n; i ++)
            scanf("%lf%lf", &a[i].x, &a[i].y);
        sort(a, a+n, cmpx);
        double ans = solve(0, n-1);
        if(ans<10000.0) printf("%.4f\n", ans);
        else puts("INFINITY");
    }
    return 0;
}
```

### 树上分治
```
/************************************************************************
    > File Name: 树上分治.cpp
    > Author: zhangab
    > Mail: 2411035458@qq.com 
    > Created Time: 2018年10月20日 星期六 16时24分39秒
    > 树上距离小于等于k的点对数
************************************************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#define pb push_back

using namespace std;
const int maxn = 10005, inf = 0x3f3f3f3f;

struct Edge
{
    int to, next, dist;
}edge[maxn<<1];
int head[maxn], cnt;

void addedge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].dist = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int n, k, ans;
int num[maxn];//num[i]表示以i为根的树 的节点数
int dp[maxn];//一维滚动。dp[i]将i删去后 当前树的最大联通块的大小

int Stack[maxn], top1;//栈
bool vis[maxn] ;//true表删除
int size;//当前树的节点数
int root;//根节点

void get_root(int u, int fa)//深搜遍历的同时找寻树的重心root
{
    dp[u] = 0;
    num[u] = 1;//初始化

    for(int i = head[u]; ~i; i  = edge[i].next)
    {
        int v = edge[i].to;
        if(v!=fa && !vis[v] )
        {//保证不回溯
            get_root(v, u);
            num[u] += num[v];//加上儿子的节点数就是根的节点数
            dp[u] = max(num[v], dp[u]);//最大联通块大小可能是子树大小
        }
    }
    //最大联通块还有可能是当前树删除子树u之后的树大小
    dp[u] = max(dp[u] , size - num[u]);
    //最后跟目前的重心对比
    if(dp[u]<dp[root])  root = u;
}

int dist[maxn];//到根节点的距离
inline bool cmp(int i, int j)
{
    return dist[i] < dist[j];
}

void Find_dist(int u, int fa , int d)
{//计算当前树的所有节点到根的距离，并将点入栈
    Stack[++top1] = u;
    dist[u] = d;
    for(int i = head[u]; ~i ; i = edge[i].next)
    {
        int v = edge[i].to;
        if(vis[v] || v==fa) continue ;
        Find_dist(v, u, d+edge[i].dist);
    }
}

int calc(int l, int r)//计算满足距离≤k的（i，j）个数
{
    int j = r, Ans = 0;//此时stack中l到r是按照dist升序排好的，ij一前一后往中间扫
    for(int i = l; i <= r; i ++)
    {
        while(dist[Stack[i]]+dist[Stack[j]]>k && j>i) j--;
        if(i==j)    break ;
        Ans += j-i;
        //Stack[i+1]~Stack[j]都是满足条件的
    }
    return Ans;
}

void solve(int u, int fa)
{
    dp[0] = maxn;
    size = num[u];
    root = 0;
    
    get_root(u, fa);//找到重心并将之转换为当前树的根

    top1 = 0;
    int top2 = 0;
    for(int i = head[root]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(vis[v])  continue;
        top2 = top1;
        Find_dist(v, root, edge[i].dist);
        //top2+1 到top1+1为子树v的所有节点
        sort(Stack+top2+1, Stack+top1+1, cmp);
        ans -= calc(top2+1, top1);//减去在同一棵子树且经过根节点（即非最短距离）的答案数
    }
    
    Stack[++top1] = root;
    dist[root ] = 0;
    sort(Stack+1, Stack+top1+1, cmp);
    ans += calc(1, top1);

    vis[root] = 1;

    for(int i = head[root]; ~i; i = edge[i].next)
        if(!vis[edge[i].to])
            solve(edge[i].to, root);//分治解决
}

void init()
{
    memset(head, -1, sizeof head);
    memset(vis, 0, sizeof vis);
    ans = 0;
    cnt = 0;
}

int main()
{
    while(scanf("%d %d", &n, &k), n&&k)
    {
        init();
        for(int i = 1; i < n; i ++)
        {
            int u, v, d;
            scanf("%d %d %d", &u, &v, &d);
            addedge(u, v, d);
            addedge(v, u, d);
        }
        num[1] = n;
        solve(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
```

## DP
### 背包
```
/************************************************************/
/* 01背包, 完全背包, 多重背包(Tested 1 times)
 * 实际应用直接调用multiPack即可, 其中w表示当前物品的代价, v表示价值, number表示数量
 * V表示背包最大容量
 */
void zeroPack(int *dp, int w, int v) {
    for(int i = V; i >= w; i--)
        dp[i] = max(dp[i], dp[i-w] + v);
}

void completePack(int *dp, int w, int v) {
    for(int i = w; i <= V; i++)
        dp[i] = max(dp[i], dp[i-w] + v);
}

void multiPack(int *dp, int w, int v, int num) {
    if(num*w >= V) {
        completePack(dp, w, v);
        return;
    }
    int k = 1;
    while(k < num) {
        zeroPack(dp, w*k, v*k);
        num -= k;
        k *= 2;
    }
    zeroPack(dp, w*num, v*num);
}
/************************************************************/
```

### 最长上升子序列
```
/************************************************************/
/* O(nlogn) 求解上升子序列问题(Tested 0 times)
 */
int n, a[N], s[N], dp[N];
// 下标从1开始
// dp[i] 表示以a[i]结尾的LIS长度
// s[i] 表示LIS序列的第i个元素

void init() {
    for(int i = 1; i <= n; i++) s[i] = INF; //上升为INF,下降为-INF
    memset(dp, 0, sizeof dp);
}

int BinSearch(int x, int y, ll v) {
    while(x <= y) {
        int mid = x + (y - x) / 2;
        if(s[mid] < v) x = mid + 1;     //严格为<或> 非严格为<=或>=
        else y = mid - 1;
    }
    return x;
}

int LIS() {
    init();
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int pos = BinSearch(1, i, a[i]);
        dp[i] = pos;
        s[pos] = min(s[pos], a[i]);    //上升为min,下降为max
        ans = max(ans, dp[i]);
    }
    return ans;
}
/************************************************************/
```

### 数位DP
```
/************************************************************/
/* 数位DP
 */
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
using namespace std;

int n, dp[9][109], a[9], k;

int dfs(int pos, int sum, int limit){
    if(pos==-1) return sum==0;
    if(!limit && dp[pos][sum]!=-1) return dp[pos][sum];
    int ans=0, up=limit?a[pos]:9;
    for(int i=0; i<=up; i++){
        int t1=(sum+i)%k;
        ans+=dfs(pos-1, t1, limit&&(i==a[pos]));
    }
    if(!limit)
        dp[pos][sum%k]=ans;
    return ans;
}

int solve(int n){
    int cnt=0;
    while(n){
        a[cnt++]=n%10;
        n/=10;
    }
    return dfs(cnt-1, 0, 1);
}


int main() {
    // freopen("in", "r", stdin); freopen("out", "w", stdout);
    int T; scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n,&k);
        memset(dp, -1, sizeof dp);
        printf("%d\n", solve(n)-1);
    }
    return 0;
}
/************************************************************/
```

## 杂项
### 正则表达式
```
// regex_match example
#include <iostream>
#include <string>
#include <regex>

int main ()
{
    if (std::regex_match ("subject1233", std::regex("(sub)(.?)(ject)(123)([3-3])") ))
        std::cout << "string literal matched\n";

    return 0;
}
```

### 康拓展开
```
/*************************************************************/
/* 康拓展开：用于压缩状态，可节省内存空间(Tested 1 times)
 */
static const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};   // 阶乘
int cantor(int *a, int n) {
    int x = 0;
    for (int i = 0; i < n; ++i) {
        int smaller = 0;  // 在当前位之后小于其的个数
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[i])
                smaller++;
        }
        x += FAC[n - i - 1] * smaller; // 康托展开累加
    }
    return x;  // 康托展开值
}


//康托展开逆运算
void decantor(int x, int n)
{
    vector<int> v;  // 存放当前可选数
    vector<int> a;  // 所求排列组合
    for(int i=1;i<=n;i++)
        v.push_back(i);
    for(int i=m;i>=1;i--)
    {
        int r = x % FAC[i-1];
        int t = x / FAC[i-1];
        x = r;
        sort(v.begin(),v.end());// 从小到大排序
        a.push_back(v[t]);      // 剩余数里第t+1个数为当前位
        v.erase(v.begin()+t);   // 移除选做当前位的数
    }
}
/*************************************************************/
```

### 快速读入
```
/************************************************************/
/* 快速读入，比getchar()快很多(Tested 2 times)
 * 最开始的时候init()一次，然后再调用readint()
 */
const int MAXSIZE = 50000007;
char buf[MAXSIZE];
ll bufpos;

void init(){
    buf[fread(buf,1,MAXSIZE,stdin)]='\0';
    bufpos=0;
}

inline int readint(){
    bool isneg;
    int val=0;
    for(;!isdigit(buf[bufpos]) && buf[bufpos]!='-';bufpos++);
    bufpos+=(isneg=buf[bufpos]=='-');
    for(;isdigit(buf[bufpos]);bufpos++)
        val=val*10+buf[bufpos]-'0';
    return isneg?-val:val;
}
/************************************************************/
```


## 图论
### bellman
```
/************************************************************/
/* bellman算法：解决有负边的最短路问题
 */
const int MAX_E=1e5+9;
const int MAX_V=1e5+9;
struct edge { int from, to, cost; };

edge es[MAX_E];
int d[MAX_V], V, E;
//d[i]表示到达顶点i的最短距离, V表示图的实际顶点数, E表示图的实际边数, 下标从0开始

void bellman(int s){
    for(int i=0; i<V; i++) d[i]=INF;
    d[s]=0;
    while(true){
        bool update=false;
        for(int i=0; i<E; i++) {
            edge e = es[i];
            if (d[e.from]!=INF && d[e.to] > d[e.from] + e.cost) {
                d[e.to]=d[e.from]+e.cost;
                update=true;
            }
        }
        if(!update) break;
    }
}

bool find_nagative_loop() {
    memset(d, 0, sizeof d);
    for(int i=0; i<V; i++){
        for(int j=0; j<E; j++){
            edge e=es[j];
            if(d[e.to]>d[e.from]+e.cost){
                d[e.to]=d[e.from]+e.cost;
                if(i==V-1) return true;
            }
        }
    }
    return false;
}
/************************************************************/
```

### dijkstra算法
```
/************************************************************/
/* dijkstra算法：解决最短路问题(Tested 0 times)
 * 前向心存图
 */
const int MAX_V=1e5+9;
int d[MAX_V];

void dijkstra(int s) {
    priority_queue<pii, vector<pii>, greater<pii> > que;
    memset(d, INF, sizeof d);
    d[s] = 0;
    que.push(pii(0, s));
    while(!que.empty()) {
        pii p = que.top(); que.pop();
        int u = p.second;
        if(d[u] < p.first) continue;
        for(int i = head[u]; ~i; i = edge[i].next) {
            Edge e = edge[i];
            if(d[e.to] > d[u] + e.cost) {
                d[e.to] = d[u] + e.cost;
                que.push(pii(d[e.to], e.to));
            }
        }
    }
}
/************************************************************/
```
### 有向最小生成树
```
/************************************************************/
/* 有向最小生成树
 */
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

const int VN = 105;
const int INF = 0x7fffffff;

template<typename Type>
class Directed_MST{
public:
    void init(int _n){
        n=_n;
        ans = 0;
        memset(vis, 0, sizeof(vis));
        memset(inc, 0, sizeof(inc));
        for(int i=0; i<=n; ++i){
            w[i][i] = INF;
            for(int j=i+1; j<=n; ++j)
                w[i][j]=w[j][i]=INF;
        }
    }
    void insert(int u, int v, Type _w){
        if(w[u][v]>_w) w[u][v] = _w;
    }
    Type directed_mst(int u){
        //==  步骤1： 判断能否形成最小树形图，直接dfs遍历
        dfs(u);
        for(int i=1; i<=n; ++i)
            if(!vis[i]) { return -1; }

        //== 如果可以形成最小树形图，继续
        memset(vis, 0, sizeof(vis));
        while(true){
            //== 1. 找最小前驱边
            for(int i=1; i<=n; ++i)if(i!=u&&!inc[i]){          //不是root而且该点没有被收缩
                w[i][i]=INF, pre[i] = i;
                for(int j=1; j<=n; ++j)if(!inc[j] && w[j][i]<w[pre[i]][i]){
                    pre[i] = j;
                }
            }
            //== 2.判断是否有环
            int i;
            for(i=1; i<=n; ++i){
                if(i!=u&&!inc[i]){
                    int j=i, cnt=0;
                    while(j!=u && pre[j]!=i && cnt<=n)
                        j=pre[j], ++cnt;     //O(n);
                    if(j==u || cnt>n) continue; //没找到
                    break;
                }
            }

            //== 没有找到环,得到答案
            if(i>n){
                for(int i=1; i<=n; ++i)if(i!=u && !inc[i]) ans+=w[pre[i]][i];
                return ans;
            }
            //==  有环，进行收缩
            int j=i;
            memset(vis, 0, sizeof(vis));
            do{
                ans += w[pre[j]][j], j=pre[j], vis[j]=inc[j]=true;
            }while(j!=i);
            inc[i] = false; // 环缩成了点i，点i仍然存在

            //==  收缩
            for(int k=1; k<=n; ++k)if(vis[k]){ // 在环中点点
                for(int j=1; j<=n; ++j)if(!vis[j]){  // 不在环中的点
                    if(w[i][j] > w[k][j]) w[i][j] = w[k][j];
                    if(w[j][k]<INF && w[j][k]-w[pre[k]][k] < w[j][i])
                        w[j][i] = w[j][k] - w[pre[k]][k];
                }
            }
        }
        return ans;
    }

private:
    // 从根结点遍历一遍，判断是否存在最小树形图
    void dfs(int u){
        vis[u] = true;
        for(int i=1; i<=n; ++i)if(!vis[i]&&w[u][i]<INF){
            dfs(i);
        }
    }

private:
    Type ans;         // 所求答案
    int n;            // 结点个数
    int pre[VN];      // 权值最小的前驱边
    bool vis[VN];     // 是在环中还是在环外
    bool inc[VN];     // 该点是否被删除了（收缩）
    Type w[VN][VN];   // 图
};


Directed_MST<double>G;
double x[VN],y[VN];
inline double getDist(double x1,double y1,double x2,double y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

int main(){
    int n,m;
    while(~scanf("%d%d",&n,&m)){
        G.init(n);
        for(int i=1; i<=n; ++i)
            scanf("%lf%lf",&x[i],&y[i]);
        for(int i=0; i<m; ++i){
            int a,b;
            scanf("%d%d",&a,&b);
            if(a==b)continue;
            G.insert(a,b,getDist(x[a],y[a],x[b],y[b]));
        }
        double ans = G.directed_mst(1);
        if(ans < 0) puts("poor snoopy");
        else printf("%.2f\n", ans);
    }
    return 0;
}
/************************************************************/
```

### 最小生成树
#### prim算法
```
/*  * Prim求MST  * 耗费矩阵cost[][]，标号从0开始，0~n-1  * 返回最小生成树的权值，返回-1表示原图不连通  */
const int INF=0x3f3f3f3f;
const int MAXN=110;
bool vis[MAXN];
int lowc[MAXN];
int Prim(int cost[][MAXN],int n)//点是0~n-1
{
    int ans=0;
    memset(vis,false,sizeof(vis));
    vis[0]=true;
    for(int i=1; i<n; i++)
        lowc[i]=cost[0][i];
    for(int i=1; i<n; i++)
    {
        int minc=INF;
        int p=-1;
        for(int j=0; j<n; j++)
            if(!vis[j]&&minc>lowc[j])
            {
                minc=lowc[j];
                p=j;
            }
        if(minc==INF)
            return -1;//原图不连通
        ans+=minc;
        vis[p]=true;
        for(int j=0; j<n; j++)
            if(!vis[j]&&lowc[j]>cost[p][j])
                lowc[j]=cost[p][j];
    }
    return ans;
}
```

#### Kruskal 算法
```
/*  * Kruskal算法求MST  */
const int MAXN=110;//最大点数
const int MAXM=10000;//最大边数
int F[MAXN];//并查集使用
struct Edge
{
    int u,v,w;
} edge[MAXM]; //存储边的信息，包括起点/终点/权值
int tol;//边数，加边前赋值为0
void addedge(int u,int v,int w)
{
    edge[tol].u=u;
    edge[tol].v=v;
    edge[tol++].w=w;
}
bool cmp(Edge a,Edge b)  //排序函数，讲边按照权值从小到大排序
{
    return a.w<b.w;

}
int find(int x)
{
    if(F[x]==-1)
        return x;
    else
        return F[x]=find(F[x]);
}
int Kruskal(int n)//传入点数，返回最小生成树的权值，如果不连通返回-1
{
    memset(F,-1,sizeof(F));
    sort(edge,edge+tol,cmp);
    int cnt=0;//计算加入的边数
    int ans=0;
    for(int i=0; i<tol; i++)
    {
        int u=edge[i].u;
        int v=edge[i].v;
        int w=edge[i].w;
        int t1=find(u);
        int t2=find(v);
        if(t1!=t2)
        {
            ans+=w;
            F[t1]=t2;
            cnt++;
        }
        if(cnt==n-1)
            break;
    }
    if(cnt<n-1)
        return -1;//不连通
    else
        return ans;
}
```

### tarjan 缩点
```
/************************************************************/
/* Tarjan算法：缩点(Tested 0 times)
 */
void tarjan(int i)
{
    int j;
    DFN[i]=LOW[i]=++Dindex;
    instack[i]=true;
    Stap[++Stop]=i;
    for (edge *e=V[i];e;e=e->next)
    {
        j=e->t;
        if (!DFN[j])
        {
            tarjan(j);
            if (LOW[j]<LOW[i])
                LOW[i]=LOW[j];
        }
        else if (instack[j] && DFN[j]<LOW[i])
            LOW[i]=DFN[j];
    }
    if (DFN[i]==LOW[i])
    {
        Bcnt++;
        do
        {
            j=Stap[Stop--];
            instack[j]=false;
            Belong[j]=Bcnt;
        }
        while (j!=i);
    }
}
void solve()
{
    int i;
    Stop=Bcnt=Dindex=0;
    memset(DFN,0,sizeof(DFN));
    for (i=1;i<=N;i++)
        if (!DFN[i])
            tarjan(i);
}
/************************************************************/
```

### 拓扑排序
```
/************************************************************/
/* 拓扑排序
 * cp from zyb.
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<TYPE>g[MAX_N];                  //TYPE可以根据需要进行修改
int degree[MAX_N];

int topo(int n)
{
    queue<TYPE>q;
    memset(degree,0,sizeof(degree));   //注意初始化
    for(int i=0;i<n;i++)               //注意数据的给法是从0开始还是1开始
    {
        for(int j=0;j<g[i].size();j++)
        {
            degree[g[i][j]]++;
        }
    }
    for(int i=0;i<n;i++)               //注意数据的给法是从0开始还是1开始
    {
        if(degree[i]==0)
        {
            q.push(i);
        }
    }
    int tot=0;
    while(q.size())
    {
        int qq=q.front();                  //根据类型修改qq的类型
        q.pop();
        tot++;
        for(int i=0;i<g[qq].size();i++)
        {
            degree[g[qq][i]]--;
            if(degree[g[qq][i]]==0)
                q.push(g[qq][i]);
        }
    }
    if(tot==n)                           //判断自环
        return 1;
    else
        return 0;
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(g,0,sizeof(g));
        int a,b;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&a,&b);
            g[a].push_back(b);                 //根据TYPE的类型和出度入度的不同，这里会有所不同
        }
        if(topo(n))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
/************************************************************/
```

### 欧拉回路
```
/************************************************************/
int head[Max_N]= {-1};
struct Edge
{
    int to,next,w;
} edge[Max_M];

void dfs(int x)
{
    t.push(x);
    for(int i=1; i<=n; i++)
    {
        if(path[x][i])         //找到连边并删除，从该点继续dfs
        {
            path[x][i]=path[i][x]=0;//删除此边
            dfs(i);
            break;
        }
    }
}
void  Fleury(int x)
{
    t.push(x);
    while(!t.empty())
    {
        int b=0;
        for(int i=1; i<=n; i++)
        {
            if(path[t.top()][i])
            {
                b=1;
                break;
            }
        }
        if(!b)                       //如果改点没有连边
        {
            printf("%d ",t.top());  //输出该点     输出路径
            t.pop();
        }
        else                //否则 对这点进行深搜
        {
            int y=t.top();
            t.pop();
            dfs(y);
        }
    }
    printf("\n");
}

/*path*/
int ans[max_m];
int ansi=0;  //for counting
bool visit[2*max_m];    //"2*" means undirected graph
void dfs(int now)
{
    for(int k=edge[now][i]; k!=0; k=edge[k].next)
    {
        if(!vis[k])
        {
            vis[k]=true;         //sign the edge
            vis[k^1]=true;       //sign the reverse edge
            dfs(edge[k].to);
            ans[cnt++]=k;
        }
    }
}
int main()
{
    memset(s,0,sizeof s);       //若从0开始，memset为-1
    for(int i=1; i<=m; i++)     //m为边数
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        edge[i].to=b;
        edge[i].w=c;
        edge[i].next=head[a];
        head[a]=i;
    }
    for(int i=1; i<=n; i++)    //n为顶点数
    {
        for(int k=head[i]; k!=0; k=edge[k].next)
        {
            cout<<i<<" "<<edge[k].to<<endl;
        }
    }
    return 0;
}
/************************************************************/
```

### 补图连通性
```
/*
给定一个图，求这个图的补图的连通块个数以及每个联通块的大小

（1）构造一条所有节点的链表： 1->2->3->…….（此处可以用set代替——将1-n的数字放入set中，会增加一个log的复杂度，而且操作不如链表灵活）
（2）从链表中取出一个点，将这个点相邻的所有点打上标记，那么，没有被打上标记的点就跟这个点成为一个联通块
（3）遍历链表找出没有被打上标记的点，从链表中将其删除并放入队列中，直到队列为空，于是找到了一个联通块；回到（2），直到链表为空
（4）算法时间复杂度O（n+m）
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000010;//此处根据题目做了修改
const int maxm = 2000010;
int n, m, edgecnt, head[maxn];
struct edge{int v, nxt; } E[maxm*2];
struct link{int pre, nxt; }L[maxn];
void del(int x){
    L[L[x].pre].nxt = L[x].nxt;
    L[L[x].nxt].pre = L[x].pre;
}
void init(){
    memset(head, -1, sizeof(head));
    edgecnt = 0;
}
void addedge(int u, int v){
    E[edgecnt].v = v, E[edgecnt].nxt = head[u], head[u] = edgecnt++;
}
bool vis1[maxn], vis2[maxn]; //vis1标记相邻点，vis2标记在队列的存在状态
int scc[maxn], scccnt;
void bfs(){
    queue <int> q;
    memset(vis1, 0, sizeof(vis1));
    memset(vis2, 0, sizeof(vis2));
    while(L[0].nxt){//还存在节点
        int now = L[0].nxt, curscc = 1;
        del(now);
        q.push(now);
        vis2[now] = 1;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int i = head[u]; ~i; i = E[i].nxt) vis1[E[i].v] = 1;
            for(int i = L[0].nxt; i; i = L[i].nxt){
                if(!vis1[i] && !vis2[i]){
                    vis2[i] = 1;
                    q.push(i);
                    curscc++;
                    del(i);
                }
            }
            for(int i = head[u]; ~i; i = E[i].nxt) vis1[E[i].v] = 0; //一定取消相邻节点的标记
        }
        scc[++scccnt] = curscc;
    }
}
int main(){
    init();
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    for(int i = 1; i <= n; i++){
        L[i-1].nxt = i; L[i].pre = i - 1;
    } L[n].nxt = 0;
    bfs();
    sort(scc + 1, scc + scccnt + 1);
    printf("%d\n", scccnt);
    for(int i = 1; i < scccnt; i++) printf("%d ", scc[i]); printf("%d", scc[scccnt]);
    return 0;
}
```

## 数学
### 卡特兰数
卡特兰数是组合数学中一个常在各种计数问题中出现的数列。
#### 公式
1. $ C_n = \frac{1}{n+1}{2n \choose n} = \frac{(2n)!}{(n+1)!n!} $
前20个卡特兰数：1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190
2. 递推公式1：$ C_0 = 1 \quad \mbox{and} \quad C_{n+1}=\sum_{i=0}^{n}C_i\,C_{n-i}\quad\mbox{for }n\ge 0 $
3. 递推公式2：$ C_0 = 1 \quad \mbox{and} \quad C_{n+1}=C_n\frac{2(2n+1)}{n+2} $
4. 近似公式：$ C_n \sim \frac{4^n}{n^{3/2}\sqrt{\pi}} $
#### 应用
1. Cn表示长度2n的dyck word的个数。Dyck word是一个有n个X和n个Y组成的字串，且所有的前缀字串皆满足X的个数大于等于Y的个数。以下为长度为6的dyck words：
XXXYYY XYXXYY XYXYXY XXYYXY XXYXYY

### FWT（异或）
```
/************************************************************/
/* FWT变换：nlogn解决位运算卷积问题(Tested 1 times)
 * copy from tmk
 */
void FWT(int a[],int n) {
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++) {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
                //xor:a[i+j]=x+y,a[i+j+d]=(x-y+mod)%mod;
                //and:a[i+j]=x+y;
                //or:a[i+j+d]=x+y;
            }
}
void UFWT(int a[],int n) {
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++) {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=1LL*(x+y)*rev2%mod,a[i+j+d]=(1LL*(x-y)*rev2%mod+mod)%mod;
                //rev2表示2在模mod下的逆元
                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                //and:a[i+j]=x-y;
                //or:a[i+j+d]=y-x;
            }
}
void solve(int a[],int b[],int n) { 
    FWT(a,n);
    FWT(b,n);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%mod;
    UFWT(a,n);
}
/************************************************************/
```

### 高斯消元
```
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
```

```
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
```

### Lucas + 中国剩余定理
```
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
```
### 矩阵快速幂
```
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
```

### 素数判别
```
const int MAXN = 65;
long long n, x[MAXN];
//素数判别
long long multi(long long a, long long b, long long p) {
    long long ans = 0;
    while(b) {
        if(b&1LL) ans = (ans+a)%p;
        a = (a+a)%p;
        b >>= 1;
    }
    return ans;
}

long long qpow(long long a, long long b, long long p) {
    long long ans = 1;
    while(b) {
        if(b&1LL) ans = multi(ans, a, p);
        a = multi(a, a, p);
        b >>= 1;
    }
    return ans;
}

bool Miller_Rabin(long long n) {
    if(n == 2) return true;
    int s = 20, i, t = 0;
    long long u = n-1;
    while(!(u & 1)) {
        t++;
        u >>= 1;
    }
    while(s--) {
        long long a = rand()%(n-2)+2;
        x[0] = qpow(a, u, n);
        for(i = 1; i <= t; i++) {
            x[i] = multi(x[i-1], x[i-1], n);
            if(x[i] == 1 && x[i-1] != 1 && x[i-1] != n-1) return false;
        }
        if(x[t] != 1) return false;
    }
    return true;
}
```

### 线性筛
```
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
```

### 莫比乌斯前缀和
```
/*
莫比乌斯前缀和，HDU4746
i~[1,n], j~[1,m], facp[(i,j)] <= p, 求<i,j>对数
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
const int M = 20;

int prime[N], cnt, facp[N], mo[N], sum[M][N];
// 素数 ，素数个数，素因子个数，莫比乌斯函数，莫比乌斯前缀和
bool vis[N];

void init() {
    mo[1] = 1;
    facp[1] = 0;
    for (long long i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[cnt ++] = i;
            mo[i] = -1;
            facp[i] = 1;
        }
        for (long long j = 0, k; j < cnt && (k = i * prime[j]) < N; j++) {
            vis[k] = 1;
            facp[k] = facp[i] + 1;
            if (i % prime[j]) {
                mo[k] = -mo[i];
            } else {
                mo[k] = 0;
                break;
            }
        }
    }
}

void sum_mo() {
    // 对于每一个数字，先把他的因子累加
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            sum[facp[i]][j] += mo[j / i]; // 倍数型
            //                 mo[i]       约数型
        }
    }
    // sum对于facp从小到大累加的
    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {
            sum[i][j] += sum[i - 1][j];
        }
    }
    // sum[][j] 前缀和
    for (int i = 0; i < M; i++) {
        for (int j = 1; j < N; j++) {
            sum[i][j] += sum[i][j - 1];
        }
    }
}

int main() {
    init(); sum_mo();
    int T;  scanf("%d", &T);
    while (T--) {
        int n, m, p;
        scanf ("%d%d%d", &n, &m, &p);
        p = min(p, 19);
        long long ans = 0;
        for (int i = 1; i <= min(n, m);) {
            long long a = n / i, b = m / i;
            int now = min(n / a, m / b);
            ans += a * b * (sum[p][now] - sum[p][i - 1]); // [i, now]中，n/a, m/b 不变
            i = now + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
```

### 求逆元
```
//O（n）求p（素数）以内的所有逆元
void getinv()
{
  inv[1]=1;
  for(int i=2;i<=n;i++)
    inv[i]=1ll*(p-p/i)*inv[p%i]%p;
}
```
```
/************************************************************/
/* inv_Fermat(a, p): 费马小定理求a关于p的逆元(Untested)
 * inv_extgcd(a, p: 拓展欧几里得求a关于p的逆元(Untested)
 * getFac(): 线性求MAXN个逆元、阶乘以及阶乘的逆元(Untested)
 */
ll pow_mod(ll a, ll b, ll p) {  //辅助函数
    ll ret = 1;
    while(b) {
        if(b & 1) ret = (ret * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ret;
}

void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d){   //辅助函数
    if (!b) {d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, y, x, d);
        y -= x * (a / b);
    }
}

ll inv_Fermat(ll a, ll p) {         //费马小定理求a关于p的逆元 
    return pow_mod(a, p-2, p);
}

ll inv_extgcd(ll a, ll p) {         //欧几里得求a关于p的逆元, 如果不存在，返回-1 
    ll d, x, y;
    ex_gcd(a, p, x, y, d);
    return d == 1 ? (x % p + p) % p : -1;
}

const int MAXN = 1e5;
ll fac[MAXN + 9], ifac[MAXN + 9], inv[MAXN + 9];

void getFac() {     //线性求MAXN个逆元、阶乘以及阶乘的逆元
    fac[0] = 1;
    for(int i = 1; i <= MAXN; i++)
        fac[i] = fact[i-1] * i % mod;
    inv[1] = 1;
    for (int i = 2; i <= MAXN; i++)
        inv[i] = (mod - mod / i) * 1LL * inv[mod % i] % mod;
    ifac[0] = 1;
    for(int i = 1; i <= MAXN; i++)
        ifac[i] = ifac[i-1] * inv[i] % mod;
}
/************************************************************/
```

## 莫队
### 普通莫队
```
/************************************************************/
/* 普通莫队：解决一类区间问题
 * 时间复杂度O(n*sqrt(n))
 */

#include<bits/stdc++.h>
#define x first
#define y second
#define ok cout << "ok" << endl;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const long double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const ll LINF = 9223372036854775807;
const double Eps = 1e-7;
const int N = 1e6+9;

struct Node {
    int l, r, block, id;
    bool operator < (const Node &rhs) const {
        if(block == rhs.block) return r < rhs.r;
        return block < rhs.block;
    }
}q[N];

int n, m, a[N], len, cnt[N], an[N];

int main(void) {
    if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
    while(~scanf("%d", &n)) {
        len = sqrt(n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", a + i);
        }
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].block = q[i].l / len;
            q[i].id = i;
        }
        sort(q, q + m);
        int l = 1, r = 0, ans = 0;
        memset(cnt, 0, sizeof cnt);
        for(int i = 0; i < m; i++) {
            Node t = q[i];
            while(r < t.r) {
                ans += (++cnt[a[++r]] == 1);
            }
            while(l > t.l) {
                ans += (++cnt[a[--l]] == 1);
            }
            while(r > t.r) {
                ans -= (--cnt[a[r--]] == 0);
            }
            while(l < t.l) {
                ans -= (--cnt[a[l++]] == 0);
            }
            an[t.id] = ans;
        }
        for(int i = 0; i < m; i++) {
            printf("%d%c", an[i], " \n"[i == m - 1]);
        }
    }

    return 0;
}
/************************************************************/
```

### 带修改莫队
```
/************************************************************/
/* 待修改莫队：解决一类区间问题
 * 时间复杂度O(n^(5/3))
 */

#include<bits/stdc++.h>
#define x first
#define y second
#define ok cout << "ok" << endl;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const long double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const ll LINF = 9223372036854775807;
const double Eps = 1e-7;
const int N = 1e6+9;

char c;
int len, n, m, a[N], cnt[N], l, r, ans, an[N], timer, tot, last[N], flag[N];

inline void sub(int pos) {
    ans -= (--cnt[a[pos]] == 0);
    flag[pos] = 0;
}

inline void add(int pos) {
    ans += (++cnt[a[pos]] == 1);
    flag[pos] = 1;
}

inline void modify(int pos, int val) {
    if(!flag[pos])
        a[pos] = val;
    else {
        sub(pos);
        a[pos] = val;
        add(pos);
    }
}

struct Node {
    int l, r, id, lblock, rblock, timer;
    Node () {}
    Node (int l, int r, int id, int timer): l(l), r(r), id(id), timer(timer) {
        lblock = l / len;
        rblock = r / len;
    }
    bool operator < (const Node &rhs) const {
        if(lblock != rhs.lblock) return lblock < rhs.lblock;
        else if(rblock != rhs.rblock) return rblock < rhs.rblock;
        return timer < rhs.timer;
    }
}q[N];

struct Node1 {
    int pos, val, last;
    Node1 () {}
    Node1 (int pos, int val, int last): pos(pos), val(val), last(last) {}
}chg[N];

int main(void) {
    if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
    while(~scanf("%d%d", &n, &m)) {
        len = pow(n, 2.0 / 3);
        timer = tot = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            last[i] = a[i];
        }
        for(int i = 0; i < m; i++) {
            scanf(" %c%d%d", &c, &l, &r);
            if(c == 'Q') {
                q[tot] = Node{l, r, tot, timer};
                tot++;
            }
            else {
                chg[++timer] = Node1{l, r, last[l]};
                last[l] = r;
            }
        }
        sort(q, q + tot);
        l = 1, r = ans = timer = 0;
        memset(cnt, 0, sizeof cnt);
        for(int i = 0; i < tot; i++) {
            Node t = q[i];
            while(timer < t.timer) {
                timer++;
                modify(chg[timer].pos, chg[timer].val);
            }
            while(timer > t.timer) {
                modify(chg[timer].pos, chg[timer].last);
                timer--;
            }
            while(r < t.r) add(++r);
            while(l > t.l) add(--l);
            while(r > t.r) sub(r--);
            while(l < t.l) sub(l++);
            an[t.id] = ans;
        }
        for(int i = 0; i < tot; i++) {
            printf("%d\n", an[i]);
        }
    }

    return 0;
}
/************************************************************/
```

## pb_ds

### hash（可取代map）

cc_hash_table 是拉链法
gp_hash_table 是查探法 
除了当数组用外，还支持find和operator[], 与map用法基本上一致，但是无法使用pair，struct
```C++
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
__gnu_pbds::cc_hash_table<int,bool> h1;
__gnu_pbds::gp_hash_table<int,bool> h2; // 比CC稍快
```

###priority——queue优先队列
1. push()  //会返回一个迭代器
2. top()  //同 stl 
3. size()  //同 stl 
4. empty() //同 stl 
5. clear()  //同 stl 
6. pop()  //同 stl 
7. join(priority_queue &other)  //合并两个堆,other会被清空
8. modify(point_iterator it,const key)  //修改一个节点的值

```C++
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds::priority_queue<int>q;//因为放置和std重复，故需要带上命名空间
__gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;//最快
__gnu_pbds::priority_queue<int,greater<int>,binary_heap_tag> pq;
__gnu_pbds::priority_queue<int,greater<int>,binomial_heap_tag> pq;
__gnu_pbds::priority_queue<int,greater<int>,rc_binomial_heap_tag> pq;
__gnu_pbds::priority_queue<int,greater<int>,thin_heap_tag> pq;//快
__gnu_pbds::priority_queue<int,greater<int> > pq;//快
```

###rb_tree_tag红黑树
1. 插入 ：insert(); 
2. 删除 ：erase();
3. 大小 ：size();
3. 查找k的排名 ：order_of_key(k); // 从0开始数
4. 查找排名为k的元素 ：t.find_by_order()；//实际是查询k+1大 返回的是迭代器 需要 *t.find_by_order();
5. lower_bound(x) // >= x 返回迭代器
6. upper_bound(x) // > x  返回迭代器
7. 合并 ： join(b) // b加入a，前提a，b的key不想交
8. 分类 ： split(v,b) // >v 的元素扔到b
9. 注意他没有multiset一样的功能，如果要存重复元素可以建结构体，添加一个无关变量用于区别
```C++
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t, p;

```

###rope平衡树

1. 运算符：rope支持operator += -= + - < ==
2. 输入输出：可以用<<运算符由输入输出流读入或输出。
3. 长度/大小：调用length()，size()都可以哦
4. 插入/添加等：
push_back(x); //在末尾添加x
insert(pos,x); //在pos插入x，自然支持整个char数组的一次插入
erase(pos,x); //从pos开始删除x个
copy(pos,len,x); //从pos开始到pos+len为止用x代替
replace(pos,x); //从pos开始换成x[pos,pos+x)
substr(pos,x); //提取pos开始x个
at(x)/[x]; //访问第x个元素 t[i], t.at(i)
  ​      
```C++
#include <ext/rope>
using namespace __gnu_cxx;//第一条下划线其实是两条
rope<int> r;
```

## 匹配问题

### 匹配问题总结
二分图匹配（匈牙利算法）
1. 一个二分图中的最大匹配数等于这个图中的最小点覆盖数
König定理是一个二分图中很重要的定理，它的意思是，一个二分图中的最大匹配数等于这个图中的最小点覆盖数。如果你还不知道什么是最小点覆盖，我也在这里说一下：假如选了一个点就相当于覆盖了以它为端点的所有边，你需要选择最少的点来覆盖所有的边。
2. 最小路径覆盖=最小路径覆盖＝｜G｜－最大匹配数
 在一个N*N的有向图中，路径覆盖就是在图中找一些路经，使之覆盖了图中的所有顶点，且任何一个顶点有且只有一条路径与之关联；（如果把这些路径中的每条路径从它的起始点走到它的终点，那么恰好可以经过图中的每个顶点一次且仅一次）；如果不考虑图中存在回路，那么每每条路径就是一个弱连通子集．
由上面可以得出：
    1.一个单独的顶点是一条路径；
    2.如果存在一路径p1,p2,......pk，其中p1 为起点，pk为终点，那么在覆盖图中，顶点p1,p2,......pk不再与其它的顶点之间存在有向边．
    最小路径覆盖就是找出最小的路径条数，使之成为G的一个路径覆盖．
     路径覆盖与二分图匹配的关系：最小路径覆盖＝｜G｜－最大匹配数；
3. 二分图最大独立集=顶点数-二分图最大匹配
独立集：图中任意两个顶点都不相连的顶点集合。

### 匈牙利算法
```
/******************************************************************/
/* 匈牙利算法：解决二分匹配问题
 * 先确定点数V，然后使用init()进行初始化，再调用hungary()，返回最大匹配对数
 */

const int MAX_V = 1e5;  //点数的最大值

int V;                  //点数，从0开始编号
vector<int> G[MAX_V];   //使用vector存邻接边
int match[MAX_V];
bool used[MAX_V];

void init() {
    for(int i = 0; i < V; i++)
        G[i].clear();
}

void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v) {
    used[v]=true;
    for(int i = 0; i < G[v].size(); i++) {
        int u = G[v][i], w = match[u];
        if(w < 0 || (!used[w] && dfs(w))) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int hungary() {
    int res=0;
    memset(match, -1, sizeof match);
    for(int v = 0; v < V; v++) {
        if(match[v] < 0) {
            memset(used, 0, sizeof used);
            if(dfs(v))
                res++;
        }
    }
    return res;
}

/******************************************************************/
```

### 二维匈牙利
```
/************************************************************/
/* 匈牙利算法：解决多重匹配问题
 * 先确定左边点数uN和右边点数vN，然后确定右边各点的最大匹配数num[]
 * 接着调用hungary()即可，返回最大匹配数
 */
const int MAXN = 1009;
const int MAXM = 509;
int uN,vN;
int g[MAXN][MAXM];      //下标从0开始
int linker[MAXM][MAXN];
bool used[MAXM];
int num[MAXM];//右边最大的匹配数
bool dfs(int u){
    for(int v = 0; v < vN;v++)
        if(g[u][v] && !used[v]){
            used[v] = true;
            if(linker[v][0] < num[v]){
                linker[v][++linker[v][0]] = u;
                return true;
            }
            for(int i = 1;i <= num[v];i++)
                if(dfs(linker[v][i])){
                    linker[v][i] = u;
                    return true;
                }
        }
    return false;
}
int hungary(){
    int res = 0;
    for(int i = 0;i < vN;i++)
        linker[i][0] = 0;       //初始化右边第i点的已匹配点数为0
    for(int u = 0; u < uN; u++){
        memset(used,false,sizeof(used));
        if(dfs(u))res++;
    }
    return res;
}
/************************************************************/
```

### KM 算法
```
/************************************************************/
/* KM 算法 求最大权匹配问题
 * 复杂度 O(nx*nx*ny)
 * 若求最小权匹配,可将权值取相反数,结果取相反数
 * 首先将图读入到邻接矩阵g[][]中，然后设置两边的点数nx, ny
 * 接着调用KM()，返回最大权
 * 注意点的编号从 0 开始
 */

const int N = 310;
int nx,ny;                  //两边的点数
int g[N][N];                //二分图描述
int linker[N],lx[N],ly[N];  //y 中各点匹配状态,x,y 中的点标号
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
//  if(fopen("in", "r")!=NULL) {freopen("in", "r", stdin); freopen("out", "w", stdout);}
//  int n;
//  while(scanf("%d",&n) == 1){
//      for(int i = 0;i < n;i++)
//          for(int j = 0;j < n;j++)
//              scanf("%d",&g[i][j]);
//      nx = ny = n;
//      printf("%d\n",KM());
//  }
//  return 0;
//}

/************************************************************/
```

## A*算法
```
// 利用A*算法和dijkstra算法寻找k短路
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;  // INF表示无穷大

const int NODE_NUM = 1e5 + 9;  // 表示图的最大点数
const int EDGE_NUM = 1e5 + 9;  // 表示图的最大边数

int tot, head[NODE_NUM], headrev[NODE_NUM], h[NODE_NUM];

struct Edge {
    int to, cost, next;
    Edge() {}
    Edge(int to, int cost, int next): to(to), cost(cost), next(next) {}
}edge[EDGE_NUM << 1];

void init() {
    tot = 0;
    memset(head, -1, sizeof head);
    memset(headrev, -1, sizeof headrev);
}

void addedge(int u, int v, int cost) {
    edge[tot] = Edge{v, cost, head[u]};
    head[u] = tot++;
    edge[tot] = Edge{u, cost, headrev[v]};
    headrev[v] = tot++;
}

void dijkstra(int start) {
    priority_queue<pii, vector<pii>, greater<pii> > que;
    memset(h, INF, sizeof h);
    h[start] = 0;
    que.push(pii(0, start));
    while (!que.empty()) {
        pii p = que.top(); que.pop();
        int u = p.second;
        if (h[u] < p.first) continue;
        for (int i = headrev[u]; ~i; i = edge[i].next) {
            Edge e = edge[i];
            if(h[e.to] > h[u] + e.cost) {
                h[e.to] = h[u] + e.cost;
                que.push(pii(h[e.to], e.to));
            }
        }
    }
}

struct Status {
    int now, g;
    Status(int now, int g): now(now), g(g) {}
    bool operator < (const Status &rhs) const {
        return g + h[now] > rhs.g + h[rhs.now];
    }
};

int Astar(int start, int endd, int k) {
    if(h[start] == INF) {
        return -1;
    } else {
        int cnt[NODE_NUM];
        memset(cnt, 0, sizeof cnt);
        priority_queue<Status> que;
        que.push(Status(start, 0));
        while(!que.empty()) {
            Status sta = que.top();
            que.pop();
            int now = sta.now;
            int g = sta.g;
            cnt[now]++;
            if(cnt[endd] == k) return g;
            if(cnt[now] > k) continue;
            for(int i = head[now]; ~i; i = edge[i].next) {
                int to = edge[i].to;
                int cost = edge[i].cost;
                que.push(Status(to, g + cost));
            }
        }
    }
    return -1;
}

int main(void) {
    int nodeNum, edgeNum, u, v, cost, start, endd, k;
    while(~scanf("%d%d", &nodeNum, &edgeNum)) {
        init();
        for(int i = 0; i < edgeNum; i++) {
            // 表示u到v有一条权值为cost的有向边
            scanf("%d%d%d", &u, &v, &cost);
            addedge(u, v, cost);
        }
        scanf("%d%d%d", &start, &endd, &k);
        dijkstra(endd);
        if(start == endd) k++;
        printf("%d\n", Astar(start, endd, k));
    }
    return 0;
}
```

## 网络流
### 最大流
#### dinic
```
/************************************************************/
/* kuangbin版dinic算法：解决最大流问题(Untested)
 * 使用邻接表，效率更高
 * 时间复杂度：O(|E| * |V| * |V|)
 */
const int INF = 0x3f3f3f3f;
const int MAXN = 2010;//点数的最大值
const int MAXM = 1200010;//边数的最大值
struct Edge{
    int to,next,cap,flow;
}edge[MAXM];//注意是 MAXM
int tol;
int head[MAXN];
void init(){
    tol = 2;
    memset(head, -1,sizeof(head));
}
void addedge(int u,int v,int w,int rw = 0){
    edge[tol].to = v; edge[tol].cap = w; edge[tol].flow = 0;
    edge[tol].next = head[u]; head[u] = tol++;
    edge[tol].to = u; edge[tol].cap = rw; edge[tol].flow = 0;
    edge[tol].next = head[v]; head[v] = tol++;
}
int Q[MAXN];
int dep[MAXN],cur[MAXN],sta[MAXN];
bool bfs(int s,int t,int n){
    int front = 0,tail = 0;
    memset(dep, -1,sizeof(dep[0])*(n+1));
    dep[s] = 0;
    Q[tail++] = s;
    while(front < tail){
        int u = Q[front++];
        for(int i = head[u]; i != -1;i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dep[v] == -1){
                dep[v] = dep[u] + 1;
                if(v == t)return true;
                Q[tail++] = v;
            }
        }
    }
    return false;
}
int dinic(int s,int t,int n){
    int maxflow = 0;
    while(bfs(s,t,n)){
        for(int i = 0;i < n;i++)cur[i] = head[i];
        int u = s, tail = 0;
        while(cur[s] != -1){
            if(u == t){
                int tp = INF;
                for(int i = tail -1;i >= 0; i--)
                    tp = min(tp,edge[sta[i]].cap - edge[sta[i]].flow);
                maxflow += tp;
                for(int i = tail -1;i >= 0; i--){
                    edge[sta[i]].flow += tp;
                    edge[sta[i]^1].flow -= tp;
                    if(edge[sta[i]].cap - edge[sta[i]].flow == 0)
                        tail = i;
                }
                u = edge[sta[tail]^1].to;
            }
            else if(cur[u] != -1 && edge[cur[u]].cap > edge[cur[u
            ]].flow && dep[u] + 1 == dep[edge[cur[u]].to]){
                sta[tail++] = cur[u];
                u = edge[cur[u]].to;
            }
            else {
                while(u != s && cur[u] == -1)
                    u = edge[sta[ --tail]^1].to;
                cur[u] = edge[cur[u]].next;
            }
        }
    }
    return maxflow;
}
/************************************************************/
```
#### EK算法
```
/************************************************************/
/* EK算法：解决最大流问题，使用邻接矩阵，可打印路径(Tested 1 times)
 * 初始化：g[][], start, end, nn
 * 时间复杂度：O(|V| * |E| * |E|)
 */
const int MAXN = 110;//注意修改，有点小
const int INF = 0x3fffffff;
int g[MAXN][MAXN];//存边的容量，没有边的初始化为0
int path[MAXN], flow[MAXN], start, en;
int nn;//点的个数，编号0-nn.nn包括了源点和汇点

queue<int>q;
int bfs() {
    int i,t;
    while(!q.empty()) q.pop();//把清空队列
    memset(path, -1, sizeof path);//每次搜索前都把路径初始化成-1
    path[start] = 0;
    //memset(flow, 0, sizeof flow);//加上这一句，可在最终的残余网络求割边
    flow[start] = INF;//源点可以有无穷的流流进
    q.push(start);
    while(!q.empty()) {
        t = q.front();
        q.pop();
        if(t == en) break;
        //枚举所有的点，如果点的编号起始点有变化可以改这里
        for(i = 0;i <= nn; i++) {
            if(i != start && path[i] == -1 && g[t][i]) {
                flow[i] = min(flow[t], g[t][i]);
                q.push(i);
                path[i] = t;
            }
        }
    }
    if(path[en] == -1) return -1;//找不到增广路径了
    return flow[en];
}
int max_flow() {
    int max_flow = 0;
    int step, now, pre;
    while((step = bfs()) != -1) {
        max_flow += step;
        now = en;
        while(now != start) {
            pre = path[now];
            g[pre][now] -= step;
            g[now][pre] += step;
            now = pre;
        }
    }
    return max_flow;
}
/************************************************************/
```

#### ISAP
```
/************************************************************/
/* ISAP + bfs初始化 + 栈优化：超高效地解决最大流问题(Tested 7 times)
 * 注意修改MAXN和MAXM成适合的大小，以提高时间效率
 * 时间复杂度：O(|E| * |V| * |V|)
 */
const int MAXN = 100010;//点数的最大值
const int MAXM = 400010;//边数的最大值，注意反向边也要算进去，也就是说要乘以2
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next,cap,flow;
}edge[MAXM];//注意是 MAXM
int tol;
int head[MAXN];
int gap[MAXN],dep[MAXN],cur[MAXN];
void init(){
    tol = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w,int rw = 0){
    edge[tol].to = v; edge[tol].cap = w; edge[tol].flow = 0;
    edge[tol].next = head[u]; head[u] = tol++;
    edge[tol].to = u; edge[tol].cap = rw; edge[tol].flow = 0;
    edge[tol].next = head[v]; head[v] = tol++;
}
int Q[MAXN];
void BFS(int start,int end){
    memset(dep,-1,sizeof(dep));
    memset(gap,0,sizeof(gap));
    gap[0] = 1;
    int front = 0, rear = 0;
    dep[end] = 0;
    Q[rear++] = end;
    while(front != rear){
        int u = Q[front++];
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].to;
            if(dep[v] != -1)continue;
            Q[rear++] = v;
            dep[v] = dep[u] + 1;
            gap[dep[v]]++;
        }
    }
}
int S[MAXN];
// start起点，end为终点，nodeNum为顶点数，一般为en+1，注意en不为最后一个顶点的情况！
int sap(int start,int end,int nodeNum) {
    BFS(start,end);
    memcpy(cur,head,sizeof(head));
    int top = 0;
    int u = start;
    int ans = 0;
    while(dep[start] < N){
        if(u == end){
            int Min = INF;
            int inser;
            for(int i = 0;i < top;i++)
                if(Min > edge[S[i]].cap - edge[S[i]].flow){
                    Min = edge[S[i]].cap - edge[S[i]].flow;
                    inser = i;
                }
            for(int i = 0;i < top;i++){
                edge[S[i]].flow += Min;
                edge[S[i]^1].flow -= Min;
            }
            ans += Min;
            top = inser;
            u = edge[S[top]^1].to;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u]; i != -1; i = edge[i].next){
            v = edge[i].to;
            if(edge[i].cap - edge[i].flow && dep[v]+1 == dep[u]){
                flag = true;
                cur[u] = i;
                break;
            }
        }
        if(flag){
            S[top++] = cur[u];
            u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u]; i != -1; i = edge[i].next)
            if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min)
            {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]]--;
        if(!gap[dep[u]])return ans;
        dep[u] = Min + 1;
        gap[dep[u]]++;
        if(u != start)u = edge[S[--top]^1].to;
    }
    return ans;
}
/************************************************************/
```

### 最小费
#### Bellman-Ford
```
/************************************************************************************/
/* Bellman-Ford版的费用流算法，效率较低
 *
 */
struct edge { int to, cap, cost, rev; };

const int MAX_V=1e5+9;
int V;
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost){
    G[from].push_back((edge){to, cap, cost, static_cast<int>(G[to].size())});
    G[to].push_back((edge){from, 0, -cost, static_cast<int>(G[from].size()-1)});
}

int min_cost_flow(int s, int t, int f){
    int res=0;
    while(f>0){
        fill(dist, dist+V, INF);
        dist[s]=0;
        bool update=true;
        while(update){
            update=false;
            for(int v=0; v<V; v++){
                if(dist[v]==INF) continue;
                for(int i=0; i<G[v].size(); i++){
                    edge &e=G[v][i];
                    if(e.cap>0 && dist[e.to]>dist[v]+e.cost){
                        dist[e.to]=dist[v]+e.cost;
                        prevv[e.to]=v;
                        preve[e.to]=i;
                        update=true;
                    }
                }
            }
        }
    }

    if(dist[t]==INF){
        return -1;
    }

    int d=f;
    for(int v=t; v!=s; v=prevv[v]){
        d=min(d, G[prevv[v]][preve[v]].cap);
    }
    f-=d;
    res+=d*dist[t];
    for(int v=t; v!=s; v=prevv[v]){
        edge &e=G[prevv[v]][preve[v]];
        e.cap-=d;
        G[v][e.rev].cap+=d;
    }
    return res;
}

/************************************************************************************/
```

#### SPFA
```
/************************************************************/
/* SPFA版最小费用最大流算法(Tested 4 times)
 * 最小费用最大流,求最大费用只需要取相反数,结果取相反数即可。
 * 点的总数为 NN,点的编号 0 ~ NN-1
 * 时间复杂度：O(|E| * |V| * |V|)
 */
const int MAXN = 10000;
const int MAXM = 100000;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next,cap,flow,cost;
}edge[MAXM];
int head[MAXN],tol;
int pre[MAXN],dis[MAXN];
bool vis[MAXN];
int NN;//节点总个数,节点编号从 0 ∼ N-1
void init(int n){   //en表示汇点, 一般是init(en + 1); 大一点也没关系
    NN = n;
    tol = 0;
    memset(head, -1,sizeof(head));
}
void addedge(int u,int v,int cap,int cost){
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].cost = cost;
    edge[tol].flow = 0;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].cost = -cost;
    edge[tol].flow = 0;
    edge[tol].next = head[v];
    head[v] = tol++;
}
bool spfa(int s,int t){
    queue<int>q;
    for(int i = 0;i < NN;i++){
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1;i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge
                    [i].cost )
            {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if(!vis[v]){
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1)return false;
    else return true;
}
//返回的是最大流,cost 存的是最小费用
int minCostMaxflow(int s,int t,int &cost){
    int flow = 0;
    cost = 0;
    while(spfa(s,t)){
        int Min = INF;
        for(int i = pre[t];i != - 1;i = pre[edge[i^1].to]){
            if(Min > edge[i].cap - edge[i].flow)
                Min = edge[i].cap - edge[i].flow;
        }
        for(int i = pre[t];i != - 1;i = pre[edge[i^1].to]){
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        flow += Min;
    }
    return flow;
}
/************************************************************/
```

#### zkw
```
/************************************************************/
/* 对于二分图类型的比较高效
 *
 */
const int MAXN = 1009;
const int MAXM = 100009;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next,cap,flow,cost;
    Edge(int _to = 0,int _next = 0,int _cap = 0,int _flow = 0,int
            _cost = 0):
        to(_to),next(_next),cap(_cap),flow(_flow),cost(_cost){}
}edge[MAXM];
struct ZKW_MinCostMaxFlow{
    int head[MAXN],tot;
    int cur[MAXN];
    int dis[MAXN];
    bool vis[MAXN];
    int ss,tt,N;//源点、汇点和点的总个数(编号是 0 ∼ N-1), 不需要额外赋值, 调用会直接赋值
    int min_cost, max_flow;
    void init() {
        tot = 0;
        memset(head, -1,sizeof(head));
    }
    void addedge(int u,int v,int cap,int cost){
        edge[tot] = Edge(v,head[u],cap,0,cost);
        head[u] = tot++;
        edge[tot] = Edge(u,head[v],0,0, -cost);
        head[v] = tot++;
    }
    int aug(int u,int flow){
        if(u == tt)return flow;
        vis[u] = true;
        for(int i = cur[u];i != -1;i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && !vis[v] && dis[u] ==
                    dis[v] + edge[i].cost){
                int tmp = aug(v,min(flow,edge[i].cap -edge[i].flow))
                    ;
                edge[i].flow += tmp;
                edge[i^1].flow -= tmp;
                cur[u] = i;
                if(tmp)return tmp;
            }
        }
        return 0;
    }
    bool modify_label(){
        int d = INF;
        for(int u = 0;u < N;u++)
            if(vis[u])
                for(int i = head[u];i != -1;i = edge[i].next){
                    int v = edge[i].to;
                    if(edge[i].cap>edge[i].flow && !vis[v])
                        d = min(d,dis[v]+edge[i].cost - dis[u]);
                }
        if(d == INF)return false;
        for(int i = 0;i < N;i++)
            if(vis[i]){
                vis[i] = false;
                dis[i] += d;
            }
        return true;
    }
    /*
     * 直接调用获取最小费用和最大流
     * 输入: start-源点,end-汇点,n-点的总个数(编号从 0 开始)
     * 返回值: pair<int,int> 第一个是最小费用,第二个是最大流
     */
    pair<int,int> mincostmaxflow(int start,int end,int n){
        ss = start, tt = end, N = n;
        min_cost = max_flow = 0;
        for(int i = 0;i < n;i++)dis[i] = 0;
        while(1){
            for(int i = 0;i < n;i++)cur[i] = head[i];
            while(1){
                for(int i = 0;i < n;i++)vis[i] = false;
                int tmp = aug(ss,INF);
                if(tmp == 0)break;
                max_flow += tmp;
                min_cost += tmp*dis[ss];
            }
            if(!modify_label())break;
        }
        return make_pair(min_cost,max_flow);
    }
}solve;
/************************************************************/
```

## 计算几何
### 叉积
#### 定义
若$ \vec{OA}=(x_1,y_1)~~\vec{OB}=(x_2,y_2) $
定义叉积：$ \vec{OA}\times \vec{OB}=x_1y_2-x_2y_1 $
#### 性质
1. $ S_{\triangle OAB}={1\over 2}|\vec{OA}\times \vec{OB}| $
2. 已知直线上的两点s、e，可以求出ax+by+c=0的参数 
a = s.y-e.y; 
b = e.x-s.x; 
c = s×e;
#### 应用
##### 判断点与直线的相对位置
在直线上取两点P，Q，需要判断的点A与直线的相对位置。令 $ t = \vec{AP}\times \vec{AQ} $ ，分三种情况讨论：
1. 当$ t = 0 $时，A在直线PQ上。
2. 当$ t < 0 $时，A在直线左侧。
3. 当$ t > 0 $时，A在直线右侧。

### 凸多边形的面积公式及重心公式
1. 面积公式：
$ A = \frac{1}{2}\sum_{i=0}^{N-1}(x_i\ y_{i+1} - x_{i+1}\ y_i) $
2. 重心公式：
$ C_x = \frac{1}{6A}\sum_{i=0}^{N-1}(x_i+x_{i+1})(x_i\ y_{i+1} - x_{i+1}\ y_i) $
$ C_y = \frac{1}{6A}\sum_{i=0}^{N-1}(y_i+y_{i+1})(x_i\ y_{i+1} - x_{i+1}\ y_i) $

### 精度控制
1. sqrtl() 函数的输入参数为long double，范围值也是long double。cos，atan等同理，只l要在函数后加个l。

### 旋转卡壳
```
#include <iostream>
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
double EPS=1e-10;
/*
题意：
给定n个点，求凸边形宽的最小值
思想
1.计算多边形 y 方向上的端点。 我们称之为 ymin 和 ymax
2.通过 ymin 和 ymax 构造两条水平切线。 由于他们已经是一对对踵点， 计算他们之间的距离并维护为一个当前最大值。
3.同时旋转两条线直到其中一条与多边形的一条边重合。
4.一个新的对踵点对此时产生。 计算新的距离， 并和当前值比较， 并更新。
5.重复步骤3和步骤4的过程直到 再次产生对踵点对 (ymin,ymax) 。

*/
double add(double a,double b)
{
    if(abs(a+b)<EPS*(abs(a)+abs(b))) return 0;
    return a+b;
}

struct point{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){
    }
    point operator +(point p)
    {
        return point(add(x,p.x),add(y,p.y));
    }
    point operator -(point p)
    {
        return point(add(x,-p.x),add(y,-p.y));
    }
    point operator *(double d)
    {
        return point(x*d,y*d);
    }
    double dot(point p)
    {
        return add(x*p.x,y*p.y);
    }
    double det(point p)
    {
        return add(x*p.y,-y*p.x);
    }
};
double cross_product(point x,point y,point z)
{
    return (z-x).det(z-y);
}
double dis(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

/****************/
/**  旋转卡壳  **/
/****************/
double rotating_caliper(vector<point> v)
{
    double min_dis = INF;
    int n = v.size();
    v.push_back(v[0]);
    for (int i = 0; i < n; ++i)
    {
        double res=0;
        for(int j=0;j<n;j++)
        {
            res=max(res,cross_product(v[i],v[i+1],v[j])/dis(v[i],v[i+1]));
        }
        min_dis = min(min_dis,res);
     }
     return min_dis;
/*****************************************************************************************************/
/***                           优化的思路 但是莫名tle了                                           ***/
/**    int j = 2;                                                                                  ***/
/**    for (int i = 0; i < n; ++i)                                                                 ***/
/**    {                                                                                           ***/
/**      while (cross_product(v[i], v[i + 1], v[j]) < cross_product(v[i], v[i + 1], v[j + 1]))     ***/
/**      {                                                                                         ***/
/**          j = (j + 1) % n;                                                                      ***/
/**      }                                                                                         ***/
/**       min_dis = min(min_dis,cross_product(v[i],v[i+1],v[j])/dis(v[i],v[i+1]) );                ***/
/**    }                                                                                           ***/
/*****************************************************************************************************/
}

/****************/
/**  计算凸包  **/
/****************/

bool cmp(const point& p,const point& q)
{
    if(p.x!=q.x) return p.x<q.x;
    return p.y<q.y;
}
vector<point> convex_hull(point *ps,int n)
{
    sort(ps,ps+n,cmp);
    int k=0;
    vector<point> qs(n*2);
    for(int i=0;i<n;i++)
    {
        while(k>1&&(qs[k-1]-qs[k-2]).det(ps[i]-qs[k-1])<=0) k--;
        qs[k++]=ps[i];
    }
    for(int i=n-2,t=k;i>=0;i--)
    {
        while(k>t&& (qs[k-1]-qs[k-2]).det(ps[i]-qs[k-1])<=0) k--;
        qs[k++]=ps[i];
    }
    qs.resize(k-1);
    return qs;
}
point ps[105];
int main()
{
    int n;
    cin>>n;
    int cnt=0;
    for(int i=0;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        ps[cnt++]=point(a,b);
    }
    vector<point> qs=convex_hull(ps,n);
    double res=rotating_caliper(qs);
    printf("%.10f\n",res);
    return 0;
}

```


## 应对卡常
1. 使用快速读入、快速输出
2. 使用`vector.reserve(size);`，一次性申请好所需要的容器空间，避免多次拓容消耗更多的时间。
3. 使用`unorder_map`代替`map`
4. 在子函数前加`inline`
5. 尽可能减小memset的大小，如果是多维数组的初始化，则memset不好改，考虑直接循环初始化。需要注意的是，对同样大小的数组进行初始化，memset要比循环快。
6. 不要将`strlen(s)`放到循环的判断中，而是令`len = strlen(s)`，然后用`len`取代之。
7. 使用前向星写邻接表，而不是vector
8. 

## 应对WA
1. 检查INF是否设置得足够大
2. 检查算术运算是否爆范围，比如两个最小的int相减。
3. 

## C++库函数相关
### algorithm
#### min_element以及max_element
取数组或容器中的最小值/最大值，假如有多个相同，会取靠前的。可以通过写cmp函数来选靠后的。
```c++
// min_element/max_element example
#include <iostream>     // std::cout
#include <algorithm>    // std::min_element, std::max_element

bool myfn(int i, int j) { return i<j; }

struct myclass {
  bool operator() (int i,int j) { return i<j; }
} myobj;

int main () {
  int myints[] = {3,7,2,5,6,4,9};

  // using default comparison:
  std::cout << "The smallest element is " << *std::min_element(myints,myints+7) << '\n';
  std::cout << "The largest element is "  << *std::max_element(myints,myints+7) << '\n';

  // using function myfn as comp:
  std::cout << "The smallest element is " << *std::min_element(myints,myints+7,myfn) << '\n';
  std::cout << "The largest element is "  << *std::max_element(myints,myints+7,myfn) << '\n';

  // using object myobj as comp:
  std::cout << "The smallest element is " << *std::min_element(myints,myints+7,myobj) << '\n';
  std::cout << "The largest element is "  << *std::max_element(myints,myints+7,myobj) << '\n';

  return 0;
}
```

#### merge
可以将两个数组合并成一个数组:
```
merge(a, a+n, b, b+m, c);     
//将a数组中的n个元素和b数组中的m个元素合并放到c中, 注意c中要有足够的空间

merge(a.begin(), a.end(), b.begin(), b.end(), c.begin() )      
//注意c要先开辟好足够空间, 即像 vi c(N)这样;

merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(c) );        
//这是合法的, back_inserter(c) 会调用c.push_back();
```

### __buitin系列
__builtin_popcount：二进制中 1 的个数
__builtin_ctz：末尾的 0，即对 lowbit 取log
__builtin_clz：开头的 0，用 31 减可以得到下取整的 log

### 非标准库的内置函数
__gcd(x, y)

### set
#### set 多次 erase 的写法
``` 
//插入10个元素，然后删掉奇数元素
set<int> se;
for(int i = 0; i < 10; i++)
     se.insert(i);
//错误的erase示范
for(auto it = se.begin(); it != se.end(); it++) {
     if(*it & 1)
          se.erase(it);
}
//正确的erase示范
auto it = se.begin(), cur = it;
while(it != se.end()) {
     cur = it++;
     if(*cur & 1)
          se.erase(cur);
}
```
错误的erase示范虽然在Linux系统中能正常编译运行, 但是提交到CF上时出现RE! 经过搜索, 找到了正确示范的那种写法.

## 备注
1. 积分表另外打印
2. 数学公式另外打印
3. 上下界网络流另外打印
