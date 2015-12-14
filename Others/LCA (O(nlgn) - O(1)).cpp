void dfs(int now)
{  
  fir[now] = ++len;
  q[len] = now;
  
  for (int i=g[now];i;i=NEXT[i])
    if (num[i] != fa[now])
    {
      fa[ num[i] ] = now;
      depth[ num[i] ] = depth[now] + 1;
      dfs(num[i]);
      
      q[++len] = now;
    }
}

inline int getlca(int a,int b)
{
  int tmp = log2[b-a+1];
  if (depth[ MIN[a][tmp] ] < depth[ MIN[b-(1<<tmp)+1][tmp] ])
    return MIN[a][tmp];
  else
    return MIN[ b - (1<<tmp) + 1 ][tmp];
}

int main()
{
    for (int i=1;i<=len;++i) MIN[i][0] = q[i];
    
    for (int j=1;(1<<j)<=len;++j)
    {
      int tmp = len - (1<<j) + 1;
      for (int i=1;i<=tmp;++i)
        if (depth[ MIN[i][j-1] ] < depth[ MIN[i + (1<<(j-1)) ][j-1] ])
          MIN[i][j] = MIN[i][j-1];
        else
          MIN[i][j] = MIN[i + (1<<(j-1))][j-1];      
    }
    
    //fir[a] < fir[b]
    getlca(fir[a],fir[b]);
}
