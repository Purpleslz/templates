/*  暴力求 原根一般很小
*   m有原根的充要条件：m=1,2,4,p,2p,p^n,p是奇质数,n是任意正整数
*   当m有原根 它有phi(phi(m))个原根  */     

LL findroot(LL p)
{
  tot=0;
  for (int i=1,tmp=p-1;i*i<=tmp;++i)
    if (tmp % i == 0)
    {
      a[++tot]=i;
      if (tmp/i!=i) a[++tot]=tmp/i;
    }
  sort(a+1,a+tot+1);

  for (int i=1,j;;++i)
  {
    for (j=1;j<=tot;++j) if (qpow((LL)i,a[j],p)==1) break;
    if (j==tot) return i;
  }
} 
