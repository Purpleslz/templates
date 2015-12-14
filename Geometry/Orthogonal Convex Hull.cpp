
/*ans1 周长*/
/*ans2 面积*/ 

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=100010,oo=2000000000;

#define X first
#define Y second
#define ABS(x) ( ((x)<0)?(-(x)):(x) )

pair <int,int> p[MAXN],L[MAXN],R[MAXN],ans[MAXN],b[MAXN],a[MAXN];
int N,topL,topR,top,n;
long long ans1,ans2;

inline void read(int &x)
{
  char ch; int tmp=1;
  while (ch=getchar(),(ch>'9' || ch<'0') && (ch!='-') );
  if (ch=='-') { tmp=-1; ch=getchar(); }
  x=ch-48;
  while (ch=getchar(),ch<='9' && ch>='0') x=x*10+ch-48;
  x*=tmp;
}

long long cross(int x1,int y1,int x2,int y2) { return (long long)x1*y2-(long long)x2*y1; }

void doit(int delta)
{
  for (int i=1;i<=N;++i) a[i].X=p[i].X*delta,a[i].Y=p[i].Y;
  sort(a+1,a+N+1);
  int MAXL=oo,MAXR=-oo,NOWL,NOWR;
  topL=topR=top=0;
  for (int i=1,j;i<=N;i=j+1)
  {
    for (j=i;j<N && a[j+1].X==a[j].X;++j);
    NOWL=oo,NOWR=-oo;
    for (int k=i;k<=j;++k)
    {
      if (NOWL>a[k].Y) NOWL=a[k].Y;
      if (NOWR<a[k].Y) NOWR=a[k].Y;
    }
    if (NOWL<MAXL)
    {
      if (MAXL!=oo) L[++topL]=make_pair(a[i].X*delta,MAXL);
      L[++topL]=make_pair(a[i].X*delta,NOWL);
      MAXL=NOWL;
    }
    if (NOWR>MAXR)
    {
      if (MAXR!=-oo) R[++topR]=make_pair(a[i].X*delta,MAXR);
      R[++topR]=make_pair(a[i].X*delta,NOWR);
      MAXR=NOWR;
    }
  }
  for (int i=topL;i;--i) b[++top]=L[i];
  for (int i=1;i<=topR;++i) b[++top]=R[i];
}

int main(void)
{
  read(N);
  for (int i=1;i<=N;++i) { read(p[i].X); read(p[i].Y); }
  doit(1);
  for (int i=1;i<=top;++i) ans[++n]=b[i];
  doit(-1);
  for (int i=top;i;--i) ans[++n]=b[i];
  for (int i=1,j;i<=n;++i)
  {
    if (i<n) j=i+1; else j=1;
    if (ans[i].X==ans[j].X) ans1+=ABS(ans[i].Y-ans[j].Y); else ans1+=ABS(ans[i].X-ans[j].X);
    ans2+=cross(ans[i].X,ans[i].Y,ans[j].X,ans[j].Y);
  }
  if(ans2<0) ans2=-ans2; ans2>>=1;
  cout << ans1 << endl;
  cout << ans2 << endl;
  return 0;
}

