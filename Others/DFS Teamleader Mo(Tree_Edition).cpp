
void dfs(int x)
{
  for (int i=1;i<MAXC;++i) fa[x][i] = fa[ fa[x][i-1] ][i-1];
  
  pos[x] = ++tot;
  for (int i=g[x];i;i=next[i])
    if (num[i] != fa[x][0])
    {
      fa[ num[i] ][0] = x;
      dep[ num[i] ] = dep[x] + 1;
      dfs(num[i]);
    }
}
