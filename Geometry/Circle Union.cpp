
//求恰好被覆盖K次的面积 SPOJ CIRU2

#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000 + 10;

const double eps = 1e-9;

const double pi = 3.141592653589793;

#define px first
#define py second

inline int sgn(double x) { if (fabs(x)<eps) return 0; else if (x>eps) return 1; else return -1; }

struct pnt
{
  double x,y;
  pnt () { };
  pnt (double a,double b) { x=a; y=b; }
  pnt operator + (const pnt &A) { return pnt(x+A.x,y+A.y); }
  pnt operator - (const pnt &A) { return pnt(x-A.x,y-A.y); }
  double operator ^ (const pnt &A) { return x*A.x+y*A.y; }   // 重载^点积 
  pnt operator / (const double &A) { return pnt(x/A,y/A); }
  double operator * (const pnt &A) { return x*A.y-A.x*y; }  //重载*叉积 
  
  double len() const
  {
    return sqrt(x*x + y*y);
  }
  
  pnt trunc(double l) const 
  {
    double r = l/len();
    return pnt(x*r,y*r);
  }
  
  pnt rotate_left() const
  {
    return pnt(-y,x);
  }
  
  pnt rotate_left(double ang) const
  {
    double c = cos(ang), s = sin(ang);
    return pnt(x*c - y*s, y*c + x*s);
  }
  
  pnt rotate_left(double c,double s) const
  { 
    return pnt(x*c - y*s, y*c + x*s);
  }
  
  pnt rotate_right() const
  {
    return pnt(y,-x);
  }
  
  pnt rotate_right(double ang) const
  {
    double c = cos(ang), s = sin(ang);
    return pnt(x*c + y*s, y*c - x*s);
  }
  
  pnt rotate_right(double c,double s) const
  {
    return pnt(x*c + y*s, y*c - x*s);
  }
};

struct rec
{
  double ang;
  pnt p;
  int v;
  rec () { };
  rec (double _ang, pnt _p, int _v) { ang = _ang; p = _p; v = _v; }
}a[MAXN * 4];

int N;

double ans[MAXN];

struct circle
{
  pnt c;
  double r;
  int cnt;
  circle () {}
  
  circle (const pnt & _c, double _r, int _cnt) { c = _c; r = _r; cnt = _cnt;}
  
  double area() const { return pi * r * r; } 
}cir[MAXN];

pair<rec,rec> circle_intersection(circle c1,circle c2)
{
  pnt a = c1.c;
  pnt b = c2.c;
  double r1 = c1.r;
  double r2 = c2.r;
  
  double d = (b - a).len();
  
  double c = (r1 * r1 + d * d - r2 * r2) / ( 2 * r1 * d);
  double s = sqrt( 1.0 - c * c);
  pnt v = (b - a) . trunc(r1);

  pnt ans1 = v.rotate_right(c,s);
  pnt ans2 = v.rotate_left(c,s);
  return make_pair( rec( atan2(ans1.y, ans1.x), a + ans1, 1),
                    rec( atan2(ans2.y, ans2.x), a + ans2, -1) );
}

bool isdel[MAXN];

inline bool circmp(const circle &a, const circle &b) 
{
  return a.r < b.r;
}

void init()
{
  sort(cir+1,cir+N+1,circmp);
  
  for (int i = 1; i <= N; ++i)
    for (int j = i + 1; j <= N; ++j)
      if ( sgn( (cir[i].c - cir[j].c).len() - (cir[j].r - cir[i].r) ) <= 0)
        cir[i].cnt++;
}

inline double getarea(rec a, rec b, double r)
{
  double t = b.ang - a.ang;
  return 0.5 * r * r * ( t - sin(t) ) + 0.5 * (a.p * b.p);
}

inline bool cmp(const rec &a, const rec &b)
{
  if ( sgn(a.ang - b.ang) != 0 ) return a.ang < b.ang;
  else return a.v > b.v;
}

void work(int now)
{
  int cnt = 0;
  
  pnt O = cir[now].c - pnt(cir[now].r,0);
  
  a[ ++cnt ] = rec(0, O, 0);
  a[ ++cnt ] = rec(2 * pi, O, 0);
  
  for (int i = 1; i <= N; ++i)
  {
    if (i == now || sgn( (cir[i].c - cir[now].c).len() - cir[i].r - cir[now].r) >= 0 ) continue;
    if ( sgn( (cir[now].c - cir[i].c).len() - (cir[i].r - cir[now].r) ) <= 0) continue;
    if ( sgn( (cir[now].c - cir[i].c).len() - (cir[now].r - cir[i].r) ) <= 0) continue;
    
    //判断掉非恰好2交点的情况 
    
    pair<rec,rec> tmp = circle_intersection(cir[now], cir[i]);
    
    a[ ++cnt ] = tmp.px;
    a[cnt].ang += pi;
    
    a[ ++cnt ] = tmp.py;
    a[cnt].ang += pi;
    
    if (a[cnt - 1].ang > a[cnt].ang)
    {
      a[ ++cnt ] = rec(0, O, 1);
      a[ ++cnt ] = rec(2*pi, O, -1);
    }
  }
  
  sort(a + 1, a + cnt + 1, cmp);
  
  int delta = cir[now].cnt;
  
  for (int i = 1; i < cnt; ++i)
  {
    delta += a[i].v;
    ans[ delta ] += getarea(a[i], a[i + 1], cir[now].r);
  }
  
}

int main()
{
  scanf("%d",&N);
  
  for (int i = 1; i <= N; ++i)
  {
    scanf("%lf%lf%lf",&cir[i].c.x,&cir[i].c.y,&cir[i].r);
    cir[i].cnt = 1;
  }
  
  init();
  
  for (int i = 1; i <= N; ++i) work(i);
      
  for (int i = 1; i < N; ++i) ans[i] -= ans[i+1];  //至少覆盖K次 -> 恰好覆盖K次 
    
  for (int i = 1; i <= N; ++i) printf("[%d] = %.3f\n",i,ans[i]);
  
  return 0;
}

