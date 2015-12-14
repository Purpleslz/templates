
/* 朱刘算法 O(VE) */
/* 无根情况 新加一个点 到所有点的距离为一个极大值（所有权值和+1） 最后减去（所有权值和+1） */
/* POJ 3164 */
 
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

const int MAXN = 100 + 10;
const int MAXM = 10000 + 10;
const double eps = 1e-8;
const int oo = 10000000;

double px[MAXN],py[MAXN];

struct EDGE
{
  int x,y;
  double z;
  EDGE() {}
  EDGE(int _x,int _y,double _z) { x=_x; y=_y; z=_z; }
}edge[MAXM];

double dist(double x1,double y1,double x2,double y2) { return sqrt( (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2) ); }

int pre[MAXN],v[MAXN],belong[MAXN],N,M;
double MIN[MAXN];

double Minimum_Directed_MST(int root,int n,int m)
{
  double res = 0;
  
  int times = 0;
  
  for (int i=1;i<=n;++i) v[i] = 0;
  
  while (1)
  {
    for (int i=1;i<=n;++i) { MIN[i] = oo; pre[i] = belong[i] = -1; }
    
        
    for (int i=1;i<=m;++i)
    {
      int x = edge[i].x,y = edge[i].y;
      if ( (edge[i].z < MIN[y]) && (x != y) )                             //找最小入边 
      {
        pre[y] = x;
        MIN[y] = edge[i].z;
      }
    }
    
    for (int i=1;i<=n;++i) if (i!=root && pre[i] == -1) return -1;   //无解 
    
    int cnt = 0;
    
    MIN[root] = 0;
    
    for (int i=1;i<=n;++i)                                       //寻找所有环 
    {
      ++times;
      res += MIN[i];
      int now = i;
      
      while ( (v[now] != times) && ( belong[now] == -1 ) && ( now != root ) )
      {
        v[now] = times;
        now = pre[now];
      }
      
      if ( (now != root) && (belong[now] == -1) ) 
      {
        ++cnt;
        for (int x = pre[now]; x != now; x = pre[x] ) belong[x] = cnt;
        belong[now] = cnt;
      }
    }
    
    if (cnt == 0) break;                                        //没有环 
    
    for (int i=1;i<=n;++i) if (belong[i] == -1) belong[i] = ++cnt;
    
    for (int i=1;i<=m;++i)
    {
      int x = edge[i].x;
      int y = edge[i].y;
      edge[i].x = belong[x];
      edge[i].y = belong[y];
      if (belong[x] != belong[y]) edge[i].z -= MIN[y];
    }
    
    n = cnt;
    root = belong[root];
  }
  
  return res;
}

int main()
{
  while (scanf("%d%d",&N,&M)!=EOF)
  {
    for (int i=1;i<=N;++i) scanf("%lf%lf",&px[i],&py[i]);
    
    for (int i=1;i<=M;++i)
    {
      int a,b;
      scanf("%d%d",&a,&b);
      edge[i] = EDGE(a,b,dist( px[a],py[a],px[b],py[b] ) );
    }
    
    double res = Minimum_Directed_MST(1,N,M);
    
    if (res < eps) printf("poor snoopy\n"); else printf("%.2f\n",res);
  }
  return 0;
}

