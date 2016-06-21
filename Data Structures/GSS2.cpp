/* 支持区间整体添加 delta 查询历史最大值 */

#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN=100010,MAXQ=100010,offset=100000;

typedef long long LL;

LL ans[MAXQ],delta_now[MAXN*2],delta_before[MAXN*2],max_now[MAXN*2],max_before[MAXN*2];
int Q,N,a[MAXN],A,B,pos[MAXN*2],tot,pre[MAXN];
int g[MAXN],next[MAXQ],num[MAXQ],cost[MAXQ],L[MAXN*2],R[MAXN*2],lch[MAXN*2],rch[MAXN*2];

inline void read(int &x)
{
  char ch; int tmp=1;
  while (ch=getchar(),(ch>'9' || ch<'0') && (ch!='-')) ;
  if (ch=='-') { tmp=-1; ch=getchar(); } x=ch-48;
  while (ch=getchar(),ch<='9' && ch>='0') x=x*10+ch-48;
  x*=tmp;
}

inline void addedge(int A,int B,int C) { ++tot; num[tot]=B; next[tot]=g[A]; g[A]=tot; cost[tot]=C; }

void make(int A,int B)
{
  int now=++tot;
  L[now]=A; R[now]=B;
  if (A<B)
  {
    lch[now]=tot+1;
    make(A,(A+B)>>1);
    rch[now]=tot+1;
    make(((A+B)>>1)+1,B);
  }
}

inline void pushdown(int now)
{
  if (delta_before[now])
  {
    delta_before[lch[now]]=max(delta_before[lch[now]],delta_now[lch[now]]+delta_before[now]);
    delta_before[rch[now]]=max(delta_before[rch[now]],delta_now[rch[now]]+delta_before[now]);
    max_before[lch[now]]=max(max_before[lch[now]],max_now[lch[now]]+delta_before[now]);
    max_before[rch[now]]=max(max_before[rch[now]],max_now[rch[now]]+delta_before[now]);
    delta_before[now]=0;
  }
  if (delta_now[now])
  {
    delta_now[lch[now]]+=delta_now[now];
    delta_now[rch[now]]+=delta_now[now];
    max_now[lch[now]]+=delta_now[now];
    max_now[rch[now]]+=delta_now[now];
    delta_now[now]=0;
  }
}

inline void update(int now)
{
  max_now[now]=max(max_now[lch[now]],max_now[rch[now]]);
  max_before[now]=max(max_before[now],max_now[now]);
}

void modify(int now,int x,int y,int delta)
{
  if (x<=L[now] && R[now]<=y)
  {
    delta_now[now]+=delta;
    delta_before[now]=max(delta_before[now],delta_now[now]);
    max_now[now]+=delta;
    max_before[now]=max(max_before[now],max_now[now]);
  }
  else
  {
    pushdown(now);
    if (x<L[rch[now]]) modify(lch[now],x,y,delta);
    if (y>R[lch[now]]) modify(rch[now],x,y,delta);
    update(now);
  }
}

LL query(int now,int x,int y)
{
  if (x<=L[now] && R[now]<=y) return max_before[now];
  else
  {
    pushdown(now);
    LL res=0;
    if (x<L[rch[now]]) res=max(res,query(lch[now],x,y));
    if (y>R[lch[now]]) res=max(res,query(rch[now],x,y));
    return res;
  }
}

int main()
{
  read(N);
  for (int i=1;i<=N;++i)
  {
    read(a[i]);
    pre[i]=pos[a[i]+offset];
    pos[a[i]+offset]=i;
  }
  
  read(Q);
  for (int i=1;i<=Q;++i)
  {
    read(A); read(B);
    addedge(B,A,i);
  }
  
  tot=0;
  make(1,N);

  for (int i=1;i<=N;++i)
  {
    modify(1,pre[i]+1,i,a[i]);
    for (int now=g[i];now;now=next[now])
      ans[cost[now]]=query(1,num[now],i);
  }

  for (int i=1;i<=Q;++i) printf("%lld\n",ans[i]);
  return 0;
}
