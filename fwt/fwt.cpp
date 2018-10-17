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
