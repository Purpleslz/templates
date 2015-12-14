bool dfs(int x)
{
  if (x==0) return 1;
  
  for (int i=g[x];i;i=next[i])
    if (!v[num[i]])
    {
      v[num[i]] = 1;
      if (dfs(match[num[i]]))
      {
        match[num[i]] = x;
        return 1;
      }
    }
  return 0;
}

int main()
{

  memset(match,0,sizeof(match));

  for (int i=1;i<=N;++i)
  {
    memset(v,0,sizeof(v));
    if (dfs(i)) ++ans;
  }
  
}
