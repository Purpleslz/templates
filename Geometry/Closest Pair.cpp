
int a[MAXN],b[MAXN],c[MAXN],tot,v[MAXN];

inline bool cmpx(int a,int b) { return p[a].x + eps < p[b].x; }
inline bool cmpy(int a,int b) { return p[a].y + eps < p[b].y; }

double closest_pair(int l,int r)
{
  double ans = oo;
  if (r-l<3)
  {
    for (int i=l;i<r;++i)
      for (int j=i+1;j<=r;++j)
        ans = min(ans, getdist( p[a[i]],p[a[j]] ) );
        
    return ans;
  }
  
  int mid = (l+r) >> 1;
  
  ++tot;
  for (int i=l;i<=mid;++i) v[ a[i] ] = tot;
  
  int h1 = l,h2 = mid + 1;
  
  for (int i=l;i<=r;++i)
    if (v[ b[i] ] == tot)
      c[h1++] = b[i];
    else
      c[h2++] = b[i];
      
  for (int i=l;i<=r;++i) b[i] = c[i];
  
  ans = min(closest_pair(l,mid),closest_pair(mid+1,r));
  
  h1 = l,h2 = mid +1;
  
  for (int i=l;i<=r;++i)
    if (( p[ b[h1] ].y<p[ b[h2] ].y || h2>r) && (h1<=mid))
      c[i] = b[h1++];
    else
      c[i] = b[h2++];
      
  for (int i=l;i<=r;++i) b[i] = c[i];

  int n = 0;
  
  double mm = p[ a[mid] ].x;

  for (int i=l;i<=r;++i)
    if ( fabs(p[ b[i] ].x - mm) < ans + eps )   // maybe.....
      c[++n] = b[i];
      
  for (int i=1;i<=n;++i)
    for (int j=i+1;j<=min(i+lim,n);++j)  // lim = 7
      ans = min(ans, getdist( p[ c[i] ] , p[ c[j] ] ) );
  
  return ans;
}

double closest_pair()
{
  for (int i=1;i<=N;++i) a[i] = b[i] = i;
  
  sort(a+1,a+N+1,cmpx);
  sort(b+1,b+N+1,cmpy);
  
  return closest_pair(1,N);
}
