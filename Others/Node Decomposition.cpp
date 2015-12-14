
int getsize(int x,int parent)
{
  size[x]=1;
  for (int i=g[x];i;i=next[i])
    if (num[i]!=parent && !v[num[i]])
      size[x]+=getsize(num[i],x);
  return size[x];
}

int getroot(int x)
{
  getsize(x,0);
  while(1)
  {
    int id=0,MAX=0;
    for (int i=g[x];i;i=next[i]) if (!v[num[i]] && MAX<size[num[i]]) MAX=size[id=num[i]];
    if (MAX<=(size[x]>>1)) break;
    size[x]-=size[id]; size[id]+=size[x]; x=id;
  }
  return x;
}

void dfs(int x)
{
  x=getroot(x);
  v[x]=1;
  
  for (int i=g[x];i;i=next[i]) if (!v[num[i]]) dfs(num[i]);  //分治处理 
  
  //处理当前的 

  v[x]=0;
}
