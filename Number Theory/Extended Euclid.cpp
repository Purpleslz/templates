
typedef long long LL;

LL ext_gcd(LL a,LL b,LL &x,LL &y)
{
  if (b==0) { x=1; y=0; return a; }
  else
  {
    LL gcd=ext_gcd(b,a%b,x,y);
    LL t=x; x=y; y=t-a/b*y;
    return gcd;
  }
} 
