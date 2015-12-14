
inline bool cmp(int a,int b) { return s[a]<s[b]; }

void doit()
{
  for (int i=1;i<=n;++i) sa[i] = i;  
  sort(sa+1,sa+n+1,cmp);
  rank[sa[1]]=1;
  for (int i=2;i<=n;++i) rank[sa[i]]=rank[sa[i-1]]+(s[sa[i-1]]!=s[sa[i]]);
  for (int j=1;rank[sa[n]]!=n;j<<=1)
  {
    for (int i=1;i<=n;++i) b[rank[sa[i]]]=i;
    for (int i=n;i;--i) if (sa[i]>j) newsa[b[rank[sa[i]-j]]--]=sa[i]-j;
    for (int i=n-j+1;i<=n;++i) newsa[b[rank[i]]]=i;
    newrank[newsa[1]]=1;
    for (int i=2;i<=n;++i)
      newrank[newsa[i]]=newrank[newsa[i-1]]+( rank[newsa[i]]!=rank[newsa[i-1]] || rank[newsa[i]+j]!=rank[newsa[i-1]+j] );
    for (int i=1;i<=n;++i)
    {
      sa[i]=newsa[i]; rank[i]=newrank[i];
    }
  }
  
  for (int i=1;i<=n;++i)
    if (rank[i]==1) h[i]=0;
    else
    {
      h[i]=max(h[i-1]-1,0);
      while (a[i+h[i]]==a[sa[rank[i]-1]+h[i]]) ++h[i];
    }
  
  for (int i=1;i<=n;++i) height[rank[i]]=h[i];
}
