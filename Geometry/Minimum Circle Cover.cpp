#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
  
const int MAXN=1000010;
  
const double eps=1e-6;
  
struct POINT
{
  double x,y,r;
  POINT () { };
  POINT (double a,double b,double c=0) { x=a; y=b; r=c; }
  POINT operator + (const POINT &A) { return POINT(x+A.x,y+A.y); }
  POINT operator - (const POINT &A) { return POINT(x-A.x,y-A.y); }
  POINT operator * (const double &A) { return POINT(x*A,y*A); }
}p[MAXN],circle;
  
int sgn(double x) { if (fabs(x)<eps) return 0; else if (x>eps) return 1; else return -1; }
  
inline double SQR(double x) { return x*x; }
  
inline double dist(const POINT &A,const POINT &B) { return sqrt(SQR(A.x-B.x)+SQR(A.y-B.y)); }
  
double cross(POINT A,POINT B) { return A.x*B.y-A.y*B.x; }
  
POINT getinsection(POINT A,POINT B,POINT C,POINT D)
{
  double t1=cross(B,C-A),t2=cross(C+D-A,B);
  return (C+D*(t1/(t1+t2)));
}
  
int N;
  
void getCircle(const POINT &A,const POINT &B,const POINT &C)
{
  POINT a,b,c,d;
  a=POINT((A.x+B.x)/2,(A.y+B.y)/2); b=POINT(B.y-A.y,A.x-B.x);
  c=POINT((C.x+B.x)/2,(C.y+B.y)/2); d=POINT(C.y-B.y,B.x-C.x);
  circle=getinsection(a,b,c,d);
  circle.r=dist(A,circle);
}
  
int main(void)
{
  scanf("%d",&N);
  for (int i=1;i<=N;++i)
  {
    scanf("%lf%lf",&p[i].x,&p[i].y);
    p[i].r=0;
  }
  random_shuffle(p+1,p+N+1);
  
  circle=p[1]; circle.r=0;
  for (int i=2;i<=N;++i)
  {
    if (sgn(dist(p[i],circle)-circle.r)>0)
    {
      circle=p[i]; circle.r=0;
      for (int j=i-1;j;--j)
        if (sgn( dist(p[j],circle)-circle.r ) >0 )
        {
          circle.r=dist(p[j],p[i])/2;
          circle.x=(p[j].x+p[i].x)/2;
          circle.y=(p[j].y+p[i].y)/2;
  
          for (int k=j+1;k<i;++k)
            if (sgn( dist(p[k],circle)-circle.r ) >0 )
              getCircle(p[i],p[j],p[k]);
        }
    }
  }
    
  printf("%.2lf %.2lf %.2lf",circle.x,circle.y,circle.r);
  return 0;
}
