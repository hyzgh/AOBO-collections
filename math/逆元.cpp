//O（n）求p（素数）以内的所有逆元
void getinv()
{
  inv[1]=1;
  for(int i=2;i<=n;i++)
    inv[i]=1ll*(p-p/i)*inv[p%i]%p;
}
