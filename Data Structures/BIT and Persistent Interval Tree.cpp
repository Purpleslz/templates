 
const int MAXN = 50000 + 5;
const int MAXM = 10000 + 5;
 
int a[MAXN],MAXV,barrel[MAXN+MAXM],tot,N,M;
 
const int MAXNODE = 3000000;
 
struct TREE
{
  int lch,rch,size;
  TREE() { lch = 0; rch = 0; size = 0; }
}T[MAXNODE];
 
int root[MAXN],ql[MAXN],qr[MAXN];
 
inline int lowbit(int x) { return (x & (-x));  }
 
struct rec
{
  int x,y,k,type;
  rec() {}
  rec(int _type,int _x,int _y,int _k = 0)
  {
    type = _type;
    x = _x;
    y = _y;
    k = _k;
  }
}q[MAXM];
 
void add(int &now,int l,int r,int x,int y)
{
  T[++tot] = T[now];
  now = tot;
   
  T[now].size += y;
 
  if (l<r)
  {
    int mid = (l+r)/2;
    if (x<=mid) 
      add(T[now].lch,l,mid,x,y);
    else
      add(T[now].rch,mid+1,r,x,y);
  }
}
 
void Bins(int x,int k,int v)
{
  for (;x<=N;x+=lowbit(x)) add(root[x],1,MAXV,k,v);
}
 
int query(int x,int y,int k)
{
  --x;
   
  int tl=0,tr=0;
   
  for (int i=x;i;i-=lowbit(i)) ql[++tl] = root[i];
  for (int i=y;i;i-=lowbit(i)) qr[++tr] = root[i];
   
  int l = 1, r = MAXV;
  while (l<r)
  {
    int mid = (l+r)/2;
     
    int sum = 0;
    for (int i=1;i<=tl;++i) sum -= T[ T[ ql[i] ].lch ].size;
    for (int i=1;i<=tr;++i) sum += T[ T[ qr[i] ].lch ].size;
     
    if (sum>=k) 
    {  
      for (int i=1;i<=tl;++i) ql[i] = T[ ql[i] ].lch; 
      for (int i=1;i<=tr;++i) qr[i] = T[ qr[i] ].lch;
      r = mid;
    } 
    else
    { 
      k-=sum; 
      for (int i=1;i<=tl;++i) ql[i] = T[ ql[i] ].rch; 
      for (int i=1;i<=tr;++i) qr[i] = T[ qr[i] ].rch;
      l = mid + 1;
    }
  }
  return barrel[l];
}
 
void init()
{
  sort( barrel + 1, barrel + MAXV + 1);
  MAXV = unique( barrel + 1, barrel + MAXV + 1) - barrel - 1;
   
  for (int i=1;i<=N;++i) a[i] = lower_bound(barrel + 1, barrel + MAXV + 1, a[i]) - barrel;
  for (int i=1;i<=M;++i)
    if (q[i].type == 1)
      q[i].y = lower_bound(barrel + 1, barrel + MAXV + 1, q[i].y) - barrel;
       
  tot = 0;
  for (int i=0;i<=N;++i) root[i] = 0;
   
  for (int i=1;i<=N;++i) Bins(i,a[i],1);
}
 
void work()
{
  for ( int i = 1; i <= M ; ++i )
    if (q[i].type == 0)
      printf("%d\n",query(q[i].x,q[i].y,q[i].k));
    else
    {
      Bins(q[i].x,a[ q[i].x ],-1);
      a[ q[i].x ] = q[i].y;
      Bins(q[i].x,a[ q[i].x ],1);
    }
}
