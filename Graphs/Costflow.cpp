
bool spfa()
{
  int head=0,tail=1;
  q[1]=S;
  for (int i=0;i<=sink;++i) v[i]=0,dist[i]=oo; //初始化所有点的v和dist 
  dist[S]=0; low[S]=oo; 
   
  while (head!=tail)
  {
    head = (head+1) % limit; //limit是循环队列长度 
    int x=q[head]; 
    v[x]=0; 
      
    for (int i=g[x];i;i=next[i])
      if (c[i] && dist[num[i]]>dist[x]+cost[i])
      {
        dist[num[i]]=dist[x]+cost[i];
        pre[num[i]]=i; low[num[i]]=min(low[x],c[i]);
         
        if (!v[num[i]])
        {
          v[num[i]]=1;
          tail = (tail+1) % limit;//limit是循环队列长度 
          q[tail]=num[i]; 
        }
      }
  }
  return dist[sink]<oo; 
}
 
void augument()
{
  total+=low[sink]*dist[sink];
  for (int now=sink;now!=S;now=num[pre[now]^1])
  {
    c[pre[now]]-=low[sink];
    c[pre[now]^1]+=low[sink]; 
  } 
}

int main()
{
  while (spfa()) augument();
}
