
/* fac[i]是去掉了所有p的倍数的阶乘
*  p[]存的是分解质因数之后的质数  num[]存的是分解质因数之后的p^k 
*
*  A中存答案 为中国剩余定理做准备 
*
*  中国剩余定理之后乱搞 */ 

long long ext_gcd(long long a, long long b, long long &x, long long &y)
{
  if (b==0)
  {
    x=1; y=0;
    return a;
  }
  else
  {
    long long t=ext_gcd( b, a % b , x, y);
    long long tmp=x;
    x=y;
    y=tmp-a/b*y;
    return t;
  }
}

inline long long solve_mod_linear(long long A, long long B, long long N) //ax = b ( mod N)  ax+Ny=b 解模线性方程 
{
  long long x,y;
  long long t=ext_gcd(A,N,x,y);
  
  if (B%t != 0 ) {} //无解 
  
  x=x*(B/t) % N;
  x=( x + N ) % N;
  return x;
}

void prepare(int NOW)
{
  fac[0]=1;
  for (long long i=1;i<=num[NOW];++i)
  {
    fac[i]=fac[i-1];
    if (i%p[NOW]) fac[i]=(fac[i]*i) % num[NOW];
  }
}

long long count(long long A,long long T) //计算A!中T因子的个数 
{
  long long res=0;
  for (;A>=T;A/=T) res+=A/T;
  return res;
}

inline long long get_inv(long long A,long long B) { return solve_mod_linear(A,1,B); } //逆元

long long pow(long long A,long long B,long long MOD)
{
  long long ans=1;
  for (;B;B>>=1)
  {
    if (B & 1) ans=(ans*A) % MOD;
    A=(A*A) % MOD;
  }
  return ans;
}

long long calcfac(long long N,int NOW)
{
  if (N<p[NOW]) return fac[N];
  long long seg=N/num[NOW],rest=N % num[NOW];
  long long res=pow(fac[num[NOW]-1],seg,num[NOW])*fac[rest] % num[NOW];  //使用威尔逊定理可优化这部分 
  res=res*calcfac(N/p[NOW],NOW) % num[NOW];
  return res;
}
 
inline void calc(long long AA,long long BB,int now)
{
  long long tmp1=count(BB,p[now]);
  long long tmp2=count(AA,p[now])+count(BB-AA,p[now]);
  if (tmp1-tmp2>=c[now]) A[now]=0;
  else
    A[now]=calcfac(BB,now) * get_inv( calcfac(AA,now) , num[now]) % num[now]  * get_inv( calcfac(BB-AA,now) ,num[now]) % num[now] 
         * pow(p[now],tmp1-tmp2,num[now]) % num[now];
}

int main()
{
  tot = 0; 
  tmp=P;
  for (int i=2;i<=tmp;++i)
  {
    if (tmp % i == 0) { ++tot; p[tot]=i; num[tot]=1; }
    for (;tmp % i == 0;tmp/=i) { ++c[tot]; num[tot]*=i; }
  }                                                         //将p分解质因数
  
  for (int i=1;i<=tot;++i)
  {
    prepare(i); 
    calc(M,N,i); //C(N,M) N>=M 
  } 
  
  for (int i=1;i<=tot;++i) ans=(ans+(solve_mod_linear(P/num[i],A[i],num[i])*P/num[i]) % P) % P; //中国剩余定理
   
}
