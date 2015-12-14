
void add(int ch,int mlen)
{
  int now=++tot,p=tail;
  maxlen[now]=mlen;
  tail=tot;
   
  for (;p && !g[p][ch];p=parent[p]) g[p][ch]=now;
   
  if (!p) parent[now]=root;
  else
    if (maxlen[p]+1==maxlen[ g[p][ch] ]) parent[now]=g[p][ch];
    else
    {
      int tmp=g[p][ch];
       
      ++tot; 
      maxlen[tot]=maxlen[ p ]+1;
      parent[tot]=parent[ tmp ];
      for (int i=0;i<MAXALPHA;++i) g[tot][i]=g[ tmp ][i];
      parent[ tmp ] = parent[ now ] = tot;
       
      for (;p && g[p][ch]==tmp;p=parent[p]) g[p][ch]=tot; 
    }
}
