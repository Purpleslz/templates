const int TEN = 10000;
const int MAXL = 1000 + 10;  // 4*MAXL

struct BIGNUM
{
  int a[MAXL];  //length = a[0]
  
  BIGNUM () { memset(a,0,SIZE); }
  
  BIGNUM& operator= (const BIGNUM &B)
  {
    memcpy(a,B.a,sizeof(int)*MAXL);
    return (*this);
  }
  
  void print()
  {
    printf("%d",a[a[0]]);
    for (int i = a[0]-1;i;--i)
    {
      if (a[i]<10) printf("0");
      if (a[i]<100) printf("0");
      if (a[i]<1000) printf("0");
      printf("%d",a[i]);
    }
  }
  
  void getvalue(int x)
  {
    a[0] = 0;
    while (x)
    {
      a[ ++a[0] ] = x % TEN;
      x/=TEN;
    }
  }
};

bool operator< (const BIGNUM &A,const BIGNUM &B)
{
  if (A.a[0]!=B.a[0]) return A.a[0]<B.a[0];
  for (int i=A.a[0];i;--i) if (A.a[i]<B.a[i]) return 1; else if (A.a[i]>B.a[i]) return 0;
  return 0;
}

BIGNUM operator+ (const BIGNUM &A,const BIGNUM &B)
{
  BIGNUM C;
  C.a[0]=max(A.a[0],B.a[0]);
  for (int i=1;i<=C.a[0];++i)
  {
    C.a[i]+=A.a[i]+B.a[i];
    C.a[i+1]+=C.a[i]/TEN;
    C.a[i]%=TEN;
  }
  if (C.a[C.a[0]+1]) ++C.a[0];
  return C;
}

BIGNUM operator- (const BIGNUM &A,const BIGNUM &B)
{
  BIGNUM C;
  C.a[0]=max(A.a[0],B.a[0]);
  for (int i=C.a[0];i;--i)
  {
    C.a[i]=A.a[i]-B.a[i];
    if (C.a[i]<0)
    {
      C.a[i]+=TEN;
      int j=i+1;
      while (!C.a[j]) { C.a[j]+=TEN-1; ++j; }
      --C.a[j];
    }
  }
  while (C.a[C.a[0]]==0 && C.a[0]>1) --C.a[0];
  return C;
}

BIGNUM operator* (const BIGNUM &A,const BIGNUM &B)
{
  BIGNUM C;
  C.a[0]=A.a[0]+B.a[0]-1;
  for (int i=1;i<=A.a[0];++i)
    for (int j=1;j<=B.a[0];++j)
    {
      C.a[i+j-1]+=A.a[i]*B.a[j];
      C.a[i+j]+=C.a[i+j-1]/TEN;
      C.a[i+j-1]%=TEN;
    }
  if (C.a[C.a[0]+1]) ++C.a[0];
  return C;
}

BIGNUM operator/ (const BIGNUM &A,const int &B)   //高精除单精 
{
  BIGNUM C;
  C.a[0]=A.a[0];
  int M=0;
  for (int i=A.a[0];i;--i)
  {
    C.a[i]=M*TEN+A.a[i];
    M=C.a[i]%B;
    C.a[i]/=B;
  }
  while (C.a[C.a[0]]==0 && C.a[0]>1) --C.a[0];
  return C;
}

int operator% (const BIGNUM &A,const int &B)   //高精除单精 
{
  BIGNUM C;
  C.a[0]=A.a[0];
  int M=0;
  for (int i=A.a[0];i;--i)
  {
    C.a[i]=M*TEN+A.a[i];
    M=C.a[i]%B;
    C.a[i]/=B;
  }
  while (C.a[C.a[0]]==0 && C.a[0]>1) --C.a[0];
  return M;
}

//高精除高精? 
待补充 
//高精除高精? end 

