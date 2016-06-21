/**************************************************************
    Problem: 2395
    User: CrystalLove
    Language: C++
    Result: Accepted
    Time:1996 ms
    Memory:1004 kb
****************************************************************/
 
#include<cstdio> 
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 200+10;
const int M = 10000+10;
int scan(){int i;scanf("%d",&i);return i;}
int n,m;
struct Edge{
    int a,b,c,d,w;
    Edge(){}
    Edge(int aa,int bb,int cc,int dd):a(aa),b(bb),c(cc),d(dd){}
}edges[M];
int fa[N];
int find(int x){if(!fa[x]) return x;return fa[x] = find(fa[x]);}
bool cmp(Edge a,Edge b){return a.w<b.w;}
struct Point{
    int x,y;
    Point(){}
    Point(int xx,int yy):x(xx),y(yy){}
}ans(1e9,1e9);
typedef long long LL;
Point mst(){
    Point now(0,0);
    memset(fa,0,sizeof(fa));
    sort(edges+1,edges+1+m,cmp);
    for(int i=1;i<=m;i++){
        int a,b;
        a = edges[i].a;
        b = edges[i].b;
        a = find(a);b = find(b);
        if(a!=b){
            if(i&1)fa[a] = b;
            else fa[b] = a;
            now.x+=edges[i].c;
            now.y+=edges[i].d;
        }
    }
    if((LL)ans.x*ans.y==(LL)now.x*now.y && now.x<ans.x)ans=now;
    if((LL)ans.x*ans.y > (LL)now.x*now.y) ans=now;
    return now;
}
LL cross(Point a,Point b,Point c){
    return ((LL)(a.x-c.x)*(b.y-c.y) - (LL)(a.y-c.y)*(b.x-c.x));
}
void solve(Point minc,Point mind){
    LL c = mind.x-minc.x,d = minc.y - mind.y;
    for(int i=1;i<=m;i++) edges[i].w = edges[i].c*d + edges[i].d*c;
    Point now = mst();
    if(cross(now,minc,mind) >= 0)return;
    solve(minc,now);
    solve(now,mind);
}
int main(){
    int i,j,a,b,c,d;
    Point minc,mind;
    n=scan();m = scan();
    for(i=1;i<=m;i++){
        a=scan()+1;b=scan()+1;
        c=scan();d=scan();
        edges[i] = Edge(a,b,c,d);
    }
    for(i=1;i<=m;i++)edges[i].w = edges[i].c;
    minc = mst();
    for(i=1;i<=m;i++)edges[i].w = edges[i].d;
    mind = mst();
    solve(minc,mind);
    printf("%d %d\n",ans.x,ans.y);
    return 0;
}

/**************************************************************
    Problem: 2395
    User: CrystalLove
    Language: C++
    Result: Accepted
    Time:2076 ms
    Memory:1472 kb
****************************************************************/
 
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
 
const int MAXM = 10000 + 10,MAXN = 200 + 10;
 
typedef long long LL;
 
struct rec
{
  int u,v,w,time,cost;
}edge[MAXM];
 
struct pnt { int x,y; };
 
LL ans = 0;
int ansx,ansy,M,N;
 
int f[MAXN];
 
int getfather(int x) { return (x==f[x])?(x):(f[x]=getfather(f[x])); }
 
inline bool cmp(const rec &a,const rec &b) { return a.w<b.w; }
 
pnt solve()
{
  for (int i=1;i<=N;++i) f[i]=i;
  sort(edge+1,edge+M+1,cmp);
 
  pnt res;
  res.x=res.y=0;
 
  for (int i=1,x,y;i<=M;++i)
    if ((x=getfather(edge[i].u))!=(y=getfather(edge[i].v)))
    {
      f[x]=y;
      res.x+=edge[i].cost;
      res.y+=edge[i].time;
    }
 
  if (((LL)res.x*res.y<ans) || (((LL)res.x*res.y==ans) && (res.x<ansx) ) )
  {
    ans=(LL)res.x*res.y;
    ansx=res.x;
    ansy=res.y;
  }
  return res;
}
 
void solve(pnt a,pnt b)
{
  for (int i=1;i<=M;++i) edge[i].w = (a.y-b.y)*edge[i].cost + (b.x-a.x)*edge[i].time;
  pnt c = solve();
  if (a.x<c.x && c.x<b.x)
  {
    solve(a,c);
    solve(c,b);
  }
}
 
int main()
{
  scanf("%d%d",&N,&M);
  for (int i=1,a,b,c,d;i<=M;++i)
  {
    scanf("%d%d%d%d",&edge[i].u,&edge[i].v,&edge[i].cost,&edge[i].time);
    ++edge[i].u; ++edge[i].v;
  }
 
  ans = 100000;
  ans = ans * ans;
 
  for (int i=1;i<=M;++i) edge[i].w=edge[i].cost;
  pnt A=solve();
  for (int i=1;i<=M;++i) edge[i].w=edge[i].time;
  pnt B=solve();
 
  solve(A,B);
 
  printf("%d %d\n",ansx,ansy);
  return 0;
}

