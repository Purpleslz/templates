#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN=500+10,MAXM=10000+10,oo=100000000;

//int g[MAXN],num[MAXM*2],next[MAXM*2],cost[MAXM*2],tot;
int id[MAXN],delta[MAXN],graph[MAXN][MAXN],N,M,ans;
bool vis[MAXN];

//inline void addedge(int a,int b,int c) { ++tot; num[tot]=b; next[tot]=g[a]; g[a]=tot; cost[tot]=c; }

int doit()
{
  for (int i=1;i<=N;++i) id[i]=i;

  ans=oo;
  
  for (int pre;N>1;N--)
  {
    for (int i=1;i<=N;++i) delta[i]=0,vis[i]=0;
    pre=1; vis[pre]=1;
    for (int times=1;times<N;++times)
    {
      int MAX=0,ch=0;
      for (int i=1,x;i<=N;++i)
        if (!vis[i])
        {
          delta[i]+=graph[id[pre]][id[i]];
          if (delta[i]>MAX) MAX=delta[ch=i];
        }
      vis[ch]=1;
      if (times==N-1)
      {
        ans=min(ans,delta[ch]);
        for (int i=1;i<=N;++i)
        {
          graph[id[pre]][id[i]]+=graph[id[ch]][id[i]];
          graph[id[i]][id[pre]]+=graph[id[i]][id[ch]];
        }
        id[ch]=id[N];
      }
      pre=ch;
    }
  }
  
  return ans;
}

int main()
{
  while (~scanf("%d%d",&N,&M))
  {
  //  for (int i=1;i<=N;++i) g[i]=0; tot=1;
    
    for (int i=1;i<=N;++i)
      for (int j=1;j<=N;++j)
        graph[i][j]=0;
        
    for (int a,b,c,i=1;i<=M;++i)
    {
      scanf("%d%d%d",&a,&b,&c);
    //  addedge(a,b,c);
    //  addedge(b,a,c);
      graph[a][b]+=c;
      graph[b][a]+=c;
    }
    
    printf("%d\n",doit());
  }
  return 0;
}
