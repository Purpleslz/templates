
/* 计算的是x*y 同时处理了进位 */ 



#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
 
const int MAXN=132000;
const double PI=3.14159265358979323846;
 
struct complex
{
  double r,i;
  complex() { }
  complex(double a, double b) { r=a; i=b; }
  complex operator + (const complex &A) { return complex(r+A.r,i+A.i); }
  complex operator - (const complex &A) { return complex(r-A.r,i-A.i); }
  complex operator * (const complex &A) { return complex(r*A.r-i*A.i,A.r*i+r*A.i); }
};
 
char str1[MAXN],str2[MAXN];
int N,n,ans[MAXN];
complex a[MAXN],b[MAXN],A[MAXN],B[MAXN],C[MAXN];
 
void dft(complex *a,complex *A,int n,int step,bool flag)
{
  if (n==1) A[0]=a[0];
  else
  {
    int m=n>>1;
    dft(a,A,m,step<<1,flag); dft(a+step,A+m,m,step<<1,flag);
    complex even,odd,root,tmp=complex(1,0);
    if (flag) root=complex(cos(PI*2.0/n),sin(PI*2.0/n)); else root=complex(cos(PI*2.0/n*(n-1)),sin(PI*2.0/n*(n-1)));
    for (int i=0;i<m;++i)
    {
      even=A[i]; odd=A[i+m]*tmp;
      A[i]=even+odd; A[i+m]=even-odd;
      tmp=tmp*root;
    }
  }
}
 
void fft(complex *a,complex *A,complex *b,complex *B,int n,complex *C)
{
  dft(a,A,n,1,1); dft(b,B,n,1,1);
  for (int i=0;i<n;++i) A[i]=A[i]*B[i];
  dft(A,C,n,1,0);
  for (int i=0;i<n;++i) C[i].r/=n;
}
 
int main(void)
{
  scanf("%d",&N);
  scanf("%s",str1);
  scanf("%s",str2);
  for (int i=0;i<N;++i)
  {
    a[i].r=str1[N-1-i]-48;
    b[i].r=str2[N-1-i]-48;
  }
   
  for (n=1;n<2*N;n<<=1);
 
  fft(a,A,b,B,n,C);
 
  int len=0;
  for (int i=0;i<MAXN;++i)
  {
    ans[i]+=(int)floor(C[i].r+0.5);
    if (ans[i]) len=i;
    ans[i+1]+=ans[i]/10;
    ans[i]%=10;
  }
  for (int i=len;i>=0;--i) printf("%d",ans[i]);
  printf("\n");
  return 0;
}
