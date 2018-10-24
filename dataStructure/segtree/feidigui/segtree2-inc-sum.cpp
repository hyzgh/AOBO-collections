/**************************************************/
/* 区间增减, 求和
 * used variables: n, h, t[], d[];
 * 根节点为1, 修改查询注意左闭右开
 */
int t[N*2], d[N*2], n, h;

void init(){
	for(int i=n-1; i>=1; i--)
		t[i]=t[i<<1]+t[i<<1|1];
	h = sizeof(int) * 8 - __builtin_clz(n);
}

void calc(int p, int k){
	t[p]=t[p<<1] + t[p<<1|1] + d[p]*k;
}

void apply(int p, int value, int k){
	t[p]+=value*k;
	if(p<n) d[p]+=value;
}

void build(int l, int r){
	int k=2;
	for(l+=n, r+=n-1; l>1; k<<=1){
		l>>=1, r>>=1;
		for(int i=r; i>=l; i--) calc(i, k);
	}
}

void push(int l, int r){
	int s=h, k=1<<(h-1);
	for(l+=n, r+=n-1; s>0; s--, k>>=1)
		for(int i=l>>s; i<=r>>s; i++)
			if(d[i]!=0){
				apply(i<<1, d[i], k);
				apply(i<<1|1, d[i], k);
				d[i]=0;
			}
}

void add(int l, int r, int value){
	if(value==0) return;
	push(l, l+1);
	push(r-1, r);
	int l0=l, r0=r, k=1;
	for(l+=n, r+=n; l<r; l>>=1, r>>=1, k<<=1){
		if(l&1) apply(l++, value, k);
		if(r&1) apply(--r, value, k);
	}
	build(l0, l0+1);
	build(r0-1, r0);
}

int query(int l, int r){
	push(l, l+1);
	push(r-1, r);
	int res=0;
	for(l+=n, r+=n; l<r; l>>=1, r>>=1){
		if(l&1) res+=t[l++];
		if(r&1) res+=t[--r];
	}
	return res;
}
/**************************************************/
