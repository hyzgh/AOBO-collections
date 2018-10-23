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
