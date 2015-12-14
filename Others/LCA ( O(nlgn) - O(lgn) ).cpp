
int getlca(int a,int b)
{
  if (dep[a]<dep[b]) swap(a,b);
  
  for (int i = MAXC-1; i >= 0; --i)
    if ( dep[ fa[a][i] ] >= dep[b] )
      a = fa[a][i];
  
  if (a == b) return a;
  
  for (int i = MAXC-1; i >= 0; --i)
    if (fa[a][i] != fa[b][i])
      a = fa[a][i], b = fa[b][i];
  
  return fa[a][0];
}
