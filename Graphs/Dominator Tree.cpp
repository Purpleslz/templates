/* SPOJ BIA */
/* idom[i] 从起点到i最近必须经过的点 */
/* dom[i] 从起点到i必须经过的点 */
/* semi[i] 半必经点 走树枝边可以到达的dfn最小的点 */
 

#include <iostream> 
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=200000+10;

int N,M,TIME;
int dfn[MAXN],id[MAXN],idom[MAXN],fa[MAXN];
vector <int> dom[MAXN],pred[MAXN],succ[MAXN];
int anc[MAXN],semi[MAXN],best[MAXN];

void init()
{
  for (int i=1;i<=N;++i)
  {
    dfn[i]=id[i]=fa[i]=idom[i]=0; //idom??
    anc[i]=semi[i]=best[i]=i; //idom?? chongfu
    dom[i].clear();
    succ[i].clear();
    pred[i].clear();
  }
  TIME=0;
}

void dfs(int now)
{
  int x;
  dfn[now]=++TIME; id[dfn[now]]=now;
  for (int i=0;i<succ[now].size();++i)
    if (!dfn[x=succ[now][i]])
    {
      dfs(x);
      fa[dfn[x]]=dfn[now];
    }
}

int get(int now)
{
  if (now==anc[now]) return now;
  int y=get(anc[now]);
  if (semi[best[now]]>semi[best[anc[now]]]) best[now]=best[anc[now]];
  return anc[now]=y;
}

void tarjan()
{
  for (int y=TIME;y>1;--y)
  {
    for (int i=0;i<pred[id[y]].size();++i)
    {
      int x=dfn[pred[id[y]][i]];
     // if (x==0) continue; // ??
      get(x);
      if (semi[best[x]]<semi[y]) semi[y]=semi[best[x]];
    }

    int x=fa[y];
    dom[semi[y]].push_back(y);
    anc[y]=x;
    
    for (int i=0;i<dom[x].size();++i)
    {
      int z=dom[x][i];
      get(z);
      if (semi[best[z]]<x) idom[z]=best[z]; else idom[z]=x;
    }
    dom[x].clear();
  }
  for (int x=2;x<=TIME;++x)
  {
   // int x=id[i];
    if (idom[x]!=semi[x]) idom[x]=idom[idom[x]];// else idom[x]=semi[idom[x]];
    dom[idom[x]].push_back(x);
  }
  idom[1]=0;
}

int main()
{

 while(cin>>N>>M)
 // while (~scanf("%d%d",&N,&M))
  {
    init();
    for (int i=1,a,b;i<=M;++i)
    {
      scanf("%d%d",&a,&b);
      pred[b].push_back(a);
      succ[a].push_back(b);
    }
    dfs(1);
    tarjan();
    
    int ans=0;
    for (int i=1;i<=N;++i) if (dom[i].size()) ++ans;
    printf("%d\n",ans);
    for (int i=1;i<=N;++i) if (dom[dfn[i]].size()) printf("%d ",i);
    printf("\n");
  }
  return 0;
}
