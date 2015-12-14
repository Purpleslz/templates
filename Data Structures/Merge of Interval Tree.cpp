/* POI 2011 Tree Rotations */

#include <iostream>
#include <cstdio>
using namespace std;

#define min(a,b) ( ((a)<(b))?(a):(b) )

const int MAXN=400005,MAXP=1000000;

typedef long long LL;

int N,n,lt[MAXN],rt[MAXN],val[MAXN],tot;
int q[MAXP],top,size[MAXN],root[MAXN];
LL f[MAXN],ans0[MAXN],ans1[MAXN];

inline void read(int &x)
{
  char ch;
  while (ch=getchar(),ch>'9' || ch<'0') ; x=ch-48;
  while (ch=getchar(),ch<='9' && ch>='0') x=x*10+ch-48;
}

struct SegmentTree { int lch,rch,cnt; }tree[MAXP];

int merge(int A,int B,LL &ans0,LL &ans1)
{
  if (A==0 || B==0) return A+B;
  ans0+=(LL)tree[tree[A].rch].cnt*tree[tree[B].lch].cnt;
  ans1+=(LL)tree[tree[B].rch].cnt*tree[tree[A].lch].cnt;
  tree[A].lch=merge(tree[A].lch,tree[B].lch,ans0,ans1);
  tree[A].rch=merge(tree[A].rch,tree[B].rch,ans0,ans1);
  tree[A].cnt=tree[tree[A].lch].cnt+tree[tree[A].rch].cnt;
  q[++top]=B;
  return A;
}

int make(int ll,int rr,int target)
{
  int now;
  if (top) now=q[top--]; else now=++tot;
  tree[now].lch=tree[now].rch=0;
  tree[now].cnt=1;
  if (ll<rr)
  {
    int mid=(ll+rr)>>1;
    if (target<=((ll+rr)>>1)) tree[now].lch=make(ll,mid,target); else tree[now].rch=make(mid+1,rr,target);
  }
  return now;
}

int init()
{
  int now=++n;
  read(val[now]);
  ++size[now];
  if (!val[now])
  {
    lt[now]=init();
    rt[now]=init();
    size[now]+=size[lt[now]]+size[rt[now]];
  }
  return now;
}

void dfs(int now)
{
  if (val[now]) root[now]=make(1,N,val[now]);
  else
  {
    if (size[lt[now]]>=size[rt[now]]) {dfs(lt[now]); dfs(rt[now]);} else  {dfs(rt[now]); dfs(lt[now]); }
    root[now]=merge(root[lt[now]],root[rt[now]],ans0[now],ans1[now]);
    f[now]=f[lt[now]]+f[rt[now]];
    f[now]+=min(ans0[now],ans1[now]);
  }
}

int main(void)
{
  read(N);
  init();
  dfs(1);
  printf("%lld\n",f[1]);
  return 0;
}
