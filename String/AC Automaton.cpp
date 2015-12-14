void make(int a,int b,int len)
{
  for(;b<len;++b)
  {
    if (!g[a][s[b]-64]) g[a][s[b]-64]=++tot;
    a=g[a][s[b]-64];
  }
}

void build()
{
  head=tail=0;
  for (int i=1;i<=26;++i) if (g[0][i]) q[++tail]=g[0][i];
  while (head!=tail)
  {
    ++head; int x=q[head];
    for (int i=1;i<=26;++i)
      if (g[x][i])
      {
        int num=g[x][i],now=fail[x];
        fail[num]=g[now][i];
        
        q[++tail]=num;
      }
      else g[x][i]=g[fail[x]][i];
  }
}

int main()
{

  for (int i=1;i<=n;++i)
  {
    scanf("%s",s);
    make(0,0,strlen(s));
  }
  
  build();
}
