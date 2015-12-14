
//寻找询问点最近k点 

struct POINT { int p[2],id; }a[MAXN]; //这是2维 可增加至k维 

inline bool cmp(const POINT &A,const POINT &B) { return A.p[comp]<B.p[comp]; }

inline void update(int now)
{
  x1[now]=min(x1[now],min(x1[lch[now]],x1[rch[now]]));
  y1[now]=min(y1[now],min(y1[lch[now]],y1[rch[now]]));
  x2[now]=max(x2[now],max(x2[lch[now]],x2[rch[now]]));
  y2[now]=max(y2[now],max(y2[lch[now]],y2[rch[now]]));
}

void make(int A,int B,int flag)
{
  int now=++tot;

  comp=flag;
  int mid=(A+B)>>1;
  nth_element(a+A,a+mid,a+B+1,cmp);
  node[now]=mid;

  x1[now]=x2[now]=a[node[now]].p[0];
  y1[now]=y2[now]=a[node[now]].p[1];

  if (A<mid)
  {
    lch[now]=tot+1;
    make(A,mid-1,1-flag);
  }
  if (mid<B)
  {
    rch[now]=tot+1;
    make(mid+1,B,1-flag);
  }
  update(now);
}

LL dist(int x1,int y1,int x2,int y2) { return (LL)(x2-x1)*(LL)(x2-x1)+(LL)(y2-y1)*(LL)(y2-y1); }  //欧几里得距离 也可求其他 

LL getdist(int X,int Y,int now)
{
  int dx=max(ABS(X-x1[now]),ABS(X-x2[now])),dy=max(ABS(Y-y1[now]),ABS(Y-y2[now]));
  return (LL)dx*(LL)dx+(LL)dy*(LL)dy;
}//要小于等于实际距离 

void query(int now)
{
  int t=node[now];
  int i=tail;

  LL dis=dist(a[t].p[0],a[t].p[1],X,Y);
  while (i && ((dis>d[i]) || (dis==d[i] && a[t].id<a[q[i]].id)) ) { d[i+1]=d[i]; q[i+1]=q[i]; --i; }
  q[i+1]=t; d[i+1]=dis; ++tail; if (tail>K) tail=K;

  LL A,B;
  if (lch[now]) A=getdist(X,Y,lch[now]); else A=0;
  if (rch[now]) B=getdist(X,Y,rch[now]); else B=0;
  if (A>B)
  {
    if (lch[now] && (tail<K || A>=d[K])) query(lch[now]);
    if (rch[now] && (tail<K || B>=d[K])) query(rch[now]);
  }
  else
  {
    if (rch[now] && (tail<K || B>=d[K])) query(rch[now]);
    if (lch[now] && (tail<K || A>=d[K])) query(lch[now]);
  }
}

//答案在d里 存的是距离 

