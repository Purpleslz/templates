
void solve(LL a,LL c,LL b)
{
  n=0;
  LL x,y;
  LL gcd=ext_gcd(a,b,x,y);
  if (c%gcd!=0) return ;
  x*=c/gcd;
  x%=(b/gcd);
  if (x<0) x+=(b/gcd);
  for (;x<b;x+=b/gcd) ans[++n]=qpow(g,x,b+1);
  sort(ans+1,ans+n+1);
}

int main(void)
{
  //x^K = a (mod P) 
  //第一行 解个数
  //第二行 各个解 
  
  
    n=0;
    if (A==0) { printf("1\n0\n"); continue; }
    g=findroot(P);
    b=ext_bsgs(g,A,P);
    if (b!=-1) solve(K,b,P-1);
    printf("%d\n",n);
    for (int i=1;i<n;++i) printf("%lld ",ans[i]);
    if (n>0) printf("%lld\n",ans[n]);
  return 0;
}
