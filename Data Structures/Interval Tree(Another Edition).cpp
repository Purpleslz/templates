/* [POI2006]Tet-Tetris 3D */

#include <iostream>
#include <cstdio>
using namespace std;

const int MAXR=1110,MAXC=1110;

struct rec
{
  int a,b;
  rec () {a=b=0; };
}MAX[MAXR*2][MAXC*2],mark[MAXR*2][MAXC*2];

int R,C,N;
int x,y,d,s,w;

int query2(int now,int L,int R,int l,int r,rec *tree)
{
  if (l<=L && R<=r) return tree[now].a;
  int ret=tree[now].b,mid=(L+R)>>1;
  if (l<=mid) ret=max(ret,query2(now<<1,L,mid,l,r,tree));
  if (r>mid) ret=max(ret,query2(now<<1|1,mid+1,R,l,r,tree));
  return ret;
}

int query1(int now,int L,int R,int l1,int r1,int l2,int r2)
{
  int ret=query2(1,1,C,r1,r2,mark[now]);
  if (l1<=L && R<=l2) return max(ret,query2(1,1,C,r1,r2,MAX[now]));
  int mid=(L+R)>>1;
  if (l1<=mid) ret=max(ret,query1(now<<1,L,mid,l1,r1,l2,r2));
  if (l2>mid) ret=max(ret,query1(now<<1|1,mid+1,R,l1,r1,l2,r2));
  return ret;
}

void modify2(int now,int L,int R,int l,int r,rec *tree,int v)
{
  if (v>tree[now].a) tree[now].a=v;
  if (l<=L && R<=r)
  {
    if (v>tree[now].b) tree[now].b=v;
    return ;
  }
  int mid=(L+R)>>1;
  if (l<=mid) modify2(now<<1,L,mid,l,r,tree,v);
  if (r>mid) modify2(now<<1|1,mid+1,R,l,r,tree,v);
}

void modify1(int now,int L,int R,int l1,int r1,int l2,int r2,int v)
{
  modify2(1,1,C,r1,r2,MAX[now],v);
  if (l1<=L && R<=l2) { modify2(1,1,C,r1,r2,mark[now],v); return ; }
  int mid=(L+R)>>1;
  if (l1<=mid) modify1(now<<1,L,mid,l1,r1,l2,r2,v);
  if (l2>mid) modify1(now<<1|1,mid+1,R,l1,r1,l2,r2,v);
}

int main(void)
{
  scanf("%d%d%d",&R,&C,&N);
  ++R;++C;
  for (int i=1;i<=N;++i)
  {
    scanf("%d%d%d%d%d",&d,&s,&w,&x,&y);
    ++x; ++y; d+=x-1; s+=y-1;
    int z=query1(1,1,R,x,y,d,s);
    modify1(1,1,R,x,y,d,s,z+w);
  }
  printf("%d\n",MAX[1][1].a);
  return 0;
}
