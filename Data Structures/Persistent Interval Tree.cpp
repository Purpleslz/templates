const int MAXN = 100000 + 10,MAXNODE = 2000000 + 10;

int root[MAXN],lch[MAXNODE],rch[MAXNODE],size[MAXNODE],MAXV;
int barrel[MAXN],tot,N,M,a[MAXN];

inline void update(int x) { size[x] = size[lch[x]] + size[rch[x]]; }

void add(int &now,int pre,int l,int r,int x)
{
  now = ++tot;
  
  if (l==r)
  {
    size[now] = size[pre] + 1;
  }
  else
  {
    int mid = (l+r)/2;
    if (x<=mid)
    {
      rch[now] = rch[pre];
      add(lch[now],lch[pre],l,mid,x);
    }
    else
    {
      lch[now] = lch[pre];
      add(rch[now],rch[pre],mid+1,r,x);
    }
    update(now);
  }
}

int query(int a,int l,int r,int x,int y )
{
  if (x<=l && r<=y) return size[a]; 
  
  int mid = (l+r) / 2;
  int res = 0;
  if (x<=mid) res += query(lch[a],l,mid,x,y);
  if (y>mid) res+= query(rch[a],mid+1,r,x,y);
  return res;
}

int query(int a,int b,int l,int r,int x,int y )
{
  
//  cout << a << " " << b << " " << l << " " << r << " " << x << " " << y << " " << size[b] << " " << size[a] << endl;
  if (x<=l && r<=y) return size[b] - size[a]; 
  
  int mid = (l+r) / 2;
  int res = 0;
  if (x<=mid) res += query(lch[a],lch[b],l,mid,x,y);
  if (y>mid) res+= query(rch[a],rch[b],mid+1,r,x,y);
  return res;
}

int check(int x,int y,int z)
{
  return query(root[x-1],root[y],1,MAXV,1,z);
  //return query(root[y],1,MAXV,1,z) - query(root[x-1],1,MAXV,1,z);  //均可。。 
}
