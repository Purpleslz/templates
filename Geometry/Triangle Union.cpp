
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-9; 

const int MAXN = 100;

int N;
double ans[MAXN];

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
  
  bool operator== (const pnt & a) const
  {
    return ( sgn(x - a.x) == 0 ) && ( sgn(y - a.y) == 0 );
  }
  
  bool operator< (const pnt & a) const
  {
    return ( sgn(x - a.x) == 0 ) ? ( sgn( y - a.y ) < 0 ) : (x < a.x);
  }
  
  double len() const
  {
    return sqrt(x*x + y*y);
  }

  double sqrlen() const
  {
    return x*x + y*y;
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

struct triangle
{
  pnt p[4];
}tri[MAXN];

struct rec
{
  pnt a,b;
  int type;
  rec() { }
  rec(pnt _a, pnt _b, int _type) { a = _a; b = _b; type = _type; } 
  bool operator< (const rec & A) const
  {
    return (a < A.a) || ( a == A.a && b < A.b); 
  }
}seg[MAXN*2],res[MAXN*MAXN*12];

int cnt,segn;
double lx[MAXN*MAXN*6];

inline double cross(pnt C,pnt A,pnt B) { return (A-C)*(B-C); }  

pnt gt_itsec_pnt(pnt A,pnt B,pnt C,pnt D)          
{
  double t1=cross(A,C,B),t2=cross(A,B,D);
  return (C+(D-C)/(1/(t1/(t1+t2))));
}

inline int line_relationship(pnt a1, pnt a2, pnt b1, pnt b2, pnt &c)
{
  if ( sgn( (a2-a1) * (b2 - b1) ) == 0 ) //parallel
  {
    if ( sgn( cross(a1, b1, b2) ) == 0 ) return 2;
    return 0; 
  }
  
  c = gt_itsec_pnt(a1, a2, b1, b2);
  
  if ( (sgn((a1-c) ^ (a2 - c)) <= 0) && (sgn((b1-c) ^ (b2 - c)) <= 0) ) return 1;
  return 0;
}

double getarea(pnt *a)
{
  double res = 0;
  for (int i = 0; i < 3; ++i)
  {
    res += a[i] * a[i+1];
  }
  return fabs(res);
}

void init()
{ 
  int mm = 0;
  for (int i = 1; i <= N; ++i)
    if ( sgn( getarea(tri[i].p) ) )
      tri[++mm] = tri[i];
  N = mm;

  cnt = 0;
  
  for (int i = 1; i <= N; ++i)
  {
    pnt a1,a2,b1,b2;
    for (int t = 0; t < 3; ++t)
    {
      a1 = tri[i].p[t];
      a2 = tri[i].p[t+1];
        
      lx[ ++cnt ] = a1.x;
        
      for (int j = i + 1; j <= N; ++j)
        for (int d = 0; d < 3; ++d)
        {
          b1 = tri[j].p[d];
          b2 = tri[j].p[d+1];
            
          pnt tmp;
            
          if ( line_relationship(a1, a2, b1, b2, tmp) == 1)
            lx[ ++cnt ] = tmp.x;
        } 
    }
  }
  
  sort(lx + 1, lx + cnt + 1);
  cnt = unique(lx + 1, lx + cnt + 1) - lx - 1;
  
  segn = 0;
  
  for (int t = 1; t <= N; ++t)
    for (int i = 0; i < 3; ++i)
      for (int j = i+1; j < 3; ++j)
      {
        pnt a = tri[t].p[i];
        pnt b = tri[t].p[j];
        pnt c = tri[t].p[ 3 - i - j];
        
        if ( sgn(a.x - b.x) == 0 ) continue;
        if ( b < a) swap(a,b);
        
        seg[ ++segn ] = rec(a, b, sgn( cross(a,b,c) ) );
      }
}

void work(double l, double r)
{
  int cnt = 0;
  for (int i = 1; i <= segn; ++i)
  {
    if (sgn(l - seg[i].a.x) >= 0 && sgn(seg[i].b.x - r) >= 0)
    {
      pnt a = gt_itsec_pnt(seg[i].a, seg[i].b, pnt(l,0), pnt(l,1));
      pnt b = gt_itsec_pnt(seg[i].a, seg[i].b, pnt(r,0), pnt(r,1));
      
      res[ ++cnt ] = rec(a, b, seg[i].type);
    }
  } 
    
  sort(res + 1, res + cnt + 1);
  
 // cout << "cnt = " << cnt << endl;
  
  int delta = 0;
  
  for (int i = 1; i < cnt; ++i)
  {
    delta += res[i].type;
    ans[ delta ] += (res[i+1].a.y - res[i].a.y + res[i+1].b.y - res[i].b.y) * (res[i].b.x - res[i].a.x) / 2;
  }
}

int main()
{
  int TestCase;
  scanf("%d",&TestCase);
  
  while (TestCase--)
  {
    scanf("%d",&N);
    
    int beforeN = N;
    
    for (int i = 1; i <= N; ++i) ans[i] = 0;
    
    for (int i = 1; i <= N; ++i)
    {
      for (int j = 0; j < 3; ++j)
        scanf("%lf%lf",&tri[i].p[j].x,&tri[i].p[j].y);
      tri[i].p[3] = tri[i].p[0];
    }
    
    init();
    
    for (int i = 1; i < cnt; ++i) work(lx[i], lx[i+1]);
        
    for (int i = 1; i <= beforeN; ++i)
      printf("%.10f\n",ans[i]);
      
  }
 
  
  return 0;
}

