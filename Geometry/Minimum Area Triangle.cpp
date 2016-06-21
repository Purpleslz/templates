/**************************************************************
    Problem: 2458
    User: Purpleslz
    Language: C++
    Result: Accepted
    Time:392 ms
    Memory:3620 kb
****************************************************************/
 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
 
#define X first
#define Y second
#define sqr(x) ( (x) * (x) )
 
typedef pair<int,int> PII;
 
const int MAXN=200010;
 
PII p[MAXN];
 
int N,tmp[MAXN];
double ans=1e10;
 
inline void read(int &x)
{
  char ch; int tmp=1;
  while (ch=getchar(),(ch!='-') && (ch>'9' || ch<'0') );
  if (ch=='-') { tmp=-1; ch=getchar(); }
  x=ch-48;
  while (ch=getchar(),ch<='9' && ch>='0') x=x*10+ch-48;
  x*=tmp;
}
 
inline bool cmpx(const PII &A,const PII &B) { return A.X<B.X; }
inline bool cmpy(int A,int B) { return p[A].Y<p[B].Y; }
 
inline double dist(int A,int B) { return sqrt(sqr( (double)p[A].X-p[B].X ) + sqr( (double)p[A].Y-p[B].Y ) ); }
 
inline double calc(int A,int B,int C) { return dist(A,B)+dist(A,C)+dist(B,C); }
 
inline double min(double A,double B) { return A<B?A:B; }
 
void doit(int l,int r)
{
  if (r-l+1<3) return ;
  int mid=( l+r ) >> 1;
  doit(l,mid-1); doit(mid+1,r);
  int n=0;
  for (int i=l;i<=r;++i) if (abs(p[i].X-p[mid].X)*2<ans) tmp[++n]=i;
  sort(tmp+1,tmp+n+1,cmpy);
  for (int i=1;i<=n-2;++i)
    for (int j=i+1;(j<n) && (abs(p[tmp[i]].Y-p[tmp[j]].Y)*2<ans);++j)
      for (int k=j+1;(k<=n) && (abs(p[tmp[i]].Y-p[tmp[k]].Y)*2<ans);++k)
        ans=min(ans,calc(tmp[i],tmp[j],tmp[k]));
}
 
int main(void)
{
  read(N);
  for (int i=1;i<=N;++i) { read(p[i].X); read(p[i].Y); }
  sort(p+1,p+N+1,cmpx);
  doit(1,N);
  printf("%.6lf",ans);
  return 0;
}

/**************************************************************
    Problem: 2458
    User: CrystalLove
    Language: C++
    Result: Accepted
    Time:1560 ms
    Memory:9484 kb
****************************************************************/
 
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
double ans;
struct Tpoint
{
    double x, y;
} p[200010], q[200010];
 
bool cmpx(Tpoint a, Tpoint b) { return a.x < b.x; }
bool cmpy(Tpoint a, Tpoint b) { return a.y < b.y; }
 
double sqr(double a) { return a * a; }
 
double dis(Tpoint a, Tpoint b) { return sqrt( sqr(a.x - b.x) + sqr(a.y - b.y) ); }
 
double cal(Tpoint a, Tpoint b, Tpoint c) { return dis(a, b) + dis(b, c) + dis(c, a); }
 
void work(int l, int r)
{
    if(r - l <= 2)
    {
        sort(p + l, p + r + 1, cmpy);
        if(r - l == 2)
            ans = min(ans, cal(p[l], p[l+1], p[r]));
        return;
    }
    int mid = l + r >> 1, mx = p[mid].x, top = 0;
    work(l, mid); work(mid + 1, r);
    inplace_merge(p + l, p + mid + 1, p + r + 1, cmpy);
    for(int i = l; i <= r; ++i)
        if(abs(p[i].x - mx) < ans / 2) q[++top] = p[i];
    for(int i = 1; i <= top; ++i)
        for(int j = i - 1; j > 0 && q[i].y - q[j].y < ans / 2; --j)
            for(int k = i - 1; k > 0 && q[i].y - q[k].y < ans / 2; --k)
                if(j != k) ans = min(ans, cal(q[i], q[j], q[k]));
}
 
int main()
{
    int N; ans = 1e100; cin >> N;
    for(int i = 1; i <= N; ++i)
        cin >> p[i].x >> p[i].y;
    sort(p + 1, p + 1 + N, cmpx);
    work(1, N); printf("%.6lf\n", ans);
}
