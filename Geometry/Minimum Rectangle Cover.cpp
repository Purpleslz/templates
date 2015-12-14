//BZOJ 1185

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
  
#define x first
#define y second
#define next(x) ( ((x)==N)?1:((x)+1)  )
#define pred(x) ( ((x)==1)?N:((x)-1)  )
  
typedef pair<double,double> PDD;
  
const double eps=1e-10;
const int MAXN=50010;
  
int N,top,LAST,u,l,r;
double ANS;
PDD a[MAXN],p[MAXN],ori,ans[4],love;
  
int dcmp(double a) { if (fabs(a)<eps) return 0; else return a<0?-1:1; }
inline double sqr(double x) { return x*x; }
PDD operator- (PDD A,PDD B) { return make_pair(A.x-B.x,A.y-B.y); }
PDD operator+ (PDD A,PDD B) { return make_pair(A.x+B.x,A.y+B.y); }
PDD operator* (PDD A,double B) { return make_pair(A.x*B,A.y*B); }
inline double Xj(PDD A,PDD B) { return A.x*B.y-B.x*A.y; }
inline double Dj(PDD A,PDD B) { return A.x*B.x+A.y*B.y; }
inline int NEXT(int x) { if (x==N) return 1; else return x+1; }
inline double f1(int now,int i) { return Xj(p[now]-p[i],p[i+1]-p[i]); }
inline double f2(int now,int i) { return Dj(p[now]-p[i],p[i+1]-p[i]); }
inline double dis(PDD A,PDD B) { return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y)); }
  
int main(void)
{
  scanf("%d",&N);
  for (int i=1;i<=N;++i) scanf("%lf%lf",&a[i].x,&a[i].y);
  sort(a+1,a+N+1);
  
  //convex hull
  for (int i=1;i<=N;++i)
  {
    while (top>1 && dcmp(Xj(p[top]-p[top-1],a[i]-p[top-1]))<=0) --top;
    p[++top]=a[i];
  }
  LAST=top-1;
  for (int i=N-1;i;--i)
  {
    while (top-LAST>1 && dcmp(Xj(p[top]-p[top-1],a[i]-p[top-1]))<=0) --top;
    p[++top]=a[i];
  }
  --top;
  //convex hull
  
  ori.x=ori.y=0;
  N=top;
  
  l=N;
  u=r=3; ANS=1e99;
  for (int i=1;i<=N;++i)
  {
    while (dcmp( fabs(f1(next(u),i)) - fabs(f1(u,i)) )>=0) u=next(u);
    while (dcmp( fabs(f2(next(r),i)) - fabs(f2(r,i)) )>=0) r=next(r);
    //if (i==1) l=r;
    while (dcmp( fabs(f2(pred(l),i)) - fabs(f2(l,i)) )>=0) l=pred(l);
    double d=dis(p[i],p[i+1]);
    double tmp=fabs(f1(u,i)/d)*( fabs(f2(l,i)/d)+fabs(f2(r,i)/d) );
    if (tmp<ANS)
    {
      ANS=tmp;
      ans[0]=p[i]+(p[i+1]-p[i])*(f2(l,i)/d/d);
      ans[1]=p[i]+(p[i+1]-p[i])*(f2(r,i)/d/d);
      PDD tmplove=p[i+1]-p[i];
      love.x=-tmplove.y;
      love.y=tmplove.x;
      love=love*(fabs(f1(u,i)/d)/dis(ori,love));
      ans[2]=ans[1]+love;
      ans[3]=ans[0]+love;
    }
  }
  printf("%.5lf\n",ANS);
  int tmp=0;
  for (int i=1;i<4;++i) if (ans[i].y<ans[tmp].y  || (ans[i].y==ans[tmp].y && ans[i].x<ans[tmp].x)) tmp=i;
  for (int i=tmp;i<4;++i) printf("%.5lf %.5lf\n",ans[i].x+eps,ans[i].y+eps);
  for (int i=0;i<tmp;++i) printf("%.5lf %.5lf\n",ans[i].x+eps,ans[i].y+eps);
  return 0;
}
