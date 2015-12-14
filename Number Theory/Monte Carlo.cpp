
LL gcd(LL a,LL b)
{
  while (b)
  {
    a%=b;
    swap(a,b);
  }
  return a;
}
 
LL plusmod(LL a,LL b,LL c)
{
  a+=b;
  return (a<c) a:a-c;
}
 
LL minusmod(LL a,LL b,LL c)
{
  a-=b;
  return (a>=0) a:a+c;
}
 
LL mulmod(LL a,LL b,LL c)
{
  a%=c;
  LL res=0;
  for (;b;b>>=1)
  {
    if (b&1) res=plusmod(res,a,c);
    a=plusmod(a,a,c);
  }
  return res;
}
 
LL powmod(LL a,LL b,LL c)
{
  a%=c;
  LL res=1;
  for (;b;b>>=1)
  {
    if (b&1) res=mulmod(res,a,c);
    a=mulmod(a,a,c);
  }
  return res;
}
 
bool isprime(LL now)
{
  int p[5]={2,3,5,7,11};
  if (now==1) return false;
  if (now==2 || now==3 || now==5 || now==7 || now==11) return true;
  for (int i=0;i<5;++i) if (powmod(p[i]%now,now-1,now)!=1) return false;
  for (int i=0;i<5;++i) if (powmod(rand()%(now-1)+1,now-1,now)!=1) return false;
  return true;
}
