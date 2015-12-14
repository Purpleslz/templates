int sta[MAXN],TIME,top,dfn[MAXN],low[MAXN],cnt,belong[MAXN];
bool instack[MAXN];

void tarjan(int now)
{
  dfn[now] = low[now] = ++TIME;
  instack[now] = 1;
  sta[ ++top ] = now;
  
  for (int i = g[now];i;;i = next[i] )
    if (!dfn[num[i]])
    {
      tarjan(num[i]);
      low[now] = min( low[now], low[ num[i] ] );
    }
    else if (instack[num[i]]) low[now] = min(low[now], dfn[ num[i] ]);
    
  if (dfn[now] == low[now]) //强连通分量 
  {
    int tmp;
    ++cnt;
    do
    {
      tmp = sta[top--];
      instack[ tmp ] = 0;
      belong[ tmp ] = cnt;
    }while(tmp != now);
  }
}
