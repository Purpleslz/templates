//连通图 有欧拉回路的图 二分图计数 SPOJ: KPGRAPHS 

#include <iostream>
#include <cstdio>
using namespace std;

const int MOD = 1000000007;

const int MAXN = 1000 + 10;

const int MAXV = 1000;

int N;

int C[MAXN][MAXN];

int f1[MAXN],f2[MAXN],f3[MAXN],t[MAXN];
int s3[MAXN];
int pow2[MAXN*MAXN];

int qpow(long long a,int b,int c)
{
  long long res = 1;
  for ( ; b; b >>= 1)
  {
    if (b & 1) res = res * a % c;
    a = a * a % c; 
  }
  return res;
}

int main()
{
  int TestCase;
  scanf("%d",&TestCase);
  for (int i=0;i<=MAXV;++i)
  {
    C[i][0] = 1;    
    for (int j = 1; j <= i; ++j)
    {
      C[i][j] = C[i-1][j] + C[i-1][j-1];
      if (C[i][j] >= MOD) C[i][j] -= MOD;
    }
  } 
  
  pow2[0] = 1;
  
  for (int i = 1; i <= 600000;++i)
  {
    pow2[i] = pow2[i-1] << 1;
    if (pow2[i] >= MOD) pow2[i] -= MOD;
  }
  
    for (int i = 1; i <= MAXV; ++i)
    {
      s3[i] = 0;
      for (int j = 0; j <= i; ++j)
        s3[i] = (1LL * C[i][j] * pow2[ j * (i-j) ] + s3[i]) % MOD;
    }
      
    
    f1[1] = 1;
    f2[1] = 1;
    f3[1] = 2;
    
    for (int i = 2; i <= MAXV; ++i)
    {
      f1[i] = pow2[ C[i][2] ];
      f2[i] = pow2[ C[i-1][2] ];
      f3[i] = s3[i];
      for (int j = 1; j < i; ++j)
      {
        f1[i] = (f1[i] - 1LL * C[i-1][j-1] * f1[j] % MOD * pow2[ C[i - j][2] ]) % MOD;
        f2[i] = (f2[i] - 1LL * C[i-1][j-1] * f2[j] % MOD * pow2[ C[i - j - 1][2] ] ) % MOD;
        f3[i] = (f3[i] - 1LL * C[i-1][j-1] * f3[j] % MOD * s3[i - j] ) % MOD; 
      }
      if (f1[i]<0) f1[i] += MOD;
      if (f2[i]<0) f2[i] += MOD;
      if (f3[i]<0) f3[i] += MOD;
    }

    int rev2 = qpow(2, MOD-2,MOD) ;
    
    for (int i=1;i<=MAXV;++i) f3[i] = 1LL * f3[i] * rev2 % MOD;
    
    t[0] = 1;
    for (int i = 1; i <= MAXV; ++i)
    {
      t[i] = f3[i];
      for (int j = 1; j < i; ++j)
        t[i] = (t[i] + 1LL * C[i-1][j-1] * f3[j] % MOD * t[i-j]) % MOD;
    }
    
  
  while (TestCase--)
  {
    scanf("%d",&N);
    printf("Connected: %d\n",f1[N]);
    printf("Eulerian: %d\n",f2[N]);
    printf("Bipartite: %d\n",t[N]);
    printf("\n");
  }
  return 0;
}
