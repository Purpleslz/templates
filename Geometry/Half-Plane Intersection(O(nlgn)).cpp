//HDU 5462 Manors
//Half-Plane Intersection
//O(nlgn)

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 100 + 10;

double sumx[MAXN], sumy[MAXN], sumx2[MAXN], sumy2[MAXN];

const double eps=1e-10;

int N,M;


//符号 
inline int sgn(double x) { if (fabs(x)<eps) return 0; else if (x>eps) return 1; else return -1; }
//符号 end 

double trim(double d, double l = 1.0) {
 return d > l ? l : (d < -l ? -l : d);
}

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
  
  bool operator== (const pnt & a) const { return ( sgn(x - a.x) == 0 ) && ( sgn(y - a.y) == 0 ); }
  
  bool operator< (const pnt & a) const { return ( sgn(x - a.x) == 0 ) ? ( sgn( y - a.y ) < 0 ) : (x < a.x); }

  double len() const { return sqrt(x*x + y*y); }

  double sqrlen() const { return x*x + y*y; }
  
  pnt trunc(double l) const 
  {
    double r = l/len();
    return pnt(x*r,y*r);
  }
  
  pnt rotate_left() const { return pnt(-y,x); }
  
  pnt rotate_left(double ang) const
  {
    double c = cos(ang), s = sin(ang);
    return pnt(x*c - y*s, y*c + x*s);
  }
  
  pnt rotate_left(double c,double s) const { return pnt(x*c - y*s, y*c + x*s); }
  
  pnt rotate_right() const { return pnt(y,-x); }
  
  pnt rotate_right(double ang) const
  {
    double c = cos(ang), s = sin(ang);
    return pnt(x*c + y*s, y*c - x*s);
  }
  
  pnt rotate_right(double c,double s) const { return pnt(x*c + y*s, y*c - x*s); }
};

struct LINE
{
  pnt a,b;
  LINE() { }
  LINE(pnt _a, pnt _b) { a = _a; b = _b; }
}L[MAXN];

pnt P2[6], P[MAXN];

double res[MAXN];

inline double arg(pnt a) { return atan2(a.y, a.x); }

double cross(pnt c, pnt a, pnt b)
{
  return (a - c) * (b - c);
}

inline bool satisfy(pnt c, LINE l)
{
  return sgn( cross(l.a, c, l.b) ) <= 0;
}

inline bool cmp(LINE l1, LINE l2)
{
  int res = sgn( arg(l1.b - l1.a) - arg(l2.b - l2.a) );
  return res == 0 ? satisfy(l1.a, l2) : res < 0;
}

pnt gt_itsec_pnt(pnt A,pnt B,pnt C,pnt D)          
{
  double t1=cross(A,C,B),t2=cross(A,B,D);
  return (C+(D-C)/(1/(t1/(t1+t2))));
}

pnt crosspoint(LINE A, LINE B)
{
  return gt_itsec_pnt(A.a, A.b, B.a, B.b);
}

int HalfPlaneIntersection(LINE *L, int n, pnt *P)
{
  sort(L + 1, L + n + 1, cmp);
  
  LINE *q = new LINE[n + 2];
  pnt *ans = new pnt[n + 2];
  
  int head0 = 1, tail0 = 0;
  int head1 = 1, tail1 = 0;
  
  q[++tail0] = L[1];
  
  for (int i = 2; i <= n; ++i)
  {
    if (sgn( arg(L[i].b - L[i].a) - arg( L[i-1].b - L[i-1].a ) ) == 0) continue;
    
    while (head1 <= tail1 && !satisfy(ans[tail1], L[i]) ) { --tail1; --tail0; }
    while (head1 <= tail1 && !satisfy(ans[head1], L[i]) ) { ++head1; ++head0; }
    
    ans[ ++tail1 ] = crosspoint( q[tail0], L[i] );
    q[ ++tail0 ] = L[i]; 
  }
  
  while (head1 <= tail1 && !satisfy(ans[tail1], q[head0]) ) { --tail1; --tail0; }
  while (head1 <= tail1 && !satisfy(ans[head1], q[tail0]) ) { ++head1; ++head0; }
  
  ans[ ++tail1 ] = crosspoint( q[tail0], q[head0] );
  
  if (tail1 - head1 + 1<= 2) 
  {
    delete [] q;
    delete [] ans;
    return 0;
  }
  
  int m = 0;
  
  for (int i = head1; i <= tail1; ++i) P[ ++m ] = ans[i];
  
  delete [] q;
  delete [] ans;
  
  return m;
}

double getArea(pnt *p, int n)
{
  double res = 0;
  
  p[n+1] = p[1];
  for (int i = 1; i <= n; ++i)
    res += p[i] * p[i+1];
    
  return fabs(res) / 2;
}

int main()
{
  int TestCase;
  scanf("%d",&TestCase);
  
  P2[0] = pnt(0,0);  
  P2[1] = pnt(4095,0);  
  P2[2] = pnt(4095,4095);  
  P2[3] = pnt(0,4095);  
  P2[4] = P2[0];
  //The Border 

  for (int ttt = 1; ttt <= TestCase; ++ttt)
  {
    scanf("%d%d",&N,&M);
    for (int i = 1; i <= N; ++i)
    {
      sumx[i] = sumx2[i] = sumy[i] = sumy2[i] = 0;
      for (int j = 1; j <= M; ++j)
      {
        double x,y;
        scanf("%lf%lf",&x,&y);
      /*  sumx[i] += x; sumy[i] += y;
        sumx2[i] += x*x; sumy2[i] += y*y;*/    
              
        //for computing the half-plane
      }
    }
    
    for (int i = 1; i <= N; ++i)
    { 
    //  int cnt = 0;
      for (int j = 1; j <= N; ++j)
        if (i != j)
        {
        /*  double A = -2.0 * ( sumx[i] - sumx[j] );
          double B = -2.0 * ( sumy[i] - sumy[j] );
          double C = sumx2[i] - sumx2[j] + sumy2[i] - sumy2[j];
          
          pnt p ;
          pnt v = pnt(-B, A);
          
          if (fabs(A) > fabs(B)) p = pnt(-C/A, 0); else p = pnt(0, -C/B);
          */   
          
          //computing the half-plane
          L[ ++cnt ] = LINE(p, p + v);
        }
        
      for (int j = 0; j < 4; ++j) L[ ++cnt ] = LINE(P2[j], P2[j+1]);  //adding the border
      
      int n = HalfPlaneIntersection(L, cnt, P);  //return the number of vertex
      res[i] = getArea(P,n);
    }
    
    printf("Case #%d:",ttt);
    for (int i = 1; i <= N; ++i) printf(" %d",(int)(res[i] + 0.5)); 
    printf("\n");
  }

  return 0;
}
