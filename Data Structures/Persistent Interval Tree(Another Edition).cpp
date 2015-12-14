/* hihocoder Couple Tree */ 

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 100000 + 10;

int TIME,N,M;

struct graph
{
  int g[MAXN],num[MAXN*2],next[MAXN*2],tot,fa[MAXN],dist[MAXN];
  int pos1[MAXN],pos2[MAXN];
  int N;
  graph() { }
  
  inline void clr()
  {
    memset(g,0,sizeof(g));
    tot = 1;
  }
  
  inline void addedge(int a,int b)
  {
    ++tot; num[tot] = b; next[tot] = g[a]; g[a] = tot;
  }
  
  void dfspos(int now)
  {
    pos1[now] = ++ TIME;
    for (int i = g[now]; i; i = next[i])
    {
      dist[ num[i] ] = dist[now] + 1 ; 
      dfspos( num[i] ) ;
    }
    pos2[now] = ++ TIME; 
  }
  
}G[2];

struct SegmentTree
{
  int lch,rch,lazy;
}T[MAXN*50];
int root[MAXN],tot;

void maketree(int &now, int l , int r)
{
  now = ++tot; 
  T[now].lazy = 1;
  /*if (l < r)
  {
    int mid = (l + r) / 2;
    
    maketree(T[now].lch,l,mid);
    maketree(T[now].rch,mid+1,r);

  }*/
}

inline void push(int now)
{
  if (T[now].lazy)
  {
    ++tot;
    T[now].lch = tot;
    ++tot;
    T[now].rch = tot;
    T[ T[now].lch ].lazy = T[ T[now].rch ].lazy = T[now].lazy; 
    T[now].lazy = 0;
  }
}

void modify(int &now,int l,int r,int x,int y,int k)
{
  ++tot;
  T[tot] = T[now];
  now = tot;
  
  if (x<=l && r<=y)
  {
    T[now].lazy = k;
    return ;
  }
  
  push(now);
  
  int mid = (l+r) / 2;
  if (x <= mid) modify(T[now].lch, l,   mid, x, y , k );
  if (y >  mid) modify(T[now].rch, mid+1, r, x, y , k );
}

int query(int now, int l, int r, int x)
{
  if (T[now].lazy) return T[now].lazy;
  int mid = (l+r) / 2;
  if ( x <= mid) return query( T[now].lch, l ,mid, x); else return query( T[now].rch, mid+1, r , x);
}

void dfs(int x,int now)
{
  int y = 1 - x;
  for (int i = G[x].g[now]; i; i = G[x].next[i])
  {
    int k = G[x].num[i];
    modify( root[ k ] = root[ now ], 1, 2*N, G[ y ].pos1[ k ], G[ y ].pos2[ k ] , k );
    dfs( x, k );
  }
}

int main()
{
  while (scanf("%d%d",&N,&M) != EOF)
  {
    
    for (int t = 0; t < 2; ++t)
    {
      G[t].clr();
      for (int i=2;i<=N;++i)
      {
        scanf("%d",&G[t].fa[i]);
        G[t].addedge( G[t].fa[i], i );
      }
    }
    
    memset(root,0,sizeof(root));
    tot = 0;
    maketree(root[1],1,2*N);
    
    for (int t = 0; t < 2; ++t )
    {
      TIME = 0;
      G[t].dist[1] = 1;
      G[t].dfspos(1);
    }
    
    dfs(0,1);
    
    int ans = 0;
    
    for (int i=1; i<=M ; ++i)
    {
      int X,Y;
      scanf("%d%d",&X,&Y);
      X = ( X + ans ) % N + 1;
      Y = ( Y + ans ) % N + 1;
      
      ans = query( root[X], 1, 2*N, G[1].pos1[Y] );
      
      printf("%d %d %d\n",ans,G[0].dist[X] - G[0].dist[ans] + 1 , G[1].dist[Y] - G[1].dist[ans] + 1); 
    }
  }
  
  return 0;
}
