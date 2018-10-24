/************************************************************/
/* inv_Fermat(a, p): 费马小定理求a关于p的逆元(Untested)
 * inv_extgcd(a, p: 拓展欧几里得求a关于p的逆元(Untested)
 * getFac(): 线性求MAXN个逆元、阶乘以及阶乘的逆元(Untested)
 */
ll pow_mod(ll a, ll b, ll p) {	//辅助函数
	ll ret = 1;
	while(b) {
		if(b & 1) ret = (ret * a) % p;
		a = (a * a) % p;
		b >>= 1;
	}
	return ret;
}

void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d){	//辅助函数
    if (!b) {d = a, x = 1, y = 0;}
    else{
        ex_gcd(b, a % b, y, x, d);
        y -= x * (a / b);
    }
}

ll inv_Fermat(ll a, ll p) {			//费马小定理求a关于p的逆元 
	return pow_mod(a, p-2, p);
}

ll inv_extgcd(ll a, ll p) {			//欧几里得求a关于p的逆元, 如果不存在，返回-1 
    ll d, x, y;
    ex_gcd(a, p, x, y, d);
    return d == 1 ? (x % p + p) % p : -1;
}

const int MAXN = 1e5;
ll fac[MAXN + 9], ifac[MAXN + 9], inv[MAXN + 9];

void getFac() {		//线性求MAXN个逆元、阶乘以及阶乘的逆元
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
