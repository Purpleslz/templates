
/*配合上面的素数判定就可以快速质因数分解了 答案在p[]里，数量为cnt*/ 

LL pollardrho(LL n,LL c)
{
  LL x=2,y=2,d=1;
  while (d==1)
  {
    x = (mulmod(x,x,n)+c)%n;
    y = (mulmod(y,y,n)+c)%n;
    y = (mulmod(y,y,n)+c)%n;
    if (x>y) d=gcd(x-y,n); else d=gcd(y-x,n);
  }
  return d;
}
 
LL getfactor(LL now)
{
  LL tmp=pollardrho(now,(rand()+1)%now);
  for (tmp;tmp==now;tmp=pollardrho(now,(rand()+1)%now));
  return tmp;
}
 
void fullfractorize(LL now)
{
  if (now==1) return ;
  if (isprime(now)) { p[++cnt]=now; return; }
 
  LL tmp=getfactor(now);
  fullfractorize(tmp);
  fullfractorize(now/tmp);
} 
