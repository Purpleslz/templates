inline int sgn(double x) { if (fabs(x)<eps) return 0; else if (x>eps) return 1; else return -1; }

inline double cross(pnt C,pnt A,pnt B) { return (A-C)*(B-C); }  

inline bool cmp(const pnt &a,const pnt &b) { if (a.x == b.x) return a.y < b.y; else return a.x < b.x; }

int ConvexHull(pnt *a, int N, pnt *res)
{
  if (N<3) {  }  //特判 
  
  sort(a+1,a+N+1);
  
  int n = 0;
  
  for (int i=1;i<=N;++i)
  {
    while (n>1 && sgn( cross(res[n-1], res[n], a[i]) ) <=0) --n;
    res[++n] = a[i];
  }
  
  int tmp = n;
    
  for (int i=N-1;i;--i)
  {
    while (n>tmp && sgn( cross(res[n-1], res[n], a[i]) ) <=0) --n;
    res[++n] = a[i];
  }
  
  //1~n n和1 是同一个点 
  if (n>1) --n;
  
  return n;
} 
